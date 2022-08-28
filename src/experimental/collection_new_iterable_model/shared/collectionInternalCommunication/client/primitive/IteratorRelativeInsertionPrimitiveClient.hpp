/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                  /* NOLINT(bugprone-reserved-identifier) */
                > class __AbstractIteratorRelativeInsertionPrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ElementType       = __ElementType;

                private:
                    using AbstractIterator  =
                            __AbstractDelegateWrapperIterator < __ElementType >;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    >auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    >auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };


                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                             /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalIteratorRelativeInsertionPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ElementType       = __ElementType;

                private:
                    using Iterator          = __IteratorType;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            Iterator    const & iterator,
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            Iterator    const & iterator,
                            ElementType      && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            Iterator    const & iterator,
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            Iterator    const & iterator,
                            ElementType      && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            Iterator                const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            Iterator                const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            Iterator            const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            Iterator            const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            Iterator        const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            Iterator        const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            Iterator                                    const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            Iterator                                    const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            Iterator            const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ */
