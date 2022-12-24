/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >
            using __LazySequenceIterableServer =
                    __IterableServer <
                            __LazySequence < __ElementType >,
                            __ElementType
                    >;


            template < typename __ElementType >
            using __LazySequenceDelegateForwardIterableClient =
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __LazySequence < __ElementType >,
                            __LazySequenceConstIterator < __ElementType >
                    >;


            template < typename __ElementType >
            using __LazySequenceContainsOfIterableClient =
                    __LocalContainsOfCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >
                    >;


            template < typename __ElementType >
            using __LazySequenceContainsOfInitializerListClient =
                    __LocalContainsOfCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >
                    >;


            template < typename __ElementType >
            using __LazySequenceFindOfIterableClient =
                    __LocalFindOfImmutableCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType,
                            __LazySequenceConstIterator < __ElementType >,
                            cds :: Iterable < __ElementType >,
                            & __iterableContains < __ElementType >,
                            & __iterableNotContains < __ElementType >
                    >;


            template < typename __ElementType >
            using __LazySequenceFindOfInitializerListClient =
                    __LocalFindOfImmutableCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType,
                            __LazySequenceConstIterator < __ElementType >,
                            std :: initializer_list < __ElementType >,
                            & __initializerListContains <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >,
                            & __initializerListNotContains <
                                    __ElementType,
                                    & cds :: meta :: equals < __ElementType >
                            >
                    >;


            template < typename __ElementType >
            using __LazySequenceFindByClient =
                    __LocalFindByImmutableCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType,
                            __LazySequenceConstIterator < __ElementType >
                    >;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __LazySequenceGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __LazySequence < __ElementType >,
                            __ElementType
                    >;

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_CONSTRUCTS_HPP__ */
