//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                      // NOLINT(bugprone-reserved-identifier)
                > class __AbstractIteratorRemovePrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __acirc_ElementType       = // NOLINT(bugprone-reserved-identifier)
                            __ElementType;

                protected:
                    using AbstractIterator          = // NOLINT(bugprone-reserved-identifier)
                            __AbstractDelegateWrapperIterator < __acirc_ElementType >;

                protected:
                    auto remove (
                            AbstractIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto removeAll (
                            AbstractIterator const * pIterators,
                            Size                     iteratorCount
                    ) noexcept -> Size;
                };


                template <
                        typename __ReceiverType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                  // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                  // NOLINT(bugprone-reserved-identifier)
                > class __LocalIteratorRemovePrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __acirc_ElementType   = // NOLINT(bugprone-reserved-identifier)
                            __ElementType;

                protected:
                    using Iterator              = // NOLINT(bugprone-reserved-identifier)
                            __IteratorType;

                protected:
                    auto remove (
                            Iterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto removeAll (
                            Iterator const * pIterators,
                            Size             iteratorCount
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
