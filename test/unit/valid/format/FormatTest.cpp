// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang),run(linux:clang)
// STD: 11+

#include "UnitTest.hpp"
#include <cds/Optional>
#include <cds/String>
#include <cds/StringView>
#include <cds/Tuple>
#include <cds/Union>
#include <cds/collection/Vector>
// #include <format>
// #include <cds/experimental/Format>
#include "../Shared.hpp"

namespace {
using namespace cds;
using namespace cds::impl;

template <typename T> struct TypeId { using Type = T; };
template <typename T> using TypeIdT = typename TypeId<T>::Type;

class FormatException : public Exception {
public:
  ~FormatException() noexcept override = default;
  template <unsigned n> explicit FormatException(char const (&msg)[n]) : _msg{msg} {}
  explicit FormatException(StringView msg) : _msg{msg} {}
  explicit FormatException(String msg) : _msg{mv(msg)} {}

  auto message() const noexcept -> StringView override {
    return _msg;
  }

private:
  String _msg;
};

struct FmtStr {
  StringView val;
  Size argIdx;

  constexpr auto operator==(FmtStr const& o) const noexcept -> bool {
    return argIdx == o.argIdx && val == o.val;
  }

  constexpr auto operator!=(FmtStr const& o) const noexcept -> bool {
    return argIdx != o.argIdx || val != o.val;
  }
};

template <typename C> struct FmtIt {
  using SVIt = typename BaseStringView<C>::ConstIterator;

  constexpr FmtIt(SVIt begin, SVIt end) : _b{begin}, _e{end} {
    goToNext();
  }

  constexpr auto operator*() const noexcept -> Union<BaseStringView<C>, FmtStr> const& {
    assert(_token);
    return *_token;
  }

  constexpr auto operator->() const noexcept -> Union<BaseStringView<C>, FmtStr> const* {
    assert(_token);
    return &*_token;
  }

  constexpr auto operator++() noexcept -> FmtIt& {
    goToNext();
    return *this;
  }

  constexpr auto operator==(Sentinel) const noexcept -> bool {
    return !_token;
  }

  constexpr auto operator!=(Sentinel) const noexcept -> bool {
    return static_cast<bool>(_token);
  }

  enum State {
    ReadingLiteral,
    ReadingFormat,
    ReadingFormatExplicitArgIdx,
    ReadLb,
    ReadRb,
  };

  constexpr auto goToNext() -> void {
    _token = nullopt;
    unsigned brCnt = 1;
    Optional<Size> explicitArgIdx;
    for (auto it = _b; it != _e; ++it) {
      auto v = *it;
      switch (_state) {
        case ReadingLiteral:
          if (v == '{') {
            _state = ReadLb;
          } else if (v == '}') {
            _state = ReadRb;
          }
          break;

        case ReadLb:
          if (v == '{') {
            _state = ReadingLiteral;
          } else {
            _state = ReadingFormatExplicitArgIdx;
            _token = StringView{&*_b, it - _b - 1};
            _isFmt = false;
            _b = it;
            return;
          }
          break;

        case ReadRb:
          if (v == '}') {
            _state = ReadingLiteral;
          } else {
            assert(false);
          }

          break;

        case ReadingFormatExplicitArgIdx:
          if (!StringTraits<C>::isDigit(v)) {
            C const* end = nullptr;
            // auto argIdx = std::strtoull(&*_b, &end, 10);
            Size argIdx = 0;
            auto r = StringUtils<C, StringTraits<C>>::readInt(&*_b, _e - _b, &end, &argIdx, 10);
            // assert(r);
            assert(r || &*_b == end);
            if (r && &*_b != end) {
              explicitArgIdx = argIdx;
            }
            _b = it;
            _state = ReadingFormat;
            [[fallthrough]];
          } else {
            break;
          }

        case ReadingFormat:
          if (v == '}') {
            assert(brCnt > 0);
            --brCnt;
            if (brCnt == 0) {
              _state = ReadingLiteral;
              Size idx = 0;

              if (explicitArgIdx) {
                idx = *explicitArgIdx;
                _explUsed = true;
              } else {
                idx = _implicitArgIdx++;
                _implUsed = true;
              }

              if (_explUsed && _implUsed) {
                throw FormatException("Explicit argument indexing requires all arguments to be indexed");
              }
              // assert(!_explUsed || !_implUsed);
              _token = FmtStr{StringView{&*_b, it - _b}, idx};
              // _token = StringView{&*_b, it - _b};
              _isFmt = true;
              _b = it + 1;
              return;
            }
          } else if (v == '{') {
            ++brCnt;
          } else if (v == ':' && brCnt == 1) {
            _b = it + 1;
          }

          break;

        default:
          assert(false && "unhandled state");
          unreachable();

      }
    }

    if (_b != _e) {
      _token = {&*_b, _e - _b};
      _isFmt = false;
      _b = _e;
    }
  }

  SVIt _b;
  SVIt _e;

  State _state {ReadingLiteral};
  Optional<Union<StringView, FmtStr>> _token;
  bool _isFmt {false};
  Size _implicitArgIdx {0};
  bool _implUsed {false};
  bool _explUsed {false};
};

// CDS_ATTR(constexpr(14)) auto operator""_f(char const* p, size_t len) -> StringView {
//   if (inConstexpr()) {
//     throw "test";
//   }
//   return StringView{p, len};
// }
//
// template <unsigned n> CDS_ATTR(constexpr(14)) auto fmts(char const(&s)[n]) -> StringView {
//   if (inConstexpr()) {
//     throw "test";
//   }
//   return StringView{s, n - 1};
// }

using namespace cds::literals;
using testing::citeq;
using cds::Vector;

template <typename C> class FormatParseContext {
public:
  explicit constexpr FormatParseContext(BaseStringView<C> const& in) : _fmtStr{in} {}

  using Iterator = typename BaseStringView<C>::Iterator;

  constexpr auto begin() const noexcept -> Iterator {
    return _fmtStr.begin();
  }

  constexpr auto end() const noexcept -> Iterator {
    return _fmtStr.end();
  }

private:
  BaseStringView<C> const& _fmtStr;
};

template <typename T> class BackInserterIterator {
public:
  CDS_ATTR(2(explicit, constexpr(11))) BackInserterIterator(T& obj) : _obj{obj} {}
  template <typename V> CDS_ATTR(constexpr(14)) auto operator=(V&& value) noexcept -> BackInserterIterator& {
    _obj.pushBack(fwd<V>(value));
    return *this;
  }

  constexpr auto operator*() noexcept -> BackInserterIterator& {
    return *this;
  }

  constexpr auto operator++() -> BackInserterIterator& {
    return *this;
  }

private:
  T& _obj;
};

template <typename C, typename U, typename A> class BackInserterIterator<BaseString<C, U, A>> {
public:
  CDS_ATTR(2(explicit, constexpr(11))) BackInserterIterator(BaseString<C, U, A>& obj) : _obj{obj} {}
  template <typename V> CDS_ATTR(constexpr(14)) auto operator=(V&& value) noexcept -> BackInserterIterator& {
    _obj += fwd<V>(value);
    return *this;
  }

  constexpr auto operator*() noexcept -> BackInserterIterator& {
    return *this;
  }

  constexpr auto operator++() -> BackInserterIterator& {
    return *this;
  }

private:
  BaseString<C, U, A>& _obj;
};

template <typename C> class FormatContext {
public:
  using Iterator = BackInserterIterator<BaseString<C>>;

  explicit FormatContext(BaseString<C>* result) : _result{result} {}

  auto out() noexcept -> Iterator {
    return Iterator{*_result};
  }

private:
  BaseString<C>* _result;
};

template <typename, typename = char> struct Formatter {};

class FmtRn {
public:
  template <unsigned n> constexpr FmtRn(char const (&str)[n]) : _sv{str, n - 1} {}
  constexpr FmtRn(StringView sv) : _sv{sv} {}
  constexpr auto begin() const noexcept {
    return FmtIt<char>{_sv.begin(), _sv.end()};
  }

  constexpr auto end() const noexcept {
    return Sentinel{};
  }
  StringView _sv;
};

std::ostream& operator<<(std::ostream& out, FmtRn const& rn) noexcept {
  for (auto it = rn.begin(); it != rn.end(); ++it) {
    using cds::meta::visitors;
    it->visit(visitors(
        [&out](StringView token) {
          out << "'tok': " << token << '\n';
        },
        [&out](FmtStr const& tok) {
          out << "'fmt idx=" << tok.argIdx << "': " << tok.val << '\n';
        }
    ));
  }
  return out;
}

template <typename F, typename Ctx, typename = void> struct FormatterParseFormatString {
  static constexpr auto parse(F& formatter, Ctx& ctx) -> typename Ctx::Iterator {
    ignore = formatter;
    auto it = ctx.begin();
    if (it == ctx.end()) {
      return it;
    }

    assert(false && "Unexpected");
  }
};

template <typename F, typename Ctx> struct FormatterParseFormatString<F, Ctx, Void<decltype(&F::template parse<Ctx>)>> {
  static constexpr auto parse(F& formatter, Ctx& ctx) -> typename Ctx::Iterator {
    return formatter.parse(ctx);
  }
};

template <Size idx> struct FormatterContainer {
  template <typename C, typename F, typename... Args> static auto doFmt(
      BaseString<C>& out, BaseStringView<C> const& in, Tuple<Args&&...> const& args, F& fmt) -> void {
    using T = RemoveCVRef<decltype(get<idx>(args))>;
    auto& formatter = get<idx>(fmt._formatters);
    // Formatter<T> formatter;
    FormatParseContext<C> fmtParCtx {in};
    if (!fmt._preValidated) {
      auto todo1 = FormatterParseFormatString<Formatter<T, C>, FormatParseContext<C>>::parse(formatter, fmtParCtx);
      if (todo1 != in.end()) {
        throw FormatException(String{"Incomplete parsing of format string '"} + in + "'");
      }
    }

    FormatContext<C> fmtCtx {&out};
    auto todo2 = formatter.format(get<idx>(args), fmtCtx);
  }

  template <typename C, typename F, typename... Args>
  static constexpr auto doValidate(BaseStringView<C> const& in, F& fmt) -> void {
    using T = RemoveCVRef<decltype(get<idx>(value<Tuple<Args&&...>>()))>;
    // Formatter<T> formatter;
    auto& formatter = get<idx>(fmt._formatters);
    FormatParseContext<C> fmtParCtx {in};
    auto todo1 = FormatterParseFormatString<Formatter<T>, FormatParseContext<C>>::parse(formatter, fmtParCtx);
    if (todo1 != in.end()) {
        throw FormatException("Incomplete parsing of format string");
    }
  }
};

// template <typename, typename...> struct FormattersImpl {};
//
// template <typename C, typename... Args, Size... is> struct FormattersImpl<unionImpl::IndexSequence<is...>, C, Args...> {
//   static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doFmt<C, Args&&...>)>...>
//       table[sizeof...(is)] = {FormatterContainer<is>::template doFmt<C, Args&&...>...};
// };
//
// template <typename, typename> struct Formatters{};
//
// template <typename C, typename... A> struct Formatters<C, Tuple<A...>> :
//     FormattersImpl<unionImpl::MakeIndexSequence<sizeof...(A)>, C, A...> {};
//
// template <typename, typename...> struct ValidationFormattersImpl {};
//
// template <typename C, typename... Args, Size... is>
// struct ValidationFormattersImpl<unionImpl::IndexSequence<is...>, C, Args...> {
//   static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doValidate<C, Args&&...>)>...>
//       table[sizeof...(is)] = {FormatterContainer<is>::template doValidate<C, Args&&...>...};
//   static constexpr auto size = sizeof...(is);
// };
//
// template <typename, typename> struct ValidationFormatters{};
//
// template <typename C, typename... A> struct ValidationFormatters<C, Tuple<A...>> :
//     ValidationFormattersImpl<unionImpl::MakeIndexSequence<sizeof...(A)>, C, A...> {};

template <typename, typename, typename...> struct MergedValidationFormattersImpl {};

template <typename C, typename F, typename... Args, Size... is>
struct MergedValidationFormattersImpl<unionImpl::IndexSequence<is...>, C, F, Args...> {
  static constexpr auto size = sizeof...(is);
  static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doValidate<C, F, Args&&...>)>...>
      parsers[size] = {FormatterContainer<is>::template doValidate<C, F, Args&&...>...};
  static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doFmt<C, F, Args&&...>)>...>
      formatters[size] = {FormatterContainer<is>::template doFmt<C, F, Args&&...>...};
};

template <typename, typename, typename> struct MergedValidationFormatters {};
template <typename C, typename F, typename... A> struct MergedValidationFormatters<C, F, Tuple<A...>> :
    MergedValidationFormattersImpl<unionImpl::MakeIndexSequence<sizeof...(A)>, C, F, A...> {};

template <typename A, typename C, typename F> constexpr auto formatValidate(
    BaseStringView<C> const& fmt, F& fmtObj) -> void {
  for (auto const& e : FmtRn{fmt}) {
    e.visit(meta::visitors(
      [](StringView const& text) {
        ignore = text;
      },
      [&fmtObj](FmtStr const& fmt) {
        using VF = MergedValidationFormatters<C, F, A>;
        if (VF::size <= fmt.argIdx) {
          if (inConstexpr()) {
            throw FormatException("Format index specification is out of range for given arguments");
          }
          throw FormatException(
              String{"Out of range format index. Requested: "} + fmt.argIdx + ", available: " + VF::size);
        }
        VF::parsers[fmt.argIdx](fmt.val, fmtObj);
      }
    ));
  }
}

template <typename C, typename F, typename A> auto formatTo(
    BaseString<C>& out, F& fmt, A&& args) -> void {
  for (auto const& e : FmtRn{fmt.get()}) {
    e.visit(meta::visitors(
      [&out](StringView const& text) {
        out += text;
      },
      [&out, &args, &fmt](FmtStr const& fmtStr) {
        MergedValidationFormatters<C, F, A>
            ::formatters[fmtStr.argIdx](out, fmtStr.val, fwd<A>(args), fmt);
      }
    ));
  }
}

template <typename C, typename... Args> struct FmtS {
  using Char = C;
  template <typename S> CDS_ATTR(2(consteval(20, constexpr(14)), implicit)) FmtS(S const& s) : _str{s} {
    if (inConstexpr()) {
      formatValidate<Tuple<Args&&...>>(_str, *this);
      _preValidated = true;
    }
  }
  // template <typename S> FmtS(S const& s) : _str{s} {}

  [[nodiscard]] auto get() const noexcept -> BaseStringView<C> {
    return _str;
  }

  BaseStringView<C> _str;
  Tuple<Formatter<RemoveCVRef<Args>>...> _formatters;
  // MergedValidationFormatters<C, Tuple<Args&&...>> _formatters;
  bool _preValidated {false};
};

template <typename... Args> auto format(FmtS<char, TypeIdT<Args>...> fmt, Args&&... args) -> String {
  String out;
  formatTo(out, fmt, impl::forwardAsTuple(fwd<Args>(args)...));
  return out;
}

enum class FmtAlignType {Leading, Centre, Trailing};
enum class FmtNumSignType : U8 {PosNeg, Neg, SpaceNeg};
enum class FmtTypeFlag : U16 {
  Binary = 0x0001u,
  Character = 0x0002u,
  Decimal = 0x0004u,
  Octal = 0x0008u,
  Hex = 0x0010u,
  Uppercase = 0x0020u,
  Escaped = 0x0040u,
  Floating = 0x0080u,
  Scientific = 0x0100u,
  Fixed = 0x0200u,
  General = 0x0400u,
  Pointer = 0x0800u,
  String = 0x1000u,
};

using FmtTypeFlags = U16;

template <typename C> struct FmtFillAlignSpec {
  constexpr FmtFillAlignSpec(FmtAlignType a, C fc) noexcept : align{a}, fillChar{fc} {}
  FmtAlignType align;
  C fillChar;
};

struct FmtNumSpec {
  FmtNumSignType sign {FmtNumSignType::Neg};
  bool alternate {false};
  bool leadingZeroes {false};
};

struct FmtSizeSpec {
  Optional<Size> size{nullopt};
  Optional<Size> explicitIdx{nullopt};
};

struct FmtWidthSpec {
  Optional<FmtSizeSpec> width{nullopt};
  Optional<FmtSizeSpec> precision{nullopt};
};

template <typename C> constexpr auto operator==(FmtFillAlignSpec<C> const& lhs, FmtFillAlignSpec<C> const& rhs)
    noexcept -> bool {
  return lhs.align == rhs.align
      && lhs.fillChar == rhs.fillChar;
}

constexpr auto operator==(FmtNumSpec const& lhs, FmtNumSpec const& rhs)
    noexcept -> bool {
  return lhs.sign == rhs.sign
      && lhs.alternate == rhs.alternate
      && lhs.leadingZeroes == rhs.leadingZeroes;
}

constexpr auto operator==(FmtSizeSpec const& lhs, FmtSizeSpec const& rhs)
    noexcept -> bool {
  return lhs.size == rhs.size
      && lhs.explicitIdx == rhs.explicitIdx;
}

constexpr auto operator==(FmtWidthSpec const& lhs, FmtWidthSpec const& rhs)
    noexcept -> bool {
  return lhs.width == rhs.width
      && lhs.precision == rhs.precision;
}

template <typename C, typename T,
          typename = typename And<Not<IsSame<C, T>>, Not<IsSame<T, bool>>,
                                  Or<IsSigned<T>, IsUnsigned<T>, IsFloating<T>>>::Type>
struct FmtAlignDefault;

template <typename C, typename T> struct FmtAlignDefault<C, T, True> {
  static constexpr auto value = FmtAlignType::Trailing;
};

template <typename C, typename T> struct FmtAlignDefault<C, T, False> {
  static constexpr auto value = FmtAlignType::Leading;
};

template <typename C> auto fillAlignSpec(C aligner) noexcept -> Optional<FmtAlignType> {
  switch (aligner) {
    case static_cast<C>('<'): return FmtAlignType::Leading;
    case static_cast<C>('>'): return FmtAlignType::Trailing;
    case static_cast<C>('^'): return FmtAlignType::Centre;
    default:                  return nullopt;
  }
}

template <typename C, typename T, typename I, typename S> constexpr auto fmtParseFillAlign(I it, S end) noexcept
    -> Tuple<I, FmtFillAlignSpec<C>> {
  // auto sizeIt = it;
  auto fillChar = static_cast<C>(' ');
  auto align = FmtAlignDefault<C, T>::value;
  if (it == end) {
    return {it, FmtFillAlignSpec<C>{align, fillChar}};
  }

  auto maybeExplicitAlign = it + 1;
  if (maybeExplicitAlign != end) {
    auto maybeAlign = fillAlignSpec(*maybeExplicitAlign);
    if (maybeAlign) {
      align = *maybeAlign;
      fillChar = /* *sizeIt; */ *it;
      /* sizeIt */ it = maybeExplicitAlign + 1;

      /*
      if (it == end) {
        return {it, nullopt};
      }
      */
    }
  }

  // Size size = 0u;
  // C const* afterRead = nullptr;
  // if (!StringUtils<C, StringTraits<C>>::readInt(&*sizeIt, end - sizeIt, &afterRead, &size, 10)) {
  //   return {it, nullopt};
  // }
  // sizeIt = sizeIt + (afterRead - &*sizeIt);
  return {/* sizeIt */ it, FmtFillAlignSpec<C>{align, /* size, */ fillChar}};
}

template <typename C, typename I, typename S> constexpr auto fmtParseNum(I it, S end) noexcept
    -> Tuple<I, FmtNumSpec> {
  if (it == end) {
    return {it, FmtNumSpec{}};
  }

  auto sign = [](C signChar) {
    switch (signChar) {
      case static_cast<C>('+'): return FmtNumSignType::PosNeg;
      case static_cast<C>(' '): return FmtNumSignType::SpaceNeg;
      default:                  return FmtNumSignType::Neg;
    }
  }(*it);

  if ((sign != FmtNumSignType::Neg || *it == static_cast<C>('-')) && ++it == end) {
    return {it, FmtNumSpec{sign}};
  }

  bool alternate = *it == static_cast<C>('#');
  if (alternate && ++it == end) {
    return {it, FmtNumSpec{sign, alternate}};
  }

  bool leadingZeroes = *it == static_cast<C>('0');
  return {leadingZeroes ? it + 1 : it, FmtNumSpec{sign, alternate, leadingZeroes}};
}

template <typename C, typename I, typename S> constexpr auto fmtParseWidthOrPrec(I it, S end)
    -> Tuple<I, Optional<FmtSizeSpec>> {
  using U = StringUtils<C, StringTraits<C>>;
  Optional<Size> size = nullopt;
  if (StringTraits<C>::isDigit(*it)) {
    size.emplace(0);
    C const* pEnd = nullptr;
    auto res = U::readInt(&*it, end - it, &pEnd, &*size, 10);
    assert(res && "Unexpected failure in width int parse");
    it = it + (pEnd - &*it);
    if (it == end) {
      return {it, makeOptional<FmtSizeSpec>(mv(size), nullopt)};
    }
  }

  if (!size && *it != static_cast<C>('{')) {
    return {it, nullopt};
  }

  Optional<Size> sizeExplicitArgIdx = nullopt;
  if (!size) {
    ++it;
    if (it != end && *it != static_cast<C>('}')) {
      sizeExplicitArgIdx.emplace(0);
      C const* pEnd = nullptr;
      auto res = U::readInt(&*it, end - it, &pEnd, &*sizeExplicitArgIdx, 10);
      if (!res) {
        throw FormatException("Nested replacement field with invalid explicit argument index");
      }
      it = it + (pEnd - &*it);
    }

    if (it == end || *it++ != static_cast<C>('}')) {
      throw FormatException("Nested replacement field in width specifier not terminated");
    }
  }

  return {it, makeOptional<FmtSizeSpec>(mv(size), mv(sizeExplicitArgIdx))};
}

template <typename C, typename I, typename S> constexpr auto fmtParseWidth(I it, S end)
    -> Tuple<I, FmtWidthSpec> {
  if (it == end) {
    return {it, FmtWidthSpec{}};
  }

  Optional<FmtSizeSpec> width{};
  cds::tie(it, width) = fmtParseWidthOrPrec<C>(it, end);
  if (it == end || *it != static_cast<C>('.')) {
    return {it, FmtWidthSpec{mv(width)}};
  }

  if (++it == end) {
    throw FormatException("Precision specification not followed by precision");
  }

  Optional<FmtSizeSpec> precision{};
  cds::tie(it, precision) = fmtParseWidthOrPrec<C>(it, end);
  return {it, FmtWidthSpec{mv(width), mv(precision)}};
}

template <typename C, typename T, typename I, typename S> constexpr auto fmtParseType(I it, S end)
    -> Tuple<I, FmtTypeFlags> {

}

template <typename T, typename C> struct FmtFillAlignComponent {
  template <typename I, typename S> constexpr auto parseFillAlign(I begin, S end) noexcept -> I {
    cds::tie(begin, _fillAlignSpec) = fmtParseFillAlign<C, T>(begin, end);
    return begin;
  }

  template <typename T0, typename I, typename F> constexpr auto formatFillAlign(
      Optional<Size> maybeMinWidth, I out, T0&& obj, Optional<Size> estWidth, F&& fmt) const noexcept -> I {
    if (!maybeMinWidth) {
      return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
    }

    auto minWidth = *maybeMinWidth;
    if (estWidth) {
      if (*estWidth >= minWidth) {
        return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
      }
      auto remaining = minWidth - *estWidth;
      if (_fillAlignSpec.align == FmtAlignType::Leading) {
        return fillN(functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out), remaining, _fillAlignSpec.fillChar);
      }

      if (_fillAlignSpec.align == FmtAlignType::Trailing) {
        return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, remaining, _fillAlignSpec.fillChar));
      }

      auto firstHalf = remaining / 2;
      auto secondHalf = remaining - firstHalf;
      return fillN(functional::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, firstHalf, _fillAlignSpec.fillChar)), secondHalf, _fillAlignSpec.fillChar);
    }

    BaseString<C> asStr;
    functional::invoke(fwd<F>(fmt), fwd<T0>(obj), BackInserterIterator<BaseString<C>>{asStr});
    return formatFillAlign(maybeMinWidth, out, asStr, asStr.size(), *this);
  }

  template <typename I> constexpr auto operator()(BaseString<C> const& obj, I out) const noexcept -> I {
    return impl::copy(obj.begin(), obj.end(), out);
  }

  FmtFillAlignSpec<C> _fillAlignSpec {FmtAlignDefault<C, T>::value, static_cast<C>(' ')};
};

template <typename T, typename C> struct FmtNumComponent {
  template <typename I, typename S> constexpr auto parseNum(I begin, S end) noexcept -> I {
    cds::tie(begin, _numSpec) = fmtParseNum<C, T>(begin, end);
    return begin;
  }

  template <typename T0, typename I, typename F>
  constexpr auto formatNum(I out, T0&& obj, Optional<Size> estWidth, F&& fmt) const noexcept -> I {
    // if (!_fillAlignSpec) {
    //   return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
    // }
    //
    // if (estWidth) {
    //   if (*estWidth >= _fillAlignSpec->size) {
    //     return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
    //   }
    //   auto remaining = _fillAlignSpec->size - *estWidth;
    //   if (_fillAlignSpec->align == FmtAlignType::Leading) {
    //     return fillN(functional::invoke(fwd<F>(fmt), fwd<T0>(obj), out), remaining, _fillAlignSpec->fillChar);
    //   }
    //
    //   if (_fillAlignSpec->align == FmtAlignType::Trailing) {
    //     return functional::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, remaining, _fillAlignSpec->fillChar));
    //   }
    //
    //   auto firstHalf = remaining / 2;
    //   auto secondHalf = remaining - firstHalf;
    //   return fillN(functional::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, firstHalf, _fillAlignSpec->fillChar)), secondHalf, _fillAlignSpec->fillChar);
    // }
    //
    // BaseString<C> asStr;
    // functional::invoke(fwd<F>(fmt), fwd<T0>(obj), BackInserterIterator<BaseString<C>>{asStr});
    // return formatFillAlign(out, asStr, asStr.size(), *this);
    return out;
  }

  template <typename I> constexpr auto operator()(BaseString<C> const& obj, I out) const noexcept -> I {
    return impl::copy(obj.begin(), obj.end(), out);
  }

  Optional<FmtNumSpec> _numSpec;
};

template <typename C, typename I> struct IntegralFormatter : FmtFillAlignComponent<I, C> {
  using FmtFillAlignComponent<I, C>::parseFillAlign;
  using FmtFillAlignComponent<I, C>::formatFillAlign;
  using U = StringUtils<C, StringTraits<C>>;

  template <typename Ctx> constexpr auto parse(Ctx& ctx) -> typename Ctx::Iterator {
    auto it = parseFillAlign(ctx.begin(), ctx.end());
    if (it == ctx.end()) {
      return it;
    }

    if (inConstexpr()) {
      throw FormatException("Extraneous characters in format string");
    }
    throw FormatException(String{"Extraneous characters in format string: '"} + StringView{&*it, ctx.end() - it} + "'");
  }

  template <typename Ctx> auto format(I value, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto len = U::intLength(value, 10);
    return formatFillAlign(/* TODO */ nullopt, ctx.out(), value, len, [len](I lValue, BackInserterIterator<BaseString<C>> out) {
      BaseString<C> asStr;
      asStr.resize(len);
      ignore = U::writeInt(lValue, len, asStr.data());
      return impl::copy(asStr.begin(), asStr.end(), out);
    });
  }
};

template <typename C> struct CharFormatter : FmtFillAlignComponent<C, C> {
  using FmtFillAlignComponent<C, C>::parseFillAlign;
  using FmtFillAlignComponent<C, C>::formatFillAlign;
  using U = StringUtils<C, StringTraits<C>>;

  template <typename Ctx> constexpr auto parse(Ctx& ctx) -> typename Ctx::Iterator {
    auto it = parseFillAlign(ctx.begin(), ctx.end());
    if (it == ctx.end()) {
      return it;
    }

    if (inConstexpr()) {
      throw FormatException("Extraneous characters in format string");
    }
    throw FormatException(String{"Extraneous characters in format string: '"} + StringView{&*it, ctx.end() - it} + "'");
  }

  template <typename Ctx> auto format(C value, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    return formatFillAlign(ctx.out(), value, 1, [](C lValue, BackInserterIterator<BaseString<C>> out) {
      return impl::copy(&lValue, &lValue + 1, out);
    });
  }
};

template <typename C> struct Formatter<C, C> : CharFormatter<C> {};

template <typename C> struct Formatter<U16, C> : IntegralFormatter<C, U16> {};
template <typename C> struct Formatter<U32, C> : IntegralFormatter<C, U32> {};
template <typename C> struct Formatter<U64, C> : IntegralFormatter<C, U64> {};
template <typename C> struct Formatter<S16, C> : IntegralFormatter<C, S16> {};
template <typename C> struct Formatter<S32, C> : IntegralFormatter<C, S32> {};
template <typename C> struct Formatter<S64, C> : IntegralFormatter<C, S64> {};

template <typename C> struct Formatter<bool, C> : FmtFillAlignComponent<bool, C> {
  using FmtFillAlignComponent<bool, C>::parseFillAlign;
  using FmtFillAlignComponent<bool, C>::formatFillAlign;
  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept -> typename Ctx::Iterator {
    auto it = parseFillAlign(ctx.begin(), ctx.end());
    if (it == ctx.end()) {
      return it;
    }

    assert(false && "unimplemented");
  }

  template <typename Ctx> auto format(bool value, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    auto asStr = value
        ? BaseStringView<C>{StringTraits<C>::Constants::_true}
        : BaseStringView<C>{StringTraits<C>::Constants::_false};
    return formatFillAlign(/* TODO */nullopt, ctx.out(), asStr, asStr.length(),
      [](BaseStringView<C> const& lValue, BackInserterIterator<BaseString<C>> out) {
          return impl::copy(lValue.begin(), lValue.end(), out);
    });
  }
};
} // namespace

TEST(FormatTest, init) {
  using V = Union<StringView, FmtStr>;
  ASSERT_TRUE(citeq(FmtRn("{}"), Vector<V>{"", FmtStr{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn(" {}"), Vector<V>{" ", FmtStr{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{} "), Vector<V>{"", FmtStr{"", 0}, " "}));
  ASSERT_TRUE(citeq(FmtRn(" { } "), Vector<V>{" ", FmtStr{" ", 0}, " "}));
  ASSERT_TRUE(citeq(FmtRn("{ }"), Vector<V>{"", FmtStr{" ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{}{}"), Vector<V>{"", FmtStr{"", 0}, "", FmtStr{"", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{{}}"), Vector<V>{"{{}}"}));
  ASSERT_TRUE(citeq(FmtRn("{ {}}"), Vector<V>{"", FmtStr{" {}", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ {} }"), Vector<V>{"", FmtStr{" {} ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{:}"), Vector<V>{"", FmtStr{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ :}"), Vector<V>{"", FmtStr{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{ : }"), Vector<V>{"", FmtStr{" ", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{1: }"), Vector<V>{"", FmtStr{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{ 1: }"), Vector<V>{"", FmtStr{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{ 1 : }"), Vector<V>{"", FmtStr{" ", 1}}));
  ASSERT_TRUE(citeq(FmtRn("{2:}{0:}"), Vector<V>{"", FmtStr{"", 2}, "", FmtStr{"", 0}}));
  ASSERT_TRUE(citeq(FmtRn("{2}{0}"), Vector<V>{"", FmtStr{"", 2}, "", FmtStr{"", 0}}));
  // ASSERT_TRUE(citeq(FmtRn("{2}{x}"), Vector<V>{"", FmtStr{"", 2}, "", FmtStr{"", 0}}));
  // std::cout << FmtRn("{ 1 : }{}") << '\n';
  // ASSERT_TRUE(citeq(FmtRn("{ 1 : }{}"), Vector<V>{"", FmtStr{" ", 1}}));
  // ASSERT_EQ(0, format("abc", 1, true));
  // format("abc"_f, 1, true);
  // std::format("abc");

  ASSERT_EQ("5true", format("{0}{1}", 5, true));
  ASSERT_EQ("true5", format("{1}{0}", 5, true));
  ASSERT_EQ("55", format("{0}{0}", 5, true));
  ASSERT_EQ("truetrue", format("truetrue", 5, true));
}

TEST(FormatTest, fmtParseFillAlign) {
  char const str0[] = "6";
  ASSERT_EQ(
      Tuple(cds::begin(str0), FmtFillAlignSpec<char>(FmtAlignType::Trailing, ' ')),
      (fmtParseFillAlign<char, int>(cds::begin(str0), cds::end(str0)))
  );
  ASSERT_EQ(
      Tuple(cds::begin(str0), FmtFillAlignSpec<char>(FmtAlignType::Leading, ' ')),
      (fmtParseFillAlign<char, char>(cds::begin(str0), cds::end(str0)))
  );
  ASSERT_EQ(
      Tuple(cds::begin(str0), FmtFillAlignSpec<char>(FmtAlignType::Leading, ' ')),
      (fmtParseFillAlign<char, bool>(cds::begin(str0), cds::end(str0)))
  );

  char const str1[] = "6d";
  ASSERT_EQ(
      Tuple(cds::begin(str1), FmtFillAlignSpec<char>(FmtAlignType::Trailing, ' ')),
      (fmtParseFillAlign<char, int>(cds::begin(str1), cds::end(str1)))
  );

  char const str2[] = "*<6";
  ASSERT_EQ(
      Tuple(cds::begin(str2) + 2, FmtFillAlignSpec<char>(FmtAlignType::Leading, '*')),
      (fmtParseFillAlign<char, int>(cds::begin(str2), cds::end(str2)))
  );

  char const str3[] = "*>6";
  ASSERT_EQ(
      Tuple(cds::begin(str3) + 2, FmtFillAlignSpec<char>(FmtAlignType::Trailing, '*')),
      (fmtParseFillAlign<char, int>(cds::begin(str3), cds::end(str3)))
  );

  char const str4[] = "*^6";
  ASSERT_EQ(
      Tuple(cds::begin(str4) + 2, FmtFillAlignSpec<char>(FmtAlignType::Centre, '*')),
      (fmtParseFillAlign<char, int>(cds::begin(str4), cds::end(str4)))
  );

  char const str5[] = "*^";
  ASSERT_EQ(
      Tuple(cds::begin(str5) + 2, FmtFillAlignSpec<char>(FmtAlignType::Centre, '*')),
      (fmtParseFillAlign<char, int>(cds::begin(str5), cds::end(str5)))
  );

  char const str6[] = "";
  ASSERT_EQ(
      Tuple(cds::begin(str6), FmtFillAlignSpec<char>(FmtAlignType::Trailing, ' ')),
      (fmtParseFillAlign<char, int>(cds::begin(str6), cds::end(str6)))
  );

  char const str7[] = "d";
  ASSERT_EQ(
      Tuple(cds::begin(str7), FmtFillAlignSpec<char>(FmtAlignType::Trailing, ' ')),
      (fmtParseFillAlign<char, int>(cds::begin(str7), cds::end(str7)))
  );
}

TEST(FormatTest, fmtParseNum) {
  char const str0[] = "";
  ASSERT_EQ(Tuple(cds::begin(str0), FmtNumSpec{FmtNumSignType::Neg, false, false}),
            (fmtParseNum<char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "+";
  ASSERT_EQ(Tuple(cds::begin(str1) + 1, FmtNumSpec{FmtNumSignType::PosNeg, false, false}),
            (fmtParseNum<char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "-";
  ASSERT_EQ(Tuple(cds::begin(str2) + 1, FmtNumSpec{FmtNumSignType::Neg, false, false}),
            (fmtParseNum<char>(cds::begin(str2), cds::end(str2))));

  char const str3[] = " ";
  ASSERT_EQ(Tuple(cds::begin(str3) + 1, FmtNumSpec{FmtNumSignType::SpaceNeg, false, false}),
            (fmtParseNum<char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "#";
  ASSERT_EQ(Tuple(cds::begin(str4) + 1, FmtNumSpec{FmtNumSignType::Neg, true, false}),
            (fmtParseNum<char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = " #";
  ASSERT_EQ(Tuple(cds::begin(str5) + 2, FmtNumSpec{FmtNumSignType::SpaceNeg, true, false}),
            (fmtParseNum<char>(cds::begin(str5), cds::end(str5))));

  char const str6[] = "0";
  ASSERT_EQ(Tuple(cds::begin(str6) + 1, FmtNumSpec{FmtNumSignType::Neg, false, true}),
            (fmtParseNum<char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = " 0";
  ASSERT_EQ(Tuple(cds::begin(str7) + 2, FmtNumSpec{FmtNumSignType::SpaceNeg, false, true}),
            (fmtParseNum<char>(cds::begin(str7), cds::end(str7))));

  char const str8[] = "#0";
  ASSERT_EQ(Tuple(cds::begin(str8) + 2, FmtNumSpec{FmtNumSignType::Neg, true, true}),
            (fmtParseNum<char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "+#0";
  ASSERT_EQ(Tuple(cds::begin(str9) + 3, FmtNumSpec{FmtNumSignType::PosNeg, true, true}),
            (fmtParseNum<char>(cds::begin(str9), cds::end(str9))));

  char const str10[] = "+#1";
  ASSERT_EQ(Tuple(cds::begin(str10) + 2, FmtNumSpec{FmtNumSignType::PosNeg, true, false}),
            (fmtParseNum<char>(cds::begin(str10), cds::end(str10))));
}

TEST(FormatTest, fmtParseWidth) {
  char const str0[] = "";
  ASSERT_EQ(Tuple(cds::begin(str0), FmtWidthSpec{}),
            (fmtParseWidth<char>(cds::begin(str0), cds::end(str0))));

  char const str1[] = "5";
  ASSERT_EQ(Tuple(cds::begin(str1) + 1, FmtWidthSpec{5}),
            (fmtParseWidth<char>(cds::begin(str1), cds::end(str1))));

  char const str2[] = "{}";
  ASSERT_EQ(Tuple(cds::begin(str2) + 2, FmtWidthSpec{FmtSizeSpec{}}),
            (fmtParseWidth<char>(cds::begin(str2), cds::end(str2))));

  char const str3[] = "d";
  ASSERT_EQ(Tuple(cds::begin(str3), FmtWidthSpec{}),
            (fmtParseWidth<char>(cds::begin(str3), cds::end(str3))));

  char const str4[] = "5d";
  ASSERT_EQ(Tuple(cds::begin(str4) + 1, FmtWidthSpec{FmtSizeSpec{5}}),
            (fmtParseWidth<char>(cds::begin(str4), cds::end(str4))));

  char const str5[] = "{1}";
  ASSERT_EQ(Tuple(cds::begin(str5) + 3, FmtWidthSpec{FmtSizeSpec{nullopt, 1}}),
            (fmtParseWidth<char>(cds::begin(str5), cds::end(str5))));

  try {
    char const stre0[] = "{";
    ignore = fmtParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{10";
    ignore = fmtParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{10d";
    ignore = fmtParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field in width specifier not terminated",
        e.message()
    );
  }

  try {
    char const stre0[] = "{n}";
    ignore = fmtParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Nested replacement field with invalid explicit argument index",
        e.message()
    );
  }

  char const str6[] = ".5";
  ASSERT_EQ(Tuple(cds::begin(str6) + 2, FmtWidthSpec{nullopt, FmtSizeSpec{5}}),
            (fmtParseWidth<char>(cds::begin(str6), cds::end(str6))));

  char const str7[] = "10.5";
  ASSERT_EQ(Tuple(cds::begin(str7) + 4, FmtWidthSpec{FmtSizeSpec{10}, FmtSizeSpec{5}}),
            (fmtParseWidth<char>(cds::begin(str7), cds::end(str7))));

  try {
    char const stre0[] = ".";
    ignore = fmtParseWidth<char>(cds::begin(stre0), cds::end(stre0));
    ASSERT_FALSE(true);
  } catch(FormatException const& e) {
    ASSERT_EQ(
        "Precision specification not followed by precision",
        e.message()
    );
  }

  char const str8[] = "10.{}";
  ASSERT_EQ(Tuple(cds::begin(str8) + 5, FmtWidthSpec{FmtSizeSpec{10}, FmtSizeSpec{}}),
            (fmtParseWidth<char>(cds::begin(str8), cds::end(str8))));

  char const str9[] = "{}.{}";
  ASSERT_EQ(Tuple(cds::begin(str9) + 5, FmtWidthSpec{FmtSizeSpec{}, FmtSizeSpec{}}),
            (fmtParseWidth<char>(cds::begin(str9), cds::end(str9))));
}

TEST(FormatTest, fmtParseWidthInFormat) {
  // ASSERT_EQ(format("{:6}", 42),    "    42");
  // ASSERT_EQ(format("{:6}", 'x'),   "x     ");
  // ASSERT_EQ(format("{:*<6}", 'x'), "x*****");
  // ASSERT_EQ(format("{:*>6}", 'x'), "*****x");
  // ASSERT_EQ(format("{:*^6}", 'x'), "**x***");
  // ASSERT_EQ(format("{:6}", true),  "true  ");
}
