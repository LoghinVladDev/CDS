/*
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_SHARED_SET_SERVER_IMPL_HPP__
#define __CDS_SHARED_SET_SERVER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > typename __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericHandler const __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __routingTable [ /* NOLINT(bugprone-reserved-identifier) */
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        nullptr,                                                                            /* __cirt_begin                         - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_end                           - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_rbegin                        - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_rend                          - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_remove                        - not expected part of Set  */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConst ),        /* __cirt_removeConst                   - expected part of Set      */
                        nullptr,                                                                            /* __cirt_removeArray                   - not expected part of Set  */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConstArray ),   /* __cirt_removeConstArray              - expected part of Set      */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAddress ),         /* __cirt_newAddress                    - expected part of Set      */
                        nullptr,                                                                            /* __cirt_newFrontAddress               - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBackAddress                - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newFrontAddressArray          - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBackAddressArray           - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBeforeAddress              - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBeforeAddressConst         - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newAfterAddress               - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newAfterAddressConst          - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBeforeAddressArray         - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newBeforeAddressArrayConst    - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newAfterAddressArray          - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_newAfterAddressArrayConst     - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_find                          - not expected part of Set  */
                        nullptr,                                                                            /* __cirt_findConst                     - not expected part of Set  */
                };


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > typename __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericConstHandler const __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __constRoutingTable [ /* NOLINT(bugprone-reserved-identifier) */
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __cirt_begin                         - expected part of Set      */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __cirt_end                           - expected part of Set      */
                        nullptr,                                                                        /* __cirt_rbegin                        - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_rend                          - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_remove                        - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_removeConst                   - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_removeArray                   - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_removeConstArray              - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newAddress                    - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newFrontAddress               - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBackAddress                - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newFrontAddressArray          - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBackAddressArray           - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBeforeAddress              - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBeforeAddressConst         - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newAfterAddress               - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newAfterAddressConst          - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBeforeAddressArray         - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newBeforeAddressArrayConst    - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newAfterAddressArray          - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_newAfterAddressArrayConst     - not expected part of Set  */
                        nullptr,                                                                        /* __cirt_find                          - not expected part of Set  */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __findConst )  /* __cirt_findConst                     - expected part of Set      */
                };


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __ss_handlers () const noexcept -> __GenericHandler const * {

                    /* return the first address in the routing table */
                    return & __SetServer :: __routingTable [0U];
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __SetServer <
                        __ReceiverType,
                        __ElementType
                > :: __ss_constHandlers () const noexcept -> __GenericConstHandler const * {

                    /* return the first address in the const routing table */
                    return & __SetServer :: __constRoutingTable [0U];
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_SET_SERVER_IMPL_HPP__ */
