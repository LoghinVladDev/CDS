//
// Created by loghin on 7/7/2022.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __begin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return Memory :: instance().create < __disis_Delegate > (
                            reinterpret_cast < __ReceiverType * > ( this )->begin()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __end () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return Memory :: instance().create < __disis_Delegate > (
                            reinterpret_cast < __ReceiverType * > ( this )->end()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerConstIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __cbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return Memory :: instance().create < __discis_Delegate > (
                            reinterpret_cast < __ReceiverType const * > ( this )->cbegin()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerConstIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __cend () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return Memory :: instance().create < __discis_Delegate > (
                            reinterpret_cast < __ReceiverType const * > ( this )->cend()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerReverseIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __rbegin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return Memory :: instance().create < __disris_Delegate > (
                            reinterpret_cast < __ReceiverType * > ( this )->rbegin()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerReverseIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __rend () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    return Memory :: instance().create < __disris_Delegate > (
                            reinterpret_cast < __ReceiverType * > ( this )->rend()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerConstReverseIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __crbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return Memory :: instance().create < __discris_Delegate > (
                            reinterpret_cast < __ReceiverType const * > ( this )->crbegin()
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServerConstReverseIteratorService <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: __crend () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    return Memory :: instance().create < __discris_Delegate > (
                            reinterpret_cast < __ReceiverType const * > ( this )->crend()
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__
