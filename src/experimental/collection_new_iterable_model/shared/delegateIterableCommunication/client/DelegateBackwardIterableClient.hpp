//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __BidirectionalDelegateWrapperIterator;   // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __ForwardDelegateWrapperIterator; // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional            // NOLINT(bugprone-reserved-identifier)
                > class __DelegateBackwardIterableClient {  // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __dbic_ElementType   = // NOLINT(bugprone-reserved-identifier)
                            __ElementType;

                protected:
                    using ReverseIterator      = // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __dbic_ElementType >,
                                    __ForwardDelegateWrapperIterator < __dbic_ElementType >
                            >;

                protected:
                    auto rbegin () noexcept -> ReverseIterator;

                protected:
                    auto rend () noexcept -> ReverseIterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_CLIENT_HPP__
