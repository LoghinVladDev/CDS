//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional                // NOLINT(bugprone-reserved-identifier)
                > class __DelegateForwardConstIterableClient {  // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __dfcic_ElementType   = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                protected:
                    using __dfcic_Iterator      = // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __dfcic_ElementType >,
                                    __ForwardDelegateWrapperIterator < __dfcic_ElementType >
                            >;

                protected:
                    auto begin () const noexcept -> __dfcic_Iterator;

                protected:
                    auto end () const noexcept -> __dfcic_Iterator;

                protected:
                    auto cbegin () const noexcept -> __dfcic_Iterator;

                protected:
                    auto cend () const noexcept -> __dfcic_Iterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_CLIENT_HPP__
