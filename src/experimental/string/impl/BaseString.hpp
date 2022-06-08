//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_BASE_IMPL_HPP__
#define __CDS_EX_STRING_BASE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                namespace __allocation { // NOLINT(bugprone-reserved-identifier)

                    constexpr static Size const __minCapacity = 64ULL; // NOLINT(bugprone-reserved-identifier)

                    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                    inline auto __alloc ( // NOLINT(bugprone-reserved-identifier)
                            Size capacity
                    ) noexcept -> __CharType * {

                        return reinterpret_cast < __CharType * > (
                                malloc ( capacity * sizeof ( __CharType ) )
                        );
                    }


                    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                    inline auto __realloc ( // NOLINT(bugprone-reserved-identifier)
                            __CharType  * pBuffer,
                            Size          newCapacity
                    ) noexcept -> __CharType * {

                        return reinterpret_cast < __CharType * > (
                                realloc ( pBuffer, newCapacity * sizeof ( __CharType ) )
                        );
                    }


                    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                    inline auto __enlarge ( // NOLINT(bugprone-reserved-identifier)
                            __CharType  * pBuffer,
                            Size          oldCapacity,
                            Size          newCapacity,
                            Size        * pStoreNewCapacity
                    ) noexcept -> __CharType * {

                        if ( oldCapacity >= newCapacity ) {
                            return pBuffer;
                        }

                        if ( newCapacity < __minCapacity ) {
                            newCapacity = __minCapacity;
                        }

                        * pStoreNewCapacity = newCapacity;
                        return __realloc ( pBuffer, newCapacity );
                    }


                    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                    inline auto __free ( // NOLINT(bugprone-reserved-identifier)
                            __CharType * pBuffer
                    ) noexcept -> void {

                        free ( pBuffer );
                    }

                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                Size const __BaseString < __CharType > :: minCapacity   = __allocation :: __minCapacity;

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                Index const __BaseString < __CharType > :: invalidIndex = StringUtils < __CharType > :: invalidIndex;
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: whitespace = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: whitespace );
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: digits = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: digits );
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: lowercaseAlphabet = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: lowercaseAlphabet );
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: uppercaseAlphabet = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: uppercaseAlphabet );
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: vowels = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: vowels );
                
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseStringView < __CharType > const __BaseString < __CharType > :: consonants = __BaseStringView < __CharType > ( meta :: __impl :: __StringData < __CharType > :: consonants );


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __BaseString const & string
                ) noexcept :
                        __BaseString ( __BaseStringView < __CharType > ( string ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __BaseString < __OtherCharType > const & string
                ) noexcept :
                        __BaseString ( __BaseStringView < __OtherCharType > ( string ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr __BaseString < __CharType > :: __BaseString (
                        __BaseString && string
                ) noexcept :
                        _pBuffer ( cds :: exchange ( string._pBuffer, nullptr ) ),
                        _length ( cds :: exchange ( string._length, 0ULL ) ),
                        _capacity ( cds :: exchange ( string._capacity, 0ULL ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        __BaseStringView < __CharType > const & string
                ) noexcept {

                    if ( string.empty() ) {
                        return;
                    }

                    this->_capacity     = maxOf ( __BaseString :: minCapacity, string.length() + 1ULL );
                    this->_length       = string.length();
                    this->_pBuffer      = StringUtils < __CharType > :: copy (
                            __allocation :: __alloc < __CharType > ( this->_capacity ),
                            0ULL,
                            string.cStr(),
                            0ULL,
                            this->_length
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        __BaseStringView < __OtherCharType > const & string
                ) noexcept {

                    if ( string.empty() ) {
                        return;
                    }

                    this->_capacity = maxOf ( __BaseString :: minCapacity, string.length() + 1ULL );
                    this->_length   = string.length();
                    this->_pBuffer  = StringUtils < __CharType > :: copy (
                            __allocation :: __alloc < __CharType > ( this->_capacity ),
                            0ULL,
                            string.cStr(),
                            0ULL,
                            this->_length
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        ElementType const * pString,
                        Size                length
                ) noexcept :
                        __BaseString (
                                __BaseStringView < __CharType > (
                                        pString,
                                        length
                                )
                        ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        ElementType const * pString
                ) noexcept :
                        __BaseString ( __BaseStringView < __CharType > ( pString ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __OtherCharType   const * pString,
                        Size                      length
                ) noexcept :
                        __BaseString (
                                __BaseStringView < __OtherCharType > (
                                        pString,
                                        length
                                )
                        ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __OtherCharType const * pString
                ) noexcept :
                        __BaseString ( __BaseStringView < __OtherCharType > ( pString ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        std :: basic_string < __CharType > const & string
                ) noexcept :
                        __BaseString ( __BaseStringView < __CharType > ( string ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        cds :: String const & string
                ) noexcept :
                        __BaseString ( __BaseStringView < char > ( string.cStr(), string.length() ) ) {

                }


                /// TODO : replace after replacing experimental :: Object :: toString () -> BaseString
                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        experimental :: Object const & object
                ) noexcept :
                        __BaseString ( __BaseStringView < __CharType > ( object.toString() ) ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        Size        length,
                        ElementType fillCharacter
                ) noexcept {

                    if ( length == 0ULL ) {
                        return;
                    }

                    this->_length   = length;
                    this->_capacity = maxOf ( length + 1ULL, __BaseString :: minCapacity );
                    this->_pBuffer  = __allocation :: __alloc < __CharType > ( this->_capacity );

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        this->_pBuffer [ index ] = fillCharacter;
                    }

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        Size              length,
                        __OtherCharType   fillCharacter
                ) noexcept :
                        __BaseString (
                                length,
                                static_cast < ElementType > ( fillCharacter )
                        ) {

                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        this->append ( static_cast < ElementType > ( * iterator ) );
                    }
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        std :: initializer_list < ElementType > const & initializerList
                ) noexcept :
                        _capacity ( maxOf ( initializerList.size() + 1ULL, __BaseString :: minCapacity ) ) {

                    this->_pBuffer = __allocation :: __alloc < __CharType > ( this->_capacity );

                    for ( auto character : initializerList ) {
                        this->_pBuffer [ this->_length ++ ] = character;
                    }

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        std :: initializer_list < __OtherCharType > const & initializerList
                ) noexcept :
                        _capacity ( maxOf ( initializerList.size() + 1ULL, __BaseString :: minCapacity ) ) {

                    this->_pBuffer = __allocation :: __alloc < __CharType > ( this->_capacity );

                    for ( auto character : initializerList ) {
                        this->_pBuffer [ this->_length ++ ] = static_cast < ElementType > ( character );
                    }

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        ElementType value
                ) noexcept :
                        _length ( 1ULL ),
                        _capacity ( __BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < __CharType > ( __BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        __NumericType value
                ) noexcept :
                        _capacity ( __BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < __CharType > ( __BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __BaseString < __CharType > :: __BaseString (
                        bool value
                ) noexcept :
                        _capacity ( __BaseString :: minCapacity ),
                        _length ( value ? 4ULL : 5ULL ),
                        _pBuffer ( __allocation :: __alloc < __CharType > ( __BaseString :: minCapacity ) ) {

                    (void) StringUtils < ElementType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            value ? "true" : "false",
                            0ULL,
                            this->_length
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __FloatingPointType value
                ) noexcept :
                        __BaseString ( std :: to_string ( value ) ) {

                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __AddressType, meta :: EnableIf < ! meta :: isSame < __AddressType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: __BaseString (
                        __AddressType const * address
                ) noexcept {

                    std :: stringstream oss;
                    oss << "0x" << std :: hex << reinterpret_cast < std :: size_t > ( address );

                    * this = oss.str();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: ~__BaseString () noexcept {
                    __allocation :: __free ( this->_pBuffer );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: begin () noexcept -> Iterator {
                    return Iterator ( this, 0 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: end () noexcept -> Iterator {
                    return Iterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: begin () const noexcept -> ConstIterator {
                    return ConstIterator ( this, 0 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: end () const noexcept -> ConstIterator {
                    return ConstIterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: cbegin () const noexcept -> ConstIterator {
                    return ConstIterator ( this, 0 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: cend () const noexcept -> ConstIterator {
                    return ConstIterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: rbegin () noexcept -> ReverseIterator {
                    return ReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: rend () noexcept -> ReverseIterator {
                    return ReverseIterator ( this, -1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: rbegin () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: rend () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, -1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: crbegin () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: crend () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, -1 );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: size () const noexcept -> Size {
                    return this->_length;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: length () const noexcept -> Size {
                    return this->size();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: capacity () const noexcept -> Size {
                    return this->_capacity;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: resize (
                        Size size
                ) noexcept -> void {

                    size ++;

                    if ( size == this->_capacity ) {
                        return;
                    }

                    this->_capacity = maxOf ( size, __BaseString :: minCapacity );
                    this->_pBuffer = __allocation :: __realloc ( this->_pBuffer, this->_capacity );

                    if ( this->_length >= this->_capacity ) {
                        this->_length = this->_capacity - 1U;
                    }

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: reserve (
                        Size size
                ) noexcept -> void {

                    if ( size < this->_capacity ) {
                        return;
                    }

                    this->resize ( size );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: shrink (
                        Size size
                ) noexcept -> void {

                    if ( size == limits :: U64_MAX ) {
                        size = this->_length;
                    }

                    if ( size > this->_capacity ) {
                        return;
                    }

                    this->resize ( size );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: empty () const noexcept -> bool {
                    return this->_length == 0ULL;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: clear () noexcept -> void {

                    if ( this->_pBuffer == nullptr ) {
                        return;
                    }

                    this->_pBuffer [0]  = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    this->_length       = 0ULL;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: operator [] (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator [] (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: at (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: at (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: get (
                        Index index
                ) noexcept (false) -> ElementType & {

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


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: get (
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


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: front () noexcept (false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: front () const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: back () noexcept(false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: back () const noexcept(false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: toStdString () const noexcept -> std :: basic_string < __CharType > {

                    return std :: basic_string < __CharType > ( this->_pBuffer );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: cStr () const noexcept -> ElementType const * {

                    return this->_pBuffer == nullptr ? meta :: __impl :: __StringData < __CharType > :: emptyString : this->_pBuffer;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: data () noexcept -> ElementType * {

                    return this->_pBuffer;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __BaseString < __CharType > :: operator std :: basic_string < __CharType > () const noexcept {

                    return this->toStdString();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr __BaseString < __CharType > :: operator ElementType const * () const noexcept {

                    return this->cStr();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction __BaseString < __CharType > :: operator ElementType * () noexcept {

                    return this->data();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: substr (
                        Index from,
                        Index until
                ) const noexcept -> __BaseString < __CharType > {

                    if ( until == -1 || until > static_cast < Index > ( this->size() ) ) {
                        until = static_cast < Index > ( this->size() );
                    }

                    if ( from < 0 ) {
                        from = 0;
                    }

                    if ( until < from ) {
                        return __BaseString ();
                    }

                    return __BaseString ( this->_pBuffer + from, static_cast < Size > ( until - from ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator () (
                        Index from,
                        Index until
                ) const noexcept -> __BaseString < __CharType > {

                    return this->substr ( from, until );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator [] (
                        Range const & range
                ) const noexcept -> __BaseString < __CharType > {

                    return this->substr ( range.from(), range.to() );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->operator = ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: operator = (
                        __BaseString && string
                ) noexcept -> __BaseString & {

                    if ( this == & string ) {
                        return * this;
                    }

                    __allocation :: __free (
                            cds :: exchange (
                                    this->_pBuffer,
                                    cds :: exchange (
                                            string._pBuffer,
                                            nullptr
                                    )
                            )
                    );

                    this->_length   = cds :: exchange ( string._length, 0ULL );
                    this->_capacity = cds :: exchange ( string._capacity, 0ULL );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: operator = (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    if ( this->_pBuffer == string.cStr() ) {
                        return * this;
                    }

                    if ( string.empty() ) {
                        __allocation :: __free ( cds :: exchange ( this->_pBuffer, nullptr ) );
                        this->_length   = 0ULL;
                        this->_capacity = 0ULL;

                        return * this;
                    }

                    if ( this->_capacity < string.length() + 1ULL ) {

                        this->_capacity = maxOf ( string.length() + 1ULL, __BaseString :: minCapacity );

                        __allocation :: __free (
                                cds :: exchange (
                                        this->_pBuffer,
                                        __allocation :: __alloc < __CharType > ( this->_capacity )
                                )
                        );
                    }

                    this->_length = string.length();

                    (void) StringUtils < ElementType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator = (
                        ElementType character
                ) noexcept -> __BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            2ULL,
                            & this->_capacity
                    );

                    this->_length = 1ULL;
                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ 1 ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: operator = (
                        __NumericType value
                ) noexcept -> __BaseString & {

                    auto valueLength = StringUtils < __CharType > :: integerLength ( value );
                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            valueLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < __CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            valueLength,
                            nullptr,
                            & this->_length
                     ) = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: operator = (
                        bool value
                ) noexcept -> __BaseString & {

                    auto valueLength = value ? 4ULL : 5ULL;
                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            valueLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            value ? "true" : "false",
                            0ULL,
                            valueLength
                     );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator = (
                        __FloatingPointType value
                ) noexcept -> __BaseString & {

                    return this->operator = ( std :: to_string ( value ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_DynamicCastConstexpr auto __BaseString < __CharType > :: equals (
                        Object const & object
                ) const noexcept -> bool {

                    if ( this == & object ) {
                        return true;
                    }

                    auto pString = dynamic_cast < decltype (this) > ( & object );
                    if ( pString == nullptr ) {
                        return false;
                    }

                    return this->operator == ( __BaseStringView < __CharType > ( * pString ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator == (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) == __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator == (
                        __BaseString const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) == __BaseStringView < __CharType > ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator == (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) == string;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator == (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return false;
                    }

                    return this->_pBuffer [ 0 ] == character;
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString == BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) == __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return string._pBuffer [ 0 ] == character;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator != (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) != __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator != (
                        __BaseString const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) != __BaseStringView < __CharType > ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator != (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) != string;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator != (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return true;
                    }

                    return this->_pBuffer [ 0 ] != character;
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString != __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) != __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return string._pBuffer [ 0 ] != character;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator < (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) < __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator < (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) < string;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator < (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->empty() ) {
                        return true;
                    }

                    return this->_pBuffer [ 0 ] < character;
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString < __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) < __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    return character < __BaseStringView < __FCharType > ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator > (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) > __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator > (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ) > string;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator > (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->empty() ) {
                        return false;
                    }

                    if ( this->length() > 1 && this->_pData [0] == character ) {
                        return true;
                    }

                    return this->_pBuffer [ 1 ] > character;
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString < __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) < __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.empty() ) {
                        return false;
                    }

                    return character > string._pBuffer [ 0 ];
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator <= (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return ! ( __BaseStringView < __CharType > ( * this ) > __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator <= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return ! ( __BaseStringView < __CharType > ( * this ) > string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator <= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator > ( character );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > __BaseStringView < __FCharType > ( rightString ) );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return ! ( __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) > __BaseStringView < __FCharType > ( rightString ) );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    return ! ( character > string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator >= (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return ! ( __BaseStringView < __CharType > ( * this ) < __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator >= (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return ! ( __BaseStringView < __CharType > ( * this ) < string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator >= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator < ( character );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < __BaseStringView < __FCharType > ( rightString ) );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> bool {

                    return ! ( __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) < __BaseStringView < __FCharType > ( rightString ) );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        __FCharType                                      character,
                        __BaseString < __FCharType >             const & string
                ) noexcept -> bool {

                    return ! ( character < string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->append ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        __BaseString && string
                ) noexcept -> __BaseString & {

                    return this->append ( std :: move ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    return this->append ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        ElementType character
                ) noexcept -> __BaseString & {

                    return this->append ( character );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        __NumericType value
                ) noexcept -> __BaseString & {

                    return this->append ( value );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        bool value
                ) noexcept -> __BaseString & {

                    return this->append ( value );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator += (
                        __FloatingPointType value
                ) noexcept -> __BaseString & {

                    return this->append ( value );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __ConvertibleType && string
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __BaseString && string
                ) const & noexcept -> __BaseString {

                    __BaseString result;
                    result.reserve ( this->length() + string.length() + 1U );

                    return result.append ( * this ).append ( std :: move ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __BaseStringView < __CharType > const & string
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + string;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + character;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __NumericType value
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + value;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        bool value
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + value;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __FloatingPointType value
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) + value;
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >     const & rightString
                ) noexcept -> __BaseString < __FCharType > {

                    return leftString + __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __ConvertibleType                    && leftString,
                        __BaseString < __FCharType >    const & rightString
                ) noexcept -> __BaseString < __FCharType > {

                    return __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) + __BaseStringView < __FCharType > ( rightString );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __FCharType                             character,
                        __BaseString < __FCharType >    const & string
                ) noexcept -> __BaseString < __FCharType > {

                    return character + __BaseStringView < __FCharType > ( string );
                }


                template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __NumericType                           value,
                        __BaseString < __FCharType >    const & string
                ) noexcept -> __BaseString < __FCharType > {

                    return value + __BaseStringView < __FCharType > ( string );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        bool                               value,
                        __BaseString < __FCharType >    const & string
                ) noexcept -> __BaseString < __FCharType > {

                    return value + __BaseStringView < __FCharType > ( string );
                }


                template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __FloatingPointType                      value,
                        __BaseString < __FCharType >     const & string
                ) noexcept -> __BaseString < __FCharType > {

                    return value + __BaseStringView < __FCharType > ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __ConvertibleType && string
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __BaseString && string
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( std :: move ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __BaseStringView < __CharType > const & string
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( string ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        ElementType character
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( character ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __NumericType value
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( value ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        bool value
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( value ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator + (
                        __FloatingPointType value
                ) && noexcept -> __BaseString {

                    return std :: move ( this->append ( value ) );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __BaseStringView < __FCharType > const & leftString,
                        __BaseString < __FCharType >          && rightString
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( rightString.prepend ( leftString ) );
                }


                template < typename __FCharType, typename __ConvertibleType, meta :: EnableIf < meta :: isNonAmbiguousConvertibleToBaseStringView < __ConvertibleType, __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __ConvertibleType                             && leftString,
                        __BaseString < __FCharType >                  && rightString
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( rightString.prepend ( __BaseStringView < __FCharType > ( std :: forward < __ConvertibleType > ( leftString ) ) ) );
                }


                template < typename __FCharType, meta :: EnableIf < meta :: isStringCharType < __FCharType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __FCharType                             character,
                        __BaseString < __FCharType >         && string
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( string.prepend ( character ) );
                }


                template < typename __FCharType, typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __FCharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __NumericType                           value,
                        __BaseString < __FCharType >         && string
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( string.prepend ( value ) );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        bool                               value,
                        __BaseString < __FCharType >        && string
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( string.prepend ( value ) );
                }


                template < typename __FCharType, typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator + (
                        __FloatingPointType                    value,
                        __BaseString < __FCharType >          && string
                ) noexcept -> __BaseString < __FCharType > {

                    return std :: move ( string.prepend ( value ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: operator * (
                        int count
                ) const & noexcept -> __BaseString {

                    return __BaseStringView < __CharType > ( * this ) * count;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: operator * (
                        int count
                ) && noexcept -> __BaseString {

                    if ( this->empty() || count == 0 ) {
                        __allocation :: __free ( cds :: exchange ( this->_pBuffer, nullptr ) );
                        (void) cds :: exchange ( this->_length, 0ULL );
                        (void) cds :: exchange ( this->_capacity, 0ULL );

                        return std :: move ( * this );
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length * count + 1ULL,
                            & this->_capacity
                    );

                    auto newLength = this->length();
                    for ( int i = 1; i < count; ++ i ) {
                        StringUtils < __CharType > :: copy (
                                this->_pBuffer,
                                newLength,
                                this->_pBuffer,
                                0ULL,
                                this->length(),
                                false
                        );

                        newLength += this->length();
                    }

                    this->_length = newLength;
                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return std :: move ( * this );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto operator * (
                        int                                  count,
                        __BaseString < __FCharType > const & string
                ) noexcept -> __BaseString < __FCharType > {

                    return count * __BaseStringView < __FCharType > ( string );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto operator * (
                        int                              count,
                        __BaseString < __FCharType >  && string
                ) noexcept -> __BaseString < __FCharType > {

                    if ( string.empty() || count == 0 ) {
                        __allocation :: __free ( cds :: exchange ( string._pBuffer, nullptr ) );
                        (void) cds :: exchange ( string._length, 0ULL );
                        (void) cds :: exchange ( string._capacity, 0ULL );

                        return std :: move ( * string );
                    }

                    string._pBuffer = __allocation :: __enlarge (
                            string._pBuffer,
                            string._capacity,
                            string._length * count + 1ULL,
                            & string._capacity
                    );

                    auto newLength = string.length();
                    for ( int i = 1; i < count; ++ i ) {
                        StringUtils < __FCharType > :: copy (
                                string._pBuffer,
                                newLength,
                                string._pBuffer,
                                0ULL,
                                string.length(),
                                false
                        );

                        newLength += string.length();
                    }

                    string._length = newLength;
                    string._pBuffer [ string._length ] = static_cast < __FCharType > ( '\0' );
                    return std :: move ( * string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->append ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        __BaseString && string
                ) noexcept -> __BaseString & {

                    if ( this->empty() && string.empty() ) {
                        return * this;
                    }

                    Size newLength = this->length() + string.length();

                    if (
                            this->_capacity < newLength + 1ULL &&
                            string._capacity >= newLength + 1ULL
                    ) {

                        (void) std :: memmove (
                                string._pBuffer + this->length(),
                                string._pBuffer,
                                string.length() * sizeof ( __CharType )
                        );

                        (void) std :: memcpy (
                                string._pBuffer,
                                this->_pBuffer,
                                this->length() * sizeof ( __CharType )
                        );

                        string._pBuffer [ newLength ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                        __allocation :: __free (
                                cds :: exchange (
                                        this->_pBuffer,
                                        cds :: exchange (
                                                string._pBuffer,
                                                nullptr
                                        )
                                )
                        );

                        this->_length   = newLength;
                        this->_capacity = cds :: exchange ( string._capacity, 0ULL );
                        (void) cds :: exchange ( string._length, 0ULL );

                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            newLength + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    this->_length   = newLength;

                    __allocation :: __free ( cds :: exchange ( string._pBuffer, nullptr ) );
                    (void) cds :: exchange ( string._length, 0ULL );
                    (void) cds :: exchange ( string._capacity, 0ULL );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    if ( this->empty() && string.empty() ) {
                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + string.length() + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    this->_length += string.length();

                    return * this;
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        ElementType character
                ) noexcept -> __BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            & character,
                            0ULL,
                            1ULL
                    );

                    ++ this->_length;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        __NumericType value
                ) noexcept -> __BaseString & {

                    auto numberLength = StringUtils < __CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < __CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: append (
                        bool value
                ) noexcept -> __BaseString & {

                    uint8 valueLength = ( value ? 4ULL : 5ULL );
                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + valueLength + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            ( value ? "true" : "false" ),
                            0ULL,
                            valueLength
                    );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: append (
                        __FloatingPointType value
                ) noexcept -> __BaseString & {

                    return this->append ( std :: to_string ( value ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->prepend ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        __BaseString && string
                ) noexcept -> __BaseString & {

                    if ( string.empty() ) {
                        return * this;
                    }

                    auto newLength = this->_length + string.length();

                    string._pBuffer = __allocation :: __enlarge (
                            string._pBuffer,
                            string._capacity,
                            newLength + 1ULL,
                            & string._capacity
                    );

                    StringUtils < __CharType > :: copy (
                            string._pBuffer,
                            string.length(),
                            this->_pBuffer,
                            0ULL,
                            this->length()
                    );

                    __allocation :: __free (
                            cds :: exchange (
                                    this->_pBuffer,
                                    cds :: exchange (
                                            string._pBuffer,
                                            nullptr
                                    )
                            )
                    );

                    this->_length   = newLength;
                    this->_capacity = cds :: exchange ( string._capacity, 0ULL );
                    (void) cds :: exchange ( string._length, 0ULL );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    if ( string.empty() ) {
                        return * this;
                    }

                    auto newLength = this->_length + string.length();
                    if ( this->_capacity >= newLength + 1U ) {

                        (void) std :: memmove (
                                this->_pBuffer + string.length(),
                                this->_pBuffer,
                                this->_length * sizeof ( ElementType )
                        );

                        this->_pBuffer [ newLength ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                        this->_length                = newLength;

                        (void) std :: memcpy (
                                this->_pBuffer,
                                string.cStr(),
                                string.length() * sizeof ( ElementType )
                        );

                        return * this;
                    }

                    this->_capacity = maxOf ( newLength + 1U, __BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < ElementType > ( this->_capacity );

                    StringUtils < __CharType > :: copy (
                            newBuffer,
                            0ULL,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    StringUtils < __CharType > :: copy (
                            newBuffer,
                            string.length(),
                            this->_pBuffer,
                            0ULL,
                            this->_length
                    );

                    this->_length = newLength;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __TCharType, meta :: EnableIf < meta :: isStringCharType < __TCharType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        ElementType character
                ) noexcept -> __BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + 1U,
                            this->_pBuffer,
                            this->length() * sizeof ( __CharType )
                    );

                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ ++ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        __NumericType value
                ) noexcept -> __BaseString & {

                    auto numberLength = StringUtils < __CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + numberLength,
                            this->_pBuffer,
                            this->_length * sizeof ( ElementType )
                    );

                    (void) StringUtils < __CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: prepend (
                        bool value
                ) noexcept -> __BaseString & {

                    auto valueLength = value ? 4ULL : 5ULL;

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + valueLength + 1ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + valueLength,
                            this->_pBuffer,
                            this->_length * sizeof ( ElementType )
                    );

                    StringUtils < __CharType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            ( value ? "true" : "false" ),
                            0ULL,
                            valueLength,
                            false
                    );

                    this->_length += valueLength;
                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: prepend (
                        __FloatingPointType value
                ) noexcept -> __BaseString & {

                    return this->prepend ( std :: to_string ( value ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: contains (
                        ElementType character
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).contains ( character );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: contains (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).contains ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: contains (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).contains ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: containsAnyOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyOf (
                            characters
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAnyOf (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAnyOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyOf (
                            string
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: containsAllOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllOf (
                            characters
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAllOf (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllOf (
                            string
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: containsAnyNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyNotOf (
                            characters
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAnyNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAnyNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAnyNotOf (
                            string
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: containsAllNotOf (
                        __CollectionType < ElementType > const & characters
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllNotOf (
                            characters
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: containsAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).containsAllNotOf (
                            string
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                          maxCount,
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            character,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            character,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findFirst (
                        ElementType character
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirst ( character );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findLast (
                        ElementType character
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLast ( character );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        ElementType                   character,
                        __CollectionType < Index >  & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAll (
                            character,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        ElementType                 character
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAll (
                            character,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                                  maxCount,
                        __ConvertibleType                  && string,
                        __CollectionType < Index >          & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                                  maxCount,
                        __ConvertibleType                  && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: findFirst (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirst (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: findLast (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLast (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        __ConvertibleType                  && string,
                        __CollectionType < Index >          & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAll (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAll (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findOf (
                        Size                              maxCount,
                        __ConvertibleType              && string,
                        __CollectionType < Index >      & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findOf (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findOf (
                        Size                              maxCount,
                        __ConvertibleType              && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findOf (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findFirstOf (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirstOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findLastOf (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLastOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllOf (
                        __ConvertibleType              && string,
                        __CollectionType < Index >      & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAllOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAllOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findNotOf (
                        Size                              maxCount,
                        __ConvertibleType              && string,
                        __CollectionType < Index >      & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findNotOf (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findNotOf (
                        Size                              maxCount,
                        __ConvertibleType              && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findNotOf (
                            maxCount,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findFirstNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirstNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findLastNotOf (
                        __ConvertibleType && string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLastNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllNotOf (
                        __ConvertibleType              && string,
                        __CollectionType < Index >      & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAllNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllNotOf (
                        __ConvertibleType && string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAllNotOf (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) ),
                            indices
                    );
                }\


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: find (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).find (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: findFirst (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirst ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprDynamicAllocation auto __BaseString < __CharType > :: findLast (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLast ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAll (
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAll (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAll (
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findOf (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findOf (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findFirstOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirstOf ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findLastOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLastOf ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAllOf (
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAllOf (
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findNotOf (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findNotOf (
                        Size                                    maxCount,
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findNotOf (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findFirstNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findFirstNotOf ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: findLastNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> Index {

                    return __BaseStringView < __CharType > ( * this ).findLastNotOf ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllNotOf (
                        __BaseStringView < __CharType > const & string,
                        __CollectionType < Index >            & storeIn
                ) const noexcept -> __CollectionType < Index > & {

                    return __BaseStringView < __CharType > ( * this ).findAllNotOf (
                            string,
                            storeIn
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: findAllNotOf (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> __CollectionType < Index > {

                    __CollectionType < Index > indices;
                    return __BaseStringView < __CharType > ( * this ).findAllNotOf (
                            string,
                            indices
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: ltrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString & {

                    return this->ltrim ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( characters ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: ltrim (
                        __BaseStringView < __CharType > const & characters
                ) noexcept -> __BaseString & {

                    Size offset = 0ULL;
                    while ( offset < this->length() && characters.contains ( this->_pBuffer [ offset ] ) ) {
                        ++ offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;

                    (void) std :: memmove (
                            this->_pBuffer,
                            this->_pBuffer + offset,
                            this->length() * sizeof ( ElementType )
                    );

                    this->_pBuffer [ this->length() ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: ltrim (
                        ElementType character
                ) noexcept -> __BaseString & {

                    Size offset = 0ULL;
                    while ( offset < this->length() && character == this->_pBuffer [ offset ] ) {
                        ++ offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;

                    (void) std :: memmove (
                            this->_pBuffer,
                            this->_pBuffer + offset,
                            this->length() * sizeof ( ElementType )
                    );

                    this->_pBuffer [ this->length() ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: rtrim (
                        ElementType character
                ) noexcept -> __BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && this->_pBuffer [ offset ] == character ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: rtrim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString & {

                    return this->rtrim ( __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( characters ) ) );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: rtrim (
                        __BaseStringView < __CharType > const & characters
                ) noexcept -> __BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && characters.contains ( this->_pBuffer [ offset ] ) ) {
                        -- offset;
                    }

                    if ( static_cast < Size > ( offset ) + 1ULL == this->length() ) {
                        return * this;
                    }

                    this->_length = static_cast < Size > ( offset ) + 1ULL;
                    this->_pBuffer [ this->length() ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: trim (
                        ElementType character
                ) noexcept -> __BaseString & {

                    return this->ltrim ( character ).rtrim ( character );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: trim (
                        __ConvertibleType && characters
                ) noexcept -> __BaseString & {

                    auto view = __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( characters ) );
                    return this->ltrim ( view ).rtrim ( view );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: trim (
                        __BaseStringView < __CharType > const & characters
                ) noexcept -> __BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: ljust (
                        Size        size,
                        ElementType element
                ) noexcept -> __BaseString & {

                    if ( size <= this->length() ) {
                        return * this;
                    }

                    size -= this->length();

                    auto newCapacity = maxOf (
                            this->_capacity,
                            size + this->length() + 1U,
                            __BaseString :: minCapacity
                    );

                    auto newBuffer = __allocation :: __alloc < __CharType > ( newCapacity );

                    for ( Size index = 0ULL; index < size; ++ index ) {
                        newBuffer [ index ] = element;
                    }

                    StringUtils < __CharType > :: copy (
                            newBuffer,
                            size,
                            this->_pBuffer,
                            0ULL,
                            this->length()
                    );

                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    this->_capacity = newCapacity;
                    this->_length = size + this->_length;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: rjust (
                        Size        size,
                        ElementType element
                ) noexcept -> __BaseString & {

                    if ( size <= this->length() ) {
                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            size + 1ULL,
                            & this->_capacity
                    );

                    for ( Size index = this->length(); index < size; ++ index ) {
                        this->_pBuffer [ index ] = element;
                    }

                    this->_pBuffer [ size ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    this->_length = size;
                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: toLower () noexcept -> __BaseString & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        this->_pBuffer [ index ] = StringUtils < __CharType > :: lower ( this->_pBuffer [ index ] );
                    }

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: toUpper () noexcept -> __BaseString & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        this->_pBuffer [ index ] = StringUtils < __CharType > :: upper ( this->_pBuffer [ index ] );
                    }

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        ElementType             separator,
                        __CollectionType      & storeIn,
                        Size                    maxCount
                ) const noexcept -> __CollectionType & {

                    return __BaseStringView < __CharType > ( * this ).split (
                            separator,
                            storeIn,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        ElementType separator,
                        Size        maxCount
                ) const noexcept -> __CollectionType < __BaseString > {

                    __CollectionType < __BaseString > tokens;
                    return __BaseStringView < __CharType > ( * this ).split (
                            separator,
                            tokens,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        __ConvertibleType      && separators,
                        __CollectionType        & storeIn,
                        Size                      maxCount
                ) const noexcept -> __CollectionType & {

                    return __BaseStringView < __CharType > ( * this ).split (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separators ) ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        __ConvertibleType      && separators,
                        Size                      maxCount
                ) const noexcept -> __CollectionType < __BaseString > {

                    __CollectionType < __BaseString > tokens;
                    return __BaseStringView < __CharType > ( * this ).split (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separators ) ),
                            tokens,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        __BaseStringView < __CharType > const & separators,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount
                ) const noexcept -> __CollectionType & {

                    return __BaseStringView < __CharType > ( * this ).split (
                            separators,
                            storeIn,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: split (
                        __BaseStringView < __CharType > const & separators,
                        Size                                    maxCount
                ) const noexcept -> __CollectionType < __BaseString > {

                    __CollectionType < __BaseString > tokens;
                    return __BaseStringView < __CharType > ( * this ).split (
                            __BaseStringView < __CharType > ( separators ),
                            tokens,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: splitByString (
                        __ConvertibleType      && separator,
                        __CollectionType        & storeIn,
                        Size                      maxCount
                ) const noexcept -> __CollectionType & {

                    return __BaseStringView < __CharType > ( * this ).splitByString (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separator ) ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: splitByString (
                        __ConvertibleType         && separator,
                        Size                         maxCount
                ) const noexcept -> __CollectionType < __BaseString > {

                    __CollectionType < __BaseString > tokens;
                    return __BaseStringView < __CharType > ( * this ).splitByString (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( separator ) ),
                            tokens,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: splitByString (
                        __BaseStringView < __CharType > const & separator,
                        __CollectionType                      & storeIn,
                        Size                                    maxCount
                ) const noexcept -> __CollectionType & {

                    return __BaseStringView < __CharType > ( * this ).splitByString (
                            separator,
                            storeIn,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: splitByString (
                        __BaseStringView < __CharType > const & separator,
                        Size                                    maxCount
                ) const noexcept -> __CollectionType < __BaseString > {

                    __CollectionType < __BaseString > tokens;
                    return __BaseStringView < __CharType > ( * this ).splitByString (
                            separator,
                            tokens,
                            maxCount
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprOverride auto __BaseString < __CharType > :: hash () const noexcept -> Index {
                    return __BaseStringView < __CharType > ( * this ).hash();
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: toString () const noexcept -> cds :: String {
                    return cds :: String ( this->cStr() );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: startsWith (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->empty() && this->_pData [ 0 ] == character;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: startsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).startsWith (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: startsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).startsWith ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseString < __CharType > :: endsWith (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->empty() && this->_pData [ this->_length - 1ULL ] == character;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: endsWith (
                        __ConvertibleType && string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).endsWith (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: endsWith (
                        __BaseStringView < __CharType > const & string
                ) const noexcept -> bool {

                    return __BaseStringView < __CharType > ( * this ).endsWith ( string );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removePrefix (
                        ElementType character
                ) noexcept -> __BaseString & {

                    if ( this->empty() || this->_pBuffer [ 0 ] != character ) {
                        return * this;
                    }

                    -- this->_length;

                    (void) std :: memmove (
                            this->_pBuffer,
                            this->_pBuffer + 1,
                            this->_length
                    );

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removePrefix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->removePrefix (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removePrefix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    if ( ! this->startsWith ( string ) ) {
                        return * this;
                    }

                    this->_length = this->_length - string.length();

                    (void) std :: memmove (
                            this->_pBuffer,
                            this->_pBuffer + string.length(),
                            this->length() - string.length()
                    );

                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removeSuffix (
                        ElementType character
                ) noexcept -> __BaseString & {

                    if ( this->empty() || this->_pBuffer [ this->_length - 1ULL ] != character ) {
                        return * this;
                    }

                    this->_pBuffer [ -- this->_length - 1ULL ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removeSuffix (
                        __ConvertibleType && string
                ) noexcept -> __BaseString & {

                    return this->removeSuffix (
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( string ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: removeSuffix (
                        __BaseStringView < __CharType > const & string
                ) noexcept -> __BaseString & {

                    if ( ! this->endsWith ( string ) ) {
                        return * this;
                    }

                    this->_length = this->_length - string.length();
                    this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType, typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: join (
                        __CollectionType < __BaseString > const & tokens,
                        __ConvertibleType                      && delimiter
                ) noexcept -> __BaseString {

                    return __BaseString :: join (
                            tokens,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( delimiter ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: join (
                        __CollectionType < __BaseString > const & tokens,
                        __BaseStringView < __CharType >   const & delimiter
                ) noexcept -> __BaseString {

                    __BaseString < __CharType > result;
                    if ( tokens.empty() ) {
                        return result;
                    }

                    Size lengthOfAllTokens = 0ULL;
                    for ( auto iterator = tokens.begin(), end = tokens.end(); iterator != end; ++ iterator ) {
                        lengthOfAllTokens += ( * iterator ).length();
                    }

                    result._capacity = maxOf (
                            lengthOfAllTokens + delimiter.length() * ( tokens.size() - 1ULL ),
                            __BaseString :: minCapacity
                    );

                    result._pBuffer = __allocation :: __alloc < __CharType > (
                            result._capacity
                    );

                    auto iterator = tokens.begin();
                    StringUtils < __CharType > :: copy (
                            result._pBuffer,
                            0ULL,
                            ( * iterator )._pBuffer,
                            0ULL,
                            ( * iterator )._length,
                            false
                    );

                    result._length += ( * iterator )._length;
                    ++ iterator;

                    for ( auto end = tokens.end(); iterator != end; ++ iterator ) {

                        StringUtils < __CharType > :: copy (
                                result._pBuffer,
                                result._length,
                                delimiter.cStr(),
                                0ULL,
                                delimiter.length(),
                                false
                        );

                        result._length += delimiter.length();

                        StringUtils < __CharType > :: copy (
                                result._pBuffer,
                                result._length,
                                ( * iterator )._pBuffer,
                                0ULL,
                                ( * iterator )._length,
                                false
                        );

                        result._length += ( * iterator )._length;
                    }

                    result._pBuffer [ result._length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return result;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: join (
                        __CollectionType < __BaseString > const & tokens,
                        ElementType                               delimiter
                ) noexcept -> __BaseString {

                    __BaseString < __CharType > result;
                    if ( tokens.empty() ) {
                        return result;
                    }

                    Size lengthOfAllTokens = 0ULL;
                    for ( auto iterator = tokens.begin(), end = tokens.end(); iterator != end; ++ iterator ) {
                        lengthOfAllTokens += ( * iterator ).length();
                    }

                    result._capacity = maxOf (
                            lengthOfAllTokens + tokens.size() - 1ULL,
                            __BaseString :: minCapacity
                    );

                    result._pBuffer = __allocation :: __alloc < __CharType > (
                            result._capacity
                    );

                    auto iterator = tokens.begin();
                    StringUtils < __CharType > :: copy (
                            result._pBuffer,
                            0ULL,
                            ( * iterator )._pBuffer,
                            0ULL,
                            ( * iterator )._length,
                            false
                    );

                    result._length += ( * iterator )._length;
                    ++ iterator;

                    for ( auto end = tokens.end(); iterator != end; ++ iterator ) {

                        result._pBuffer [ result._length ++ ] = delimiter;

                        StringUtils < __CharType > :: copy (
                                result._pBuffer,
                                result._length,
                                ( * iterator )._pBuffer,
                                0ULL,
                                ( * iterator )._length,
                                false
                        );

                        result._length += ( * iterator )._length;
                    }

                    result._pBuffer [ result._length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    return result;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __ConvertibleType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ConvertibleType, __CharType > () > > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: replace (
                        Index                   from,
                        Index                   until,
                        __ConvertibleType    && inPlace
                ) noexcept -> __BaseString & {

                    return this->replace (
                            from,
                            until,
                            __BaseStringView < __CharType > ( std :: forward < __ConvertibleType > ( inPlace ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptionalInline auto __BaseString < __CharType > :: replace (
                        Index                                   from,
                        Index                                   until,
                        __BaseStringView < __CharType > const & inPlace
                ) noexcept -> __BaseString & {

                    if ( from < 0 ) {
                        from = 0;
                    }

                    if ( static_cast < Size > ( until ) > this->length() ) {
                        until = static_cast < Index > ( this->length() );
                    }

                    if ( from > until ) {
                        return * this;
                    }

                    auto leftLength         = static_cast < Size > ( from );
                    auto sectionLength      = static_cast < Size > ( until - from );
                    auto remainingLength    = static_cast < Size > ( this->length() - until );

                    this->_length = this->length() - sectionLength + inPlace.length();

                    if ( this->_length + 1ULL < this->_capacity ) {
                        (void) std :: memmove (
                                this->_pBuffer + until,
                                this->_pBuffer + from,
                                 remainingLength * sizeof ( ElementType )
                        );

                        (void) std :: memcpy (
                                this->_pBuffer + from,
                                inPlace.cStr(),
                                sectionLength * sizeof ( ElementType )
                        );

                        this->_pBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                        return * this;
                    }

                    auto newCapacity = maxOf ( this->_length + 1ULL, __BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < __CharType > ( newCapacity );

                    (void) std :: memcpy (
                            newBuffer,
                            this->_pBuffer,
                            leftLength * sizeof ( ElementType )
                    );

                    (void) std :: memcpy (
                            newBuffer + until,
                            this->_pBuffer + from,
                            remainingLength * sizeof ( ElementType )
                    );

                    (void) std :: memcpy (
                            newBuffer + from,
                            inPlace.cStr(),
                            sectionLength * sizeof ( ElementType )
                    );

                    newBuffer [ this->_length ] = meta :: __impl :: __StringData < ElementType > :: nullCharacter;
                    this->_capacity = newCapacity;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: reverse () noexcept -> __BaseString & {

                    if ( this->length() < 2ULL ) {
                        return * this;
                    }

                    Size opposite = this->_length - 1ULL;
                    for ( Size index = 0ULL; index < opposite; ++ index, -- opposite ) {

                        auto aux                    = this->_pBuffer [ index ];
                        this->_pBuffer [ index ]    = this->_pBuffer [ opposite ];
                        this->_pBuffer [ opposite ] = aux;
                    }

                    return * this;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: forEach (
                        __Action const & action
                ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Action > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: forEach (
                        __Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: some (
                        Size                  count,
                        __Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                auto __BaseString < __CharType > :: some (
                        Size                  count,
                        __Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                auto __BaseString < __CharType > :: atLeast (
                        Size                  count,
                        __Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                auto __BaseString < __CharType > :: atLeast (
                        Size                  count,
                        __Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                auto __BaseString < __CharType > :: atMost (
                        Size                  count,
                        __Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                auto __BaseString < __CharType > :: atMost (
                        Size                  count,
                        __Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    Size trueCount = 0ULL;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
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
                __CDS_OptimalInline auto __BaseString < __CharType > :: moreThan (
                        Size                  count,
                        __Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return this->atLeast ( count + 1, predicate );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: moreThan (
                        Size                  count,
                        __Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atLeast ( count + 1, predicate );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: fewerThan (
                        Size                  count,
                        __Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return this->atMost ( count - 1, predicate );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: fewerThan (
                        Size                  count,
                        __Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atMost ( count - 1, predicate );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: count (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    Size trueCount = 0U;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: count (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size {

                    Size trueCount = 0U;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: any (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: any (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: all (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( ! predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: all (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( ! predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: none (
                        __Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: none (
                        __Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: format (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString {

                    __BaseString < __CharType > result;
                    auto formatLength = StringUtils < __CharType > :: length ( pFormat );
                    result._capacity = StringUtils < __CharType > :: stringLengthOfArguments (
                            std :: forward < __ArgumentTypes > ( arguments ) ...
                    ) + __CDS_StringFormat_StartSize + formatLength;

                    result._pBuffer = __allocation :: __alloc < __CharType > ( result._capacity );
                    result._length = std :: snprintf (
                            result._pBuffer,
                            result._capacity,
                            pFormat,
                            std :: forward < __ArgumentTypes > ( arguments ) ...
                    );

                    if ( result._capacity <= result._length ) {

                        __allocation :: __free ( result._pBuffer );

                        result._capacity = result._length + 1ULL;
                        __allocation :: __alloc < __CharType > ( result._capacity );

                        result._length = std :: snprintf (
                                result._pBuffer,
                                result._capacity,
                                pFormat,
                                std :: forward < __ArgumentTypes > ( arguments ) ...
                        );
                    }

                    return result;
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: f (
                        __CharType        const * pFormat,
                        __ArgumentTypes    && ... arguments
                ) noexcept ( false ) -> __BaseString {

                    return __BaseString < __CharType > :: format (
                            pFormat,
                            std :: forward < __ArgumentTypes > ( arguments ) ...
                    );
                }


                template < typename __FCharType > // NOLINT(bugprone-reserved-identifier)
                auto operator << (
                        std :: wostream                    & out,
                        __BaseString < __FCharType > const & obj
                ) noexcept -> std :: wostream & {
                    return ( out << obj.cStr() );
                }

#if defined(CDS_STRING_DEBUG)

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                auto __BaseString < __CharType > :: diag () const noexcept -> __BaseString {
                    return __BaseStringView < __CharType > ( "Debug = { data = '" ) + this->_pBuffer +
                            "', length = " + this->_length +
                            ", capacity = " + this->_capacity + " }";
                }

#endif

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_IMPL_HPP__
