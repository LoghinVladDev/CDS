/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >
            class __SharedPointerControlBlock {

            private:
                Atomic < uint32 >           _ownerCount;

            private:
                Atomic < uint32 >           _observerCount;

            private:
                std :: atomic_flag          _dataExpired;

            private:
                std :: atomic_flag          _blockExpired;

            private:
                __ElementType             * _pObject;

            public:
                static auto __new (
                        __ElementType * pointer = nullptr
                ) noexcept -> __SharedPointerControlBlock *;

            public:
                auto __use () noexcept -> __SharedPointerControlBlock *;

            public:
                auto __checkAndUse () noexcept -> __SharedPointerControlBlock *;

            public:
                auto __observe () noexcept -> __SharedPointerControlBlock *;

            public:
                auto __release () noexcept -> __ElementType *;

            public:
                auto __disposeSelf () noexcept -> void;

            public:
                auto __disposeObserver () noexcept -> void;

            public:
                __CDS_NoDiscard auto __expired () noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto __get () const noexcept -> __ElementType *;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __exchange (
                        __ElementType * pointer
                ) noexcept -> __ElementType *;
            };

        }
    }
}

#endif /* __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ */
