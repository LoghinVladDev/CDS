/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_KEY_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_KEY_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline KeyException :: KeyException () noexcept :
            RuntimeException ( "Argument Format Error" ) {

    }


    inline KeyException :: KeyException (
            KeyException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline KeyException :: KeyException (
            KeyException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    template < typename __KeyType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline KeyException :: KeyException (
            __KeyType const & key
    ) noexcept :
            RuntimeException ( String ( "Key Exception : Key '" ) + key + "' is invalid for Object" ) {

    }

} /* namespace cds */

#endif /* __CDS_KEY_EXCEPTION_IMPL_HPP__ */
