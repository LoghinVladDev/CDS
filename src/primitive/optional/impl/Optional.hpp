/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_OPTIONAL_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OPTIONAL_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SharedPointer>

namespace cds {

    template < typename __ElementType >
    __CDS_OptimalInline Optional < __ElementType > :: Optional (
            Optional const & optional
    ) noexcept :
            _pObject ( optional._pObject ) {

    }


    template < typename __ElementType >
    constexpr Optional < __ElementType > :: Optional (
            Optional && optional
    ) noexcept :
            _pObject ( std :: move ( optional._pObject ) ) {

    }


    template < typename __ElementType >
    __CDS_OptimalInline Optional < __ElementType > :: Optional (
            __ElementType const & element
    ) noexcept ( noexcept ( __ElementType ( element ) ) ):
            _pObject ( new __ElementType ( element ) ) {

    }


    template < typename __ElementType >
    __CDS_OptimalInline Optional < __ElementType > :: Optional (
            __ElementType && element
    ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) ):
            _pObject ( new __ElementType ( std :: move ( element ) ) ) {

    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator = (
            Optional const & optional
    ) noexcept -> Optional & {

        if ( this == & optional ) {
            return * this;
        }

        this->_pObject = optional._pObject;
        return * this;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator = (
            Optional && optional
    ) noexcept -> Optional & {

        if ( this == & optional ) {
            return * this;
        }

        this->_pObject = std :: move ( optional._pObject );
        return * this;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator = (
            __ElementType const & element
    ) noexcept ( noexcept ( __ElementType ( element ) ) ) -> Optional & {

        this->_pObject = new __ElementType ( element );
        return * this;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator = (
            __ElementType && element
    ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) ) -> Optional & {

        this->_pObject = new __ElementType ( std :: move ( element ) );
        return * this;
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: empty () noexcept -> Optional {

        Optional nullOptional;
        nullOptional._pObject = nullptr;
        return nullOptional;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: of (
            __ElementType const & element
    ) noexcept ( noexcept ( __ElementType ( element ) ) ) -> Optional {

        return Optional ( element );
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: of (
            __ElementType && element
    ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) ) -> Optional {

        return Optional ( std :: move ( element ) );
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: isPresent () const noexcept -> bool {

        return ! this->_pObject.isNull();
    }


    template < typename __ElementType >
    template < typename __Consumer >
    constexpr auto Optional < __ElementType > :: ifPresent (
            __Consumer const & consumer
    ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void {

        if ( this->isPresent() ) {
            consumer ( * this->_pObject );
        }
    }


    template < typename __ElementType >
    template < typename __Predicate >
    __CDS_OptimalInline auto Optional < __ElementType > :: filter (
            __Predicate const & predicate
    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Optional < __ElementType > {

        if ( ! this->isPresent() || predicate ( * this->_pObject ) ) {
            return {};
        }

        return * this;
    }


    template < typename __ElementType >
    template < typename __Mapper >
    __CDS_OptimalInline auto Optional < __ElementType > :: map (
            __Mapper const & mapper
    ) const noexcept ( noexcept ( mapper ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Optional < cds :: meta :: ReturnOf < __Mapper > > {

        if ( ! this->isPresent() ) {
            return {};
        }

        return { mapper ( * this->_pObject ) };
    }


    template < typename __ElementType >
    template < typename __Mapper >
    __CDS_OptimalInline auto Optional < __ElementType > :: flatMap (
            __Mapper const & mapper
    ) const noexcept ( noexcept ( mapper ( * this ) ) ) -> Optional < cds :: meta :: ReturnOf < __Mapper > > {

        if ( ! this->isPresent() ) {
            return {};
        }

        return { mapper ( *this ) };
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: get () const noexcept (false) -> __ElementType & {

        if ( ! this->isPresent() ) {
            throw NoSuchElementException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator * () const noexcept (false) -> __ElementType & {

        return this->get();
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: operator -> () const noexcept (false) -> __ElementType * {

        return ( & this->get() );
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: orElse (
            __ElementType & element
    ) const noexcept -> __ElementType & {

        if ( ! this->isPresent() ) {
            return element;
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: orElse (
            __ElementType const & element
    ) const noexcept -> __ElementType const & {

        if ( ! this->isPresent() ) {
            return element;
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    template < typename __Supplier >
    __CDS_OptimalInline auto Optional < __ElementType > :: orElseGet (
            __Supplier const & supplier
    ) const noexcept ( noexcept ( supplier () ) ) -> __ElementType {

        if ( ! this->isPresent() ) {
            return supplier ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    template <
            typename __Supplier,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDerivedFrom < cds :: meta :: ReturnOf < __Supplier >, std :: exception > ()
            >
    > __CDS_OptimalInline auto Optional < __ElementType > :: orElseThrow (
            __Supplier const & supplier
    ) const noexcept ( false ) -> __ElementType & {

        if ( ! this->isPresent() ) {
            throw supplier ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    template <
            typename __ExceptionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDerivedFrom < __ExceptionType, std :: exception > ()
            >
    > __CDS_OptimalInline auto Optional < __ElementType > :: orElseThrow () const noexcept ( false ) -> __ElementType & {

        if ( ! this->isPresent() ) {
            throw __ExceptionType ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pOptional = dynamic_cast < decltype (this) > ( & object );
        if ( pOptional == nullptr ) {
            return false;
        }

        if ( this->isPresent() != pOptional->isPresent() ) {
            return false;
        }

        if ( ! this->isPresent() ) {
            return true;
        }

        return
                this->_pObject == pOptional->_pObject ||
                * this->_pObject == * pOptional->_pObject;
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: toString () const noexcept -> String {

        std :: stringstream oss;
        oss << "| ";
        if ( this->isPresent() ) {
            oss << * this->_pObject;
        } else {
            oss << "none";
        }

        oss << " |";
        return oss.str();
    }


    template < typename __ElementType >
    __CDS_OptimalInline auto Optional < __ElementType > :: hash () const noexcept -> Size {

        if ( this->isPresent() ) {
            return cds :: Hash < __ElementType > :: hash ( * this->_pObject );
        }

        return 0ULL;
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: operator == (
            Optional const & optional
    ) const noexcept -> bool {

        if ( this == & optional ) {
            return true;
        }

        if ( this->isPresent() != optional.isPresent() ) {
            return false;
        }

        if ( ! this->isPresent() ) {
            return true;
        }

        return
                this->_pObject == optional._pObject ||
                * this->_pObject == * optional.pObject;
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: operator != (
            Optional const & optional
    ) const noexcept -> bool {

        if ( this == & optional ) {
            return false;
        }

        if ( this->isPresent() != optional.isPresent() ) {
            return true;
        }

        if ( ! this->isPresent() ) {
            return false;
        }

        return
                this->_pObject != optional._pObject &&
                * this->_pObject != * optional.pObject;
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: operator == (
            __ElementType const & element
    ) const noexcept -> bool {

        if ( ! this->isPresent() ) {
            return false;
        }

        return
                this->_pObject.get() == & element ||
                * this->_pObject == element;
    }


    template < typename __ElementType >
    constexpr auto Optional < __ElementType > :: operator != (
            __ElementType const & element
    ) const noexcept -> bool {

        if ( ! this->isPresent() ) {
            return true;
        }

        return
                this->_pObject.get() != & element &&
                * this->_pObject != element;
    }


    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeOptional (
            __ConstructionArguments && ... arguments
    ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> Optional < __ElementType > {

        return cds :: Optional < __ElementType > ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) );
    }

} /* namespace cds */

#endif /* __CDS_OPTIONAL_IMPL_HPP__ */
