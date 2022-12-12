/*
 * Created by loghin on 27.01.2021.
 */

#ifndef __CDS_REFERENCE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_REFERENCE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType >
    template <
            typename __ReferredValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: __hidden :: __impl :: __ReferableTo <
                            __ElementType,
                            __ReferredValueType
                    > :: value &&
                    ! cds :: meta :: isSame <
                            Reference < __ElementType >,
                            cds :: meta :: RemoveConst < cds :: meta :: RemoveReference < __ElementType > >
                    > ()
            >
    > constexpr Reference < __ElementType > :: Reference (
            __ReferredValueType && value
    ) noexcept ( noexcept ( cds :: __hidden :: __impl :: __referenceImplicitCastCheck < __ElementType > ( std :: forward < __ReferredValueType > ( value ) ) ) ) :
            _pObject ( & ( cds :: __hidden :: __impl :: __referenceImplicitCastCheck < __ElementType > ( value ) ) ) {

    }


    template < typename __ElementType >
    constexpr Reference < __ElementType > :: operator __ElementType & () const noexcept {

        return * this->_pObject;
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: get () const noexcept -> __ElementType & {

        return * this->_pObject;
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: operator -> () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: operator == (
            Reference const & reference
    ) const noexcept -> bool {

        return
                this->_pObject == reference._pObject ||
                cds :: meta :: equals ( * this->_pObject, * reference._pObject );
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: operator != (
            Reference const & reference
    ) const noexcept -> bool {

        return
                this->_pObject != reference._pObject &&
                ! cds :: meta :: equals ( * this->_pObject, * reference._pObject );
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: operator == (
            __ElementType const & element
    ) const noexcept -> bool {

        return
                this->_pObject == & element ||
                cds :: meta :: equals ( * this->_pObject, element );
    }


    template < typename __ElementType >
    constexpr auto Reference < __ElementType > :: operator != (
            __ElementType const & element
    ) const noexcept -> bool {

        return
                this->_pObject != & element &&
                ! cds :: meta :: equals ( * this->_pObject, element );
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Reference < __ElementType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pReference = dynamic_cast < decltype (this) > ( & object );
        if ( pReference == nullptr ) {
            return false;
        }

        return
                this->_pObject == pReference->_pObject ||
                cds :: meta :: equals ( * this->_pObject, * pReference->_pObject );
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Reference < __ElementType > :: hash () const noexcept -> Size {

        return cds :: Hash < __ElementType > :: hash ( * this->_pObject );
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Reference < __ElementType > :: toString () const noexcept -> String {

        std :: stringstream oss;
        cds :: meta :: print ( oss << "< " << ( cds :: meta :: isConst < __ElementType > () ? "const " : "") << "& of 0x" << std :: hex
                            << reinterpret_cast < Size > ( this->_pObject ) << std :: dec << " : " , * this->_pObject ) << " >";
        return oss.str();
    }


    template < typename __ElementType >
    template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto Reference < __ElementType > :: operator () (
            __ArgumentTypes && ... arguments
    ) noexcept ( noexcept (
            ( * this->_pObject ) ( std :: forward < __ArgumentTypes > ( arguments ) ... )
    ) ) -> typename __hidden :: __impl :: __ReturnOfUnsafe < __ElementType > :: Type {

        return ( * this->_pObject ) ( std :: forward < __ArgumentTypes > ( arguments ) ... );
    }

} /* namespace cds */

#endif /* __CDS_REFERENCE_IMPL_HPP__ */
