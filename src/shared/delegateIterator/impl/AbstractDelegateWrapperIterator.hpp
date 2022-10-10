/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator () noexcept = default;


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                    Object                                          const * pOwner,
                    __AbstractDelegateIterator < __ElementType >          * pDelegate
            ) noexcept :
                    _pOwner ( pOwner ),
                    _pDelegate ( pDelegate ) {

                /* Initialization constructor stores the owner collection and takes ownership of the wrapped abstract delegate */
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                    __AbstractDelegateWrapperIterator const & iterator
            ) noexcept :
                    _pOwner ( iterator._pOwner ),
                    _pDelegate ( iterator._pDelegate->copy() ) {

                /* Copy Constructor stores the owner collection and creates a copy of the iterator's wrapped abstract delegate for the new iterator to own */
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            constexpr __AbstractDelegateWrapperIterator < __ElementType > :: __AbstractDelegateWrapperIterator (
                    __AbstractDelegateWrapperIterator && iterator
            ) noexcept :
                    _pOwner ( cds :: exchange ( iterator._pOwner, nullptr ) ),
                    _pDelegate ( cds :: exchange ( iterator._pDelegate, nullptr ) ) {

                /* Move Constructor exchanges values stored in the given iterator for null values, taking ownership of the wrapped abstract delegate in the process */
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __AbstractDelegateWrapperIterator < __ElementType > :: ~__AbstractDelegateWrapperIterator () noexcept {

                /* Destructor releases ownership of the wrapped abstract delegate */
                delete this->_pDelegate;
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __AbstractDelegateWrapperIterator < __ElementType > :: of (
                    Object const * pObject
            ) const noexcept -> bool {

                /* Compare the stored owner collection to the received collection */
                return this->_pOwner == pObject;
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: advance (
                    __IteratorAdvanceDirection direction
            ) noexcept -> __AbstractDelegateWrapperIterator & {

                /* Call the advance function in the wrapped abstract delegate */
                this->_pDelegate->advance ( direction );
                return * this;
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: equals (
                    __AbstractDelegateWrapperIterator const & iterator
            ) const noexcept -> bool {

                /* Determine equality based on owner and then by delegate equality */
                return
                        this->_pOwner == iterator._pOwner &&
                        this->_pDelegate->equals ( * iterator._pDelegate );
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: valid () const noexcept -> bool {

                /* Determine validity by owner existence and delegate validity */
                return
                        this->_pDelegate != nullptr &&
                        this->_pDelegate->valid();
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprPureAbstract auto __AbstractDelegateWrapperIterator < __ElementType > :: value () const noexcept -> __ElementType & {

                /* Obtain value from delegate */
                return this->_pDelegate->value();
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto __AbstractDelegateWrapperIterator < __ElementType > :: copy (
                    __AbstractDelegateWrapperIterator const & iterator
            ) noexcept -> __AbstractDelegateWrapperIterator & {

                /* Do nothing if self copying */
                if ( this == & iterator ) {
                    return * this;
                }

                /* Release previous delegate */
                delete this->_pDelegate;

                /* Copy delegate from given iterator. Copy owner as well */
                this->_pDelegate    = iterator._pDelegate->copy();
                this->_pOwner       = iterator._pOwner;

                return * this;
            }


            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto __AbstractDelegateWrapperIterator < __ElementType > :: move (
                    __AbstractDelegateWrapperIterator && iterator
            ) noexcept -> __AbstractDelegateWrapperIterator & {

                /* Do nothing if self moving */
                if ( this == & iterator ) {
                    return * this;
                }

                /* Release previous delegate */
                delete this->_pDelegate;

                /* Take ownership of the delegate from given iterator. Release owner as well */
                this->_pDelegate    = cds :: exchange ( iterator._pDelegate, nullptr );
                this->_pOwner       = cds :: exchange ( iterator._pOwner, nullptr );

                return * this;
            }

        }
    }
}

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_IMPL_HPP__ */
