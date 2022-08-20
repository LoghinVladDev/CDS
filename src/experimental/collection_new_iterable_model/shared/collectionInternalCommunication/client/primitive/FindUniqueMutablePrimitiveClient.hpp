//
// Created by loghin on 09/08/22.
//

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                     // NOLINT(bugprone-reserved-identifier)
                        bool     __bidirectional                // NOLINT(bugprone-reserved-identifier)
                > class __FindUniqueMutablePrimitiveClient {    // NOLINT(bugprone-reserved-identifier)

                public:
                    using Iterator =
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __ElementType >,
                                    __ForwardDelegateWrapperIterator < __ElementType >
                            >;

                public:
                    __CDS_NoDiscard auto find (
                            __KeyType const & key
                    ) noexcept -> Iterator;
                };


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                     // NOLINT(bugprone-reserved-identifier)
                > class __LocalFindUniqueMutablePrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                public:
                    using Iterator = __IteratorType;

                public:
                    __CDS_NoDiscard auto find (
                            __KeyType const & key
                    ) noexcept -> Iterator;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__
