/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult = cds :: meta :: RemoveReference < typename std :: invoke_result < __Mapper, __ElementType const & > :: type >
            > class __LazySequenceTransitionPipeline;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType, typename __Mapper, typename __MapperResult >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __CDS_InheritsEBOs __LazySequenceTransitionPipelineConstIterator : public cds :: meta :: ForwardIterator { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:
                __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >    const * _pPipeline {nullptr};

            private:
                __LazySequenceConstIterator < __ElementType >                                           _iterator;

            public:
                constexpr __LazySequenceTransitionPipelineConstIterator () noexcept = delete;

            public:
                __LazySequenceTransitionPipelineConstIterator (
                        __LazySequenceTransitionPipelineConstIterator const & iterator
                ) noexcept;

            public:
                constexpr __LazySequenceTransitionPipelineConstIterator (
                        __LazySequenceTransitionPipelineConstIterator && iterator
                ) noexcept;

            public:
                __LazySequenceTransitionPipelineConstIterator (
                        __LazySequenceConstIterator < __ElementType     >                                    && iterator,
                        __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >    const & sequence
                ) noexcept;

            public:
                ~__LazySequenceTransitionPipelineConstIterator () noexcept = default;

            public:
                auto operator = (
                        __LazySequenceTransitionPipelineConstIterator const & iterator
                ) noexcept -> __LazySequenceTransitionPipelineConstIterator &;

            public:
                auto operator = (
                        __LazySequenceTransitionPipelineConstIterator && iterator
                ) noexcept -> __LazySequenceTransitionPipelineConstIterator &;

            public:
                __CDS_NoDiscard constexpr auto operator * () const noexcept -> __MapperResult const &;

            public:
                __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __MapperResult const *;

            public:
                __CDS_NoDiscard constexpr auto operator == (
                        __LazySequenceTransitionPipelineConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto operator != (
                        __LazySequenceTransitionPipelineConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                auto operator ++ () noexcept -> __LazySequenceTransitionPipelineConstIterator &;

            public:
                auto operator ++ (int) noexcept -> __LazySequenceTransitionPipelineConstIterator;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_HPP__ */
