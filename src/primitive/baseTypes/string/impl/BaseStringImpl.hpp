//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_STRING_BASE_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_STRING_BASE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
Size const __BaseString <__CharType>::minCapacity   = __allocation::__minCapacity;

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
Index const __BaseString <__CharType>::invalidIndex = StringUtils <__CharType>::invalidIndex;

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::whitespace = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::whitespace);

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::digits = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::digits);

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::lowercaseAlphabet = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::lowercaseAlphabet);

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::uppercaseAlphabet = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::uppercaseAlphabet);

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::vowels = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::vowels);

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseStringView <__CharType> const __BaseString <__CharType>::consonants = __BaseStringView <__CharType> (meta::__impl::__StringData <__CharType>::consonants);


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__BaseString const& string) noexcept(false) :
    __BaseString (__BaseStringView <__CharType> (string)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__BaseString <__OtherCharType> const& string) noexcept(false) :
    __BaseString ( __BaseStringView <__OtherCharType> (string) ) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr __BaseString <__CharType>::__BaseString (__BaseString&& string) noexcept :
    _pBuffer (cds::exchange (string._pBuffer, nullptr)),
    _length (cds::exchange (string._length, 0u)),
    _capacity (cds::exchange (string._capacity, 0u)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (__BaseStringView <__CharType> const& string) noexcept(false) {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (string.empty()) {
    return;
  }

  _capacity     = maxOf (__BaseString::minCapacity, string.length() + 1u);
  _length       = string.length();
  _pBuffer      = StringUtils <__CharType>::copy (__Alloc::__alloc (_capacity), 0u, string.cStr(), 0u, _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (__BaseStringView <__OtherCharType> const& string) noexcept(false) {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (string.empty()) {
    return;
  }

  _capacity = maxOf (__BaseString::minCapacity, string.length() + 1u);
  _length   = string.length();
  _pBuffer  = StringUtils <__CharType>::copy (__Alloc::__alloc (_capacity), 0u, string.cStr(), 0u, _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (ElementType const* pString, Size length) noexcept(false) :
    __BaseString (__BaseStringView <__CharType> (pString, length)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (ElementType const* pString) noexcept(false) :
    __BaseString (__BaseStringView <__CharType> (pString)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__OtherCharType const* pString, Size length) noexcept(false) :
    __BaseString (__BaseStringView <__OtherCharType> (pString, length)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__OtherCharType const* pString) noexcept(false) :
    __BaseString (__BaseStringView <__OtherCharType> (pString)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (std::basic_string <__CharType> const& string) noexcept(false) :
    __BaseString (__BaseStringView <__CharType> (string)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (Object const& object) noexcept(false) :
    __BaseString (__BaseStringView <__CharType> (object.toString())) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (Size length, ElementType fillCharacter) noexcept(false) {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (length == 0u) {
    return;
  }

  _length   = length;
  _capacity = maxOf (length + 1u, __BaseString::minCapacity);
  _pBuffer  = __Alloc::__alloc (_capacity);

  for (Size index = 0u; index < _length; ++index) {
    _pBuffer [index] = fillCharacter;
  }

  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (Size length,__OtherCharType fillCharacter) noexcept(false) :
    __BaseString (length, static_cast <ElementType> (fillCharacter)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IteratorType, meta::EnableIf <meta::IsIterator <__IteratorType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (__IteratorType const& begin, __IteratorType const& end) noexcept(false) {
  for (auto iterator = begin; iterator != end; ++iterator) {
    append (static_cast <ElementType> (*iterator));
  }
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (std::initializer_list <ElementType> const& initializerList) noexcept(false) :
    _capacity (maxOf (initializerList.size() + 1u, __BaseString::minCapacity)) {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  _pBuffer = __Alloc::__alloc (_capacity);
  for (auto character : initializerList) {
    _pBuffer [_length++] = character;
  }

  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __OtherCharType, meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value&& !meta::IsSame <__OtherCharType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (
    std::initializer_list <__OtherCharType> const& initializerList
) noexcept(false) :
    _capacity (maxOf (initializerList.size() + 1u, __BaseString::minCapacity)) {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  _pBuffer = __Alloc::__alloc (_capacity);
  for (auto character : initializerList) {
    _pBuffer [_length++] = static_cast <ElementType> (character);
  }

  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (ElementType value) noexcept(false) :
    _length (1u),
    _capacity (__BaseString::minCapacity),
    _pBuffer (__allocation::__StringPrimitiveAlloc <__CharType>::__alloc (__BaseString::minCapacity)) {

  _pBuffer [0] = value;
  _pBuffer [1] = meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (__NumericType value) noexcept(false) :
    _capacity (__BaseString::minCapacity),
    _pBuffer (__allocation::__StringPrimitiveAlloc <__CharType>::__alloc (__BaseString::minCapacity)) {
      
  *StringUtils <ElementType>::writeInteger (_pBuffer, 0u, value, StringUtils <ElementType>::integerLength (value), &_length) = 
      meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__BaseString <__CharType>::__BaseString (bool value) noexcept(false) :
    _capacity (__BaseString::minCapacity),
    _length (value ? 4ULL : 5ULL),
    _pBuffer (__allocation::__StringPrimitiveAlloc <__CharType>::__alloc (__BaseString::minCapacity)) {

  (void) StringUtils <ElementType>::copy (_pBuffer, 0u, value ? "true" : "false", 0u, _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__FloatingPointType value) noexcept(false) :
    __BaseString (std::to_string (value)) {

}

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __AddressType, meta::EnableIf <!meta::IsStringCharType <__AddressType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::__BaseString (__AddressType const* address) noexcept(false) {
  std::stringstream oss;
  oss << address;
  *this = oss.str();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::~__BaseString () noexcept {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __Alloc::__free (_pBuffer);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::begin () noexcept -> Iterator {
  return Iterator (_pBuffer);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::end () noexcept -> Iterator {
  return Iterator (_pBuffer + _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::begin () const noexcept -> ConstIterator {
  return ConstIterator (_pBuffer);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::end () const noexcept -> ConstIterator {
  return ConstIterator (_pBuffer + _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::cbegin () const noexcept -> ConstIterator {
  return ConstIterator (_pBuffer);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::cend () const noexcept -> ConstIterator {
  return ConstIterator (_pBuffer + _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::rbegin () noexcept -> ReverseIterator {
  return ReverseIterator (_pBuffer + _length - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::rend () noexcept -> ReverseIterator {
  return ReverseIterator (_pBuffer - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::rbegin () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pBuffer + _length - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::rend () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pBuffer - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::crbegin () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pBuffer + _length - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString <__CharType>::crend () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pBuffer - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::size () const noexcept -> Size {
  return _length;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::length () const noexcept -> Size {
  return size();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::capacity () const noexcept -> Size {
  return _capacity;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::resize (Size size) noexcept(false) -> void {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  size++;
  if (size == _capacity) {
    return;
  }

  _capacity = maxOf (size, __BaseString::minCapacity);
  _pBuffer = __Alloc::__realloc (_length + 1u, _pBuffer, _capacity);
  if (_length >= _capacity) {
    _length = _capacity - 1u;
  }

  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::reserve (Size size) noexcept(false) -> void {
  if (size < _capacity) {
    return;
  }

  resize (size);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::shrink (
    Size size
) noexcept(false) -> void {
  if (size == limits::U64_MAX) {
    size = _length;
  }

  if (size > _capacity) {
    return;
  }

  resize (size);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::empty () const noexcept -> bool {
  return _length == 0u;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::clear () noexcept -> void {
  if (_pBuffer == nullptr) {
    return;
  }

  _pBuffer [0]  = meta::__impl::__StringData <ElementType>::nullCharacter;
  _length       = 0u;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value>> 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::operator [] (
    __NumericType index
) noexcept (false) -> ElementType& {
  return get (static_cast <Index> (index));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value>> 
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator [] (
    __NumericType index
) const noexcept (false) -> ElementType {
  return get (static_cast <Index> (index));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::at (
    Index index
) noexcept (false) -> ElementType& {
  return get (index);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::at (
    Index index
) const noexcept (false) -> ElementType {
  return get (index);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::get (
    Index index
) noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }
  
  if (index < 0) {
    index += ((-index) / static_cast <Index> (size()) + 1) *
             static_cast <Index> (size());
  }

  if (index >= static_cast <Index> (size())) {
    index = index % static_cast <Index> (size());
  }

  return _pBuffer [index];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::get (
    Index index
) const noexcept (false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }
  
  if (index < 0) {
    index += ((-index) / static_cast <Index> (size()) + 1) *
             static_cast <Index> (size());
  }

  if (index >= static_cast <Index> (size())) {
    index = index % static_cast < Index> (size());
  }

  return _pBuffer [index];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::front () noexcept (false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }

  return _pBuffer [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::front () const noexcept (false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }

  return _pBuffer [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::back () noexcept(false) -> ElementType& {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }

  return _pBuffer [_length - 1u];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::back () const noexcept(false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }

  return _pBuffer [_length - 1u];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::toStdString () const noexcept(false) -> std::basic_string <__CharType> {
  return std::basic_string <__CharType> (_pBuffer);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::cStr () const noexcept -> ElementType const* {
  return _pBuffer == nullptr ? meta::__impl::__StringData <__CharType>::emptyString : _pBuffer;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::data () noexcept -> ElementType * {
  return _pBuffer;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline __BaseString <__CharType>::operator std::basic_string <__CharType> () const noexcept(false) {
  return toStdString();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr __BaseString <__CharType>::operator ElementType const* () const noexcept {
  return cStr();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction __BaseString <__CharType>::operator ElementType * () noexcept {
  return data();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::substr (
    Index from,
    Index until
) const noexcept(false) -> __BaseString <__CharType> {
  if (until == -1 || until > static_cast <Index> (size())) {
    until = static_cast <Index> (size());
  }

  if (from < 0) {
    from = 0;
  }

  if (until < from) {
    return __BaseString ();
  }

  return __BaseString (_pBuffer + from, static_cast <Size> (until - from));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator () (
    Index from,
    Index until
) const noexcept(false) -> __BaseString <__CharType> {
  return substr (from, until);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator = ( // NOLINT(bugprone-unhandled-self-assignment) 
    __ConvertibleType&& string
) noexcept(false) -> __BaseString& {
  return operator = (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))); // NOLINT(misc-unconventional-assign-operator)
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator = ( // NOLINT(bugprone-unhandled-self-assignment)
    __BaseString <__CharType> const& string
) noexcept(false) -> __BaseString& {
  return operator = (__BaseStringView <__CharType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptionalInline auto __BaseString <__CharType>::operator = (
    __BaseString&& string
) noexcept -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (this == &string) {
    return *this;
  }

  __Alloc::__free (cds::exchange (_pBuffer, cds::exchange (string._pBuffer, nullptr)));
  _length   = cds::exchange (string._length, 0u);
  _capacity = cds::exchange (string._capacity, 0u);

  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::operator = (
    __BaseStringView <__CharType> const& string
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (_pBuffer == string.cStr()) {
    return *this;
  }

  if (string.empty()) {
    __Alloc::__free (cds::exchange (_pBuffer, nullptr));
    _length   = 0u;
    _capacity = 0u;
    return *this;
  }

  if (_capacity < string.length() + 1u) {
    _capacity = maxOf (string.length() + 1u, __BaseString::minCapacity);
    __Alloc::__free (cds::exchange (_pBuffer, __Alloc::__alloc (_capacity)));
  }

  _length = string.length();
  (void) StringUtils <ElementType>::copy (_pBuffer, 0u, string.cStr(), 0u, string.length());
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator = (
    ElementType character
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, 2u, &_capacity);
  _length = 1u;
  _pBuffer [0] = character;
  _pBuffer [1] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::operator = (
    __NumericType value
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto valueLength = StringUtils <__CharType>::integerLength (value);
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, valueLength + 1u, &_capacity);
  *StringUtils <__CharType>::writeInteger (_pBuffer, 0u, value, valueLength, &_length) =
      meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::operator = (bool value) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto valueLength = value ? 4u : 5u;
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, valueLength + 1u, &_capacity);
  (void) StringUtils <__CharType>::copy (_pBuffer, 0u, value ? "true" : "false", 0u, valueLength + 1u);
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator = (
    __FloatingPointType value
) noexcept(false) -> __BaseString& {
  return operator = (std::to_string (value)); // NOLINT(misc-unconventional-assign-operator) 
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto __BaseString <__CharType>::equals (
    Object const& object
) const noexcept -> bool {
  if (this == &object) {
    return true;
  }

  auto pString = dynamic_cast <decltype (this)> (&object);
  if (pString == nullptr) {
    return false;
  }

  return operator == (__BaseStringView <__CharType> (*pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator == (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) == __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator == (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) == string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator == (
    ElementType character
) const noexcept -> bool {
  if (length() != 1u) {
    return false;
  }

  return _pBuffer [0] == character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return leftString == __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) == __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  if (string.length() != 1u) {
    return false;
  }

  return string.cStr() [0] == character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator != (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) != __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator != (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) != string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator != (
    ElementType character
) const noexcept -> bool {
  if (length() != 1u) {
    return true;
  }

  return _pBuffer [0] != character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return leftString != __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) != __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  if (string.length() != 1u) {
    return true;
  }

  return string.cStr() [0] != character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator < (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) < __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator < (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) < string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator < (
    ElementType character
) const noexcept -> bool {
  if (empty()) {
    return true;
  }

  return _pBuffer [0] < character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return leftString < __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) < __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  return character < __BaseStringView <__FCharType> (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator > (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) > __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator > (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this) > string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator > (
    ElementType character
) const noexcept -> bool {
  if (empty()) {
    return false;
  }

  if (length() > 1u && _pBuffer [0] == character) {
    return true;
  }

  return _pBuffer [0] > character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return leftString < __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) < __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  if (string.empty()) {
    return false;
  }

  return character > string.cStr() [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator <= (
    __ConvertibleType&& string
) const noexcept -> bool {
  return !(__BaseStringView <__CharType> (*this) > __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator <= (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {

  return !(__BaseStringView <__CharType> (*this) > string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator <= (
    ElementType character
) const noexcept -> bool {
  return !operator > (character);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return !(leftString > __BaseStringView <__FCharType> (rightString));
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return !(__BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) > __BaseStringView <__FCharType> (rightString));
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  return !(character > string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator >= (
    __ConvertibleType&& string
) const noexcept -> bool {
  return !(__BaseStringView <__CharType> (*this) < __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator >= (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return !(__BaseStringView <__CharType> (*this) < string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::operator >= (
    ElementType character
) const noexcept -> bool {
  return !operator < (character);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool {
  return !(leftString < __BaseStringView <__FCharType> (rightString));
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool {
  return !(__BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) < __BaseStringView <__FCharType> (rightString));
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool {
  return !(character < string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    __ConvertibleType&& string
) noexcept(false) -> __BaseString& {
  return append (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    __BaseString&& string
) noexcept(false) -> __BaseString& {
  return append (std::move (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    __BaseStringView <__CharType> const& string
) noexcept(false) -> __BaseString& {
  return append (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    ElementType character
) noexcept(false) -> __BaseString& {
  return append (character);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    __NumericType value
) noexcept(false) -> __BaseString& {
  return append (value);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    bool value
) noexcept(false) -> __BaseString& {
  return append (value);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator += (
    __FloatingPointType value
) noexcept(false) -> __BaseString& {
  return append (value);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __ConvertibleType&& string
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __BaseString&& string
) const& noexcept(false) -> __BaseString {
  __BaseString result;
  result.reserve (length() + string.length() + 1u);
  return result.append (*this).append (std::move (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __BaseStringView <__CharType> const& string
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    ElementType character
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __NumericType value
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + value;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    bool value
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + value;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __FloatingPointType value
) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) + value;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept(false) -> __BaseString <__FCharType> {
  return leftString + __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept(false) -> __BaseString <__FCharType> {
  return __BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString)) + __BaseStringView <__FCharType> (rightString);
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType> {
  return character + __BaseStringView <__FCharType> (string);
}


template <typename __FCharType, typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__FCharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __NumericType                     value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType> {
  return value + __BaseStringView <__FCharType> (string);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    bool                              value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType> {
  return value + __BaseStringView <__FCharType> (string);
}


template <typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __FloatingPointType               value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType> {
  return value + __BaseStringView <__FCharType> (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __ConvertibleType&& string
)&& noexcept(false) -> __BaseString {
  return std::move (append ( __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __BaseString&& string
)&& noexcept(false) -> __BaseString {
  return std::move (append (std::move (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __BaseStringView <__CharType> const& string
)&& noexcept(false) -> __BaseString {
  return std::move (append (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    ElementType character
)&& noexcept(false) -> __BaseString {
  return std::move (append (character));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __NumericType value
)&& noexcept(false) -> __BaseString {
  return std::move (append (value));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    bool value
)&& noexcept(false) -> __BaseString {
  return std::move (append (value));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator + (
    __FloatingPointType value
)&& noexcept(false) -> __BaseString {
  return std::move (append (value));
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType>&&          rightString
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (rightString.prepend (leftString));
}


template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __ConvertibleType&&           leftString,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (rightString.prepend (__BaseStringView <__FCharType> (std::forward <__ConvertibleType> (leftString))));
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __FCharType                   character,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (string.prepend (character));
}


template <typename __FCharType, typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__FCharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __NumericType                 value,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (string.prepend (value));
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    bool                          value,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (string.prepend (value));
}


template <typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator + (
    __FloatingPointType           value,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType> {
  return std::move (string.prepend (value));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::operator * (int count) const& noexcept(false) -> __BaseString {
  return __BaseStringView <__CharType> (*this) * count;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptionalInline auto __BaseString <__CharType>::operator * (int count)&& noexcept(false) -> __BaseString {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (empty() || count == 0) {
    __Alloc::__free (cds::exchange (_pBuffer, nullptr));
    (void) cds::exchange (_length, 0u);
    (void) cds::exchange (_capacity, 0u);

    return std::move (*this);
  }

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length * count + 1u, &_capacity);
  auto newLength = length();
  for (int i = 1; i < count; ++i) {
    StringUtils <__CharType>::copy (_pBuffer, newLength, _pBuffer, 0u, length(), false);
    newLength += length();
  }

  _length = newLength;
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return std::move (*this);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto operator * (
    int                               count,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType> {
  return count * __BaseStringView <__FCharType> (string);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptionalInline auto operator * (
    int                           count,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__FCharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (string.empty() || count == 0) {
    __Alloc::__free (cds::exchange (string._pBuffer, nullptr));
    (void) cds::exchange (string._length, 0u);
    (void) cds::exchange (string._capacity, 0u);

    return std::move (*string);
  }

  string._pBuffer = __Alloc::__enlarge (string._pBuffer, string._capacity, string._length * count + 1u, &string._capacity);
  auto newLength = string.length();
  for (int i = 1; i < count; ++i) {
    StringUtils <__FCharType>::copy (string._pBuffer, newLength, string._pBuffer, 0u, string.length(), false);
    newLength += string.length();
  }

  string._length = newLength;
  string._pBuffer [string._length] = static_cast <__FCharType> ('\0');
  return std::move (*string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    __ConvertibleType&& string
) noexcept(false) -> __BaseString& {
  return append (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    __BaseString&& string
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (empty() && string.empty()) {
    return *this;
  }

  Size newLength = length() + string.length();

  if (_capacity < newLength + 1u && string._capacity >= newLength + 1u) {
    (void) std::memmove (
        string._pBuffer + length(),
        string._pBuffer,
        string.length() * sizeof (__CharType)
    );

    (void) std::memcpy (
        string._pBuffer,
        _pBuffer,
        length() * sizeof (__CharType)
    );

    string._pBuffer [newLength] = meta::__impl::__StringData <ElementType>::nullCharacter;
    __Alloc::__free (cds::exchange (_pBuffer, cds::exchange (string._pBuffer, nullptr)));
    _length   = newLength;
    _capacity = cds::exchange (string._capacity, 0u);
    (void) cds::exchange (string._length, 0u);
    return *this;
  }

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, newLength + 1u, &_capacity);
  StringUtils <__CharType>::copy (_pBuffer, _length, string.cStr(), 0u, string.length());
  _length   = newLength;

  __Alloc::__free (cds::exchange (string._pBuffer, nullptr));
  (void) cds::exchange (string._length, 0u);
  (void) cds::exchange (string._capacity, 0u);
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    __BaseStringView <__CharType> const& string
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (empty() && string.empty()) {
    return *this;
  }

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + string.length() + 1u, &_capacity);
  StringUtils <__CharType>::copy (_pBuffer, _length, string.cStr(), 0u, string.length());
  _length += string.length();
  return *this;
}

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    ElementType character
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + 2u, &_capacity);
  StringUtils <__CharType>::copy (_pBuffer, _length, &character, 0u, 1u);
  ++_length;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    __NumericType value
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto numberLength = StringUtils <__CharType>::integerLength (value);
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + numberLength + 1u, &_capacity);
  *StringUtils <__CharType>::writeInteger (_pBuffer, _length, value, numberLength, &_length) =
      meta::__impl::__StringData <ElementType>::nullCharacter;
  return* this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::append (
    bool value
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  uint8 valueLength = (value ? 4u : 5u);
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + valueLength + 1u, &_capacity);
  StringUtils <__CharType>::copy (_pBuffer, _length, (value ? "true" : "false"), 0u, valueLength);
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::append (
    __FloatingPointType value
) noexcept(false) -> __BaseString& {
  return append (std::to_string (value));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    __ConvertibleType&& string
) noexcept(false) -> __BaseString& {
  return prepend (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    __BaseString&& string
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (string.empty()) {
    return *this;
  }

  auto newLength = _length + string.length();
  string._pBuffer = __Alloc::__enlarge (string._pBuffer, string._capacity, newLength + 1u, &string._capacity);
  StringUtils <__CharType>::copy (string._pBuffer, string.length(), _pBuffer, 0u, length());
  __Alloc::__free (cds::exchange (_pBuffer, cds::exchange (string._pBuffer, nullptr)));

  _length   = newLength;
  _capacity = cds::exchange (string._capacity, 0u);
  (void) cds::exchange (string._length, 0u);
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    __BaseStringView <__CharType> const& string
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (string.empty()) {
    return *this;
  }

  auto newLength = _length + string.length();
  if (_capacity >= newLength + 1u) {
    (void) std::memmove (
        _pBuffer + string.length(),
        _pBuffer,
        _length * sizeof (ElementType)
    );

    _pBuffer [newLength] = meta::__impl::__StringData <ElementType>::nullCharacter;
    _length                = newLength;

    (void) std::memcpy (
        _pBuffer,
        string.cStr(),
        string.length() * sizeof (ElementType)
    );

    return *this;
  }

  _capacity = maxOf (newLength + 1u, __BaseString::minCapacity);
  auto newBuffer = __Alloc::__alloc (_capacity);
  StringUtils <__CharType>::copy (newBuffer, 0u, string.cStr(), 0u, string.length());
  StringUtils <__CharType>::copy (newBuffer, string.length(), _pBuffer, 0u, _length);

  _length = newLength;
  __Alloc::__free (cds::exchange (_pBuffer, newBuffer));
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    ElementType character
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + 2u, &_capacity);
  (void) std::memmove (
      _pBuffer + 1u,
      _pBuffer,
      length() * sizeof ( __CharType )
  );

  _pBuffer [0] = character;
  _pBuffer [++_length] = meta::__impl::__StringData <ElementType>::nullCharacter;

  return * this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    __NumericType value
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto numberLength = StringUtils <__CharType>::integerLength (value);
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + numberLength + 1u, &_capacity);
  (void) std::memmove (
      _pBuffer + numberLength,
      _pBuffer,
      _length * sizeof ( ElementType )
  );

  (void) StringUtils <__CharType>::writeInteger (_pBuffer, 0u, value, numberLength, nullptr);
  _length += numberLength;
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::prepend (
    bool value
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto valueLength = value ? 4u : 5u;
  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, _length + valueLength + 1u, &_capacity);
  (void) std::memmove (
      _pBuffer + valueLength,
      _pBuffer,
      _length * sizeof (ElementType)
  );

  StringUtils <__CharType>::copy (_pBuffer, 0u, (value ? "true" : "false"), 0u, valueLength, false);
  _length += valueLength;
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::prepend (
    __FloatingPointType value
) noexcept(false) -> __BaseString& {
  return prepend (std::to_string (value));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::contains (
    ElementType character
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).contains (character);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::contains (
    __ConvertibleType&& string
) const noexcept(false) -> bool {
  return __BaseStringView <__CharType> (*this).contains (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::contains (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> bool {
  return __BaseStringView <__CharType> (*this).contains (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyOf (characters);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllOf (characters);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyNotOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyNotOf (characters);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyNotOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAnyNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAnyNotOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllNotOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllNotOf (characters);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllNotOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::containsAllNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).containsAllNotOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                      maxCount,
    ElementType               character,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).find (maxCount, character, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                        maxCount,
    ElementType character
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).find (maxCount, character, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findFirst (
    ElementType character
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findFirst (character);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findLast (
    ElementType character
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findLast (character);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    ElementType               character,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAll (character, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    ElementType character
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAll (character, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).find (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).find (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::findFirst (
    __ConvertibleType&& string
) const noexcept(false) -> Index {
  return __BaseStringView <__CharType> (*this).findFirst (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::findLast (
    __ConvertibleType&& string
) const noexcept(false) -> Index {
  return __BaseStringView <__CharType> (*this).findLast (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAll (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAll (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findOf (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findOf (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findOf (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findOf (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findFirstOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findFirstOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findLastOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findLastOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllOf (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAllOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllOf (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAllOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findNotOf (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findNotOf (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findNotOf (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findNotOf (
      maxCount,
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findFirstNotOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findFirstNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findLastNotOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findLastNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllNotOf (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAllNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      storeIn
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllNotOf (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAllNotOf (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)),
      indices
  );
}\


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).find (maxCount, string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::find (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).find (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::findFirst (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> Index {
  return __BaseStringView <__CharType> (*this).findFirst (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseString <__CharType>::findLast (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> Index {
  return __BaseStringView <__CharType> (*this).findLast (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAll (string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAll (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAll (string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findOf (maxCount, string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findOf (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findFirstOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findFirstOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findLastOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findLastOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllOf (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAllOf (string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllOf (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAllOf (string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findNotOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findNotOf (maxCount, string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findNotOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findNotOf (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findFirstNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findFirstNotOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::findLastNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  return __BaseStringView <__CharType> (*this).findLastNotOf (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllNotOf (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return __BaseStringView <__CharType> (*this).findAllNotOf (string, storeIn);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::findAllNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return __BaseStringView <__CharType> (*this).findAllNotOf (string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::ltrim (__ConvertibleType&& characters) noexcept -> __BaseString& {
  return ltrim (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (characters)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::ltrim (__BaseStringView <__CharType> const& characters) noexcept -> __BaseString& {
  Size offset = 0u;
  while (offset < length() && characters.contains (_pBuffer [offset])) {
    ++offset;
  }

  if (offset == 0u) {
    return *this;
  }

  _length -= offset;
  (void) std::memmove (
      _pBuffer,
      _pBuffer + offset,
      length() * sizeof (ElementType)
  );

  _pBuffer [length()] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::ltrim (ElementType character) noexcept -> __BaseString& {
  Size offset = 0u;
  while (offset < length() && character == _pBuffer [offset]) {
    ++offset;
  }

  if (offset == 0u) {
    return *this;
  }

  _length -= offset;
  (void) std::memmove (
      _pBuffer,
      _pBuffer + offset,
      length() * sizeof (ElementType)
  );

  _pBuffer [length()] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::rtrim (ElementType character) noexcept -> __BaseString& {
  Index offset = static_cast <Index> (length()) - 1;
  while (offset >= 0 && _pBuffer [offset] == character) {
    --offset;
  }

  if (offset == 0) {
    return *this;
  }

  _length = offset + 1u;
  _pBuffer [length()] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::rtrim (__ConvertibleType&& characters) noexcept -> __BaseString& {
  return rtrim (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (characters)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::rtrim (__BaseStringView <__CharType> const& characters) noexcept -> __BaseString& {
  Index offset = static_cast <Index> (length()) - 1;
  while (offset >= 0 && characters.contains (_pBuffer [offset])) {
    --offset;
  }

  if (static_cast <Size> (offset) + 1u == length()) {
    return *this;
  }

  _length = static_cast <Size> (offset) + 1u;
  _pBuffer [length()] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::trim (ElementType character) noexcept -> __BaseString& {
  return ltrim (character).rtrim (character);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::trim (__ConvertibleType&& characters) noexcept -> __BaseString& {
  auto view = __BaseStringView <__CharType> (std::forward <__ConvertibleType> (characters));
  return ltrim (view).rtrim (view);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::trim (__BaseStringView <__CharType> const& characters) noexcept -> __BaseString& {
  return ltrim (characters).rtrim (characters);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused auto __BaseString <__CharType>::ljust (Size size, ElementType element) noexcept -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (size <= length()) {
    return *this;
  }

  size -= length();
  auto newCapacity = maxOf (_capacity, size + length() + 1u, __BaseString::minCapacity);
  auto newBuffer = __Alloc::__alloc (newCapacity);
  for (Size index = 0u; index < size; ++index) {
    newBuffer [index] = element;
  }

  StringUtils <__CharType>::copy (newBuffer, size, _pBuffer, 0u, length());
  __Alloc::__free (cds::exchange (_pBuffer, newBuffer));
  _capacity = newCapacity;
  _length = size + _length;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused auto __BaseString <__CharType>::rjust (Size size, ElementType element) noexcept -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (size <= length()) {
    return *this;
  }

  _pBuffer = __Alloc::__enlarge (_pBuffer, _capacity, size + 1u,& _capacity);
  for (Size index = length(); index < size; ++index) {
    _pBuffer [index] = element;
  }

  _pBuffer [size] = meta::__impl::__StringData <ElementType>::nullCharacter;
  _length = size;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::toLower () noexcept -> __BaseString& {
  for (Size index = 0u; index < length(); ++index) {
    _pBuffer [index] = StringUtils <__CharType>::lower (_pBuffer [index]);
  }

  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::toUpper () noexcept -> __BaseString& {
  for (Size index = 0u; index < length(); ++index) {
    _pBuffer [index] = StringUtils <__CharType>::upper (_pBuffer [index]);
  }

  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __CollectionType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    ElementType       separator,
    __CollectionType& storeIn,
    Size              maxCount
) const noexcept(false) -> __CollectionType& {
  return __BaseStringView <__CharType> (*this).split (separator, storeIn, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    ElementType separator,
    Size        maxCount
) const noexcept(false) -> __CollectionType <__BaseString> {
  __CollectionType <__BaseString> tokens;
  return __BaseStringView <__CharType> (*this).split (separator, tokens, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    __ConvertibleType&& separators,
    __CollectionType&   storeIn,
    Size                maxCount
) const noexcept(false) -> __CollectionType& {
  return __BaseStringView <__CharType> (*this).split (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (separators)),
      storeIn, maxCount
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    __ConvertibleType&& separators,
    Size                maxCount
) const noexcept(false) -> __CollectionType <__BaseString> {
  __CollectionType <__BaseString> tokens;
  return __BaseStringView <__CharType> (*this).split (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (separators)),
      tokens, maxCount
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __CollectionType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    __BaseStringView <__CharType> const&  separators,
    __CollectionType&                     storeIn,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType& {
  return __BaseStringView <__CharType> (*this).split (separators, storeIn, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::split (
    __BaseStringView <__CharType> const&  separators,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType <__BaseString> {
  __CollectionType <__BaseString> tokens;
  return __BaseStringView <__CharType> (*this).split (__BaseStringView <__CharType> (separators), tokens, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_OptimalInline auto __BaseString <__CharType>::splitByString (
    __ConvertibleType&& separator,
    __CollectionType&   storeIn,
    Size                maxCount
) const noexcept(false) -> __CollectionType& {
  return __BaseStringView <__CharType> (*this).splitByString (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (separator)),
      storeIn, maxCount
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_OptimalInline auto __BaseString <__CharType>::splitByString (
    __ConvertibleType&& separator,
    Size                maxCount
) const noexcept(false) -> __CollectionType <__BaseString> {
  __CollectionType <__BaseString> tokens;
  return __BaseStringView <__CharType> (*this).splitByString (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (separator)),
      tokens, maxCount
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __CollectionType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_OptimalInline auto __BaseString <__CharType>::splitByString (
    __BaseStringView <__CharType> const&  separator,
    __CollectionType&                     storeIn,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType& {
  return __BaseStringView <__CharType> (*this).splitByString (separator, storeIn, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_OptimalInline auto __BaseString <__CharType>::splitByString (
    __BaseStringView <__CharType> const&  separator,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType <__BaseString> {
  __CollectionType <__BaseString> tokens;
  return __BaseStringView <__CharType> (*this).splitByString (separator, tokens, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto __BaseString <__CharType>::hash () const noexcept -> Size {
  return __BaseStringView <__CharType> (*this).hash();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::toString () const noexcept(false) -> cds::String {
  return cds::String (cStr());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::startsWith (ElementType character) const noexcept -> bool {
  return !empty() && _pBuffer [0] == character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::startsWith (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).startsWith (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::startsWith (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).startsWith (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __BaseString <__CharType>::endsWith (ElementType character) const noexcept -> bool {
  return !empty() && _pBuffer [_length - 1u] == character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::endsWith (
    __ConvertibleType&& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).endsWith (
      __BaseStringView <__CharType> (std::forward <__ConvertibleType> (string))
  );
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto __BaseString <__CharType>::endsWith (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  return __BaseStringView <__CharType> (*this).endsWith (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removePrefix (
    ElementType character
) noexcept -> __BaseString& {
  if (empty() || _pBuffer [0] != character) {
    return *this;
  }

  --_length;

  (void) std::memmove (
      _pBuffer,
      _pBuffer + 1,
      _length
  );
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removePrefix (
    __ConvertibleType&& string
) noexcept -> __BaseString& {
  return removePrefix (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removePrefix (
    __BaseStringView <__CharType> const& string
) noexcept -> __BaseString& {
  if (!startsWith (string)) {
    return *this;
  }

  _length = _length - string.length();
  (void) std::memmove (
      _pBuffer,
      _pBuffer + string.length(),
      length() - string.length()
  );
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removeSuffix (
    ElementType character
) noexcept -> __BaseString& {
  if (empty() || _pBuffer [_length - 1u] != character) {
    return *this;
  }

  _pBuffer [--_length - 1u] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removeSuffix (
    __ConvertibleType&& string
) noexcept -> __BaseString& {
  return removeSuffix (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::removeSuffix (
    __BaseStringView <__CharType> const& string
) noexcept -> __BaseString& {
  if (!endsWith (string)) {
    return *this;
  }

  _length = _length - string.length();
  _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __CollectionType, typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::join (
    __CollectionType <__BaseString> const&  tokens,
    __ConvertibleType&&                     delimiter
) noexcept(false) -> __BaseString {
  return __BaseString::join (tokens, __BaseStringView <__CharType> (std::forward <__ConvertibleType> (delimiter)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::join (
    __CollectionType <__BaseString> const&  tokens,
    __BaseStringView <__CharType> const&    delimiter
) noexcept(false) -> __BaseString {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  if (tokens.empty()) {
    return result;
  }

  Size lengthOfAllTokens = 0u;
  for (auto iterator = tokens.begin(), end = tokens.end(); iterator != end; ++iterator) {
    lengthOfAllTokens += (*iterator).length();
  }

  result._capacity = maxOf (lengthOfAllTokens + delimiter.length() * (tokens.size() - 1u), __BaseString::minCapacity);
  result._pBuffer = __Alloc::__alloc (result._capacity);
  auto iterator = tokens.begin();
  StringUtils <__CharType>::copy (result._pBuffer, 0u, (*iterator)._pBuffer, 0u, (*iterator)._length, false);

  result._length += (*iterator)._length;
  ++iterator;
  for (auto end = tokens.end(); iterator != end; ++iterator) {
    StringUtils <__CharType>::copy (result._pBuffer, result._length, delimiter.cStr(), 0u, delimiter.length(), false);
    result._length += delimiter.length();
    StringUtils <__CharType>::copy (result._pBuffer, result._length, (*iterator)._pBuffer, 0u, (*iterator)._length, false);
    result._length += (*iterator)._length;
  }

  result._pBuffer [result._length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::join (
    __CollectionType <__BaseString> const&  tokens,
    ElementType                             delimiter
) noexcept(false) -> __BaseString {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  if (tokens.empty()) {
    return result;
  }

  Size lengthOfAllTokens = 0u;
  for (auto iterator = tokens.begin(), end = tokens.end(); iterator != end; ++iterator) {
    lengthOfAllTokens += (*iterator).length();
  }

  result._capacity = maxOf (lengthOfAllTokens + tokens.size() - 1u, __BaseString::minCapacity);
  result._pBuffer = __Alloc::__alloc (result._capacity);
  auto iterator = tokens.begin();
  StringUtils <__CharType>::copy (result._pBuffer, 0u, (*iterator)._pBuffer, 0u, (*iterator)._length, false);
  
  result._length += (*iterator)._length;
  ++iterator;
  for (auto end = tokens.end(); iterator != end; ++iterator) {
    result._pBuffer [result._length++] = delimiter;
    StringUtils <__CharType>::copy (result._pBuffer, result._length, (*iterator)._pBuffer, 0u, (*iterator)._length, false);
    result._length += (*iterator)._length;
  }

  result._pBuffer [result._length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptionalInline auto __BaseString <__CharType>::replace (
    Index               from,
    Index               until,
    __ConvertibleType&& inPlace
) noexcept(false) -> __BaseString& {
  return replace (from, until, __BaseStringView <__CharType> (std::forward <__ConvertibleType> (inPlace )));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptionalInline auto __BaseString <__CharType>::replace (
    Index                                from,
    Index                                until,
    __BaseStringView <__CharType> const& inPlace
) noexcept(false) -> __BaseString& {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  if (from < 0) {
    from = 0;
  }

  if (static_cast <Size> (until) > length()) {
    until = static_cast <Index> (length());
  }

  if (from > until) {
    return *this;
  }

  auto leftLength         = static_cast <Size> (from);
  auto sectionLength      = static_cast <Size> (until - from);
  auto remainingLength    = static_cast <Size> (length() - until);

  _length = length() - sectionLength + inPlace.length();
  if (_length + 1u < _capacity) {
    (void) std::memmove (
        _pBuffer + until + inPlace.length() - sectionLength - 1u,
        _pBuffer + until - 1u,
        (remainingLength + 1u) * sizeof (ElementType)
    );

    (void) std::memcpy (
        _pBuffer + from,
        inPlace.cStr(),
        inPlace.length() * sizeof (ElementType)
    );

    _pBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
    return * this;
  }

  auto newCapacity = maxOf (_length + 1u, __BaseString::minCapacity);
  auto newBuffer = __Alloc::__alloc (newCapacity);
  (void) std::memcpy (
      newBuffer,
      _pBuffer,
      leftLength * sizeof (ElementType)
  );

  (void) std::memcpy (
      newBuffer + from + inPlace.length() - sectionLength,
      _pBuffer + from,
      remainingLength * sizeof (ElementType)
  );

  (void) std::memcpy (
      newBuffer + from,
      inPlace.cStr(),
      inPlace.length() * sizeof (ElementType)
  );

  newBuffer [_length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  _capacity = newCapacity;
  __Alloc::__free (cds::exchange (_pBuffer, newBuffer));
  return *this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString <__CharType>::reverse () noexcept -> __BaseString& {
  if (length() < 2u) {
    return *this;
  }

  Size opposite = _length - 1u;
  for (Size index = 0u; index < opposite; ++index, --opposite) {
    auto aux            = _pBuffer [index];
    _pBuffer [index]    = _pBuffer [opposite];
    _pBuffer [opposite] = aux;
  }

  return* this;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __Action > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::forEach (
    __Action const& action
) noexcept (noexcept(action(meta::referenceOf<ElementType>()))) -> void {
  for (Size index = 0u; index < _length; ++index) {
    action (_pBuffer [index]);
  }
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __Action > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::forEach (
    __Action const& action
) const noexcept (noexcept(action(meta::valueOf <ElementType>()))) -> void {
  for (Size index = 0u; index < _length; ++index) {
    action (_pBuffer [index]);
  }
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::some (
    Size                count,
    __Predicate const&  predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return trueCount == count;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::some (
    Size                count,
    __Predicate const&  predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return trueCount == count;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::atLeast (
    Size                count,
    __Predicate const&  predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount >= count) {
      return true;
    }
  }

  return false;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::atLeast (
    Size                count,
    __Predicate const&  predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount >= count) {
      return true;
    }
  }

  return false;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::atMost (
    Size                count,
    __Predicate const&  predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::atMost (
    Size                count,
    __Predicate const&  predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::moreThan (
    Size                count,
    __Predicate const&  predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  return atLeast (count + 1, predicate);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::moreThan (
    Size                  count,
    __Predicate const&  predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  return atLeast (count + 1, predicate);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::fewerThan (
    Size                count,
    __Predicate const&  predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  return atMost (count - 1, predicate);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::fewerThan (
    Size                count,
    __Predicate const&  predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  return atMost (count - 1, predicate);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::count (
    __Predicate const& predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> Size {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }
  }

  return trueCount;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::count (
    __Predicate const& predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> Size {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      ++trueCount;
    }
  }

  return trueCount;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::any (
    __Predicate const& predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::any (
    __Predicate const& predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::all (
    __Predicate const& predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (!predicate (_pBuffer [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::all (
    __Predicate const& predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (!predicate (_pBuffer [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::none (
    __Predicate const& predicate
) noexcept (noexcept(predicate(meta::referenceOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::none (
    __Predicate const& predicate
) const noexcept(noexcept(predicate(meta::valueOf <ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pBuffer [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::format (
    __CharType const*     pFormat,
    __ArgumentTypes&&...  arguments
) noexcept ( false ) -> __BaseString {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  auto formatLength = StringUtils <__CharType>::length (pFormat);
  result._capacity = StringUtils <__CharType>::stringLengthOfArguments (
      std::forward <__ArgumentTypes> (arguments)...
  ) + __CDS_StringFormat_StartSize + formatLength;

  result._pBuffer = __Alloc::__alloc ( result._capacity );
  result._length = std::snprintf (
      result._pBuffer, result._capacity,
      pFormat, std::forward <__ArgumentTypes> (arguments) ...
  );

  if (result._capacity <= result._length) {
    __Alloc::__free (result._pBuffer);
    result._capacity = result._length + 1u;
    __Alloc::__alloc (result._capacity);
    result._length = std::snprintf (
        result._pBuffer, result._capacity,
        pFormat, std::forward <__ArgumentTypes> (arguments) ...
    );
  }

  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __BaseString <__CharType>::f (
    __CharType const*     pFormat,
    __ArgumentTypes&&...  arguments
) noexcept (false) -> __BaseString {
  return __BaseString <__CharType>::format (pFormat, std::forward <__ArgumentTypes> (arguments) ...);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::wostream&                    out,
    __BaseString <__FCharType> const& obj
) noexcept -> std::wostream & {
  return out.write(obj.cStr(), obj.size());
}


#if defined(CDS_STRING_DEBUG)
template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __BaseString <__CharType>::diag () const noexcept -> __BaseString {
  return __BaseStringView <__CharType> ( "Debug = { data = '" ) + _pBuffer +
      "', length = " + _length +
      ", capacity = " + _capacity + " }";
}
#endif


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::ostream&                     out,
    __BaseString <__FCharType> const& obj
) noexcept -> std::ostream & {
  return out.write(obj.cStr(), obj.size());
}

} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_STRING_BASE_IMPL_HPP__ 
