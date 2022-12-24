/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__
#define __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../shared/iterableInternalCommunication/server/MutableCollectionServerDispatcher.hpp"

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
                > using __MutableCollectionServerDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =                                                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionServerDispatcher <
                                __ServerType, __ServiceType, __ElementType,
                                __AbstractIteratorType, __AbstractConstIteratorType, __IteratorType, __ConstIteratorType,
                                __beginFunction, __endFunction, __cbeginFunction, __cendFunction,
                                __newAddressFunction,
                                __removeFunction, __removeConstFunction, __removeArrayFunction, __removeConstArrayFunction
                        >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ */
