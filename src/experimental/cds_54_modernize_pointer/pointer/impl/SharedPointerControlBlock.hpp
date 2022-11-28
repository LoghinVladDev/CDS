/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __new (
                    __ElementType * pointer
            ) noexcept -> __SharedPointerControlBlock * {

                auto block = new __SharedPointerControlBlock ();
                block->_dataExpired.clear();
                block->_blockExpired.clear();
                block->_ownerCount      = 1U;
                block->_observerCount   = 1U;
                block->_pObject         = pointer;
                return block;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __use () noexcept -> __SharedPointerControlBlock * {

                (void) this->_ownerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                return this;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __checkAndUse () noexcept -> __SharedPointerControlBlock * {

                if ( ! this->_dataExpired.test_and_set (std :: memory_order_acquire) ) {

                    (void) this->_ownerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                    (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                    this->_dataExpired.clear (std :: memory_order_release);
                    return this;
                }

                return nullptr;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __observe () noexcept -> __SharedPointerControlBlock * {

                (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                return this;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __disposeObserver () noexcept -> void {

                if (
                        1U == this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_blockExpired.test_and_set (std :: memory_order_acq_rel)
                ) {

                    delete this;
                }
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __release () noexcept -> __ElementType * {

                if (
                        1U == this->_ownerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_dataExpired.test_and_set (std :: memory_order_acq_rel)
                ) {

                    auto pToReturn = this->_pObject;
                    this->__disposeSelf();
                    return pToReturn;
                } else {

                    (void) this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease);
                }

                return nullptr;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __disposeSelf () noexcept -> void {

                if (
                        1U == this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_blockExpired.test_and_set (std :: memory_order_acq_rel)
                ) {

                    delete this;
                }
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __expired () noexcept -> bool {

                if ( ! this->_dataExpired.test_and_set (std :: memory_order_acquire) ) {
                    this->_dataExpired.clear (std :: memory_order_release);
                    return false;
                }

                return true;
            }


            template < typename __ElementType >
            constexpr auto __SharedPointerControlBlock < __ElementType > :: __get () const noexcept -> __ElementType * {

                return this->_pObject;
            }


            template < typename __ElementType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __SharedPointerControlBlock < __ElementType > :: __exchange (
                    __ElementType * pointer
            ) noexcept -> __ElementType * {

                return cds :: exchange ( this->_pObject, pointer );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ */
