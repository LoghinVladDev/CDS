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
                > constexpr void ( Collection < __ElementType > :: * const __ListServer < __ReceiverType, __ElementType > :: __routingTable [0x13U] ) ();


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > constexpr void ( Collection < __ElementType > :: * const __ListServer < __ReceiverType, __ElementType > :: __constRoutingTable [0x13U] ) () const;


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
