/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "CollectionServerDispatcher.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __begin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    /* call the template received member function and wrap iterator in a new delegate */
                    return Memory :: instance().create < __DelegateIterator < __ElementType, __IteratorType > > (
                            ( reinterpret_cast < __ServerType * > ( this ) ->* __beginFunction ) ()
                    );
                }


                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __end () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    /* call the template received member function and wrap iterator in a new delegate */
                    return Memory :: instance().create < __DelegateIterator < __ElementType, __IteratorType > > (
                            ( reinterpret_cast < __ServerType * > ( this ) ->* __endFunction ) ()
                    );
                }


                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __beginLocal () noexcept -> __IteratorType {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __beginFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __endLocal () noexcept -> __IteratorType {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __endFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __remove (
                        __AbstractIteratorType const * pIterator
                ) noexcept -> bool {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __removeFunction ) (
                            * pIterator
                    );
                }


                template <
                        typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __MutableCollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
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
                        __removeConstArrayFunction
                > :: __removeArray (
                        __AbstractIteratorType  const * const * ppIterators,
                        Size                                    iteratorArrayCount
                ) noexcept -> Size {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __removeArrayFunction ) (
                            ppIterators,
                            iteratorArrayCount
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ */
