/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                constexpr __BidirectionalDelegateWrapperIterator < __ElementType > :: __BidirectionalDelegateWrapperIterator () noexcept = default;


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                constexpr __BidirectionalDelegateWrapperIterator < __ElementType > :: __BidirectionalDelegateWrapperIterator (
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > (
                                pOwner,
                                pDelegate
                        ) {

                    /* Construct Base Class with given parameters */
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline __BidirectionalDelegateWrapperIterator < __ElementType > :: __BidirectionalDelegateWrapperIterator (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > ( iterator ) {

                    /* Construct Base Class with Copy Constructor */
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                constexpr __BidirectionalDelegateWrapperIterator < __ElementType > :: __BidirectionalDelegateWrapperIterator (
                        __BidirectionalDelegateWrapperIterator && iterator
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > ( std :: move ( iterator ) ) {

                    /* Construct Base Class with Move Constructor */
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __BidirectionalDelegateWrapperIterator < __ElementType > :: ~__BidirectionalDelegateWrapperIterator () noexcept = default;


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator = (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) noexcept -> __BidirectionalDelegateWrapperIterator & {

                    /* Call base copy function and reinterpret result, as this is __BidirectionalDelegateWrapperIterator */
                    return reinterpret_cast < __BidirectionalDelegateWrapperIterator & > ( this->copy ( iterator ) ); /* NOLINT(misc-unconventional-assign-operator) */
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator = (
                        __BidirectionalDelegateWrapperIterator && iterator
                ) noexcept -> __BidirectionalDelegateWrapperIterator & {

                    /* Call base move function and reinterpret result, as this is __BidirectionalDelegateWrapperIterator */
                    return reinterpret_cast < __BidirectionalDelegateWrapperIterator & > ( this->move ( std :: move ( iterator ) ) ); /* NOLINT(misc-unconventional-assign-operator) */
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator == (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) const noexcept -> bool {

                    /* Call base equals function */
                    return this->equals ( iterator );
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator != (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) const noexcept -> bool {

                    /* Call base equals function and reverse result */
                    return ! this->equals ( iterator );
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator ++ () noexcept -> __BidirectionalDelegateWrapperIterator & {

                    /* Request an iterator advance in the forward direction */
                    return reinterpret_cast < __BidirectionalDelegateWrapperIterator & > ( this->advance ( __IteratorAdvanceDirection :: __iad_forward ) );
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator -- () noexcept -> __BidirectionalDelegateWrapperIterator & {

                    /* Request an iterator advance in the backward direction */
                    return reinterpret_cast < __BidirectionalDelegateWrapperIterator & > ( this->advance ( __IteratorAdvanceDirection :: __iad_backward ) );
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator * () const noexcept -> ElementType & {

                    /* Request the stored value */
                    return this->value();
                }


                template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprPureAbstract auto __BidirectionalDelegateWrapperIterator < __ElementType > :: operator -> () const noexcept -> ElementType * {

                    /* Request the address of the stored value */
                    return & ( this->value() );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ */
