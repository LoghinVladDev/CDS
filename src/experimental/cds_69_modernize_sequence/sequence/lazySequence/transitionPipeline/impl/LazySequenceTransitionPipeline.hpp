/*
 * Created by loghin on 05/11/22.
 */

#ifndef __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_cpplang_ConstexprOverride auto __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __iicch_obtainGenericHandler (
                    __IterableInternalRequestType requestType
            ) noexcept -> __GenericHandler {

                return this->__is_handlers () [static_cast < uint32 > (requestType)];
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_cpplang_ConstexprOverride auto __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __iicch_obtainGenericConstHandler (
                    __IterableInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler {

                return this->__is_constHandlers () [static_cast < uint32 > (requestType)];
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline auto __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __cbegin (
                    __LazySequenceTransitionPipeline const * pObject
            ) noexcept -> __AbstractDelegateIterator < __MapperResult > * {

                return Memory :: instance().create < __DelegateIterator < __MapperResult, __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult > > > (
                        __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult > (
                                pObject->_pBaseIterable->cbegin(),
                                * pObject
                        )
                );
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline auto __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __cend (
                    __LazySequenceTransitionPipeline const * pObject
            ) noexcept -> __AbstractDelegateIterator < __MapperResult > * {

                return Memory :: instance().create < __DelegateIterator < __MapperResult, __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult > > > (
                        __LazySequenceTransitionPipelineConstIterator < __ElementType, __Mapper, __MapperResult > (
                                pObject->_pBaseIterable->cend(),
                                * pObject
                        )
                );
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __LazySequenceTransitionPipeline (
                    __Mapper                            const & mapper,
                    cds :: Iterable < __ElementType >   const * pSequence,
                    bool                                        ownership
            ) noexcept :
                    _mapper (mapper),
                    _pBaseIterable (pSequence),
                    _ownedIterable (ownership) {

            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __LazySequenceTransitionPipeline <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: ~__LazySequenceTransitionPipeline () noexcept {

                if ( this->_ownedIterable ) {
                    Memory :: instance ().destroy (this->_pBaseIterable);
                }
            }

        }
    }
}

#endif /* __CDS_SEQUENCE_LAZY_SEQUENCE_TRANSITION_PIPELINE_IMPL_HPP__ */
