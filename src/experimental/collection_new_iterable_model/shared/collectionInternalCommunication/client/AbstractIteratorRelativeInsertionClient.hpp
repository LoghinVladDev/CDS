//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_ABSTRACT_ITERATOR_RELATIVE_INSERTION_CLIENT_HPP__
#define __CDS_SHARED_ABSTRACT_ITERATOR_RELATIVE_INSERTION_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType                       // NOLINT(bugprone-reserved-identifier)
                > class __AbstractIteratorRelativeInsertionClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                private:
                    using AbstractIterator  =
                            __AbstractDelegateWrapperIterator < __ElementType >;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBefore (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceAfter (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllBefore (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllAfter (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __OtherIteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & iterableType,
                            __OtherIteratorType const & end
                    ) noexcept (false) -> void;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_ITERATOR_RELATIVE_INSERTION_CLIENT_HPP__
