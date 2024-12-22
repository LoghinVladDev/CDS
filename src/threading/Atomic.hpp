//
// Created by vloghin on 19.12.2024.
//

#ifndef CDS_THREADING_ATOMIC_HPP
#define CDS_THREADING_ATOMIC_HPP
#pragma once

#include <cds/meta/Compiler>

#define CDS_ATTR_atomic_impl(_variant) CDS_ATTR_atomic_impl_ ## _variant
#define CDS_ATTR_atomic_impl_c11 1u

#ifndef CDS_ATTR_atomic_impl_current
#ifndef __STDC_NO_ATOMICS__
#define CDS_ATTR_atomic_impl_current CDS_ATTR_atomic_impl_c11
#else // #ifndef __STDC_NO_ATOMICS__
#error C11 Atomic operations library not provided by the current compiler, no alternative present.
#endif // #else #ifndef __STDC_NO_ATOMICS__
#endif // #ifndef CDS_ATTR_atomic_impl_current

#if CDS_ATTR(atomic_impl(current)) == CDS_ATTR(atomic_impl(c11))
#include "atomic/AtomicC11.hpp"
#endif // #if CDS_ATTR(atomic_impl(current)) == CDS_ATTR(atomic_impl(c11))

namespace cds {
namespace impl {
class AtomicFlag : private BaseAtomicFlag {
  using Base = BaseAtomicFlag;

public:
  using Base::Base;
  using Base::operator=;
  using Base::clear;
  using Base::testAndSet;
};

template <typename T> class Atomic : public BaseAtomic<T> {
public:
  using BaseAtomic<T>::BaseAtomic;
  using BaseAtomic<T>::operator=;
};

template <typename T> class Atomic<T*> : public BaseAtomicPtr<T> {
public:
  using BaseAtomicPtr<T>::BaseAtomicPtr;
  using BaseAtomicPtr<T>::operator=;
};
} // namespace impl

using impl::Atomic;
using impl::AtomicFlag;
using impl::AtomicMemoryOrder;
} // namespace cds

#endif // #ifndef CDS_THREADING_ATOMIC_HPP
