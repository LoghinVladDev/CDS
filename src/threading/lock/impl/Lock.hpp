/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_LOCK_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LOCK_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __LockedObjectType >
    __CDS_OptimalInline Lock < __LockedObjectType > :: Lock (
            __LockedObjectType & lock
    ) noexcept :
            _lock ( lock ) {

        this->_lock.lock ();
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline Lock < __LockedObjectType > :: ~Lock () noexcept {

        this->_lock.unlock ();
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto Lock < __LockedObjectType > :: toString () const noexcept -> String {

        return "Lock over " + this->_lock.toString ();
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto Lock < __LockedObjectType > :: hash () const noexcept -> Size {

        return this->_lock.hash ();
    }

} /* namespace cds */

#endif /* __CDS_LOCK_HPP__ */
