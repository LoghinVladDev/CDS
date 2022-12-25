/*
 * Created by loghin on 05/11/22.
 */

#ifndef __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > class __LazySequenceTransitionPipeline :                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    public cds :: Iterable < __MapperResult >,
                    private __LazySequenceTransitionPipelineIterableServer < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineDelegateForwardIterableClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineContainsOfIterableClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineContainsOfInitializerListClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineFindOfIterableClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineFindOfInitializerListClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineFindByClient < __ElementType, __Mapper, __MapperResult >,
                    public __LazySequenceTransitionPipelineGenericStatementsClient < __ElementType, __Mapper, __MapperResult > {

            private:
                cds :: Iterable < __ElementType >   const * _pBaseIterable  {nullptr};

            private:
                bool                                        _ownedIterable  {false};

            private:
                __Mapper                                    _mapper;

            private:
                using BaseIterable = cds :: Iterable < __ElementType >;

            private:
                using Server =
                        __LazySequenceTransitionPipelineIterableServer < __ElementType, __Mapper, __MapperResult >;

            private:
                using DelegateForwardIterableClient =
                        __LazySequenceTransitionPipelineDelegateForwardIterableClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using ContainsOfIterableClient =
                        __LazySequenceTransitionPipelineContainsOfIterableClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using ContainsOfInitializerListClient =
                        __LazySequenceTransitionPipelineContainsOfInitializerListClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using FindOfIterableClient =
                        __LazySequenceTransitionPipelineFindOfIterableClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using FindOfInitializerListClient =
                        __LazySequenceTransitionPipelineFindOfInitializerListClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using FindByClient =
                        __LazySequenceTransitionPipelineFindByClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using GenericStatementsClient =
                        __LazySequenceTransitionPipelineGenericStatementsClient < __ElementType, __Mapper, __MapperResult >;

            private:
                using typename BaseIterable :: __GenericHandler;

            private:
                using typename BaseIterable :: __GenericConstHandler;

            public:
                using typename DelegateForwardIterableClient :: ConstIterator;

            private:
                friend class __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult >;

            private:
                friend DelegateForwardIterableClient;

            private:
                friend Server;

            private:
                friend ContainsOfIterableClient;

            private:
                friend ContainsOfInitializerListClient;

            private:
                friend FindOfIterableClient;

            private:
                friend FindOfInitializerListClient;

            private:
                friend FindByClient;

            private:
                friend GenericStatementsClient;

            private:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (
                        __IterableInternalRequestType requestType
                ) noexcept -> __GenericHandler override;

            private:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (
                        __IterableInternalRequestType requestType
                ) const noexcept -> __GenericConstHandler override;

            private:
                __CDS_NoDiscard static auto __cbegin (
                        __LazySequenceTransitionPipeline const * pObject
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            private:
                __CDS_NoDiscard static auto __cend (
                        __LazySequenceTransitionPipeline const * pObject
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            private:
                __CDS_NoDiscard constexpr static auto __cbeginLocal (
                        __LazySequenceTransitionPipeline const * pObject
                ) noexcept -> ConstIterator;

            private:
                __CDS_NoDiscard constexpr static auto __cendLocal (
                        __LazySequenceTransitionPipeline const * pObject
                ) noexcept -> ConstIterator;

            public:
                using DelegateForwardIterableClient :: begin;

            public:
                using DelegateForwardIterableClient :: end;

            public:
                using DelegateForwardIterableClient :: cbegin;

            public:
                using DelegateForwardIterableClient :: cend;

            public:
                using ContainsOfIterableClient :: containsAnyOf;

            public:
                using ContainsOfIterableClient :: containsAllOf;

            public:
                using ContainsOfIterableClient :: containsNoneOf;

            public:
                using ContainsOfIterableClient :: containsAnyNotOf;

            public:
                using ContainsOfInitializerListClient :: containsAnyOf;

            public:
                using ContainsOfInitializerListClient :: containsAllOf;

            public:
                using ContainsOfInitializerListClient :: containsNoneOf;

            public:
                using ContainsOfInitializerListClient :: containsAnyNotOf;

            public:
                using FindOfIterableClient :: findOf;

            public:
                using FindOfIterableClient :: findFirstOf;

            public:
                using FindOfIterableClient :: findLastOf;

            public:
                using FindOfIterableClient :: findAllOf;

            public:
                using FindOfIterableClient :: findNotOf;

            public:
                using FindOfIterableClient :: findFirstNotOf;

            public:
                using FindOfIterableClient :: findLastNotOf;

            public:
                using FindOfIterableClient :: findAllNotOf;

            public:
                using FindOfInitializerListClient :: findOf;

            public:
                using FindOfInitializerListClient :: findFirstOf;

            public:
                using FindOfInitializerListClient :: findLastOf;

            public:
                using FindOfInitializerListClient :: findAllOf;

            public:
                using FindOfInitializerListClient :: findNotOf;

            public:
                using FindOfInitializerListClient :: findFirstNotOf;

            public:
                using FindOfInitializerListClient :: findLastNotOf;

            public:
                using FindOfInitializerListClient :: findAllNotOf;

            public:
                using FindByClient :: findThat;

            public:
                using FindByClient :: findFirstThat;

            public:
                using FindByClient :: findLastThat;

            public:
                using FindByClient :: findAllThat;

            public:
                using GenericStatementsClient :: forEach;

            public:
                using GenericStatementsClient :: count;

            public:
                using GenericStatementsClient :: atLeast;

            public:
                using GenericStatementsClient :: atMost;

            public:
                using GenericStatementsClient :: moreThan;

            public:
                using GenericStatementsClient :: fewerThan;

            public:
                using GenericStatementsClient :: any;

            public:
                using GenericStatementsClient :: all;

            public:
                using GenericStatementsClient :: none;

            public:
                __LazySequenceTransitionPipeline () noexcept = delete;

            public:
                constexpr __LazySequenceTransitionPipeline (
                        __LazySequence < __ElementType > * pSequence,
                        bool                               ownership
                ) noexcept;

            public:
                ~__LazySequenceTransitionPipeline() noexcept override;
            };

        }
    }
}

#endif /* __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_HPP__ */
