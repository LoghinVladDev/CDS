//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__

#include "../../../../iterator/IteratorDistance.hpp"

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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > auto __BoundaryInsertionPrimitiveClient <
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
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
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
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
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
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
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
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceFront (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast < __ElementType * ( __ReceiverType :: * ) () > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newFrontAddress
                                            )
                                    )
                            ) ()
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBack (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast < __ElementType * ( __ReceiverType :: * ) () > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBackAddress
                                            )
                                    )
                            ) ()
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newFrontAddressArray
                                    )
                            )
                    ) (
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBackAddressArray
                                    )
                            )
                    ) (
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
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
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {


                    Size    const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newFrontAddressArray
                                    )
                            )
                    ) (
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {


                    Size    const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBackAddressArray
                                    )
                            )
                    ) (
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceFront (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new ( static_cast < __ReceiverType * > ( this )->__newFront () ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBack (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new ( static_cast < __ReceiverType * > ( this )->__newBack () ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newFrontArray (
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBackArray (
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
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
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {


                    Size    const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newFrontArray (
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {


                    Size    const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBackArray (
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
