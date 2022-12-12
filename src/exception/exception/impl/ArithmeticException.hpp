/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_ARITHMETIC_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ARITHMETIC_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline ArithmeticException :: ArithmeticException () noexcept :
            RuntimeException ( "Arithmetic Exception" ) {

    }


    inline ArithmeticException :: ArithmeticException (
            ArithmeticException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline ArithmeticException :: ArithmeticException (
            ArithmeticException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline ArithmeticException :: ArithmeticException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_ARITHMETIC_EXCEPTION_IMPL_HPP__ */
