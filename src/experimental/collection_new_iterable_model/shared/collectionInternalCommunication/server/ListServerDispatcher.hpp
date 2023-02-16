/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_EX_SHARED_LIST_SERVER_DISPATCHER_HPP__
#define __CDS_EX_SHARED_LIST_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../shared/iterableInternalCommunication/server/ListServerDispatcher.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
                > using __ListServerDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListServerDispatcher <
                                __ServerType, __ServiceType, __ElementType,
                                __AbstractIteratorType, __AbstractConstIteratorType,
                                __IteratorType, __ConstIteratorType, __ReverseIteratorType, __ConstReverseIteratorType,
                                __beginFunction, __endFunction,
                                __cbeginFunction, __cendFunction,
                                __rbeginFunction, __rendFunction,
                                __crbeginFunction, __crendFunction,
                                __newAddressFunction, __newFrontFunction, __newBackFunction, __newFrontArrayFunction, __newBackArrayFunction,
                                __newBeforeFunction, __newBeforeConstFunction, __newAfterFunction, __newAfterConstFunction,
                                __newBeforeArrayFunction, __newBeforeArrayConstFunction, __newAfterArrayFunction, __newAfterArrayConstFunction,
                                __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
                        >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_LIST_SERVER_DISPATCHER_HPP__ */
