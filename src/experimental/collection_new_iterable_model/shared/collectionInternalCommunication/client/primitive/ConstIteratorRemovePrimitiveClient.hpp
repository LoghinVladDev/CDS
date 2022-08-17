//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename >
                class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType                          // NOLINT(bugprone-reserved-identifier)
                > class __AbstractConstIteratorRemovePrimitiveClient {  // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename, typename >
                    friend class __RemoveByCompositeClient; // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            typename,
                            typename __FElementType,    // NOLINT(bugprone-reserved-identifier)
                            typename __FIterableType,   // NOLINT(bugprone-reserved-identifier)
                            __ContainsFunction < __FIterableType, __FElementType >
                    > friend class __RemoveOfCompositeClient;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __acirc_ElementType       = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                protected:
                    using AbstractConstIterator     = // NOLINT(bugprone-reserved-identifier)
                            __AbstractDelegateWrapperIterator < __acirc_ElementType >;

                public:
                    auto remove (
                            AbstractConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto removeAll (
                            AbstractConstIterator const * pIterators,
                            Size                          iteratorCount
                    ) noexcept -> Size;
                };


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                     // NOLINT(bugprone-reserved-identifier)
                > class __LocalConstIteratorRemovePrimitiveClient { // NOLINT(bugprone-reserved-identifier)

                protected:
                    using __acirc_ElementType       = // NOLINT(bugprone-reserved-identifier)
                            __ElementType const;

                protected:
                    using ConstIterator             = __IteratorType;

                public:
                    auto remove (
                            ConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto removeAll (
                            ConstIterator const * pIterators,
                            Size                  iteratorCount
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
