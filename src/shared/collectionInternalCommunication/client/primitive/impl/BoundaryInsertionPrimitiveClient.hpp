/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the copy constructor via front emplacement */
                return this->emplaceFront ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the move constructor via front emplacement */
                return this->emplaceFront ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the copy constructor via back emplacement */
                return this->emplaceBack ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the move constructor via back emplacement */
                return this->emplaceBack ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceFront ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceFront ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceBack ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceBack ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplaceFront (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                /* Handle type of the new front address function */
                using __ReceiverNewFrontHandlerType = __ElementType * ( __ReceiverType :: * ) ();
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                /* Create the request for a new front address handler, call it and pass the received address, and
                 * forward the received parameters to the emplacement new operator */
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
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplaceBack (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                /* Handle type of the new back address function */
                using __ReceiverNewBackHandlerType  = __ElementType * ( __ReceiverType :: * ) ();
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                /* Create the request for a new back address handler, call it and pass the received address, and
                 * forward the received parameters to the emplacement new operator */
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
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAll (
                    __ArgumentTypes && ... values
            ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                /* Handle type of the new front address function */
                using __ReceiverNewFrontArrayHandlerType    = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto    const pReceiver                     = reinterpret_cast < __ReceiverType * > ( this );
                /* The number of received values is the numbers of elements to be created */
                Size    const parameterCount                = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements                    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new front address array with the created buffer */
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

                /* Forward initialization values to construct each received address with them */
                cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                        ppElements,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAll (
                    __ArgumentTypes && ... values
            ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                /* Handle type of the new back address function */
                using __ReceiverNewBackArrayHandlerType = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto    const pReceiver                 = reinterpret_cast < __ReceiverType * > ( this );
                /* The number of received values is the numbers of elements to be created */
                Size    const parameterCount            = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements                = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new back address array with the created buffer */
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

                /* Forward initialization values to construct each received address with them */
                cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                        ppElements,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant with RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size */
                this->pushFrontAllOf (
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant without RandomAccessIterator - 'operator -'. Call pushFrontAllOf without size, letting
                 * the function compute the distance between start and end */
                this->pushFrontAllOf (
                        iterable.begin(),
                        iterable.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size */
                this->pushFrontAllOf (
                        list.begin(),
                        list.end(),
                        list.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant with RandomAccessIterator - 'operator -'. Call pushBackAllOf with size */
                this->pushBackAllOf (
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant without RandomAccessIterator - 'operator -'. Call pushBackAllOf without size, letting
                 * the function compute the distance between start and end */
                this->pushBackAllOf (
                        iterable.begin(),
                        iterable.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call pushBackAllOf with size */
                this->pushBackAllOf (
                        list.begin(),
                        list.end(),
                        list.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count
            ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void {

                /* Handle type of the new front address function */
                using __ReceiverNewFrontArrayHandlerType    = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto    const pReceiver                     = reinterpret_cast < __ReceiverType * > ( this );
                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size    const parameterCount                = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements                    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new front address array with the created buffer */
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

                /* Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                Size index = 0ULL;
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                }

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __BoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count
            ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void {

                /* Handle type of the new back address function */
                using __ReceiverNewBackArrayHandlerType = void ( __ReceiverType :: * ) ( Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto    const pReceiver                 = reinterpret_cast < __ReceiverType * > ( this );
                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size    const parameterCount            = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements                = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new back address array with the created buffer */
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

                /* Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                Size index = 0ULL;
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                }

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the copy constructor via front emplacement */
                return this->emplaceFront ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the move constructor via front emplacement */
                return this->emplaceFront ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the copy constructor via back emplacement */
                return this->emplaceBack ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Invoke the move constructor via back emplacement */
                return this->emplaceBack ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceFront ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceFront ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceBack ( element );
            }


            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* Call non-deprecated, equivalent function */
                return this->emplaceBack ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplaceFront (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                /* call local dispatcher function to acquire a new front address, then construct element
                 * with received parameters */
                return * new ( reinterpret_cast < __ReceiverType * > ( this )->__newFront () ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplaceBack (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference {

                /* call local dispatcher function to acquire a new back address, then construct element
                 * with received parameters */
                return * new ( reinterpret_cast < __ReceiverType * > ( this )->__newBack () ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAll (
                    __ArgumentTypes && ... values
            ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                /* The number of received values is the numbers of elements to be created */
                Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call local dispatcher handle for a new front address array with the created buffer */
                reinterpret_cast < __ReceiverType * > ( this )->__newFrontArray (
                        parameterCount,
                        ppElements
                );

                /* Forward initialization values to construct each received address with them */
                cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                        ppElements,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAll (
                    __ArgumentTypes && ... values
            ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void {

                /* The number of received values is the numbers of elements to be created */
                Size    const parameterCount = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call local dispatcher handle for a new back address array with the created buffer */
                reinterpret_cast < __ReceiverType * > ( this )->__newBackArray (
                        parameterCount,
                        ppElements
                );

                /* Forward initialization values to construct each received address with them */
                cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                        ppElements,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant with RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size */
                this->pushFrontAllOf (
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant without RandomAccessIterator - 'operator -'. Call pushFrontAllOf without size, letting
                 * the function compute the distance between start and end */
                this->pushFrontAllOf (
                        iterable.begin(),
                        iterable.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call pushFrontAllOf with size */
                this->pushFrontAllOf (
                        list.begin(),
                        list.end(),
                        list.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant with RandomAccessIterator - 'operator -'. Call pushBackAllOf with size */
                this->pushBackAllOf (
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IterableType const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> void {

                /* Variant without RandomAccessIterator - 'operator -'. Call pushBackAllOf without size, letting
                 * the function compute the distance between start and end */
                this->pushBackAllOf (
                        iterable.begin(),
                        iterable.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __TElementType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call pushBackAllOf with size */
                this->pushBackAllOf (
                        list.begin(),
                        list.end(),
                        list.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushFrontAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count
            ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> void {

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size    const parameterCount    = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements        = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call local dispatcher handle for a new front address array with the created buffer */
                reinterpret_cast < __ReceiverType * > ( this )->__newFrontArray (
                        parameterCount,
                        ppElements
                );

                /* Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                Size index = 0ULL;
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                }

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalBoundaryInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: pushBackAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count
            ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> void {

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size    const parameterCount    = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto          ppElements        = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call local dispatcher handle for a new back address array with the created buffer */
                reinterpret_cast < __ReceiverType * > ( this )->__newBackArray (
                        parameterCount,
                        ppElements
                );

                /* Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                Size index = 0ULL;
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) new ( ppElements [ index ++ ] ) __ElementType ( * iterator );
                }

                /* Free the temporary address buffer */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ */
