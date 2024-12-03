//
// Created by loghin on 31.03.2024.
//

#ifndef CDS_FORMAT_FORMAT_HPP
#define CDS_FORMAT_FORMAT_HPP
#pragma once

#include <cds/String>
#include <cds/exception/Exception>

namespace cds {
namespace experimental {
namespace impl {
using cds::impl::BaseString;
using cds::impl::BaseStringView;
using cds::impl::StringAbstract;
using cds::impl::StringTraits;
using cds::impl::StringUtils;
using cds::impl::fwd;
using meta::And;
using meta::EnableIf;
using meta::IsIntegral;
using meta::Not;
using meta::RemoveCVRef;

struct FormatStringTraits {
  Size paramCount;
  Size estSize;
};

enum class FormatStringAnalysisState {
  InFormatString,
  InParam,
  InPotentialEnd,
  EndReqEscape,
};

class FormatStringException : public Exception {
  // TODO
  CDS_ATTR(2(nodiscard, constexpr(20))) auto message() const noexcept -> BaseStringView<char> override {
    return "StringFormatException";
  }
};

template<typename C, typename T>
class BaseFormatString {
public:
  template<typename Fmt>
  CDS_ATTR(2(implicit, consteval(20, constexpr(20))))
  BaseFormatString(Fmt &&fmt) : _view{fwd<Fmt>(fmt)} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const noexcept -> BaseStringView<C, T> const & {
    return _view;
  }

protected:
  CDS_ATTR(2(nodiscard, constexpr(14))) auto analyze() const CDS_ATTR(noexcept(false)) -> FormatStringTraits {
    FormatStringTraits traits{0u, 0u};
    using
    enum FormatStringAnalysisState;
    FormatStringAnalysisState state = InFormatString;

    for (auto c: _view) {
      switch (state) {
        case InFormatString:
          if (c == static_cast<C>('{')) {
            state = InParam;
          } else if (c == static_cast<C>('}')) {
            state = EndReqEscape;
          } else {
            ++traits.estSize;
          }
          break;
        case InParam:
          if (c == static_cast<C>('{')) {
            ++traits.estSize;
            state = InFormatString;
            break;
          }
          if (c == static_cast<C>('}')) {
            state = InPotentialEnd;
          }
          break;
        case InPotentialEnd: {
          if (c == static_cast<C>('}')) {
            state = InParam;
          } else {
            ++traits.paramCount;
            state = c == '{' ? InParam : InFormatString;
          }
          break;
        }
        case EndReqEscape: {
          if (c != static_cast<C>('}')) {
            throw FormatStringException();
          }
          ++traits.estSize;
          state = InFormatString;
          break;
        }
      }
    }

    if (state == InPotentialEnd) {
      ++traits.paramCount;
    }

    return traits;
  }

private:
  BaseStringView<C, T> _view;
};

template<typename A, EnableIf<StringAbstract<A>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11)))
auto fmtEstSizeOf(A &&arg) noexcept -> Size {
  return StringAbstract<A>::length(fwd<A>(arg));
}

template<typename A, EnableIf<IsIntegral<RemoveCVRef<A>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11)))
auto fmtEstSizeOf(A &&arg) noexcept -> Size {
  // TODO: other bases, requires looking into fmt string
  return StringUtils<char, StringTraits <char>>::intLength(fwd<A>(arg), 10);
}

template<typename A, EnableIf<And<Not<StringAbstract<A>>, Not<IsIntegral<RemoveCVRef<A>>>>> = 0>
CDS_ATTR(2(nodiscard, constexpr(11))) auto fmtEstSizeOf(A &&arg) noexcept -> Size {
  // TODO
  return 0;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto fmtEstSizeOfN() noexcept -> Size {
  return 0u;
}

template <typename F, typename... R> CDS_ATTR(2(nodiscard, constexpr(11))) auto fmtEstSizeOfN(F&& f, R&&... r)
    noexcept -> Size {
  return fmtEstSizeOf(fwd<F>(f)) + fmtEstSizeOfN(fwd<R>(r)...);
}

template<typename C>
class FmtIt {
public:
  using View = BaseStringView<C, StringUtils<C, StringTraits<C>>>;

  CDS_ATTR(2(explicit, constexpr(14))) FmtIt(View const &view)
  CDS_ATTR(noexcept(false)):
      _b{view.data()},
      _e{view.data() + view.length()},
      _n{locateStart(_b)} {}

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(false)) -> FmtIt & {
    if (_b == _e) {
      return *this;
    }

    _b = minOf(locateEnd(_n + 1) + 1, _e);
    _n = minOf(locateStart(_b), _e);
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const noexcept -> View {
    return View{_b, static_cast<Size>(_n - _b)};
  }

private:
  CDS_ATTR(2(nodiscard, constexpr(14))) auto locateStart(C const *from) CDS_ATTR(noexcept(false)) -> C const * {
    while (from < _e) {
      auto encountered = false;
      if (*from == static_cast<C>('{')) {
        encountered = true;
      }
      ++from;
      if (from == _e) {
        return _e;
      }
      if (encountered && *from != static_cast<C>('{')) {
        return from - 1;
      }

      if (encountered) {
        ++from;
      }
    }

    return _e;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto locateEnd(C const *from) CDS_ATTR(noexcept(false)) -> C const * {
    while (from < _e) {
      auto encountered = false;
      if (*from == static_cast<C>('}')) {
        encountered = true;
      }
      ++from;
      if (encountered && (from == _e || *from != static_cast<C>('}'))) {
        return from - 1;
      } else if (encountered && from + 1 == _e && *from == static_cast<C>('}')) {
        return _e - 2;
      }
    }

    return _e;
  }

  C const *_b;
  C const *_e;
  C const *_n;
};

template <typename T> struct Formatter {
  template <typename S, typename O> CDS_ATTR(constexpr(14)) auto operator()(S& string, O&& obj)
      const CDS_ATTR(noexcept(false)) -> void {
    string += fwd<O>(obj);
  }
};

template <typename C, typename T, typename A, typename V> CDS_ATTR(constexpr(14))
auto fmtAppendIt(BaseString<C, T, A>& str, V&& v) CDS_ATTR(noexcept(false)) -> void {
  bool prevBracket = false;
  for (auto c : fwd<V>(v)) {
    if (prevBracket) {
      prevBracket = false;
      continue;
    }

    str += c;
    if (c == static_cast<C>('{')) {
      prevBracket = true;
    } else if (c == static_cast<C>('}')) {
      prevBracket = true;
    }
  }
}

template<typename C, typename T, typename A, typename I, typename F, typename... R>
CDS_ATTR(constexpr(14)) auto fmtAppend(BaseString<C, T, A> &str, I &&it, F &&first, R &&... rem)
    CDS_ATTR(noexcept(false)) -> void {
  fmtAppendIt(str, *fwd<I>(it));
  Formatter<RemoveCVRef<F>>{}(str, fwd<F>(first));
  fmtAppend(str, ++it, fwd<R>(rem)...);
}

template<typename C, typename T, typename A, typename I>
CDS_ATTR(constexpr(14)) auto fmtAppend(BaseString<C, T, A> &str, I &&it) CDS_ATTR(noexcept(false)) -> void {
  fmtAppendIt(str, *fwd<I>(it));
}

template<typename C, typename T>
class BaseCallableFormatString : public BaseFormatString<C, T> {
  using BaseFormatString<C, T>::analyze;
public:
  using BaseFormatString<C, T>::get;

  template<typename... Args>
  CDS_ATTR(2(nodiscard, constexpr(20))) auto operator()(Args &&... args) const
  CDS_ATTR(noexcept(false)) -> BaseString<C, T, Allocator<C>> {
    auto const traits = analyze();
    if (traits.paramCount != sizeof... (Args)) {
      throw FormatStringException();
    }

    auto len = traits.estSize + (fmtEstSizeOfN(fwd<Args>(args)...));
    String res;
    res.reserve(len);
    fmtAppend(res, FmtIt<C>{get()}, fwd<Args>(args)...);
    return res;
  }
};

//template <typename C, typename T, typename... Args> CDS_ATTR(2(nodiscard, constexpr(20)))
//auto format(BaseFormatString<C, T> format, Args&&... args) CDS_ATTR(noexcept(false))
//    -> BaseString<C, T, Allocator<C>> {
//  return "";
//  return format(BaseFormatString<C, StringUtils<C, StringTraits<C>>>{format}, fwd<Args>(args)...);
//}

//#if CDS_ATTR(ctad)
//template <typename C> BaseFormatString(C const*) -> BaseFormatString<C, StringUtils<C, StringTraits<C>>>;
//template <typename C> BaseFormatString(C const(&)[]) -> BaseFormatString<C, StringUtils<C, StringTraits<C>>>;
//#endif // #if CDS_ATTR(ctad)

using CallableFormatString = BaseCallableFormatString<char, StringUtils<char, StringTraits<char>>>;
} // namespace impl

//using impl::format;

inline namespace literals {
CDS_ATTR(2(nodiscard, consteval(20, constexpr(14))))
auto operator ""_f(char const *fmt, std::size_t len) noexcept -> impl::CallableFormatString {
  return {impl::BaseStringView{fmt, len}};
}
} // namespace literals

using impl::Formatter;
} // namespace experimental
} // namespace cds

#include "OptionalFormat.hpp"
#include "VectorFormat.hpp"

#endif // #ifndef CDS_FORMAT_FORMAT_HPP
