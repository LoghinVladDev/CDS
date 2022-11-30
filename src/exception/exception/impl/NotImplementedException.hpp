/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NOT_IMPLEMENTED_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NOT_IMPLEMENTED_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline NotImplementedException :: NotImplementedException () noexcept :
            Exception ( "Not Implemented" ) {

    }


    inline NotImplementedException :: NotImplementedException (
            NotImplementedException const & exception
    ) noexcept :
            Exception ( exception ) {

    }


    inline NotImplementedException :: NotImplementedException (
            NotImplementedException && exception
    ) noexcept :
            Exception ( std :: move ( exception ) ) {

    }


    inline NotImplementedException :: NotImplementedException (
            StringView message
    ) noexcept :
            Exception ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_NOT_IMPLEMENTED_EXCEPTION_IMPL_HPP__ */
