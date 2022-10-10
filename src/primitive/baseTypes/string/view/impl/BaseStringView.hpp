//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_BASE_STRING_VIEW_IMPL_HPP__
#define __CDS_BASE_STRING_VIEW_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            Index const __BaseStringView < __CharType > :: invalidIndex = StringUtils < __CharType > :: invalidIndex;


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                    __BaseStringView const & string
            ) noexcept :
                    _pData ( string._pData ),
                    _length ( string._length ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                    __BaseStringView && string
            ) noexcept :
                    _pData ( cds :: exchange ( string._pData, nullptr ) ),
                    _length ( cds :: exchange ( string._length, 0ULL ) ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                   __BaseString < __CharType > const & string
            ) noexcept :
                    _pData ( string._pBuffer ),
                    _length ( string._length ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                    std :: basic_string < __CharType > const & string
            ) noexcept :
                    _pData ( string.c_str() ),
                    _length ( string.length() ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                    ElementType const * pString
            ) noexcept :
                    __BaseStringView (
                            pString,
                            pString == nullptr ? 0ULL : StringUtils < __CharType > :: length ( pString )
                    ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: __BaseStringView (
                    ElementType const * pString,
                    Size                length
            ) noexcept :
                    _pData ( pString ),
                    _length ( length ) {

            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: begin () const noexcept -> ConstIterator {

                return ConstIterator ( this, 0 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: end () const noexcept -> ConstIterator {

                return ConstIterator ( this, this->_length );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: cbegin () const noexcept -> ConstIterator {

                return ConstIterator ( this, 0 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: cend () const noexcept -> ConstIterator {

                return ConstIterator ( this, this->_length );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: rbegin () const noexcept -> ConstReverseIterator {

                return ConstReverseIterator ( this, this->_length - 1 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: rend () const noexcept -> ConstReverseIterator {

                return ConstReverseIterator ( this, -1 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: crbegin () const noexcept -> ConstReverseIterator {

                return ConstReverseIterator ( this, this->_length - 1 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: crend () const noexcept -> ConstReverseIterator {

                return ConstReverseIterator ( this, -1 );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: length () const noexcept -> Size {

                return this->_length;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: size () const noexcept -> Size {

                return this->length();
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: clear () noexcept -> void {

                this->_pData    = nullptr;
                this->_length   = 0ULL;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: empty () const noexcept -> bool {

                return this->_length == 0ULL;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator [] (
                    Index index
            ) const noexcept (false) -> ElementType {

                return this->get ( index );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: at (
                    Index index
            ) const noexcept (false) -> ElementType {

                return this->get ( index );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: get (
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

                return this->_pData [ index ];
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: front () const noexcept (false) -> ElementType {

                if ( this->empty() ) {
                    throw OutOfBoundsException ( 0, 0 );
                }

                return this->_pData [ 0 ];
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: back () const noexcept (false) -> ElementType {

                if ( this->empty() ) {
                    throw OutOfBoundsException ( 0, 0 );
                }

                return this->_pData [ this->_length - 1U ];
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: toStdString () const noexcept -> std :: basic_string < __CharType > {

                return std :: basic_string < __CharType > ( this->_pData );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: cStr () const noexcept -> ElementType const * {

                return this->_pData == nullptr ? meta :: __impl :: __StringData < __CharType > :: emptyString : this->_pData;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: data () const noexcept -> ElementType const * {

                return this->_pData == nullptr ? meta :: __impl :: __StringData < __CharType > :: emptyString : this->_pData;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseStringView < __CharType > :: operator ElementType const * () const noexcept {

                return this->_pData;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline __BaseStringView < __CharType > :: operator std :: basic_string < __CharType > () const noexcept {

                return std :: basic_string < __CharType > ( this->_pData );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptionalInline auto __BaseStringView < __CharType > :: substr (
                    Index from,
                    Index until
            ) const noexcept ->__BaseString < __CharType > {

                if ( until == -1 || until > static_cast < Index > ( this->size() ) ) {
                    until = static_cast < Index > ( this->size() );
                }

                if ( from < 0 ) {
                    from = 0;
                }

                if ( until < from ) {
                    return __BaseString < __CharType > ();
                }

                return __BaseString < __CharType > ( this->_pData, static_cast < Size > ( until - from ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: operator () (
                    Index from,
                    Index until
            ) const noexcept ->__BaseString < __CharType > {

                return this->substr ( from, until );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __RangeType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: operator [] (
                    __RangeType const & range
            ) const noexcept ->__BaseString < __CharType > {

                return this->substr ( range.from(), range.to() );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                   __BaseString < __CharType > const & string
            ) noexcept -> __BaseStringView & {

                return this->operator = ( __BaseStringView ( string ) ); // NOLINT(misc-unconventional-assign-operator)
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                    __BaseStringView const & string
            ) noexcept -> __BaseStringView & {

                if ( this->_pData == string._pData ) {
                    return * this;
                }

                this->_pData    = string._pData;
                this->_length   = string._length;

                return * this;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                    __BaseStringView && string
            ) noexcept -> __BaseStringView & {

                if ( this->_pData == string._pData ) {
                    return * this;
                }

                this->_pData    = cds :: exchange ( string._pData, nullptr );
                this->_length   = cds :: exchange ( string._length, 0ULL );

                return * this;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                    std :: basic_string < __CharType > const & string
            ) noexcept -> __BaseStringView & {

                return this->operator = ( __BaseStringView ( string ) ); // NOLINT(misc-unconventional-assign-operator)
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                    ElementType const * pString
            ) noexcept -> __BaseStringView & {

                return this->operator = ( __BaseStringView ( pString ) ); // NOLINT(misc-unconventional-assign-operator)
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_DynamicCastConstexpr auto __BaseStringView < __CharType > :: equals ( // NOLINT(bugprone-unhandled-self-assignment)
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


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator == (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                if ( this->length() != string.length() ) {
                    return false;
                }

                return StringUtils < __CharType > :: compare (
                        this->_pData,
                        this->length(),
                        string._pData,
                        string.length()
                ) == StringUtils < __CharType > :: equal;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator == (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return this->operator == ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator == (
                    ElementType const * pString
            ) const noexcept -> bool {

                return this->operator == ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator == (
                    ElementType character
            ) const noexcept -> bool {

                if ( this->length() != 1ULL ) {
                    return false;
                }

                return this->_pData [ 0 ] == character;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( leftString ) == rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( pLeftString ) == rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator == (
                    __FCharType                                   character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                if ( string.length() != 1ULL ) {
                    return false;
                }

                return string.cStr() [ 0 ] == character;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator != (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                if ( this->length() != string.length() ) {
                    return true;
                }

                return StringUtils < __CharType > :: compare (
                        this->_pData,
                        this->length(),
                        string._pData,
                        string.length()
                ) != StringUtils < __CharType > :: equal;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator != (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return this->operator != ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator != (
                    ElementType const * pString
            ) const noexcept -> bool {

                return this->operator != ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator != (
                    ElementType character
            ) const noexcept -> bool {

                if ( this->length() != 1ULL ) {
                    return true;
                }

                return this->_pData [ 0 ] != character;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( leftString ) != rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( pLeftString ) != rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator != (
                    __FCharType                                     character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                if ( string.length() != 1ULL ) {
                    return true;
                }

                return string.cStr() [ 0 ] != character;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator < (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                return StringUtils < __CharType > :: compare (
                        this->_pData,
                        this->length(),
                        string._pData,
                        string.length()
                ) == StringUtils < __CharType > :: lesser;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator < (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return this->operator < ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator < (
                    ElementType const * pString
            ) const noexcept -> bool {

                return this->operator < ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator < (
                    ElementType character
            ) const noexcept -> bool {

                if ( this->empty() ) {
                    return true;
                }

                return this->_pData [ 0 ] < character;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( leftString ) < rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( pLeftString ) < rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator < (
                    __FCharType                                   character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                if ( string.empty() ) {
                    return true;
                }

                if ( string.length() > 1 && character == string.cStr() [ 0 ] ) {
                    return true;
                }

                return character < string.cStr() [0];
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator > (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                return StringUtils < __CharType > :: compare (
                        this->_pData,
                        this->length(),
                        string._pData,
                        string.length()
                ) == StringUtils < __CharType > :: greater;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator > (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return this->operator > ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator > (
                    ElementType const * pString
            ) const noexcept -> bool {

                return this->operator > ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator > (
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


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( leftString ) > rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return __BaseStringView < __FCharType > ( pLeftString ) > rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator > (
                    __FCharType                                     character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                if ( string.empty() ) {
                    return false;
                }

                return character > string.cStr() [ 0 ];
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator <= (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                return ! this->operator > ( string );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator <= (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return ! this->operator > ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator <= (
                    ElementType const * pString
            ) const noexcept -> bool {

                return ! this->operator > ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator <= (
                    ElementType character
            ) const noexcept -> bool {

                return ! this->operator > ( character );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return ! ( __BaseStringView < __FCharType > ( leftString ) > rightString );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return ! ( __BaseStringView < __FCharType > ( pLeftString ) > rightString );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator <= (
                    __FCharType                                     character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                return ! ( character > string );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator >= (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                return ! this->operator < ( string );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator >= (
                    std :: basic_string < __CharType > const & string
            ) const noexcept -> bool {

                return ! this->operator < ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator >= (
                    ElementType const * pString
            ) const noexcept -> bool {

                return ! this->operator < ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: operator >= (
                    ElementType character
            ) const noexcept -> bool {

                return ! this->operator < ( character );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return ! ( __BaseStringView < __FCharType > ( leftString ) < rightString );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept -> bool {

                return ! ( __BaseStringView < __FCharType > ( pLeftString ) < rightString );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto operator >= (
                    __FCharType                                     character,
                    __BaseStringView < __FCharType >        const & string
            ) noexcept -> bool {

                return ! ( character < string );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: operator + (
                    __BaseStringView < __CharType > const & string
            ) const noexcept ->__BaseString < __CharType > {

                __BaseString < __CharType > result;

                result._length      = this->length() + string.length();
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __CharType > ( result._capacity );

                StringUtils < __CharType > :: copy (
                        result.data(),
                        0ULL,
                        this->cStr(),
                        0ULL,
                        this->length(),
                        false
                );

                StringUtils < __CharType > :: copy (
                        result.data(),
                        this->length(),
                        string.cStr(),
                        0ULL,
                        string.length()
                );

                return result;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: operator + (
                    std :: basic_string < __CharType > const & string
            ) const noexcept ->__BaseString < __CharType > {

                return this->operator + ( __BaseStringView ( string ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: operator + (
                    ElementType const * pString
            ) const noexcept ->__BaseString < __CharType > {

                return this->operator + ( __BaseStringView ( pString ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: operator + (
                    ElementType character
            ) const noexcept -> __BaseString < __CharType > {

                __BaseString < __CharType > result;

                result._length      = this->length() + 1ULL;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __CharType > ( result._capacity );

                StringUtils < __CharType > :: copy (
                        result.data(),
                        0ULL,
                        this->cStr(),
                        0ULL,
                        this->length(),
                        false
                );

                result._pBuffer [ result._length - 1ULL ]   = character;
                result._pBuffer [ result._length ]          = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                return result;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: operator + (
                    __NumericType value
            ) const noexcept ->__BaseString < __CharType > {

                __BaseString < __CharType > result;
                auto valueLength = StringUtils < __CharType > :: integerLength ( value );

                result._length      = this->length() + valueLength;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __CharType > ( result._capacity );

                StringUtils < __CharType > :: copy (
                        result.data(),
                        0ULL,
                        this->_pData,
                        0ULL,
                        this->length(),
                        false
                );

                * StringUtils < __CharType > :: writeInteger (
                        result.data(),
                        this->length(),
                        value,
                        valueLength,
                        nullptr
                ) = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                return result;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: operator + (
                    bool value
            ) const noexcept ->__BaseString < __CharType > {

                __BaseString < __CharType > result;
                auto valueLength = value ? 4ULL : 5ULL;

                result._length      = this->length() + valueLength;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __CharType > ( result._capacity );

                StringUtils < __CharType > :: copy (
                        result._pBuffer,
                        0ULL,
                        this->_pData,
                        0ULL,
                        this->length(),
                        false
                );

                StringUtils < __CharType > :: copy (
                        result._pBuffer,
                        this->length(),
                        value ? "true" : "false",
                        0ULL,
                        valueLength
                );

                return result;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: operator + (
                    __FloatingPointType value
            ) const noexcept ->__BaseString < __CharType > {

                return this->operator + ( __BaseStringView ( std :: to_string ( value ) ) );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto operator + (
                    std :: basic_string < __FCharType >     const & leftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept ->__BaseString < __FCharType > {

                return __BaseStringView < __FCharType > ( leftString ) + rightString;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto operator + (
                    __FCharType                             const * pLeftString,
                    __BaseStringView < __FCharType >        const & rightString
            ) noexcept ->__BaseString < __FCharType > {

                return __BaseStringView < __FCharType > ( pLeftString ) + rightString;
            }


            template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __FCharType                                 character,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept ->__BaseString < __FCharType > {

               __BaseString < __FCharType > result;

                result._length      = string.length() + 1ULL;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __FCharType > ( result._capacity );

                result._pBuffer [ 0 ] = character;

                StringUtils < __FCharType > :: copy (
                        result.data(),
                        1ULL,
                        string.cStr(),
                        0ULL,
                        string.length()
                );

                result._pBuffer [ result._length ]          = static_cast < __FCharType > ( character );

                return result;
            }


            template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    __NumericType                               value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept ->__BaseString < __FCharType > {

               __BaseString < __FCharType > result;
                auto valueLength = StringUtils < __FCharType > :: integerLength ( value );

                result._length      = string.length() + valueLength;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __FCharType > ( result._capacity );

                (void) StringUtils < __FCharType > :: writeInteger (
                        result.data(),
                        0ULL,
                        value,
                        valueLength,
                        nullptr
                );

                StringUtils < __FCharType > :: copy (
                        result.data(),
                        valueLength,
                        string.cStr(),
                        0ULL,
                        string.length()
                );

                return result;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator + (
                    bool                                        value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept ->__BaseString < __FCharType > {

               __BaseString < __FCharType > result;
                auto valueLength = value ? 4ULL : 5ULL;

                result._length      = string.length() + valueLength;
                result._capacity    = maxOf ( result._length + 1U, __allocation :: __minCapacity );
                result._pBuffer     = __allocation :: __alloc < __FCharType > ( result._capacity );

                StringUtils < __FCharType > :: copy (
                        result.data (),
                        0ULL,
                        value ? "true" : "false",
                        0ULL,
                        valueLength,
                        false
                );

                StringUtils < __FCharType > :: copy (
                        result.data(),
                        valueLength,
                        string.cStr(),
                        0ULL,
                        string.length(),
                        false
                );

                return result;
            }


            template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto operator + (
                    __FloatingPointType                         value,
                    __BaseStringView < __FCharType >    const & string
            ) noexcept ->__BaseString < __FCharType > {

                return __BaseStringView < __FCharType > ( std :: to_string ( value ) ) + string;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: operator * (
                    int count
            ) const & noexcept ->__BaseString < __CharType > {

               __BaseString < __CharType > result;

                if ( this->empty() || count == 0 ) {
                    return result;
                }

                if ( count == 1 ) {
                    return * this;
                }

                result._capacity = maxOf ( count * this->length() + 1ULL, __allocation :: __minCapacity );
                result._pBuffer = __allocation :: __alloc < __CharType > ( result._capacity );

                for ( int i = 0; i < count; ++ i ) {
                    StringUtils < __CharType > :: copy (
                            result._pBuffer,
                            result._length,
                            this->_pData,
                            0ULL,
                            this->length(),
                            false
                    );

                    result._length += this->length();
                }

                result._pBuffer [ result._length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                return result;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator * (
                    int                                      count,
                    __BaseStringView < __FCharType > const & string
            ) noexcept ->__BaseString < __FCharType > {

               __BaseString < __FCharType > result;

                if ( string.empty() || count == 0 ) {
                    return result;
                }

                if ( count == 1 ) {
                    return * string;
                }

                result._capacity = maxOf ( count * string.length() + 1ULL, __allocation :: __minCapacity );
                result._pBuffer = __allocation :: __alloc < __FCharType > ( result._capacity );

                for ( int i = 0; i < count; ++ i ) {
                    StringUtils < __FCharType > :: copy (
                            result._pBuffer,
                            result._length,
                            string.cStr(),
                            0ULL,
                            string.length(),
                            false
                    );

                    result._length += string.length();
                }

                result._pBuffer [ result._length ] = static_cast < __FCharType > ( '\0' );
                return result;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: contains (
                    ElementType character
            ) const noexcept -> bool {

                return this->findFirst ( character ) != __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: contains (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->contains ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: contains (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> bool {

                return this->findFirst ( string ) != __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptionalInline auto __BaseStringView < __CharType > :: containsAnyOf (
                    __CollectionType < ElementType > const & characters
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( characters.contains ( this->_pData [ index ] ) ) {
                        return true;
                    }
                }

                return false;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAnyOf (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->containsAnyOf ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAnyOf (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        return true;
                    }
                }

                return false;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptionalInline auto __BaseStringView < __CharType > :: containsAllOf (
                    __CollectionType < ElementType > const & characters
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! characters.contains ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAllOf (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->containsAllOf ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAllOf (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptionalInline auto __BaseStringView < __CharType > :: containsAnyNotOf (
                    __CollectionType < ElementType > const & characters
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! characters.contains ( this->_pData [ index ] ) ) {
                        return true;
                    }
                }

                return false;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAnyNotOf (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->containsAnyNotOf ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAnyNotOf (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        return true;
                    }
                }

                return false;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptionalInline auto __BaseStringView < __CharType > :: containsAllNotOf (
                    __CollectionType < ElementType > const & characters
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( characters.contains ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAllNotOf (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->containsAllNotOf ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: containsAllNotOf (
                    __BaseStringView const & string
            ) const noexcept -> bool {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: find (
                    Size                          maxCount,
                    ElementType                   character,
                    __CollectionType < Index >  & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                Size found = 0ULL;
                for ( Size index = 0ULL; index < this->_length && found < maxCount; ++ index ) {
                    if ( this->_pData [ index ] == character ) {
                        storeIn.add ( static_cast < Index > ( index ) );
                        ++ found;
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: find (
                    Size                        maxCount,
                    ElementType                 character
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->find (
                        maxCount,
                        character,
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findFirst (
                    ElementType character
            ) const noexcept -> Index {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( this->_pData [ index ] == character ) {
                        return static_cast < Index > ( index );
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findLast (
                    ElementType character
            ) const noexcept -> Index {

                for ( Index index = static_cast < Index > ( this->_length ) - 1; index >= 0; -- index ) {
                    if ( this->_pData [ index ] == character ) {
                        return index;
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: findAll (
                    ElementType                 character,
                    __CollectionType < Index >  & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( this->_pData [ index ] == character ) {
                        storeIn.insert ( static_cast < Index > ( index ) );
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAll (
                    ElementType                 character
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAll (
                        character,
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: find (
                    Size                                  maxCount,
                    __ConvertibleType                  && string,
                    __CollectionType < Index >          & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->find (
                        maxCount,
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: find (
                    Size                                  maxCount,
                    __ConvertibleType                  && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->find (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: findFirst (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findFirst ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: findLast (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findLast ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAll (
                    __ConvertibleType                  && string,
                    __CollectionType < Index >          & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->findAll (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAll (
                    __ConvertibleType && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAll (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findOf (
                    Size                            maxCount,
                    __ConvertibleType              && string,
                    __CollectionType < Index >      & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->findOf (
                        maxCount,
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findOf (
                    Size                              maxCount,
                    __ConvertibleType              && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findOf (
                        maxCount,
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findFirstOf (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findFirstOf ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findLastOf (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findLastOf ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllOf (
                    __ConvertibleType              && string,
                    __CollectionType < Index >      & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->findAllOf (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllOf (
                    __ConvertibleType && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAllOf (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findNotOf (
                    Size                              maxCount,
                    __ConvertibleType              && string,
                    __CollectionType < Index >      & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->findNotOf (
                        maxCount,
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findNotOf (
                    Size                              maxCount,
                    __ConvertibleType              && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findNotOf (
                        maxCount,
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findFirstNotOf (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findFirstNotOf ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findLastNotOf (
                    __ConvertibleType && string
            ) const noexcept -> Index {

                return this->findLastNotOf ( __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllNotOf (
                    __ConvertibleType              && string,
                    __CollectionType < Index >      & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return this->findAllNotOf (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllNotOf (
                    __ConvertibleType && string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAllNotOf (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( string ) ),
                        indices
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: find (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return StringUtils < __CharType > :: find (
                        this->_pData,
                        this->_length,
                        string.cStr(),
                        string.length(),
                        maxCount,
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: find (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->find ( maxCount, string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: findFirst (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                return StringUtils < __CharType > :: findFirst (
                        this->_pData,
                        this->_length,
                        string.cStr(),
                        string.length()
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprDynamicAllocation auto __BaseStringView < __CharType > :: findLast (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                return StringUtils < __CharType > :: findLast (
                        this->_pData,
                        this->_length,
                        string.cStr(),
                        string.length()
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAll (
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                return StringUtils < __CharType > :: findAll (
                        this->_pData,
                        this->_length,
                        string.cStr(),
                        string.length(),
                        storeIn
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAll (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAll ( string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findOf (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                Size found = 0ULL;
                for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        storeIn.insert ( static_cast < Index > ( index ) );
                        ++ found;
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findOf (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findOf ( maxCount, string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findFirstOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        return static_cast < Index > ( index );
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findLastOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        return static_cast < Index > ( index );
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: findAllOf (
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( string.contains ( this->_pData [ index ] ) ) {
                        storeIn.insert ( static_cast < Index > ( index ) );
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAllOf ( string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: findNotOf (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                Size found = 0ULL;
                for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        storeIn.insert ( static_cast < Index > ( index ) );
                        ++ found;
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findNotOf (
                    Size                                    maxCount,
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findNotOf ( maxCount, string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findFirstNotOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        return static_cast < Index > ( index );
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: findLastNotOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> Index {

                for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        return static_cast < Index > ( index );
                    }
                }

                return __BaseStringView :: invalidIndex;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: findAllNotOf (
                    __BaseStringView < __CharType > const & string,
                    __CollectionType < Index >            & storeIn
            ) const noexcept -> __CollectionType < Index > & {

                for ( Size index = 0ULL; index < this->length(); ++ index ) {
                    if ( ! string.contains ( this->_pData [ index ] ) ) {
                        storeIn.insert ( static_cast < Index > ( index ) );
                    }
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: findAllNotOf (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> __CollectionType < Index > {

                __CollectionType < Index > indices;
                return this->findAllNotOf ( string, indices );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: split (
                    ElementType             separator,
                    __CollectionType      & storeIn,
                    Size                    maxCount
            ) const noexcept -> __CollectionType & {

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
                        storeIn.insert (__BaseString < __CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                        currentSegmentLength = 0ULL;
                        currentSegmentOffset = index + 1;
                    }
                }

                if ( currentSegmentLength != 0ULL ) {
                    storeIn.insert (__BaseString < __CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: split (
                    ElementType separator,
                    Size        maxCount
            ) const noexcept -> __CollectionType <__BaseString < __CharType > > {

                __CollectionType <__BaseString < __CharType > > tokens;
                return this->split (
                        separator,
                        tokens,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: split (
                    __ConvertibleType             && separators,
                    __CollectionType               & storeIn,
                    Size                             maxCount
            ) const noexcept -> __CollectionType & {

                return this->split (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( separators ) ),
                        storeIn,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: split (
                    __ConvertibleType              && separators,
                    Size                              maxCount
            ) const noexcept -> __CollectionType <__BaseString < __CharType > > {

                __CollectionType <__BaseString < __CharType > > tokens;
                return this->split (
                        __BaseStringView ( std :: forward < __ConvertibleType > ( separators ) ),
                        tokens,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: split (
                    __BaseStringView < __CharType > const & separators,
                    __CollectionType                      & storeIn,
                    Size                                    maxCount
            ) const noexcept -> __CollectionType & {

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
                        storeIn.insert (__BaseString < __CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                        currentSegmentLength = 0ULL;
                        currentSegmentOffset = index + 1;
                    }
                }

                if ( currentSegmentLength != 0ULL ) {
                    storeIn.insert (__BaseString < __CharType > ( this->_pData + currentSegmentOffset, currentSegmentLength ) );
                }

                return storeIn;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: split (
                    __BaseStringView < __CharType > const & separators,
                    Size                                    maxCount
            ) const noexcept -> __CollectionType <__BaseString < __CharType > > {

                __CollectionType <__BaseString < __CharType > > tokens;
                return this->split (
                        separators,
                        tokens,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: splitByString (
                    __ConvertibleType && separator,
                    __CollectionType   & storeIn,
                    Size                 maxCount
            ) const noexcept -> __CollectionType & {

                return this->splitByString (
                        __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separator ) ),
                        storeIn,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ...> class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: splitByString (
                    __ConvertibleType && separator,
                    Size                 maxCount
            ) const noexcept -> __CollectionType <__BaseString < __CharType > > {

                __CollectionType <__BaseString < __CharType > > list;
                return this->splitByString (
                        __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separator ) ),
                        list,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: splitByString (
                    __BaseStringView < __CharType > const & separator,
                    __CollectionType                      & storeIn,
                    Size                                    maxCount
            ) const noexcept -> __CollectionType & {

                if ( separator.empty() ) {
                    return storeIn;
                }

                auto separatorPredictiveCount = this->count ([& separator]( char character ) noexcept -> bool {
                    return character == separator[0];
                });

                Index * pOccurrences = __allocation :: __alloc < Index > ( separatorPredictiveCount );

                auto actualSeparatorCount = StringUtils < __CharType > :: findAll (
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
                            storeIn.insert (
                                   __BaseString < __CharType > (
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


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: splitByString (
                    __BaseStringView < __CharType > const & separator,
                    Size                                    maxCount
            ) const noexcept -> __CollectionType < __BaseString < __CharType > > {

                __CollectionType <__BaseString < __CharType > > tokens;
                return this->splitByString (
                        separator,
                        tokens,
                        maxCount
                );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprOverride auto __BaseStringView < __CharType > :: hash () const noexcept -> Size {

                Size currentExponent = 1U;
                Size finalHash       = 0ULL;

                if ( this->empty() ) {
                    return 0ULL;
                }

                for ( Size index = this->_length - 1ULL; index > 0ULL; -- index ) {
                    finalHash += static_cast < Size > ( this->_pData [ index ] ) * currentExponent;
                    currentExponent *= 31ULL;
                }

                return finalHash + this->_pData [ 0 ] * currentExponent;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: toString () const noexcept ->__BaseString < __CharType > {
                return __BaseString < __CharType > ( this->_pData, this->_length );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: startsWith (
                    ElementType character
            ) const noexcept -> bool {

                return ! this->empty() && this->_pData [ 0 ] == character;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: startsWith (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->startsWith ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: startsWith (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> bool {

                Size offset = 0ULL;
                for ( auto minLength = minOf ( this->_length, string._length ); offset < minLength; ++ offset ) {
                    if ( this->_pData [ offset ] != string._pData [ offset ] ) {
                        return false;
                    }
                }

                return offset == string._length;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseStringView < __CharType > :: endsWith (
                    ElementType character
            ) const noexcept -> bool {

                return ! this->empty() && this->_pData [ this->_length - 1ULL ] == character;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: endsWith (
                    __ConvertibleType && string
            ) const noexcept -> bool {

                return this->endsWith ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseStringView < __CharType > :: endsWith (
                    __BaseStringView < __CharType > const & string
            ) const noexcept -> bool {

                Size offset = 0;
                for ( auto minLength = minOf ( this->_length, string._length ); offset < minLength; ++ offset ) {
                    if ( this->_pData [ this->_length - offset - 1ULL ] != string._pData [ string._length - offset - 1ULL ] ) {
                        return false;
                    }
                }

                return offset == string._length;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Action > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: forEach (
                    __Action const & action
            ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    action ( this->_pData [ index ] );
                }
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: some (
                    Size                  count,
                    __Predicate   const & predicate
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


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: atLeast (
                    Size                  count,
                    __Predicate   const & predicate
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


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: atMost (
                    Size                  count,
                    __Predicate   const & predicate
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


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: moreThan (
                    Size                  count,
                    __Predicate   const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                return this->atLeast ( count + 1, predicate );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: fewerThan (
                    Size                  count,
                    __Predicate   const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                return this->atMost ( count - 1, predicate );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: count (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size {

                Size trueCount = 0U;
                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( predicate ( this->_pData [ index ] ) ) {
                        ++ trueCount;
                    }
                }

                return trueCount;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: any (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( predicate ( this->_pData [ index ] ) ) {
                        return true;
                    }
                }

                return false;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: all (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( ! predicate ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto __BaseStringView < __CharType > :: none (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                for ( Size index = 0ULL; index < this->_length; ++ index ) {
                    if ( predicate ( this->_pData [ index ] ) ) {
                        return false;
                    }
                }

                return true;
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: ostream                         & out,
                    __BaseStringView < __FCharType > const & obj
            ) noexcept -> std :: ostream & {

                return ( out << obj.cStr() );
            }


            template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
            auto operator << (
                    std :: wostream                        & out,
                    __BaseStringView < __FCharType > const & obj
            ) noexcept -> std :: wostream & {

                return ( out << obj.cStr() );
            }

        }
    }
}


#endif // __CDS_BASE_STRING_VIEW_IMPL_HPP__
