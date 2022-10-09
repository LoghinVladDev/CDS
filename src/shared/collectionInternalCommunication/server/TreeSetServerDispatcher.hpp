/*
 * Created by stefan on 29.08.2022.
 */

#ifndef __CDS_SHARED_TREE_SET_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_TREE_SET_SERVER_DISPATCHER_HPP__   /* NOLINT(bugprone-reserved-identifier) */

#include "SetServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ServerType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseConstIteratorType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                    const -> __ConstIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                    const -> __ConstIteratorType,           /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )           ()                                                    const -> __ReverseConstIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )             ()                                                    const -> __ReverseConstIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                           -> __ElementType *,               /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                     -> bool,                          /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )       -> Size,                          /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __ElementType const & )                             const -> __ConstIteratorType            /* NOLINT(bugprone-reserved-identifier) */
            > class __TreeSetServerDispatcher :     /* NOLINT(bugprone-reserved-identifier) */
                    public __SetServerDispatcher <
                            __ServerType,
                            __ServiceType,
                            __ElementType,
                            __AbstractConstIteratorType,
                            __ConstIteratorType,
                            __cbeginFunction,
                            __cendFunction,
                            __newAddressFunction,
                            __removeConstFunction,
                            __removeConstArrayFunction,
                            __findConstFunction
                    > {

                    protected:
                        auto __crbeginLocal () const noexcept -> __ReverseConstIteratorType;        /* NOLINT(bugprone-reserved-identifier) */

                    protected:
                        auto __crendLocal () const noexcept -> __ReverseConstIteratorType;          /* NOLINT(bugprone-reserved-identifier) */

                    };
        }
    }
}

#endif /* __CDS_SHARED_TREE_SET_SERVER_DISPATCHER_HPP__ */
