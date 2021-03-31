//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_BLOCKSIZE_HPP
#define CDS_BLOCKSIZE_HPP

#include <CDS/Object>

namespace crypto {
    class BlockSize : public Object {
    public:
        enum class Value {
            BITS_UNDEFINED,
            BITS_16,
            BITS_24,
            BITS_32,
            BITS_64,
            BITS_128,
            BITS_256,
            BITS_512,
            BITS_1024,
            BITS_2048,
            BITS_3072,
            BITS_4096,
            BITS_8192,
            BITS_16384,
            BITS_32768
        };

    private:
        Value _size {Value::BITS_UNDEFINED};

        constexpr static Size sizes[] = {2u, 3u, 4u, 8u, 16u, 32u, 64u, 128u, 256u, 384u, 512u, 1024u, 2048u, 4096u};

        constexpr static Size sizeCount = 14u;

    public:

        constexpr BlockSize () noexcept = default;
        constexpr BlockSize ( BlockSize const & obj ) noexcept = default;
        constexpr BlockSize ( BlockSize && obj ) noexcept : _size(std::exchange(obj._size, Value::BITS_UNDEFINED)) {}
        constexpr BlockSize ( BlockSize::Value value ) noexcept : _size(value) { } // NOLINT(google-explicit-constructor)
        constexpr explicit BlockSize ( Size reqSize ) noexcept : _size(closestSize(reqSize)) {}

        constexpr auto static closestSize (Size s) noexcept -> Value {
            if ( s <= sizes[0] ) return fixedSize(sizes[0]);

            for ( auto i = 0; i < sizeCount - 1; i++ ) {
                if ( ! ( sizes[i] <= s && s <= sizes[i + 1] ) )
                    continue;

                return fixedSize(sizes[i]);
            }

            return fixedSize(sizes[sizeCount - 1]);
        }

        constexpr auto static fixedSize (Size s) noexcept -> Value {
            switch(s) {
                case sizes[0]:  return    Value::BITS_16;
                case sizes[1]:  return    Value::BITS_24;
                case sizes[2]:  return    Value::BITS_32;
                case sizes[3]:  return    Value::BITS_64;
                case sizes[4]:  return    Value::BITS_128;
                case sizes[5]:  return    Value::BITS_256;
                case sizes[6]:  return    Value::BITS_512;
                case sizes[7]:  return    Value::BITS_1024;
                case sizes[8]:  return    Value::BITS_2048;
                case sizes[9]:  return    Value::BITS_3072;
                case sizes[10]: return    Value::BITS_4096;
                case sizes[11]: return    Value::BITS_8192;
                case sizes[12]: return    Value::BITS_16384;
                case sizes[13]: return    Value::BITS_32768;

                default:
                return Value::BITS_UNDEFINED;
            }
        }

        [[nodiscard]] constexpr auto bytes() const noexcept -> Size {
            switch (this->_size) {
                case Value::BITS_UNDEFINED: return 0u;
                case Value::BITS_16:        return sizes[0];    // 2B
                case Value::BITS_24:        return sizes[1];    // 3B
                case Value::BITS_32:        return sizes[2];    // 4B
                case Value::BITS_64:        return sizes[3];    // 8B
                case Value::BITS_128:       return sizes[4];    // 16B
                case Value::BITS_256:       return sizes[5];    // 32B
                case Value::BITS_512:       return sizes[6];    // 64B
                case Value::BITS_1024:      return sizes[7];    // 128B
                case Value::BITS_2048:      return sizes[8];    // 256B
                case Value::BITS_3072:      return sizes[9];    // 384B
                case Value::BITS_4096:      return sizes[10];   // 512B
                case Value::BITS_8192:      return sizes[11];   // 1KB
                case Value::BITS_16384:     return sizes[12];   // 2KB
                case Value::BITS_32768:     return sizes[13];   // 4KB
            }

            return 0u;
        }

        constexpr auto operator == (Object const & obj) const noexcept -> bool override {
            if ( this == & obj ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & obj );
            if ( p == nullptr ) return false;

            return this->_size == p->_size;
        }

        constexpr auto operator == ( BlockSize const & o ) const noexcept -> bool {
            return this->_size == o._size;
        }

        constexpr auto operator == ( Value v ) const noexcept -> bool {
            return this->_size == v;
        }

        constexpr auto operator != ( BlockSize const & o ) const noexcept -> bool {
            return this->_size != o._size;
        }

        constexpr BlockSize & operator = (BlockSize const & obj) noexcept {
            if ( this == & obj ) return * this;

            this->_size = obj._size;
            return * this;
        }

        constexpr BlockSize & operator = (Value v) noexcept {
            this->_size = v;
            return * this;
        }

        constexpr auto operator != ( Value v ) const noexcept -> bool {
            return this->_size != v;
        }

        constexpr explicit operator Value () const noexcept { // NOLINT(google-explicit-constructor)
            return this->_size;
        }

        constexpr explicit operator Size () const noexcept {
            return this->bytes();
        }

        [[nodiscard]] constexpr auto bits () const noexcept -> Size {
            return this->bytes() * 8;
        }

        [[nodiscard]] auto toString() const noexcept -> String override {
            return String().append("BlockSize of ").append(this->bytes() * 8).append(" bytes");
        }

        constexpr ~BlockSize () noexcept override { }
    };

//    namespace size {
//#define _SIZE(_i) constexpr BlockSize SIZE_ ## _i = BlockSize::Value::BITS_ ## _i
//
//        _SIZE(16);
//        _SIZE(24);
//        _SIZE(32);
//        _SIZE(64);
//        _SIZE(128);
//        _SIZE(256);
//        _SIZE(512);
//        _SIZE(1024);
//        _SIZE(2048);
//        _SIZE(3072);
//        _SIZE(4096);
//        _SIZE(8192);
//        _SIZE(16384);
//        _SIZE(32768);
//
//#undef _SIZE
//    }
}

#endif //CDS_BLOCKSIZE_HPP
