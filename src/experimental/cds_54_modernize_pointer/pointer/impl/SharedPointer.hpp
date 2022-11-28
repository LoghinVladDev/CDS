/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            inline auto __SharedPointerControlBlock :: __new () noexcept -> __SharedPointerControlBlock * {

                auto block = new __SharedPointerControlBlock ();
                block->_dataExpired.clear();
                block->_blockExpired.clear();
                block->_ownerCount      = 1U;
                block->_observerCount   = 0U;
                return block;
            }


            inline auto __SharedPointerControlBlock :: __use () noexcept -> __SharedPointerControlBlock * {

                (void) this->_ownerCount.getThenAdd (1U, AtomicMemoryOrder :: Relaxed);
                return this;
            }


            inline auto __SharedPointerControlBlock :: __release () noexcept -> bool {

                bool memoryDisposable = false;
                if (
                        1U == this->_ownerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_dataExpired.test_and_set (std :: memory_order_acq_rel)
                ) {

                    memoryDisposable = true;
                }

                this->__disposeSelf ();
                return memoryDisposable;
            }


            inline auto __SharedPointerControlBlock :: __disposeSelf () noexcept -> void {

                if (
                        1U == this->_observerCount.getThenSubtract (1U, AtomicMemoryOrder :: AcquireRelease) &&
                        ! this->_blockExpired.test_and_set (std :: memory_order_acq_rel)
                ) {

                    delete this;
                }
            }

        }
    }

    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer () noexcept :
            _pControl ( ControlBlock :: __new () ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer () noexcept :
            _pControl ( ControlBlock :: __new () ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new () ),
            Base ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new () ),
            Base ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl->__use() ),
            Base ( pointer._pObject ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl->__use() ),
            Base ( pointer._pObject ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ),
            Base ( std :: move ( pointer ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ),
            Base ( std :: move ( pointer ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: ~SharedPointer () noexcept {

        if ( this->_pControl->__release () ) {

            __Deleter () ( this->_pObject );
        }
    }

} /* namespace cds */

#endif /* __CDS_SHARED_POINTER_IMPL_HPP__ */
