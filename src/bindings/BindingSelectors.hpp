//
// Created by loghin on 12/17/23.
//

#ifndef CDS_SHARED_BINDING_SELECTORS_HPP
#define CDS_SHARED_BINDING_SELECTORS_HPP

#include <cds/meta/Base>

namespace cds {
namespace impl {
namespace sel {
struct Value {};
struct Selector {};
struct Forward {};
struct Backward {};
struct Immutable {};
struct Mutable {};

template <typename...> struct With {};

template <typename S, typename M> struct Matches : ::cds::meta::IsSame<S, M> {};

template <template <typename...> class S, typename M> struct TMatches : ::cds::meta::False {};
template <template <typename...> class S, typename ...MPs> struct TMatches<S, S<MPs...>> : ::cds::meta::True {};

template <typename S, typename...> struct AppearsIn : ::cds::meta::False {};
template <typename S> struct AppearsIn<S> : ::cds::meta::False {};
template <typename S, typename F, typename... R> struct AppearsIn<S, F, R...> :
    ::cds::meta::Conditional<Matches<S, F>, ::cds::meta::True, AppearsIn<S, R...>> {};

template <template <typename...> class S, typename...> struct TAppearsIn : ::cds::meta::False {};
template <template <typename...> class S> struct TAppearsIn<S> : ::cds::meta::False {};
template <template <typename...> class S, typename F, typename... R> struct TAppearsIn<S, F, R...> :
    ::cds::meta::Conditional<TMatches<S, F>, ::cds::meta::True, TAppearsIn<S, R...>> {};

template <typename W, typename S> struct ContainsSelector : ::cds::meta::False {};
template <typename... Pack, typename S> struct ContainsSelector<With<Pack...>, S> : AppearsIn<S, Pack...> {};

template <typename W, typename... S> struct ContainsAllSelectors :
    meta::All<meta::Bind<ContainsSelector, W, meta::Ph<0>>::template Type, S...> {};

template <typename W, template <typename...> class S> struct TContainsSelector : ::cds::meta::False {};
template <typename... Pack, template <typename...> class S>
struct TContainsSelector<With<Pack...>, S> : TAppearsIn<S, Pack...> {};

template <typename P, typename E> struct Push {};
template <template <typename...> class F, typename... Pack, typename E> struct Push<F<Pack...>, E> {
  using Type = F<Pack..., E>;
};

template <template <typename...> class S, typename...> struct TSplitMergeWithout;
template <template <typename...> class S> struct TSplitMergeWithout<S> {
  using Type = With<>;
};

template <template <typename...> class S, typename F, typename... R> struct TSplitMergeWithout<S, F, R...> {
  using Without = typename TSplitMergeWithout<S, R...>::Type;
  using Type = ::cds::meta::Conditional<
      TMatches<S, F>,
      Without,
      typename Push<Without, F>::Type
  >;
};

template <typename W, template <typename...> class S> struct TExtractSelector {
  using Type = void;
};

template <typename... Pack, template <typename...> class S> struct TExtractSelector<With<Pack...>, S> {
  using Type = typename TSplitMergeWithout<S, Pack...>::Type;
};

template <typename T, template <typename...> class F, typename...> struct SplitMergeWithout;
template <typename T, template <typename...> class F> struct SplitMergeWithout<T, F> {
  using Type = F<>;
};

template <typename T, template <typename...> class F, typename Fi, typename... R>
struct SplitMergeWithout<T, F, Fi, R...> {
  using WOut = typename SplitMergeWithout<T, F, R...>::Type;
  using Type = ::cds::meta::Conditional<
      cds::meta::IsSame<T, Fi>,
      WOut,
      typename Push<WOut, Fi>::Type
  >;
};

template <typename P, typename ...T> struct Without {};
template <template <typename...> class F, typename... P, typename T> struct Without<F<P...>, T> {
  using Type = typename SplitMergeWithout<T, F, P...>::Type;
};

template <template <typename...> class F, typename... P, typename T1, typename ...T2> struct Without<F<P...>, T1, T2...> {
  using Type = typename Without<typename Without<F<P...>, T2...>::Type, T1>::Type;
};
} // namespace sel
} // namespace impl
} // namespace cds

#endif // CDS_SHARED_BINDING_SELECTORS_HPP
