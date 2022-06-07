//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__
#define __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace hidden {
            namespace impl {

                template < typename CharType >
                Index const BaseStringView < CharType > :: invalidIndex = StringUtils < CharType > :: invalidIndex;


                template < typename CharType >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        BaseStringView const & string
                ) noexcept :
                        _pData ( string._pData ),
                        _length ( string._length ) {

                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        BaseStringView && string
                ) noexcept :
                        _pData ( cds :: exchange ( string._pData, nullptr ) ),
                        _length ( cds :: exchange ( string._length, 0ULL ) ) {

                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        BaseString < CharType > const & string
                ) noexcept :
                        _pData ( string._pBuffer ),
                        _length ( string._length ) {

                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        std :: basic_string < CharType > const & string
                ) noexcept :
                        _pData ( string.c_str() ),
                        _length ( string.length() ) {

                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isStringCharType < T > () > >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        ElementType const * pString
                ) noexcept :
                        BaseStringView (
                                pString,
                                pString == nullptr ? 0ULL : StringUtils < CharType > :: length ( pString )
                        ) {

                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: BaseStringView (
                        ElementType const * pString,
                        Size                length
                ) noexcept :
                        _pData ( pString ),
                        _length ( length ) {

                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: begin () const noexcept -> ConstIterator {

                    return ConstIterator ( this, 0 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: end () const noexcept -> ConstIterator {

                    return ConstIterator ( this, this->_length );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: cbegin () const noexcept -> ConstIterator {

                    return ConstIterator ( this, 0 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: cend () const noexcept -> ConstIterator {

                    return ConstIterator ( this, this->_length );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: rbegin () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator ( this, this->_length - 1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: rend () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator ( this, -1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: crbegin () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator ( this, this->_length - 1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: crend () const noexcept -> ConstReverseIterator {

                    return ConstReverseIterator ( this, -1 );
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: length () const noexcept -> Size {

                    return this->_length;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: size () const noexcept -> Size {

                    return this->length();
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: clear () noexcept -> void {

                    this->_pData    = nullptr;
                    this->_length   = 0ULL;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: empty () const noexcept -> bool {

                    return this->_length == 0ULL;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator [] (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: at (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: get (
                        Index index
                ) const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( index, 0 );
                    }


                    if ( index < 0 ) {
                        index += ( ( -index ) / static_cast < Index > ( this->size() ) + 1) *
                                 static_cast < Index > ( this->size() );
                    }

                    if ( index >= static_cast < Index > ( this->size() ) ) {
                        index = index % static_cast < Index > ( this->size() );
                    }

                    return this->_pBuffer [ index ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: front () const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: back () const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: toStdString () const noexcept -> std :: basic_string < CharType > {

                    return std :: basic_string < CharType > ( this->_pData );
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: cStr () const noexcept -> ElementType const * {

                    return this->_pData == nullptr ? "" : this->_pData;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: data () const noexcept -> ElementType const * {

                    return this->_pData == nullptr ? "" : this->_pData;
                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: operator ElementType const * () const noexcept {

                    return this->_pData;
                }


                template < typename CharType >
                __CDS_OptimalInline BaseStringView < CharType > :: operator std :: basic_string < CharType > () const noexcept {

                    return std :: basic_string < CharType > ( this->_pData );
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseStringView < CharType > :: substr (
                        Index from,
                        Index until
                ) const noexcept -> BaseString < CharType > {

                    if ( until == -1 || until > static_cast < Index > ( this->size() ) ) {
                        until = static_cast < Index > ( this->size() );
                    }

                    if ( from < 0 ) {
                        from = 0;
                    }

                    if ( until < from ) {
                        return BaseString < CharType > ();
                    }

                    return BaseString < CharType > ( this->_pBuffer, static_cast < Size > ( until - from ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: operator () (
                        Index from,
                        Index until
                ) const noexcept -> BaseString < CharType > {

                    return this->substr ( from, until );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: operator [] (
                        Range const & range
                ) const noexcept -> BaseString < CharType > {

                    return this->substr ( range.from(), range.to() );
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        BaseString < CharType > const & string
                ) noexcept -> BaseStringView & {

                    return this->operator = ( BaseStringView ( string ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        BaseStringView const & string
                ) noexcept -> BaseStringView & {

                    if ( this->_pData == string._pData ) {
                        return * this;
                    }

                    this->_pData    = string._pData;
                    this->_length   = string._length;

                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        BaseStringView && string
                ) noexcept -> BaseStringView & {

                    if ( this->_pData == string._pData ) {
                        return * this;
                    }

                    this->_pData    = cds :: exchange ( string._pData, nullptr );
                    this->_length   = cds :: exchange ( string._length, 0ULL );

                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseStringView & {

                    return this->operator = ( BaseStringView ( string ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        ElementType const * pString
                ) noexcept -> BaseStringView & {

                    return this->operator = ( BaseStringView ( pString ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_cpplang_DynamicCastConstexpr auto BaseStringView < CharType > :: equals ( // NOLINT(bugprone-unhandled-self-assignment)
                        Object const & object
                ) const noexcept -> bool {

                    if ( this == & object ) {
                        return * this;
                    }

                    auto pView = dynamic_cast < decltype ( this ) > ( & object );
                    if ( pView == nullptr ) {
                        return false;
                    }

                    return this->operator == ( * pView );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator == (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->_pData,
                            this->length(),
                            string._pData,
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator == (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return this->operator == ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator == (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return this->operator == ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator == (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return false;
                    }

                    return this->_pData [ 0 ] == character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) == rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) == rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return string._pData [ 0 ] == character;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator != (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->_pData,
                            this->length(),
                            string._pData,
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator != (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return this->operator != ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator != (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return this->operator != ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator != (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return true;
                    }

                    return this->_pData [ 0 ] != character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) != rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) != rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return string._pData [ 0 ] != character;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator < (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->_pData,
                            this->length(),
                            string._pData,
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator < (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return this->operator < ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator < (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return this->operator < ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator < (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->empty() ) {
                        return true;
                    }

                    return this->_pData [ 0 ] < character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) < rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) < rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    if ( string.empty() ) {
                        return true;
                    }

                    if ( string.length() > 1 && character == string._pData [ 0 ] ) {
                        return true;
                    }

                    return character < string._pData [0];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator > (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->_pData,
                            this->length(),
                            string._pData,
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator > (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return this->operator > ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator > (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return this->operator > ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator > (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->empty() ) {
                        return false;
                    }

                    if ( this->length() > 1 && this->_pData [0] == character ) {
                        return true;
                    }

                    return this->_pData [ 1 ] > character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) > rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) > rightString;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    if ( string.empty() ) {
                        return false;
                    }

                    return character > string._pData [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator <= (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator <= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator <= (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return ! this->operator > ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator <= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator > ( character );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( leftString ) > rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( pLeftString ) > rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    return ! ( character > string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator >= (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator >= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator >= (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return ! this->operator < ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: operator >= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator < ( character );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( leftString ) < rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( pLeftString ) < rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        FCharType                                   character,
                        BaseStringView < FCharType >        const & string
                ) noexcept -> bool {

                    return ! ( character < string );
                }


                template < typename CharType >
                auto BaseStringView < CharType > :: operator + (
                        BaseStringView < CharType > const & string
                ) const noexcept -> BaseString < CharType > {

                    BaseString < CharType > result;

                    result._length      = this->length() + string.length();
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < CharType > ( result._capacity );

                    StringUtils < CharType > :: copy (
                            result.data(),
                            0ULL,
                            this->cStr(),
                            0ULL,
                            this->length(),
                            false
                    );

                    StringUtils < CharType > :: copy (
                            result.data(),
                            this->length(),
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    return result;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: operator + (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> BaseString < CharType > {

                    return this->operator + ( BaseStringView ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: operator + (
                        ElementType const * pString
                ) const noexcept -> BaseString < CharType > {

                    return this->operator + ( BaseStringView ( pString ) );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isStringCharType < T > () > >
                auto BaseStringView < CharType > :: operator + (
                        ElementType character
                ) const noexcept -> BaseString < CharType > {

                    BaseString < CharType > result;

                    result._length      = this->length() + 1ULL;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < CharType > ( result._capacity );

                    StringUtils < CharType > :: copy (
                            result.data(),
                            0ULL,
                            this->cStr(),
                            0ULL,
                            this->length(),
                            false
                    );

                    result._pBuffer [ result._length - 1ULL ]   = character;
                    result._pBuffer [ result._length ]          = meta :: impl :: StringData < ElementType > :: nullCharacter;

                    return result;
                }


                template < typename CharType >
                template < typename NumericType, meta :: EnableIf < meta :: isIntegralToString < CharType, NumericType > () > >
                auto BaseStringView < CharType > :: operator + (
                        NumericType value
                ) const noexcept -> BaseString < CharType > {

                    BaseString < CharType > result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result._length      = this->length() + valueLength;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < CharType > ( result._capacity );

                    StringUtils < CharType > :: copy (
                            result.data(),
                            0ULL,
                            this->_pData,
                            0ULL,
                            this->length(),
                            false
                    );

                    * StringUtils < CharType > :: writeInteger (
                            result.data(),
                            this->length(),
                            value,
                            valueLength,
                            nullptr
                    ) = meta :: impl :: StringData < ElementType > :: nullCharacter;

                    return result;
                }


                template < typename CharType >
                auto BaseStringView < CharType > :: operator + (
                        bool value
                ) const noexcept -> BaseString < CharType > {

                    BaseString < CharType > result;
                    auto valueLength = value ? 4ULL : 5ULL;

                    result._length      = this->length() + valueLength;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < CharType > ( result._capacity );

                    StringUtils < CharType > :: copy (
                            result._pBuffer,
                            0ULL,
                            this->_pData,
                            0ULL,
                            this->length(),
                            false
                    );

                    StringUtils < CharType > :: copy (
                            result._pBuffer,
                            this->length(),
                            value ? "true" : "false",
                            0ULL,
                            valueLength
                    );

                    return result;
                }


                template < typename CharType >
                template < typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: operator + (
                        FloatingPointType value
                ) const noexcept -> BaseString < CharType > {

                    return this->operator + ( BaseStringView ( std :: to_string ( value ) ) );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        std :: basic_string < FCharType >   const & leftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> BaseString < FCharType > {

                    return BaseStringView < FCharType > ( leftString ) + rightString;
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        FCharType                           const * pLeftString,
                        BaseStringView < FCharType >        const & rightString
                ) noexcept -> BaseString < FCharType > {

                    return BaseStringView < FCharType > ( pLeftString ) + rightString;
                }


                template < typename FCharType, meta :: EnableIf < meta :: isStringCharType < FCharType > () > = 0 >
                auto operator + (
                        FCharType                               character,
                        BaseStringView < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;

                    result._length      = string.length() + 1ULL;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < FCharType > ( result._capacity );

                    result._pBuffer [ 0 ] = character;

                    StringUtils < FCharType > :: copy (
                            result.data(),
                            1ULL,
                            string._pData,
                            0ULL,
                            string.length()
                    );

                    result._pBuffer [ result._length ]          = static_cast < FCharType > ( character );

                    return result;
                }


                template < typename FCharType, typename NumericType, meta :: EnableIf < meta :: isIntegralToString < FCharType, NumericType > () > = 0 >
                auto operator + (
                        NumericType                             value,
                        BaseStringView < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result._length      = string.length() + valueLength;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < FCharType > ( result._capacity );

                    (void) StringUtils < FCharType > :: writeInteger (
                            result.data(),
                            0ULL,
                            value,
                            valueLength,
                            nullptr
                    );

                    StringUtils < FCharType > :: copy (
                            result.data(),
                            valueLength,
                            string._pData,
                            0ULL,
                            string.length()
                    );

                    return result;
                }


                template < typename FCharType >
                auto operator + (
                        bool                                    value,
                        BaseStringView < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = value ? 4ULL : 5ULL;

                    result._length      = string.length() + valueLength;
                    result._capacity    = maxOf ( result._length + 1U, __allocation :: minCapacity );
                    result._pBuffer     = __allocation :: __alloc < FCharType > ( result._capacity );

                    StringUtils < FCharType > :: copy (
                            result.data (),
                            0ULL,
                            value ? "true" : "false",
                            0ULL,
                            valueLength,
                            false
                    );

                    StringUtils < FCharType > :: copy (
                            result.data(),
                            valueLength,
                            string._pData,
                            0ULL,
                            string.length(),
                            false
                    );

                    return result;
                }


                template < typename FCharType, typename FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < FloatingPointType > () > >
                __CDS_OptimalInline auto operator + (
                        FloatingPointType                       value,
                        BaseStringView < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return BaseStringView < FCharType > ( std :: to_string ( value ) ) + string;
                }


                template < typename CharType >
                auto BaseStringView < CharType > :: operator * (
                        int count
                ) const & noexcept -> BaseString < CharType > {

                    BaseString < CharType > result;

                    if ( this->empty() || count == 0 ) {
                        return result;
                    }

                    if ( count == 1 ) {
                        return * this;
                    }

                    result._capacity = maxOf ( count * this->length() + 1ULL, __allocation :: minCapacity );
                    result._pBuffer = __allocation :: __alloc < CharType > ( result._capacity );

                    for ( int i = 0; i < count; ++ i ) {
                        StringUtils < CharType > :: copy (
                                result._pBuffer,
                                result._length,
                                this->_pBuffer,
                                0ULL,
                                this->length(),
                                false
                        );

                        result._length += this->length();
                    }

                    result._pBuffer [ result._length ] = meta :: impl :: StringData < ElementType > :: nullCharacter;
                    return result;
                }


                template < typename FCharType >
                auto operator * (
                        int                                  count,
                        BaseStringView < FCharType > const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;

                    if ( string.empty() || count == 0 ) {
                        return result;
                    }

                    if ( count == 1 ) {
                        return * string;
                    }

                    result._capacity = maxOf ( count * string.length() + 1ULL, __allocation :: minCapacity );
                    result._pBuffer = __allocation :: __alloc < FCharType > ( result._capacity );

                    for ( int i = 0; i < count; ++ i ) {
                        StringUtils < FCharType > :: copy (
                                result._pBuffer,
                                result._length,
                                string._pBuffer,
                                0ULL,
                                string.length(),
                                false
                        );

                        result._length += string.length();
                    }

                    result._pBuffer [ result._length ] = static_cast < FCharType > ( '\0' );
                    return result;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: contains (
                        ElementType character
                ) const noexcept -> bool {

                    return this->findFirst ( character ) != BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: contains (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->contains ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: contains (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return this->findFirst ( string ) != BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptionalInline auto BaseStringView < CharType > :: containsAnyOf (
                        CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( characters.contains ( this->_pData [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAnyOf (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->containsAnyOf ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAnyOf (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptionalInline auto BaseStringView < CharType > :: containsAllOf (
                        CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! characters.contains ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAllOf (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->containsAllOf ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAllOf (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptionalInline auto BaseStringView < CharType > :: containsAnyNotOf (
                        CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! characters.contains ( this->_pData [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAnyNotOf (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->containsAnyNotOf ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAnyNotOf (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptionalInline auto BaseStringView < CharType > :: containsAllNotOf (
                        CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( characters.contains ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAllNotOf (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->containsAllNotOf ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: containsAllNotOf (
                        BaseStringView const & string
                ) const noexcept -> bool {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseStringView < CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character,
                        CollectionType < Index >  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->_length && found < maxCount; ++ index ) {
                        if ( this->_pBuffer [ index ] == character ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find (
                            maxCount,
                            character,
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findFirst (
                        ElementType character
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( this->_pData [ index ] == character ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findLast (
                        ElementType character
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->_length ) - 1; index >= 0; -- index ) {
                        if ( this->_pData [ index ] == character ) {
                            return index;
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseStringView < CharType > :: findAll (
                        ElementType                 character,
                        CollectionType < Index >  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( this->_pData [ index ] == character ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAll (
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll (
                            character,
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: find (
                        Size                                maxCount,
                        ConvertibleType                  && string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->find (
                            maxCount,
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: find (
                        Size                                maxCount,
                        ConvertibleType                  && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: findFirst (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findFirst ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: findLast (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findLast ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAll (
                        ConvertibleType                  && string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->findAll (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAll (
                        ConvertibleType && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findOf (
                        Size                            maxCount,
                        ConvertibleType              && string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->findOf (
                            maxCount,
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                    template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findOf (
                        Size                            maxCount,
                        ConvertibleType              && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf (
                            maxCount,
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findFirstOf (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findFirstOf ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findLastOf (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findLastOf ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllOf (
                        ConvertibleType              && string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->findAllOf (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllOf (
                        ConvertibleType && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findNotOf (
                        Size                            maxCount,
                        ConvertibleType              && string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->findNotOf (
                            maxCount,
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findNotOf (
                        Size                            maxCount,
                        ConvertibleType              && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf (
                            maxCount,
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findFirstNotOf (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findFirstNotOf ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findLastNotOf (
                        ConvertibleType && string
                ) const noexcept -> Index {

                    return this->findLastNotOf ( BaseStringView ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllNotOf (
                        ConvertibleType              && string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return this->findAllNotOf (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllNotOf (
                        ConvertibleType && string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf (
                            BaseStringView ( std :: forward < ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: find (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: find (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length(),
                            maxCount,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: find (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: findFirst (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findFirst (
                            this->_pData,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseStringView < CharType > :: findLast (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findLast (
                            this->_pData,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAll (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: findAll (
                            this->_pData,
                            this->_length,
                            string.cStr(),
                            string.length(),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAll (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findFirstOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findLastOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseStringView < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pData [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseStringView < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findFirstNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: findLastNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseStringView :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseStringView < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pData [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf ( string, indices );
                }


                template < typename CharType >
                template < typename ListType >
                auto BaseStringView < CharType > :: split (
                        ElementType     separator,
                        ListType      & storeIn,
                        Size            maxCount
                ) const noexcept -> ListType & {

                    Index splitIndex = 0;
                    if ( this->empty() ) {
                        return storeIn;
                    }

                    Index   currentSegmentOffset    = 0;
                    Size    currentSegmentLength    = 0ULL;

                    for ( Index index = 0ULL; index < static_cast < Index > ( this->length() ); ++ index ) {
                        if ( this->_pData [ index ] != separator || splitIndex >= static_cast < Index > ( maxCount ) - 1 ) {
                            ++ currentSegmentLength;
                        } else {

                            if ( currentSegmentLength == 0ULL ) {
                                continue;
                            }

                            ++ splitIndex;
                            storeIn.add ( BaseString < CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                            currentSegmentLength = 0ULL;
                            currentSegmentOffset = index + 1;
                        }
                    }

                    if ( currentSegmentLength != 0ULL ) {
                        storeIn.add ( BaseString < CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: split (
                        ElementType separator,
                        Size        maxCount
                ) const noexcept -> ListType < BaseString < CharType > > {

                    ListType < BaseString < CharType > > tokens;
                    return this->split (
                            separator,
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: split (
                        ConvertibleType             && separators,
                        ListType                      & storeIn,
                        Size                            maxCount
                ) const noexcept -> ListType & {

                    return this->split (
                            BaseStringView ( std :: forward < ConvertibleType > ( separators ) ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: split (
                        ConvertibleType              && separators,
                        Size                            maxCount
                ) const noexcept -> ListType < BaseString < CharType > > {

                    ListType < BaseString < CharType > > tokens;
                    return this->split (
                            BaseStringView ( std :: forward < ConvertibleType > ( separators ) ),
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                auto BaseStringView < CharType > :: split (
                        BaseStringView < CharType > const & separators,
                        ListType                          & storeIn,
                        Size                                maxCount
                ) const noexcept -> ListType & {

                    Index splitIndex = 0;
                    if ( this->empty() ) {
                        return storeIn;
                    }

                    Index   currentSegmentOffset    = 0;
                    Size    currentSegmentLength    = 0ULL;

                    for ( Index index = 0ULL; index < static_cast < Index > ( this->length() ); ++ index ) {
                        if ( ! separators.contains ( this->_pData [ index ] ) || splitIndex >= static_cast < Index > ( maxCount ) - 1 ) {
                            ++ currentSegmentLength;
                        } else {

                            if ( currentSegmentLength == 0ULL ) {
                                currentSegmentOffset = index + 1;
                                continue;
                            }

                            ++ splitIndex;
                            storeIn.add ( BaseString < CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                            currentSegmentLength = 0ULL;
                            currentSegmentOffset = index + 1;
                        }
                    }

                    if ( currentSegmentLength != 0ULL ) {
                        storeIn.add ( BaseString < CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: split (
                        BaseStringView < CharType > const & separators,
                        Size                                maxCount
                ) const noexcept -> ListType < BaseString < CharType > > {

                    ListType < BaseString < CharType > > tokens;
                    return this->split (
                            separators,
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: splitByString (
                        ConvertibleType && separator,
                        ListType         & storeIn,
                        Size               maxCount
                ) const noexcept -> ListType & {

                    return this->splitByString (
                            BaseStringView < CharType > ( std :: forward < ConvertibleType > ( separator ) ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ...> class ListType, typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_OptimalInline auto BaseStringView < CharType > :: splitByString (
                        ConvertibleType && separator,
                        Size               maxCount
                ) const noexcept -> ListType < BaseString < CharType > > {

                    ListType < BaseString < CharType > > list;
                    return this->splitByString (
                            BaseStringView < CharType > ( std :: forward < ConvertibleType > ( separator ) ),
                            list,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                auto BaseStringView < CharType > :: splitByString (
                        BaseStringView < CharType > const & separator,
                        ListType                          & storeIn,
                        Size                                maxCount
                ) const noexcept -> ListType & {

                    if ( separator.empty() ) {
                        return storeIn;
                    }

                    auto separatorPredictiveCount = this->count ([first = separator[0]]( char character ) noexcept -> bool {
                        return character == first;
                    });

                    Index * pOccurrences = __allocation :: __alloc < Index > ( separatorPredictiveCount );

                    auto actualSeparatorCount = StringUtils < CharType > :: findAll (
                            this->_pData,
                            this->_length,
                            separator._pData,
                            separator._length,
                            pOccurrences,
                            separatorPredictiveCount
                    );

                    Size tokenOffset        = 0ULL;
                    Size addedTokenCount    = 0ULL;

                    for ( Size currentSeparatorIndex = 0ULL; currentSeparatorIndex < actualSeparatorCount; ++ currentSeparatorIndex ) {

                        if ( tokenOffset < pOccurrences [ currentSeparatorIndex ] ) {

                            if ( addedTokenCount < maxCount ) {
                                ++ addedTokenCount;
                                storeIn.add (
                                        BaseString < CharType > (
                                                this->_pData + tokenOffset,
                                                static_cast < Size > ( pOccurrences [ currentSeparatorIndex ] )
                                        )
                                );
                            } else {
                                break;
                            }

                            while (
                                    currentSeparatorIndex < actualSeparatorCount &&
                                    pOccurrences [ currentSeparatorIndex ] + separator._length <= pOccurrences [ currentSeparatorIndex + 1 ]
                            ) {
                                currentSeparatorIndex ++;
                                tokenOffset = pOccurrences [ currentSeparatorIndex ] + separator._length;
                            }
                        }
                    }

                    __allocation :: __free ( pOccurrences );
                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                auto BaseStringView < CharType > :: splitByString (
                        BaseStringView < CharType > const & separator,
                        Size                                maxCount
                ) const noexcept -> ListType < BaseString < CharType > > {

                    ListType < BaseString < CharType > > tokens;
                    return this->splitByString (
                            separator,
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprOverride auto BaseStringView < CharType > :: hash () const noexcept -> Index {

                    Size finalHash = 0;

                    if ( ! this->empty() ) {
                        finalHash += ( this->_length & 0xFF00U ) + ( this->_pData [ 0 ] & 0xFFU );
                    }

                    Size shlOffset  = 4ULL;
                    Size shlMask    = 0xFFULL;

                    while ( ( shlOffset < 56ULL ) && ( shlOffset >> 2ULL ) < this->length() ) {

                        finalHash |= ( ( static_cast < Size > ( this->_pData [ shlOffset >> 2ULL ] ) & shlMask ) << shlOffset );
                        shlOffset += 2ULL;
                    }

                    return static_cast < Index > ( finalHash );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: toString () const noexcept -> BaseString < CharType > {
                    return BaseString < CharType > ( this->_pData, this->_length );
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: startsWith (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->empty() && this->_pData [ 0 ] == character;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: startsWith (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->startsWith ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: startsWith (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    Size offset = 0ULL;
                    for ( auto minLength = minOf ( this->_length, string._length ); offset < minLength; ++ offset ) {
                        if ( this->_pData [ offset ] != string._pData [ offset ] ) {
                            return false;
                        }
                    }

                    return offset == string._length;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: endsWith (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->empty() && this->_pData [ this->_length - 1ULL ] == character;
                }


                template < typename CharType >
                template < typename ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < ConvertibleType, CharType > () > >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: endsWith (
                        ConvertibleType && string
                ) const noexcept -> bool {

                    return this->endsWith ( BaseStringView < CharType > ( std :: forward < ConvertibleType > ( string ) ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseStringView < CharType > :: endsWith (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    Size offset = 0;
                    for ( auto minLength = minOf ( this->_length, string._length ); offset < minLength; ++ offset ) {
                        if ( this->_pData [ this->_length - offset ] != string._pData [ string._length - offset ] ) {
                            return false;
                        }
                    }

                    return offset == string._length;
                }


                template < typename CharType >
                template < typename Action >
                auto BaseStringView < CharType > :: forEach (
                        Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pData [ index ] );
                    }
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: some (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return trueCount == count;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: atLeast (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount >= count ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: atMost (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            ++ trueCount;
                        }

                        if ( trueCount > count ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseStringView < CharType > :: moreThan (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atLeast ( count + 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseStringView < CharType > :: fewerThan (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atMost ( count - 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: count (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size {

                    Size trueCount = 0U;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: any (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: all (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( ! predicate ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseStringView < CharType > :: none (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pData [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename FCharType >
                auto operator << (
                        std :: wostream                    & out,
                        BaseStringView < FCharType > const & obj
                ) noexcept -> std :: wostream & {
                    return ( out << obj.cStr() );
                }

            }
        }
    }
}


#endif // __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__
