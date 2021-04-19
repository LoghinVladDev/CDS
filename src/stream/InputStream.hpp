//
// Created by vladl on 17/04/2021.
//

#ifndef CDS_INPUTSTREAM_HPP
#define CDS_INPUTSTREAM_HPP

#include <CDS/Object>

class InputStream : public Object {
protected:
    InputStream () noexcept = default;
    InputStream (InputStream const &) noexcept = default;
    InputStream (InputStream &&) noexcept = default;
    ~InputStream() noexcept override = default;

public:

    virtual auto readByte () noexcept(false) -> CDS_byte;
    virtual auto readBytes ( CDS_byte *, Size ) noexcept -> Size;

    template < class T >
    inline auto read () noexcept (false) -> T {
        T obj;
        if ( sizeof ( T ) != this->readBytes( reinterpret_cast < CDS_byte * > ( & obj ), sizeof ( T ) ) ) {
            /// throw
        }

        return obj;
    }

    using readInt = read<int>;
    using readLong = read<long long int>;
    using readFloat = read<float>;
    using readDouble = read<double>;
    using readBoolean = read<bool>;
};


#endif //CDS_INPUTSTREAM_HPP
