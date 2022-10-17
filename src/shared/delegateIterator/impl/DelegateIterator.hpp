/*
 * Created by loghin on 6/26/22.
 */
 
#ifndef __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator () noexcept = default;


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                    IteratorType const & iterator
            ) noexcept :
                    _wrappedIterator ( iterator ) {

                /* initialization, copy base iterator */
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                    IteratorType && iterator
            ) noexcept :
                    _wrappedIterator ( std :: move ( iterator ) ) {

                /* initialization, move base iterator */
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                    __DelegateIterator const & iterator
            ) noexcept :
                    _wrappedIterator ( iterator._wrappedIterator ) {

                /* initialization, copy iterator's base iterator */
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                    __DelegateIterator && iterator
            ) noexcept :
                    _wrappedIterator ( std :: move ( iterator._wrappedIterator ) ) {

                /* initialization, move iterator's base iterator */
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprDestructor __DelegateIterator < __ElementType, __WrappedIteratorType > :: ~__DelegateIterator () noexcept = default;


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TWrappedIteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value
                    >
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: __advanceBackwards () noexcept -> void {

                /* since wrapped iterator is bidirectional, -- is possible */
                -- this->_wrappedIterator;
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprOverride auto __DelegateIterator <
                    __ElementType,
                    __WrappedIteratorType
            > :: iterator () const noexcept -> __WrappedIteratorType const * {

                /* return the address of this iterator */
                return & this->_wrappedIterator;
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TWrappedIteratorType,                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value
                    >
            > __CDS_cpplang_ConstexprNonLiteralReturn auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: __advanceBackwards () noexcept -> void {

                /* empty on purpose, as WrappedIteratorType does not have a '-- operator' definition */
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: advance (
                    __IteratorAdvanceDirection direction
            ) noexcept -> void {

                /* if direction is forward, advance forward */
                if ( direction == __IteratorAdvanceDirection :: __iad_forward ) {
                    ++ this->_wrappedIterator;
                    return;
                }

                /* otherwise, advance backward */
                return this->__advanceBackwards();
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: equals (
                    __AbstractDelegateIterator < __ElementType > const & iterator
            ) const noexcept -> bool {

                /* reinterpret received iterator, as it will receive only compatible iterators, and compare wrapped iterators */
                return this->_wrappedIterator == reinterpret_cast < decltype ( this ) > ( & iterator )->_wrappedIterator;
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: valid () const noexcept -> bool {

                /* valid if the wrapped iterator is valid ( bool cast ) */
                return static_cast < bool > ( this->_wrappedIterator );
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: copy () const noexcept -> __AbstractDelegateIterator < __ElementType > * {

                /* create a copy of this value */
                return cds :: copy ( * this );
            }


            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: value () const noexcept -> ElementType & {

                /* return the value of the wrapped iterator */
                return * this->_wrappedIterator;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__ */
