/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType  /* NOLINT(bugprone-reserved-identifier) */
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
                    __KeyType const & key
            ) noexcept -> __AbstractDelegateIterator < __ElementType > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType, __IteratorType > > (
                        ( reinterpret_cast < __ServerType * > ( this ) ->* __findFunction ) ( key )
                );
            }


            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType  /* NOLINT(bugprone-reserved-identifier) */
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
                    __KeyType const & key
            ) const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                        ( reinterpret_cast < __ServerType const * > ( this ) ->* __findConstFunction ) ( key )
                );
            }


            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType  /* NOLINT(bugprone-reserved-identifier) */
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
                    __KeyType const & key
            ) noexcept -> __IteratorType {

                /* call the template received member function*/
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __findFunction ) ( key );
            }


            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType  /* NOLINT(bugprone-reserved-identifier) */
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
                    __KeyType const & key
            ) const noexcept -> __ConstIteratorType {

                /* call the template received member function*/
                return ( reinterpret_cast < __ServerType const * > ( this ) ->* __findConstFunction ) ( key );
            }

        }
    }
}

#endif /* __CDS_SHARED_MAP_SERVER_DISPATCHER_IMPL_HPP__ */
