//
// Created by loghin on 6/4/24.
//

#if defined(CDS_PRIMITIVE_TUPLE_HPP) && defined(CDS_PRIMITIVE_STRING_BASE_HPP) && !defined(CDS_COMMON_TUPLE_STRING_HPP)
#define CDS_COMMON_TUPLE_STRING_HPP

namespace cds {
namespace impl {
namespace tupleToString {
using meta::EnableIf;
using meta::Eq;
using meta::Lt;
using meta::Int;
using meta::RemoveCVRef;
using meta::IsSame;
using meta::IsIntegral;
using meta::IsFloating;

template <Size idx, Size len, typename S, typename T, EnableIf<Eq<Int<idx + 1>, Int<len>>> = 0>
CDS_ATTR(constexpr(20)) auto tupleToStringIdx(S& string, T const& tuple) -> void {
  string += S{get<idx>(tuple)};
}

template <Size idx, Size len, typename S, typename T, EnableIf<Lt<Int<idx + 1>, Int<len>>> = 0>
CDS_ATTR(constexpr(20)) auto tupleToStringIdx(S& string, T const& tuple) -> void {
  string += S{get<idx>(tuple)};
  string += ", ";
  tupleToStringIdx<idx + 1, len>(string, tuple);
}

template <typename T, typename = void> struct TupleToStringEstLen {
  template <typename U> CDS_ATTR(constexpr(11)) static auto len(CDS_ATTR(unused) U&&) noexcept -> Size {
    return 0U;
  }
};

template <typename T> struct TupleToStringEstLen<T, EnableIf<StringAbstract<T>, void>> {
  template <typename U> CDS_ATTR(constexpr(14)) static auto len(U&& obj) noexcept -> Size {
    return StringAbstract<>::length(fwd<U>(obj));
  }
};

template <> struct TupleToStringEstLen<bool, void> {
  CDS_ATTR(constexpr(11)) static auto len(bool value) noexcept -> Size {
    return value ? 4U : 5U;
  }
};

template <typename T> struct TupleToStringEstLen<T, EnableIf<typename StringTraits<T>::IsChar, void>> {
  CDS_ATTR(constexpr(11)) static auto len(CDS_ATTR(unused) T value) noexcept -> Size {
    return 1U;
  }
};

template <typename T> struct TupleToStringEstLen<T, EnableIf<IsIntegral<T>, void>> {
  CDS_ATTR(constexpr(14)) static auto len(T value) noexcept -> Size {
    return StringUtils<char, StringTraits<char>>::intLength(value, 10);
  }
};

template <typename T> struct TupleToStringEstLen<T, EnableIf<IsFloating<T>, void>> {
  static auto len(T value) noexcept -> Size {
    return StringUtils<char, StringTraits<char>>::floatingLength(value);
  }
};

template <Size idx, Size len, typename T, EnableIf<Eq<Int<idx + 1>, Int<len>>> = 0>
CDS_ATTR(constexpr(20)) auto tupleToStringEstimateLength(T const& tuple) -> Size {
  auto const& data = get<idx>(tuple);
  return TupleToStringEstLen<RemoveCVRef<decltype(data)>>::len(data);
}

template <Size idx, Size len, typename T, EnableIf<Lt<Int<idx + 1>, Int<len>>> = 0>
CDS_ATTR(constexpr(20)) auto tupleToStringEstimateLength(T const& tuple) -> Size {
  auto const& data = get<idx>(tuple);
  return TupleToStringEstLen<RemoveCVRef<decltype(data)>>::len(data)
      + 2U + tupleToStringEstimateLength<idx + 1, len>(tuple);
}

template <typename S, typename... Types> CDS_ATTR(constexpr(20))
auto tupleToString(S& string, Tuple<Types...> const& tuple) CDS_ATTR(noexcept(false)) -> void {
  string.reserve(tupleToStringEstimateLength<0u, sizeof...(Types)>(tuple) + 2U);
  string += "(";
  tupleToStringIdx<0U, sizeof...(Types)>(string, tuple);
  string += ")";
}
} // namespace tupleToString
} // namespace impl

template <typename... Types> template <typename C, typename U, typename A>
CDS_ATTR(2(nodiscard, constexpr(20))) auto Tuple<Types...>::toString(A&& alloc)
    const CDS_ATTR(noexcept(false)) -> impl::BaseString<C, U, A> {
  impl::BaseString<C, U, A> result{fwd<A>(alloc)};
  impl::tupleToString::tupleToString(result, *this);
  return result;
}
} // namespace cds

#endif // CDS_COMMON_TUPLE_STRING_HPP
