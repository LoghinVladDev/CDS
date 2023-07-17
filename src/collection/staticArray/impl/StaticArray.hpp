// NOLINT(llvm-header-guard)
// Created by loghin on 16/02/23.
//

#ifndef __CDS_STATIC_ARRAY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_STATIC_ARRAY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto StaticArray <__Element, __size>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __is_handlers()[static_cast<uint32>(requestType)];
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto StaticArray <__Element, __size>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __is_constHandlers()[static_cast<uint32>(requestType)];
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray <__Element, __size>::StaticArray (
    std::initializer_list <__Element> const& initializerList
) noexcept : Implementation () {
  Size index = 0u;
  for (auto const& element : initializerList) {
    if (index == __size) {
      break;
    }
    *__sab_get(index++) = element;
  }
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable>
__CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray <__Element, __size>::StaticArray (
    __Iterable const& iterable
) noexcept : Implementation () {
  Size index = 0u;
  for (auto const& element : iterable) {
    if (index == __size) {
      break;
    }
    *__sab_get(index++) = element;
  }
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable>
__CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <__Element, __size>::operator = (
    __Iterable const& iterable
) noexcept -> StaticArray& {
  Size index = 0u;
  for (auto const& element : iterable) {
    if (index == __size) {
      break;
    }
    *__sab_get(index++) = element;
  }
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <__Element, __size>::operator = (
    std::initializer_list <__Element> const& initializerList
) noexcept -> StaticArray& {
  Size index = 0u;
  for (auto const& element : initializerList) {
    if (index == __size) {
      break;
    }
    *__sab_get(index++) = element;
  }
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::operator == (
    StaticArray const& array
) const noexcept -> bool {
  return __sab_equals(array);
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::operator != (
    StaticArray const& array
) const noexcept -> bool {
  return !__sab_equals(array);
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto StaticArray <__Element, __size>::size () const noexcept -> Size {
  return __sab_size();
}

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <__Element, __size>::front () noexcept (false) -> __Element & {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }
  return *__sab_get(0);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <__Element, __size>::back () noexcept (false) -> __Element & {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }
  return *__sab_get(__size - 1u);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto StaticArray <__Element, __size>::front () const noexcept (false) -> __Element const& {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }
  return *__sab_get(0);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto StaticArray <__Element, __size>::back () const noexcept (false) -> __Element const& {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }
  return *__sab_get(__size - 1u);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::get (
    Index index
) noexcept (false) -> __Element& {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }

  return *__sab_get(circularAdjustedIndex(index));
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::get (
    Index index
) const noexcept (false) -> __Element const& {
  if (__size == 0u) {
    throw OutOfBoundsException (0u, 0u);
  }
  return *__sab_get(circularAdjustedIndex(index));
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::operator [] (
    Index index
) noexcept (false) -> __Element& {
  return get (index);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::operator [] (
    Index index
) const noexcept (false) -> __Element const& {
  return get(index);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <__Element, __size>::data () noexcept -> __Element * {
  return __sab_data();
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto StaticArray <__Element, __size>::data () const noexcept -> __Element const * {
  return __sab_data();
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Comparator>
__CDS_OptimalInline auto StaticArray <__Element, __size>::sort (
    __Comparator const& comparator
) noexcept -> void {
  __sab_sort(comparator);
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto StaticArray <__Element, __size>::toString () const noexcept(false) -> String {
  // List represented by values enclosed in square brackets. If Empty, return bracket set
  if (__size == 0u) {
    return {"[]"};
  }

  // use a StringStream to output the contents for maximum compatibility. Start with open bracket
  std::stringstream out;
  out << "[ ";

  // iterate through Set and append iterator value to Stream
  for (Size index = 0u; index < __size; ++index) { // NOLINT(clion-misra-cpp2008-8-0-1)
    cds::meta::print (out, *__sab_get(index)) << ", ";
  }

  // transform to std string
  auto asString = out.str();

  // replace ", " with " ]"
  asString[asString.length() - 2u] = ' ';
  asString[asString.length() - 1u] = ']';

  // return std::string to be reused as cds::String
  return asString;
}


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto StaticArray <__Element, __size>::circularAdjustedIndex (
    Index index
) const noexcept -> Index {
  // if given negative index, wrap to the nearest positive index by skipping minimum no. of 'size' blocks
  if (index < 0) {
    index += ((-index) / size() + 1) * size();
  }

  // if greater than size, use remainder.
  if (index >= static_cast<Index>(size())) {
    index = index % size();
  }

  // return bounded index
  return index;
}
} // namespace cds

#endif // __CDS_STATIC_ARRAY_IMPL_HPP__
