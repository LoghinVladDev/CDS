//
// Created by loghin on 4/8/24.
//

#ifndef CDS_META_ITERABLE_TRAITS_HPP
#define CDS_META_ITERABLE_TRAITS_HPP

#include <cds/iterator/Iterator>
#include <cds/iterator/AddressIterator>

namespace cds {
namespace meta {
namespace impl {
template <typename T, template <typename> class P, typename = typename meta::IsIterable<T>::Type>
struct IsIterableOfThat : meta::False {};

template <typename T, template <typename> class P> struct IsIterableOfThat<T, P, meta::False> : meta::False {};
template <typename T, template <typename> class P> struct IsIterableOfThat<T, P, meta::True> :
    P<decltype(*cds::begin(rvalue<T>()))> {};
} // namespace impl

template <typename T, template <typename> class P> struct IsIterableOfThat : impl::IsIterableOfThat<T, P>::Type {};
} // namespace meta
} // namespace cds

#endif // CDS_META_ITERABLE_TRAITS_HPP
