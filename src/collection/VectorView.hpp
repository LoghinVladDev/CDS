//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_VECTOR_VIEW_HPP
#define CDS_COLLECTION_VECTOR_VIEW_HPP
#pragma once

#include "../bindings/BindingSelectors.hpp"
#include "../bindings/static/ContainsOfStaticBinding.hpp"
#include "../bindings/static/FindStaticBinding.hpp"
#include "../bindings/static/FindOfStaticBinding.hpp"
#include "../bindings/static/GenericLoopBinding.hpp"

#include "vectorView/DynamicVectorViewBase.hpp"
#include "vectorView/StaticVectorViewBase.hpp"
#include "vectorView/VectorViewBase.hpp"
#include "vectorView/VectorViewDecl.hpp"

namespace cds {
namespace impl {
using meta::Bool;
using meta::Conditional;
using meta::RemoveRef;
} // namespace impl

namespace meta {
template <typename T, Size extent> struct IterableTraits<cds::impl::VectorView<T, extent>> {
  using Value = T;
  using Iterator = iterator::ForwardAddressIterator<T>;
  using ConstIterator = iterator::ForwardAddressIterator<T const>;
  using ReverseIterator = iterator::BackwardAddressIterator<T>;
  using ConstReverseIterator = iterator::BackwardAddressIterator<T const>;
};
} // namespace meta

namespace impl {
namespace bindingsVV {
using namespace sel;

using ContainsOpt = With<Value, Projector>;
using FindOpt = With<Value, Projector, Immutable, Mutable>;
using LoopOpt = With<Immutable, Mutable>;

template <typename T, Size extent> using Self = VectorView<T, extent>;
template <typename T, Size extent> struct CDS_ATTR(ebo) ContainsOf :
    ContainsOfStaticBinding<Self<T, extent>, ContainsOpt> {};
template <typename T, Size extent> struct CDS_ATTR(ebo) Find :
    FindStaticBinding<Self<T, extent>, FindOpt> {};
template <typename T, Size extent> struct CDS_ATTR(ebo) FindOf :
    FindOfStaticBinding<Self<T, extent>, FindOpt> {};
template <typename T, Size extent> struct CDS_ATTR(ebo) GenericLoop :
    GenericLoopBinding<Self<T, extent>, LoopOpt> {};
} // namespace bindingsVV

template <typename T, Size extent> class VectorView :
    public BaseVectorView<T, Conditional<
        Bool<extent == limits::sizeMax>,
        BaseDynamicVectorView<T>,
        BaseStaticVectorView<T, extent>>
    >,
    public bindingsVV::ContainsOf<T, extent>,
    public bindingsVV::Find<T, extent>,
    public bindingsVV::FindOf<T, extent>,
    public bindingsVV::GenericLoop<T, extent> {
  using Base = BaseVectorView<T, Conditional<
      Bool<extent == limits::sizeMax>,
      BaseDynamicVectorView<T>,
      BaseStaticVectorView<T, extent>>
  >;
public:
  using Base::Base;
  using Base::operator=;
};

template <typename T, Size n> CDS_ATTR(2(nodiscard, constexpr(11))) auto makeView(T(&array)[n]) noexcept ->
    VectorView<T, n> {
  return VectorView<T, n>(array);
}

template <Size r, typename T, Size n> CDS_ATTR(2(nodiscard, constexpr(11))) auto makeView(T(&array)[n]) noexcept ->
    VectorView<T, r> {
  return VectorView<T, r>(array);
}

template <typename R, EnableIf<VectorViewConversion<R>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
auto makeView(R&& data) noexcept -> VectorView<typename VectorViewConversion<R>::ElementType> {
  return VectorView<typename VectorViewConversion<R>::ElementType>{fwd<R>(data)};
}

template <Size r, typename R, EnableIf<VectorViewConversion<R>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
auto makeView(R&& data) noexcept -> VectorView<typename VectorViewConversion<R>::ElementType, r> {
  return VectorView<typename VectorViewConversion<R>::ElementType, r>{fwd<R>(data)};
}

template <typename T, typename E, typename A, typename S> CDS_ATTR(2(nodiscard, constexpr(11)))
auto makeView(BaseVector<T, E, A, S>& data) noexcept -> VectorView<T> {
  return VectorView<T>{data};
}

template <typename T, typename E, typename A, typename S> CDS_ATTR(2(nodiscard, constexpr(11)))
auto makeView(BaseVector<T, E, A, S> const& data) noexcept -> VectorView<T const> {
  return VectorView<T const>{data};
}

#if CDS_ATTR(ctad)
template <typename T, Size n> VectorView(T(&)[n]) -> VectorView<T, n>;
template <typename I, typename S> VectorView(I begin, S endOrSize)
    -> VectorView<RemoveRef<decltype(*begin)>>;
template <typename R> VectorView(R&& range)
    -> VectorView<typename VectorViewConversion<R>::ElementType>;
#endif // #if CDS_ATTR(ctad)
} // namespace impl

using impl::VectorView;
using impl::makeView;
} // namespace cds

#include "../format/VectorViewFormat.hpp"

#endif // #ifndef CDS_COLLECTION_VECTOR_VIEW_HPP
