//
// Created by vladl on 17/04/2021.
//

#ifndef CDS_OUTPUTSTREAM_HPP
#define CDS_OUTPUTSTREAM_HPP

#include <CDS/Object>

class OutputStream : public Object {
protected:
    OutputStream () noexcept = default;
    OutputStream (OutputStream const &) noexcept = default;
    OutputStream (OutputStream &&) noexcept = default;
    ~OutputStream() noexcept override = default;

public:

    virtual auto writeByte () noexcept -> bool;
    virtual auto writeBytes ( CDS_byte *, Size ) noexcept -> Size;

    template < class T >
    inline auto write ( T const & obj ) noexcept (false) -> void {
        if ( this->writeBytes( reinterpret_cast < CDS_byte * > ( & obj ), sizeof(T) ) != sizeof(T) ) {
            ///throw
        }
    }

    using writeInt = write<int>;
    using writeLong = write<long long>;
    using writeFloat = write<float>;
    using writeDouble = write<double>;
    using writeBoolean = write<bool>;
};

#endif //CDS_OUTPUTSTREAM_HPP
