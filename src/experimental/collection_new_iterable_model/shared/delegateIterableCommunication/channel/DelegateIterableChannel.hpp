//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__

#include "../DelegateIterableRequest.hpp"
#include "../DelegateIterableResponse.hpp"
#include "../../delegateIterator/AbstractDelegateIterator.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename, typename, bool >
                class __DelegateForwardIterableClient;          // NOLINT(bugprone-reserved-identifier)

                template < typename, typename, bool >
                class __DelegateBackwardIterableClient;         // NOLINT(bugprone-reserved-identifier)

                template < typename, typename, bool >
                class __DelegateForwardConstIterableClient;     // NOLINT(bugprone-reserved-identifier)

                template < typename, typename, bool >
                class __DelegateBackwardConstIterableClient;    // NOLINT(bugprone-reserved-identifier)

                template < typename, typename >
                class __AbstractIteratorRemoveClient;           // NOLINT(bugprone-reserved-identifier)

                template < typename, typename >
                class __AbstractConstIteratorRemoveClient;      // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterableChannel :         // NOLINT(bugprone-reserved-identifier)
                        public cds :: Object {              // NOLINT(bugprone-reserved-identifier)

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateForwardIterableClient < __ReceiverType, __ElementType, true >;

                private:
                    friend class __DelegateBackwardIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateBackwardIterableClient < __ReceiverType, __ElementType, true >;

                private:
                    friend class __DelegateForwardConstIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateForwardConstIterableClient < __ReceiverType, __ElementType, true >;

                private:
                    friend class __DelegateBackwardConstIterableClient < __ReceiverType, __ElementType, false >;

                private:
                    friend class __DelegateBackwardConstIterableClient < __ReceiverType, __ElementType, true >;

                private:
                    friend class __AbstractIteratorRemoveClient < __ReceiverType, __ElementType >;

                private:
                    friend class __AbstractConstIteratorRemoveClient < __ReceiverType, __ElementType >;

                protected:
                    __CDS_NoDiscard virtual auto __dich_transmitRequest ( // NOLINT(bugprone-reserved-identifier)
                            __DelegateIterableRequest   const * pRequest,
                            __DelegateIterableResponse        * pResponse
                    ) noexcept -> bool = 0;

                protected:
                    __CDS_NoDiscard virtual auto __dich_transmitConstRequest ( // NOLINT(bugprone-reserved-identifier)
                            __DelegateIterableRequest   const * pRequest,
                            __DelegateIterableResponse        * pResponse
                    ) const noexcept -> bool = 0;

                public:
                    __CDS_cpplang_ConstexprDestructor ~__DelegateIterableChannel () noexcept override;
                };

            }
        }
    }
}

#include "../../delegateIterator/impl/AbstractDelegateIterator.hpp"

#endif // __CDS_SHARED_DELEGATE_ITERABLE_CHANNEL_HPP__
