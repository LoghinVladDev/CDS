/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __new (
                    __ElementType * pointer
            ) noexcept -> __SharedPointerControlBlock * {

                auto * block = new __SharedPointerControlBlock (); /* NOLINT(clion-misra-cpp2008-18-4-1, *-owning-memory) */
                block->_dataExpired.clear();
                block->_blockExpired.clear();
                block->_ownerCount      = 1U;
                block->_observerCount   = 1U;
                block->_pObject         = pointer;
                return block;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __use () noexcept -> __SharedPointerControlBlock * {

                (void) this->_ownerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                return this;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __checkAndUse () noexcept -> __SharedPointerControlBlock * {

                if ( ! this->_dataExpired.test_and_set (std :: memory_order_acquire) ) { /* NOLINT(clion-misra-cpp2008-5-3-1) */

                    (void) this->_ownerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                    (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                    this->_dataExpired.clear (std :: memory_order_release);
                    return this;
                }

                return nullptr;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __observe () noexcept -> __SharedPointerControlBlock * {

                (void) this->_observerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                return this;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __disposeObserver () noexcept -> void {

                if (
                        1U == this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_blockExpired.test_and_set (std :: memory_order_acq_rel)                            /* NOLINT(clion-misra-cpp2008-5-3-1) */
                ) {

                    delete this;
                }
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __release () noexcept -> __ElementType * {

                if (
                        1U == this->_ownerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_dataExpired.test_and_set (std :: memory_order_acq_rel)                         /* NOLINT(clion-misra-cpp2008-5-3-1) */
                ) {

                    auto pToReturn = this->_pObject;
                    this->__disposeSelf();
                    return pToReturn;
                }

                (void) this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease);
                return nullptr;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __disposeSelf () noexcept -> void {

                if (
                        1U == this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_blockExpired.test_and_set (std :: memory_order_acq_rel)                            /* NOLINT(clion-misra-cpp2008-5-3-1) */
                ) {

                    delete this;
                }
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __SharedPointerControlBlock < __ElementType > :: __expired () noexcept -> bool {

                if ( ! this->_dataExpired.test_and_set (std :: memory_order_acquire) ) {    /* NOLINT(clion-misra-cpp2008-5-3-1) */
                    this->_dataExpired.clear (std :: memory_order_release);
                    return false;
                }

                return true;
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __SharedPointerControlBlock < __ElementType > :: __get () const noexcept -> __ElementType * {

                return this->_pObject;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_IMPL_HPP__ */
