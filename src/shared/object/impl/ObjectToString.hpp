//
// Created by loghin on 6/9/22.
//

#if defined ( __CDS_OBJECT_HPP__ ) && defined ( __CDS_STRING_HPP__ )
#ifndef __CDS_OBJECT_TO_STRING_IMPL_HPP__
#define __CDS_OBJECT_TO_STRING_IMPL_HPP__

namespace cds {

    inline auto Object :: toString () const noexcept -> String {

        std :: stringstream oss;
        oss << "Object at 0x" << std :: hex << reinterpret_cast < AddressValueType const > ( this );
        return oss.str();
    }


    inline Object :: operator String () const noexcept {

        return this->toString();
    }


    inline auto operator << (
            std :: ostream        & out,
            Object          const & object
    ) noexcept -> std::ostream & {

        return (out << object.toString().cStr());
    }

}

#endif // __CDS_OBJECT_TO_STRING_IMPL_HPP__
#endif
