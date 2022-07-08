//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType                                       // NOLINT(bugprone-reserved-identifier)
                > class __AbstractConstIteratorRelativeInsertionPrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                private:
                    using AbstractConstIterator  =
                            __AbstractDelegateWrapperIterator < __ElementType const >;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractConstIterator   const & iterator,
                            ElementType             const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractConstIterator    const & iterator,
                            ElementType                   && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractConstIterator   const & iterator,
                            ElementType             const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractConstIterator    const & iterator,
                            ElementType                   && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBefore (
                            AbstractConstIterator        const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceAfter (
                            AbstractConstIterator        const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllBefore (
                            AbstractConstIterator    const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllAfter (
                            AbstractConstIterator    const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractConstIterator                       const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractConstIterator                       const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            AbstractConstIterator   const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            AbstractConstIterator   const & iterator,
                            __OtherIteratorType     const & iterableType,
                            __OtherIteratorType     const & end
                    ) noexcept (false) -> void;
                };


                template <
                        typename __ReceiverType,                                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                 // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,                                  // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                                 // NOLINT(bugprone-reserved-identifier)
                > class __LocalConstIteratorRelativeInsertionPrimitiveClient {  // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                private:
                    using ConstIterator = __IteratorType;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            ConstIterator   const & iterator,
                            ElementType     const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            ConstIterator    const & iterator,
                            ElementType           && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            ConstIterator   const & iterator,
                            ElementType     const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            ConstIterator    const & iterator,
                            ElementType           && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBefore (
                            ConstIterator                const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceAfter (
                            ConstIterator                const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllBefore (
                            ConstIterator            const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllAfter (
                            ConstIterator            const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            ConstIterator   const & iterator,
                            __IterableType  const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            ConstIterator                               const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            ConstIterator           const & iterator,
                            __IterableType          const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            ConstIterator                               const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            ConstIterator           const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            ConstIterator           const & iterator,
                            __OtherIteratorType     const & iterableType,
                            __OtherIteratorType     const & end
                    ) noexcept (false) -> void;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
