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

struct FmtStr {
  StringView val;
  Size argIdx;

  auto operator==(FmtStr const& o) const noexcept -> bool {
    return argIdx == o.argIdx && val == o.val;
  }

  auto operator!=(FmtStr const& o) const noexcept -> bool {
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
            char* end;
            auto argIdx = std::strtoull(&*_b, &end, 10);
            if (&*_b != end) {
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
              Size idx;

              if (explicitArgIdx) {
                idx = *explicitArgIdx;
                _explUsed = true;
              } else {
                idx = _implicitArgIdx++;
                _implUsed = true;
              }

              assert(!_explUsed || !_implUsed);
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
  explicit FormatParseContext(BaseStringView<C> const& in) : _fmtStr{in} {}

  using Iterator = typename BaseStringView<C>::Iterator;

  auto begin() const noexcept -> Iterator {
    return _fmtStr.begin();
  }

  auto end() const noexcept -> Iterator {
    return _fmtStr.end();
  }

private:
  BaseStringView<C> const& _fmtStr;
};

template <typename C> class FormatContext {
  class FormatIterator {
  public:
    explicit FormatIterator(FormatContext* ctx) : _ctx{ctx} {}

    auto operator=(C value) noexcept -> FormatIterator& {
      *_ctx->_result += value;
      return *this;
    }

    auto operator*() noexcept -> FormatIterator& {
      return *this;
    }

    auto operator++() -> FormatIterator& {
      return *this;
    }

  private:
    FormatContext* _ctx;
  };

public:
  using Iterator = FormatIterator;

  explicit FormatContext(BaseString<C>* result) : _result{result} {}

  auto out() noexcept -> FormatIterator {
    return FormatIterator{this};
  }

private:
  BaseString<C>* _result;
};

template <typename T, typename C = char> struct Formatter {};

template <typename C, typename I> struct IntegralFormatter {
  using U = StringUtils<C, StringTraits<C>>;

  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept -> typename Ctx::Iterator {
    auto it = ctx.begin();
    if (it == ctx.end()) {
      return it;
    }

    assert(false && "unimplemented");
  }

  template <typename Ctx> auto format(I value, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    BaseString<C> asStr;
    auto len = U::intLength(value, 10);
    asStr.resize(len);
    ignore = U::writeInt(value, len, asStr.data());
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

template <typename C> struct Formatter<U16, C> : IntegralFormatter<C, U16> {};
template <typename C> struct Formatter<U32, C> : IntegralFormatter<C, U32> {};
template <typename C> struct Formatter<U64, C> : IntegralFormatter<C, U64> {};
template <typename C> struct Formatter<S16, C> : IntegralFormatter<C, S16> {};
template <typename C> struct Formatter<S32, C> : IntegralFormatter<C, S32> {};
template <typename C> struct Formatter<S64, C> : IntegralFormatter<C, S64> {};

template <typename C> struct Formatter<bool, C> {
  template <typename Ctx> constexpr auto parse(Ctx& ctx) noexcept -> typename Ctx::Iterator {
    auto it = ctx.begin();
    if (it == ctx.end()) {
      return it;
    }

    assert(false && "unimplemented");
  }

  template <typename Ctx> auto format(bool value, Ctx& ctx) const noexcept -> typename Ctx::Iterator {
    BaseString<C> asStr;
    asStr += value;
    return impl::copy(asStr.begin(), asStr.end(), ctx.out());
  }
};

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

template <typename F, typename = void> struct FormatterParseFormatString {
  template <typename C> static auto parse(F& formatter, C& ctx) -> typename C::Iterator {
    ignore = formatter;
    auto it = ctx.begin();
    if (it == ctx.end()) {
      return it;
    }

    assert(false && "Unexpected");
  }
};

template <typename F> struct FormatterParseFormatString<F, Void<decltype(&F::parse)>> {
  template <typename C> static auto parse(F& formatter, C& ctx) -> typename C::Iterator {
    return formatter.parse(ctx);
  }
};

template <Size idx> struct FormatterContainer {
  template <typename C, typename... Args>
  static auto doFmt(BaseString<C>& out, BaseStringView<C> const& in, Tuple<Args&&...> const& args) -> void {
    using T = RemoveCVRef<decltype(get<idx>(args))>;
    Formatter<T> formatter;
    FormatParseContext<C> fmtParCtx {in};
    auto todo1 = FormatterParseFormatString<Formatter<T>>::parse(formatter, fmtParCtx);

    FormatContext<C> fmtCtx {&out};
    auto todo2 = formatter.format(get<idx>(args), fmtCtx);
  }

  template <typename C, typename... Args>
  static auto doValidate(BaseStringView<C> const& in) -> void {
    using T = RemoveCVRef<decltype(get<idx>(value<Tuple<Args&&...>>()))>;
    Formatter<T> formatter;
    FormatParseContext<C> fmtParCtx {in};
    auto todo1 = FormatterParseFormatString<Formatter<T>>::parse(formatter, fmtParCtx);
    if (todo1 != in.end()) {
      assert(false);
    }
  }
};

template <typename, typename...> struct FormattersImpl {};

template <typename C, typename... Args, Size... is> struct FormattersImpl<unionImpl::IndexSequence<is...>, C, Args...> {
  static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doFmt<C, Args&&...>)>...>
      table[sizeof...(is)] = {FormatterContainer<is>::template doFmt<C, Args&&...>...};
};

template <typename, typename> struct Formatters{};

template <typename C, typename... A> struct Formatters<C, Tuple<A...>> :
FormattersImpl<unionImpl::MakeIndexSequence<sizeof...(A)>, C, A...> {};

template <typename, typename...> struct ValidationFormattersImpl {};

template <typename C, typename... Args, Size... is>
struct ValidationFormattersImpl<unionImpl::IndexSequence<is...>, C, Args...> {
  static constexpr meta::Common<Decay<decltype(&FormatterContainer<is>::template doValidate<C, Args&&...>)>...>
      table[sizeof...(is)] = {FormatterContainer<is>::template doValidate<C, Args&&...>...};
};

template <typename, typename> struct ValidationFormatters{};

template <typename C, typename... A> struct ValidationFormatters<C, Tuple<A...>> :
    ValidationFormattersImpl<unionImpl::MakeIndexSequence<sizeof...(A)>, C, A...> {};

template <typename A, typename C> constexpr auto formatValidate(BaseStringView<C> const& fmt) -> void {
  for (auto const& e : FmtRn{fmt}) {
    e.visit(meta::visitors(
      [](StringView const& text) {
        ignore = text;
      },
      [](FmtStr const& fmt) {
        ValidationFormatters<C, A>::table[fmt.argIdx](fmt.val);
      }
    ));
  }
}

template <typename C, typename... Args> struct FmtS {
  template <typename S> CDS_ATTR(consteval(20, constexpr(14))) FmtS(S const& s) : _str{s} {
    if (inConstexpr()) {
      formatValidate<Tuple<Args&&...>>(_str);
      // auto it = FmtIt<C>{_str.cbegin(), _str.cend()};
      // _preValidated = true;
    }
  }
  // template <typename S> FmtS(S const& s) : _str{s} {}

  auto get() const noexcept -> BaseStringView<C> {
    return _str;
  }

  BaseStringView<C> _str;
  bool _preValidated {false};
};

template <typename C, typename F, typename A> auto formatTo(BaseString<C>& out, F const& fmt, A&& args) -> void {
  for (auto const& e : FmtRn{fmt}) {
    e.visit(meta::visitors(
      [&out](StringView const& text) {
        out += text;
      },
      [&out, &args](FmtStr const& fmt) {
        Formatters<C, A>::table[fmt.argIdx](out, fmt.val, fwd<A>(args));
      }
    ));
  }
}

template <typename... Args> auto format(FmtS<char, TypeIdT<Args>...> fmt, Args&&... args) -> String {
  String out;
  formatTo(out, fmt.get(), cds::impl::forwardAsTuple(fwd<Args>(args)...));
  return out;
}
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
  // std::cout << FmtRn("{ 1 : }{}") << '\n';
  // ASSERT_TRUE(citeq(FmtRn("{ 1 : }{}"), Vector<V>{"", FmtStr{" ", 1}}));
  // ASSERT_EQ(0, format("abc", 1, true));
  // format("abc"_f, 1, true);
  // std::format("abc");

  int const v = 5;
  std::cout << format("{1}{0}", v, true);
}
