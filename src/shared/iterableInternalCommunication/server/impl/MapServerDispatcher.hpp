/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __KeyType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractIteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __IteratorType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __beginFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __endFunction,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractIteratorType const & >                         __removeFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractIteratorType const * const *, Size >        __removeArrayFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __IteratorType, __KeyType const & >                         __findFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperConstMemberFunction < __ServiceType, __ConstIteratorType, __KeyType const & >               __findConstFunction             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __MapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __find (
                    __ServerType          * pServer,
                    __KeyType       const & key
            ) noexcept -> __AbstractDelegateIterator < __ElementType > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType, __IteratorType > > (
                        ( pServer ->* __findFunction ) ( key )
                );
            }


            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __KeyType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractIteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __IteratorType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __beginFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __endFunction,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractIteratorType const & >                         __removeFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractIteratorType const * const *, Size >        __removeArrayFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __IteratorType, __KeyType const & >                         __findFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperConstMemberFunction < __ServiceType, __ConstIteratorType, __KeyType const & >               __findConstFunction             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __MapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __findConst (
                    __ServerType    const * pServer,
                    __KeyType       const & key
            ) noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                        ( pServer ->* __findConstFunction ) ( key )
                );
            }


            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __KeyType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractIteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __IteratorType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __beginFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __endFunction,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractIteratorType const & >                         __removeFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractIteratorType const * const *, Size >        __removeArrayFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __IteratorType, __KeyType const & >                         __findFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperConstMemberFunction < __ServiceType, __ConstIteratorType, __KeyType const & >               __findConstFunction             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __MapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __findLocal (
                    __ServerType          * pServer,
                    __KeyType       const & key
            ) noexcept -> __IteratorType {

                /* call the template received member function*/
                return ( pServer ->* __findFunction ) ( key );
            }


            template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __KeyType,                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractIteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __IteratorType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __beginFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                          __endFunction,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractIteratorType const & >                         __removeFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: PredicateMemberFunction < __ServiceType, __AbstractConstIteratorType const & >                    __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractIteratorType const * const *, Size >        __removeArrayFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperMemberFunction < __ServiceType, __IteratorType, __KeyType const & >                         __findFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: MapperConstMemberFunction < __ServiceType, __ConstIteratorType, __KeyType const & >               __findConstFunction             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > __CDS_OptimalInline auto __MapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __findConstLocal (
                    __ServerType    const * pServer,
                    __KeyType       const & key
            ) noexcept -> __ConstIteratorType {

                /* call the template received member function*/
                return ( pServer ->* __findConstFunction ) ( key );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__ */
