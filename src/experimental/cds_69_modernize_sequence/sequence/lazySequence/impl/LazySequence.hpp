/*
 * Created by loghin on 12/24/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_IMPL_HPP__
#define __CDS_LAZY_SEQUENCE_IMPL_HPP__

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >
            uint32 const __LazySequence < __ElementType > :: __ls_baseFilterCapacity;


            template < typename __ElementType >
            __CDS_cpplang_ConstexprOverride auto __LazySequence < __ElementType > :: __iicch_obtainGenericHandler (
                    __IterableInternalRequestType requestType
            ) noexcept -> __GenericHandler {

                return this->__is_handlers () [ static_cast < uint32 > ( requestType ) ];
            }


            template < typename __ElementType >
            __CDS_cpplang_ConstexprOverride auto __LazySequence < __ElementType > :: __iicch_obtainGenericConstHandler (
                    __IterableInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler {

                return this->__is_constHandlers () [ static_cast < uint32 > ( requestType ) ];
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __LazySequence < __ElementType > :: __cbegin (
                    __LazySequence const * pObject
            ) noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                return Memory :: instance().create < __DelegateIterator < __ElementType const, ConstIterator > > (
                        ConstIterator (
                                pObject->_pBaseIterable->cbegin(),
                                * pObject
                        )
                );
            }


            template < typename __ElementType >
            __CDS_OptimalInline auto __LazySequence < __ElementType > :: __cend (
                    __LazySequence const * pObject
            ) noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                return Memory :: instance().create < __DelegateIterator < __ElementType const, ConstIterator > > (
                        ConstIterator (
                                pObject->_pBaseIterable->cend(),
                                * pObject
                        )
                );
            }


            template < typename __ElementType >
            constexpr auto __LazySequence < __ElementType > :: __cbeginLocal (
                    __LazySequence const * pObject
            ) noexcept -> ConstIterator {

                return {
                    pObject->_pBaseIterable->cbegin(),
                    * pObject
                };
            }


            template < typename __ElementType >
            constexpr auto __LazySequence < __ElementType > :: __cendLocal (
                    __LazySequence const * pObject
            ) noexcept -> ConstIterator {

                return {
                    pObject->_pBaseIterable->cend(),
                    * pObject
                };
            }


            template < typename __ElementType >
            constexpr __LazySequence < __ElementType > :: __LazySequence (
                    cds :: Iterable < __ElementType > const & iterable
            ) noexcept :
                    _filterCount (0U),
                    _filterCapacity (0U),
                    _pFilters (nullptr),
                    _ownedIterable (false),
                    _pBaseIterable (& iterable) {

            }


            template < typename __ElementType >
            __CDS_OptimalInline __LazySequence < __ElementType > :: ~__LazySequence () noexcept {

                if ( this->_ownedIterable ) {
                    delete this->_pBaseIterable;
                }

                __allocation :: __freePrimitiveArray (
                        this->_pFilters
                );
            }


            template < typename __ElementType >
            template < typename __Predicate >
            __CDS_OptimalInline auto __LazySequence < __ElementType > :: filter (
                    __Predicate const & predicate
            ) noexcept -> __LazySequence & {

                if ( this->_filterCount == this->_filterCapacity ) {

                    this->_filterCapacity   = cds :: maxOf ( __ls_baseFilterCapacity, 2 * this->_filterCapacity );
                    this->_pFilters         = __allocation :: __reallocPrimitiveArray < cds :: functional :: Predicate < __ElementType const & > > (
                            this->_pFilters,
                            this->_filterCapacity
                    );
                }

                (void) new ( & this->_pFilters [ this->_filterCount ++ ] ) cds :: functional :: Predicate < __ElementType const & > (
                        predicate
                );
                return * this;
            }

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_IMPL_HPP__ */
