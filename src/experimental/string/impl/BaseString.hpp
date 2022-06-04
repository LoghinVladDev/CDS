//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_BASE_IMPL_HPP__
#define __CDS_EX_STRING_BASE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {


                template < typename CharType >
                Size const BaseString < CharType > :: minCapacity;

                template < typename CharType >
                Index const BaseString < CharType > :: invalidIndex;


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
                            Memory :: instance().createArray < CharType > (
                                    this->_capacity
                            ),
                            pString,
                            length
                    );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        ElementType const * pString
                ) noexcept :
                        BaseString (
                                pString,
                                pString == nullptr ? 0ULL : StringUtils < CharType > :: length ( pString )
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
                            Memory :: instance().createArray < CharType > (
                                    this->_capacity
                            ),
                            pString,
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
                    this->_pBuffer  = Memory :: instance().createArray < ElementType > ( this->_capacity );

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

                    this->_pBuffer = Memory :: instance().createArray < CharType > ( this->_capacity );

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

                    this->_pBuffer = Memory :: instance().createArray < CharType > ( this->_capacity );

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
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

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
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

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
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

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
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    this->_pBuffer [ 0 ] = value;
                    this->_pBuffer [ 1 ] = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint8 > () > >
                BaseString < CharType > :: BaseString (
                        uint8 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint16 > () > >
                BaseString < CharType > :: BaseString (
                        uint16 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint8 > () > >
                BaseString < CharType > :: BaseString (
                        sint8 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, sint16 > () > >
                BaseString < CharType > :: BaseString (
                        sint16 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                template < typename T, meta :: EnableIf < ! meta :: isSame < T, uint64 > () > >
                BaseString < CharType > :: BaseString (
                        std :: size_t value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        bool value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    if ( value ) {

                        (void) StringUtils < ElementType > :: copy (
                                this->_pBuffer,
                                "true",
                                4ULL
                        );
                    } else {

                        (void) StringUtils < ElementType > :: copy (
                                this->_pBuffer,
                                "false",
                                5ULL
                        );
                    }
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        uint32 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        uint64 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        sint32 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        sint64 value
                ) noexcept :
                        _capacity ( BaseString :: minCapacity ),
                        _pBuffer ( Memory :: instance().createArray < ElementType > ( BaseString :: minCapacity ) ) {

                    * StringUtils < ElementType > :: write (
                            this->_pBuffer,
                            0ULL,
                            value,
                            & this->_length
                    ) = static_cast < ElementType > ( '\0' );
                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        float value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        double value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                BaseString < CharType > :: BaseString (
                        long double value
                ) noexcept :
                        BaseString ( std :: to_string ( value ) ) {

                }


                template < typename CharType >
                __CDS_OptimalInline BaseString < CharType > :: ~BaseString () noexcept {
                    Memory :: instance().destroyArray ( this->_pBuffer );
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
                constexpr auto BaseString < CharType > :: empty () const noexcept -> bool {
                    return this->_length == 0ULL;
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
                auto BaseString < CharType > :: operator = (
                        BaseString && string
                ) noexcept -> BaseString & {

                    if ( this == & string ) {
                        return * this;
                    }

                    Memory :: instance().destroyArray (
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < CharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < CharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            StringUtils < CharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            StringUtils < CharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        CharType                                    character,
                        BaseString < CharType >             const & string
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


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return ! ( character < string );
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: cStr () const noexcept -> ElementType const * {
                    return this->_pBuffer;
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: data () noexcept -> ElementType * {
                    return this->_pBuffer;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprOverride auto BaseString < CharType > :: hash () const noexcept -> Index {
                    return static_cast < Index > ( this->_length );
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
