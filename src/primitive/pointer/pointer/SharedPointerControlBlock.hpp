/* NOLINT(llvm-header-guard)
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __SharedPointerControlBlock { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                Atomic < uint32 >           _ownerCount;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                Atomic < uint32 >           _observerCount;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                std :: atomic_flag          _dataExpired;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                std :: atomic_flag          _blockExpired;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __ElementType             * _pObject;

            public:                 /* NOLINT(readability-redundant-access-specifiers) */
                static auto __new ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ElementType * pointer = nullptr
                ) noexcept -> __SharedPointerControlBlock *;

            public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
                auto __use () noexcept -> __SharedPointerControlBlock *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                         /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __OtherElementType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto __cast () noexcept -> __SharedPointerControlBlock < __OtherElementType > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                                                 /* NOLINT(readability-redundant-access-specifiers) */
                auto __checkAndUse () noexcept -> __SharedPointerControlBlock *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                auto __observe () noexcept -> __SharedPointerControlBlock *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                             /* NOLINT(readability-redundant-access-specifiers) */
                auto __release () noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                auto __disposeSelf () noexcept -> void; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                         /* NOLINT(readability-redundant-access-specifiers) */
                auto __disposeObserver () noexcept -> void; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                                 /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto __expired () noexcept -> bool; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                                                         /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __get () const noexcept -> __ElementType *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-use-nodiscard) */

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto __observerCount () const noexcept -> Size; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-use-nodiscard) */

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto __ownerCount () const noexcept -> Size;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-use-nodiscard) */
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_POINTER_SHARED_POINTER_CONTROL_BLOCK_HPP__ */
