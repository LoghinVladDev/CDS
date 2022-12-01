/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_TYPE_EXCEPTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TYPE_EXCEPTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline TypeException :: TypeException () noexcept :
            RuntimeException ( "Type Cast Exception" ) {

    }


    inline TypeException :: TypeException (
            TypeException const & exception
    ) noexcept :
            RuntimeException ( exception ) {

    }


    inline TypeException :: TypeException (
            TypeException && exception
    ) noexcept :
            RuntimeException ( std :: move ( exception ) ) {

    }


    inline TypeException :: TypeException (
            StringView message
    ) noexcept :
            RuntimeException ( message ) {

    }


    template < typename __FromType, typename __ToType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline TypeException :: TypeException () noexcept :
            RuntimeException ( String ( "Type Cast Exception. Cannot convert '" + cds :: meta :: Type < __FromType > :: name () + "' to '" + cds :: meta :: Type < __ToType > :: name () + "'" ) ) {

    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline TypeException :: TypeException (
            __ElementType const & value
    ) noexcept :
            RuntimeException ( String ( "Type Cast Exception. Conversion to '" ) + cds :: meta :: Type < __ElementType > :: name () + "' not possible" ) {

    }

} /* namespace cds */

#endif /* __CDS_TYPE_EXCEPTION_IMPL_HPP__ */
