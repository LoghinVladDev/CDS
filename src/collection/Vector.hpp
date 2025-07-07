//
// Created by loghin on 10/18/24.
//

#ifndef CDS_COLLECTION_VECTOR_HPP
#define CDS_COLLECTION_VECTOR_HPP
#pragma once

#include <cds/functional/Comparator>
#include <cds/memory/Allocator>

#include "../bindings/BindingSelectors.hpp"
#include "../bindings/static/ContainsOfStaticBinding.hpp"
#include "../bindings/static/FindStaticBinding.hpp"
#include "../bindings/static/FindOfStaticBinding.hpp"
#include "../bindings/static/GenericLoopBinding.hpp"

#include "../ds/array/ArrayBase.hpp"
#include "../ds/array/ArrayDynamicBackScalingBase.hpp"
#include "../ds/array/ArrayTraits.hpp"

#include "vector/VectorDecl.hpp"

namespace cds {
namespace impl {
using functional::Equal;
} // namespace impl

namespace meta {
template <typename T, typename E, typename A, typename S> struct IterableTraits<cds::impl::BaseVector<T, E, A, S>> {
  using Value = T;
  using Iterator = iterator::ForwardAddressIterator<T>;
  using ConstIterator = iterator::ForwardAddressIterator<T const>;
  using ReverseIterator = iterator::BackwardAddressIterator<T>;
  using ConstReverseIterator = iterator::BackwardAddressIterator<T const>;
};
} // namespace meta

namespace impl {
namespace bindingsBV {
using namespace sel;

using ContainsOpt = With<Value, Projector>;
using FindOpt = With<Value, Projector, Immutable, Mutable>;
using LoopOpt = With<Immutable, Mutable>;

template <typename... A> using Self = BaseVector<A...>;
template <typename... A> struct CDS_ATTR(ebo) ContainsOf : ContainsOfStaticBinding<Self<A...>, ContainsOpt> {};
template <typename... A> struct CDS_ATTR(ebo) Find : FindStaticBinding<Self<A...>, FindOpt> {};
template <typename... A> struct CDS_ATTR(ebo) FindOf : FindOfStaticBinding<Self<A...>, FindOpt> {};
template <typename... A> struct CDS_ATTR(ebo) GenericLoop : GenericLoopBinding<Self<A...>, LoopOpt> {};
} // namespace bindingsBV

template <typename T, typename E, typename A, typename S> class CDS_ATTR(ebo) BaseVector :
    public ArrayBase<T, E, A, S>,
    public bindingsBV::ContainsOf<T, E, A, S>,
    public bindingsBV::Find<T, E, A, S>,
    public bindingsBV::FindOf<T, E, A, S>,
    public bindingsBV::GenericLoop<T, E, A, S> {
public:
  using Base = ArrayBase<T, E, A, S>;

  using typename Base::Value;

  using Base::Base;
  using Base::operator=;
};

template <typename T, typename A = Allocator<T>> class Vector :
    public BaseVector<T, Equal<>, A, ArrayDynamicBackScalingBase<T, Equal<>, A, ArrayTraits<T>>> {
public:
  using BaseVector<T, Equal<>, A, ArrayDynamicBackScalingBase<T, Equal<>, A, ArrayTraits<T>>>::BaseVector;
  using BaseVector<T, Equal<>, A, ArrayDynamicBackScalingBase<T, Equal<>, A, ArrayTraits<T>>>::operator=;
};

#if CDS_ATTR(ctad)
template <typename T, typename A = Allocator<T>> Vector(std::initializer_list<T> const&, A const& = {}) -> Vector<T, A>;
#endif // #if CDS_ATTR(ctad)
} // namespace impl

using impl::Vector;
} // namespace cds

#include "../format/VectorFormat.hpp"

#endif // #ifndef CDS_COLLECTION_VECTOR_HPP
