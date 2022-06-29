//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__

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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertBefore (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertBefore (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->insertBefore (
                            iterator,
                            std :: move ( element )
                    );
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAfter (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAfter (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->insertAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBefore (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept (false) -> ElementReference {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBeforeAddressConst,
                            reinterpret_cast < void const * > ( & iterator )
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceAfter (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept (false) -> ElementReference {

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newAfterAddressConst,
                            reinterpret_cast < void const * > ( & iterator )
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllBefore (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept (false) -> void {

                    __CollectionInternalRequestMultipleIteratorRelative const parameters {
                            sizeof ... ( __ArgumentTypes ),
                            reinterpret_cast < void const * > ( & iterator )
                    };

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst,
                            & parameters
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameters._count );
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllAfter (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept (false) -> void {

                    __CollectionInternalRequestMultipleIteratorRelative const parameters {
                            sizeof ... ( __ArgumentTypes ),
                            reinterpret_cast < void const * > ( & iterator )
                    };

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst,
                            & parameters
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameters._count );
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept (false) -> void {

                    this->insertAllOfBefore (
                            iterator,
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfBefore (
                        AbstractConstIterator                           const & iterator,
                        std :: initializer_list < __ElementType >       const & list
                ) noexcept (false) -> void {

                    this->insertAllOfBefore (
                            iterator,
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept (false) -> void {

                    this->insertAllOfAfter (
                            iterator,
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfAfter (
                        AbstractConstIterator                           const & iterator,
                        std :: initializer_list < __ElementType >       const & list
                ) noexcept (false) -> void {

                    this->insertAllOfAfter (
                            iterator,
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept (false) -> void {

                    __CollectionInternalRequestMultipleIteratorRelative const parameters {
                            __IteratorDistance < __IteratorType > :: __compute ( begin, end ),
                            reinterpret_cast < void const * > ( & iterator )
                    };

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst,
                            & parameters
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameters._count );
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
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( pElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept (false) -> void {

                    __CollectionInternalRequestMultipleIteratorRelative const parameters {
                            __IteratorDistance < __IteratorType > :: __compute ( begin, end ),
                            reinterpret_cast < void const * > ( & iterator )
                    };

                    __CollectionInternalRequest const request {
                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst,
                            & parameters
                    };

                    auto pElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameters._count );
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
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( pElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pElements );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__
