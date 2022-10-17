/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator () noexcept = default;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                    Object                                          const * pOwner,
                    __AbstractDelegateIterator < __ElementType >          * pDelegate
            ) noexcept :
                    __AbstractDelegateWrapperIterator < __ElementType > (
                            pOwner,
                            pDelegate
                    ) {

                /* Construct Base Class with given parameters */
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                    __ForwardDelegateWrapperIterator const & iterator
            ) noexcept :
                    __AbstractDelegateWrapperIterator < __ElementType > ( iterator ) {

                /* Construct Base Class with Copy Constructor */
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                    __ForwardDelegateWrapperIterator && iterator
            ) noexcept :
                    __AbstractDelegateWrapperIterator < __ElementType > ( std :: move ( iterator ) ) {

                /* Construct Base Class with Move Constructor */
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __ForwardDelegateWrapperIterator < __ElementType > :: ~__ForwardDelegateWrapperIterator () noexcept = default;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __ForwardDelegateWrapperIterator < __ElementType > :: operator = (
                    __ForwardDelegateWrapperIterator const & iterator
            ) noexcept -> __ForwardDelegateWrapperIterator & {

                /* Call base copy function and reinterpret result, as this is __ForwardDelegateWrapperIterator */
                return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->copy ( iterator ) ); /* NOLINT(misc-unconventional-assign-operator) */
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_OptimalInline auto __ForwardDelegateWrapperIterator < __ElementType > :: operator = (
                    __ForwardDelegateWrapperIterator && iterator
            ) noexcept -> __ForwardDelegateWrapperIterator & {

                /* Call base move function and reinterpret result, as this is __ForwardDelegateWrapperIterator */
                return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->move ( std :: move ( iterator ) ) ); /* NOLINT(misc-unconventional-assign-operator) */
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator == (
                    __ForwardDelegateWrapperIterator const & iterator
            ) const noexcept -> bool {

                /* Call base equals function */
                return this->equals ( iterator );
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator != (
                    __ForwardDelegateWrapperIterator const & iterator
            ) const noexcept -> bool {

                /* Call base equals function and reverse result */
                return ! this->equals ( iterator );
            }


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator ++ () noexcept -> __ForwardDelegateWrapperIterator & {

                /* Request an iterator advance in the forward direction */
                return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->advance ( __IteratorAdvanceDirection :: __iad_forward ) );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ */
