/* NOLINT(llvm-header-guard)
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_IMPL_HPP__   /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_IMPL_HPP__   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#ifdef _MSC_VER

#include "../../../impl/forceFunctionPointerCast.hpp"

#endif

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __MutableCollectionServer <  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    __ReceiverType,
                    __ElementType
            > :: __GenericHandler const __MutableCollectionServer <
                    __ReceiverType,
                    __ElementType
            > :: __routingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {

#ifdef _MSC_VER

                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __begin ),
                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __end ),

#else

                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __begin ),              /* __cirt_begin                         - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __end ),                /* __cirt_end                           - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */

#endif

                            nullptr,                                                                            /* __cirt_rbegin                        - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_rend                          - not expected part of MutableCollection    */

#ifdef _MSC_VER

                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __remove ),
                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __removeConst ),
                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __removeArray ),
                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __removeConstArray ),
                            __forceFunctionPointerCast < __GenericHandler > ( & __ReceiverType :: __newAddress ),

#else

                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __remove ),             /* __cirt_remove                        - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConst ),        /* __cirt_removeConst                   - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeArray ),        /* __cirt_removeArray                   - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConstArray ),   /* __cirt_removeConstArray              - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAddress ),         /* __cirt_newAddress                    - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */

#endif

                            nullptr,                                                                            /* __cirt_newFrontAddress               - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBackAddress                - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newFrontAddressArray          - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBackAddressArray           - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBeforeAddress              - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBeforeAddressConst         - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newAfterAddress               - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newAfterAddressConst          - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBeforeAddressArray         - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newBeforeAddressArrayConst    - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newAfterAddressArray          - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_newAfterAddressArrayConst     - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_find                          - not expected part of MutableCollection    */
                            nullptr,                                                                            /* __cirt_findConst                     - not expected part of MutableCollection    */
                    };


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __MutableCollectionServer <  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    __ReceiverType,
                    __ElementType
            > :: __GenericConstHandler const __MutableCollectionServer <
                    __ReceiverType,
                    __ElementType
            > :: __constRoutingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {

#ifdef _MSC_VER

                            __forceFunctionPointerCast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),
                            __forceFunctionPointerCast < __GenericConstHandler > ( & __ReceiverType :: __cend ),

#else

                            reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __cirt_begin                         - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __cirt_end                           - expected part of MutableCollection        */  /* NOLINT(*-reinterpret-cast) */

#endif

                            nullptr,                                                                        /* __cirt_rbegin                        - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_rend                          - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_remove                        - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_removeConst                   - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_removeArray                   - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_removeConstArray              - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newAddress                    - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newFrontAddress               - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBackAddress                - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newFrontAddressArray          - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBackAddressArray           - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBeforeAddress              - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBeforeAddressConst         - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newAfterAddress               - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newAfterAddressConst          - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBeforeAddressArray         - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newBeforeAddressArrayConst    - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newAfterAddressArray          - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_newAfterAddressArrayConst     - not expected part of MutableCollection    */
                            nullptr,                                                                        /* __cirt_find                          - not expected part of MutableCollection    */
                            nullptr                                                                         /* __cirt_findConst                     - not expected part of MutableCollection    */
                    };


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __MutableCollectionServer <
                    __ReceiverType,
                    __ElementType
            > :: __mcs_handlers () const noexcept -> __GenericHandler const * {

                /* return the first address in the routing table */
                return & __MutableCollectionServer :: __routingTable [0U];
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __MutableCollectionServer <
                    __ReceiverType,
                    __ElementType
            > :: __mcs_constHandlers () const noexcept -> __GenericConstHandler const * {

                /* return the first address in the const routing table */
                return & __MutableCollectionServer :: __constRoutingTable [0U];
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_MUTABLE_COLLECTION_SERVER_IMPL_HPP__ */