/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NO_SUCH_ELEMENT_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NO_SUCH_ELEMENT_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline NoSuchElementException :: NoSuchElementException () noexcept :
            RuntimeException ( "No Such Element Exists" ) {

    }


    inline NoSuchElementException :: NoSuchElementException (
            NoSuchElementException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline NoSuchElementException :: NoSuchElementException (
            NoSuchElementException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline NoSuchElementException :: NoSuchElementException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }

} /* namespace cds */

#endif /* __CDS_NO_SUCH_ELEMENT_EXCEPTION_IMPL_HPP__ */
