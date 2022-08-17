//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __BidirectionalDelegateWrapperIterator;   // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __ForwardDelegateWrapperIterator; // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                             // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional                            // NOLINT(bugprone-reserved-identifier)
                > class __DelegateBackwardConstIterablePrimitiveClient {    // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __dbcic_ElementType   = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                public:
                    using ConstReverseIterator  = // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __dbcic_ElementType >,
                                    __ForwardDelegateWrapperIterator < __dbcic_ElementType >
                            >;

                public:
                    __CDS_NoDiscard auto rbegin () const noexcept -> ConstReverseIterator;

                public:
                    __CDS_NoDiscard auto rend () const noexcept -> ConstReverseIterator;

                public:
                    __CDS_NoDiscard auto crbegin () const noexcept -> ConstReverseIterator;

                public:
                    __CDS_NoDiscard auto crend () const noexcept -> ConstReverseIterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__
