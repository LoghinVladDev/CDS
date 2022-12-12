/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    __CDS_cpplang_VirtualConstexpr auto Exception :: what () const noexcept -> StringLiteral {

        return this->_message.cStr();
    }


    inline Exception :: Exception () noexcept :
            Object (),
            std :: exception (),
            _message ( "Unknown/Undefined Exception" ) {

    }


    inline Exception :: Exception (
            Exception const & exception
    ) noexcept :
            Object (),
            std :: exception (),
            _message ( exception._message ) {

    }


    inline Exception :: Exception (
            Exception && exception
    ) noexcept :
            Object (),
            std :: exception (),
            _message ( std :: move ( exception._message ) ) {

    }


    inline Exception :: Exception (
            std :: exception const & exception
    ) noexcept :
            Object (),
            std :: exception ( exception ),
            _message ( exception.what() ) {

    }


    inline Exception :: Exception (
            StringView message
    ) noexcept :
            Object (),
            std :: exception (),
            _message ( message ) {

    }


    inline auto Exception :: toString () const noexcept -> String {

        return this->_message;
    }


    inline auto Exception :: hash () const noexcept -> Size {

        return this->_message.hash();
    }


    inline auto Exception :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pException = dynamic_cast < decltype (this) > ( & object );
        if ( pException == nullptr ) {
            return false;
        }

        return this->_message == pException->_message;
    }

} /* namespace cds */

#endif /* __CDS_EXCEPTION_IMPL_HPP__ */
