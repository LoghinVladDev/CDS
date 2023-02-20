/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "IterableServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __CollectionServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractConstIteratorType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeConstFunction,
                    __removeConstArrayFunction
            > :: __newAddress (
                    __ServerType        * pServer,
                    __ElementType const * pReferenceElement,
                    bool                * pNewElementCreated
            ) noexcept -> __ElementType * {

                /* call the template received member function */
                return ( pServer ->* __newAddressFunction ) (
                        pReferenceElement,
                        pNewElementCreated
                );
            }


            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __CollectionServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractConstIteratorType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeConstFunction,
                    __removeConstArrayFunction
            > :: __removeConst (
                    __ServerType                      * pServer,
                    __AbstractConstIteratorType const * pIterator
            ) noexcept -> bool {

                /* call the template received member function */
                return ( pServer ->* __removeConstFunction ) (
                        * pIterator
                );
            }


            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __CollectionServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractConstIteratorType,
                    __ConstIteratorType,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeConstFunction,
                    __removeConstArrayFunction
            > :: __removeConstArray (
                    __ServerType                              * pServer,
                    __AbstractConstIteratorType const * const * ppIterators,
                    Size                                        iteratorArrayCount
            ) noexcept -> Size {

                /* call the template received member function */
                return ( pServer ->* __removeConstArrayFunction ) (
                        ppIterators,
                        iteratorArrayCount
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ */
