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
                > void ( Collection < __ElementType > :: * const __ListServer < __ReceiverType, __ElementType > :: __routingTable [0x13U] ) () = { // NOLINT(bugprone-reserved-identifier)
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __begin ),         /* __cirt_begin */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __end ),           /* __cirt_end */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __rbegin ),        /* __cirt_rbegin */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __rend ),          /* __cirt_rend */
                        nullptr, /* __cirt_remove */
                        nullptr, /* __cirt_removeConst */
                        nullptr, /* __cirt_newAddress */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __newFront ),      /* __cirt_newFrontAddress */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __newBack ),       /* __cirt_newBackAddress */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __newFrontArray ), /* __cirt_newFrontAddressArray */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () > ( & __ReceiverType :: __newBackArray ),  /* __cirt_newBackAddressArray */
                        nullptr, /* __cirt_newBeforeAddress */
                        nullptr, /* __cirt_newBeforeAddressConst */
                        nullptr, /* __cirt_newAfterAddress */
                        nullptr, /* __cirt_newAfterAddressConst */
                        nullptr, /* __cirt_newBeforeAddressArray */
                        nullptr, /* __cirt_newBeforeAddressArrayConst */
                        nullptr, /* __cirt_newAfterAddressArray */
                        nullptr  /* __cirt_newAfterAddressArrayConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > void ( Collection < __ElementType > :: * const __ListServer < __ReceiverType, __ElementType > :: __constRoutingTable [0x13U] ) () const = { // NOLINT(bugprone-reserved-identifier)
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () const > ( & __ReceiverType :: __cbegin ),          /* __cirt_begin */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () const > ( & __ReceiverType :: __cend ),            /* __cirt_end */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () const > ( & __ReceiverType :: __crbegin ),         /* __cirt_rbegin */
                        reinterpret_cast < void ( Collection < __ElementType > :: * ) () const > ( & __ReceiverType :: __crend ),           /* __cirt_rend */
                        nullptr, /* __cirt_remove */
                        nullptr, /* __cirt_removeConst */
                        nullptr, /* __cirt_newAddress */
                        nullptr, /* __cirt_newFrontAddress */
                        nullptr, /* __cirt_newBackAddress */
                        nullptr, /* __cirt_newFrontAddressArray */
                        nullptr, /* __cirt_newBackAddressArray */
                        nullptr, /* __cirt_newBeforeAddress */
                        nullptr, /* __cirt_newBeforeAddressConst */
                        nullptr, /* __cirt_newAfterAddress */
                        nullptr, /* __cirt_newAfterAddressConst */
                        nullptr, /* __cirt_newBeforeAddressArray */
                        nullptr, /* __cirt_newBeforeAddressArrayConst */
                        nullptr, /* __cirt_newAfterAddressArray */
                        nullptr  /* __cirt_newAfterAddressArrayConst */
                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __ls_handlers () const noexcept -> void ( Collection < __ElementType > :: * const * ) () {

                    return & __ListServer :: __routingTable [0U];
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __ListServer <
                        __ReceiverType,
                        __ElementType
                > :: __ls_constHandlers () const noexcept -> void ( Collection < __ElementType > :: * const * ) () const {

                    return & __ListServer :: __constRoutingTable [0U];
                }

            }
        }
    }
}

#endif // __CDS_SHARED_LIST_SERVER_IMPL_HPP__
