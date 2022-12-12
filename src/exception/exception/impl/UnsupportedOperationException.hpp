/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_UNSUPPORTED_OPERATION_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNSUPPORTED_OPERATION_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline UnsupportedOperationException :: UnsupportedOperationException () noexcept :
            Exception ( "Unsupported Operation" ) {

    }


    inline UnsupportedOperationException :: UnsupportedOperationException (
            UnsupportedOperationException const & exception
    ) noexcept :
            Exception ( exception ) {

    }


    inline UnsupportedOperationException :: UnsupportedOperationException (
            UnsupportedOperationException && exception
    ) noexcept :
            Exception ( std :: move ( exception ) ) {

    }


    inline UnsupportedOperationException :: UnsupportedOperationException (
            StringView message
    ) noexcept :
            Exception ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_UNSUPPORTED_OPERATION_EXCEPTION_IMPL_HPP__ */
