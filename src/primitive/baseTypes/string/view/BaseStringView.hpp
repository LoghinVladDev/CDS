//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_BASE_STRING_VIEW_HPP__
#define __CDS_BASE_STRING_VIEW_HPP__

namespace cds {

    template < typename C >
    class Sequence;

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseStringView { // NOLINT(bugprone-reserved-identifier)

            public:
                /**
                 * @brief Represents an element in the string
                 */
                using ElementType = __CharType;

            private:
                class AbstractConstIterator;

            public:
                class ConstIterator;

            public:
                class ConstReverseIterator;


            private:
                ElementType const * _pData  { nullptr };

            private:
                Size                _length { 0ULL };

            public:
                static Index const  invalidIndex;

            public:
                constexpr __BaseStringView () noexcept = default;

            public:
                constexpr __BaseStringView (
                        __BaseStringView const & string
                ) noexcept;

            public:
                constexpr __BaseStringView (
                        __BaseStringView && string
                ) noexcept;

            public:
                __CDS_Explicit constexpr __BaseStringView ( // NOLINT(google-explicit-constructor)
                        __BaseString < __CharType > const & string
                ) noexcept;

            public:
                __CDS_Explicit constexpr __BaseStringView ( // NOLINT(google-explicit-constructor)
                        std :: basic_string < __CharType > const & string
                ) noexcept;

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_Explicit constexpr __BaseStringView ( // NOLINT(google-explicit-constructor)
                        ElementType const * pString
                ) noexcept;

            public:
                constexpr __BaseStringView (
                        ElementType const * pString,
                        Size                length
                ) noexcept;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto begin () const noexcept -> ConstIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto end () const noexcept -> ConstIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto cbegin () const noexcept -> ConstIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto cend () const noexcept -> ConstIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto rbegin () const noexcept -> ConstReverseIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto rend () const noexcept -> ConstReverseIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto crbegin () const noexcept -> ConstReverseIterator;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto crend () const noexcept -> ConstReverseIterator;


            public:
                __CDS_NoDiscard constexpr auto length () const noexcept -> Size;

            public:
                __CDS_NoDiscard constexpr auto size () const noexcept -> Size;


            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto clear () noexcept -> void;

            public:
                __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

            public:
                __CDS_cpplang_ConstexprConditioned auto operator [] (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_ConstexprConditioned auto at (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_ConstexprConditioned auto get (
                        Index index
                ) const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementType;

            public:
                __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementType;


            public:
                __CDS_NoDiscard auto toStdString () const noexcept -> std :: basic_string < __CharType >;

            public:
                __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const *;

            public:
                __CDS_NoDiscard constexpr auto data () const noexcept -> ElementType const *;


            public:
                __CDS_Implicit operator std :: basic_string < __CharType > () const noexcept; // NOLINT(google-explicit-constructor)

            public:
                __CDS_Implicit constexpr operator ElementType const * () const noexcept; // NOLINT(google-explicit-constructor)


            public:
                auto substr (
                        Index from,
                        Index until = -1
                ) const noexcept -> __BaseString < __CharType >;

            public:
                auto operator () (
                        Index from,
                        Index to = -1
                ) const noexcept -> __BaseString < __CharType >;

            public:
                template < typename __RangeType > // NOLINT(bugprone-reserved-identifier)
                auto operator [] (
                        __RangeType const & range
                ) const noexcept -> __BaseString < __CharType >;


            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __BaseString < __CharType > const & string
                ) noexcept -> __BaseStringView &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __BaseStringView const & string
                ) noexcept -> __BaseStringView &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __BaseStringView && string
                ) noexcept -> __BaseStringView &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        std :: basic_string < __CharType > const & string
                ) noexcept -> __BaseStringView &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        ElementType const * pString
                ) noexcept -> __BaseStringView &;


            public:
                __CDS_NoDiscard __CDS_cpplang_DynamicCastConstexpr auto equals (
                        Object const & object
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseStringView const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        ElementType character
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseStringView const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        ElementType character
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                        ElementType character
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                        ElementType character
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                        ElementType character
                ) const noexcept -> bool;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> bool;

#if defined(CDS_QT)

                public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        QString const & string
                ) const noexcept -> bool;

#endif

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        ElementType const * pString
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                        ElementType character
                ) const noexcept -> bool;


            public:
                auto operator + (
                        __BaseStringView const & string
                ) const noexcept -> __BaseString < __CharType >;

            public:
                auto operator + (
                        std :: basic_string < __CharType > const & string
                ) const noexcept -> __BaseString < __CharType >;

            public:
                auto operator + (
                        ElementType const * pString
                ) const noexcept -> __BaseString < __CharType >;

#if defined(CDS_QT)

                public:
                auto operator + (
                        QString const & string
                ) const noexcept -> __BaseString < __CharType >;

#endif

            public:
                template < typename __TCharType = __CharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        ElementType character
                ) const noexcept -> __BaseString < __CharType >;

            public:
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __NumericType value
                ) const noexcept -> __BaseString < __CharType >;

            public:
                auto operator + (
                        bool value
                ) const noexcept -> __BaseString < __CharType >;

            public:
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto operator + (
                        __FloatingPointType value
                ) const noexcept -> __BaseString < __CharType >;


            public:
                auto operator * (
                        int repeatCount
                ) const & noexcept -> __BaseString < __CharType >;



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
                        __CollectionType < ElementType > const & string
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
                        __CollectionType < ElementType > const & string
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
                        __CollectionType < ElementType > const & string
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
                        ElementType                 character
                ) const noexcept -> __CollectionType < Index >;


            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto find (
                        Size                          maxCount,
                        __ConvertibleType          && string,
                        __CollectionType < Index >  & storeIn
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
                        Size                        maxCount,
                        __ConvertibleType        && string
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
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto split (
                        ElementType         separator,
                        __CollectionType  & storeIn,
                        Size                maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto split (
                        ElementType     separator,
                        Size            maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString < __CharType > >;

            public:
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto split (
                        __ConvertibleType   && separators,
                        __CollectionType     & storeIn,
                        Size                   maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto split (
                        __ConvertibleType && separators,
                        Size                 maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString < __CharType > >;

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
                ) const noexcept -> __CollectionType < __BaseString < __CharType > >;

            public:
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto splitByString (
                        __ConvertibleType      && separators,
                        __CollectionType        & storeIn,
                        Size                      maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto splitByString (
                        __ConvertibleType    && separator,
                        Size                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString < __CharType > >;

            public:
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                auto splitByString (
                        __BaseStringView < __CharType > const & separator,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType &;

            public:
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_NoDiscard auto splitByString (
                        __BaseStringView < __CharType > const & separator,
                        Size                                    maxCount = limits :: U32_MAX
                ) const noexcept -> __CollectionType < __BaseString < __CharType > >;


            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index;

            public:
                __CDS_NoDiscard auto toString () const noexcept -> __BaseString < __CharType >;


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
                template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                auto forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto some (
                        Size                count,
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atLeast (
                        Size                count,
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto atMost (
                        Size                count,
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto moreThan (
                        Size                count,
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto fewerThan (
                        Size                count,
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto count (
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto any (
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto all (
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

            public:
                template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                auto none (
                        __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;


            public:
                auto sequence () const & noexcept -> Sequence < __BaseStringView < __CharType > const >;

            public:
                auto sequence () const && noexcept -> Sequence < __BaseStringView < __CharType > const >;

            };


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                         const * pLeftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                               character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                         const * pLeftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                       const * pLeftString,
                    __BaseStringView < __FCharType >  const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                         const * pLeftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                         const * pLeftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

#endif

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                         const * pLeftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> bool;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FCharType                         const * leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#if defined(CDS_QT)

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    QString                             const & leftString,
                    __BaseStringView < __FCharType >    const & rightString
            ) noexcept -> __BaseString < __FCharType >;

#endif

            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __NumericType                               value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    bool                                        value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FloatingPointType                         value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator * (
                    int                                         repeatCount,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept -> __BaseString < __FCharType >;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: wostream                        & out,
                    __BaseStringView < __FCharType > const & obj
            ) noexcept -> std :: wostream &;

            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: ostream                         & out,
                    __BaseStringView < __FCharType > const & obj
            ) noexcept -> std :: ostream &;

        }
    }
}

#endif // __CDS_BASE_STRING_VIEW_HPP__
