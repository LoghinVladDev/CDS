/*
 * Created by loghin on 6/3/22.
 */

#ifndef __CDS_STRING_BASE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STRING_BASE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/meta/TypeTraits>

#include "../../../shared/impl/generalPredicates.hpp"   /* NOLINT(llvm-include-order) */
#include "../../../shared/impl/arithmetic.hpp"
#include "../../../shared/memory/PrimitiveAllocation.hpp"

#include <CDS/Limits>                                   /* NOLINT(llvm-include-order) */
#include "StringUtils.hpp"
#include <cstring>
#include <sstream>

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename C >
    class Sequence;

    class OutOfBoundsException;

    namespace __hidden {                            /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __CharType >        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __BaseStringView;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __CharType >        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __BaseString : public Object {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Represents an element in the string
                 */
                using ElementType = __CharType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using Iterator              = cds :: ForwardAddressIterator < __CharType >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using ConstIterator         = cds :: ForwardAddressIterator < __CharType const >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using ReverseIterator       = cds :: BackwardAddressIterator < __CharType >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using ConstReverseIterator  = cds :: BackwardAddressIterator < __CharType const >;

            private:
                friend class __BaseStringView < __CharType >;


            private:    /* NOLINT(readability-redundant-access-specifiers) */
                ElementType       * _pBuffer        { nullptr };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                Size                _length         { 0ULL };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                Size                _capacity       { 0ULL };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                static Size const   minCapacity;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static Index const  invalidIndex;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const whitespace;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const digits;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const lowercaseAlphabet;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const uppercaseAlphabet;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const vowels;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                static __BaseStringView < __CharType > const consonants;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __BaseString () noexcept = default;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                __BaseString (
                        __BaseString const & string
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __CDS_Implicit __BaseString (     /* NOLINT(*-explicit-*) */
                        __BaseString < __OtherCharType > const & string
                ) noexcept;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __BaseString (
                        __BaseString && string
                ) noexcept;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (   /* NOLINT(*-explicit-*) */
                        __BaseStringView < __CharType > const & string
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __CDS_Implicit __BaseString (     /* NOLINT(*-explicit-*) */
                        __BaseStringView < __OtherCharType > const & string
                ) noexcept;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (   /* NOLINT(*-explicit-*) */
                        ElementType const * pString
                ) noexcept;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (   /* NOLINT(*-explicit-*) */
                        std :: basic_string < __CharType > const & string
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __BaseString (
                        ElementType const * pString,
                        Size                length
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __CDS_Implicit __BaseString (     /* NOLINT(*-explicit-*) */
                        __OtherCharType const * pString
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __BaseString (
                        __OtherCharType   const * pString,
                        Size                      length
                ) noexcept;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (   /* NOLINT(*-explicit-*) */
                        Object const & object
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __BaseString (
                        Size        length,
                        ElementType fillCharacter
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __BaseString (
                        Size              length,
                        __OtherCharType   fillCharacter
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isIterator < __IteratorType > () > = 0
                > __BaseString (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (
                        std :: initializer_list < ElementType > const & initializerList
                ) noexcept;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf <
                                meta :: isStringCharType < __OtherCharType > () &&
                                ! meta :: isSame < __OtherCharType, __CharType > ()
                        > = 0
                > __CDS_Implicit __BaseString (
                        std :: initializer_list < __OtherCharType > const & initializerList
                ) noexcept;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __BaseString (
                        QString const & string
                ) noexcept;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_Implicit __BaseString (                                                                                           /* NOLINT(*-explicit-*) */
                        ElementType value
                ) noexcept;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_Implicit __BaseString (                                                                                               /* NOLINT(*-explicit-*) */
                        __NumericType value
                ) noexcept;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit __BaseString (   /* NOLINT(*-explicit-*) */
                        bool value
                ) noexcept;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_Implicit __BaseString (                                                                                           /* NOLINT(*-explicit-*) */
                        __FloatingPointType value
                ) noexcept;

            public:                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __AddressType, meta :: EnableIf < ! meta :: isStringCharType < __AddressType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_Explicit __BaseString (
                        __AddressType const * address
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                ~__BaseString () noexcept override;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () noexcept -> Iterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () noexcept -> Iterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto begin () const noexcept -> ConstIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto end () const noexcept -> ConstIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cbegin () const noexcept -> ConstIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto cend () const noexcept -> ConstIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () noexcept -> ReverseIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () noexcept -> ReverseIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () const noexcept -> ConstReverseIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto rend () const noexcept -> ConstReverseIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crbegin () const noexcept -> ConstReverseIterator;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprNonLiteralReturn auto crend () const noexcept -> ConstReverseIterator;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto length () const noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto size () const noexcept -> Size;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto capacity () const noexcept -> Size;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto resize (
                        Size size
                ) noexcept -> void;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto reserve (
                        Size size
                ) noexcept -> void;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto shrink (
                        Size size = limits :: U64_MAX
                ) noexcept -> void;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto clear () noexcept -> void;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __NumericType,
                        cds :: meta :: EnableIf < cds :: meta :: isIntegral < __NumericType > () > = 0
                > __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator [] (
                        __NumericType index
                ) noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __NumericType,
                        cds :: meta :: EnableIf < cds :: meta :: isIntegral < __NumericType > () > = 0
                > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (
                        __NumericType index
                ) const noexcept (false) -> ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto at (
                        Index index
                ) noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto at (
                        Index index
                ) const noexcept (false) -> ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto get (
                        Index index
                ) noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (
                        Index index
                ) const noexcept (false) -> ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto toStdString () const noexcept -> std :: basic_string < ElementType >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const *;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> ElementType *;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Implicit operator std :: basic_string < __CharType > () const noexcept; /* NOLINT(*-explicit-*) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Explicit constexpr operator ElementType const * () const noexcept; /* NOLINT(*-explicit-*) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Explicit __CDS_cpplang_NonConstConstexprMemberFunction operator ElementType * () noexcept; /* NOLINT(*-explicit-*) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto substr (
                        Index from,
                        Index until = -1
                ) const noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto operator () (
                        Index from,
                        Index until = -1
                ) const noexcept -> __BaseString;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __ConvertibleType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto operator = (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        __BaseString const & string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        __BaseStringView < ElementType > const & string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = ElementType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator = (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator = (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator = (
                        bool value
                ) noexcept -> __BaseString &;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator = (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;


            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                        Object const & object
                ) const noexcept -> bool override;

            public:                                                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            /** cpp-20 non-ambiguity rule */
            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseString const & string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __ConvertibleType && string
                ) const noexcept -> bool;

                /** cpp-20 non-ambiguity rule */
            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseString const & string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        ElementType character
                ) const noexcept -> bool;


            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator += (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator += (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator += (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator += (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator += (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator += (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator += (
                        bool value
                ) noexcept -> __BaseString &;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator += (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __ConvertibleType && string
                ) const & noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        __BaseString && string
                ) const & noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        __BaseStringView < __CharType > const & string
                ) const & noexcept -> __BaseString;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        QString const & string
                ) const & noexcept -> __BaseString;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        ElementType character
                ) const & noexcept -> __BaseString;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __NumericType value
                ) const & noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        bool value
                ) const & noexcept -> __BaseString;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __FloatingPointType value
                ) const & noexcept -> __BaseString;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __ConvertibleType && string
                ) && noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        __BaseString && string
                ) && noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        __BaseStringView < __CharType > const & string
                ) && noexcept -> __BaseString;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        QString const & string
                ) && noexcept -> __BaseString;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        ElementType character
                ) && noexcept -> __BaseString;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __NumericType value
                ) && noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator + (
                        bool value
                ) && noexcept -> __BaseString;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto operator + (
                        __FloatingPointType value
                ) && noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator * (
                        int repeatCount
                ) const & noexcept -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator * (
                        int repeatCount
                ) && noexcept -> __BaseString;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto append (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto append (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto append (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto append (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto append (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto append (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto append (
                        bool value
                ) noexcept -> __BaseString &;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto append (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto prepend (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto prepend (
                        __BaseString && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto prepend (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto prepend (
                        QString const & string
                ) noexcept -> __BaseString &;

#endif

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto prepend (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto prepend (
                        __NumericType value
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto prepend (
                        bool value
                ) noexcept -> __BaseString &;

            public:                                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto prepend (
                        __FloatingPointType value
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto find (
                        Size                          maxCount,
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst (
                        ElementType character
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast (
                        ElementType character
                ) const noexcept -> Index;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findAll (
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findAll (
                        ElementType character
                ) const noexcept -> __CollectionType < Index >;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto find (
                        Size                            maxCount,
                        __ConvertibleType            && string,
                        __CollectionType < Index >    & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto find (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto findAll (
                        __ConvertibleType                  && string,
                        __CollectionType < Index >          & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto findAll (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto findOf (
                        Size                          maxCount,
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto findOf (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto findAllOf (
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto findAllOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto findNotOf (
                        Size                          maxCount,
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto findNotOf (
                        Size                          maxCount,
                        __ConvertibleType          && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto findAllNotOf (
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto findAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findAll (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findAll (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findAllOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto findAllNotOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto findAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto ltrim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto ltrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto ltrim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto ltrim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto rtrim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto rtrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto rtrim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto rtrim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto trim (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto trim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto trim (
                        __BaseStringView < __CharType > const & characters = __BaseString :: whitespace
                ) noexcept -> __BaseString &;

#if defined(CDS_QT)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto trim (
                        QString const & characters
                ) noexcept -> __BaseString &;

#endif

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto ljust (
                        Size        size,
                        ElementType element = ' '
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto rjust (
                        Size        size,
                        ElementType element = ' '
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> __BaseString &;

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto split (
                        ElementType             separator,
                        __CollectionType      & storeIn,
                        Size                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto split (
                        ElementType     separator,
                        Size            maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __ConvertibleType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > auto split (
                        __ConvertibleType        && separators,
                        __CollectionType          & storeIn,
                        Size                        maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard auto split (
                        __ConvertibleType      && separators,
                        Size                      maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto split (
                        __BaseStringView < __CharType > const & separators,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard auto split (
                        __BaseStringView < __CharType > const & separators,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __CollectionType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __ConvertibleType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_MaybeUnused auto splitByString (
                        __ConvertibleType     && separator,
                        __CollectionType       & storeIn,
                        Size                     maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (
                        __ConvertibleType      && separator,
                        Size                      maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CollectionType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_MaybeUnused auto splitByString (
                        __BaseStringView < __CharType > const & separators,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_MaybeUnused auto splitByString (
                        __BaseStringView < __CharType > const & separators,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto replace (
                        Index                   from,
                        Index                   until,
                        __ConvertibleType    && inPlace
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto replace (
                        Index                                   from,
                        Index                                   until,
                        __BaseStringView < __CharType > const & inPlace
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto reverse () noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto startsWith (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto startsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto endsWith (
                        ElementType character
                ) const noexcept -> bool;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto endsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_MaybeUnused __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        ElementType character
                ) noexcept -> __BaseString &;

            public:                                                                                                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString &;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename                        __ConvertibleType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0
                > __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        __ConvertibleType                        && delimiter
                ) noexcept -> __BaseString;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        __BaseStringView < __CharType >     const & delimiter
                ) noexcept -> __BaseString;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard static auto join (
                        __CollectionType < __BaseString >   const & tokens,
                        ElementType                                 delimiter
                ) noexcept -> __BaseString;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Action >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void;

            public:                             /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Action >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto forEach (
                        __Action const & action
                ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto some (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto some (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto atLeast (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto atLeast (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto atMost (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto atMost (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto moreThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto moreThan (
                        Size                count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto fewerThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto fewerThan (
                        Size                  count,
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto count (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto count (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto any (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto any (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto all (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto all (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto none (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto none (
                        __Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

            public:                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard static auto format (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString;

            public:                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard static auto f (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto sequence () & noexcept -> Sequence < __BaseString >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < __BaseString const >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto sequence () && noexcept -> Sequence < __BaseString >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < __BaseString const >;


#if defined(CDS_STRING_DEBUG)

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto diag () const noexcept -> __BaseString;

#endif
            };


            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >     const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                          character,
                    __BaseString < __FCharType > const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> bool;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    QString                         const & leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __BaseStringView < __FCharType >    const & leftString,
                    __BaseString < __FCharType >        const & rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >    const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    QString                      const & leftString,
                    __BaseString < __FCharType > const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __FCharType                             character,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __NumericType                           value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    bool                                    value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __FloatingPointType                     value,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __BaseStringView < __FCharType > const & leftString,
                    __BaseString < __FCharType >          && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __ConvertibleType                    && leftString,
                    __BaseString < __FCharType >         && rightString
            ) noexcept -> __BaseString < __FCharType >;

#if defined(CDS_QT)

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            friend auto operator + (
                    QString                      const & leftString,
                    __BaseString < __FCharType >      && rightString
            ) noexcept -> __BaseString < __FCharType >;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __FCharType                        character,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __NumericType                      value,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    bool                            value,
                    __BaseString < __FCharType > && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator + (
                    __FloatingPointType                value,
                    __BaseString < __FCharType >    && rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator * (
                    int                                     repeatCount,
                    __BaseString < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator * (
                    int                             repeatCount,
                    __BaseString < __FCharType > && string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator << (
                    std :: ostream                     & out,
                    __BaseString < __FCharType > const & obj
            ) noexcept -> std :: ostream &;

            template < typename __FCharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto operator << (
                    std :: wostream                    & out,
                    __BaseString < __FCharType > const & obj
            ) noexcept -> std :: wostream &;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#include "view/BaseStringView.hpp"

#include "impl/BaseStringNonException.hpp"

#include <CDS/Utility>

#include "impl/StringUtils.hpp" /* NOLINT(llvm-include-order) */
#include "impl/BaseString.hpp"

#include "view/impl/BaseStringView.hpp"

#include "view/Literal.hpp"

#include "../../../shared/string/impl/StringSequence.hpp"
#include "../../../shared/string/view/impl/StringViewSequence.hpp"

#endif /* __CDS_STRING_BASE_HPP__ */
