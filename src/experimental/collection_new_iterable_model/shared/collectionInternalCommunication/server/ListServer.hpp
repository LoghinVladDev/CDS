//
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_LIST_SERVER_HPP__
#define __CDS_SHARED_LIST_SERVER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __ListServer {              // NOLINT(bugprone-reserved-identifier)

                private:
                    constexpr static void ( Collection < __ElementType > :: * const __routingTable [0x13U] ) () = { // NOLINT(bugprone-reserved-identifier)
                            nullptr, /* __cirt_begin */
                            nullptr, /* __cirt_end */
                            nullptr, /* __cirt_rbegin */
                            nullptr, /* __cirt_rend */
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

                private:
                    constexpr static void ( Collection < __ElementType > :: * const __constRoutingTable [0x13U] ) () const = { // NOLINT(bugprone-reserved-identifier)
                            nullptr, /* __cirt_begin */
                            nullptr, /* __cirt_end */
                            nullptr, /* __cirt_rbegin */
                            nullptr, /* __cirt_rend */
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

                protected:
                    constexpr auto __ls_handlers () const noexcept -> void ( Collection < __ElementType > :: * const * ) ();               // NOLINT(bugprone-reserved-identifier)

                protected:
                    constexpr auto __ls_constHandlers () const noexcept -> void ( Collection < __ElementType > :: * const * ) () const;    // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_LIST_SERVER_HPP__
