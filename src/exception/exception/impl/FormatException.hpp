/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_FORMAT_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FORMAT_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline FormatException :: FormatException () noexcept :
            IllegalArgumentException ( "Argument Format Error" ) {

    }


    inline FormatException :: FormatException (
            FormatException const & exception
    ) noexcept :
            IllegalArgumentException ( exception ) {

    }


    inline FormatException :: FormatException (
            FormatException && exception
    ) noexcept :
            IllegalArgumentException ( std :: move ( exception ) ) {

    }


    inline FormatException :: FormatException (
            StringView message
    ) noexcept :
            IllegalArgumentException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_FORMAT_EXCEPTION_IMPL_HPP__ */
