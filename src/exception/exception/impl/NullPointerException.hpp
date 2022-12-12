/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NULL_POINTER_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NULL_POINTER_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline NullPointerException :: NullPointerException () noexcept :
            RuntimeException ( "Tried De-Referencing a null valued Pointer" ) {

    }


    inline NullPointerException :: NullPointerException (
            NullPointerException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline NullPointerException :: NullPointerException (
            NullPointerException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline NullPointerException :: NullPointerException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_NULL_POINTER_EXCEPTION_IMPL_HPP__ */
