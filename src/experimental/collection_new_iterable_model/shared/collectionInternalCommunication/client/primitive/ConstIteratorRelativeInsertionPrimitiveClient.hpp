/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                      /* NOLINT(bugprone-reserved-identifier) */
                > class __AbstractConstIteratorRelativeInsertionPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ElementType       = __ElementType;

                private:
                    using AbstractConstIterator  =
                            __AbstractDelegateWrapperIterator < __ElementType const >;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractConstIterator   const & iterator,
                            ElementType             const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractConstIterator    const & iterator,
                            ElementType                   && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractConstIterator   const & iterator,
                            ElementType             const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractConstIterator    const & iterator,
                            ElementType                   && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            AbstractConstIterator        const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            AbstractConstIterator        const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            AbstractConstIterator    const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            AbstractConstIterator    const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractConstIterator                       const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractConstIterator   const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractConstIterator                       const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            AbstractConstIterator   const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end,
                            Size                            count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            AbstractConstIterator   const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end,
                            Size                            count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };


                template <
                        typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                                 /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalConstIteratorRelativeInsertionPrimitiveClient {  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ElementType       = __ElementType;

                private:
                    using ConstIterator = __IteratorType;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            ConstIterator   const & iterator,
                            ElementType     const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            ConstIterator    const & iterator,
                            ElementType           && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            ConstIterator   const & iterator,
                            ElementType     const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            ConstIterator    const & iterator,
                            ElementType           && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            ConstIterator                const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            ConstIterator                const &     iterator,
                            __EmplaceArgumentTypes            && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            ConstIterator            const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            ConstIterator            const &     iterator,
                            __ArgumentTypes               && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            ConstIterator   const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            ConstIterator   const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            ConstIterator                               const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            ConstIterator           const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            ConstIterator           const & iterator,
                            __IterableType          const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            ConstIterator                               const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            ConstIterator           const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end,
                            Size                            count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            ConstIterator           const & iterator,
                            __OtherIteratorType     const & begin,
                            __OtherIteratorType     const & end,
                            Size                            count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ */
