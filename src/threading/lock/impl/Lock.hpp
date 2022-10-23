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


    template < typename __LockedObjectType >
    __CDS_OptimalInline DeferredLock < __LockedObjectType > :: DeferredLock (
            __LockedObjectType & lock
    ) noexcept :
            _pLock ( & lock ) {

    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline DeferredLock < __LockedObjectType > :: ~DeferredLock () noexcept {

        if ( this->_used && this->_pLock != nullptr ) {
            this->_pLock->unlock ();
            this->_pLock = nullptr;
        }
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: lock () noexcept -> void {

        this->_pLock->lock();
        this->_used = true;
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: unlock () noexcept -> void {

        this->_pLock->unlock();
        this->_pLock = nullptr;
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: tryLock () noexcept -> bool {

        if ( this->_pLock->tryLock() ) {
            this->_pLock = nullptr;
            this->_used = true;
            return true;
        }

        return false;
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pLock = dynamic_cast < decltype (this) > ( & object );
        if ( pLock == nullptr ) {
            return false;
        }

        return this->_pLock->equals ( * pLock->_pLock );
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: toString () const noexcept -> String {

        return "DeferredLock over " + this->_pLock->toString ();
    }


    template < typename __LockedObjectType >
    __CDS_OptimalInline auto DeferredLock < __LockedObjectType > :: hash () const noexcept -> Size {

        return this->_pLock->hash ();
    }

} /* namespace cds */

#endif /* __CDS_LOCK_HPP__ */
