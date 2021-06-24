//
// Created by loghin on 23.06.2021.
//

#ifndef CDS_CRYPTOBLOCK_
#define CDS_CRYPTOBLOCK_HPP

#include <CDS/Object>

#if __cpp_constepxr >= 201907
#define __crypto_block_constexpr constexpr
#else
#define __crypto_block_constexpr inline
#endif

template < Size byteSize >
class CryptoBlock : public Object {
private:
    byte _paddingElement { 0x00u };
    byte _data[byteSize] = { this->_paddingElement };

public:

    constexpr explicit CryptoBlock ( byte paddingElement = 0x00u ) noexcept : _paddingElement(paddingElement) {
        std::memset ( static_cast < void * > (this->_data), this->_paddingElement, byteSize );
    }

    constexpr CryptoBlock ( CryptoBlock const & block ) noexcept : _paddingElement(block._paddingElement) {
        std::memcpy ( static_cast < void * > (this->_data), static_cast < void const * > (block._data), byteSize );
    }

    template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
    constexpr CryptoBlock ( CryptoBlock < otherSize > const & block ) noexcept : _paddingElement(block.paddingElement()) {
        this->setData(block);
    }

    __crypto_block_constexpr ~CryptoBlock() noexcept override = default;

    constexpr explicit CryptoBlock ( byte const * pData, Size size = UINT64_MAX, byte paddingElement = 0x00u ) noexcept : _paddingElement(paddingElement) {
        this->setData( pData, size );
    }

    constexpr auto setPaddingElement ( byte paddingElement ) noexcept -> CryptoBlock & {
        this->_paddingElement = paddingElement;
        return * this;
    }

    [[nodiscard]] constexpr auto paddingElement () const noexcept -> byte { return this->_paddingElement; }
    [[nodiscard]] constexpr auto paddingElement () noexcept -> byte & { return this->_paddingElement; }

    [[nodiscard]] constexpr auto data () const noexcept -> byte const * { return this->_data; }
    [[nodiscard]] constexpr auto data () noexcept -> byte * { return this->_data; }

    constexpr auto operator = ( CryptoBlock const & block ) noexcept -> CryptoBlock & {
        if ( this == & block ) return * this;

        this->_paddingElement = block._paddingElement;

        return this->setData(block); // NOLINT(misc-unconventional-assign-operator)
    }

    template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
    constexpr auto operator = ( CryptoBlock < otherSize > const & block ) noexcept -> CryptoBlock & {
        if ( this == & block ) return * this;

        this->_paddingElement = block._paddingElement;

        return this->setData( block );
    }

    constexpr auto setData ( CryptoBlock const & block ) noexcept -> CryptoBlock & {
        if ( this == & block ) return * this;

        std::memcpy ( static_cast < void * > ( this->_data ), static_cast < void const * > (block._data), byteSize );
        return * this;
    }

    template < Size otherSize, Size minSize = std::min ( otherSize, byteSize ) >
    constexpr auto setData ( CryptoBlock < otherSize > const & block ) noexcept -> CryptoBlock & {
        if ( this == & block ) return * this;

        std::memcpy ( static_cast < void * > ( this->_data ), static_cast < void const * > ( block.data() ), minSize );
        std::memset ( static_cast < void * > ( this->_data + minSize ), this->_paddingElement, byteSize - minSize );

        return * this;
    }

    constexpr auto setData ( byte const * pData, Size size = UINT64_MAX ) noexcept -> CryptoBlock & {
        auto minBufferSize = std::min ( byteSize, size );

        std::memcpy ( static_cast < void * > (this->_data), static_cast < void const * > (pData), minBufferSize );

        if ( size < byteSize )
            std::memset( static_cast < void * > (this->_data + size), this->_paddingElement, byteSize - size );

        return * this;
    }

    __crypto_block_constexpr auto operator ^ ( CryptoBlock const & other ) const noexcept -> CryptoBlock {
        CryptoBlock result;

        for ( Size i = 0; i < byteSize; ++ i )
            result._data[i] = this->_data[i] ^ other._data[i];

        return result;
    }

    __crypto_block_constexpr auto operator & ( CryptoBlock const & other ) const noexcept -> CryptoBlock {
        CryptoBlock result;

        for ( Size i = 0; i < byteSize; ++ i )
            result._data[i] = this->_data[i] & other._data[i];

        return result;
    }

    __crypto_block_constexpr auto operator | ( CryptoBlock const & other ) const noexcept -> CryptoBlock {
        CryptoBlock result;

        for ( Size i = 0; i < byteSize; ++ i )
            result._data[i] = this->_data[i] | other._data[i];

        return result;
    }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator ^ ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
        CryptoBlock < minSize > result;

        for ( Size i = 0; i < minSize; ++ i )
            result.data()[i] = this->data()[i] ^ other.data()[i];

        return result;
    }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator & ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
        CryptoBlock < minSize > result;

        for ( Size i = 0; i < minSize; ++ i )
            result.data()[i] = this->data()[i] & other.data()[i];

        return result;
    }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator | ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > {
        CryptoBlock < minSize > result;

        for ( Size i = 0; i < minSize; ++ i )
            result.data()[i] = this->data()[i] | other.data()[i];

        return result;
    }

    __crypto_block_constexpr auto operator ^= ( CryptoBlock const & other ) noexcept -> CryptoBlock & { return ( * this = (* this) ^ other ); }
    __crypto_block_constexpr auto operator &= ( CryptoBlock const & other ) noexcept -> CryptoBlock & { return ( * this = (* this) & other ); }
    __crypto_block_constexpr auto operator |= ( CryptoBlock const & other ) noexcept -> CryptoBlock & { return ( * this = (* this) | other ); }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator ^= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > { return ( * this = (* this) ^ other ); }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator &= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > { return ( * this = (* this) & other ); }

    template < Size otherSize, Size minSize = std::min ( byteSize, otherSize ) >
    __crypto_block_constexpr auto operator |= ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < minSize > { return ( * this = (* this) | other ); }

    constexpr auto operator [] (Index index) const noexcept -> byte {
        if ( index < 0 )
            index += ( ( 0 - index ) / byteSize + 1 ) * byteSize;

        return this->_data[index % byteSize];
    }

    constexpr auto operator [] (Index index) noexcept -> byte & {
        if ( index < 0 )
            index += ( ( 0 - index ) / byteSize + 1 ) * byteSize;

        return this->_data[index % byteSize];
    }

    template < Size otherSize, Size totalSize = byteSize + otherSize >
    __crypto_block_constexpr auto operator + ( CryptoBlock < otherSize > const & other ) const noexcept -> CryptoBlock < totalSize > {
        CryptoBlock < totalSize > newBlock (this->_paddingElement);

        std::memcpy ( static_cast < void * > (newBlock.data()), static_cast < void const * > (this->data()), byteSize );
        std::memcpy ( static_cast < void * > (newBlock.data() + byteSize), static_cast < void const * > (this->data()), otherSize );

        return newBlock;
    }

private:
    constexpr static auto decToHex (byte number) noexcept -> char {
        return ( number >= 0x00u && number <= 0x09u ? ( static_cast < char > (number + '0') ) : ( static_cast < char > ( number + 'a' - 0x0Au ) ) );
    }

    static auto byteToHex (byte value) noexcept -> StringLiteral {
        thread_local static char asHex[0x03u];

        asHex[0] = decToHex( value / 0x10u );
        asHex[1] = decToHex( value % 0x10u );
        asHex[2] = 0x00u;

        return asHex;
    }

    static auto bytesToHex ( byte const * pData ) noexcept -> String {
        String result;

        for ( Size i = 0; i < byteSize; i++ )
            result += String(byteToHex(pData[i])) + " ";

        return result;
    }

public:
    [[nodiscard]] auto toString () const noexcept -> String override {
        return String("CryptoBlock ") +
            "{ size = " + byteSize +
            ", data = " + CryptoBlock::bytesToHex(this->data()) +
            ", padChar = " + String(CryptoBlock::byteToHex(this->_paddingElement)) +
            " }";
    }

    [[nodiscard]] inline auto toHex () const noexcept -> String {
        return CryptoBlock::bytesToHex(this->_data);
    }

    template < Size newSize >
    [[nodiscard]] auto split ( byte paddingElement = 0x00u ) const noexcept -> LinkedList < CryptoBlock < newSize > > {
        LinkedList < CryptoBlock < newSize > > newBlocks;

        for ( Index i = 0; i < byteSize; i += newSize ) {
            CryptoBlock < newSize > newBlock (paddingElement);
            auto minBufferSize = std::min ( newSize, byteSize - i );

            std::memcpy ( static_cast < void * > (newBlock.data()), static_cast < void const * > ((this->_data + i)), minBufferSize );

            if ( minBufferSize < newSize )
                std::memset ( static_cast < void * > ( newBlock.data() + minBufferSize ), paddingElement, newSize - minBufferSize );

            newBlocks.add(newBlock);
        }

        return newBlocks;
    }

    class InvalidHexFormat : public std::exception {
        String _message;
    public:
        explicit InvalidHexFormat(char c) { this->_message = String("Invalid Hex Format, character encountered : ") + c; }

        [[nodiscard]] auto what() const noexcept -> StringLiteral override { return this->_message.cStr(); }
    };

    [[nodiscard]] auto static fromHex ( String const & hexString, byte paddingElement = 0x00u ) noexcept(false) -> CryptoBlock {
        CryptoBlock block;

        static auto hexToByte = [](char c) noexcept(false) -> byte {
            if ( c >= '0' && c <= '9' ) return c - '0';
            else if ( c >= 'A' && c <= 'Z') return c - 'A' + 10;
            else if ( c >= 'a' && c <= 'z') return c - 'a' + 10;

            throw InvalidHexFormat (c);
        };

        auto it = hexString.begin();

        auto skipWhitespace = [& it, & hexString] { while ( it != hexString.end() && (String(" \t\n").contains(it.value())) ) it.next(); };

        for ( Index i = 0; i < byteSize; i++ ) {
            byte toAdd = 0x00u;

            skipWhitespace();

            if ( it == hexString.end() ) toAdd = paddingElement;
            else {
                toAdd = hexToByte(it.value()) << 4;
                it.next();

                skipWhitespace();

                if (it != hexString.end()) { toAdd += hexToByte(it.value()); it.next(); }
            }

            block._data[i] = toAdd;
        }

        return block;
    }

    constexpr auto operator == (CryptoBlock const & block) const noexcept -> bool {
        if ( this == & block ) return true;

        return std::memcmp ( this->_data, block._data, byteSize ) == 0;
    }
};

#undef __crypto_block_constexpr

#endif //CDS_CRYPTOBLOCK_
