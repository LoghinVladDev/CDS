//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType                   // NOLINT(bugprone-reserved-identifier)
                > class __BoundaryInsertionPrimitiveClient {    // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;

                public:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;
                };


                template <
                        typename __ReceiverType,                    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType                       // NOLINT(bugprone-reserved-identifier)
                > class __LocalBoundaryInsertionPrimitiveClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto prepend (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto append (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;

                public:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__
