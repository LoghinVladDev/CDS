/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertBefore (
                        AbstractIterator    const & iterator,
                        ElementType         const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertBefore (
                        AbstractIterator const & iterator,
                        ElementType           && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAfter (
                        AbstractIterator    const & iterator,
                        ElementType         const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType      /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAfter (
                        AbstractIterator const & iterator,
                        ElementType           && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceBefore (
                        AbstractIterator        const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    using __ReceiverNewBeforeHandlerType    = __ElementType * ( __ReceiverType :: * ) ( __GenericIterator );
                    auto const pReceiver                    = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    auto const pNewLocation = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewBeforeHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddress
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator()
                    );

                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceAfter (
                        AbstractIterator        const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    using __ReceiverNewAfterHandlerType = __ElementType * ( __ReceiverType :: * ) ( __GenericIterator );
                    auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    auto const pNewLocation = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewAfterHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddress
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator()
                    );

                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllBefore (
                        AbstractIterator    const &     iterator,
                        __ArgumentTypes          && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    using __ReceiverNewBeforeArrayHandlerType   = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                    auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewBeforeArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                                ppElements,
                                std :: forward < __ArgumentTypes > ( values ) ...
                        );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllAfter (
                        AbstractIterator    const &     iterator,
                        __ArgumentTypes          && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    using __ReceiverNewAfterArrayHandlerType    = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                    auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewAfterArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                                ppElements,
                                std :: forward < __ArgumentTypes > ( values ) ...
                        );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator    const & iterator,
                        __IterableType      const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator                            const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator    const & iterator,
                        __IterableType      const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator                            const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator    const & iterator,
                        __IteratorType      const & begin,
                        __IteratorType      const & end,
                        Size                        count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    using __ReceiverNewBeforeArrayHandlerType   = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                    auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewBeforeArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        Size index = 0ULL;
                        for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                            (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                        }
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator    const & iterator,
                        __IteratorType      const & begin,
                        __IteratorType      const & end,
                        Size                        count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    using __ReceiverNewAfterArrayHandlerType    = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                    auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                    if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = (
                            pReceiver ->* reinterpret_cast < __ReceiverNewAfterArrayHandlerType > (
                                    pReceiver->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        Size index = 0ULL;
                        for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                            (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                        }
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertBefore (
                        Iterator    const & iterator,
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertBefore (
                        Iterator    const & iterator,
                        ElementType      && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAfter (
                        Iterator    const & iterator,
                        ElementType const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAfter (
                        Iterator    const & iterator,
                        ElementType      && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceBefore (
                        Iterator                const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newBefore ( & iterator );
                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType     /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __EmplaceArgumentTypes /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceAfter (
                        Iterator                const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAfter ( & iterator );
                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllBefore (
                        Iterator        const &     iterator,
                        __ArgumentTypes      && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                                ppElements,
                                std :: forward < __ArgumentTypes > ( values ) ...
                        );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename ... __ArgumentTypes        /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllAfter (
                        Iterator         const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newAfterArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                                ppElements,
                                std :: forward < __ArgumentTypes > ( values ) ...
                        );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        Iterator        const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        Iterator                                    const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IterableType             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        Iterator        const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        Iterator                                    const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            list.begin(),
                            list.end(),
                            list.size()
                    );
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __LocalClientIteratorType  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfBefore (
                        Iterator        const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        Size                    count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        Size index = 0ULL;
                        for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                            (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                        }
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }


                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __LocalClientIteratorType  /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __IteratorType             /* NOLINT(bugprone-reserved-identifier) */
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfAfter (
                        Iterator        const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end,
                        Size                    count
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! static_cast < bool > ( iterator ) ) {
                        return false;
                    }

                    Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                    auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newAfterArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    if ( allocationStatus ) {
                        Size index = 0ULL;
                        for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                            (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                        }
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return allocationStatus;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ */
