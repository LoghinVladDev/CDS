//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_BASE_IMPL_HPP__
#define __CDS_EX_STRING_BASE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                namespace __allocation { // NOLINT(bugprone-reserved-identifier)

                    constexpr static Size const minCapacity = 64ULL;

                    template < typename CharType >
                    inline auto __alloc ( // NOLINT(bugprone-reserved-identifier)
                            Size        capacity
                    ) noexcept -> CharType * {

                        return reinterpret_cast < CharType * > (
                                malloc ( capacity * sizeof ( CharType ) )
                        );
                    }


                    template < typename CharType >
                    inline auto __realloc ( // NOLINT(bugprone-reserved-identifier)
                            CharType  * pBuffer,
                            Size        newCapacity
                    ) noexcept -> CharType * {

                        return reinterpret_cast < CharType * > (
                                realloc ( pBuffer, newCapacity * sizeof ( CharType ) )
                        );
                    }


                    template < typename CharType >
                    inline auto __enlarge ( // NOLINT(bugprone-reserved-identifier)
                            CharType  * pBuffer,
                            Size        oldCapacity,
                            Size        newCapacity,
                            Size      * pStoreNewCapacity
                    ) noexcept -> CharType * {

                        if ( oldCapacity >= newCapacity ) {
                            return pBuffer;
                        }

                        if ( newCapacity < minCapacity ) {
                            newCapacity = minCapacity;
                        }

                        * pStoreNewCapacity = newCapacity;
                        return __realloc ( pBuffer, newCapacity );
                    }


                    template < typename CharType >
                    inline auto __free ( // NOLINT(bugprone-reserved-identifier)
                            CharType  * pBuffer
                    ) noexcept -> void {

                        free ( pBuffer );
                    }

                }

                template < typename CharType >
                Size const BaseString < CharType > :: minCapacity   = __allocation :: minCapacity;

                template < typename CharType >
                Index const BaseString < CharType > :: invalidIndex = StringUtils < CharType > :: invalidIndex;


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        BaseString const & string
                ) noexcept :
                        BaseString ( BaseStringView < CharType > ( string ) ) {

                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        BaseString < OtherCharType > const & string
                ) noexcept :
                        BaseString ( BaseStringView < OtherCharType > ( string ) ) {

                }


                template < typename CharType >
                constexpr BaseString < CharType > :: BaseString (
                        BaseString && string
                ) noexcept :
                        _pBuffer ( cds :: exchange ( string._pBuffer, nullptr ) ),
                        _length ( cds :: exchange ( string._length, 0ULL ) ),
                        _capacity ( cds :: exchange ( string._capacity, 0ULL ) ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        BaseStringView < CharType > const & string
                ) noexcept {

                    if ( string.empty() ) {
                        return;
                    }

                    this->_capacity     = maxOf ( BaseString :: minCapacity, string.length() + 1ULL );
                    this->_length       = string.length();
                    this->_pBuffer      = StringUtils < CharType > :: copy (
                            __allocation :: __alloc < CharType > ( this->_capacity ),
                            0ULL,
                            string.cStr(),
                            0ULL,
                            this->_length
                    );
                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                BaseString < CharType > :: BaseString (
                        BaseStringView < OtherCharType > const & string
                ) noexcept {

                    if ( string.empty() ) {
                        return;
                    }

                    this->_capacity = maxOf ( BaseString :: minCapacity, string.length() + 1ULL );
                    this->_length   = string.length();
                    this->_pBuffer  = StringUtils < CharType > :: copy (
                            __allocation :: __alloc < CharType > ( this->_capacity ),
                            0ULL,
                            string.cStr(),
                            0ULL,
                            this->_length
                    );
                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType const * pString,
                        Size                length
                ) noexcept :
                        BaseString (
                                BaseStringView < CharType > (
                                        pString,
                                        length
                                )
                        ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType const * pString
                ) noexcept :
                        BaseString ( BaseStringView < CharType > ( pString ) ) {

                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        OtherCharType   const * pString,
                        Size                    length
                ) noexcept :
                        BaseString (
                                BaseStringView < OtherCharType > (
                                        pString,
                                        length
                                )
                        ) {

                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        OtherCharType const * pString
                ) noexcept :
                        BaseString ( BaseStringView < OtherCharType > ( pString ) ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        std :: basic_string < CharType > const & string
                ) noexcept :
                        BaseString ( BaseStringView < CharType > ( string ) ) {

                }


                /// TODO : replace after replacing experimental :: Object :: toString () -> BaseString
                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        experimental :: Object const & object
                ) noexcept :
                        BaseString ( BaseStringView < CharType > ( object.toString().cStr() ) ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        Size        length,
                        ElementType fillCharacter
                ) noexcept {

                    if ( length == 0ULL ) {
                        return;
                    }

                    this->_length   = length;
                    this->_capacity = maxOf ( length + 1ULL, BaseString :: minCapacity );
                    this->_pBuffer  = __allocation :: __alloc < CharType > ( this->_capacity );

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        this->_pBuffer [ index ] = fillCharacter;
                    }

                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        Size            length,
                        OtherCharType   fillCharacter
                ) noexcept :
                        BaseString (
                                length,
                                static_cast < ElementType > ( fillCharacter )
                        ) {

                }


                template < typename CharType >
                template < typename IteratorType, meta :: EnableIf < meta :: isIterator < IteratorType > () > >
                BaseString < CharType > :: BaseString (
                        IteratorType const & begin,
                        IteratorType const & end
                ) noexcept {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        this->append ( * iterator );
                    }
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        std :: initializer_list < ElementType > const & initializerList
                ) noexcept :
                        _capacity ( maxOf ( initializerList.size() + 1ULL, BaseString :: minCapacity ) ) {

                    this->_pBuffer = __allocation :: __alloc < CharType > ( this->_capacity );

                    for ( auto character : initializerList ) {
                        this->_pBuffer [ this->_length ++ ] = character;
                    }

                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                BaseString < CharType > :: BaseString (
                        std :: initializer_list < OtherCharType > const & initializerList
                ) noexcept :
                        _capacity ( maxOf ( initializerList.size() + 1ULL, BaseString :: minCapacity ) ) {

                    this->_pBuffer = __allocation :: __alloc < CharType > ( this->_capacity );

                    for ( auto character : initializerList ) {
                        this->_pBuffer [ this->_length ++ ] = static_cast < ElementType > ( character );
                    }

                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType value
                ) noexcept :
                        _length ( 1ULL ),
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType value
                ) noexcept :
                        _length ( 1ULL ),
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType value
                ) noexcept :
                        _length ( 1ULL ),
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        ElementType value
                ) noexcept :
                        _length ( 1ULL ),
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                BaseString < CharType > :: BaseString (
                        uint8 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                BaseString < CharType > :: BaseString (
                        uint16 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                BaseString < CharType > :: BaseString (
                        sint8 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                BaseString < CharType > :: BaseString (
                        sint16 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                BaseString < CharType > :: BaseString (
                        std :: size_t value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        bool value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _length ( value ? 4ULL : 5ULL ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    (void) StringUtils < ElementType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            value ? "true" : "false",
                            0ULL,
                            this->_length
                    );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        uint32 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        uint64 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        sint32 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        sint64 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            StringUtils < ElementType > :: integerLength ( value ),
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        float value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        double value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: BaseString (
                        long double value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: ~BaseString () noexcept {
                    __allocation :: __free ( this->_pBuffer );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: begin () noexcept -> Iterator {
                    return Iterator ( this, 0 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: end () noexcept -> Iterator {
                    return Iterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: begin () const noexcept -> ConstIterator {
                    return ConstIterator ( this, 0 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: end () const noexcept -> ConstIterator {
                    return ConstIterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: cbegin () const noexcept -> ConstIterator {
                    return ConstIterator ( this, 0 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: cend () const noexcept -> ConstIterator {
                    return ConstIterator ( this, static_cast < Index > ( this->_length ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: rbegin () noexcept -> ReverseIterator {
                    return ReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: rend () noexcept -> ReverseIterator {
                    return ReverseIterator ( this, -1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: rbegin () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: rend () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, -1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: crbegin () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, static_cast < Index > ( this->_length ) - 1 );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: crend () const noexcept -> ConstReverseIterator {
                    return ConstReverseIterator ( this, -1 );
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: size () const noexcept -> Size {
                    return this->_length;
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: length () const noexcept -> Size {
                    return this->size();
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: capacity () const noexcept -> Size {
                    return this->_capacity;
                }


                template < typename CharType >
                auto BaseString < CharType > :: resize (
                        Size size
                ) noexcept -> void {

                    size ++;

                    if ( size == this->_capacity ) {
                        return;
                    }

                    this->_capacity = maxOf ( size, BaseString :: minCapacity );;
                    this->_pBuffer = __allocation :: __realloc ( this->_pBuffer, this->_capacity );

                    if ( this->_length >= this->_capacity ) {
                        this->_length = this->_capacity - 1U;
                    }

                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: reserve (
                        Size size
                ) noexcept -> void {

                    if ( size < this->_capacity ) {
                        return;
                    }

                    this->resize ( size );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: shrink (
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


                template < typename CharType >
                constexpr auto BaseString < CharType > :: empty () const noexcept -> bool {
                    return this->_length == 0ULL;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: clear () noexcept -> void {

                    if ( this->_pBuffer == nullptr ) {
                        return;
                    }

                    this->_pBuffer [0]  = static_cast < ElementType > ( '\0' );
                    this->_length       = 0ULL;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: operator [] (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator [] (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: at (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: at (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: get (
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: get (
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
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: front () noexcept (false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: front () const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: back () noexcept(false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: back () const noexcept(false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: toStdString () const noexcept -> std :: basic_string < CharType > {

                    return std :: basic_string < CharType > ( this->_pBuffer );
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: cStr () const noexcept -> ElementType const * {

                    return this->_pBuffer == nullptr ? "" : this->_pBuffer;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: data () noexcept -> ElementType * {

                    return this->_pBuffer;
                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: operator std :: basic_string < CharType > () const noexcept {

                    return this->toStdString();
                }


                template < typename CharType >
                constexpr BaseString < CharType > :: operator ElementType const * () const noexcept {

                    return this->cStr();
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction BaseString < CharType > :: operator ElementType * () noexcept {

                    return this->data();
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: substr (
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
                        return BaseString ();
                    }

                    return BaseString ( this->_pBuffer, static_cast < Size > ( until - from ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator () (
                        Index from,
                        Index until
                ) const noexcept -> BaseString < CharType > {

                    return this->substr ( from, until );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator [] (
                        Range const & range
                ) const noexcept -> BaseString < CharType > {

                    return this->substr ( range.from(), range.to() );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator = ( // NOLINT(bugprone-unhandled-self-assignment)
                        BaseString const & string
                ) noexcept -> BaseString & {

                    return this->operator = ( BaseStringView < CharType > ( string ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: operator = (
                        BaseString && string
                ) noexcept -> BaseString & {

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


                template < typename CharType >
                auto BaseString < CharType > :: operator = (
                        BaseStringView < CharType > const & string
                ) noexcept -> BaseString & {

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

                        this->_capacity = maxOf ( string.length() + 1ULL, BaseString :: minCapacity );

                        __allocation :: __free (
                                cds :: exchange (
                                        this->_pBuffer,
                                        __allocation :: __alloc < CharType > ( this->_capacity )
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


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator = (
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseString & {

                    return this->operator = ( BaseStringView < CharType > ( string ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator = (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    return this->operator = ( BaseStringView < CharType > ( pString ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator = (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            2ULL,
                            & this->_capacity
                    );

                    this->_length = 1ULL;
                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( character );

                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_DynamicCastConstexpr auto BaseString < CharType > :: equals (
                        Object const & object
                ) const noexcept -> bool {

                    if ( this == & object ) {
                        return true;
                    }

                    auto pString = dynamic_cast < decltype (this) > ( & object );
                    if ( pString == nullptr ) {
                        return false;
                    }

                    return this->operator == ( BaseStringView < CharType > ( * pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseString const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) == BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) == string;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) == BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) == BaseStringView < CharType > ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return false;
                    }

                    return this->_pBuffer [ 0 ] == character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString == BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) == BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) == BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return string._pBuffer [ 0 ] == character;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseString const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) != BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) != string;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) != BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) != BaseStringView < CharType > ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return true;
                    }

                    return this->_pBuffer [ 0 ] != character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString != BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) != BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) != BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return string._pBuffer [ 0 ] != character;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseString const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) < string;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->empty() ) {
                        return true;
                    }

                    return this->_pBuffer [ 0 ] < character;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    return character < BaseStringView < FCharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseString const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) > string;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
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


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return leftString < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( leftString ) < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return BaseStringView < FCharType > ( pLeftString ) < BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.empty() ) {
                        return false;
                    }

                    return character > string._pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseString const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) > string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) > BaseStringView < CharType > ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator > ( character );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( leftString ) > BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( pLeftString ) > BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    return ! ( character > string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        BaseString const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) < string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return ! ( BaseStringView < CharType > ( * this ) < BaseStringView < CharType > ( pString ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator < ( character );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( leftString ) < BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( BaseStringView < FCharType > ( pLeftString ) < BaseStringView < FCharType > ( rightString ) );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    return ! ( character < string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        BaseString const & string
                ) noexcept -> BaseString & {

                    return this->append ( BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        BaseString && string
                ) noexcept -> BaseString & {

                    return this->append ( std :: move ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        BaseStringView < CharType > const & string
                ) noexcept -> BaseString & {

                    return this->append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseString & {

                    return this->append ( BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    return this->append ( BaseStringView < CharType > ( pString ) );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        uint8 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        uint16 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        sint8 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        sint16 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        std :: size_t value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        bool value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        uint32 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        uint64 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        sint32 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        sint64 value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        float value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        double value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        long double value
                ) noexcept -> BaseString & {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseString const & string
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseString && string
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + string.length() + 1U );

                    return result.append ( * this ).append ( std :: move ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseStringView < CharType > const & string
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + string;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: basic_string < CharType > const & string
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + BaseStringView < CharType > ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType const * pString
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + BaseStringView < CharType > ( pString );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + character;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + character;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + character;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + character;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint8 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint16 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint8 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint16 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: size_t value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        bool value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint32 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint64 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint32 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint64 value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        float value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        double value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        long double value
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) + value;
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> BaseString < FCharType > {

                    return leftString + BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> BaseString < FCharType > {

                    return BaseStringView < FCharType > ( leftString ) + BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> BaseString < FCharType > {

                    return BaseStringView < FCharType > ( pLeftString ) + BaseStringView < FCharType > ( rightString );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return character + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return character + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return character + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return character + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint8                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint16                              value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint8                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint16                              value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType, typename T = std :: size_t, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        std :: size_t                       value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        bool                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint32                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint64                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint32                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint64                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        float                               value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        double                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        long double                         value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    return value + BaseStringView < FCharType > ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseString const & string
                ) && noexcept -> BaseString {

                    return this->append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseString && string
                ) && noexcept -> BaseString {

                    return this->append ( std :: move ( string ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        BaseStringView < CharType > const & string
                ) && noexcept -> BaseString {

                    return this->append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: basic_string < CharType > const & string
                ) && noexcept -> BaseString {

                    return this->append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType const * pString
                ) && noexcept -> BaseString {

                    return this->append ( pString );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) && noexcept -> BaseString {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) && noexcept -> BaseString {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) && noexcept -> BaseString {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) && noexcept -> BaseString {

                    return this->append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint8 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint16 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint8 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint16 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: size_t value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        bool value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint32 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint64 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint32 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint64 value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        float value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        double value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        long double value
                ) && noexcept -> BaseString {

                    return this->append ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >          && rightString
                ) noexcept -> BaseString < FCharType > {

                    return rightString.prepend ( leftString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >                  && rightString
                ) noexcept -> BaseString < FCharType > {

                    return rightString.prepend ( leftString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >                  && rightString
                ) noexcept -> BaseString < FCharType > {

                    return rightString.prepend ( pLeftString );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( character );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( character );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( character );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( character );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint8                               value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint16                              value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint8                               value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint16                              value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType, typename T = std :: size_t, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        std :: size_t                       value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        bool                               value,
                        BaseString < FCharType >        && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint32                              value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint64                              value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint32                              value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint64                             value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        float                                value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        double                               value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        long double                          value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator * (
                        int count
                ) const & noexcept -> BaseString {

                    return BaseStringView < CharType > ( * this ) * count;
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: operator * (
                        int count
                ) && noexcept -> BaseString {

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
                        StringUtils < CharType > :: copy (
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
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                    return std :: move ( * this );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator * (
                        int                              count,
                        BaseString < FCharType > const & string
                ) noexcept -> BaseString < FCharType > {

                    return count * BaseStringView < FCharType > ( string );
                }


                template < typename FCharType >
                __CDS_OptionalInline auto operator * (
                        int                         count,
                        BaseString < FCharType >  && string
                ) noexcept -> BaseString < FCharType > {

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
                        StringUtils < FCharType > :: copy (
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
                    string._pBuffer [ string._length ] = static_cast < FCharType > ( '\0' );
                    return std :: move ( * string );
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        BaseString const & string
                ) noexcept -> BaseString & {

                    if ( this->empty() && string.empty() ) {
                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + string.length() + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    this->_length += string.length();

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        BaseString && string
                ) noexcept -> BaseString & {

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
                                string.length() * sizeof ( CharType )
                        );

                        (void) std :: memcpy (
                                string._pBuffer,
                                this->_pBuffer,
                                this->length() * sizeof ( CharType )
                        );

                        string._pBuffer [ newLength ] = static_cast < ElementType > ( '\0' );

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

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        BaseStringView < CharType > const & string
                ) noexcept -> BaseString & {

                    if ( this->empty() && string.empty() ) {
                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + string.length() + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    this->_length += string.length();

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseString & {

                    if ( this->empty() && string.empty() ) {
                        return * this;
                    }

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + string.length() + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            string.c_str(),
                            0ULL,
                            string.length()
                    );

                    this->_length += string.length();

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    if ( this->empty() && pString == nullptr ) {
                        return * this;
                    }

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + stringLength + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            pString,
                            0ULL,
                            stringLength
                    );

                    this->_length += stringLength;

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                auto BaseString < CharType > :: append (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            & character,
                            0ULL,
                            1ULL
                    );

                    ++ this->_length;

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                auto BaseString < CharType > :: append (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            & character,
                            0ULL,
                            1ULL
                    );

                    ++ this->_length;

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                auto BaseString < CharType > :: append (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            & character,
                            0ULL,
                            1ULL
                    );

                    ++ this->_length;

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                auto BaseString < CharType > :: append (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            & character,
                            0ULL,
                            1ULL
                    );

                    ++ this->_length;

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                auto BaseString < CharType > :: append (
                        uint8 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                auto BaseString < CharType > :: append (
                        uint16 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                auto BaseString < CharType > :: append (
                        sint8 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                auto BaseString < CharType > :: append (
                        sint16 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                auto BaseString < CharType > :: append (
                        std :: size_t value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        bool value
                ) noexcept -> BaseString & {

                    uint8 valueLength = ( value ? 4ULL : 5ULL );
                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + valueLength + 1ULL,
                            & this->_capacity
                    );

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            this->_length,
                            ( value ? "true" : "false" ),
                            0ULL,
                            valueLength
                    );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        uint32 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        uint64 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        sint32 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: append (
                        sint64 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + numberLength + 1ULL,
                            & this->_capacity
                    );

                    * StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            this->_length,
                            value,
                            numberLength,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: append (
                        float value
                ) noexcept -> BaseString & {

                    return this->append ( std :: to_string ( value ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: append (
                        double value
                ) noexcept -> BaseString & {

                    return this->append ( std :: to_string ( value ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: append (
                        long double value
                ) noexcept -> BaseString & {

                    return this->append ( std :: to_string ( value ) );
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        BaseString const & string
                ) noexcept -> BaseString & {

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

                        this->_pBuffer [ newLength ] = static_cast < ElementType > ( '\0' );
                        this->_length                = newLength;

                        (void) std :: memcpy (
                                this->_pBuffer,
                                string.cStr(),
                                string.length() * sizeof ( ElementType )
                        );

                        return * this;
                    }

                    this->_capacity = maxOf ( newLength + 1U, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < ElementType > ( this->_capacity );

                    StringUtils < CharType > :: copy (
                            newBuffer,
                            0ULL,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        BaseString && string
                ) noexcept -> BaseString & {

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

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        BaseStringView < CharType > const & string
                ) noexcept -> BaseString & {

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

                        this->_pBuffer [ newLength ] = static_cast < ElementType > ( '\0' );
                        this->_length                = newLength;

                        (void) std :: memcpy (
                                this->_pBuffer,
                                string.cStr(),
                                string.length() * sizeof ( ElementType )
                        );

                        return * this;
                    }

                    this->_capacity = maxOf ( newLength + 1U, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < ElementType > ( this->_capacity );

                    StringUtils < CharType > :: copy (
                            newBuffer,
                            0ULL,
                            string.cStr(),
                            0ULL,
                            string.length()
                    );

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseString & {

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

                        this->_pBuffer [ newLength ] = static_cast < ElementType > ( '\0' );
                        this->_length                = newLength;

                        (void) std :: memcpy (
                                this->_pBuffer,
                                string.c_str(),
                                string.length() * sizeof ( ElementType )
                        );

                        return * this;
                    }

                    this->_capacity = maxOf ( newLength + 1U, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < ElementType > ( this->_capacity );

                    StringUtils < CharType > :: copy (
                            newBuffer,
                            0ULL,
                            string.c_str(),
                            0ULL,
                            string.length()
                    );

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    auto stringLength = StringUtils < CharType > :: length ( pString );

                    if ( stringLength == 0ULL ) {
                        return * this;
                    }

                    auto newLength = this->_length + stringLength;
                    if ( this->_capacity >= newLength + 1U ) {

                        (void) std :: memmove (
                                this->_pBuffer + stringLength,
                                this->_pBuffer,
                                this->_length * sizeof ( ElementType )
                        );

                        this->_pBuffer [ newLength ] = static_cast < ElementType > ( '\0' );
                        this->_length                = newLength;

                        (void) std :: memcpy (
                                this->_pBuffer,
                                pString,
                                stringLength * sizeof ( ElementType )
                        );

                        return * this;
                    }

                    this->_capacity = maxOf ( newLength + 1U, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < ElementType > ( this->_capacity );

                    StringUtils < CharType > :: copy (
                            newBuffer,
                            0ULL,
                            pString,
                            0ULL,
                            stringLength
                    );

                    StringUtils < CharType > :: copy (
                            newBuffer,
                            stringLength,
                            this->_pBuffer,
                            0ULL,
                            this->_length
                    );

                    this->_length = newLength;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                auto BaseString < CharType > :: prepend (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + 1U,
                            this->_pBuffer,
                            this->length() * sizeof ( CharType )
                    );

                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ ++ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                auto BaseString < CharType > :: prepend (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + 1U,
                            this->_pBuffer,
                            this->length() * sizeof ( CharType )
                    );

                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ ++ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                auto BaseString < CharType > :: prepend (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + 1U,
                            this->_pBuffer,
                            this->length() * sizeof ( CharType )
                    );

                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ ++ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                auto BaseString < CharType > :: prepend (
                        ElementType character
                ) noexcept -> BaseString & {

                    this->_pBuffer = __allocation :: __enlarge (
                            this->_pBuffer,
                            this->_capacity,
                            this->_length + 2ULL,
                            & this->_capacity
                    );

                    (void) std :: memmove (
                            this->_pBuffer + 1U,
                            this->_pBuffer,
                            this->length() * sizeof ( CharType )
                    );

                    this->_pBuffer [ 0 ] = character;
                    this->_pBuffer [ ++ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                auto BaseString < CharType > :: prepend (
                        uint8 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                auto BaseString < CharType > :: prepend (
                        uint16 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                auto BaseString < CharType > :: prepend (
                        sint8 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                auto BaseString < CharType > :: prepend (
                        sint16 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                auto BaseString < CharType > :: prepend (
                        std :: size_t value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        bool value
                ) noexcept -> BaseString & {

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

                    StringUtils < CharType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            ( value ? "true" : "false" ),
                            0ULL,
                            valueLength,
                            false
                    );

                    this->_length += valueLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        uint32 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        uint64 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        sint32 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: prepend (
                        sint64 value
                ) noexcept -> BaseString & {

                    auto numberLength = StringUtils < CharType > :: integerLength ( value );

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

                    (void) StringUtils < CharType > :: writeInteger (
                            this->_pBuffer,
                            0ULL,
                            value,
                            numberLength,
                            nullptr
                    );

                    this->_length += numberLength;
                    this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: prepend (
                        float value
                ) noexcept -> BaseString & {

                    return this->prepend ( std :: to_string ( value ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: prepend (
                        double value
                ) noexcept -> BaseString & {

                    return this->prepend ( std :: to_string ( value ) );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: prepend (
                        long double value
                ) noexcept -> BaseString & {

                    return this->prepend ( std :: to_string ( value ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: contains (
                        ElementType character
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ).contains ( character );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        BaseString const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ).contains ( BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ).contains ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ).contains ( BaseStringView < CharType > ( string ) );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return BaseStringView < CharType > ( * this ).contains ( BaseStringView < CharType > ( pString ) );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character,
                        CollectionType < Index >  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            character,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            character,
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirst (
                        ElementType character
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirst ( character );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLast (
                        ElementType character
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLast ( character );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                 character,
                        CollectionType < Index >  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAll (
                            character,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAll (
                            character,
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseString                  const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseString                  const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirst (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLast (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseString                  const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseString                  const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                            maxCount,
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                            maxCount,
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                            maxCount,
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                            maxCount,
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstNotOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastNotOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirst ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLast ( string );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAll (
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAll (
                            string,
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstOf ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastOf ( string );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllOf (
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllOf (
                            string,
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            string,
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstNotOf ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastNotOf ( string );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            string,
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            string,
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        std :: basic_string < CharType >    const & string,
                        CollectionType < Index >                  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        std :: basic_string < CharType >    const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirst (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLast (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstNotOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastNotOf (
                            BaseStringView < CharType > ( string )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( string ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( string ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        ElementType                         const * pString,
                        CollectionType < Index >                  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        ElementType                         const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).find (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirst (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLast (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAll (
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        ElementType                      const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findOf (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        ElementType                      const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstOf (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        ElementType                      const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastOf (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllOf (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllOf (
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        ElementType                      const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findNotOf (
                            maxCount,
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findFirstNotOf (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return BaseStringView < CharType > ( * this ).findLastNotOf (
                            BaseStringView < CharType > ( pString )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAllNotOf (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return BaseStringView < CharType > ( * this ).findAllNotOf (
                            BaseStringView < CharType > ( pString ),
                            indices
                    );
                }


                template < typename CharType >
                auto BaseString < CharType > :: ltrim (
                        CharType const * pCharacters
                ) noexcept -> BaseString & {

                    Size offset = 0ULL;
                    Size charactersLength = StringUtils < CharType > :: length ( pCharacters );
                    while ( offset < this->length() && StringUtils < CharType > :: contains ( pCharacters, charactersLength, this->_pBuffer [ offset ] ) ) {
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

                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: ltrim (
                        BaseString const & characters
                ) noexcept -> BaseString & {

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

                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: ltrim (
                        BaseStringView < CharType > const & characters
                ) noexcept -> BaseString & {

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

                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: ltrim (
                        std :: basic_string < CharType > const & characters
                ) noexcept -> BaseString & {

                    Size offset = 0ULL;
                    while ( offset < this->length() && StringUtils < CharType > :: contains ( characters.c_str(), characters.length(), this->_pBuffer [ offset ] ) ) {
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

                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: rtrim (
                        ElementType character
                ) noexcept -> BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && this->_pBuffer [ offset ] == character ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: rtrim (
                        ElementType const * pCharacters
                ) noexcept -> BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    auto charactersLength = StringUtils < CharType > :: length ( pCharacters );
                    while ( offset >= 0 && StringUtils < CharType > :: contains ( pCharacters, charactersLength, this->_pBuffer [ offset ] ) ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: rtrim (
                        BaseString const & characters
                ) noexcept -> BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && characters.contains ( this->_pBuffer [ offset ] ) ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: rtrim (
                        BaseStringView < CharType > const & characters
                ) noexcept -> BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && characters.contains ( this->_pBuffer [ offset ] ) ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: rtrim (
                        std :: basic_string < CharType > const & characters
                ) noexcept -> BaseString & {

                    Index offset = static_cast < Index > ( this->length() ) - 1;
                    while ( offset >= 0 && StringUtils < CharType > :: contains ( characters.c_str(), characters.length(), this->_pBuffer [ offset ] ) ) {
                        -- offset;
                    }

                    if ( offset == 0ULL ) {
                        return * this;
                    }

                    this->_length -= offset;
                    this->_pBuffer [ this->length() ] = static_cast < ElementType > ( '\0' );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: trim (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->ltrim ( character ).rtrim ( character );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: trim (
                        ElementType const * pCharacters
                ) noexcept -> BaseString & {

                    return this->ltrim ( pCharacters ).rtrim ( pCharacters );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: trim (
                        BaseString const & characters
                ) noexcept -> BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: trim (
                        BaseStringView < CharType > const & characters
                ) noexcept -> BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: trim (
                        std :: basic_string < CharType > const & characters
                ) noexcept -> BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename CharType >
                auto BaseString < CharType > :: ljust (
                        Size        size,
                        ElementType element
                ) noexcept -> BaseString & {

                    if ( size <= this->length() ) {
                        return * this;
                    }

                    size -= this->length();

                    auto newCapacity = maxOf (
                            this->_capacity,
                            size + this->length() + 1U,
                            BaseString :: minCapacity
                    );

                    auto newBuffer = __allocation :: __alloc < CharType > ( newCapacity );

                    for ( Size index = 0ULL; index < size; ++ index ) {
                        newBuffer [ index ] = element;
                    }

                    StringUtils < CharType > :: copy (
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


                template < typename CharType >
                auto BaseString < CharType > :: rjust (
                        Size        size,
                        ElementType element
                ) noexcept -> BaseString & {

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

                    this->_pBuffer [ size ] = static_cast < ElementType > ( '\0' );
                    this->_length = size;
                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: toLower () noexcept -> BaseString & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        this->_pBuffer [ index ] = StringUtils < CharType > :: lower ( this->_pBuffer [ index ] );
                    }

                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: toUpper () noexcept -> BaseString & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        this->_pBuffer [ index ] = StringUtils < CharType > :: upper ( this->_pBuffer [ index ] );
                    }

                    return * this;
                }


                template < typename CharType >
                template < typename ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        ElementType     separator,
                        ListType      & storeIn,
                        Size            maxCount
                ) const noexcept -> ListType & {

                    return BaseStringView < CharType > ( * this ).split (
                            separator,
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        ElementType separator,
                        Size        maxCount
                ) const noexcept -> ListType < BaseString > {

                    ListType < BaseString > tokens;
                    return BaseStringView < CharType > ( * this ).split (
                            separator,
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        BaseString  const & separators,
                        ListType          & storeIn,
                        Size                maxCount
                ) const noexcept -> ListType & {

                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( separators ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        BaseString  const & separators,
                        Size                maxCount
                ) const noexcept -> ListType < BaseString > {

                    ListType < BaseString > tokens;
                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( separators ),
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        BaseStringView < CharType > const & separators,
                        ListType                          & storeIn,
                        Size                                maxCount
                ) const noexcept -> ListType & {

                    return BaseStringView < CharType > ( * this ).split (
                            separators,
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        BaseStringView < CharType > const & separators,
                        Size                                maxCount
                ) const noexcept -> ListType < BaseString > {

                    ListType < BaseString > tokens;
                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( separators ),
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        std :: basic_string < CharType >    const & separators,
                        ListType                                  & storeIn,
                        Size                                        maxCount
                ) const noexcept -> ListType & {

                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( separators ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        std :: basic_string < CharType >    const & separators,
                        Size                                        maxCount
                ) const noexcept -> ListType < BaseString > {

                    ListType < BaseString > tokens;
                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( separators ),
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                template < typename ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        ElementType                         const * pSeparators,
                        ListType                                  & storeIn,
                        Size                                        maxCount
                ) const noexcept -> ListType & {

                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( pSeparators ),
                            storeIn,
                            maxCount
                    );
                }


                template < typename CharType >
                template < template < typename ... > class ListType >
                __CDS_OptimalInline auto BaseString < CharType > :: split (
                        ElementType                         const * pSeparators,
                        Size                                        maxCount
                ) const noexcept -> ListType < BaseString > {

                    ListType < BaseString > tokens;
                    return BaseStringView < CharType > ( * this ).split (
                            BaseStringView < CharType > ( pSeparators ),
                            tokens,
                            maxCount
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprOverride auto BaseString < CharType > :: hash () const noexcept -> Index {
                    return static_cast < Index > ( this->_length );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: toString () const noexcept -> cds :: String {
                    return cds :: String ( this->cStr() );
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: replace (
                        Index               from,
                        Index               until,
                        BaseString  const & inPlace
                ) noexcept -> BaseString & {

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

                        this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                        return * this;
                    }

                    auto newCapacity = maxOf ( this->_length + 1ULL, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < CharType > ( newCapacity );

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

                    newBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                    this->_capacity = newCapacity;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: replace (
                        Index                                   from,
                        Index                                   until,
                        BaseStringView < CharType >     const & inPlace
                ) noexcept -> BaseString & {

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

                        this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                        return * this;
                    }

                    auto newCapacity = maxOf ( this->_length + 1ULL, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < CharType > ( newCapacity );

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

                    newBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                    this->_capacity = newCapacity;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: replace (
                        Index                                       from,
                        Index                                       until,
                        std :: basic_string < CharType >    const & inPlace
                ) noexcept -> BaseString & {

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
                                inPlace.c_str(),
                                sectionLength * sizeof ( ElementType )
                        );

                        this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                        return * this;
                    }

                    auto newCapacity = maxOf ( this->_length + 1ULL, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < CharType > ( newCapacity );

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
                            inPlace.c_str(),
                            sectionLength * sizeof ( ElementType )
                    );

                    newBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                    this->_capacity = newCapacity;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename CharType >
                __CDS_OptionalInline auto BaseString < CharType > :: replace (
                        Index               from,
                        Index               until,
                        ElementType const * pInPlace
                ) noexcept -> BaseString & {

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
                    auto inPlaceLength      = StringUtils < CharType > :: length ( pInPlace );

                    this->_length = this->length() - sectionLength + inPlaceLength;

                    if ( this->_length + 1ULL < this->_capacity ) {
                        (void) std :: memmove (
                                this->_pBuffer + until,
                                this->_pBuffer + from,
                                 remainingLength * sizeof ( ElementType )
                        );

                        (void) std :: memcpy (
                                this->_pBuffer + from,
                                pInPlace,
                                sectionLength * sizeof ( ElementType )
                        );

                        this->_pBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                        return * this;
                    }

                    auto newCapacity = maxOf ( this->_length + 1ULL, BaseString :: minCapacity );
                    auto newBuffer = __allocation :: __alloc < CharType > ( newCapacity );

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
                            pInPlace,
                            sectionLength * sizeof ( ElementType )
                    );

                    newBuffer [ this->_length ] = static_cast < ElementType > ( '\0' );
                    this->_capacity = newCapacity;
                    __allocation :: __free ( cds :: exchange ( this->_pBuffer, newBuffer ) );

                    return * this;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: reverse () noexcept -> BaseString & {

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


                template < typename CharType >
                template < typename Action >
                auto BaseString < CharType > :: forEach (
                        Action const & action
                ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }


                template < typename CharType >
                template < typename Action >
                auto BaseString < CharType > :: forEach (
                        Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: some (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: some (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: atLeast (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: atLeast (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: atMost (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: atMost (
                        Size                count,
                        Predicate   const & predicate
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


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseString < CharType > :: moreThan (
                        Size                count,
                        Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return this->atLeast ( count + 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseString < CharType > :: moreThan (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atLeast ( count + 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseString < CharType > :: fewerThan (
                        Size                count,
                        Predicate   const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    return this->atMost ( count - 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                __CDS_OptimalInline auto BaseString < CharType > :: fewerThan (
                        Size                count,
                        Predicate   const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    return this->atMost ( count - 1, predicate );
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: count (
                        Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

                    Size trueCount = 0U;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: count (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> Size {

                    Size trueCount = 0U;
                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            ++ trueCount;
                        }
                    }

                    return trueCount;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: any (
                        Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: any (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return true;
                        }
                    }

                    return false;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: all (
                        Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( ! predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: all (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( ! predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: none (
                        Predicate const & predicate
                ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }


                template < typename CharType >
                template < typename Predicate >
                auto BaseString < CharType > :: none (
                        Predicate const & predicate
                ) const noexcept ( noexcept ( predicate ( meta :: valueOf < ElementType > () ) ) ) -> bool {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( predicate ( this->_pBuffer [ index ] ) ) {
                            return false;
                        }
                    }

                    return true;
                }

#if defined(CDS_STRING_DEBUG)

                template < typename CharType >
                auto BaseString < CharType > :: diag () const noexcept -> BaseString {
                    return BaseStringView ( "Debug = { data = '" ) + this->_pBuffer +
                            ", length = " + this->_length +
                            ", capacity = " + this->_capacity + " }";
                }

#endif

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_IMPL_HPP__
