//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__

#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator () noexcept = default;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > (
                                pOwner,
                                pDelegate
                        ) {

                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                        __ForwardDelegateWrapperIterator const & iterator
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > ( iterator ) {

                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardDelegateWrapperIterator < __ElementType > :: __ForwardDelegateWrapperIterator (
                        __ForwardDelegateWrapperIterator && iterator
                ) noexcept :
                        __AbstractDelegateWrapperIterator < __ElementType > ( std :: move ( iterator ) ) {

                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __ForwardDelegateWrapperIterator < __ElementType > :: ~__ForwardDelegateWrapperIterator () noexcept = default;


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __ForwardDelegateWrapperIterator < __ElementType > :: operator = (
                        __ForwardDelegateWrapperIterator const & iterator
                ) noexcept -> __ForwardDelegateWrapperIterator & {

                    return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->copy ( iterator ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __ForwardDelegateWrapperIterator < __ElementType > :: operator = (
                        __ForwardDelegateWrapperIterator && iterator
                ) noexcept -> __ForwardDelegateWrapperIterator & {

                    return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->move ( std :: move ( iterator ) ) ); // NOLINT(misc-unconventional-assign-operator)
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator == (
                        __ForwardDelegateWrapperIterator const & iterator
                ) const noexcept -> bool {

                    return this->equals ( iterator );
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator != (
                        __ForwardDelegateWrapperIterator const & iterator
                ) const noexcept -> bool {

                    return ! this->equals ( iterator );
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator ++ () noexcept -> __ForwardDelegateWrapperIterator & {

                    return reinterpret_cast < __ForwardDelegateWrapperIterator & > ( this->advance ( __IteratorAdvanceDirection :: __iad_forward ) );
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator * () const noexcept -> ElementType & {

                    return this->value();
                }


                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __ForwardDelegateWrapperIterator < __ElementType > :: operator -> () const noexcept -> ElementType * {

                    return & ( this->value() );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
