/*
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_SHARED_LIST_SERVER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_LIST_SERVER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __GenericHandler const __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __routingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __begin ),                  /* __cirt_begin                         - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __end ),                    /* __cirt_end                           - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __rbegin ),                 /* __cirt_rbegin                        - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __rend ),                   /* __cirt_rend                          - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __remove ),                 /* __cirt_remove                        - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConst ),            /* __cirt_removeConst                   - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeArray ),            /* __cirt_removeArray                   - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConstArray ),       /* __cirt_removeConstArray              - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAddress ),             /* __cirt_newAddress                    - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newFront ),               /* __cirt_newFrontAddress               - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBack ),                /* __cirt_newBackAddress                - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newFrontArray ),          /* __cirt_newFrontAddressArray          - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBackArray ),           /* __cirt_newBackAddressArray           - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBefore ),              /* __cirt_newBeforeAddress              - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeConst ),         /* __cirt_newBeforeAddressConst         - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfter ),               /* __cirt_newAfterAddress               - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterConst ),          /* __cirt_newAfterAddressConst          - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeArray ),         /* __cirt_newBeforeAddressArray         - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeArrayConst ),    /* __cirt_newBeforeAddressArrayConst    - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterArray ),          /* __cirt_newAfterAddressArray          - expected part of List     */
                    reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterArrayConst ),     /* __cirt_newAfterAddressArrayConst     - expected part of List     */
                    nullptr,                                                                                /* __cirt_find                          - not expected part of List */
                    nullptr                                                                                 /* __cirt_findConst                     - not expected part of List */
            };


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > typename __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __GenericConstHandler const __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __constRoutingTable [ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
            ] = {
                    reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __cirt_begin                         - expected part of List     */
                    reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __cirt_end                           - expected part of List     */
                    reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __crbegin ),   /* __cirt_rbegin                        - expected part of List     */
                    reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __crend ),     /* __cirt_rend                          - expected part of List     */
                    nullptr,                                                                        /* __cirt_remove                        - not expected part of List */
                    nullptr,                                                                        /* __cirt_removeConst                   - not expected part of List */
                    nullptr,                                                                        /* __cirt_removeArray                   - not expected part of List */
                    nullptr,                                                                        /* __cirt_removeConstArray              - not expected part of List */
                    nullptr,                                                                        /* __cirt_newAddress                    - not expected part of List */
                    nullptr,                                                                        /* __cirt_newFrontAddress               - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBackAddress                - not expected part of List */
                    nullptr,                                                                        /* __cirt_newFrontAddressArray          - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBackAddressArray           - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBeforeAddress              - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBeforeAddressConst         - not expected part of List */
                    nullptr,                                                                        /* __cirt_newAfterAddress               - not expected part of List */
                    nullptr,                                                                        /* __cirt_newAfterAddressConst          - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBeforeAddressArray         - not expected part of List */
                    nullptr,                                                                        /* __cirt_newBeforeAddressArrayConst    - not expected part of List */
                    nullptr,                                                                        /* __cirt_newAfterAddressArray          - not expected part of List */
                    nullptr,                                                                        /* __cirt_newAfterAddressArrayConst     - not expected part of List */
                    nullptr,                                                                        /* __cirt_find                          - not expected part of List */
                    nullptr                                                                         /* __cirt_findConst                     - not expected part of List */
            };


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __ls_handlers () const noexcept -> __GenericHandler const * {

                /* return the first address in the routing table */
                return & __ListServer :: __routingTable [0U];
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __ListServer <
                    __ReceiverType,
                    __ElementType
            > :: __ls_constHandlers () const noexcept -> __GenericConstHandler const * {

                /* return the first address in the const routing table */
                return & __ListServer :: __constRoutingTable [0U];
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_LIST_SERVER_IMPL_HPP__ */
