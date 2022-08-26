/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceFront ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceFront ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceBack ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceFront ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceFront ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceBack ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceFront (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                    using __ReceiverNewFrontHandlerType = __ElementType * ( __ReceiverType :: * ) ();
                    auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                    return * new (
                            (
                                    pReceiver ->* reinterpret_cast < __ReceiverNewFrontHandlerType > (
                                            pReceiver->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newFrontAddress
                                            )
                                    )
                            ) ()
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBack (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                    using __ReceiverNewBackHandlerType  = __ElementType * ( __ReceiverType :: * ) ();
                    auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                    return * new (
                            (
                                    pReceiver ->* reinterpret_cast < __ReceiverNewBackHandlerType > (
                                            pReceiver->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBackAddress
                                            )
                                    )
                            ) ()
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAll (
                        __ArgumentTypes && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                    using __ReceiverNewFrontArrayHandlerType    = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                    auto    const pReceiver                     = reinterpret_cast < __ReceiverType * > ( this );
                    Size    const parameterCount                = sizeof ... ( __ArgumentTypes );
                    auto          ppElements                    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            pReceiver ->* reinterpret_cast < __ReceiverNewFrontArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAll (
                        __ArgumentTypes && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                    using __ReceiverNewBackArrayHandlerType = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                    auto    const pReceiver                 = reinterpret_cast < __ReceiverType * > ( this );
                    Size    const parameterCount            = sizeof ... ( __ArgumentTypes );
                    auto          ppElements                = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            pReceiver ->* reinterpret_cast < __ReceiverNewBackArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IterableType const & iterable
                ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                    this->pushFrontAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void {

                    this->pushFrontAllOf (
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IterableType const & iterable
                ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                    this->pushBackAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void {

                    this->pushBackAllOf (
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count
                ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void {

                    using __ReceiverNewFrontArrayHandlerType    = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                    auto    const pReceiver                     = reinterpret_cast < __ReceiverType * > ( this );
                    Size    const parameterCount                = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto          ppElements                    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            pReceiver ->* reinterpret_cast < __ReceiverNewFrontArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __BoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count
                ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void {

                    using __ReceiverNewBackArrayHandlerType = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                    auto    const pReceiver                 = reinterpret_cast < __ReceiverType * > ( this );
                    Size    const parameterCount            = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto          ppElements                = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            pReceiver ->* reinterpret_cast < __ReceiverNewBackArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
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
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceFront ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFront (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceFront ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceBack ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBack (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceFront ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: prepend (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceFront ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference {

                    return this->emplaceBack ( element );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType       /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: append (
                        ElementType && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference {

                    return this->emplaceBack ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceFront (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                    return * new ( reinterpret_cast < __ReceiverType * > ( this )->__newFront () ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBack (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                    return * new ( reinterpret_cast < __ReceiverType * > ( this )->__newBack () ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAll (
                        __ArgumentTypes && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    reinterpret_cast < __ReceiverType * > ( this )->__newFrontArray (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAll (
                        __ArgumentTypes && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                    Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    reinterpret_cast < __ReceiverType * > ( this )->__newBackArray (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IterableType const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                    this->pushFrontAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> void {

                    this->pushFrontAllOf (
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IterableType const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                    this->pushBackAllOf (
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> void {

                    this->pushBackAllOf (
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushFrontAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> void {

                    Size    const parameterCount    = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto          ppElements        = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    reinterpret_cast < __ReceiverType * > ( this )->__newFrontArray (
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
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalBoundaryInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: pushBackAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end,
                        Size                   count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> void {

                    Size    const parameterCount    = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto          ppElements        = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    reinterpret_cast < __ReceiverType * > ( this )->__newBackArray (
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

#endif /* __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ */
