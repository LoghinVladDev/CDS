/* NOLINT(llvm-header-guard)
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__   /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __IterableServer <       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    __ReceiverType,
                    __ElementType
            > :: __GenericHandler const __IterableServer <
                    __ReceiverType,
                    __ElementType
            > :: __routingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {
                            nullptr,                                                                            /* __iirt_begin                         - not expected part of Iterable        */
                            nullptr,                                                                            /* __iirt_end                           - not expected part of Iterable        */
                            nullptr,                                                                            /* __iirt_rbegin                        - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_rend                          - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_remove                        - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_removeConst                   - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_removeArray                   - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_removeConstArray              - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newAddress                    - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newFrontAddress               - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBackAddress                - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newFrontAddressArray          - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBackAddressArray           - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBeforeAddress              - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBeforeAddressConst         - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newAfterAddress               - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newAfterAddressConst          - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBeforeAddressArray         - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newBeforeAddressArrayConst    - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newAfterAddressArray          - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_newAfterAddressArrayConst     - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_find                          - not expected part of Iterable    */
                            nullptr,                                                                            /* __iirt_findConst                     - not expected part of Iterable    */
                    };


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __IterableServer <       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    __ReceiverType,
                    __ElementType
            > :: __GenericConstHandler const __IterableServer <
                    __ReceiverType,
                    __ElementType
            > :: __constRoutingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-c-arrays) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {
                            reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __iirt_begin                         - expected part of Iterable        */ /* NOLINT(*-reinterpret-cast) */
                            reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __iirt_end                           - expected part of Iterable        */ /* NOLINT(*-reinterpret-cast) */
                            nullptr,                                                                        /* __iirt_rbegin                        - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_rend                          - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_remove                        - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_removeConst                   - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_removeArray                   - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_removeConstArray              - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newAddress                    - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newFrontAddress               - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBackAddress                - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newFrontAddressArray          - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBackAddressArray           - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBeforeAddress              - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBeforeAddressConst         - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newAfterAddress               - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newAfterAddressConst          - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBeforeAddressArray         - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newBeforeAddressArrayConst    - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newAfterAddressArray          - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_newAfterAddressArrayConst     - not expected part of Iterable    */
                            nullptr,                                                                        /* __iirt_find                          - not expected part of Iterable    */
                            nullptr                                                                         /* __iirt_findConst                     - not expected part of Iterable    */
                    };


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __IterableServer <
                    __ReceiverType,
                    __ElementType
            > :: __is_handlers () const noexcept -> __GenericHandler const * {

                /* return the first address in the routing table */
                return & __IterableServer :: __routingTable [0U];
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __IterableServer <
                    __ReceiverType,
                    __ElementType
            > :: __is_constHandlers () const noexcept -> __GenericConstHandler const * {

                /* return the first address in the const routing table */
                return & __IterableServer :: __constRoutingTable [0U];
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERABLE_SERVER_IMPL_HPP__ */