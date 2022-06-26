//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional                // NOLINT(bugprone-reserved-identifier)
                > class __DelegateBackwardConstIterableClient { // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __dbcic_ElementType   = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                protected:
                    using __dbcic_Iterator      = // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __dbcic_ElementType >,
                                    __ForwardDelegateWrapperIterator < __dbcic_ElementType >
                            >;

                protected:
                    auto rbegin () const noexcept -> __dbcic_Iterator;

                protected:
                    auto rend () const noexcept -> __dbcic_Iterator;

                protected:
                    auto crbegin () const noexcept -> __dbcic_Iterator;

                protected:
                    auto crend () const noexcept -> __dbcic_Iterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_CLIENT_HPP__
