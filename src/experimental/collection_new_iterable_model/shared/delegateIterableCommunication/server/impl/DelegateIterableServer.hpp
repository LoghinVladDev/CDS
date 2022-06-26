//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType, // NOLINT(bugprone-reserved-identifier)
                        bool     __forward,             // NOLINT(bugprone-reserved-identifier)
                        bool     __backward             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __DelegateIterableServer <
                        __ReceiverType,
                        __ElementType,
                        __WrappedIteratorType,
                        __forward,
                        __backward
                > :: __dis_handleRequest (
                        __DelegateIteratorRequestType requestType
                ) noexcept -> __AbstractDelegateIterator < __ElementType > * {

                    switch ( requestType ) {
                        case __DelegateIteratorRequestType :: __dirt_begin:     return this->__difr_begin();
                        case __DelegateIteratorRequestType :: __dirt_end:       return this->__difr_end();
                        case __DelegateIteratorRequestType :: __dirt_rbegin:    return this->__dibr_begin();
                        case __DelegateIteratorRequestType :: __dirt_rend:      return this->__dibr_end();
                        default:                                                return nullptr;
                    }
                }

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERABLE_SERVER_IMPL_HPP__
