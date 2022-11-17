/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __AccumulatorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LastType         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __expansiveInsert (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __AccumulatorType   * pAccumulator,
                    __LastType         && lastValue
            ) noexcept ( false ) -> void {

                /* being the last value, call insert in the caller accumulator */
                (void) pAccumulator->insert ( std :: forward < __LastType > ( lastValue ) );
            }


            template <
                    typename     __AccumulatorType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename     __FirstType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename ... __RemainingTypes   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __expansiveInsert (       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __AccumulatorType      *     pAccumulator,
                    __FirstType           &&     firstValue,
                    __RemainingTypes      && ... remainingValues
            ) noexcept ( false ) -> void {

                /* call insert on the first value */
                (void) pAccumulator->insert ( std :: forward < __FirstType > ( firstValue ) );

                /* recursively call the same function with the remaining values */
                __expansiveInsert (
                        pAccumulator,
                        std :: forward < __RemainingTypes > ( remainingValues ) ...
                );
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
            > auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insert (
                    ElementType const & element
            ) noexcept ( false ) -> ElementReference {

                /* decay of the element type */
                using __ConstructibleElementType    = cds :: meta :: RemoveConst < __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /* called handle type */
                using __ReceiverNewHandlerType      = __ConstructibleElementType * ( __ReceiverType :: * ) ( __ConstructibleElementType const *, bool * );

                /* receiver to call the request to */
                auto  const pReceiver               = reinterpret_cast < __ReceiverType * > ( this );

                /* status if new element was created and construction is possible */
                bool        newElementCreated;

                /* call receiver to acquire a new address from */
                auto const  pElementLocation        = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewHandlerType > (
                                    pReceiver->__iicch_obtainGenericHandler (
                                            __IterableInternalRequestType :: __iirt_newAddress
                                    )
                            )
                ) (
                        & element,
                        & newElementCreated
                );

                /* if no new element was created, return reference to received location */
                if ( ! newElementCreated ) {
                    return * pElementLocation;
                }

                /* return reference to the received address element, after in-place copy construction */
                return * new (
                        pElementLocation
                ) __ElementType ( element );
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
            > auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insert (
                    ElementType && element
            ) noexcept ( false ) -> ElementReference {

                /* decay of the element type */
                using __ConstructibleElementType    = cds :: meta :: RemoveConst < __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /* called handle type */
                using __ReceiverNewHandlerType      = __ConstructibleElementType * ( __ReceiverType :: * ) ( __ConstructibleElementType const *, bool * );

                /* receiver to call the request to */
                auto  const pReceiver               = reinterpret_cast < __ReceiverType * > ( this );

                /* status if new element was created and construction is possible */
                bool        newElementCreated;

                /* call receiver to acquire a new address from */
                auto  const pElementLocation        = (
                        pReceiver ->* reinterpret_cast < __ReceiverNewHandlerType > (
                                pReceiver->__iicch_obtainGenericHandler (
                                        __IterableInternalRequestType :: __iirt_newAddress
                                )
                        )
                ) (
                        & element,
                        & newElementCreated
                );

                /* if no new element was created, return reference to received location */
                if ( ! newElementCreated ) {
                    return * pElementLocation;
                }

                /* return reference to the received address element, after in-place move construction */
                return * new (
                        pElementLocation
                ) __ElementType ( std :: move ( element ) );
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
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: add (
                    ElementType const & element
            ) noexcept ( false ) -> ElementReference {

                /* call insert due to deprecation */
                return this->insert ( element );
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
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: add (
                    ElementType && element
            ) noexcept ( false ) -> ElementReference {

                /* call insert due to deprecation */
                return this->insert ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplace (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( false ) -> ElementReference {

                /* decay of the element type */
                using __ConstructibleElementType    = cds :: meta :: RemoveConst < __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                /* called handle type */
                using __ReceiverNewHandlerType      = __ConstructibleElementType * ( __ReceiverType :: * ) ( __ConstructibleElementType const *, bool * );

                /* prepare a memory container of the newly constructed element, to avoid destruction in out-of-stack contexts, without need
                 * of dynamic allocation */
                cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType > referenceElementContainer;

                /* emplace-construct new element */
                referenceElementContainer.construct (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                /* since resources are allocated ( constructor can allocate ) prior to a potential throw call, try */
                try {

                    /* receiver to call the request to */
                    auto  const pReceiver               = reinterpret_cast < __ReceiverType * > ( this );

                    /* status if new element was created and construction is possible */
                    bool        newElementCreated;

                    /* call receiver to acquire a new address from */
                    auto  const pElementLocation        = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewHandlerType > (
                                    pReceiver->__iicch_obtainGenericHandler (
                                            __IterableInternalRequestType :: __iirt_newAddress
                                    )
                            )
                    ) (
                            & referenceElementContainer.data(),
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {

                        /* if no new element was created, destruct the created element */
                        referenceElementContainer.destruct();

                    } else {

                        /* otherwise, copy created data to the received memory address */
                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pElementLocation ),
                                reinterpret_cast < void const * > ( & referenceElementContainer._data[0] ),
                                sizeof ( __ElementType )
                        );

                    }

                    /* either way, return reference to received address */
                    return * pElementLocation;
                } catch (...) {

                    /* in the case the call throws, destruct allocated data and throw the exception further in the stack */
                    referenceElementContainer.destruct();
                    throw;
                }
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAll (
                    __ArgumentTypes && ... values
            ) noexcept ( false ) -> void {

                /* call expansive insert with the received forwarding references on this object as the accumulator */
                __expansiveInsert (
                        this,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAll (
                    __ArgumentTypes && ... values
            ) noexcept ( false ) -> void {

                /* call expansive insert with the received forwarding references on this object as the accumulator */
                __expansiveInsert (
                        this,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    __IterableType const & iterable
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
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
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    std :: initializer_list < __ElementType > const & list
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
                        list.begin(),
                        list.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    __IterableType const & iterable
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
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
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    std :: initializer_list < __ElementType > const & list
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
                        list.begin(),
                        list.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept ( false ) -> void {

                /* call insert with extracted iterator values */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) this->insert ( * iterator );
                }
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __RandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept ( false ) -> void {

                /* call insertAllOf with received parameters */
                return this->insertAllOf (
                        begin,
                        end
                );
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
            > auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insert (
                    ElementType const & element
            ) noexcept ( false ) -> ElementReference {

                /* status if new element was created and construction is possible */
                bool newElementCreated;

                /* call receiver to acquire a new address from */
                auto pElementLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAddress (
                        & element,
                        & newElementCreated
                );

                /* if no new element was created, return reference to received location */
                if ( ! newElementCreated ) {
                    return * pElementLocation;
                }

                /* return reference to the received address element, after in-place copy construction */
                return * new (
                        pElementLocation
                ) __ElementType ( element );
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
            > auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insert (
                    ElementType && element
            ) noexcept ( false ) -> ElementReference {

                /* status if new element was created and construction is possible */
                bool newElementCreated;

                /* call receiver to acquire a new address from */
                auto pElementLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAddress (
                        & element,
                        & newElementCreated
                );

                /* if no new element was created, return reference to received location */
                if ( ! newElementCreated ) {
                    return * pElementLocation;
                }

                /* return reference to the received address element, after in-place move construction */
                return * new (
                        pElementLocation
                ) __ElementType ( std :: move ( element ) );
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
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: add (
                    ElementType const & element
            ) noexcept ( false ) -> ElementReference {

                /* call insert due to deprecation */
                return this->insert ( element );
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
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: add (
                    ElementType && element
            ) noexcept ( false ) -> ElementReference {

                /* call insert due to deprecation */
                return this->insert ( std :: move ( element ) );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: emplace (
                    __EmplaceArgumentTypes && ... parameters
            ) noexcept ( false ) -> ElementReference {

                /* prepare a memory container of the newly constructed element, to avoid destruction in out-of-stack contexts, without need
                 * of dynamic allocation */
                cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType > referenceElementContainer;

                /* emplace-construct new element */
                referenceElementContainer.construct (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                try {

                    /* status if new element was created and construction is possible */
                    bool        newElementCreated;

                    /* call receiver to acquire a new address from */
                    auto  const pElementLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAddress (
                            & referenceElementContainer.data(),
                            & newElementCreated
                    );

                    if ( ! newElementCreated ) {

                        /* if no new element was created, destruct the created element */
                        referenceElementContainer.destruct();

                    } else {

                        /* otherwise, copy created data to the received memory address */
                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pElementLocation ),
                                reinterpret_cast < void const * > ( & referenceElementContainer._data[0] ),
                                sizeof ( __ElementType )
                        );

                    }

                    /* either way, return reference to received address */
                    return * pElementLocation;
                } catch (...) {

                    /* in the case the call throws, destruct allocated data and throw the exception further in the stack */
                    referenceElementContainer.destruct();
                    throw;
                }
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAll (
                    __ArgumentTypes && ... values
            ) noexcept ( false ) -> void {

                /* call expansive insert with the received forwarding references on this object as the accumulator */
                __expansiveInsert (
                        this,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename ... __ArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAll (
                    __ArgumentTypes && ... values
            ) noexcept ( false ) -> void {

                /* call expansive insert with the received forwarding references on this object as the accumulator */
                __expansiveInsert (
                        this,
                        std :: forward < __ArgumentTypes > ( values ) ...
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    __IterableType const & iterable
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
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
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    std :: initializer_list < __ElementType > const & list
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
                        list.begin(),
                        list.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IterableType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    __IterableType const & iterable
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
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
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    std :: initializer_list < __ElementType > const & list
            ) noexcept ( false ) -> void {

                /* call insert all of with extracted iterators */
                this->insertAllOf (
                        list.begin(),
                        list.end()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: insertAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept ( false ) -> void {

                /* call insert with extracted iterator values */
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    (void) this->insert ( * iterator );
                }
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReturnType               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __IteratorType             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __LocalRandomInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __ReturnType
            > :: addAllOf (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept ( false ) -> void {

                /* call insertAllOf with received parameters */
                return this->insertAllOf (
                        begin,
                        end
                );
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ */
