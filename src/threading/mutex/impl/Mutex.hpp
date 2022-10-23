/*
 * Created by loghin on 08.03.2021.
 */

#ifndef __CDS_MUTEX_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTEX_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline Mutex :: Mutex () noexcept {

        cds :: __hidden :: __impl :: __mutexPlatformInit ( & this->_handle );
    }


    inline Mutex :: ~Mutex () noexcept {

        cds :: __hidden :: __impl :: __mutexPlatformDestroy ( & this->_handle );
    }


    inline auto Mutex :: lock () noexcept -> void {

        cds :: __hidden :: __impl :: __mutexPlatformLock ( & this->_handle );
    }


    inline auto Mutex :: unlock () noexcept -> void {

        cds :: __hidden :: __impl :: __mutexPlatformUnlock ( & this->_handle );
    }


    inline auto Mutex :: tryLock () noexcept -> bool {

        return cds :: __hidden :: __impl :: __mutexPlatformTryLock ( & this->_handle );
    }


    inline auto Mutex :: toString () const noexcept -> String {

        /* Reused from Collection */
        /* Default toString implementation, store 'Mutex at 0x....'. Use a stringstream for simplicity */
        std :: stringstream oss;
        oss << "Collection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );

        /* converted to std :: string, and to cds :: String afterwards */
        return oss.str();
    }


    inline auto Mutex :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( & this->_handle );
    }


    inline auto Mutex :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pMutex = dynamic_cast < decltype (this) > ( & object );
        if ( pMutex == nullptr ) {
            return false;
        }

        return std :: memcmp (
                & pMutex->_handle,
                & pMutex->_handle,
                sizeof ( cds :: __hidden :: __impl :: __MutexPlatformHandleType )
        ) == 0;
    }

} /* namespace cds */

#endif /* __CDS_MUTEX_IMPL_HPP__ */
