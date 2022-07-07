//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator () noexcept = default;


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                        IteratorType const & iterator
                ) noexcept :
                        _wrappedIterator ( iterator ) {

                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                        IteratorType && iterator
                ) noexcept :
                        _wrappedIterator ( std :: move ( iterator ) ) {

                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                        __DelegateIterator const & iterator
                ) noexcept :
                        _wrappedIterator ( iterator._wrappedIterator ) {

                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr __DelegateIterator < __ElementType, __WrappedIteratorType > :: __DelegateIterator (
                        __DelegateIterator && iterator
                ) noexcept :
                        _wrappedIterator ( std :: move ( iterator._wrappedIterator ) ) {

                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprDestructor __DelegateIterator < __ElementType, __WrappedIteratorType > :: ~__DelegateIterator () noexcept = default;


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __DelegateIterator <
                        __ElementType,
                        __WrappedIteratorType
                > :: iterator () const noexcept -> __WrappedIteratorType const & {

                    return this->_wrappedIterator;
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TWrappedIteratorType,                                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value
                        >
                > constexpr auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: __advanceBackwards () noexcept -> void {

                    -- this->_wrappedIterator;
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TWrappedIteratorType,                                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value
                        >
                > constexpr auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: __advanceBackwards () noexcept -> void {

                    /* empty on purpose, as WrappedIteratorType does not have a '-- operator' definition */
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: advance (
                        __IteratorAdvanceDirection direction
                ) noexcept -> void {

                    if ( direction == __IteratorAdvanceDirection :: __iad_forward ) {
                        ++ this->_wrappedIterator;
                        return;
                    }

                    return this->__advanceBackwards();
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: equals (
                        __AbstractDelegateIterator < __ElementType > const & iterator
                ) const noexcept -> bool {

                    return this->_wrappedIterator == reinterpret_cast < decltype ( this ) > ( & iterator )->_wrappedIterator;
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: valid () const noexcept -> bool {

                    return static_cast < bool > ( this->_wrappedIterator );
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: copy () const noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return cds :: copy ( * this );
                }


                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_ConstexprPureAbstract auto __DelegateIterator < __ElementType, __WrappedIteratorType > :: value () const noexcept -> ElementType & {

                    return * this->_wrappedIterator;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERATOR_IMPL_HPP__
