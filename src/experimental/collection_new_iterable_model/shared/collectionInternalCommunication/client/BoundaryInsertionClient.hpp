//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > class __BoundaryInsertionClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;
                };

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > class __LocalBoundaryInsertionClient {    // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_HPP__
