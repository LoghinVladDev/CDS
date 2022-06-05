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
                BaseString < CharType > :: BaseString (
                        BaseString const & string
                ) noexcept :
                        BaseString (
                                string.cStr(),
                                string.length()
                        ) {

                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                BaseString < CharType > :: BaseString (
                        BaseString < OtherCharType > const & string
                ) noexcept :
                        BaseString (
                                string.cStr(),
                                string.length()
                        ) {

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
                ) noexcept :
                        BaseString (
                                string.cStr(),
                                string.length()
                        ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        ElementType const * pString,
                        Size                length
                ) noexcept {

                    if ( pString == nullptr ) {
                        return;
                    }

                    this->_capacity = maxOf ( BaseString :: minCapacity, length + 1ULL );
                    this->_length   = length;

                    this->_pBuffer  = StringUtils < CharType > :: copy (
                            __allocation :: __alloc < CharType > ( this->_capacity ),
                            0ULL,
                            pString,
                            0ULL,
                            length
                    );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        ElementType const * pString
                ) noexcept :
                        BaseString (
                                pString,
                                StringUtils < CharType > :: length ( pString )
                        ) {

                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                BaseString < CharType > :: BaseString (
                        OtherCharType   const * pString,
                        Size                    length
                ) noexcept {

                    if ( pString == nullptr ) {
                        return;
                    }

                    this->_capacity = maxOf ( BaseString :: minCapacity, length + 1ULL );
                    this->_length   = length;

                    this->_pBuffer  = StringUtils < CharType > :: copy (
                            __allocation :: __alloc < CharType > ( this->_capacity ),
                            0ULL,
                            pString,
                            0ULL,
                            length
                    );
                }


                template < typename CharType >
                template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
                BaseString < CharType > :: BaseString (
                        OtherCharType const * pString
                ) noexcept :
                        BaseString (
                                pString,
                                pString == nullptr ? 0ULL : StringUtils < OtherCharType > :: length ( pString )
                        ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        std :: basic_string < CharType > const & string
                ) noexcept :
                        BaseString (
                                string.c_str(),
                                string.length()
                        ) {

                }


                /// TODO : replace after replacing experimental :: Object :: toString () -> BaseString
                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        experimental :: Object const & object
                ) noexcept :
                        BaseString (
                                object.toString().cStr(),
                                object.toString().length()
                        ) {

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
                BaseString < CharType > :: BaseString (
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
                BaseString < CharType > :: BaseString (
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
                BaseString < CharType > :: BaseString (
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
                BaseString < CharType > :: BaseString (
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
                BaseString < CharType > :: BaseString (
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
                        _pBuffer ( __allocation :: __alloc < CharType > ( BaseString :: minCapacity ) ) {

                    if ( value ) {

                        (void) StringUtils < ElementType > :: copy (
                                this->_pBuffer,
                                0ULL,
                                "true",
                                0ULL,
                                4ULL
                        );
                    } else {

                        (void) StringUtils < ElementType > :: copy (
                                this->_pBuffer,
                                0ULL,
                                "false",
                                0ULL,
                                5ULL
                        );
                    }
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
                auto BaseString < CharType > :: reserve (
                        Size size
                ) noexcept -> void {

                    if ( size < this->_capacity ) {
                        return;
                    }

                    this->resize ( size );
                }


                template < typename CharType >
                auto BaseString < CharType > :: shrink (
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
                    return this->_pBuffer;
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
                auto BaseString < CharType > :: operator = (
                        BaseString const & string
                ) noexcept -> BaseString & {

                    if ( this == & string ) {
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
                auto BaseString < CharType > :: operator = (
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

                        this->_pBuffer  = __allocation :: __free (
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
                auto BaseString < CharType > :: operator = (
                        std :: basic_string < CharType > const & string
                ) noexcept -> BaseString & {

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
                            string.c_str(),
                            0ULL,
                            string.length()
                    );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: operator = (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    if ( this->_pBuffer == pString ) {
                        return * this;
                    }

                    auto stringLength = StringUtils < ElementType > :: length ( pString );

                    if ( stringLength == 0ULL ) {
                        __allocation :: __free ( cds :: exchange ( this->_pBuffer, nullptr ) );
                        this->_length   = 0ULL;
                        this->_capacity = 0ULL;

                        return * this;
                    }


                    if ( this->_capacity < stringLength + 1ULL ) {

                        this->_capacity = maxOf ( stringLength + 1ULL, BaseString :: minCapacity );

                        __allocation :: __free (
                                cds :: exchange (
                                        this->_pBuffer,
                                        __allocation :: __alloc < CharType > ( this->_capacity )
                                )
                        );
                    }

                    this->_length = stringLength;

                    (void) StringUtils < ElementType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            pString,
                            0ULL,
                            stringLength
                    );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: operator = (
                        ElementType character
                ) noexcept -> BaseString & {

                    if ( this->_capacity < 2ULL ) {

                        this->_capacity = BaseString :: minCapacity;
                        __allocation :: __free (
                                cds :: exchange (
                                        this->_pBuffer,
                                        __allocation :: __alloc < CharType > ( this->_capacity )
                                )
                        );
                    }

                    this->_length = 1ULL;

                    (void) StringUtils < ElementType > :: copy (
                            this->_pBuffer,
                            0ULL,
                            & character,
                            0ULL,
                            1ULL
                    );

                    return * this;
                }


                template < typename CharType >
                auto BaseString < CharType > :: equals (
                        Object const & object
                ) const noexcept -> bool {

                    if ( this == & object ) {
                        return true;
                    }

                    auto pString = dynamic_cast < decltype (this) > ( & object );
                    if ( pString == nullptr ) {
                        return false;
                    }

                    return this->operator == ( * pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseString const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType const * pString
                ) const noexcept -> bool {

                    auto otherStringLength = StringUtils < CharType > :: length ( pString );
                    if ( this->length() != otherStringLength ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            otherStringLength
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < FCharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < FCharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < FCharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < FCharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return StringUtils < FCharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < FCharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseString const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType const * pString
                ) const noexcept -> bool {

                    auto otherStringLength = StringUtils < CharType > :: length ( pString );
                    if ( this->length() != otherStringLength ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            otherStringLength
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->_length != 1ULL ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < FCharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < FCharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < FCharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < FCharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < FCharType > :: equal;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return StringUtils < FCharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) != StringUtils < FCharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseString const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType character
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: lesser;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: lesser;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            pLeftString,
                            StringUtils < FCharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: lesser;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < FCharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseString const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        ElementType character
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: greater;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: greater;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            pLeftString,
                            StringUtils < FCharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < FCharType > :: greater;
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        FCharType                                    character,
                        BaseString < FCharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < FCharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < FCharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseString const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        ElementType const * pString
                ) const noexcept -> bool {


                    return ! this->operator > ( pString );
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

                    return ! ( leftString > rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString > rightString );
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

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        ElementType const * pString
                ) const noexcept -> bool {


                    return ! this->operator < ( pString );
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

                    return ! ( leftString < rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < rightString );
                }


                template < typename FCharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString < rightString );
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

                    return this->append ( string );
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

                    return this->append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator += (
                        ElementType const * pString
                ) noexcept -> BaseString & {

                    return this->append ( pString );
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

                    BaseString result;
                    result.reserve ( this->length() + string.length() + 1U );

                    return result.append ( * this ).append ( string );
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

                    BaseString result;
                    result.reserve ( this->length() + string.length() + 1U );

                    return result.append ( * this ).append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: basic_string < CharType > const & string
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + string.length() + 1U );

                    return result.append ( * this ).append ( string );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType const * pString
                ) const & noexcept -> BaseString {

                    BaseString result;
                    BaseStringView < CharType > wrapper = pString;

                    result.reserve ( this->length() + wrapper.length() + 1U );

                    return result.append ( * this ).append ( wrapper );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + 2U );

                    return result.append ( * this ).append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + 2U );

                    return result.append ( * this ).append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + 2U );

                    return result.append ( * this ).append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        ElementType character
                ) const & noexcept -> BaseString {

                    BaseString result;
                    result.reserve ( this->length() + 2U );

                    return result.append ( * this ).append ( character );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint8 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint16 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint8 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint16 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        std :: size_t value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        bool value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = value ? 4ULL : 5ULL;

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint32 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        uint64 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint32 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        sint64 value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto valueLength = StringUtils < CharType > :: integerLength ( value );

                    result.reserve ( this->length() + valueLength + 1U );

                    return result.append ( * this ).append ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        float value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( this->length() + wrapper.length() + 1U );

                    return result.append ( * this ).append ( wrapper );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        double value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( this->length() + wrapper.length() + 1U );

                    return result.append ( * this ).append ( wrapper );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator + (
                        long double value
                ) const & noexcept -> BaseString {

                    BaseString result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( this->length() + wrapper.length() + 1U );

                    return result.append ( * this ).append ( wrapper );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        BaseStringView < FCharType > const & leftString,
                        BaseString < FCharType >     const & rightString
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( leftString.length() + rightString.length() + 1U );

                    return result.append ( leftString ).append ( rightString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        std :: basic_string < FCharType >    const & leftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( leftString.length() + rightString.length() + 1U );

                    return result.append ( leftString ).append ( rightString );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        FCharType                            const * pLeftString,
                        BaseString < FCharType >             const & rightString
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    BaseStringView < FCharType > wrapper = pLeftString;

                    result.reserve ( wrapper.length() + rightString.length() + 1U );

                    return result.append ( wrapper ).append ( rightString );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( string.length() + 2ULL );

                    return result.append ( character ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( string.length() + 2ULL );

                    return result.append ( character ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( string.length() + 2ULL );

                    return result.append ( character ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        FCharType                           character,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    result.reserve ( string.length() + 2ULL );

                    return result.append ( character ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint8                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, uint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        uint16                              value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint8 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint8                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType, meta :: EnableIf < ! meta :: isSame < FCharType, sint16 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        sint16                              value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType, typename T = std :: size_t, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > = 0 >
                __CDS_OptimalInline auto operator + (
                        std :: size_t                       value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        bool                               value,
                        BaseString < FCharType >    const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = value ? 4ULL : 5ULL;

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint32                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint64                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint32                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint64                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto valueLength = StringUtils < FCharType > :: integerLength ( value );

                    result.reserve ( string.length() + valueLength + 1ULL );

                    return result.append ( value ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        float                               value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( string.length() + wrapper.length() + 1ULL );

                    return result.append ( wrapper ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        double                              value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( string.length() + wrapper.length() + 1ULL );

                    return result.append ( wrapper ).append ( string );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        long double                         value,
                        BaseString < FCharType >     const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;
                    auto wrapper = std :: to_string ( value );

                    result.reserve ( string.length() + wrapper.length() + 1ULL );

                    return result.append ( wrapper ).append ( string );
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
                        bool                              value,
                        BaseString < FCharType >        && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint32                             value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        uint64                             value,
                        BaseString < FCharType >         && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        sint32                             value,
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
                        float                               value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        double                              value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator + (
                        long double                         value,
                        BaseString < FCharType >          && string
                ) noexcept -> BaseString < FCharType > {

                    return string.prepend ( value );
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator * (
                        int count
                ) const & noexcept -> BaseString {

                    BaseString result;

                    if ( this->empty() || count == 0 ) {
                        return result;
                    }

                    if ( count == 1 ) {
                        return * this;
                    }

                    result.reserve ( count * this->length() + 1ULL );

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

                    result._pBuffer [ result._length ] = static_cast < ElementType > ( '\0' );
                    return result;
                }


                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: operator * (
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
                        int                             count,
                        BaseString < FCharType > const & string
                ) noexcept -> BaseString < FCharType > {

                    BaseString < FCharType > result;

                    if ( string.empty() || count == 0 ) {
                        return result;
                    }

                    if ( count == 1 ) {
                        return * string;
                    }

                    result.reserve ( count * string.length() + 1ULL );

                    for ( int i = 0; i < count; ++ i ) {
                        StringUtils < FCharType > :: copy (
                                result._pBuffer,
                                result._length,
                                string->_pBuffer,
                                0ULL,
                                string->length(),
                                false
                        );

                        result._length += string->length();
                    }

                    result._pBuffer [ result._length ] = static_cast < FCharType > ( '\0' );
                    return result;
                }


                template < typename FCharType >
                __CDS_OptimalInline auto operator * (
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

                    return this->findFirst ( character ) != BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        BaseString const & string
                ) const noexcept -> bool {

                    return this->findFirst ( string ) != BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return this->findFirst ( string ) != BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return this->findFirst ( string ) != BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: contains (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return this->findFirst ( pString ) != BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
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
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                        maxCount,
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find ( maxCount, character, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirst (
                        ElementType character
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( this->_pBuffer [ index ] == character ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLast (
                        ElementType character
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->_length ) - 1; index >= 0; -- index ) {
                        if ( this->_pBuffer [ index ] == character ) {
                            return index;
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                 character,
                        CollectionType < Index >  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        if ( this->_pBuffer [ index ] == character ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                 character
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( character, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseString                  const & string,
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
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseString                  const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        BaseString const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findFirst (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        BaseString const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findLast (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseString                  const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: findAll (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length(),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseString                  const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                            maxCount,
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                            maxCount,
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                            maxCount,
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                            maxCount,
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        BaseString const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        BaseString              const & string,
                        CollectionType < Index >      & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        BaseString              const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
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
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->find ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findFirst (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findLast (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length()
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: findAll (
                            this->_pBuffer,
                            this->_length,
                            string.cStr(),
                            string.length(),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                maxCount,
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string,
                        CollectionType < Index >          & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! string.contains ( this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        BaseStringView < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        std :: basic_string < CharType >    const & string,
                        CollectionType < Index >                  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: find (
                            this->_pBuffer,
                            this->_length,
                            string.c_str(),
                            string.length(),
                            maxCount,
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
                    return this->find ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findFirst (
                            this->_pBuffer,
                            this->_length,
                            string.c_str(),
                            string.length()
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findLast (
                            this->_pBuffer,
                            this->_length,
                            string.c_str(),
                            string.length()
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: findAll (
                            this->_pBuffer,
                            this->_length,
                            string.c_str(),
                            string.length(),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found = 0ULL;
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {
                        if ( ! StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf ( maxCount, string, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> Index {

                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {
                        if ( ! StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        std :: basic_string < CharType > const & string,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( ! StringUtils < CharType > :: contains ( string.c_str(), string.length(), this->_pBuffer [ index ] ) ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf ( string, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: find (
                        Size                                        maxCount,
                        ElementType                         const * pString,
                        CollectionType < Index >                  & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: find (
                            this->_pBuffer,
                            this->_length,
                            pString,
                            StringUtils < CharType > :: length ( pString ),
                            maxCount,
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
                    return this->find ( maxCount, pString, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findFirst (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findFirst (
                            this->_pBuffer,
                            this->_length,
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprDynamicAllocation auto BaseString < CharType > :: findLast (
                        ElementType const * pString
                ) const noexcept -> Index {

                    return StringUtils < CharType > :: findLast (
                            this->_pBuffer,
                            this->_length,
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    return StringUtils < CharType > :: findAll (
                            this->_pBuffer,
                            this->_length,
                            pString,
                            StringUtils < CharType > :: length ( pString ),
                            storeIn
                    );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                __CDS_OptimalInline auto BaseString < CharType > :: findAll (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAll ( pString, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found  = 0ULL;
                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {

                        if (
                                StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findOf (
                        Size                                     maxCount,
                        ElementType                      const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findOf ( maxCount, pString, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstOf (
                        ElementType                      const * pString
                ) const noexcept -> Index {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length(); ++ index ) {

                        if (
                                StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastOf (
                        ElementType                      const * pString
                ) const noexcept -> Index {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {

                        if (
                                StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length(); ++ index ) {

                        if (
                                StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllOf (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllOf ( pString, indices );
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    Size found          = 0ULL;
                    auto stringLength   = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length() && found < maxCount; ++ index ) {

                        if (
                                ! StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                            ++ found;
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findNotOf (
                        Size                                     maxCount,
                        ElementType                      const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findNotOf ( maxCount, pString, indices );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findFirstNotOf (
                        ElementType const * pString
                ) const noexcept -> Index {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length(); ++ index ) {

                        if (
                                ! StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: findLastNotOf (
                        ElementType const * pString
                ) const noexcept -> Index {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Index index = static_cast < Index > ( this->length() ) - 1; index >= 0; -- index ) {

                        if (
                                ! StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            return static_cast < Index > ( index );
                        }
                    }

                    return BaseString :: invalidIndex;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        ElementType                      const * pString,
                        CollectionType < Index >               & storeIn
                ) const noexcept -> CollectionType < Index > & {

                    auto stringLength = StringUtils < CharType > :: length ( pString );
                    for ( Size index = 0ULL; index < this->length(); ++ index ) {

                        if (
                                ! StringUtils < CharType > :: contains (
                                        pString,
                                        stringLength,
                                        this->_pBuffer [ index ]
                                )
                        ) {
                            storeIn.add ( static_cast < Index > ( index ) );
                        }
                    }

                    return storeIn;
                }


                template < typename CharType >
                template < template < typename ... > class CollectionType >
                auto BaseString < CharType > :: findAllNotOf (
                        ElementType const * pString
                ) const noexcept -> CollectionType < Index > {

                    CollectionType < Index > indices;
                    return this->findAllNotOf ( pString, indices );
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
                auto BaseString < CharType > :: trim (
                        ElementType character
                ) noexcept -> BaseString & {

                    return this->ltrim ( character ).rtrim ( character );
                }


                template < typename CharType >
                auto BaseString < CharType > :: trim (
                        ElementType const * pCharacters
                ) noexcept -> BaseString & {

                    return this->ltrim ( pCharacters ).rtrim ( pCharacters );
                }


                template < typename CharType >
                auto BaseString < CharType > :: trim (
                        BaseString const & characters
                ) noexcept -> BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename CharType >
                auto BaseString < CharType > :: trim (
                        BaseStringView < CharType > const & characters
                ) noexcept -> BaseString & {

                    return this->ltrim ( characters ).rtrim ( characters );
                }


                template < typename CharType >
                auto BaseString < CharType > :: trim (
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
                auto BaseString < CharType > :: split (
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

                    for ( Size index = 0ULL; index < this->length(); ++ index ) {
                        if ( this->_pBuffer [ index ] != separator || splitIndex >= static_cast < Index > ( maxCount ) - 1 ) {
                            ++ currentSegmentLength;
                        } else {

                            if ( currentSegmentLength == 0ULL ) {
                                continue;
                            }

                            ++ splitIndex;
                            storeIn.add ( BaseString ( this->_pBuffer + currentSegmentOffset, currentSegmentLength ) );
                            currentSegmentLength = 0ULL;
                            currentSegmentOffset = static_cast < Index > ( index ) + 1ULL;
                        }
                    }

                    if ( currentSegmentLength != 0ULL ) {
                        storeIn.add ( BaseString ( this->_pBuffer + currentSegmentOffset, currentSegmentLength ) );
                    }

                    return storeIn;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprOverride auto BaseString < CharType > :: hash () const noexcept -> Index {
                    return static_cast < Index > ( this->_length );
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
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
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
