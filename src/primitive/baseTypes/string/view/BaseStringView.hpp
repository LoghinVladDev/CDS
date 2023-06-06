//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_BASE_STRING_VIEW_HPP__    // NOLINT(llvm-header-guard)
#define __CDS_BASE_STRING_VIEW_HPP__    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "../../../../shared/sequence/Predeclaration.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __CharType>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __BaseStringView {            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
public:
  //
  // \brief Represents an element in the string
  //
  using ElementType = __CharType;

  using ConstIterator         = ForwardAddressIterator <__CharType const>;
  using ConstReverseIterator  = BackwardAddressIterator <__CharType const>;
  static Index const  invalidIndex;
  
  constexpr __BaseStringView () noexcept = default;
  constexpr __BaseStringView (__BaseStringView const& string) noexcept = default;
  constexpr __BaseStringView (__BaseStringView&& string) noexcept:
      _pData (cds::exchange (string._pData, nullptr)), _length (cds::exchange (string._length, 0u)) {

  }

  __CDS_Implicit constexpr __BaseStringView (__BaseString <__CharType> const& string) noexcept;  // NOLINT(google-explicit-constructor)
  __CDS_Implicit constexpr __BaseStringView (std::basic_string <__CharType> const& string) noexcept;   // NOLINT(google-explicit-constructor)

  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit constexpr __BaseStringView (ElementType const* pString) noexcept; // NOLINT(google-explicit-constructor)

  constexpr __BaseStringView (ElementType const* pString, Size length) noexcept;
  ~__BaseStringView() noexcept = default;

  __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;    // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;      // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;   // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;     // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto rbegin () const noexcept -> ConstReverseIterator;    // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto rend () const noexcept -> ConstReverseIterator;      // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto crbegin () const noexcept -> ConstReverseIterator;   // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto crend () const noexcept -> ConstReverseIterator;     // NOLINT(modernize-use-nodiscard)
  
  __CDS_NoDiscard constexpr auto length () const noexcept -> Size;    // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto size () const noexcept -> Size;      // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;     // NOLINT(modernize-use-nodiscard)
  __CDS_cpplang_NonConstConstexprMemberFunction auto clear () noexcept -> void;

  template <typename __NumericType, cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value> = 0> 
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __NumericType index
  ) const noexcept (false) -> ElementType;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto at (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Index index
  ) const noexcept (false) -> ElementType;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Index index
  ) const noexcept (false) -> ElementType;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementType; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementType;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  
  __CDS_NoDiscard __CDS_MaybeUnused auto toStdString () const noexcept -> std::basic_string <__CharType>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const*;               // NOLINT(modernize-use-nodiscard)
  __CDS_NoDiscard constexpr auto data () const noexcept -> ElementType const*;               // NOLINT(modernize-use-nodiscard)
  __CDS_Implicit operator std::basic_string <__CharType> () const noexcept;   // NOLINT(google-explicit-constructor)
  __CDS_Implicit constexpr operator ElementType const* () const noexcept;        // NOLINT(google-explicit-constructor)
  
  __CDS_NoDiscard auto substr (Index from, Index until = -1) const noexcept -> __BaseString <__CharType>;
  __CDS_NoDiscard auto operator () (Index from, Index to = -1) const noexcept -> __BaseString <__CharType>;
  
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      __BaseString <__CharType> const& string
  ) noexcept -> __BaseStringView&;
  
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      __BaseStringView const& string
  ) noexcept -> __BaseStringView&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      __BaseStringView&& string
  ) noexcept -> __BaseStringView&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      std::basic_string <__CharType> const& string
  ) noexcept -> __BaseStringView&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      ElementType const* pString
  ) noexcept -> __BaseStringView&;
  
  __CDS_NoDiscard __CDS_cpplang_DynamicCastConstexpr auto equals (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      Object const& object
  ) const noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;
#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView const& string
  ) const noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;

#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;


  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;
#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;
#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;
#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> bool;
#endif

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;
  
  auto operator + (                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView const& string
  ) const noexcept -> __BaseString <__CharType>;

  auto operator + (                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      std::basic_string <__CharType> const& string
  ) const noexcept -> __BaseString <__CharType>;

  auto operator + (                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType const* pString
  ) const noexcept -> __BaseString <__CharType>;

#if defined(CDS_QT)
  auto operator + (                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      QString const& string
  ) const noexcept -> __BaseString <__CharType>;
#endif

  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (
      ElementType character
  ) const noexcept -> __BaseString <__CharType>;

  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (
      __NumericType value
  ) const noexcept -> __BaseString <__CharType>;

  auto operator + (
      bool value
  ) const noexcept -> __BaseString <__CharType>;

  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (
      __FloatingPointType value
  ) const noexcept -> __BaseString <__CharType>;
  
  auto operator * (
      int repeatCount
  ) const noexcept -> __BaseString <__CharType>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto containsAnyOf (
      __CollectionType <ElementType> const& characters
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf (                                                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto containsAllOf (
      __CollectionType < ElementType > const& string
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf (                                                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto containsAnyNotOf (
      __CollectionType < ElementType > const& string
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (                                                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto containsAllNotOf (
      __CollectionType < ElementType > const& string
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (                                                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
  
  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto find (
      Size                      maxCount,
      ElementType               character,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto find (
      Size        maxCount,
      ElementType character
  ) const noexcept -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      ElementType character
  ) const noexcept -> Index;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAll (
      ElementType               character,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAll (
      ElementType character
  ) const noexcept -> __CollectionType <Index>;


  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto find (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto find (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (                                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAll (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAll (
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;
  
  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findOf (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findOf (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (                                                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAllOf (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;
  
  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAllOf (
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;


  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findNotOf (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findNotOf (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (                                                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> Index;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAllNotOf (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAllNotOf (
      __ConvertibleType&& string
  ) const noexcept -> __CollectionType <Index>;


  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto find (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto find (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string
  ) const noexcept -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAll (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAll (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> __CollectionType <Index>;


  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findOf (
      Size                                    maxCount,
      __BaseStringView <__CharType> const& string
  ) const noexcept -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAllOf (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAllOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> __CollectionType <Index>;


  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findNotOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findNotOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string
  ) const noexcept -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAllNotOf (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept -> __CollectionType <Index>&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAllNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> __CollectionType <Index>;
  
  
  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto split (
      ElementType       separator,
      __CollectionType& storeIn,
      Size              maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto split (
      ElementType separator,
      Size        maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType <__BaseString <__CharType>>;

  template <
      typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto split (
      __ConvertibleType&& separators,
      __CollectionType&   storeIn,
      Size                maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto split (
      __ConvertibleType&& separators,
      Size                maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType <__BaseString <__CharType>>;

  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto split (
      __BaseStringView <__CharType> const&  separators,
      __CollectionType&                     storeIn,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto split (
      __BaseStringView <__CharType> const&  separators,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType <__BaseString <__CharType>>;

  template <
      typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto splitByString (
      __ConvertibleType&& separators,
      __CollectionType&   storeIn,
      Size                maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType&;

  template <
      template <typename...> class  __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                      __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& separator,
      Size                maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType <__BaseString <__CharType>>;

  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto splitByString (
      __BaseStringView <__CharType> const&  separator,
      __CollectionType&                     storeIn,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType&;

  template <template <typename...>class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const&  separator,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept -> __CollectionType <__BaseString <__CharType>>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
  __CDS_NoDiscard auto toString () const noexcept -> __BaseString <__CharType>;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)
  
  __CDS_NoDiscard constexpr auto startsWith (
      ElementType character
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
  
  __CDS_NoDiscard constexpr auto endsWith (
      ElementType character
  ) const noexcept -> bool;

  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (                                                                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
  
  template <typename __Action>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto forEach (
      __Action const& action
  ) const noexcept (noexcept(action(meta::valueOf<ElementType>()))) -> void;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto some (
      Size                count,
      __Predicate const&  predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto atLeast (
      Size                count,
      __Predicate const&  predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto atMost (
      Size                count,
      __Predicate const&  predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto moreThan (
      Size                count,
      __Predicate const&  predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto fewerThan (
      Size                count,
      __Predicate const&  predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto count (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> Size;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto any (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto all (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue <ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto none (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept(predicate(meta::valueOf<ElementType>()))) -> bool;
  
  auto sequence () const& noexcept -> Sequence <__BaseStringView <__CharType> const>;
  auto sequence () const&& noexcept -> Sequence <__BaseStringView <__CharType> const>;

private:
  ElementType const*  _pData  {nullptr};
  Size                _length {0ULL};

  template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto operator << (
      std::wostream&                        out,
      __BaseStringView <__FCharType> const& obj
  ) noexcept -> std::wostream &;

  template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto operator << (
      std::ostream&                         out,
      __BaseStringView <__FCharType> const& obj
  ) noexcept -> std::ostream &;
};


template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType const*                    pLeftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> bool;

template <typename __FCharType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    std::basic_string <__FCharType> const&  leftString,
    __BaseStringView <__FCharType> const&   rightString
) noexcept -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FCharType                         const* leftString,
    __BaseStringView <__FCharType>    const& rightString
) noexcept -> __BaseString <__FCharType>;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    QString const&                        leftString,
    __BaseStringView <__FCharType> const& rightString
) noexcept -> __BaseString <__FCharType>;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FCharType                           character,
    __BaseStringView <__FCharType> const& string
) noexcept -> __BaseString <__FCharType>;

template <typename __FCharType, typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__FCharType, __NumericType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __NumericType                         value,
    __BaseStringView <__FCharType> const& string
) noexcept -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    bool                                  value,
    __BaseStringView <__FCharType> const& string
) noexcept -> __BaseString <__FCharType>;

template < typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FloatingPointType                   value,
    __BaseStringView <__FCharType> const& string
) noexcept -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator * (
    int                                   repeatCount,
    __BaseStringView <__FCharType> const& string
) noexcept -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::wostream&                        out,
    __BaseStringView <__FCharType> const& obj
) noexcept -> std::wostream &;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::ostream&                         out,
    __BaseStringView <__FCharType> const& obj
) noexcept -> std::ostream &;

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_BASE_STRING_VIEW_HPP__
