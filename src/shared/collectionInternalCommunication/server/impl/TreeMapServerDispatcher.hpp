//
// Created by stefan on 10.10.2022.
//

#ifndef __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__  /* NOLINT(bugprone-reserved-identifier) */

#include "MapServerDispatcher.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ServerType,                                                                                                                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseConstIteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )            ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )              ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )           ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )             ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType              /* NOLINT(bugprone-reserved-identifier) */
            > auto __TreeMapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ReverseConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __rbeginLocal () -> __ReverseIteratorType {

                return ( reinterpret_cast < __ServerType * > ( this ) ->* __rbeginFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseConstIteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )            ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )              ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )           ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )             ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType              /* NOLINT(bugprone-reserved-identifier) */
            > auto __TreeMapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ReverseConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __rendLocal () -> __ReverseIteratorType {

                return ( reinterpret_cast < __ServerType * > ( this ) ->* __rendFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseConstIteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )            ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )              ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )           ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )             ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType              /* NOLINT(bugprone-reserved-identifier) */
            > auto __TreeMapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ReverseConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __crbeginLocal () const -> __ReverseConstIteratorType {

                return ( reinterpret_cast < __ServerType const * > ( this ) ->* __crbeginFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                      /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseConstIteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )            ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )              ()                                                              -> __ReverseIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )           ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )             ()                                                      const   -> __ReverseConstIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,                 /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                            /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType              /* NOLINT(bugprone-reserved-identifier) */
            > auto __TreeMapServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __KeyType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ReverseConstIteratorType,
                    __beginFunction,
                    __endFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction,
                    __findFunction,
                    __findConstFunction
            > :: __crendLocal () const -> __ReverseConstIteratorType {

                return ( reinterpret_cast < __ServerType const * > ( this ) ->* __crendFunction ) ();
            }
        }
    }
}

#endif //__CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_IMPL_HPP__
