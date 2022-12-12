/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_DIVIDE_BY_ZERO_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_DIVIDE_BY_ZERO_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline DivideByZeroException :: DivideByZeroException () noexcept :
            ArithmeticException ( "Divide By Zero Exception" ) {

    }


    inline DivideByZeroException :: DivideByZeroException (
            DivideByZeroException const & exception
    ) noexcept :
            ArithmeticException ( exception ) {

    }


    inline DivideByZeroException :: DivideByZeroException (
            DivideByZeroException && exception
    ) noexcept :
            ArithmeticException ( std :: move ( exception ) ) {

    }


    inline DivideByZeroException :: DivideByZeroException (
            StringView message
    ) noexcept :
            ArithmeticException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_DIVIDE_BY_ZERO_EXCEPTION_IMPL_HPP__ */
