//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_BASE_HPP__
#define __CDS_EX_STRING_BASE_HPP__

#include <CDS/Range>
#include "StringUtils.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename C >
    class Sequence;

    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseStringView;

                template < typename CharType >
                class BaseString : public experimental :: Object {

                public:
                    /**
                     * @brief Represents an element in the string
                     */
                    using ElementType = CharType;

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
                    friend class BaseStringView < CharType >;


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
                    static BaseStringView < CharType > const whitespace;

                public:
                    static BaseStringView < CharType > const digits;

                public:
                    static BaseStringView < CharType > const lowercaseAlphabet;

                public:
                    static BaseStringView < CharType > const uppercaseAlphabet;

                public:
                    static BaseStringView < CharType > const vowels;

                public:
                    static BaseStringView < CharType > const consonants;

                public:
                    constexpr BaseString () noexcept = default;

                public:
                    BaseString (
                            BaseString const & string
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            BaseString < OtherCharType > const & string
                    ) noexcept;

                public:
                    constexpr BaseString (
                            BaseString && string
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            BaseStringView < CharType > const & string
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            BaseStringView < OtherCharType > const & string
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            ElementType const * pString
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            std :: basic_string < CharType > const & string
                    ) noexcept;

                /// todo remove
                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            cds :: String const & string
                    ) noexcept;

                public:
                    BaseString (
                            ElementType const * pString,
                            Size                length
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            OtherCharType const * pString
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    BaseString (
                            OtherCharType   const * pString,
                            Size                    length
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            experimental :: Object const & object
                    ) noexcept;

                public:
                    BaseString (
                            Size        length,
                            ElementType fillCharacter
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    BaseString (
                            Size            length,
                            OtherCharType   fillCharacter
                    ) noexcept;

                public:
                    template < typename IteratorType, meta :: EnableIf < meta :: isIterator < IteratorType > () > = 0 >
                    BaseString (
                            IteratorType const & begin,
                            IteratorType const & end
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString (
                            std :: initializer_list < ElementType > const & initializerList
                    ) noexcept;

                public:
                    template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
                    __CDS_Implicit BaseString (
                            std :: initializer_list < OtherCharType > const & initializerList
                    ) noexcept;

#if defined(CDS_QT)

                public:
                    BaseString (
                            QString const & string
                    ) noexcept;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            ElementType value
                    ) noexcept;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            NumericType value
                    ) noexcept;

                public:
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            bool value
                    ) noexcept;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    __CDS_Implicit BaseString ( // NOLINT(google-explicit-constructor)
                            FloatingPointType value
                    ) noexcept;

                public:
                    template < typename T, meta :: EnableIf < ! meta :: isSame < T, ElementType > () > = 0 >
                    __CDS_Explicit BaseString (
                            T const * address
                    ) noexcept;

                public:
                    ~BaseString () noexcept override;


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
                    __CDS_NoDiscard auto toStdString () const noexcept -> std :: basic_string < CharType >;

                public:
                    __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const *;

                public:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> ElementType *;


                public:
                    __CDS_Implicit operator std :: basic_string < CharType > () const noexcept; // NOLINT(google-explicit-constructor)

                public:
                    __CDS_Explicit constexpr operator ElementType const * () const noexcept; // NOLINT(google-explicit-constructor)

                public:
                    __CDS_Explicit __CDS_cpplang_NonConstConstexprMemberFunction operator ElementType * () noexcept; // NOLINT(google-explicit-constructor)


                public:
                    __CDS_NoDiscard auto substr (
                            Index from,
                            Index until = -1
                    ) const noexcept -> BaseString;

                public:
                    __CDS_NoDiscard auto operator () (
                            Index from,
                            Index until = -1
                    ) const noexcept -> BaseString;

                public:
                    __CDS_NoDiscard auto operator [] (
                            Range const & range
                    ) const noexcept -> BaseString;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto operator = (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    auto operator = (
                            BaseString && string
                    ) noexcept -> BaseString &;

                public:
                    auto operator = (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto operator = (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto operator = (
                            NumericType value
                    ) noexcept -> BaseString &;

                public:
                    auto operator = (
                            bool value
                    ) noexcept -> BaseString &;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto operator = (
                            FloatingPointType value
                    ) noexcept -> BaseString &;


                public:
                    __CDS_NoDiscard __CDS_cpplang_DynamicCastConstexpr auto equals (
                            Object const & object
                    ) const noexcept -> bool override;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView< ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                //// cpp-20 non-ambiguity rule
                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            BaseString const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                    public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            ElementType character
                    ) const noexcept -> bool;


                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            BaseStringView < FCharType > const & leftString,
                            BaseString < FCharType >     const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                    //// cpp-20 non-ambiguity rule
                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            BaseString const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                    public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            ElementType character
                    ) const noexcept -> bool;


                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            BaseStringView < FCharType > const & leftString,
                            BaseString < FCharType >     const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                    public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            ElementType character
                    ) const noexcept -> bool;


                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            BaseStringView < FCharType >    const & leftString,
                            BaseString < FCharType >        const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            ElementType character
                    ) const noexcept -> bool;


                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            BaseStringView < FCharType >    const & leftString,
                            BaseString < FCharType >        const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                    public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            ElementType character
                    ) const noexcept -> bool;



                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            BaseStringView < FCharType > const & leftString,
                            BaseString < FCharType >     const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            FCharType                        character,
                            BaseString < FCharType > const & string
                    ) noexcept -> bool;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

#if defined(CDS_QT)

                    public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            QString const & string
                    ) const noexcept -> bool;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            ElementType character
                    ) const noexcept -> bool;


                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            BaseStringView < FCharType >    const & leftString,
                            BaseString < FCharType >        const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            QString                     const & leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto operator += (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    auto operator += (
                            BaseString && string
                    ) noexcept -> BaseString &;

                public:
                    auto operator += (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto operator += (
                            QString const & string
                    ) noexcept -> BaseString &;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto operator += (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto operator += (
                            NumericType value
                    ) noexcept -> BaseString &;

                public:
                    auto operator += (
                            bool value
                    ) noexcept -> BaseString &;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto operator += (
                            FloatingPointType value
                    ) noexcept -> BaseString &;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto operator + (
                            ConvertibleType && string
                    ) const & noexcept -> BaseString;

                public:
                    auto operator + (
                            BaseString && string
                    ) const & noexcept -> BaseString;

                public:
                    auto operator + (
                            BaseStringView < CharType > const & string
                    ) const & noexcept -> BaseString;

#if defined(CDS_QT)

                    public:
                    auto operator + (
                            QString const & string
                    ) const & noexcept -> BaseString;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) const & noexcept -> BaseString;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto operator + (
                            NumericType value
                    ) const & noexcept -> BaseString;

                public:
                    auto operator + (
                            bool value
                    ) const & noexcept -> BaseString;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto operator + (
                            FloatingPointType value
                    ) const & noexcept -> BaseString;


                public:
                    template < typename FCharType >
                    friend auto operator + (
                            BaseStringView < FCharType >    const & leftString,
                            BaseString < FCharType >        const & rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    friend auto operator + (
                            ConvertibleType && leftString,
                            BaseString < FCharType >    const & rightString
                    ) noexcept -> BaseString < FCharType >;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            QString     const & leftString,
                            BaseString < FCharType > const & rightString
                    ) noexcept -> BaseString < FCharType >;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    friend auto operator + (
                            FCharType                           character,
                            BaseString < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename NumericType, meta :: EnableIf < meta :: isIntegralToString < FCharType, NumericType > () > >
                    friend auto operator + (
                            NumericType                         value,
                            BaseString < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            bool                                value,
                            BaseString < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > >
                    friend auto operator + (
                            FloatingPointType                   value,
                            BaseString < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;



                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto operator + (
                            ConvertibleType && string
                    ) && noexcept -> BaseString;

                public:
                    auto operator + (
                            BaseString && string
                    ) && noexcept -> BaseString;

                public:
                    auto operator + (
                            BaseStringView < CharType > const & string
                    ) && noexcept -> BaseString;

#if defined(CDS_QT)

                    public:
                    auto operator + (
                            QString const & string
                    ) && noexcept -> BaseString;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) && noexcept -> BaseString;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto operator + (
                            NumericType value
                    ) && noexcept -> BaseString;

                public:
                    auto operator + (
                            bool value
                    ) && noexcept -> BaseString;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto operator + (
                            FloatingPointType value
                    ) && noexcept -> BaseString;


                public:
                    template < typename FCharType >
                    friend auto operator + (
                            BaseStringView < FCharType > const & leftString,
                            BaseString < FCharType >          && rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < ConvertibleType, FCharType > () > >
                    friend auto operator + (
                            ConvertibleType && leftString,
                            BaseString < FCharType >         && rightString
                    ) noexcept -> BaseString < FCharType >;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            QString                  const & leftString,
                            BaseString < FCharType >      && rightString
                    ) noexcept -> BaseString < FCharType >;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > >
                    friend auto operator + (
                            FCharType                      character,
                            BaseString < FCharType >    && rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename NumericType, meta :: EnableIf < meta :: isIntegralToString < FCharType, NumericType > () > >
                    friend auto operator + (
                            NumericType                    value,
                            BaseString < FCharType >    && rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            bool                        value,
                            BaseString < FCharType > && rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType, typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > >
                    friend auto operator + (
                            FloatingPointType              value,
                            BaseString < FCharType >    && rightString
                    ) noexcept -> BaseString < FCharType >;


                public:
                    auto operator * (
                            int repeatCount
                    ) const & noexcept -> BaseString;

                public:
                    auto operator * (
                            int repeatCount
                    ) && noexcept -> BaseString;

                public:
                    template < typename FCharType >
                    friend auto operator * (
                            int                                 repeatCount,
                            BaseString < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator * (
                            int                         repeatCount,
                            BaseString < FCharType > && string
                    ) noexcept -> BaseString < FCharType >;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto append (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    auto append (
                            BaseString && string
                    ) noexcept -> BaseString &;

                public:
                    auto append (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto append (
                            QString const & string
                    ) noexcept -> BaseString &;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto append (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto append (
                            NumericType value
                    ) noexcept -> BaseString &;

                public:
                    auto append (
                            bool value
                    ) noexcept -> BaseString &;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto append (
                            FloatingPointType value
                    ) noexcept -> BaseString &;


                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto prepend (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    auto prepend (
                            BaseString && string
                    ) noexcept -> BaseString &;

                public:
                    auto prepend (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto prepend (
                            QString const & string
                    ) noexcept -> BaseString &;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isStringCharType < T > () > = 0 >
                    auto prepend (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > = 0 >
                    auto prepend (
                            NumericType value
                    ) noexcept -> BaseString &;

                public:
                    auto prepend (
                            bool value
                    ) noexcept -> BaseString &;

                public:
                    template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > = 0 >
                    auto prepend (
                            FloatingPointType value
                    ) noexcept -> BaseString &;



                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAnyOf (
                             CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                            ConvertibleType && string
                    ) const noexcept -> bool;
                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAllOf (
                             CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAnyNotOf (
                             CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAnyNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAllNotOf (
                             CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto containsAllNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;



                public:
                    template < template < typename ... > class CollectionType >
                    auto find (
                            Size                        maxCount,
                            ElementType                 character,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto find (
                            Size                        maxCount,
                            ElementType                 character
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst (
                            ElementType character
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast (
                            ElementType character
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAll (
                            ElementType                 character,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAll (
                            ElementType                 character
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto find (
                            Size                        maxCount,
                            ConvertibleType && string,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto find (
                            Size                        maxCount,
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto findAll (
                            ConvertibleType && string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto findAll (
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto findOf (
                            Size                        maxCount,
                            ConvertibleType && string,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto findOf (
                            Size                        maxCount,
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto findAllOf (
                            ConvertibleType && string,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto findAllOf (
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto findNotOf (
                            Size                        maxCount,
                            ConvertibleType && string,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto findNotOf (
                            Size                        maxCount,
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                            ConvertibleType && string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto findAllNotOf (
                            ConvertibleType && string,
                            CollectionType < Index >  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto findAllNotOf (
                            ConvertibleType && string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto find (
                            Size                                maxCount,
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto find (
                            Size                                maxCount,
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAll (
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAll (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findOf (
                            Size                                maxCount,
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findOf (
                            Size                                maxCount,
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllOf (
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findNotOf (
                            Size                        maxCount,
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findNotOf (
                            Size                                maxCount,
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllNotOf (
                            BaseStringView < CharType > const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    auto ltrim (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto ltrim (
                            ConvertibleType && characters
                    ) noexcept -> BaseString &;

                public:
                    auto ltrim (
                            BaseStringView < CharType > const & characters = BaseString :: whitespace
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto ltrim (
                            QString const & characters
                    ) noexcept -> BaseString &;

#endif


                public:
                    auto rtrim (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto rtrim (
                            ConvertibleType && characters
                    ) noexcept -> BaseString &;

                public:
                    auto rtrim (
                            BaseStringView < CharType > const & characters = BaseString :: whitespace
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto rtrim (
                            QString const & characters
                    ) noexcept -> BaseString &;

#endif


                public:
                    auto trim (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto trim (
                            ConvertibleType && characters
                    ) noexcept -> BaseString &;

                public:
                    auto trim (
                            BaseStringView < CharType > const & characters = BaseString :: whitespace
                    ) noexcept -> BaseString &;

#if defined(CDS_QT)

                public:
                    auto trim (
                            QString const & characters
                    ) noexcept -> BaseString &;

#endif


                public:
                    auto ljust (
                            Size        size,
                            ElementType element = ' '
                    ) noexcept -> BaseString &;

                public:
                    auto rjust (
                            Size        size,
                            ElementType element = ' '
                    ) noexcept -> BaseString &;


                public:
                    __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> BaseString &;

                public:
                    __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> BaseString &;


                public:
                    template < typename ListType >
                    auto split (
                            ElementType     separator,
                            ListType      & storeIn,
                            Size            maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            ElementType     separator,
                            Size            maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType < BaseString >;

                public:
                    template < typename ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto split (
                            ConvertibleType && separators,
                            ListType              & storeIn,
                            Size                    maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto split (
                            ConvertibleType && separators,
                            Size                    maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType < BaseString >;

                public:
                    template < typename ListType >
                    auto split (
                            BaseStringView < CharType > const & separators,
                            ListType                          & storeIn,
                            Size                                maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            BaseStringView < CharType > const & separators,
                            Size                                maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType < BaseString >;

                public:
                    template < typename ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto splitByString (
                            ConvertibleType      && separator,
                            ListType              & storeIn,
                            Size                    maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard auto splitByString (
                            ConvertibleType      && separator,
                            Size                    maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType < BaseString >;

                public:
                    template < typename ListType >
                    auto splitByString (
                            BaseStringView < CharType > const & separators,
                            ListType                          & storeIn,
                            Size                                maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto splitByString (
                            BaseStringView < CharType > const & separators,
                            Size                                maxCount = limits :: U32_MAX
                    ) const noexcept -> ListType < BaseString >;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index override;

                /// change this later blyat
                public:
                    __CDS_NoDiscard auto toString () const noexcept -> cds :: String override;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    auto replace (
                            Index                   from,
                            Index                   until,
                            ConvertibleType && inPlace
                    ) noexcept -> BaseString &;

                public:
                    auto replace (
                            Index                               from,
                            Index                               until,
                            BaseStringView < CharType > const & inPlace
                    ) noexcept -> BaseString &;


                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto reverse () noexcept -> BaseString &;


                public:
                    constexpr auto startsWith (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_cpplang_ConstexprConditioned auto startsWith (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_cpplang_ConstexprConditioned auto startsWith (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;


                public:
                    constexpr auto endsWith (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_cpplang_ConstexprConditioned auto endsWith (
                            ConvertibleType && string
                    ) const noexcept -> bool;

                public:
                    __CDS_cpplang_ConstexprConditioned auto endsWith (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;


                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removePrefix (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;


                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                            ElementType character
                    ) noexcept -> BaseString &;

                public:
                    template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                            ConvertibleType && string
                    ) noexcept -> BaseString &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto removeSuffix (
                            BaseStringView < CharType > const & string
                    ) noexcept -> BaseString &;


                public:
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > = 0 >
                    __CDS_NoDiscard static auto join (
                            CollectionType < BaseString >   const & tokens,
                            ConvertibleType && delimiter
                    ) noexcept -> BaseString < BaseString >;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard static auto join (
                            CollectionType < BaseString >   const & tokens,
                            BaseStringView < CharType >     const & delimiter
                    ) noexcept -> BaseString;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard static auto join (
                            CollectionType < BaseString >   const & tokens,
                            ElementType                             delimiter
                    ) noexcept -> BaseString;


                public:
                    template < typename Action >
                    auto forEach (
                            Action const & action
                    ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void;

                public:
                    template < typename Action >
                    auto forEach (
                            Action const & action
                    ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto some (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto some (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atLeast (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atLeast (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atMost (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atMost (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto moreThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto moreThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto fewerThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto fewerThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto count (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto count (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto any (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto any (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto all (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto all (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto none (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto none (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;


                public:
                    template < typename ... ArgumentTypes >
                    __CDS_NoDiscard static auto format (
                            StringLiteral           format,
                            ArgumentTypes    && ... arguments
                    ) noexcept ( false ) -> BaseString;

                public:
                    template < typename ... ArgumentTypes >
                    __CDS_NoDiscard static auto f (
                            StringLiteral           format,
                            ArgumentTypes    && ... arguments
                    ) noexcept ( false ) -> BaseString;

                public:
                    auto sequence () & noexcept -> Sequence < BaseString >;

                public:
                    auto sequence () const & noexcept -> Sequence < BaseString const >;

                public:
                    auto sequence () && noexcept -> Sequence < BaseString >;

                public:
                    auto sequence () const && noexcept -> Sequence < BaseString const >;


                public:
                    template < typename FCharType >
                    friend auto operator << (
                            std :: wostream                & out,
                            BaseString < FCharType > const & obj
                    ) noexcept -> std :: wostream &;


#if defined(CDS_STRING_DEBUG)

                public:
                    __CDS_NoDiscard auto diag () const noexcept -> BaseString;

#endif
                };

            }
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

#include "../shared/string/impl/StringSequence.hpp"
#include "../shared/string/view/impl/StringViewSequence.hpp"

#endif // __CDS_EX_STRING_BASE_HPP__
