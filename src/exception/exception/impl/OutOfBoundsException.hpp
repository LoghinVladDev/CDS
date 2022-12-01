/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_OUT_OF_BOUNDS_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OUT_OF_BOUNDS_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline OutOfBoundsException :: OutOfBoundsException () noexcept :
            RuntimeException ( "Out of Bounds Access for Object" ) {

    }


    inline OutOfBoundsException :: OutOfBoundsException (
            OutOfBoundsException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline OutOfBoundsException :: OutOfBoundsException (
            OutOfBoundsException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline OutOfBoundsException :: OutOfBoundsException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }


    inline OutOfBoundsException :: OutOfBoundsException (
            Index requested,
            Index capacity
    ) noexcept :
            RuntimeException ( String("Out of Bounds Exception : Requested : ") + requested + ", capacity : " + capacity ) {

    }

} /* namespace cds */

#endif /* __CDS_OUT_OF_BOUNDS_EXCEPTION_IMPL_HPP__ */
