//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_BLOCK_HPP
#define CDS_BLOCK_HPP

#include <crypto/primitives/BlockSize.hpp>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <CDS/Range>
#include <CDS/Object>
#include <CDS/String>

namespace crypto {

    template < BlockSize::Value byteSize >
    class Block : public Object {
//        using byte = byte;

    private:
        __crypto_constexpr static inline BlockSize bytes = byteSize;

        byte * _pData {nullptr};
        byte _paddingCharacter {'\0'};

    public:
        constexpr explicit Block (byte padChar = '\0') noexcept:
                _paddingCharacter(padChar),
                _pData(new byte[bytes.bytes()]) {
            std::memset(this->_pData, this->_paddingCharacter, bytes.bytes());
        }

        constexpr Block (Block const & obj) noexcept :
                _paddingCharacter(obj._paddingCharacter),
                _pData(new byte[bytes.bytes()]) {
            std::memcpy(this->_pData, obj._pData, bytes.bytes());
        }

        constexpr Block (Block && obj) noexcept :
                _paddingCharacter(obj._paddingCharacter),
                _pData(new byte[bytes.bytes()]) {
            std::memcpy(this->_pData, obj._pData, bytes.bytes());
            std::memset(obj._pData, obj._paddingCharacter, bytes.bytes());
        }

#if defined(_MSC_VER)
#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#endif

        constexpr explicit Block ( byte const * pData, Size size = SIZE_MAX, byte padChar = '\0') noexcept :
                _paddingCharacter(padChar),
                _pData(new byte[bytes.bytes()]) {
            auto toCopy = std::min( size, bytes.bytes() );

            std::memcpy (this->_pData, pData, toCopy );

            if ( toCopy < bytes.bytes() )
                std::memset(this->_pData + toCopy, this->_paddingCharacter, bytes.bytes() - toCopy );
        }

        constexpr explicit Block ( StringLiteral pString, byte padChar = '\0' ) noexcept : // NOLINT(cppcoreguidelines-pro-type-member-init)
                Block( reinterpret_cast<byte const *>(pString), static_cast<Size>(std::strlen(pString)), padChar ) { }

        constexpr explicit Block ( String const & str, byte padChar = '\0' ) noexcept : // NOLINT(cppcoreguidelines-pro-type-member-init)
                Block( str.cStr(), padChar ) { }

        constexpr auto setPaddingValue ( byte padChar ) noexcept -> Block & {
            this->_paddingCharacter = padChar;
            return * this;
        }

        [[nodiscard]] constexpr auto data () const noexcept -> byte const * { return this->_pData; }
        [[nodiscard]] constexpr auto data () noexcept -> byte * { return this->_pData; }

        constexpr auto size () noexcept -> BlockSize { return bytes; }

        constexpr auto set ( Block const & obj ) noexcept -> Block & {
            std::memcpy (this->_pData, obj._pData, bytes.bytes() );
            this->_paddingCharacter = obj._paddingCharacter;

            return * this;
        }

        constexpr auto set ( Block && obj ) noexcept -> Block & {
            std::memcpy (this->_pData, obj._pData, bytes.bytes() );
            this->_paddingCharacter = obj._paddingCharacter;

            std::memset (obj._pData, 0, bytes.bytes() );
            obj._paddingCharacter = '\0';

            return * this;
        }

        constexpr auto set ( byte const * pBytes, Size l = SIZE_MAX ) noexcept -> Block & {
            auto toCopy = std::min(l, bytes.bytes());
            std::memcpy (this->_pData, pBytes, toCopy );

            if ( toCopy < bytes.bytes() )
                std::memset(this->_pData + toCopy, this->_paddingCharacter, bytes.bytes() - toCopy );

            return * this;
        }

        constexpr auto set ( StringLiteral pString ) noexcept -> Block & {
            return this->set ( reinterpret_cast < byte const * >(pString), static_cast < Size > ( std::strlen(pString) ) );
        }

        constexpr auto set ( String const & str ) noexcept -> Block & {
            return this->set ( str.cStr() );
        }

        constexpr Block & operator = ( Block const & obj ) noexcept {
            if ( this == & obj ) return * this;
            return this->set(obj); // NOLINT(misc-unconventional-assign-operator)
        }

        constexpr Block & operator = ( Block && obj ) noexcept {
            if ( this == & obj ) return * this;

            std::memcpy (this->_pData, obj._pData, bytes.bytes() );
            this->_paddingCharacter = obj._paddingCharacter;

            std::memset (obj._pData, 0, bytes.bytes() );
            obj._paddingCharacter = '\0';

            return * this;
        }

        [[nodiscard]] constexpr auto equals ( Object const & o ) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & o );

            if ( p == nullptr ) return false;

            for ( Size i = 0; i < bytes.bytes(); i++ )
                if (this->_pData[i] != p->_pData[i] ) return false;

            return true;
        }

        constexpr auto operator [] (Index index) const noexcept -> byte {
            if ( index < 0 ) index += ( (0 - index) / bytes.bytes() + 1 ) * bytes.bytes();
            return this->_pData[index % bytes.bytes()];
        }

        constexpr auto operator [] (Index index) noexcept -> byte & {
            if ( index < 0 ) index += ( (0 - index) / bytes.bytes() + 1 ) * bytes.bytes();
            return this->_pData[index % bytes.bytes()];
        }

        constexpr auto operator ^ (Block const & b) const noexcept -> Block {
            Block result;

            for ( Index i = 0; i < bytes.bytes(); i ++ )
                result._pData[i] = this->_pData[i] ^ b._pData[i];

            return result;
        }

        constexpr auto operator | (Block const & b) const noexcept -> Block {
            Block result;

            for ( Index i = 0; i < bytes.bytes(); i ++ )
                result._pData[i] = this->_pData[i] | b._pData[i];

            return result;
        }

        constexpr auto operator & (Block const & b) const noexcept -> Block {
            Block result;

            for ( Index i = 0; i < bytes.bytes(); i ++ )
                result._pData[i] = this->_pData[i] & b._pData[i];

            return result;
        }

        constexpr auto operator ~ () const noexcept -> Block {
            Block result;

            for ( Index i = 0; i < bytes.bytes(); i ++ )
                result._pData[i] = ~ this->_pData[i];

            return result;
        }

        auto toString () const noexcept -> String override { // NOLINT(modernize-use-nodiscard)
            return String()
                .append("Block{")
                .append("size=").append(bytes.bytes())
                .append(",data=").append(reinterpret_cast<StringLiteral>(this->_pData))
                .append("}");
        }

        auto toHex () const noexcept -> String { // NOLINT(modernize-use-nodiscard)
            std::stringstream ss;

            for ( auto i : Range (bytes.bytes()) ) {
                ss << std::hex << std::setfill('0') << std::setw(2) << this->_pData[i];
            }

            return ss.str();
        }

        class InvalidFormat : public std::exception {
        private:
            String message;
        public:
            InvalidFormat(String const & expected, String const & got) noexcept {
                this->message = String("Format Invalid. Encountered '").append(got).append("', expected values in '")
                        .append(expected).append("'");
            }

            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return this->message.cStr();
            }
        };

        auto static fromHex (String const &, byte = '\0') noexcept(false) -> Block;
        auto static fromBinary (String const &, byte = '\0') noexcept(false) -> Block;
        auto static fromOctal (String const &, byte = '\0') noexcept(false) -> Block;
        auto static fromDecimal (String const &, byte = '\0') noexcept(false) -> Block;
        auto static fromChar (String const &, byte = '\0') noexcept(false) -> Block;
    };

    template < BlockSize::Value byteSize >
    auto Block<byteSize>::fromBinary( String const & str, byte paddingChar ) noexcept(false) -> Block {
        if ( ! str.all ( [] (auto c) { return c == '0' || c == '1'; } ) )
            throw InvalidFormat("0 or 1", "Char not 0 or 1");

        auto startLen = std::min((str.length() / 8), bytes.bytes()) * 8;
        uint8 currentValue = 0u;
        Index shiftPos = 7;
        Index bytesPos = 0;
        Block result;
        result._paddingCharacter = paddingChar;

        for ( Index i = 0; i < startLen; i ++ ) {
            currentValue |= (str[i] - '0') << ( shiftPos -- );

            if ( shiftPos < 0 ) {
                result._pData[bytesPos ++] = currentValue;
                currentValue = 0u;
                shiftPos = 7;
            }
        }

        if ( str.length() % 8 != 0 && startLen / 8 < bytes.bytes() ) {
            for ( Index i = str.length() / 8 * 8; i < str.length(); i ++ )
                currentValue |= (str[i] - '0') << ( shiftPos -- );

            result._pData[bytesPos ++] = currentValue;
        }

        if ( bytesPos < bytes.bytes() )
            std::memset( result._pData + bytesPos, result._paddingCharacter, bytes.bytes() - bytesPos );

        return result;
    }

#if defined(_MSC_VER)
#pragma pop_macro("max")
#pragma pop_macro("min")
#endif
}

#endif //CDS_BLOCK_HPP
