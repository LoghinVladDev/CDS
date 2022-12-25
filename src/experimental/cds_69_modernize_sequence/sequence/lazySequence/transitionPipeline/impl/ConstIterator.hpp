/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __LazySequenceTransitionPipelineConstIterator (
                    __LazySequenceTransitionPipelineConstIterator const & iterator
            ) noexcept :
                    _pPipeline ( iterator._pPipeline ),
                    _iterator ( iterator._iterator ) {

            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __LazySequenceTransitionPipelineConstIterator (
                    __LazySequenceTransitionPipelineConstIterator && iterator
            ) noexcept :
                    _pPipeline ( cds :: exchange ( iterator._pPipeline, nullptr ) ),
                    _iterator ( std :: move ( iterator._iterator ) ) {

            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: __LazySequenceTransitionPipelineConstIterator (
                    IterableIterator                                                                     && iterator,
                    __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >    const & pipeline
            ) noexcept :
                    _pPipeline ( & pipeline ),
                    _iterator ( std :: move ( iterator ) ) {

            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator = (
                    __LazySequenceTransitionPipelineConstIterator const & iterator
            ) noexcept -> __LazySequenceTransitionPipelineConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pPipeline    = iterator._pPipeline;
                this->_iterator     = iterator._iterator;
                return * this;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > __CDS_OptimalInline auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator = (
                    __LazySequenceTransitionPipelineConstIterator && iterator
            ) noexcept -> __LazySequenceTransitionPipelineConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pPipeline    = cds :: exchange ( iterator._pPipeline, nullptr );
                this->_iterator     = std :: move ( iterator._iterator );
                return * this;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator * () const noexcept -> __MapperResult {

                return this->_pPipeline->_mapper ( * this->_iterator );
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator == (
                    __LazySequenceTransitionPipelineConstIterator const & iterator
            ) const noexcept -> bool {

                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->_pPipeline == iterator._pPipeline &&
                        this->_iterator  == iterator._iterator;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator != (
                    __LazySequenceTransitionPipelineConstIterator const & iterator
            ) const noexcept -> bool {

                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->_pPipeline != iterator._pPipeline ||
                        this->_iterator  != iterator._iterator;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator ++ () noexcept -> __LazySequenceTransitionPipelineConstIterator & {

                ++ this->_iterator;
                return * this;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > auto __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator ++ (int) noexcept -> __LazySequenceTransitionPipelineConstIterator {

                auto copy = * this;
                ++ this->_iterator;
                return * this;
            }


            template <
                    typename __ElementType,
                    typename __Mapper,
                    typename __MapperResult
            > constexpr __LazySequenceTransitionPipelineConstIterator <
                    __ElementType,
                    __Mapper,
                    __MapperResult
            > :: operator bool () const noexcept {

                return
                        this->_pPipeline != nullptr &&
                        static_cast < bool > ( this->_iterator );
            }

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONST_ITERATOR_IMPL_HPP__ */
