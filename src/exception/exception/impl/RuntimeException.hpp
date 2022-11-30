/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_RUNTIME_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_RUNTIME_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline RuntimeException :: RuntimeException () noexcept :
            Exception ( "Runtime Exception" ) {

    }


    inline RuntimeException :: RuntimeException (
            RuntimeException const & exception
    ) noexcept :
            Exception ( exception ) {

    }


    inline RuntimeException :: RuntimeException (
            RuntimeException && exception
    ) noexcept :
            Exception ( std :: move ( exception ) ) {

    }


    inline RuntimeException :: RuntimeException (
            StringView message
    ) noexcept :
            Exception ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_RUNTIME_EXCEPTION_IMPL_HPP__ */
