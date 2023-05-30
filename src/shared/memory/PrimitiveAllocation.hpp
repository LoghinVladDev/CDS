//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_SHARED_PRIMITIVE_ALLOCATION_HPP__
#define __CDS_SHARED_PRIMITIVE_ALLOCATION_HPP__ // NOLINT(bugprone-reserved-identifier)
#pragma once

#include <CDS/exception/OutOfMemoryException>

namespace cds {           // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {      // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {        // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __allocation {  // NOLINT(bugprone-reserved-identifier)

template < typename __Type, Size __size = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
struct __RawContainer { // NOLINT(bugprone-reserved-identifier)
  constexpr static auto size = __size;
  using Type = __Type;

  template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
  __CDS_cpplang_ConstexprNonLiteralReturn auto construct (
          __ArgumentTypes && ... arguments
  ) noexcept -> void {
    new (&this->_data[0u]) __Type(std::forward <__ArgumentTypes> (arguments)...);
  }

  __CDS_cpplang_ConstexprNonLiteralReturn auto destruct () noexcept -> void {
    this->data().~__Type();
  }

  constexpr auto data () const noexcept -> __Type const& {
    return *static_cast<__Type const*>(static_cast<void const*>(&this->_data[0u]));
  }

  __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __Type& {
    return *static_cast<__Type*>(static_cast<void*>(&this->_data[0u]));
  }

  alignas (__Type) Byte _data [ __size ] {0};
};


template <
    typename __Type,                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Size __align,                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Size __size,                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    bool __fastRealloc = __align <= alignof(max_align_t),                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    bool __checkedRealloc = !__fastRealloc && __align <= 2u * alignof(max_align_t), /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    bool __slowRealloc = !__checkedRealloc                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
> struct __PrimitiveRealloc {};                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

template <typename __Type, Size __align, Size __size> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
struct __PrimitiveRealloc <__Type, __align, __size, true, false, false> {
  inline auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    (void) oldElementCount;
    auto pNewBuffer = static_cast<__Type*>(reallocf(pOldBuffer, __size * newElementCount));
    if (pNewBuffer == nullptr) {
      throw OutOfMemoryException();
    }

    assert(pNewBuffer % __align == 0u);
    return pNewBuffer;
  }
};

template <typename __Type, Size __align, Size __size> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
struct __PrimitiveRealloc <__Type, __align, __size, false, true, false> {
inline auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
  auto const size = __size * newElementCount;
  auto pNewBuffer = reallocf(pOldBuffer, size);
  if (pNewBuffer == nullptr) {
    throw OutOfMemoryException();
  }

  if (pNewBuffer % __align != 0u) {
    auto pAlignedBuffer = aligned_alloc(__align, size * oldElementCount);
    if (pAlignedBuffer == nullptr) {
      free(pNewBuffer);
      throw OutOfMemoryException();
    }

    free(cds::exchange(pNewBuffer, static_cast<__Type*>(std::memcpy(pAlignedBuffer, pNewBuffer, size))));
  }

  return pNewBuffer;
}
};

template <typename __Type, Size __align, Size __size> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
struct __PrimitiveRealloc <__Type, __align, __size, false, false, true> {
inline auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
  auto pNewBuffer = aligned_alloc(__align, __size * newElementCount);
  if (pNewBuffer == nullptr) {
    free(pNewBuffer);
    throw OutOfMemoryException();
  }

  free(cds::exchange(pNewBuffer(std::memcpy(pNewBuffer, pOldBuffer, __size * oldElementCount))));
  return pNewBuffer;
}
};

template <
    typename __Type,                                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Size __align                = alignof(__Type),                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Size __size                 = sizeof(__Type)                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) *//* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
> struct __PrimitiveAlloc : __PrimitiveRealloc <                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __Type,
    __align,
    __size
> {
  using Type = __Type;
  constexpr static auto const size              = __size;
  constexpr static auto const align             = __align;
  constexpr static auto const adjustedSize      = cds::maxOf(size, align);

  static_assert(adjustedSize % align == 0, "Size must be a multiple of alignment");

  inline auto __alloc() noexcept(false) -> __Type* {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto pMemory = static_cast<__Type*>(aligned_alloc(align, adjustedSize));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }

    return pMemory;
  }

  inline auto __free(__Type* pObject) noexcept -> void { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    free(static_cast<void*>(pObject));
  }

  inline auto __alloc(Size elementCount) noexcept(false) -> __Type* {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    assert((size * elementCount) % align == 0u);
    auto pMemory = static_cast<__Type*>(aligned_alloc(align, size * elementCount));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }

    return pMemory;
  }
};


template < typename __Type, Size __primitiveSize = sizeof ( __Type) > // NOLINT(bugprone-reserved-identifier)
__CDS_DeprecatedHint("Use __PrimitiveAlloc::__alloc, as __allocPrimitiveObject does not support aligned allocation")
inline auto __allocPrimitiveObject () noexcept -> __Type * { // NOLINT(bugprone-reserved-identifier)
  return static_cast <__Type *> (malloc (__primitiveSize));
}


template < typename __Type, Size __primitiveSize = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
__CDS_DeprecatedHint("Use __PrimitiveAlloc::__alloc, as __allocPrimitiveArray does not support aligned allocation")
inline auto __allocPrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
        Size capacity
) noexcept -> __Type * {
  return reinterpret_cast < __Type * > ( malloc ( capacity * __primitiveSize ) );
}


template < typename __Type, Size __primitiveSize = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
__CDS_DeprecatedHint("Use __PrimitiveAlloc::__realloc, as __reallocPrimitiveArray does not support aligned allocation")
inline auto __reallocPrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
    __Type  * pBuffer,
    Size      newCapacity
) noexcept -> __Type * {
  return reinterpret_cast < __Type * > (
      realloc ( pBuffer, newCapacity * __primitiveSize )
  );
}


template < typename __Type > // NOLINT(bugprone-reserved-identifier)
__CDS_DeprecatedHint("Use __PrimitiveAlloc::__free, as __freePrimitiveObject does not support aligned allocation")
inline auto __freePrimitiveObject ( // NOLINT(bugprone-reserved-identifier)
    __Type * pObject
) noexcept -> void {
  free ( pObject );
}


template < typename __Type > // NOLINT(bugprone-reserved-identifier)
__CDS_DeprecatedHint("Use __PrimitiveAlloc::__free, as __freePrimitiveArray does not support aligned allocation")
inline auto __freePrimitiveArray ( // NOLINT(bugprone-reserved-identifier)
    __Type * pBuffer
) noexcept -> void {
  free ( pBuffer );
}


template <
    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
    typename __LastType             // NOLINT(bugprone-reserved-identifier)
> inline auto __forwardIntoArray (      // NOLINT(bugprone-reserved-identifier)
    __ElementType       ** ppElement,
    __LastType          && lastValue
) noexcept (false) -> void {
  (void) new ( * ppElement ) __ElementType ( std :: forward < __LastType > ( lastValue ) );
}


template <
    typename     __ElementType,      // NOLINT(bugprone-reserved-identifier)
    typename     __FirstType,        // NOLINT(bugprone-reserved-identifier)
    typename ... __RemainingTypes    // NOLINT(bugprone-reserved-identifier)
> inline auto __forwardIntoArray (       // NOLINT(bugprone-reserved-identifier)
    __ElementType       **      ppElements,
    __FirstType         &&      firstValue,
    __RemainingTypes    && ...  remainingValues
) noexcept (false) -> void {
  (void) new ( * ppElements ) __ElementType ( std :: forward < __FirstType > ( firstValue ) );
  __forwardIntoArray (
      ppElements + 1,
      std :: forward < __RemainingTypes > ( remainingValues ) ...
  );
}

} // namespace __allocation
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_PRIMITIVE_ALLOCATION_HPP__
