//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_STRING_BASE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_STRING_BASE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/meta/TypeTraits>

#include "../../../shared/impl/generalPredicates.hpp"   // NOLINT(llvm-include-order)
#include "../../../shared/impl/arithmetic.hpp"
#include "../../../shared/sequence/Predeclaration.hpp"

#include <CDS/Limits>                                   // NOLINT(llvm-include-order)
#include "StringUtils.hpp"
#include <cstring>
#include <sstream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

class OutOfBoundsException;

namespace __hidden {                  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __CharType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __BaseStringView;               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __CharType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __BaseString : public Object {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \brief Represents an element in the string
  using ElementType = __CharType;

  using Iterator              = cds::ForwardAddressIterator <__CharType>;
  using ConstIterator         = cds::ForwardAddressIterator <__CharType const>;
  using ReverseIterator       = cds::BackwardAddressIterator <__CharType>;
  using ConstReverseIterator  = cds::BackwardAddressIterator <__CharType const>;
  
  static Index const  invalidIndex;

  static __BaseStringView <__CharType> const whitespace;
  static __BaseStringView <__CharType> const digits;
  static __BaseStringView <__CharType> const lowercaseAlphabet;
  static __BaseStringView <__CharType> const uppercaseAlphabet;
  static __BaseStringView <__CharType> const vowels;
  static __BaseStringView <__CharType> const consonants;
  
  constexpr __BaseString () noexcept = default;
  __BaseString (__BaseString const& string) noexcept(false);

  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __CDS_Implicit __BaseString (__BaseString <__OtherCharType> const& string) noexcept(false);  // NOLINT(*-explicit-*)

  constexpr __BaseString (__BaseString&& string) noexcept;
  __CDS_Implicit __BaseString (__BaseStringView <__CharType> const& string) noexcept(false); // NOLINT(*-explicit-*)
 
  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __CDS_Implicit __BaseString (__BaseStringView <__OtherCharType> const& string) noexcept(false);  // NOLINT(*-explicit-*)
 
  __CDS_Implicit __BaseString (ElementType const* pString) noexcept(false);  // NOLINT(*-explicit-*)
 
  __CDS_Implicit __BaseString (std::basic_string <__CharType> const& string) noexcept(false);  // NOLINT(*-explicit-*)

  __BaseString (ElementType const* pString, Size length) noexcept(false);
 
  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __CDS_Implicit __BaseString (__OtherCharType const* pString) noexcept(false);  // NOLINT(*-explicit-*)
 
  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __BaseString (__OtherCharType const* pString, Size length) noexcept(false);

  __CDS_Implicit __BaseString (Object const& object) noexcept(false);  // NOLINT(*-explicit-*)
 
  __BaseString (Size length, ElementType fillCharacter) noexcept(false);
 
  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __BaseString (Size length, __OtherCharType fillCharacter) noexcept(false);
 
  template <
      typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsIterator <__IteratorType>::value> = 0
  > __BaseString (__IteratorType const& begin, __IteratorType const& end) noexcept(false);
 
  __CDS_Implicit __BaseString (std::initializer_list <ElementType> const& initializerList) noexcept(false);
 
  template <
      typename __OtherCharType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsStringCharType <__OtherCharType>::value && !meta::IsSame <__OtherCharType, __CharType>::value> = 0
  > __CDS_Implicit __BaseString (std::initializer_list <__OtherCharType> const& initializerList) noexcept(false);

#if defined(CDS_QT)
  __BaseString (QString const& string) noexcept(false);
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit __BaseString (ElementType value) noexcept(false); // NOLINT(*-explicit-*)
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit __BaseString (__NumericType value) noexcept(false); // NOLINT(*-explicit-*)
 
  __CDS_Implicit __BaseString (bool value) noexcept(false);  // NOLINT(*-explicit-*)
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Implicit __BaseString (__FloatingPointType value) noexcept(false); // NOLINT(*-explicit-*)
 
  template <typename __AddressType, meta::EnableIf <!meta::IsStringCharType <__AddressType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit __BaseString (__AddressType const* address) noexcept(false);

  ~__BaseString () noexcept override;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () noexcept -> Iterator; 
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () noexcept -> Iterator; 
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () const noexcept -> ConstIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () const noexcept -> ConstIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cbegin () const noexcept -> ConstIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cend () const noexcept -> ConstIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () noexcept -> ReverseIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () noexcept -> ReverseIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () const noexcept -> ConstReverseIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () const noexcept -> ConstReverseIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crbegin () const noexcept -> ConstReverseIterator;
  __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crend () const noexcept -> ConstReverseIterator;
  
  __CDS_NoDiscard constexpr auto length () const noexcept -> Size;
  __CDS_NoDiscard constexpr auto size () const noexcept -> Size;
  __CDS_NoDiscard constexpr auto capacity () const noexcept -> Size;
  
  auto resize (Size size) noexcept(false) -> void;
  auto reserve (Size size) noexcept(false) -> void;
  auto shrink (Size size = limits::U64_MAX) noexcept(false) -> void;

  auto clear () noexcept -> void;
  __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

  template <
      typename __NumericType,
      cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value> = 0
  > __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator [] (
      __NumericType index
  ) noexcept (false) -> ElementType&;

  template <
      typename __NumericType,
      cds::meta::EnableIf <cds::meta::IsIntegral <__NumericType>::value> = 0
  > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (
      __NumericType index
  ) const noexcept (false) -> ElementType;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto at (
      Index index
  ) noexcept (false) -> ElementType&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto at (
      Index index
  ) const noexcept (false) -> ElementType;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto get (
      Index index
  ) noexcept (false) -> ElementType&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (
      Index index
  ) const noexcept (false) -> ElementType;

  __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementType&;
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementType;
  __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementType&;
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementType;
  
  __CDS_NoDiscard auto toStdString () const noexcept(false) -> std::basic_string <ElementType>;
  __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const*;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> ElementType*;
  
  __CDS_Implicit operator std::basic_string <__CharType> () const noexcept(false); // NOLINT(*-explicit-*)
  __CDS_Explicit constexpr operator ElementType const* () const noexcept; // NOLINT(*-explicit-*)
  __CDS_Explicit __CDS_cpplang_NonConstConstexprMemberFunction operator ElementType* () noexcept; // NOLINT(*-explicit-*) 

  __CDS_NoDiscard auto substr (Index from, Index until = -1) const noexcept(false) -> __BaseString;
  __CDS_NoDiscard auto operator () (Index from, Index until = -1) const noexcept(false) -> __BaseString;
 
  template <
      typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto operator = (__ConvertibleType&& string) noexcept(false) -> __BaseString&;

  auto operator = (__BaseString const& string) noexcept(false) -> __BaseString&;
  auto operator = (__BaseString&& string) noexcept -> __BaseString&;
  auto operator = (__BaseStringView <ElementType> const& string) noexcept(false) -> __BaseString&;

  template <typename __TCharType = ElementType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (ElementType character) noexcept(false) -> __BaseString&;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__NumericType value) noexcept(false) -> __BaseString&;

  auto operator = (bool value) noexcept(false) -> __BaseString&;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator = (__FloatingPointType value) noexcept(false) -> __BaseString&;
  
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (Object const& object) const noexcept -> bool override;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  //* cpp-20 non-ambiguity rule 
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      __BaseString const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  //* cpp-20 non-ambiguity rule 
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      __BaseString const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

#if defined(CDS_QT)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
      QString const& string
  ) const noexcept -> bool;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
      ElementType character
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator += (__ConvertibleType&& string) noexcept(false) -> __BaseString&;

  auto operator += (__BaseString&& string) noexcept(false) -> __BaseString&;
  auto operator += (__BaseStringView <__CharType> const& string) noexcept(false) -> __BaseString&;

#if defined(CDS_QT)
  auto operator += (QString const& string) noexcept(false) -> __BaseString&;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator += (ElementType character) noexcept(false) -> __BaseString&;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator += (__NumericType value) noexcept(false) -> __BaseString&;

  auto operator += (bool value) noexcept(false) -> __BaseString&;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator += (__FloatingPointType value) noexcept(false) -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__ConvertibleType&& string) const& noexcept(false) -> __BaseString;

  auto operator + (__BaseString&& string) const& noexcept(false) -> __BaseString;
  auto operator + (__BaseStringView <__CharType> const& string) const& noexcept(false) -> __BaseString;

#if defined(CDS_QT)
  auto operator + (QString const& string) const& noexcept(false) -> __BaseString;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (ElementType character) const& noexcept(false) -> __BaseString;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__NumericType value) const& noexcept(false) -> __BaseString;

  auto operator + (bool value) const& noexcept(false) -> __BaseString;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__FloatingPointType value) const& noexcept(false) -> __BaseString;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__ConvertibleType&& string)&& noexcept(false) -> __BaseString;

  auto operator + (__BaseString&& string)&& noexcept(false) -> __BaseString;

  auto operator + (__BaseStringView <__CharType> const& string)&& noexcept(false) -> __BaseString;

#if defined(CDS_QT)
  auto operator + (QString const& string)&& noexcept(false) -> __BaseString;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (ElementType character)&& noexcept(false) -> __BaseString;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__NumericType value)&& noexcept(false) -> __BaseString;

  auto operator + (bool value)&& noexcept(false) -> __BaseString;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto operator + (__FloatingPointType value)&& noexcept(false) -> __BaseString;

  auto operator * (int repeatCount) const& noexcept(false) -> __BaseString;
  auto operator * (int repeatCount)&& noexcept(false) -> __BaseString;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto append (__ConvertibleType&& string) noexcept(false) -> __BaseString&;

  auto append (__BaseString&& string) noexcept(false) -> __BaseString&;
  auto append (__BaseStringView <__CharType> const& string) noexcept(false) -> __BaseString&;

#if defined(CDS_QT) 
  auto append (QString const& string) noexcept(false) -> __BaseString&;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto append (ElementType character) noexcept(false) -> __BaseString&;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto append (__NumericType value) noexcept(false) -> __BaseString&;

  auto append (bool value) noexcept(false) -> __BaseString&;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto append (__FloatingPointType value) noexcept(false) -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto prepend (__ConvertibleType&& string) noexcept(false) -> __BaseString&;

  auto prepend (__BaseString&& string) noexcept(false) -> __BaseString&;

  auto prepend (__BaseStringView <__CharType> const& string) noexcept(false) -> __BaseString&;

#if defined(CDS_QT)
  auto prepend (QString const& string) noexcept(false) -> __BaseString&;
#endif
 
  template <typename __TCharType = __CharType, meta::EnableIf <meta::IsStringCharType <__TCharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto prepend (ElementType character) noexcept(false) -> __BaseString&;
 
  template <typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__CharType, __NumericType>::value> = 0>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto prepend (__NumericType value) noexcept(false) -> __BaseString&;

  auto prepend (bool value) noexcept(false) -> __BaseString&;
 
  template <typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto prepend (__FloatingPointType value) noexcept(false) -> __BaseString&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (ElementType character) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
      __ConvertibleType&& string
  ) const noexcept(false) -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> bool;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
      __CollectionType <ElementType> const& characters
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
      __CollectionType <ElementType> const& characters
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
      __CollectionType <ElementType> const& characters
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
      __CollectionType <ElementType> const& characters
  ) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto find (
      Size                      maxCount,
      ElementType               character,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto find (
      Size        maxCount,
      ElementType character
  ) const noexcept(false) -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst (
      ElementType character
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast (
      ElementType character
  ) const noexcept -> Index;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAll (
      ElementType               character,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAll (
      ElementType character
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto find (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto find (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
      __ConvertibleType&& string
  ) const noexcept(false) -> Index;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
      __ConvertibleType&& string
  ) const noexcept(false) -> Index;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAll (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAll (
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findOf (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findOf (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
      __ConvertibleType&& string
  ) const noexcept -> Index;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
      __ConvertibleType&& string
  ) const noexcept -> Index;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAllOf (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAllOf (
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findNotOf (
      Size                      maxCount,
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findNotOf (
      Size                maxCount,
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
      __ConvertibleType&& string
  ) const noexcept -> Index;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
      __ConvertibleType&& string
  ) const noexcept -> Index;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto findAllNotOf (
      __ConvertibleType&&       string,
      __CollectionType <Index>& storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto findAllNotOf (
      __ConvertibleType&& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto find (
      Size                                   maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto find (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string
  ) const noexcept(false) -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> Index;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAll (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAll (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string
  ) const noexcept(false) -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAllOf (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAllOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> __CollectionType <Index>;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findNotOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findNotOf (
      Size                                  maxCount,
      __BaseStringView <__CharType> const&  string
  ) const noexcept(false) -> __CollectionType <Index>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> Index;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAllNotOf (
      __BaseStringView <__CharType> const&  string,
      __CollectionType <Index>&             storeIn
  ) const noexcept(false) -> __CollectionType <Index>&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAllNotOf (
      __BaseStringView <__CharType> const& string
  ) const noexcept(false) -> __CollectionType <Index>;

  auto ltrim (ElementType character) noexcept -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto ltrim (__ConvertibleType&& characters) noexcept -> __BaseString&;

  auto ltrim (__BaseStringView <__CharType> const& characters = __BaseString::whitespace) noexcept -> __BaseString&;

#if defined(CDS_QT)
  auto ltrim (QString const& characters) noexcept -> __BaseString&;
#endif

  auto rtrim (ElementType character) noexcept -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto rtrim (__ConvertibleType&& characters) noexcept -> __BaseString&;

  auto rtrim (__BaseStringView <__CharType> const& characters = __BaseString::whitespace) noexcept -> __BaseString&;

#if defined(CDS_QT) 
  auto rtrim (QString const& characters) noexcept -> __BaseString&;
#endif

  auto trim (ElementType character) noexcept -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto trim (__ConvertibleType&& characters) noexcept -> __BaseString&;

  auto trim (__BaseStringView <__CharType> const& characters = __BaseString::whitespace) noexcept -> __BaseString&;

#if defined(CDS_QT) 
  auto trim (QString const& characters) noexcept -> __BaseString&;
#endif
  
  auto ljust (Size size, ElementType element = ' ') noexcept -> __BaseString&;
  auto rjust (Size size, ElementType element = ' ') noexcept -> __BaseString&;

  __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> __BaseString&;
  __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> __BaseString&;

  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto split (
      ElementType       separator,
      __CollectionType& storeIn,
      Size              maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto split (
      ElementType separator,
      Size        maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType <__BaseString>;
 
  template <
      typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > auto split (
      __ConvertibleType&& separators,
      __CollectionType&   storeIn,
      Size                maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard auto split (
      __ConvertibleType&& separators,
      Size                maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType <__BaseString>;

  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto split (
      __BaseStringView <__CharType> const&  separators,
      __CollectionType&                     storeIn,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto split (
      __BaseStringView <__CharType> const&  separators,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType <__BaseString>;
 
  template <
      typename __CollectionType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ConvertibleType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_MaybeUnused auto splitByString (
      __ConvertibleType&& separator,
      __CollectionType&   storeIn,
      Size                maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (
      __ConvertibleType&& separator,
      Size                maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType <__BaseString>;

  template <typename __CollectionType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_MaybeUnused auto splitByString (
      __BaseStringView <__CharType> const&  separators,
      __CollectionType&                     storeIn,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType&;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (
      __BaseStringView <__CharType> const&  separators,
      Size                                  maxCount = limits::U32_MAX
  ) const noexcept(false) -> __CollectionType <__BaseString>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;
  __CDS_NoDiscard auto toString () const noexcept(false) -> cds::String override;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto replace (Index from, Index until, __ConvertibleType&& inPlace) noexcept(false) -> __BaseString&;
  auto replace (Index from, Index until, __BaseStringView <__CharType> const& inPlace) noexcept(false) -> __BaseString&;
  __CDS_cpplang_NonConstConstexprMemberFunction auto reverse () noexcept -> __BaseString&;

  __CDS_NoDiscard constexpr auto startsWith (ElementType character) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_NoDiscard constexpr auto endsWith (ElementType character) const noexcept -> bool;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (
      __ConvertibleType&& string
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (
      __BaseStringView <__CharType> const& string
  ) const noexcept -> bool;

  __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
      ElementType character
  ) noexcept -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
      __ConvertibleType&& string
  ) noexcept -> __BaseString&;

  __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
      __BaseStringView <__CharType> const& string
  ) noexcept -> __BaseString&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
      ElementType character
  ) noexcept -> __BaseString&;
 
  template <typename __ConvertibleType, meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
      __ConvertibleType&& string
  ) noexcept -> __BaseString&;

  __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
      __BaseStringView <__CharType> const& string
  ) noexcept -> __BaseString&;
 
  template <
      template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                        __ConvertibleType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      meta::EnableIf <meta::IsConvertibleToBaseStringView <__ConvertibleType, __CharType>::value> = 0
  > __CDS_NoDiscard static auto join (
      __CollectionType <__BaseString> const&  tokens,
      __ConvertibleType&&                     delimiter
  ) noexcept(false) -> __BaseString;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard static auto join (
      __CollectionType <__BaseString> const&  tokens,
      __BaseStringView <__CharType> const&    delimiter
  ) noexcept(false) -> __BaseString;
 
  template <template <typename...> class __CollectionType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard static auto join (
      __CollectionType <__BaseString> const&  tokens,
      ElementType                             delimiter
  ) noexcept(false) -> __BaseString;
 
  template <typename __Action>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto forEach (
      __Action const& action
  ) const noexcept (noexcept(action(cds::meta::valueOf <ElementType>()))) -> void;
 
  template <typename __Action>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto forEach (
      __Action const& action
  ) noexcept (noexcept(action(cds::meta::referenceOf <ElementType>()))) -> void;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto some (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto some (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto atLeast (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto atLeast (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto atMost (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto atMost (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto moreThan (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto moreThan (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto fewerThan (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto fewerThan (
      Size               count,
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto count (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> Size;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto count (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> Size;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto any (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto any (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto all (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto all (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto none (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) const noexcept (noexcept (predicate (cds::meta::valueOf <ElementType>()))) -> bool;

  template <typename __Predicate = decltype (&predicates::alwaysTrue<ElementType>)> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto none (
      __Predicate const& predicate = &predicates::alwaysTrue <ElementType>
  ) noexcept (noexcept (predicate (cds::meta::referenceOf <ElementType>()))) -> bool;
 
  template <typename...__ArgumentTypes>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard static auto format (
      __CharType const*     pFormat,
      __ArgumentTypes&&...  arguments
  ) noexcept (false) -> __BaseString;
 
  template <typename...__ArgumentTypes>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard static auto f (
      __CharType const*     pFormat,
      __ArgumentTypes&&...  arguments
  ) noexcept (false) -> __BaseString;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <__BaseString>;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <__BaseString const>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <__BaseString>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <__BaseString const>;
  
#if defined(CDS_STRING_DEBUG)
  __CDS_NoDiscard auto diag () const noexcept -> __BaseString;
#endif

private:
  friend class __BaseStringView <__CharType>;
  ElementType*  _pBuffer  {nullptr};
  Size          _length   {0u};
  Size          _capacity {0u};

  static Size const   minCapacity;
};


template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator == (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator != (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool; 

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator < (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator > (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator <= (
    __FCharType                          character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept -> bool;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    QString const&                    leftString,
    __BaseString <__FCharType> const& rightString
) noexcept -> bool;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto operator >= (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept -> bool;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType> const&     rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __ConvertibleType&&               leftString,
    __BaseString <__FCharType> const& rightString
) noexcept(false) -> __BaseString <__FCharType>;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    QString                      const& leftString,
    __BaseString <__FCharType> const&   rightString
) noexcept(false) -> __BaseString <__FCharType>;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FCharType                       character,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__FCharType, __NumericType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __NumericType                     value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    bool                              value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FloatingPointType               value,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __BaseStringView <__FCharType> const& leftString,
    __BaseString <__FCharType>&&          rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __ConvertibleType, meta::EnableIf <meta::IsNonAmbiguousConvertibleToBaseStringView <__ConvertibleType, __FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __ConvertibleType&&           leftString,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

#if defined(CDS_QT)

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
friend auto operator + (
    QString const&                leftString,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

#endif

template <typename __FCharType, meta::EnableIf <meta::IsStringCharType <__FCharType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FCharType                   character,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __NumericType, meta::EnableIf <meta::IsIntegralToString <__FCharType, __NumericType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __NumericType                 value,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    bool                          value,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType, typename __FloatingPointType, meta::EnableIf <meta::IsFloatingPoint <__FloatingPointType>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator + (
    __FloatingPointType           value,
    __BaseString <__FCharType>&&  rightString
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator * (
    int                               repeatCount,
    __BaseString <__FCharType> const& string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator * (
    int                           repeatCount,
    __BaseString <__FCharType>&&  string
) noexcept(false) -> __BaseString <__FCharType>;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::ostream&                     out,
    __BaseString <__FCharType> const& obj
) noexcept -> std::ostream &;

template <typename __FCharType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto operator << (
    std::wostream&                    out,
    __BaseString <__FCharType> const& obj
) noexcept -> std::wostream &;

} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#include "view/BaseStringView.hpp"

#include "impl/BaseStringNonException.hpp"

#include "../../../shared/memory/PrimitiveAllocation.hpp"
#include <CDS/exception/OutOfBoundsException>
#include <CDS/exception/OutOfMemoryException>

#include "impl/StringUtilsImpl.hpp" // NOLINT(llvm-include-order)
#include "impl/BaseStringImpl.hpp"

#include "view/impl/BaseStringViewImpl.hpp"

#include "view/Literal.hpp"

#include "../../../shared/string/impl/StringSequence.hpp"
#include "../../../shared/string/view/impl/StringViewSequence.hpp"

#endif // __CDS_STRING_BASE_HPP__ 
