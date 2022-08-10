//
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_MAP_SERVER_IMPL_HPP__
#define __CDS_SHARED_MAP_SERVER_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > typename __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericHandler const __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __routingTable [ // NOLINT(bugprone-reserved-identifier)
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __begin ),          /* __cirt_begin */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __end ),            /* __cirt_end */
                        nullptr,                                                                        /* __cirt_rbegin */
                        nullptr,                                                                        /* __cirt_rend */
                        nullptr,                                                                        /* __cirt_remove */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __removeConst ),    /* __cirt_removeConst */
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __newAddress ),     /* __cirt_newAddress */
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
                        reinterpret_cast < __GenericHandler > ( & __ReceiverType :: __find ),           /* __cirt_find */
                        nullptr,                                                                        /* __cirt_findConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > typename __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __GenericConstHandler const __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __constRoutingTable [ // NOLINT(bugprone-reserved-identifier)
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ] = {
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cbegin ),    /* __cirt_begin */
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __cend ),      /* __cirt_end */
                        nullptr,                                                                        /* __cirt_rbegin */
                        nullptr,                                                                        /* __cirt_rend */
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
                        reinterpret_cast < __GenericConstHandler > ( & __ReceiverType :: __findConst )  /* __cirt_findConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __ms_handlers () const noexcept -> __GenericHandler const * {

                    return & __MapServer :: __routingTable [0U];
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __MapServer <
                        __ReceiverType,
                        __ElementType
                > :: __ms_constHandlers () const noexcept -> __GenericConstHandler const * {

                    return & __MapServer :: __constRoutingTable [0U];
                }

            }
        }
    }
}

#endif // __CDS_SHARED_MAP_SERVER_IMPL_HPP__
