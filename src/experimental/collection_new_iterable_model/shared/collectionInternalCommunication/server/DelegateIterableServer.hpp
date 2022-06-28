//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType, // NOLINT(bugprone-reserved-identifier)
                        bool     __forward,             // NOLINT(bugprone-reserved-identifier)
                        bool     __backward             // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableServer :      // NOLINT(bugprone-reserved-identifier)
                        public cds :: meta :: Conditional <
                                __forward,
                                __DelegateIterableForwardPositiveResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >,
                                __DelegateIterableForwardNegativeResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >
                        >,
                        public cds :: meta :: Conditional<
                                __backward,
                                __DelegateIterableBackwardPositiveResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >,
                                __DelegateIterableBackwardNegativeResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >
                        > {

                protected:
                    auto __dis_handleRequest ( // NOLINT(bugprone-reserved-identifier)
                            __DelegateIteratorRequestType requestType
                    ) noexcept -> __AbstractDelegateIterator < __ElementType > *;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__
