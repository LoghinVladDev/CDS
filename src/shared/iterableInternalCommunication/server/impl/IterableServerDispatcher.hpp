/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                            __ServerType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ServiceType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cbeginFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cendFunction          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __IterableServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction
            > :: __cbegin (
                    __ServerType const * pServer
            ) noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                        ( pServer ->* __cbeginFunction ) ()
                );
            }


            template <
                    typename                                                                            __ServerType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ServiceType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cbeginFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cendFunction          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __IterableServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction
            > :: __cend (
                    __ServerType const * pServer
            ) noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance ().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                        ( pServer ->* __cendFunction ) ()
                );
            }


            template <
                    typename                                                                            __ServerType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ServiceType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cbeginFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cendFunction          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > constexpr auto __IterableServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction
            > :: __cbeginLocal (
                    __ServerType const * pServer
            ) noexcept -> __ConstIteratorType {

                /* call the template received member function */
                return ( pServer ->* __cbeginFunction ) ();
            }


            template <
                    typename                                                                            __ServerType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ServiceType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cbeginFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cendFunction          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > constexpr auto __IterableServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction
            > :: __cendLocal (
                    __ServerType const * pServer
            ) noexcept -> __ConstIteratorType {

                /* call the template received member function */
                return ( pServer ->* __cendFunction ) ();
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_IMPL_HPP__ */
