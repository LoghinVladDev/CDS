//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_FIND_HPP
#define CDS_PRIMITIVE_STRING_FIND_HPP
#pragma once

#include <cds/Utility>

#include "StringViewBaseDecl.hpp"

namespace cds {
namespace impl {
using meta::Not;
using meta::RemoveCVRef;
using meta::False;
using meta::True;
using functional::Equal;

template <typename C, typename U, typename V>
struct GenericFindEnabledFor<BaseStringView<C, U>, V, Equal<>> : Not<IsString<RemoveCVRef<V>>> {};

// template <typename> struct IsBaseStringView : False {};
// template <typename C, typename U> struct IsBaseStringView<BaseStringView<C, U>> : True {};
//
// template <typename TAttr, typename VAttr, typename P, typename Tr> class StringFindIterableRange {
// public:
//   using Iterable = TAttr;
//   using Value = VAttr;
//   using Predicate = P;
//   using Transformer = Tr;
//   using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
//   using Iterator = StringFindIterator<UnderlyingIterator, RemoveRef<VAttr>, P, Tr>;
//   using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
//   using ConstIterator = StringFindIterator<UnderlyingConstIterator, RemoveRef<VAttr>, P, Tr>;
//
//   template <typename T, typename V> CDS_ATTR(constexpr(11)) StringFindIterableRange(T&& obj, V&& v)
//       CDS_ATTR(noexcept(noexcept(TAttr(cds::forward<T>(obj))) && noexcept(VAttr(cds::forward<V>(v))))) :
//       _o(cds::forward<T>(obj)), _v(cds::forward<V>(v)) {}
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
//       CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v)))) -> Iterator {
//     return Iterator(cds::begin(_o), cds::end(_o), _v);
//   }
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
//       CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v)))) -> ConstIterator {
//     return ConstIterator(cds::begin(_o), cds::end(_o), _v);
//   }
//
// #if CDS_ATTR(sentinel)
//   CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
//     return {};
//   }
// #else // #if CDS_ATTR(sentinel)
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
//       CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v)))) -> Iterator {
//     return Iterator(cds::end(_o), cds::end(_o), _v);
//   }
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
//       CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v)))) -> ConstIterator {
//     return ConstIterator(cds::end(_o), cds::end(_o), _v);
//   }
// #endif // #if CDS_ATTR(sentinel) #else
//
// private:
//   TAttr _o;
//   VAttr const _v;
// };
//
// template <typename TAttr, typename VAttr, typename SAttr, typename P, typename Tr> class StringFindSelectIterableRange {
// public:
//   using Iterable = TAttr;
//   using Value = VAttr;
//   using Predicate = P;
//   using Transformer = Tr;
//   using UnderlyingIterator = decltype(cds::begin(value<TAttr>()));
//   using Iterator = StringFindSelectIterator<UnderlyingIterator, RemoveRef<VAttr>, RemoveRef<SAttr>, P, Tr>;
//   using UnderlyingConstIterator = decltype(cds::begin(value<TAttr const>()));
//   using ConstIterator = StringFindSelectIterator<UnderlyingConstIterator, RemoveRef<VAttr>, RemoveRef<SAttr>, P, Tr>;
//
//   template <typename T, typename V, typename S>
//   CDS_ATTR(constexpr(11)) StringFindSelectIterableRange(T&& obj, V&& v, S&& s) CDS_ATTR(noexcept(
//       noexcept(TAttr(cds::forward<T>(obj)))
//       && noexcept(VAttr(cds::forward<V>(v)))
//       && noexcept(SAttr(cds::forward<S>(s)))
//   )) : _o(cds::forward<T>(obj)), _v(cds::forward<V>(v)), _s(cds::forward<S>(s)) {}
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto begin()
//       CDS_ATTR(noexcept(noexcept(Iterator(cds::begin(_o), cds::end(_o), _v, _s)))) -> Iterator {
//     return Iterator(cds::begin(_o), cds::end(_o), _v, _s);
//   }
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const
//       CDS_ATTR(noexcept(noexcept(ConstIterator(cds::begin(_o), cds::end(_o), _v, _s)))) -> ConstIterator {
//     return ConstIterator(cds::begin(_o), cds::end(_o), _v, _s);
//   }
//
// #if CDS_ATTR(sentinel)
//   CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Sentinel {
//     return {};
//   }
// #else // #if CDS_ATTR(sentinel)
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto end()
//       CDS_ATTR(noexcept(noexcept(Iterator(cds::end(_o), cds::end(_o), _v, _s)))) -> Iterator {
//     return Iterator(cds::end(_o), cds::end(_o), _v, _s);
//   }
//
//   CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const
//       CDS_ATTR(noexcept(noexcept(ConstIterator(cds::end(_o), cds::end(_o), _v, _s)))) -> ConstIterator {
//     return ConstIterator(cds::end(_o), cds::end(_o), _v, _s);
//   }
// #endif // #if CDS_ATTR(sentinel) #else
//
// private:
//   TAttr _o;
//   VAttr const _v;
//   SAttr const _s;
// };
//
// template <
//     typename I, typename V, typename P, typename T,
//     typename R = StringFindIterableRange<Extend<I>, Extend<V>, P, T>,
//     EnableIf<IsBaseStringView<RemoveCVRef<I>>> = 0
// > CDS_ATTR(2(nodiscard, constexpr(20))) auto find(
//     I&& view, V&& value, CDS_ATTR(unused) P const& equal, CDS_ATTR(unused) T const& transform
// ) CDS_ATTR(noexcept(noexcept(R(cds::forward<I>(view), cds::forward<V>(value))))) -> R {
//   return R(cds::forward<I>(view), cds::forward<V>(value));
// }
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_FIND_HPP
