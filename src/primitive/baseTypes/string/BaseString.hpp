//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_STRING_BASE_HPP__
#define __CDS_STRING_BASE_HPP__

#include <CDS/meta/TypeTraits>

#include "../../../shared/impl/generalPredicates.hpp"
#include "../../../shared/impl/arithmetic.hpp"
#include "../../../shared/memory/PrimitiveAllocation.hpp"

#include <CDS/Limits>
#include "StringUtils.hpp"
#include <cstring>
#include <sstream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename C >
    class Sequence;

    class OutOfBoundsException;

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseStringView; // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseString : public Object { // NOLINT(bugprone-reserved-identifier)

            public:
                /**
                 * @brief Represents an element in the string
                 */
                using ElementType = __CharType;

            private:
                class AbstractIterator;

            private:
                class AbstractConstIterator;

            public:
                class Iterator;

            public:
                class ConstIterator;

            public:
                class ReverseIterator;

            public:
                class ConstReverseIterator;

            private:
                friend class __BaseStringView < __CharType >;


            private:
                ElementType       * _pBuffer        { nullptr };

            private:
                Size                _length         { 0ULL };

            private:
                Size                _capacity       { 0ULL };

            private:
                static Size const   minCapacity;

            public:
                static Index const  invalidIndex;

            public:
                static __BaseStringView < __CharType > const whitespace;

            public:
                static __BaseStringView < __CharType > const digits;

            public:
                static __BaseStringView < __CharType > const lowercaseAlphabet;

            public:
                static __BaseStringView < __CharType > const uppercaseAlphabet;

            public:
                static __BaseStringView < __CharType > const vowels;

            public:
                static __BaseStringView < __CharType > const consonants;

            public:
                constexpr __BaseString () noexcept = default;

            public:
                __BaseString (
                        __BaseString const & string
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __BaseString < __OtherCharType > const & string
                ) noexcept;

            public:
                constexpr __BaseString (
                        __BaseString && string
                ) noexcept;

            public:
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __BaseStringView < __CharType > const & string
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __BaseStringView < __OtherCharType > const & string
                ) noexcept;

            public:
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        ElementType const * pString
                ) noexcept;

            public:
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        std :: basic_string < __CharType > const & string
                ) noexcept;

            public:
                __BaseString (
                        ElementType const * pString,
                        Size                length
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __OtherCharType const * pString
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __BaseString (
                        __OtherCharType   const * pString,
                        Size                      length
                ) noexcept;

            public:
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        Object const & object
                ) noexcept;

            public:
                __BaseString (
                        Size        length,
                        ElementType fillCharacter
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __BaseString (
                        Size              length,
                        __OtherCharType   fillCharacter
                ) noexcept;

            public:
                template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __BaseString (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept;

            public:
                __CDS_Implicit __BaseString (
                        std :: initializer_list < ElementType > const & initializerList
                ) noexcept;

            public:
                template < typename __OtherCharType, meta :: EnableIf < meta :: isStringCharType < __OtherCharType > () && ! meta :: isSame < __OtherCharType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString (
                        std :: initializer_list < __OtherCharType > const & initializerList
                ) noexcept;

#if defined(CDS_QT)

            public:
                __BaseString (
                        QString const & string
                ) noexcept;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        ElementType value
                ) noexcept;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __NumericType value
                ) noexcept;

            public:
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        bool value
                ) noexcept;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Implicit __BaseString ( // NOLINT(google-explicit-constructor)
                        __FloatingPointType value
                ) noexcept;

            public:
                template < typename __AddressType, meta :: EnableIf < ! meta :: isStringCharType < __AddressType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Explicit __BaseString (
                        __AddressType const * address
                ) noexcept;

            public:
                ~__BaseString () noexcept override;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () noexcept -> Iterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () noexcept -> Iterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () const noexcept -> ConstIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () const noexcept -> ConstIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cbegin () const noexcept -> ConstIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cend () const noexcept -> ConstIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () noexcept -> ReverseIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () noexcept -> ReverseIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () const noexcept -> ConstReverseIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () const noexcept -> ConstReverseIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crbegin () const noexcept -> ConstReverseIterator;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crend () const noexcept -> ConstReverseIterator;


            public:
                __CDS_NoDiscard constexpr auto length () const noexcept -> Size;

            public:
                __CDS_NoDiscard constexpr auto size () const noexcept -> Size;


            public:
                __CDS_NoDiscard constexpr auto capacity () const noexcept -> Size;


            public:
                auto resize (
                        Size size
                ) noexcept -> void;

            public:
                auto reserve (
                        Size size
                ) noexcept -> void;

            public:
                auto shrink (
                        Size size = limits :: U64_MAX
                ) noexcept -> void;


            public:
                auto clear () noexcept -> void;

            public:
                __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator [] (
                        Index index
                ) noexcept (false) -> ElementType &;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto at (
                        Index index
                ) noexcept (false) -> ElementType &;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto at (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto get (
                        Index index
                ) noexcept (false) -> ElementType &;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementType &;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementType &;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementType;


            public:
                __CDS_NoDiscard auto toStdString () const noexcept -> std :: basic_string < ElementType >;

            public:
                __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const *;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> ElementType *;


            public:
                __CDS_Implicit operator std :: basic_string < __CharType > () const noexcept; // NOLINT(google-explicit-constructor)

            public:
                __CDS_Explicit constexpr operator ElementType const * () const noexcept; // NOLINT(google-explicit-constructor)

            public:
                __CDS_Explicit __CDS_cpplang_NonConstConstexprMemberFunction operator ElementType * () noexcept; // NOLINT(google-explicit-constructor)


            public:
                __CDS_NoDiscard auto substr (
                        Index from,
                        Index until = -1
                ) const noexcept -> __BaseString;

            public:
                __CDS_NoDiscard auto operator () (
                        Index from,
                        Index until = -1
                ) const noexcept -> __BaseString;

            public:
                template < typename __RangeType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto operator [] (
                        __RangeType const & range
                ) const noexcept -> __BaseString;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator = (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                auto operator = (
                        __BaseString const & string
                ) noexcept -> __BaseString &;

            public:
                auto operator = (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public:
                auto operator = (
                        __BaseStringView < ElementType > const & string
                ) noexcept -> __BaseString &;

            public:
                template < typename __TCharType = ElementType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator = (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator = (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public:
                auto operator = (
                        bool value
                ) noexcept -> __BaseString &;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator = (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;


            public:
                __CDS_NoDiscard __CDS_cpplang_DynamicCastConstexpr auto equals (
                        Object const & object
                ) const noexcept -> bool override;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            //// cpp-20 non-ambiguity rule
            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseString const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        ElementType character
                ) const noexcept -> bool;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __ConvertibleType && string
                ) const noexcept -> bool;

                //// cpp-20 non-ambiguity rule
            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseString const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        ElementType character
                ) const noexcept -> bool;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        ElementType character
                ) const noexcept -> bool;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        ElementType character
                ) const noexcept -> bool;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        ElementType character
                ) const noexcept -> bool;




            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        ElementType character
                ) const noexcept -> bool;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator += (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                auto operator += (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public:
                auto operator += (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto operator += (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator += (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator += (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public:
                auto operator += (
                        bool value
                ) noexcept -> __BaseString &;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator += (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __ConvertibleType && string
                ) const & noexcept -> __BaseString;

            public:
                auto operator + (
                        __BaseString && string
                ) const & noexcept -> __BaseString;

            public:
                auto operator + (
                        __BaseStringView < __CharType > const & string
                ) const & noexcept -> __BaseString;

#if defined(CDS_QT)

                public:
                auto operator + (
                        QString const & string
                ) const & noexcept -> __BaseString;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        ElementType character
                ) const & noexcept -> __BaseString;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __NumericType value
                ) const & noexcept -> __BaseString;

            public:
                auto operator + (
                        bool value
                ) const & noexcept -> __BaseString;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __FloatingPointType value
                ) const & noexcept -> __BaseString;



            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __ConvertibleType && string
                ) && noexcept -> __BaseString;

            public:
                auto operator + (
                        __BaseString && string
                ) && noexcept -> __BaseString;

            public:
                auto operator + (
                        __BaseStringView < __CharType > const & string
                ) && noexcept -> __BaseString;

#if defined(CDS_QT)

                public:
                auto operator + (
                        QString const & string
                ) && noexcept -> __BaseString;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        ElementType character
                ) && noexcept -> __BaseString;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __NumericType value
                ) && noexcept -> __BaseString;

            public:
                auto operator + (
                        bool value
                ) && noexcept -> __BaseString;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __FloatingPointType value
                ) && noexcept -> __BaseString;


            public:
                auto operator * (
                        int repeatCount
                ) const & noexcept -> __BaseString;

            public:
                auto operator * (
                        int repeatCount
                ) && noexcept -> __BaseString;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto append (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                auto append (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public:
                auto append (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto append (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto append (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto append (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public:
                auto append (
                        bool value
                ) noexcept -> __BaseString &;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto append (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;


            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto prepend (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                auto prepend (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public:
                auto prepend (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto prepend (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto prepend (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto prepend (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public:
                auto prepend (
                        bool value
                ) noexcept -> __BaseString &;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto prepend (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;



            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (
                        ElementType character
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto containsAnyOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto containsAllOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto containsAnyNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto containsAllNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;



            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto find (
                        Size                          maxCount,
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst (
                        ElementType character
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast (
                        ElementType character
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findAll (
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAll (
                        ElementType character
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto find (
                        Size                            maxCount,
                        __ConvertibleType            && string,
                        __CollectionType < Index >    & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto find (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto findAll (
                        __ConvertibleType                  && string,
                        __CollectionType < Index >          & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAll (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto findOf (
                        Size                          maxCount,
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findOf (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto findAllOf (
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAllOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto findNotOf (
                        Size                          maxCount,
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findNotOf (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto findAllNotOf (
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findAll (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAll (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findAllOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto findAllNotOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto findAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;


            public:
                auto ltrim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto ltrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public:
                auto ltrim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto ltrim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif


            public:
                auto rtrim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto rtrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public:
                auto rtrim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto rtrim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif


            public:
                auto trim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto trim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public:
                auto trim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public:
                auto trim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif


            public:
                auto ljust (
                        Size        size,
                        ElementType element = ' '
                ) noexcept -> __BaseString &;

            public:
                auto rjust (
                        Size        size,
                        ElementType element = ' '
                ) noexcept -> __BaseString &;


            public:
                __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> __BaseString &;

            public:
                __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> __BaseString &;


            public:
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto split (
                        ElementType             separator,
                        __CollectionType      & storeIn,
                        Size                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto split (
                        ElementType     separator,
                        Size            maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto split (
                        __ConvertibleType        && separators,
                        __CollectionType          & storeIn,
                        Size                        maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto split (
                        __ConvertibleType      && separators,
                        Size                      maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto split (
                        __BaseStringView < __CharType > const & separators,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto split (
                        __BaseStringView < __CharType > const & separators,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto splitByString (
                        __ConvertibleType     && separator,
                        __CollectionType       & storeIn,
                        Size                     maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto splitByString (
                        __ConvertibleType      && separator,
                        Size                      maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto splitByString (
                        __BaseStringView < __CharType > const & separators,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto splitByString (
                        __BaseStringView < __CharType > const & separators,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

            public:
                __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto replace (
                        Index                   from,
                        Index                   until,
                        __ConvertibleType    && inPlace
                ) noexcept -> __BaseString &;

            public:
                auto replace (
                        Index                                   from,
                        Index                                   until,
                        __BaseStringView < __CharType > const & inPlace
                ) noexcept -> __BaseString &;


            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto reverse () noexcept -> __BaseString &;


            public:
                constexpr auto startsWith (
                        ElementType character
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto startsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_cpplang_ConstexprConditioned auto startsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;


            public:
                constexpr auto endsWith (
                        ElementType character
                ) const noexcept -> bool;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto endsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public:
                __CDS_cpplang_ConstexprConditioned auto endsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;


            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;


            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;


            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        __ConvertibleType                        && delimiter
                ) noexcept -> __BaseString;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        __BaseStringView < __CharType >     const & delimiter
                ) noexcept -> __BaseString;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        ElementType                                 delimiter
                ) noexcept -> __BaseString;


            public:
                template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                auto forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void;

            public:
                template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                auto forEach (
                        __Action const & action
                ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto some (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto some (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atLeast (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atLeast (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atMost (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atMost (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto moreThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto moreThan (
                        Size                count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto fewerThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto fewerThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto count (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto count (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto any (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto any (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto all (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto all (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto none (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto none (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;


            public:
                template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard static auto format (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString;

            public:
                template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard static auto f (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString;

            public:
                auto sequence () & noexcept -> Sequence < __BaseString >;

            public:
                auto sequence () const & noexcept -> Sequence < __BaseString const >;

            public:
                auto sequence () && noexcept -> Sequence < __BaseString >;

            public:
                auto sequence () const && noexcept -> Sequence < __BaseString const >;


#if defined(CDS_STRING_DEBUG)

            public:
                __CDS_NoDiscard auto diag () const noexcept -> __BaseString;

#endif
            };


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                          character,
                    __BaseString < __FCharType > const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    QString                      const & leftString,
                    __BaseString < __FCharType > const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __NumericType                           value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    bool                                    value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FloatingPointType                     value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >          && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >         && rightString
            ) noexcept -> __BaseString < __FCharType >;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            friend auto operator + (
                    QString                      const & leftString,
                    __BaseString < __FCharType >      && rightString
            ) noexcept -> __BaseString < __FCharType >;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FCharType                        character,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __NumericType                      value,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    bool                            value,
                    __BaseString < __FCharType > && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FloatingPointType                value,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator * (
                    int                                     repeatCount,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator * (
                    int                             repeatCount,
                    __BaseString < __FCharType > && string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: ostream                     & out,
                    __BaseString < __FCharType > const & obj
            ) noexcept -> std :: ostream &;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: wostream                    & out,
                    __BaseString < __FCharType > const & obj
            ) noexcept -> std :: wostream &;

        }
    }
}

#include "AbstractIterator.hpp"
#include "AbstractConstIterator.hpp"
#include "Iterator.hpp"
#include "ConstIterator.hpp"
#include "ReverseIterator.hpp"
#include "ConstReverseIterator.hpp"

#include "view/BaseStringView.hpp"

#include "impl/BaseStringNonException.hpp"

#include <CDS/Utility>

#include "impl/AbstractIterator.hpp"
#include "impl/AbstractConstIterator.hpp"
#include "impl/Iterator.hpp"
#include "impl/ConstIterator.hpp"
#include "impl/ReverseIterator.hpp"
#include "impl/ConstReverseIterator.hpp"
#include "impl/StringUtils.hpp"
#include "impl/BaseString.hpp"

#include "view/AbstractConstIterator.hpp"
#include "view/ConstIterator.hpp"
#include "view/ConstReverseIterator.hpp"

#include "view/impl/AbstractConstIterator.hpp"
#include "view/impl/ConstIterator.hpp"
#include "view/impl/ConstReverseIterator.hpp"
#include "view/impl/BaseStringView.hpp"

#include "view/Literal.hpp"

#include "../../../shared/string/impl/StringSequence.hpp"
#include "../../../shared/string/view/impl/StringViewSequence.hpp"

#endif // __CDS_STRING_BASE_HPP__
