//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_IMPL_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_IMPL_HPP__

#include "../../../iterator/IteratorDistance.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceFront ( element );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceFront ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBack ( element );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceFront (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newFrontAddress,
                            nullptr
                    };

                    __CollectionInternalRequestResponse response {
                            false,
                            nullptr
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    return * new ( response._pData ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBack (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBackAddress,
                            nullptr
                    };

                    __CollectionInternalRequestResponse response {
                            false,
                            nullptr
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    return * new ( response._pData ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size                        const parameterCount = sizeof ... ( __ArgumentTypes );
                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newFrontAddressArray,
                            & parameterCount
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );
                    __CollectionInternalRequestResponse response {
                            false,
                            reinterpret_cast < void * > ( pElements )
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            pElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size                        const parameterCount = sizeof ... ( __ArgumentTypes );
                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBackAddressArray,
                            & parameterCount
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );
                    __CollectionInternalRequestResponse response {
                            false,
                            reinterpret_cast < void * > ( pElements )
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            pElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IterableType const & iterable
                ) noexcept (false) -> void {

                    this->pushFrontAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->pushFrontAllOf (
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IterableType const & iterable
                ) noexcept (false) -> void {

                    this->pushBackAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->pushBackAllOf (
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    Size const parameterCount = __IteratorDistance < __IteratorType > :: __compute (
                            begin,
                            end
                    );

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newFrontAddressArray,
                            & parameterCount
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );
                    __CollectionInternalRequestResponse response {
                            false,
                            reinterpret_cast < void * > ( pElements )
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( pElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    Size const parameterCount = __IteratorDistance < __IteratorType > :: __compute (
                            begin,
                            end
                    );

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBackAddressArray,
                            & parameterCount
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );
                    __CollectionInternalRequestResponse response {
                            false,
                            reinterpret_cast < void * > ( pElements )
                    };

                    auto const requestAvailabilityStatus = static_cast < __ReceiverType * > ( this )->__cicch_transmitRequest (
                            & request,
                            & response
                    );

                    if ( ! requestAvailabilityStatus || ! response._status ) {
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                        throw RuntimeException ( "Unexpected error in BoundaryInsertionClient :: pushFront" );
                    }

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( pElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_BOUNDARY_INSERTION_CLIENT_IMPL_HPP__
