/*
 * Created by loghin on 12/24/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_LAZY_SEQUENCE_CONST_ITERATOR_IMPL_HPP__

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >
            __CDS_OptimalInline __LazySequenceConstIterator < __ElementType > :: __LazySequenceConstIterator (
                    __LazySequenceConstIterator const & iterator
            ) noexcept :
                    _pSequence ( iterator._pSequence ),
                    _iterator ( iterator._iterator ) {

            }


            template < typename __ElementType >
            constexpr __LazySequenceConstIterator < __ElementType > :: __LazySequenceConstIterator (
                    __LazySequenceConstIterator && iterator
            ) noexcept :
                    _pSequence ( cds :: exchange ( iterator._pSequence, nullptr ) ),
                    _iterator ( std :: move ( iterator._iterator ) ) {

            }


            template < typename __ElementType >
            __CDS_OptimalInline __LazySequenceConstIterator < __ElementType > :: __LazySequenceConstIterator (
                    typename cds :: Iterable < __ElementType > :: ConstIterator      && iterator,
                    __LazySequence < __ElementType >                            const & sequence
            ) noexcept :
                    _pSequence ( & sequence ),
                    _iterator ( std :: move ( iterator ) ) {

                this->__ls_filter();
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __LazySequenceConstIterator < __ElementType > :: operator = (
                    __LazySequenceConstIterator const & iterator
            ) noexcept -> __LazySequenceConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pSequence    = iterator._pSequence;
                this->_iterator     = iterator._iterator;

                return * this;
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __LazySequenceConstIterator < __ElementType > :: operator = (
                    __LazySequenceConstIterator && iterator
            ) noexcept -> __LazySequenceConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pSequence    = cds :: exchange ( iterator._pSequence, nullptr );
                this->_iterator     = std :: move ( iterator._iterator );

                return * this;
            }


            template < typename __ElementType >
            constexpr auto __LazySequenceConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

                return * this->_iterator;
            }


            template < typename __ElementType >
            constexpr auto __LazySequenceConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

                return & ( * this->_iterator );
            }


            template < typename __ElementType >
            constexpr auto __LazySequenceConstIterator < __ElementType > :: operator == (
                    __LazySequenceConstIterator const & iterator
            ) const noexcept -> bool {

                if ( this == & iterator ) {
                    return true;
                }

                return
                        this->_pSequence == iterator._pSequence &&
                        this->_iterator  == iterator._iterator;
            }


            template < typename __ElementType >
            constexpr auto __LazySequenceConstIterator < __ElementType > :: operator != (
                    __LazySequenceConstIterator const & iterator
            ) const noexcept -> bool {

                if ( this == & iterator ) {
                    return false;
                }

                return
                        this->_pSequence != iterator._pSequence ||
                        this->_iterator  != iterator._iterator;
            }


            template < typename __ElementType >
            auto __LazySequenceConstIterator < __ElementType > :: operator ++ () noexcept -> __LazySequenceConstIterator & {

                ++ this->_iterator;
                this->__ls_filter();
                return * this;
            }


            template < typename __ElementType >
            auto __LazySequenceConstIterator < __ElementType > :: __ls_filter () noexcept -> void {

                auto const end = this->_pSequence->_pBaseIterable->end();
                bool allFiltersSatisfied = false;
                while ( this->_iterator != end && ! allFiltersSatisfied ) {

                    allFiltersSatisfied = true;
                    auto const & value = * this->_iterator;
                    for ( uint32 filterIndex = 0U; filterIndex < this->_pSequence->_filterCount; ++ filterIndex ) {
                        if ( ! this->_pSequence->_pFilters [ filterIndex ] ( value ) ) {
                            allFiltersSatisfied = false;
                            break;
                        }
                    }

                    if ( ! allFiltersSatisfied ) {
                        ++ this->_iterator;
                    }
                }
            }


            template < typename __ElementType >
            auto __LazySequenceConstIterator < __ElementType > :: operator ++ (int) noexcept -> __LazySequenceConstIterator {

                auto copy = * this;
                ++ * this;
                return copy;
            }


            template < typename __ElementType >
            constexpr __LazySequenceConstIterator < __ElementType > :: operator bool () const noexcept {

                return
                        this->_pSequence != nullptr &&
                        static_cast < bool > ( this->_iterator );
            }

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_CONST_ITERATOR_IMPL_HPP__ */
