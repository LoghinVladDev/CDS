//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_CONST_ITERABLE_SERVER_HPP__
#define __CDS_SHARED_DELEGATE_CONST_ITERABLE_SERVER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType,     // NOLINT(bugprone-reserved-identifier)
                        bool     __forward,                 // NOLINT(bugprone-reserved-identifier)
                        bool     __backward                 // NOLINT(bugprone-reserved-identifier)
                > class __DelegateConstIterableServer :     // NOLINT(bugprone-reserved-identifier)
                        public cds :: meta :: Conditional <
                                __forward,
                                __DelegateConstIterableForwardPositiveResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >,
                                __DelegateConstIterableForwardNegativeResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >
                        >,
                        public cds :: meta :: Conditional<
                                __backward,
                                __DelegateConstIterableBackwardPositiveResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >,
                                __DelegateConstIterableBackwardNegativeResponse <
                                        __ReceiverType,
                                        __ElementType,
                                        __WrappedIteratorType
                                >
                        > {

                protected:
                    auto __dcis_handleRequest ( // NOLINT(bugprone-reserved-identifier)
                            __DelegateIteratorRequestType requestType
                    ) const noexcept -> __AbstractDelegateIterator < __ElementType const > *;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_CONST_ITERABLE_SERVER_HPP__
