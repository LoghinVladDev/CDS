//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __AccumulatorType, // NOLINT(bugprone-reserved-identifier)
                        typename __LastType         // NOLINT(bugprone-reserved-identifier)
                > inline auto __expansiveInsert (   // NOLINT(bugprone-reserved-identifier)
                        __AccumulatorType   * pAccumulator,
                        __LastType         && lastValue
                ) noexcept (false) -> void {

                    (void) pAccumulator->insert ( std :: forward < __LastType > ( lastValue ) );
                }


                template <
                        typename     __AccumulatorType, // NOLINT(bugprone-reserved-identifier)
                        typename     __FirstType,       // NOLINT(bugprone-reserved-identifier)
                        typename ... __RemainingTypes   // NOLINT(bugprone-reserved-identifier)
                > inline auto __expansiveInsert (       // NOLINT(bugprone-reserved-identifier)
                        __AccumulatorType      *     pAccumulator,
                        __FirstType           &&     firstValue,
                        __RemainingTypes      && ... remainingValues
                ) noexcept (false) -> void {

                    (void) pAccumulator->insert ( std :: forward < __FirstType > ( firstValue ) );
                    __expansiveInsert (
                            pAccumulator,
                            std :: forward < __RemainingTypes > ( remainingValues ) ...
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
                > auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insert (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    bool newElementCreated;
                    auto pElementLocation = (
                                 static_cast < __ReceiverType * > ( this )->*
                                 reinterpret_cast <
                                         __ElementType * ( __ReceiverType :: * ) (
                                                 __ElementType const *,
                                                 bool                *
                                         )
                                 > (
                                         static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                 __CollectionInternalRequestType :: __cirt_newAddress
                                         )
                                 )
                    ) (
                            & element,
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        return * pElementLocation;
                    }

                    return * new (
                            pElementLocation
                    ) __ElementType ( element );
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
                > auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insert (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    bool newElementCreated;
                    auto pElementLocation = (
                            static_cast < __ReceiverType * > ( this )->*
                            reinterpret_cast <
                                    __ElementType * ( __ReceiverType :: * ) (
                                            __ElementType const *,
                                            bool                *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAddress
                                    )
                            )
                    ) (
                            & element,
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        return * pElementLocation;
                    }

                    return * new (
                            pElementLocation
                    ) __ElementType ( std :: move ( element ) );
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
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: add (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    return this->insert ( element );
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
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: add (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->insert ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplace (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType > referenceElementContainer;
                    referenceElementContainer.construct (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    bool newElementCreated;
                    auto pElementLocation = (
                            static_cast < __ReceiverType * > ( this )->*
                            reinterpret_cast <
                                    __ElementType * ( __ReceiverType :: * ) (
                                            __ElementType const *,
                                            bool                *
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAddress
                                    )
                            )
                    ) (
                            & referenceElementContainer.data(),
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        referenceElementContainer.destruct();
                    } else {
                        std::memcpy (
                                pElementLocation,
                                & referenceElementContainer._data[0],
                                sizeof ( __ElementType )
                        );
                    }

                    return * pElementLocation;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    __expansiveInsert (
                            this,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    __expansiveInsert (
                            this,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        __IterableType const & iterableType
                ) noexcept (false) -> void {

                    this->insertAllOf (
                            iterableType.begin(),
                            iterableType.end()
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
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->insertAllOf (
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
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        __IterableType const & iterableType
                ) noexcept (false) -> void {

                    this->insertAllOf (
                            iterableType.begin(),
                            iterableType.end()
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
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->insertAllOf (
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
                > auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        this->insert ( * iterator );
                    }
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    return this->insertAllOf (
                            begin,
                            end
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
                > auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insert (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    bool newElementCreated;
                    auto pElementLocation = static_cast < __ReceiverType * > ( this )->__new (
                            & element,
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        return * pElementLocation;
                    }

                    return * new (
                            pElementLocation
                    ) __ElementType ( element );
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
                > auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insert (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    bool newElementCreated;
                    auto pElementLocation = static_cast < __ReceiverType * > ( this )->__new (
                            & element,
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        return * pElementLocation;
                    }

                    return * new (
                            pElementLocation
                    ) __ElementType ( std :: move ( element ) );
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
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: add (
                        ElementType const & element
                ) noexcept (false) -> ElementReference {

                    return this->insert ( element );
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
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: add (
                        ElementType && element
                ) noexcept (false) -> ElementReference {

                    return this->insert ( std :: move ( element ) );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplace (
                        __EmplaceArgumentTypes && ... parameters
                ) noexcept (false) -> ElementReference {

                    cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType > referenceElementContainer;
                    referenceElementContainer.construct (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    bool newElementCreated;
                    auto pElementLocation = static_cast < __ReceiverType * > ( this )->__new (
                            & referenceElementContainer.data(),
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {
                        referenceElementContainer.destruct();
                    } else {
                        std::memcpy (
                                pElementLocation,
                                & referenceElementContainer._data[0],
                                sizeof ( __ElementType )
                        );
                    }

                    return * pElementLocation;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    __expansiveInsert (
                            this,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAll (
                        __ArgumentTypes && ... values
                ) noexcept (false) -> void {

                    __expansiveInsert (
                            this,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        __IterableType const & iterableType
                ) noexcept (false) -> void {

                    this->insertAllOf (
                            iterableType.begin(),
                            iterableType.end()
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
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->insertAllOf (
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
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        __IterableType const & iterableType
                ) noexcept (false) -> void {

                    this->insertAllOf (
                            iterableType.begin(),
                            iterableType.end()
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
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        std :: initializer_list < __ElementType > const & list
                ) noexcept (false) -> void {

                    this->insertAllOf (
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
                > auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    for ( auto iterator = begin; iterator != end; ++ iterator ) {
                        this->insert ( * iterator );
                    }
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: addAllOf (
                        __IteratorType const & begin,
                        __IteratorType const & end
                ) noexcept (false) -> void {

                    return this->insertAllOf (
                            begin,
                            end
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
