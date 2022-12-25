/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineIterableServer =
                    __IterableServer <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineDelegateForwardIterableClient =
                    __LocalDelegateForwardConstIterablePrimitiveClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineContainsOfIterableClient =
                    __LocalContainsOfCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult,
                            cds :: Iterable < __MapperResult >,
                            & __iterableContains < __MapperResult >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineContainsOfInitializerListClient =
                    __LocalContainsOfCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult,
                            std :: initializer_list < __MapperResult >,
                            & __initializerListContains <
                                    __MapperResult,
                                    & cds :: meta :: equals < __MapperResult >
                            >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineFindOfIterableClient =
                    __LocalFindOfImmutableCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult,
                            __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult >,
                            cds :: Iterable < __MapperResult >,
                            & __iterableContains < __MapperResult >,
                            & __iterableNotContains < __MapperResult >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineFindOfInitializerListClient =
                    __LocalFindOfImmutableCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult,
                            __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult >,
                            std :: initializer_list < __MapperResult >,
                            & __initializerListContains <
                                    __MapperResult,
                                    & cds :: meta :: equals < __MapperResult >
                            >,
                            & __initializerListNotContains <
                                    __MapperResult,
                                    & cds :: meta :: equals < __MapperResult >
                            >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineFindByClient =
                    __LocalFindByImmutableCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult,
                            __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult >
                    >;


            template < typename __ElementType, typename __Mapper, typename __MapperResult >         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __LazySequenceTransitionPipelineGenericStatementsClient = /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __LocalGenericImmutableStatementsCompositeClient <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult
                    >;

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ */
