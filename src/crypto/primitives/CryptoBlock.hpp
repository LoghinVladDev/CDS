//
// Created by loghin on 23.06.2021.
//

#ifndef CDS_CRYPTOBLOCK_HPP
#define CDS_CRYPTOBLOCK_HPP

#include <CDS/Object>
#include <CDS/Utility>

namespace cds {

    template < Size byteSize >
    class CryptoBlock : public Object {
    private:
        Byte _paddingElement { 0x00U };
        Byte _data[byteSize] = { this->_paddingElement };

    public:

        constexpr explicit CryptoBlock ( Byte paddingElement = 0x00U ) noexcept : _paddingElement(paddingElement) {
            (void) std :: memset ( static_cast < void * > (this->_data), this->_paddingElement, byteSize );
        }

        constexpr CryptoBlock ( CryptoBlock const & block ) noexcept : _paddingElement(block._paddingElement) {
            (void) std :: memcpy ( static_cast < void * > (this->_data), static_cast < void const * > (block._data), byteSize );
        }

        template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
        constexpr explicit CryptoBlock ( CryptoBlock < otherSize > const & block ) noexcept : _paddingElement(block.paddingElement()) {
            this->setData(block);
        }

        __CDS_cpplang_ConstexprDestructor ~CryptoBlock() noexcept override = default;

        constexpr explicit CryptoBlock ( Byte const * pData, Size size = UINT64_MAX, Byte paddingElement = 0x00U ) noexcept : _paddingElement(paddingElement) {
            this->setData( pData, size );
        }

        constexpr auto setPaddingElement ( Byte paddingElement ) noexcept -> CryptoBlock & {
            this->_paddingElement = paddingElement;
            return * this;
        }

        __CDS_NoDiscard constexpr auto paddingElement () const noexcept -> Byte {
            return this->_paddingElement;
        }

        __CDS_NoDiscard constexpr auto paddingElement () noexcept -> Byte & {
            return this->_paddingElement;
        }

        __CDS_NoDiscard constexpr auto data () const noexcept -> Byte const * {
            return this->_data;
        }

        __CDS_NoDiscard constexpr auto data () noexcept -> Byte * {
            return this->_data;
        }

        constexpr auto operator = ( CryptoBlock const & block ) noexcept -> CryptoBlock & {
            if ( this == & block ) {
                return * this;
            }

            this->_paddingElement = block._paddingElement;

            return this->setData(block); // NOLINT(misc-unconventional-assign-operator)
        }

        template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
        constexpr auto operator = ( CryptoBlock < otherSize > const & block ) noexcept -> CryptoBlock & {
            if ( this == & block ) {
                return * this;
            }

            this->_paddingElement = block._paddingElement;

            return this->setData( block );  // NOLINT(misc-unconventional-assign-operator)
        }

        constexpr auto setData ( CryptoBlock const & block ) noexcept -> CryptoBlock & {
            if ( this == & block ) {
                return * this;
            }

            (void) std :: memcpy ( static_cast < void * > ( this->_data ), static_cast < void const * > (block._data), byteSize );
            return * this;
        }

        template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
        constexpr auto setData ( CryptoBlock < otherSize > const & block ) noexcept -> CryptoBlock & {
            if ( this == & block ) {
                return * this;
            }

            (void) std :: memcpy ( static_cast < void * > ( this->_data ), static_cast < void const * > ( block.data() ), minSize );
            (void) std :: memset ( static_cast < void * > ( this->_data + minSize ), this->_paddingElement, byteSize - minSize );

            return * this;
        }

        constexpr auto setData ( Byte const * pData, Size size = UINT64_MAX ) noexcept -> CryptoBlock & {
            auto minBufferSize = std::min ( byteSize, size );

            (void) std :: memcpy ( static_cast < void * > (this->_data), static_cast < void const * > (pData), minBufferSize );

            if ( size < byteSize ) {
                (void) std :: memset( static_cast < void * > (this->_data + size), this->_paddingElement, byteSize - size );
            }

            return * this;
        }

        __CDS_cpplang_ConstexprDestructor auto operator ^ ( CryptoBlock const & other ) const noexcept -> CryptoBlock {
            CryptoBlock result;

            for ( Size i = 0u; i < byteSize; ++ i ) {
                result._data[i] = this->_data[i] ^ other._data[i];
            }

            return result;
        }

        __CDS_cpplang_ConstexprDestructor auto operator & ( CryptoBlock const & other ) const noexcept -> CryptoBlock { // NOLINT(clion-misra-cpp2008-5-3-3)
            CryptoBlock result;

            for ( Size i = 0u; i < byteSize; ++ i ) {
                result._data[i] = this->_data[i] & other._data[i];
            }

            return result;
        }

        __CDS_cpplang_ConstexprDestructor auto operator | ( CryptoBlock const & other ) const noexcept -> CryptoBlock {
            CryptoBlock result;

            for ( Size i = 0u; i < byteSize; ++ i ) {
                result._data[i] = this->_data[i] | other._data[i];
            }

            return result;
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator ^ ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
            CryptoBlock < minSize > result;

            for ( Size i = 0u; i < minSize; ++ i ) {
                result.data()[i] = this->data()[i] ^ other.data()[i];
            }

            return result;
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator & ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > { // NOLINT(clion-misra-cpp2008-5-3-3)
            CryptoBlock < minSize > result;

            for ( Size i = 0u; i < minSize; ++ i ) {
                result.data()[i] = this->data()[i] & other.data()[i];
            }

            return result;
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator | ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
            CryptoBlock < minSize > result;

            for ( Size i = 0u; i < minSize; ++ i ) {
                result.data()[i] = this->data()[i] | other.data()[i];
            }

            return result;
        }

        __CDS_cpplang_ConstexprDestructor auto operator ^= ( CryptoBlock const & other ) noexcept -> CryptoBlock & {
            return ( this->operator= ( (* this) ^ other ) );
        }

        __CDS_cpplang_ConstexprDestructor auto operator &= ( CryptoBlock const & other ) noexcept -> CryptoBlock & {
            return ( this->operator= ( (* this) & other ) );
        }

        __CDS_cpplang_ConstexprDestructor auto operator |= ( CryptoBlock const & other ) noexcept -> CryptoBlock & {
            return ( this->operator= ( (* this) | other ) );
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator ^= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
            return ( this->operator= ( (* this) ^ other ) );
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator &= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
            return ( this->operator= ( (* this) & other ) );
        }

        template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
        __CDS_cpplang_ConstexprDestructor auto operator |= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
            return ( this->operator= ( (* this) | other ) );
        }

        constexpr auto operator [] (Index index) const noexcept -> Byte {
            if ( index < 0 ) {
                index += ( static_cast < Size > (0 - index) / byteSize + 1u) * byteSize;
            }

            return this->_data[ static_cast < Size > ( index ) % byteSize ];
        }

        constexpr auto operator [] (Index index) noexcept -> Byte & {
            if ( index < 0 ) {
                index += ( static_cast < Size > (0 - index) / byteSize + 1u ) * byteSize;
            }

            return this->_data[ static_cast < Size > ( index ) % byteSize];
        }

        template < Size otherSize, Size totalSize = byteSize + otherSize >
        __CDS_cpplang_ConstexprDestructor auto operator + ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < totalSize > {
            CryptoBlock < totalSize > newBlock (this->_paddingElement);

            (void) std :: memcpy ( static_cast < void * > (newBlock.data()), static_cast < void const * > (this->data()), byteSize );
            (void) std :: memcpy ( static_cast < void * > (newBlock.data() + byteSize), static_cast < void const * > (this->data()), otherSize );

            return newBlock;
        }

    private:
        constexpr static auto decToHex (Byte number) noexcept -> char {
            return (
                    number >= 0x00U && number <= 0x09U                                  ?
                    ( static_cast < char > ( static_cast < char > ( number ) + '0') )   :
                    ( static_cast < char > ( static_cast < char > ( number ) + 'a' - static_cast < char > ( 0x0AU ) ) )
            );
        }

        static auto byteToHex (Byte value) noexcept -> StringLiteral {
            thread_local static char asHex[0x03U];

            asHex[0] = decToHex( static_cast < Byte > ( value / 0x10U ) );
            asHex[1] = decToHex( static_cast < Byte > ( value % 0x10U ) );
            asHex[2] = static_cast < char > ( 0x00U );

            return asHex;
        }

        static auto bytesToHex ( Byte const * pData ) noexcept -> String {
            String result;

            for ( Size i = 0u; i < byteSize; i++ ) {
                result += String(byteToHex(pData[i])) + " "; // NOLINT(clion-misra-cpp2008-5-2-4,clion-misra-cpp2008-5-2-5)
            }

            return result;
        }

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return String("CryptoBlock ") +
                "{ size = "     + byteSize +
                ", data = "     + CryptoBlock::bytesToHex(this->data()) +
                ", padChar = "  + String(CryptoBlock::byteToHex(this->_paddingElement)) +
                " }";
        }

        __CDS_NoDiscard inline auto toHex () const noexcept -> String {
            return CryptoBlock :: bytesToHex(this->_data);
        }

        template < Size newSize >
        __CDS_NoDiscard auto split ( Byte paddingElement = 0x00U ) const noexcept -> DoubleLinkedList < CryptoBlock < newSize > > {
            DoubleLinkedList < CryptoBlock < newSize > > newBlocks;

            for ( Size i = 0u; i < byteSize; i += newSize ) {
                CryptoBlock < newSize > newBlock (paddingElement);
                auto minBufferSize = std::min ( newSize, byteSize - i );

                (void) std :: memcpy ( static_cast < void * > (newBlock.data()), static_cast < void const * > ((this->_data + i)), minBufferSize );

                if ( minBufferSize < newSize ) {
                    (void) std :: memset ( static_cast < void * > ( newBlock.data() + minBufferSize ), static_cast < char > ( paddingElement ), newSize - minBufferSize );
                }

                newBlocks.add(newBlock);
            }

            return newBlocks;
        }

        class InvalidHexFormat : public std::exception {
            String _message;
        public:
            explicit InvalidHexFormat(char c) { this->_message = String("Invalid Hex Format, character encountered : ") + c; }

            __CDS_NoDiscard auto what() const noexcept -> StringLiteral override { return this->_message.cStr(); }
        };

        __CDS_NoDiscard auto static fromHex ( String const & hexString, Byte paddingElement = 0x00U ) noexcept(false) -> CryptoBlock {
            CryptoBlock block;

            static auto hexToByte = [](char c) noexcept(false) -> Byte {
                if ( c >= '0' && c <= '9' ) {
                    return static_cast < Byte > ( c - '0' );
                } else if ( c >= 'A' && c <= 'Z') {
                    return static_cast < Byte > ( c - 'A' + 10 );
                } else if ( c >= 'a' && c <= 'z') {
                    return static_cast < Byte > ( c - 'a' + 10 );
                } else {
                    throw IllegalArgumentException (c);
                }
            };

            auto it = hexString.begin();

            auto skipWhitespace = [& it, & hexString] {
                while ( it != hexString.end() && (String(" \t\n").contains(it.value())) ) {
                    (void) it.next();
                }
            };

            for ( Size i = 0u; i < byteSize; i++ ) {
                Byte toAdd;

                skipWhitespace();

                if ( it == hexString.end() ) {
                    toAdd = paddingElement;
                } else {
                    toAdd = hexToByte(it.value()) << 4; // NOLINT(clion-misra-cpp2008-5-0-12)
                    (void) it.next();

                    skipWhitespace();

                    if (it != hexString.end()) {
                        toAdd += hexToByte(it.value()); // NOLINT(clion-misra-cpp2008-5-0-12)
                        (void) it.next();
                    }
                }

                block._data[i] = toAdd;
            }

            return block;
        }

        constexpr auto operator == (CryptoBlock const & block) const noexcept -> bool {
            if ( this == & block ) {
                return true;
            }

            return std::memcmp ( this->_data, block._data, byteSize ) == 0;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
            if ( this == & o ) {
                return true;
            }

            auto p = dynamic_cast < CryptoBlock < byteSize > const * > ( & o );
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_NoDiscard auto static split ( Byte const * pData, Size size, Byte paddingElement = 0x00U ) noexcept -> DoubleLinkedList < CryptoBlock < byteSize > > {
            DoubleLinkedList < CryptoBlock < byteSize > > newBlocks;

            for ( Size i = 0u; i < size; i += byteSize ) {
                CryptoBlock < byteSize > newBlock (paddingElement);
                auto minBufferSize = std::min ( byteSize, size - i );

                (void) std::memcpy ( static_cast < void * > (newBlock.data()), static_cast < void const * > ((pData + i)), minBufferSize );

                if ( minBufferSize < byteSize ) {
                    (void) std::memset ( static_cast < void * > ( newBlock.data() + minBufferSize ), static_cast < char > ( paddingElement ), byteSize - minBufferSize );
                }

                newBlocks.add(newBlock);
            }

            return newBlocks;
        }

        __CDS_NoDiscard inline auto static split ( String const & string, Byte paddingElement = 0x00U ) noexcept -> DoubleLinkedList < CryptoBlock < byteSize > > {
            return CryptoBlock < byteSize > :: split ( reinterpret_cast < uint8 const * > ( string.cStr() ), string.length(), paddingElement );
        }

        __CDS_NoDiscard inline auto toPlainText () const noexcept -> String {
            String s;
            s.resize(byteSize);
            (void) std::memcpy ( static_cast < void * > ( s.data() ), static_cast < void const * > ( this->_data ), byteSize );
            return s;
        }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<CryptoBlock<byteSize>> {
            constexpr static StringLiteral name = "CryptoBlock";
        };

    }
}

#endif //CDS_CRYPTOBLOCK_HPP
