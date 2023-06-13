//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_SHARED_PRIMITIVE_ALLOCATION_HPP__
#define __CDS_SHARED_PRIMITIVE_ALLOCATION_HPP__ // NOLINT(bugprone-reserved-identifier)
#pragma once

#include <CDS/exception/OutOfMemoryException>
#include <CDS/exception/UnsupportedOperationException>
#include <cassert>

#ifdef __CDS_compiler_MSVC
#include <malloc.h>
#endif

namespace cds {           // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {      // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {        // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __allocation {  // NOLINT(bugprone-reserved-identifier)

#ifdef __CDS_compiler_MSVC
inline auto aligned_alloc(std::size_t align, std::size_t size) -> void* {
    (void) align;
    return malloc(size);
}
#endif

template < typename __Type, Size __size = sizeof ( __Type ) > // NOLINT(bugprone-reserved-identifier)
struct __RawContainer { // NOLINT(bugprone-reserved-identifier)
  constexpr static auto size = __size;
  using Type = __Type;

  template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
  __CDS_cpplang_ConstexprNonLiteralReturn auto construct (
          __ArgumentTypes && ... arguments
  ) noexcept -> void {
    new (&this->_data[0u]) __Type (std::forward <__ArgumentTypes> (arguments)...);
  }

  __CDS_cpplang_ConstexprNonLiteralReturn auto destruct () noexcept -> void {
    this->data().~__Type();
  }

  constexpr auto data () const noexcept -> __Type const& {
    return *static_cast <__Type const*> (static_cast<void const*>(&this->_data[0u]));
  }

  __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __Type& {
    return *static_cast <__Type*> (static_cast<void*>(&this->_data[0u]));
  }

  alignas (__Type) Byte _data [ __size ] {0};
};


template <
    typename __Type,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __BasePrimitiveAllocTraits {                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto const size              = __size;
  constexpr static auto const align             = cds::maxOf(__align, alignof(void*));
  constexpr static auto const adjustedSize      = cds::maxOf(size, align);
};


template <
    typename __Type,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size,                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool __malloc         = __align <= sizeof(void*), // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool __aligned_alloc  = !__malloc                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __BasePrimitiveAlloc {                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static auto __alloc() noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    static_assert(__malloc || __aligned_alloc, "Type is not alloc compatible");
    throw UnsupportedOperationException();
  }

  static auto __alloc(Size) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    static_assert(__malloc || __aligned_alloc, "Type is not alloc compatible");
    throw UnsupportedOperationException();
  }
};


template <
    typename __Type,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __BasePrimitiveAlloc <__Type, __align, __size, true, false> {

  using __Base = __BasePrimitiveAllocTraits <__Type, __align, __size>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  static auto __alloc() noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    auto pMemory = static_cast <__Type*> (malloc(__Base::adjustedSize));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }

    return pMemory;
  }

  static auto __alloc(Size elementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    auto pMemory = static_cast <__Type*> (malloc(__Base::size * elementCount));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }
    return pMemory;
  }
};


template <
    typename __Type,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align,                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __BasePrimitiveAlloc <__Type, __align, __size, false, true> {

  using __Base = __BasePrimitiveAllocTraits <__Type, __align, __size>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static_assert(__Base::adjustedSize % __Base::align == 0, "Size must be a multiple of alignment");

  static auto __alloc() noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    auto pMemory = static_cast <__Type*> (aligned_alloc(__Base::align, __Base::adjustedSize));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }

    return pMemory;
  }

  static auto __alloc(Size elementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    auto pMemory = static_cast <__Type*> (aligned_alloc(__Base::align, __Base::size * elementCount));
    if (pMemory == nullptr) {
      throw OutOfMemoryException();
    }
    return pMemory;
  }
};


template <
    typename __Type,                                                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align,                                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size,                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool __fastRealloc = __align <= alignof(max_align_t),                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool __checkedRealloc = !__fastRealloc && __align <= 2u * alignof(max_align_t), // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool __slowRealloc = !__fastRealloc && !__checkedRealloc                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __BasePrimitiveRealloc {                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static auto __realloc(Size, __Type*, Size) noexcept(false) -> __Type* {           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    static_assert(__fastRealloc || __checkedRealloc || __slowRealloc, "Type is not realloc compatible");
    throw UnsupportedOperationException();
  }
};

template <typename __Type, Size __align, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __BasePrimitiveRealloc <__Type, __align, __size, true, false, false> {
  static auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    (void) oldElementCount;
    auto pNewBuffer = static_cast <__Type*> (realloc(pOldBuffer, __size * newElementCount));
    if (pNewBuffer == nullptr) {
      free(pOldBuffer);
      throw OutOfMemoryException();
    }

    assert(reinterpret_cast<std::size_t>(pNewBuffer) % __align == 0u);
    return pNewBuffer;
  }
};

template <typename __Type, Size __align, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __BasePrimitiveRealloc <__Type, __align, __size, false, true, false> {
  static auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    auto const size = __size * newElementCount;
    auto pNewBuffer = realloc(pOldBuffer, size);
    if (pNewBuffer == nullptr) {
      free(pOldBuffer);
      throw OutOfMemoryException();
    }
  
    if (pNewBuffer % __align != 0u) {
      auto pAlignedBuffer = aligned_alloc(__align, size * oldElementCount);
      if (pAlignedBuffer == nullptr) {
        free(pNewBuffer);
        throw OutOfMemoryException();
      }
  
      free(cds::exchange(pNewBuffer, static_cast <__Type*> (std::memcpy(pAlignedBuffer, pNewBuffer, size * oldElementCount))));
    }
  
    return pNewBuffer;
  }
};

template <typename __Type, Size __align, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __BasePrimitiveRealloc <__Type, __align, __size, false, false, true> {
  static auto __realloc(Size oldElementCount, __Type* pOldBuffer, Size newElementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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
    typename __Type,                                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __align                = alignof(__Type),                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size __size                 = sizeof(__Type)                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)// NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __PrimitiveAlloc : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __BasePrimitiveRealloc <__Type, __align, __size>,
    __BasePrimitiveAlloc <__Type, __align, __size> {
  using Type = __Type;
  using __Alloc = __BasePrimitiveAlloc <__Type, __align, __size>;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)// NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __Base = __BasePrimitiveAllocTraits <__Type, __align, __size>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)// NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  static auto __free(__Type* pObject) noexcept -> void { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    free(static_cast <void*> (pObject));
  }

  static auto __calloc() noexcept(false) -> __Type* { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    return static_cast <__Type*> (std::memset(__Alloc::__alloc(), 0u, __Base::size));
  }
  
  static auto __calloc(Size elementCount) noexcept(false) -> __Type* {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    return static_cast <__Type*> (std::memset(__Alloc::__alloc(elementCount), 0u, __Base::size * elementCount));
  }
};

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
