//
// Created by loghin on 7/3/22.
//

#ifndef __CDS_SHARED_SET_SERVER_HPP__
#define __CDS_SHARED_SET_SERVER_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __SetServer {               // NOLINT(bugprone-reserved-identifier)

                private:
                    using __GenericHandler      = auto ( Collection < __ElementType > :: * ) () -> void; // NOLINT(bugprone-reserved-identifier)

                private:
                    using __GenericConstHandler = auto ( Collection < __ElementType > :: * ) () const -> void;  // NOLINT(bugprone-reserved-identifier)

                private:
                    static __GenericHandler const __routingTable [   // NOLINT(bugprone-reserved-identifier)
                            static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                    ];

                private:
                    static __GenericConstHandler const __constRoutingTable [   // NOLINT(bugprone-reserved-identifier)
                            static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                    ];

                protected:
                    constexpr auto __ss_handlers () const noexcept -> __GenericHandler const *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    constexpr auto __ss_constHandlers () const noexcept -> __GenericConstHandler const *;   // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_SET_SERVER_HPP__
