/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_ILLEGAL_ARGUMENT_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ILLEGAL_ARGUMENT_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline IllegalArgumentException :: IllegalArgumentException () noexcept :
            RuntimeException ( "Illegal Argument" ) {

    }


    inline IllegalArgumentException :: IllegalArgumentException (
            IllegalArgumentException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline IllegalArgumentException :: IllegalArgumentException (
            IllegalArgumentException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline IllegalArgumentException :: IllegalArgumentException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_ILLEGAL_ARGUMENT_EXCEPTION_IMPL_HPP__ */
