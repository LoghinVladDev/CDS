//
// Created by loghin on 7/7/2022.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                class __DelegateIterableServerIteratorNoService {};   // NOLINT(bugprone-reserved-identifier)


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                     // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServerIteratorService {   // NOLINT(bugprone-reserved-identifier)
                protected:
                    using __disis_Delegate = __DelegateIterator < __ElementType, __IteratorType >;  // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __begin () noexcept -> __AbstractDelegateIterator < __ElementType > *;     // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __end () noexcept -> __AbstractDelegateIterator < __ElementType > *;       // NOLINT(bugprone-reserved-identifier)
                };


                template <
                        typename __ReceiverType,                        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                         // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServerConstIteratorService {  // NOLINT(bugprone-reserved-identifier)
                protected:
                    using __discis_Delegate = __DelegateIterator < __ElementType const, __IteratorType >;  // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __cbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;     // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __cend () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;       // NOLINT(bugprone-reserved-identifier)
                };


                class __DelegateIterableServerReverseIteratorNoService {};    // NOLINT(bugprone-reserved-identifier)


                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                             // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                             // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServerReverseIteratorService {    // NOLINT(bugprone-reserved-identifier)
                protected:
                    using __disris_Delegate = __DelegateIterator < __ElementType, __IteratorType >;  // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __rbegin () noexcept -> __AbstractDelegateIterator < __ElementType > *;     // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __rend () noexcept -> __AbstractDelegateIterator < __ElementType > *;       // NOLINT(bugprone-reserved-identifier)
                };


                class __DelegateIterableServerConstReverseIteratorNoService {};   // NOLINT(bugprone-reserved-identifier)


                template <
                        typename __ReceiverType,                                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                                 // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServerConstReverseIteratorService {   // NOLINT(bugprone-reserved-identifier)
                protected:
                    using __discris_Delegate = __DelegateIterator < __ElementType const, __IteratorType >;  // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __crbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;     // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __crend () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;       // NOLINT(bugprone-reserved-identifier)
                };


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        bool     __mutable,                         // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional,                   // NOLINT(bugprone-reserved-identifier)
                        typename __MutableForwardIteratorType,      // NOLINT(bugprone-reserved-identifier)
                        typename __ImmutableForwardIteratorType,    // NOLINT(bugprone-reserved-identifier)
                        typename __MutableBackwardIteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ImmutableBackwardIteratorType    // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServer :                  // NOLINT(bugprone-reserved-identifier)
                        public cds :: meta :: Conditional <
                                __mutable,
                                __DelegateIterableServerIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __MutableForwardIteratorType
                                >,
                                __DelegateIterableServerIteratorNoService
                        >,
                        public __DelegateIterableServerConstIteratorService <
                                __ReceiverType,
                                __ElementType,
                                __ImmutableForwardIteratorType
                        >,
                        public cds :: meta :: Conditional <
                                __mutable && __bidirectional,
                                __DelegateIterableServerReverseIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __MutableBackwardIteratorType
                                >,
                                __DelegateIterableServerReverseIteratorNoService
                        >,
                        public cds :: meta :: Conditional <
                                __bidirectional,
                                __DelegateIterableServerConstReverseIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __ImmutableBackwardIteratorType
                                >,
                                __DelegateIterableServerConstReverseIteratorNoService
                        > {

                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__
