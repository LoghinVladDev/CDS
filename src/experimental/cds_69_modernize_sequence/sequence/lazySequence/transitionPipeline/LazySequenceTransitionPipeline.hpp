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
                    private __LazySequenceTransitionPipelineIterableServer < __ElementType, __Mapper, __MapperResult > {

            private:
                cds :: Iterable < __ElementType >   const * _pBaseIterable  {nullptr};

            private:
                bool                                        _ownedIterable  {false};

            private:
                __Mapper                                    _mapper;

            private:
                using BaseIterable = cds :: Iterable < __MapperResult >;

            private:
                using Server =
                        __LazySequenceTransitionPipelineIterableServer < __ElementType, __Mapper, __MapperResult >;

            private:
                using typename BaseIterable :: __GenericHandler;

            private:
                using typename BaseIterable :: __GenericConstHandler;

            private:
                friend Server;

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
                ) noexcept -> __AbstractDelegateIterator < __MapperResult > *;

            private:
                __CDS_NoDiscard static auto __cend (
                        __LazySequenceTransitionPipeline const * pObject
                ) noexcept -> __AbstractDelegateIterator < __MapperResult > *;

            public:
                __LazySequenceTransitionPipeline () noexcept = delete;

            public:
                constexpr __LazySequenceTransitionPipeline (
                        __Mapper                            const & mapper,
                        cds :: Iterable < __ElementType >   const * pIterable,
                        bool                                        ownership
                ) noexcept;

            public:
                ~__LazySequenceTransitionPipeline() noexcept override;
            };

        }
    }
}

#endif /* __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_HPP__ */
