/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/9/22.
 */

#if defined ( __CDS_OBJECT_HPP__ ) && defined ( __CDS_STRING_HPP__ )
#ifndef __CDS_SHARED_OBJECT_TO_STRING_IMPL_HPP__
#define __CDS_SHARED_OBJECT_TO_STRING_IMPL_HPP__

namespace cds {

    inline auto Object :: toString () const noexcept(false) -> String {

        std :: stringstream oss;
        oss << "Object at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );
        return oss.str();
    }


    inline Object :: operator __hidden :: __impl :: __BaseString < char > () const noexcept(false) {

        return this->toString();
    }


    inline auto operator << (
            std :: ostream        & out,
            Object          const & object
    ) noexcept(false) -> std::ostream & {

        return (out << object.toString());
    }

} /* namespace cds */

#endif /* __CDS_SHARED_OBJECT_TO_STRING_IMPL_HPP__ */
#endif /* defined ( __CDS_OBJECT_HPP__ ) && defined ( __CDS_STRING_HPP__ ) */
