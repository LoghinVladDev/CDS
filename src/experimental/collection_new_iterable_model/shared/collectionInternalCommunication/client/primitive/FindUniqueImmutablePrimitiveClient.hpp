//
// Created by loghin on 09/08/22.
//

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                     // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional                // NOLINT(bugprone-reserved-identifier)
                > class __FindUniqueImmutablePrimitiveClient {    // NOLINT(bugprone-reserved-identifier)

                public:
                    using ConstIterator =
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __ElementType const >,
                                    __ForwardDelegateWrapperIterator < __ElementType const >
                    >;

                protected:
                    __CDS_NoDiscard auto find (
                            __KeyType const & key
                    ) const noexcept -> ConstIterator;
                };


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                     // NOLINT(bugprone-reserved-identifier)
                > class __LocalFindUniqueImmutablePrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                public:
                    using ConstIterator = __IteratorType;

                protected:
                    __CDS_NoDiscard auto find (
                            __KeyType const & key
                    ) const noexcept -> ConstIterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__
