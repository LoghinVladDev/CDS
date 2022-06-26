//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator () noexcept = default;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept :
                        _pOwner ( pOwner ),
                        _pDelegate ( pDelegate ) {

                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                        __AbstractDelegateWrapperIterator const & iterator
                ) noexcept :
                        _pOwner ( iterator._pOwner ),
                        _pDelegate ( iterator._pDelegate->copy() ) {

                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                        __AbstractDelegateWrapperIterator && iterator
                ) noexcept :
                        _pOwner ( cds :: exchange ( iterator._pOwner, nullptr ) ),
                        _pDelegate ( cds :: exchange ( iterator._pDelegate, nullptr ) ) {

                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __AbstractDelegateWrapperIterator < __ElementType > :: ~__AbstractDelegateWrapperIterator () noexcept {

                    delete this->_pDelegate;
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                constexpr auto __AbstractDelegateWrapperIterator < __ElementType > :: of (
                        Object const * pObject
                ) const noexcept -> bool {

                    return this->_pOwner == pObject;
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: advance (
                        __IteratorAdvanceDirection direction
                ) noexcept -> __AbstractDelegateWrapperIterator & {

                    this->_pDelegate->advance ( direction );
                    return * this;
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: equals (
                        __AbstractDelegateWrapperIterator const & iterator
                ) const noexcept -> bool {

                    return
                            this->_pOwner == iterator._pOwner &&
                            this->_pDelegate->equals ( * iterator._pDelegate );
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: valid () const noexcept -> bool {

                    return
                            this->_pDelegate != nullptr &&
                            this->_pDelegate->valid();
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: value () const noexcept -> __ElementType & {

                    return this->_pDelegate->value();
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __AbstractDelegateWrapperIterator < __ElementType > :: copy (
                        __AbstractDelegateWrapperIterator const & iterator
                ) noexcept -> __AbstractDelegateWrapperIterator & {

                    if ( this == & iterator ) {
                        return * this;
                    }

                    delete this->_pDelegate;
                    this->_pDelegate    = iterator._pDelegate->copy();
                    this->_pOwner       = iterator._pOwner;

                    return * this;
                }


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __AbstractDelegateWrapperIterator < __ElementType > :: move (
                        __AbstractDelegateWrapperIterator && iterator
                ) noexcept -> __AbstractDelegateWrapperIterator & {

                    if ( this == & iterator ) {
                        return * this;
                    }

                    delete this->_pDelegate;
                    this->_pDelegate    = cds :: exchange ( iterator._pDelegate, nullptr );
                    this->_pOwner       = cds :: exchange ( iterator._pOwner, nullptr );

                    return * this;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
