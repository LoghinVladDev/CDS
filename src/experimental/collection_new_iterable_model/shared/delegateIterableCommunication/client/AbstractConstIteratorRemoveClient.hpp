//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_HPP__
#define __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier)

                template < typename, typename >
                class __IterableRemoveByPredicate;          // NOLINT(bugprone-reserved-identifier)

                template <
                        typename,
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >
                > class __IterableRemoveOf;                                                             // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                  // NOLINT(bugprone-reserved-identifier)
                > class __AbstractConstIteratorRemoveClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    friend class __IterableRemoveByPredicate < __ReceiverType, __ElementType >;

                private:
                    template <
                            typename,                                                   // NOLINT(bugprone-reserved-identifier)
                            typename __TElementType,                                    // NOLINT(bugprone-reserved-identifier)
                            typename __FromIterableType,                                // NOLINT(bugprone-reserved-identifier)
                            __ContainsFunction < __FromIterableType, __TElementType >   // NOLINT(bugprone-reserved-identifier)
                    > friend class __IterableRemoveOf;                                  // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __acirc_ElementType       = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                protected:
                    using AbstractConstIterator     = // NOLINT(bugprone-reserved-identifier)
                            __AbstractDelegateWrapperIterator < __acirc_ElementType >;

                protected:
                    auto remove (
                            AbstractConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto removeAll (
                            AbstractConstIterator const * pIterators,
                            Size                          iteratorCount
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_CONST_ITERATOR_REMOVE_CLIENT_HPP__
