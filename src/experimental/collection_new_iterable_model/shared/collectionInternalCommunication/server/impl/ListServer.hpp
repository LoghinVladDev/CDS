//
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_LIST_SERVER_IMPL_HPP__
#define __CDS_SHARED_LIST_SERVER_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > typename __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericHandler const __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __routingTable [ // NOLINT(bugprone-reserved-identifier)
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __begin ),                  /* __cirt_begin */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __end ),                    /* __cirt_end */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __rbegin ),                 /* __cirt_rbegin */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __rend ),                   /* __cirt_rend */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __remove ),                 /* __cirt_remove */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConst ),            /* __cirt_removeConst */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAddress ),             /* __cirt_newAddress */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newFront ),               /* __cirt_newFrontAddress */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBack ),                /* __cirt_newBackAddress */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newFrontArray ),          /* __cirt_newFrontAddressArray */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBackArray ),           /* __cirt_newBackAddressArray */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBefore ),              /* __cirt_newBeforeAddress */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeConst ),         /* __cirt_newBeforeAddressConst */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfter ),               /* __cirt_newAfterAddress */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterConst ),          /* __cirt_newAfterAddressConst */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeArray ),         /* __cirt_newBeforeAddressArray */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newBeforeArrayConst ),    /* __cirt_newBeforeAddressArrayConst */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterArray ),          /* __cirt_newAfterAddressArray */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAfterArrayConst ),     /* __cirt_newAfterAddressArrayConst */
                        nullptr,                                                                                /* __cirt_find */
                        nullptr                                                                                 /* __cirt_findConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > typename __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericConstHandler const __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __constRoutingTable [ // NOLINT(bugprone-reserved-identifier)
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __cirt_begin */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __cirt_end */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __crbegin ),   /* __cirt_rbegin */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __crend ),     /* __cirt_rend */
                        nullptr,                                                                        /* __cirt_remove */
                        nullptr,                                                                        /* __cirt_removeConst */
                        nullptr,                                                                        /* __cirt_newAddress */
                        nullptr,                                                                        /* __cirt_newFrontAddress */
                        nullptr,                                                                        /* __cirt_newBackAddress */
                        nullptr,                                                                        /* __cirt_newFrontAddressArray */
                        nullptr,                                                                        /* __cirt_newBackAddressArray */
                        nullptr,                                                                        /* __cirt_newBeforeAddress */
                        nullptr,                                                                        /* __cirt_newBeforeAddressConst */
                        nullptr,                                                                        /* __cirt_newAfterAddress */
                        nullptr,                                                                        /* __cirt_newAfterAddressConst */
                        nullptr,                                                                        /* __cirt_newBeforeAddressArray */
                        nullptr,                                                                        /* __cirt_newBeforeAddressArrayConst */
                        nullptr,                                                                        /* __cirt_newAfterAddressArray */
                        nullptr,                                                                        /* __cirt_newAfterAddressArrayConst */
                        nullptr,                                                                        /* __cirt_find */
                        nullptr                                                                         /* __cirt_findConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __ls_handlers () const noexcept -> __GenericHandler const * {

                    return & __ListServer :: __routingTable [0U];
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __ls_constHandlers () const noexcept -> __GenericConstHandler const * {

                    return & __ListServer :: __constRoutingTable [0U];
                }

            }
        }
    }
}

#endif // __CDS_SHARED_LIST_SERVER_IMPL_HPP__
