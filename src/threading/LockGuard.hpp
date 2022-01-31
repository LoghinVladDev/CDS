//
// Created by loghin on 31.01.2022.
//

#ifndef CDS_LOCKGUARD_HPP
#define CDS_LOCKGUARD_HPP

#include <CDS/Mutex>

namespace cds {

    template < typename LockType >
    class LockGuard : public Object {
    private:
        LockType * pLock { nullptr };

    public:
        LockGuard () noexcept = delete;
        LockGuard ( LockType && ) noexcept = delete;

        auto operator = ( LockGuard const & ) noexcept -> LockGuard & = delete;
        auto operator = ( LockGuard && ) noexcept -> LockGuard & = delete;

        explicit LockGuard ( LockType & lock ) noexcept {
            this->pLock = & lock;
            this->pLock->lock();
        }

        ~LockGuard () noexcept override {
            this->pLock->unlock();
        }
    };

}

#endif //CDS_LOCKGUARD_HPP
