//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_BASE_STRING_VIEW_HPP__
#define __CDS_EX_BASE_STRING_VIEW_HPP__

namespace cds {

    template < typename C >
    class Sequence;

    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseStringView {

                public:
                    /**
                     * @brief Represents an element in the string
                     */
                    using ElementType = CharType;

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
                    constexpr BaseStringView () noexcept = default;

                public:
                    constexpr BaseStringView (
                            BaseStringView const & string
                    ) noexcept;

                public:
                    constexpr BaseStringView (
                            BaseStringView && string
                    ) noexcept;

                public:
                    __CDS_Implicit constexpr BaseStringView ( // NOLINT(google-explicit-constructor)
                            BaseString < CharType > const & string
                    ) noexcept;

                public:
                    __CDS_Implicit constexpr BaseStringView ( // NOLINT(google-explicit-constructor)
                            std :: basic_string < CharType > const & string
                    ) noexcept;

                public:
                    __CDS_Implicit constexpr BaseStringView ( // NOLINT(google-explicit-constructor)
                            std :: basic_string_view < CharType > const & string
                    ) noexcept;

                public:
                    __CDS_Implicit constexpr BaseStringView ( // NOLINT(google-explicit-constructor)
                            ElementType const * pString
                    ) noexcept;

                public:
                    constexpr BaseStringView (
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
                    __CDS_NoDiscard auto toStdString () const noexcept -> std :: basic_string < CharType >;

                public:
                    __CDS_NoDiscard constexpr auto cStr () const noexcept -> ElementType const *;

                public:
                    __CDS_NoDiscard constexpr auto data () const noexcept -> ElementType const *;


                public:
                    __CDS_Implicit operator std :: basic_string < CharType > () const noexcept; // NOLINT(google-explicit-constructor)

                public:
                    __CDS_Implicit constexpr operator ElementType const * () const noexcept; // NOLINT(google-explicit-constructor)


                public:
                    auto substr (
                            Index from,
                            Index until = -1
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator () (
                            Index from,
                            Index to = -1
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator [] (
                            Range const & range
                    ) const noexcept -> BaseString < CharType >;


                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            BaseString < CharType > const & string
                    ) noexcept -> BaseStringView &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            BaseStringView const & string
                    ) noexcept -> BaseStringView &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            BaseStringView && string
                    ) noexcept -> BaseStringView &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            std :: basic_string < CharType > const & string
                    ) noexcept -> BaseStringView &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            std :: basic_string_view < CharType > const & string
                    ) noexcept -> BaseStringView &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            ElementType const * pString
                    ) noexcept -> BaseStringView &;


                public:
                    __CDS_NoDiscard __CDS_cpplang_DynamicCastConstexpr auto equals (
                            Object const & object
                    ) const noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            BaseStringView const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator == (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            BaseStringView const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            std :: basic_string < CharType >    const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator != (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator < (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator < (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator > (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator > (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator <= (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator <= (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator >= (
                            std :: basic_string < CharType > const & string
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
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> bool;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

#endif

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            FCharType                       const * pLeftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> bool;

                public:
                    template < typename FCharType >
                    __CDS_cpplang_ConstexprConditioned friend auto operator >= (
                            FCharType                               character,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> bool;


                public:
                    auto operator + (
                            BaseStringView const & string
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            ElementType const * pString
                    ) const noexcept -> BaseString < CharType >;

#if defined(CDS_QT)

                    public:
                    auto operator + (
                            QString const & string
                    ) const noexcept -> BaseString < CharType >;

#endif

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isSame < T, uint8 > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isSame < T, uint16 > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isSame < T, sint8 > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < meta :: isSame < T, sint16 > () > = 0 >
                    auto operator + (
                            ElementType character
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > = 0 >
                    auto operator + (
                            uint8 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > = 0 >
                    auto operator + (
                            uint16 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > = 0 >
                    auto operator + (
                            sint8 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = CharType, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > = 0 >
                    auto operator + (
                            sint16 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    template < typename T = std :: size_t, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > = 0 >
                    auto operator + (
                            std :: size_t value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            bool value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            uint32 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            uint64 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            sint32 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            sint64 value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            float value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            double value
                    ) const noexcept -> BaseString < CharType >;

                public:
                    auto operator + (
                            long double value
                    ) const noexcept -> BaseString < CharType >;


                public:
                    template < typename FCharType >
                    friend auto operator + (
                            std :: basic_string < FCharType >   const & leftString,
                            BaseStringView < FCharType >        const & rightString
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            FCharType                       const * leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> BaseString < FCharType >;

#if defined(CDS_QT)

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            QString                         const & leftString,
                            BaseStringView < FCharType >    const & rightString
                    ) noexcept -> BaseString < FCharType >;

#endif

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint8 > () > >
                    friend auto operator + (
                            FCharType               character,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint16 > () > >
                    friend auto operator + (
                            FCharType               character,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint8 > () > >
                    friend auto operator + (
                            FCharType           character,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint16 > () > >
                    friend auto operator + (
                            FCharType               character,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint8 > () > >
                    friend auto operator + (
                            uint8                   value,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint16 > () > >
                    friend auto operator + (
                            uint16                  value,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint8 > () > >
                    friend auto operator + (
                            sint8                   value,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint16 > () > >
                    friend auto operator + (
                            sint16                  value,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType, typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                    friend auto operator + (
                            std :: size_t           value,
                            BaseStringView  const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            bool                                    value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            uint32                                  value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            uint64                                  value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            sint32                                  value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            sint64                                  value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            float                                   value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            double                                  value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;

                public:
                    template < typename FCharType >
                    friend auto operator + (
                            long double                             value,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;



                public:
                    auto operator * (
                            int repeatCount
                    ) const & noexcept -> BaseString < CharType >;

                public:
                    template < typename FCharType >
                    friend auto operator * (
                            int                                     repeatCount,
                            BaseStringView < FCharType >    const & string
                    ) noexcept -> BaseString < FCharType >;



                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto contains (
                            ElementType const * pString
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAnyOf (
                            CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyOf (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyOf (
                            ElementType const * string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAllOf (
                            CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllOf (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllOf (
                            ElementType const * string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAnyNotOf (
                            CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAnyNotOf (
                            ElementType const * string
                    ) const noexcept -> bool;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto containsAllNotOf (
                            CollectionType < ElementType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllNotOf (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllNotOf (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllNotOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard auto containsAllNotOf (
                            ElementType const * string
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
                    template < template < typename ... > class CollectionType >
                    auto find (
                            Size                            maxCount,
                            BaseString < CharType > const & string,
                            CollectionType < Index >      & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto find (
                            Size                            maxCount,
                            BaseString < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAll (
                            BaseString < CharType > const & string,
                            CollectionType < Index >      & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAll (
                            BaseString < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findOf (
                            Size                            maxCount,
                            BaseString < CharType > const & string,
                            CollectionType < Index >      & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findOf (
                            Size                            maxCount,
                            BaseString < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllOf (
                            BaseString < CharType > const & string,
                            CollectionType < Index >      & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllOf (
                            BaseString < CharType >          const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findNotOf (
                            Size                                maxCount,
                            BaseString < CharType >     const & string,
                            CollectionType < Index >          & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findNotOf (
                            Size                            maxCount,
                            BaseString < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                            BaseString < CharType >          const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllNotOf (
                            BaseString < CharType > const & string,
                            CollectionType < Index >      & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllNotOf (
                            BaseString < CharType > const & string
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
                    template < template < typename ... > class CollectionType >
                    auto find (
                            Size                                        maxCount,
                            std :: basic_string < CharType >    const & string,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto find (
                            Size                                     maxCount,
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAll (
                            std :: basic_string < CharType > const & string,
                            CollectionType < Index >               & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAll (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findOf (
                            Size                                     maxCount,
                            std :: basic_string < CharType > const & string,
                            CollectionType < Index >               & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findOf (
                            Size                                     maxCount,
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllOf (
                            std :: basic_string < CharType > const & string,
                            CollectionType < Index >               & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findNotOf (
                            Size                                     maxCount,
                            std :: basic_string < CharType > const & string,
                            CollectionType < Index >               & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findNotOf (
                            Size                                     maxCount,
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllNotOf (
                            std :: basic_string < CharType > const & string,
                            CollectionType < Index >               & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllNotOf (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto find (
                            Size                                        maxCount,
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto find (
                            Size                                        maxCount,
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findFirst (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto findLast (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAll (
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAll (
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findOf (
                            Size                                        maxCount,
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findOf (
                            Size                                        maxCount,
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstOf (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastOf (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllOf (
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllOf (
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < template < typename ... > class CollectionType >
                    auto findNotOf (
                            Size                                        maxCount,
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findNotOf (
                            Size                                        maxCount,
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirstNotOf (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLastNotOf (
                            ElementType                         const * pString
                    ) const noexcept -> Index;

                public:
                    template < template < typename ... > class CollectionType >
                    auto findAllNotOf (
                            ElementType                         const * pString,
                            CollectionType < Index >                  & storeIn
                    ) const noexcept -> CollectionType < Index > &;

                public:
                    template < template < typename ... > class CollectionType >
                    __CDS_NoDiscard auto findAllNotOf (
                            ElementType                         const * pString
                    ) const noexcept -> CollectionType < Index >;


                public:
                    template < typename ListType >
                    auto split (
                            ElementType     separator,
                            ListType      & storeIn,
                            Size            maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            ElementType     separator,
                            Size            maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto split (
                            BaseString < CharType >  const & separators,
                            ListType                       & storeIn,
                            Size                             maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            BaseString < CharType >  const & separators,
                            Size                             maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto split (
                            BaseStringView < CharType > const & separators,
                            ListType                          & storeIn,
                            Size                                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            BaseStringView < CharType > const & separators,
                            Size                                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto split (
                            std :: basic_string < CharType >    const & separators,
                            ListType                                  & storeIn,
                            Size                                        maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            std :: basic_string < CharType >    const & separators,
                            Size                                        maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto split (
                            CharType    const * separators,
                            ListType          & storeIn,
                            Size                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto split (
                            CharType    const * separators,
                            Size                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto splitByString (
                            BaseString < CharType >  const & separators,
                            ListType                       & storeIn,
                            Size                             maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto splitByString (
                            BaseString < CharType >  const & separators,
                            Size                             maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto splitByString (
                            BaseStringView < CharType > const & separators,
                            ListType                          & storeIn,
                            Size                                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto splitByString (
                            BaseStringView < CharType > const & separators,
                            Size                                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto splitByString (
                            std :: basic_string < CharType >    const & separators,
                            ListType                                  & storeIn,
                            Size                                        maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto splitByString (
                            std :: basic_string < CharType >    const & separators,
                            Size                                        maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;

                public:
                    template < typename ListType >
                    auto splitByString (
                            CharType    const * separators,
                            ListType          & storeIn,
                            Size                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType &;

                public:
                    template < template < typename ... > class ListType >
                    __CDS_NoDiscard auto splitByString (
                            CharType    const * separators,
                            Size                maxCount = limits :: U64_MAX
                    ) const noexcept -> ListType < BaseString < CharType > >;


                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index;

                public:
                    __CDS_NoDiscard auto toString () const noexcept -> BaseString < CharType >;


                public:
                    constexpr auto startsWith (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    constexpr auto startsWith (
                            ElementType const * pString
                    ) const noexcept -> bool;

                public:
                    constexpr auto startsWith (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    constexpr auto startsWith (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    constexpr auto startsWith (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;


                public:
                    constexpr auto endsWith (
                            ElementType character
                    ) const noexcept -> bool;

                public:
                    constexpr auto endsWith (
                            ElementType const * pString
                    ) const noexcept -> bool;

                public:
                    constexpr auto endsWith (
                            BaseString < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    constexpr auto endsWith (
                            BaseStringView < CharType > const & string
                    ) const noexcept -> bool;

                public:
                    constexpr auto endsWith (
                            std :: basic_string < CharType > const & string
                    ) const noexcept -> bool;


                public:
                    template < typename Action >
                    auto forEach (
                            Action const & action
                    ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto some (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atLeast (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto atMost (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto moreThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto fewerThan (
                            Size                count,
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto count (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto any (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto all (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;

                public:
                    template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
                    auto none (
                            Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool;


                public:
                    auto sequence () const & noexcept -> Sequence < BaseStringView const >;

                public:
                    auto sequence () const && noexcept -> Sequence < BaseStringView const >;
                };

            }
        }
    }
}

#endif // __CDS_EX_BASE_STRING_VIEW_HPP__
