//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_BASE_STRING_VIEW_IMPL_HPP__   // NOLINT(llvm-header-guard) 
#define __CDS_BASE_STRING_VIEW_IMPL_HPP__   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once


namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
Index const __BaseStringView <__CharType>::invalidIndex = StringUtils <__CharType>::invalidIndex;


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr __BaseStringView <__CharType>::__BaseStringView (__BaseString <__CharType> const& string) noexcept :
    _pData (string._pBuffer), _length (string._length) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr __BaseStringView <__CharType>::__BaseStringView (std::basic_string <__CharType> const& string) noexcept :
    _pData (string.c_str()), _length (string.length()) {

}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr __BaseStringView <__CharType>::__BaseStringView (ElementType const* pString) noexcept :
    __BaseStringView (pString, pString == nullptr ? 0u : StringUtils <__CharType>::length (pString)) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr __BaseStringView <__CharType>::__BaseStringView (ElementType const* pString, Size length) noexcept :
    _pData (pString), _length (length) {

}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::begin () const noexcept -> ConstIterator {
  return ConstIterator (_pData);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::end () const noexcept -> ConstIterator {
  return ConstIterator (_pData + _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::cbegin () const noexcept -> ConstIterator {
  return ConstIterator (_pData);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::cend () const noexcept -> ConstIterator {
  return ConstIterator (_pData + _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::rbegin () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pData + _length - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::rend () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pData - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::crbegin () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pData + _length - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::crend () const noexcept -> ConstReverseIterator {
  return ConstReverseIterator (_pData - 1u);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::length () const noexcept -> Size {
  return _length;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::size () const noexcept -> Size {
  return length();
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::clear () noexcept -> void {
  _pData    = nullptr;
  _length   = 0u;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::empty () const noexcept -> bool {
  return _length == 0u;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __NumericType, cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value>>
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator [] (
    __NumericType index
) const noexcept (false) -> ElementType {
  return get (static_cast <Index> (index));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::at (
    Index index
) const noexcept (false) -> ElementType {
  return get (index);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::get (
    Index index
) const noexcept (false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException (index, 0);
  }

  // if given negative index, wrap to the nearest positive index by skipping minimum no. of 'size' blocks 
  if (index < 0) {
    index += ((-index) / size() + 1) * size();
  }

  // if greater than size, use remainder. 
  if (index >= static_cast <Index> (size())) {
    index = index % size();
  }

  return _pData [index];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::front () const noexcept (false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }
  
  return _pData [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::back () const noexcept (false) -> ElementType {
  if (empty()) {
    throw OutOfBoundsException ("String is Empty");
  }

  return _pData [_length - 1u];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_MaybeUnused __CDS_OptimalInline auto __BaseStringView <__CharType>::toStdString () const noexcept(false) -> std::basic_string <__CharType> {
  return std::basic_string <__CharType> (_pData, _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::cStr () const noexcept -> ElementType const* {
  return _pData == nullptr ? meta::__impl::__StringData <__CharType>::emptyString : _pData;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::data () const noexcept -> ElementType const* {
  return _pData == nullptr ? meta::__impl::__StringData <__CharType>::emptyString : _pData;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr __BaseStringView <__CharType>::operator ElementType const* () const noexcept {
  return _pData;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline __BaseStringView <__CharType>::operator std::basic_string <__CharType> () const noexcept(false) {
  return std::basic_string <__CharType> (_pData);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptionalInline auto __BaseStringView <__CharType>::substr (Index from, Index until) const noexcept(false) ->__BaseString <__CharType> {
  if (until == -1 || until > static_cast <Index> (size())) {
    until = static_cast <Index> (size());
  }

  if (from < 0) {
    from = 0;
  }

  if (until < from) {
    return {};
  }

  return {_pData, static_cast <Size> (until - from)};
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::operator () (Index from, Index until) const noexcept(false) ->__BaseString <__CharType> {
  return substr (from, until);
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::operator = (  // NOLINT(bugprone-unhandled-self-assignment) 
    __BaseString <__CharType> const& string
) noexcept -> __BaseStringView& {
  return operator = (__BaseStringView(string));                                        // NOLINT(misc-unconventional-assign-operator)
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::operator = (  // NOLINT(bugprone-unhandled-self-assignment) 
    __BaseStringView const& string
) noexcept -> __BaseStringView& {
  if (_pData == string._pData) {
    return * this;
  }

  _pData    = string._pData;
  _length   = string._length;

  return* this;
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::operator = (  // NOLINT(bugprone-unhandled-self-assignment) 
    __BaseStringView&& string
) noexcept -> __BaseStringView& {
  if (_pData == string._pData) {
    return *this;
  }

  _pData    = cds::exchange (string._pData, nullptr);
  _length   = cds::exchange (string._length, 0u);

  return *this;
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::operator = (  // NOLINT(bugprone-unhandled-self-assignment) 
    std::basic_string <__CharType> const& string
) noexcept -> __BaseStringView& {
  return operator = (__BaseStringView (string));                                        // NOLINT(misc-unconventional-assign-operator)
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView <__CharType>::operator = (  // NOLINT(bugprone-unhandled-self-assignment) 
    ElementType const* pString
) noexcept -> __BaseStringView& {
  return operator = (__BaseStringView (pString));                                       // NOLINT(misc-unconventional-assign-operator)
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_DynamicCastConstexpr auto __BaseStringView <__CharType>::equals (                 // NOLINT(bugprone-unhandled-self-assignment) 
    Object const& object
) const noexcept -> bool {
  if (this == &object) {
    return * this;
  }

  auto pView = dynamic_cast <decltype (this)> (&object);
  if (pView == nullptr) {
    return false;
  }

  return operator == (*pView);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator == (
    __BaseStringView const& string
) const noexcept -> bool {
  if (length() != string.length()) {
    return false;
  }

  return StringUtils <__CharType>::equal == StringUtils <__CharType>::compare ( _pData, length(), string._pData, string.length());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator == (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return operator == (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator == (
    ElementType const* pString
) const noexcept -> bool {

  return operator == (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator == (
    ElementType character
) const noexcept -> bool {
  if (length() != 1u) {
    return false;
  }

  return _pData [0] == character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator == (
    std::basic_string <__FCharType> const&  leftString,
__BaseStringView <__FCharType> const&       rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (leftString) == rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator == (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> ( pLeftString ) == rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator == (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  if (string.length() != 1u) {
    return false;
  }

  return string.cStr() [0] == character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator != (
    __BaseStringView const& string
) const noexcept -> bool {
  if ( length() != string.length() ) {
    return true;
  }

  return StringUtils <__CharType>::equal != StringUtils <__CharType>::compare (_pData, length(), string._pData, string.length());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator != (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return operator != (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator != (
    ElementType const* pString
) const noexcept -> bool {
  return operator != (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator != (
    ElementType character
) const noexcept -> bool {
  if (length() != 1u) {
    return true;
  }

  return _pData [0] != character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator != (
    std::basic_string <__FCharType> const&  leftString,
__BaseStringView <__FCharType> const&       rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (leftString) != rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator != (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (pLeftString) != rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator != (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  if (string.length() != 1u) {
    return true;
  }

  return string.cStr() [0] != character;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator < (
    __BaseStringView const& string
) const noexcept -> bool {
  return StringUtils <__CharType>::lesser == StringUtils <__CharType>::compare (_pData, length(), string._pData, string.length());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator < (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return operator < (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator < (
    ElementType const* pString
) const noexcept -> bool {
  return operator < (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator < (
    ElementType character
) const noexcept -> bool {
  if (empty()) {
    return true;
  }

  return _pData [0] < character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator < (
    std::basic_string <__FCharType> const&  leftString,
__BaseStringView <__FCharType> const&       rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (leftString) < rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator < (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (pLeftString) < rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator < (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  if (string.empty()) {
    return true;
  }

  if (string.length() > 1 && character == string.cStr() [0]) {
    return true;
  }

  return character < string.cStr() [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator > (
    __BaseStringView const& string
) const noexcept -> bool {
  return StringUtils <__CharType>::greater == StringUtils <__CharType>::compare (_pData, length(), string._pData, string.length());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator > (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return operator > (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator > (
    ElementType const* pString
) const noexcept -> bool {
  return operator > (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator > (
    ElementType character
) const noexcept -> bool {
  if (empty()) {
    return false;
  }

  if (length() > 1 && _pData [0] == character) {
    return true;
  }

  return _pData [1] > character;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator > (
    std::basic_string <__FCharType> const&  leftString,
__BaseStringView <__FCharType> const&       rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (leftString) > rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator > (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return __BaseStringView <__FCharType> (pLeftString) > rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator > (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  if (string.empty()) {
    return false;
  }

  return character > string.cStr() [0];
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator <= (
    __BaseStringView const& string
) const noexcept -> bool {
  return !operator > (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator <= (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return !operator > (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator <= (
    ElementType const* pString
) const noexcept -> bool {
  return !operator > (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator <= (
    ElementType character
) const noexcept -> bool {
  return !operator > ( character );
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator <= (
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool {
  return !( __BaseStringView <__FCharType> (leftString) > rightString );
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return !(__BaseStringView <__FCharType> (pLeftString) > rightString);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  return !(character > string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator >= (
    __BaseStringView const& string
) const noexcept -> bool {
  return !operator < (string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator >= (
    std::basic_string <__CharType> const& string
) const noexcept -> bool {
  return !operator < (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator >= (
    ElementType const* pString
) const noexcept -> bool {
  return !operator < (__BaseStringView (pString));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::operator >= (
    ElementType character
) const noexcept -> bool {
  return !operator < ( character );
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator >= (
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool {
    return !(__BaseStringView <__FCharType> (leftString) < rightString);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool {
  return !(__BaseStringView <__FCharType> (pLeftString) < rightString);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool {
  return !(character < string);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::operator + (
    __BaseStringView <__CharType> const& string
) const noexcept(false) ->__BaseString <__CharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  result._length      = length() + string.length();
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  StringUtils <__CharType>::copy (result.data(), 0u, cStr(), 0u, length(), false);
  StringUtils <__CharType>::copy (result.data(), length(), string.cStr(), 0u, string.length());
  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::operator + (
    std::basic_string <__CharType> const& string
) const noexcept(false) ->__BaseString <__CharType> {
  return operator + (__BaseStringView (string));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::operator + (
    ElementType const* pString
) const noexcept(false) ->__BaseString <__CharType> {
  return operator + (__BaseStringView (pString));
}


template <typename __CharType>                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __TCharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::operator + (
    ElementType character
) const noexcept(false) -> __BaseString <__CharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  __BaseString <__CharType> result;
  result._length      = length() + 1u;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  StringUtils <__CharType>::copy (result.data(), 0u, cStr(), 0u, length(), false);
  result._pBuffer [result._length - 1u] = character;
  result._pBuffer [result._length]      = meta::__impl::__StringData <ElementType>::nullCharacter;
  return result;
}


template <typename __CharType>                                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value>>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::operator + (
    __NumericType value
) const noexcept(false) ->__BaseString <__CharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  auto valueLength = StringUtils <__CharType>::integerLength (value);
  result._length      = length() + valueLength;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  StringUtils <__CharType>::copy (result.data(), 0u, _pData, 0u, length(), false);
  *StringUtils <__CharType>::writeInteger (result.data(), length(), value, valueLength, nullptr) = 
      meta::__impl::__StringData <ElementType>::nullCharacter;

  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::operator + (
    bool value
) const noexcept(false) ->__BaseString <__CharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  auto valueLength = value ? 4u : 5u;
  result._length      = length() + valueLength;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  StringUtils <__CharType>::copy (result._pBuffer, 0u, _pData, 0u, length(), false);
  StringUtils <__CharType>::copy (result._pBuffer, length(), value ? "true" : "false", 0u, valueLength);
  return result;
}


template <typename __CharType>                                                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::operator + (
    __FloatingPointType value
) const noexcept(false) ->__BaseString <__CharType> {
  return operator + (__BaseStringView (std::to_string (value)));
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto operator + (
    std::basic_string <__FCharType> const& leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept(false) ->__BaseString <__FCharType> {
  return __BaseStringView <__FCharType> (leftString) + rightString;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto operator + (
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType>const&  rightString
) noexcept(false) ->__BaseString <__FCharType> {
  return __BaseStringView <__FCharType> (pLeftString) + rightString;
}


template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator + (
    __FCharType                                 character,
    __BaseStringView <__FCharType>    const& string
) noexcept(false) ->__BaseString <__FCharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__FCharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__FCharType> result;
  result._length      = string.length() + 1u;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  result._pBuffer [0] = character;
  StringUtils <__FCharType>::copy (result.data(), 1u, string.cStr(), 0u, string.length());

  result._pBuffer [result._length]          = static_cast <__FCharType> (character);
  return result;
}


template < typename __FCharType, typename __NumericType, meta::EnableIf < meta::isIntegralToString < __FCharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator + (
    __NumericType                         value,
    __BaseStringView <__FCharType> const& string
) noexcept(false) ->__BaseString <__FCharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__FCharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__FCharType> result;
  auto valueLength = StringUtils <__FCharType>::integerLength (value);
  result._length      = string.length() + valueLength;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  (void) StringUtils <__FCharType>::writeInteger (result.data(), 0u, value, valueLength, nullptr);
  StringUtils <__FCharType>::copy (result.data(), valueLength, string.cStr(), 0u, string.length());
  return result;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator + (
    bool                                  value,
    __BaseStringView <__FCharType> const& string
) noexcept(false) ->__BaseString <__FCharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__FCharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__FCharType> result;
  auto valueLength = value ? 4u : 5u;
  result._length      = string.length() + valueLength;
  result._capacity    = maxOf (result._length + 1u, __allocation::__minCapacity);
  result._pBuffer     = __Alloc::__alloc (result._capacity);

  StringUtils <__FCharType>::copy (result.data (), 0u, value ? "true" : "false", 0u, valueLength, false);
  StringUtils <__FCharType>::copy (result.data(), valueLength, string.cStr(), 0u, string.length(), false);
  return result;
}


template <typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto operator + (
    __FloatingPointType                   value,
    __BaseStringView <__FCharType> const& string
) noexcept(false) ->__BaseString <__FCharType> {
  return __BaseStringView <__FCharType> (std::to_string (value)) + string;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::operator * (
    int count
) const noexcept(false) ->__BaseString <__CharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__CharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__CharType> result;
  if (empty() || count == 0) {
    return result;
  }

  if (count == 1) {
    return *this;
  }

  result._capacity = maxOf (count * length() + 1u, __allocation::__minCapacity);
  result._pBuffer = __Alloc::__alloc (result._capacity);
  for (int i = 0; i < count; ++i) {
    StringUtils <__CharType>::copy (result._pBuffer, result._length, _pData, 0u, length(), false);
    result._length += length();
  }

  result._pBuffer [result._length] = meta::__impl::__StringData <ElementType>::nullCharacter;
  return result;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator * (
    int                                   count,
    __BaseStringView <__FCharType> const& string
) noexcept(false) ->__BaseString <__FCharType> {
  using __Alloc = __allocation::__StringPrimitiveAlloc <__FCharType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __BaseString <__FCharType> result;
  if (string.empty() || count == 0) {
    return result;
  }

  if (count == 1) {
    return string;
  }

  result._capacity = maxOf (count * string.length() + 1u, __allocation::__minCapacity);
  result._pBuffer = __Alloc::__alloc (result._capacity);

  for (int i = 0; i < count; ++i) {
    StringUtils <__FCharType>::copy (result._pBuffer, result._length, string.cStr(), 0u, string.length(), false);
    result._length += string.length();
  }

  result._pBuffer [result._length] = static_cast <__FCharType> ('\0');
  return result;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::contains (
    ElementType character
) const noexcept -> bool {
  return findFirst ( character ) != __BaseStringView::invalidIndex;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::contains (
    __ConvertibleType&& string
) const noexcept(false) -> bool {
  return contains (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::contains (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> bool {
  return findFirst (string) != __BaseStringView::invalidIndex;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptionalInline auto __BaseStringView <__CharType>::containsAnyOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (characters.contains (_pData [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAnyOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return containsAnyOf (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAnyOf (
    __BaseStringView const& string
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (string.contains (_pData [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptionalInline auto __BaseStringView <__CharType>::containsAllOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (!characters.contains (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAllOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return containsAllOf (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAllOf (
    __BaseStringView const& string
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (!string.contains (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptionalInline auto __BaseStringView <__CharType>::containsAnyNotOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (!characters.contains (_pData [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAnyNotOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return containsAnyNotOf (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAnyNotOf (
    __BaseStringView const& string
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (!string.contains (_pData [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptionalInline auto __BaseStringView <__CharType>::containsAllNotOf (
    __CollectionType <ElementType> const& characters
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++index) {
    if (characters.contains (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAllNotOf (
    __ConvertibleType&& string
) const noexcept -> bool {
  return containsAllNotOf (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::containsAllNotOf (
    __BaseStringView const& string
) const noexcept -> bool {
  for (Size index = 0u; index < length(); ++ index) {
    if (string.contains (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::find (
    Size                      maxCount,
    ElementType               character,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  Size found = 0u;
  for (Size index = 0u; index < _length && found < maxCount; ++index) {
    if (_pData [index] == character) {
      storeIn.insert (static_cast <Index> (index));
      ++found;
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::find (
    Size        maxCount,
    ElementType character
) const noexcept -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return find (maxCount, character, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findFirst (
    ElementType character
) const noexcept -> Index {
  for (Size index = 0u; index < _length; ++index) {
    if (_pData [index] == character) {
      return static_cast <Index> (index);
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findLast (
    ElementType character
) const noexcept -> Index {
  for (Index index = static_cast <Index> (_length) - 1; index >= 0; --index) {
    if (_pData [index] == character ) {
      return index;
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::findAll (
    ElementType               character,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  for (Size index = 0u; index < _length; ++index) {
    if (_pData [index] == character) {
      storeIn.insert ( static_cast <Index> (index) );
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findAll (
    ElementType character
) const noexcept -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAll (character, indices);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::find (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return find (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::find (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return find (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::findFirst (
    __ConvertibleType&& string
) const noexcept(false) -> Index {
  return findFirst (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::findLast (
    __ConvertibleType&& string
) const noexcept(false) -> Index {
  return findLast (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAll (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return findAll (__BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAll (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAll (__BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findOf (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return findOf (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findOf (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findOf (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findFirstOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return findFirstOf (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findLastOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return findLastOf (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAllOf (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return findAllOf (__BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAllOf (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAllOf (__BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findNotOf (
    Size                      maxCount,
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return findNotOf (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findNotOf (
    Size                maxCount,
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findNotOf (maxCount, __BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findFirstNotOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return findFirstNotOf (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findLastNotOf (
    __ConvertibleType&& string
) const noexcept -> Index {
  return findLastNotOf (__BaseStringView (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAllNotOf (
    __ConvertibleType&&       string,
    __CollectionType <Index>& storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return findAllNotOf (__BaseStringView (std::forward <__ConvertibleType>(string)), storeIn);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::findAllNotOf (
    __ConvertibleType&& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAllNotOf (__BaseStringView (std::forward <__ConvertibleType>(string)), indices);
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::find (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return StringUtils <__CharType>::find (_pData, _length, string.cStr(), string.length(), maxCount, storeIn);
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::find (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return find (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::findFirst (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> Index {
  return StringUtils <__CharType>::findFirst (_pData, _length, string.cStr(), string.length());
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView <__CharType>::findLast (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> Index {
  return StringUtils <__CharType>::findLast (_pData, _length, string.cStr(), string.length());
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findAll (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  return StringUtils <__CharType>::findAll (_pData, _length, string.cStr(), string.length(), storeIn);
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findAll (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAll (string, indices);
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  Size found = 0u;
  for (Size index = 0u; index < length() && found < maxCount; ++index) {
    if (string.contains (_pData [index])) {
      storeIn.insert (static_cast <Index> (index));
      ++found;
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findOf (
    Size                                 maxCount,
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findOf (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findFirstOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  for (Size index = 0u; index < length(); ++index) {
    if (string.contains (_pData [index])) {
      return static_cast <Index> (index);
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findLastOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  for (Index index = static_cast <Index> (length()) - 1; index >= 0; --index) {
    if (string.contains (_pData [index])) {
      return static_cast <Index> (index);
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::findAllOf (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  for (Size index = 0u; index < length(); ++index) {
    if (string.contains (_pData [index])) {
      storeIn.insert (static_cast <Index> (index));
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findAllOf (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAllOf (string, indices);
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::findNotOf (
    Size                                  maxCount,
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  Size found = 0u;
  for (Size index = 0u; index < length() && found < maxCount; ++index) {
    if (!string.contains (_pData [index])) {
      storeIn.insert (static_cast <Index> (index));
      ++found;
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findNotOf (
    Size                                 maxCount,
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findNotOf (maxCount, string, indices);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findFirstNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  for (Size index = 0u; index < length(); ++index) {
    if (!string.contains (_pData [index])) {
      return static_cast <Index> (index);
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::findLastNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept -> Index {
  for (Index index = static_cast <Index> (length()) - 1; index >= 0; --index) {
    if (!string.contains (_pData [index])) {
      return static_cast <Index> (index);
    }
  }

  return __BaseStringView::invalidIndex;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::findAllNotOf (
    __BaseStringView <__CharType> const&  string,
    __CollectionType <Index>&             storeIn
) const noexcept(false) -> __CollectionType <Index>& {
  for (Size index = 0u; index < length(); ++index) {
    if (!string.contains (_pData [index])) {
      storeIn.insert (static_cast <Index> (index));
    }
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::findAllNotOf (
    __BaseStringView <__CharType> const& string
) const noexcept(false) -> __CollectionType <Index> {
  __CollectionType <Index> indices;
  return findAllNotOf (string, indices);
}


template <typename __CharType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::split (
    ElementType       separator,
    __CollectionType& storeIn,
    Size              maxCount
) const noexcept(false) -> __CollectionType& {
  Index splitIndex = 0;
  if (empty()) {
    return storeIn;
  }

  Index   currentSegmentOffset    = 0;
  Size    currentSegmentLength    = 0u;

  for (Index index = 0u; index < static_cast <Index> (length()); ++index) {
    if (_pData [index] != separator || splitIndex >= static_cast <Index> (maxCount) - 1) {
      ++currentSegmentLength;
    } else {

      if (currentSegmentLength == 0u) {
        continue;
      }

      ++splitIndex;
      storeIn.insert (__BaseString <__CharType> (_pData + currentSegmentOffset, currentSegmentLength));
      currentSegmentLength = 0u;
      currentSegmentOffset = index + 1;
    }
  }

  if (currentSegmentLength != 0u) {
    storeIn.insert (__BaseString <__CharType> (_pData + currentSegmentOffset, currentSegmentLength));
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::split (
    ElementType separator,
    Size        maxCount
) const noexcept(false) -> __CollectionType <__BaseString <__CharType> > {
  __CollectionType <__BaseString <__CharType>> tokens;
  return split (separator, tokens, maxCount);
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::split (
    __ConvertibleType&& separators,
    __CollectionType&   storeIn,
    Size                maxCount
) const noexcept(false) -> __CollectionType& {
  return split (__BaseStringView (std::forward <__ConvertibleType> (separators)), storeIn, maxCount);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::split (
    __ConvertibleType&& separators,
    Size                maxCount
) const noexcept(false) -> __CollectionType <__BaseString <__CharType> > {
  __CollectionType <__BaseString <__CharType>> tokens;
  return split (__BaseStringView (std::forward <__ConvertibleType> (separators)), tokens, maxCount);
}


template <typename __CharType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::split (
    __BaseStringView <__CharType> const&  separators,
    __CollectionType&                     storeIn,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType& {
  Index splitIndex = 0;
  if (empty()) {
    return storeIn;
  }

  Index   currentSegmentOffset    = 0;
  Size    currentSegmentLength    = 0u;

  for (Index index = 0u; index <static_cast <Index> (length()); ++index) {
    if (!separators.contains (_pData [index]) || splitIndex >= static_cast <Index> (maxCount) - 1) {
      ++currentSegmentLength;
    } else {
      if (currentSegmentLength == 0u) {
        currentSegmentOffset = index + 1;
        continue;
      }

      ++splitIndex;
      storeIn.insert (__BaseString <__CharType> (_pData + currentSegmentOffset, currentSegmentLength));
      currentSegmentLength = 0u;
      currentSegmentOffset = index + 1;
    }
  }

  if (currentSegmentLength != 0u) {
    storeIn.insert (__BaseString <__CharType> (_pData + currentSegmentOffset, currentSegmentLength));
  }

  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::split (
    __BaseStringView <__CharType> const& separators,
    Size                                 maxCount
) const noexcept(false) -> __CollectionType <__BaseString <__CharType> > {
  __CollectionType <__BaseString <__CharType> > tokens;
  return split (separators, tokens, maxCount);
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_OptimalInline auto __BaseStringView <__CharType>::splitByString (
    __ConvertibleType&& separator,
    __CollectionType&   storeIn,
    Size                maxCount
) const noexcept(false) -> __CollectionType& {
  return splitByString (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (separator)), storeIn, maxCount);
}


template <typename __CharType>                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    template <typename...> class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    typename                     __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_MaybeUnused __CDS_OptimalInline auto __BaseStringView <__CharType>::splitByString (
    __ConvertibleType&& separator,
    Size                maxCount
) const noexcept(false) -> __CollectionType <__BaseString <__CharType>> {
  __CollectionType <__BaseString <__CharType>> list;
  return splitByString (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (separator)), list, maxCount);
}


template <typename __CharType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::splitByString (
    __BaseStringView <__CharType> const&  separator,
    __CollectionType&                     storeIn,
    Size                                  maxCount
) const noexcept(false) -> __CollectionType& {
  using __Alloc = __allocation::__PrimitiveAlloc <Index>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  if (separator.empty()) {
    return storeIn;
  }

  auto separatorPredictiveCount = count ([& separator](char character) noexcept -> bool {
    return character == separator[0];
  });

  auto pOccurrences = __Alloc::__alloc (separatorPredictiveCount);
  auto actualSeparatorCount = StringUtils <__CharType>::findAll (
      _pData, _length, separator._pData, separator._length, 
      pOccurrences, separatorPredictiveCount
  );

  Size tokenOffset        = 0u;
  Size addedTokenCount    = 0u;
  for (Size currentSeparatorIndex = 0u; currentSeparatorIndex < actualSeparatorCount; ++currentSeparatorIndex) {
    if (tokenOffset < pOccurrences [currentSeparatorIndex]) {
      if (addedTokenCount < maxCount) {
        ++addedTokenCount;
        storeIn.insert (__BaseString <__CharType> (_pData + tokenOffset, static_cast <Size> (pOccurrences [currentSeparatorIndex])));
      } else {
        break;
      }

      while (
          currentSeparatorIndex < actualSeparatorCount &&
          pOccurrences [currentSeparatorIndex] + separator._length <= pOccurrences [currentSeparatorIndex + 1]
      ) {
        currentSeparatorIndex++;
        tokenOffset = pOccurrences [currentSeparatorIndex] + separator._length;
      }
    }
  }

  __Alloc::__free (pOccurrences);
  return storeIn;
}


template <typename __CharType>                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_MaybeUnused auto __BaseStringView <__CharType>::splitByString (
    __BaseStringView <__CharType>   const&  separator,
    Size                                    maxCount
) const noexcept(false) -> __CollectionType <__BaseString <__CharType>> {
  __CollectionType <__BaseString <__CharType>> tokens;
  return splitByString (separator, tokens, maxCount);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprOverride auto __BaseStringView <__CharType>::hash () const noexcept -> Size {
  Size currentExponent = 1u;
  Size finalHash       = 0u;

  if (empty()) {
    return 0u;
  }

  for (Size index = _length - 1u; index > 0u; --index) {
    finalHash += static_cast <Size> (_pData [index]) * currentExponent;
    currentExponent *= 31u;
  }

  return finalHash + _pData [0] * currentExponent;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::toString () const noexcept(false) ->__BaseString <__CharType> {
  return __BaseString <__CharType> (_pData, _length);
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::startsWith (
    ElementType character
) const noexcept -> bool {
  return !empty() && _pData [0] == character;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <
    typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>
> __CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::startsWith (
    __ConvertibleType&& string
) const noexcept -> bool {
  return startsWith (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::startsWith (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  Size offset = 0u;
  for (auto minLength = minOf (_length, string._length); offset < minLength; ++offset) {
    if (_pData [offset] != string._pData [offset]) {
      return false;
    }
  }

  return offset == string._length;
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __BaseStringView <__CharType>::endsWith (
    ElementType character
) const noexcept -> bool {
  return !empty() && _pData [_length - 1u] == character;
}


template <typename __CharType>                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value>>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::endsWith (
    __ConvertibleType&& string
) const noexcept -> bool {
  return endsWith (__BaseStringView <__CharType> (std::forward <__ConvertibleType> (string)));
}


template <typename __CharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_cpplang_ConstexprConditioned auto __BaseStringView <__CharType>::endsWith (
    __BaseStringView <__CharType> const& string
) const noexcept -> bool {
  Size offset = 0u;
  for (auto minLength = minOf (_length, string._length); offset < minLength; ++offset) {
    if (_pData [_length - offset - 1u] != string._pData [string._length - offset - 1u]) {
      return false;
    }
  }

  return offset == string._length;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Action>      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::forEach (
    __Action const& action
) const noexcept (noexcept(action(meta::valueOf<ElementType>()))) -> void {
  for (Size index = 0u; index < _length; ++index) {
    action (_pData [index]);
  }
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::some (
    Size               count,
    __Predicate const& predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return trueCount == count;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::atLeast (
    Size                count,
    __Predicate const&  predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      ++trueCount;
    }

    if (trueCount >= count) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::atMost (
    Size                count,
    __Predicate const&  predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      ++trueCount;
    }

    if (trueCount > count) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::moreThan (
    Size                count,
    __Predicate const&  predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  return atLeast (count + 1u, predicate);
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __BaseStringView <__CharType>::fewerThan (
    Size                count,
    __Predicate const&  predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  return atMost (count - 1u, predicate);
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::count (
    __Predicate const& predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> Size {
  Size trueCount = 0u;
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      ++trueCount;
    }
  }

  return trueCount;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::any (
    __Predicate const& predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      return true;
    }
  }

  return false;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::all (
    __Predicate const& predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (!predicate (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __BaseStringView <__CharType>::none (
    __Predicate const& predicate
) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool {
  for (Size index = 0u; index < _length; ++index) {
    if (predicate (_pData [index])) {
      return false;
    }
  }

  return true;
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator << (
    std::ostream&                         out,
    __BaseStringView <__FCharType> const& obj
) noexcept -> std::ostream & {
  out.write(obj._pData, obj._length);
}


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto operator << (
    std::wostream&                        out,
    __BaseStringView <__FCharType> const& obj
) noexcept -> std::wostream & {
  out.write(obj._pData, obj._length);
}

} // namespace __impl 
} // namespace __hidden 
} // namespace cds 


#endif // __CDS_BASE_STRING_VIEW_IMPL_HPP__ 
