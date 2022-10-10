/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
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

                /* Invoke the copy constructor via front emplacement */
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

                /* Invoke the move constructor via front emplacement */
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

                /* Invoke the copy constructor via back emplacement */
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

                /* Invoke the move constructor via back emplacement */
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

                /* Handle type of the new before address function */
                using __ReceiverNewBeforeHandlerType    = __ElementType * ( __ReceiverType :: * ) ( __GenericIterator );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                    = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace before it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* Create the request for a new before address handler and call it */
                auto const pNewLocation = (
                        pReceiver ->* reinterpret_cast < __ReceiverNewBeforeHandlerType > (
                                pReceiver->__cicch_obtainGenericHandler (
                                        __CollectionInternalRequestType :: __cirt_newBeforeAddress
                                )
                        )
                ) (
                        iterator._pDelegate->iterator()
                );

                /* If no address received, insertion not possible */
                if ( pNewLocation == nullptr ) {
                    return false;
                }

                /* Otherwise, use placement new for creation */
                (void) new ( pNewLocation ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                /* Successful Result */
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

                /* Handle type of the new after address function */
                using __ReceiverNewAfterHandlerType = __ElementType * ( __ReceiverType :: * ) ( __GenericIterator );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace after it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* Create the request for a new after address handler and call it */
                auto const pNewLocation = (
                        pReceiver ->* reinterpret_cast < __ReceiverNewAfterHandlerType > (
                                pReceiver->__cicch_obtainGenericHandler (
                                        __CollectionInternalRequestType :: __cirt_newAfterAddress
                                )
                        )
                ) (
                        iterator._pDelegate->iterator()
                );

                /* If no address received, insertion not possible */
                if ( pNewLocation == nullptr ) {
                    return false;
                }

                /* Otherwise, use placement new for creation */
                (void) new ( pNewLocation ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                /* Successful Result */
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

                /* Handle type of the new before address function */
                using __ReceiverNewBeforeArrayHandlerType   = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace before it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created */
                Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new before address array with the created buffer */
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

                /* If status OK, initialize received memory with received values */
                if ( allocationStatus ) {
                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }

                /* Free temporary buffer and return status */
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

                /* Handle type of the new after address function */
                using __ReceiverNewAfterArrayHandlerType    = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace after it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created */
                Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new after address array with the created buffer */
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

                /* If status OK, initialize received memory with received values */
                if ( allocationStatus ) {
                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }

                /* Free temporary buffer and return status */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                return allocationStatus;
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: insertAllOfBefore (
                    AbstractIterator    const & iterator,
                    __IterableType      const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size */
                return this->insertAllOfBefore (
                        iterator,
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: insertAllOfBefore (
                    AbstractIterator    const & iterator,
                    __IterableType      const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
                 * the function compute the distance between start and end */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size */
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
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: insertAllOfAfter (
                    AbstractIterator    const & iterator,
                    __IterableType      const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size */
                return this->insertAllOfAfter (
                        iterator,
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType              /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: insertAllOfAfter (
                    AbstractIterator    const & iterator,
                    __IterableType      const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
                 * the function compute the distance between start and end */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size */
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

                /* Handle type of the new before address function */
                using __ReceiverNewBeforeArrayHandlerType   = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace before it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new before address array with the created buffer */
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

                /* If status OK, Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                if ( allocationStatus ) {
                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }
                }

                /* Free temporary buffer and return status */
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

                /* Handle type of the new after address function */
                using __ReceiverNewAfterArrayHandlerType    = bool ( __ReceiverType :: * ) ( __GenericIterator, Size, __ElementType ** );
                /* Caller object reinterpreted as receiver of the request */
                auto const pReceiver                        = reinterpret_cast < __ReceiverType * > ( this );

                /* If iterator invalid, cannot emplace before it */
                if ( ! iterator.of ( pReceiver ) || ! iterator.valid() ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Request and call handler for a new after address array with the created buffer */
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

                /* If status OK, Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                if ( allocationStatus ) {
                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }
                }

                /* Free temporary buffer and return status */
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

                /* Invoke the copy constructor via front emplacement */
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

                /* Invoke the move constructor via front emplacement */
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

                /* Invoke the copy constructor via back emplacement */
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

                /* Invoke the move constructor via back emplacement */
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

                /* If iterator invalid, cannot emplace before it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* Call dispatcher local new before address handler */
                auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newBefore ( & iterator );

                /* If no address received, insertion not possible */
                if ( pNewLocation == nullptr ) {
                    return false;
                }

                /* Otherwise, use placement new for creation */
                (void) new ( pNewLocation ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                /* Successful Result */
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

                /* If iterator invalid, cannot emplace after it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* Call dispatcher local new after address handler */
                auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAfter ( & iterator );

                /* If no address received, insertion not possible */
                if ( pNewLocation == nullptr ) {
                    return false;
                }

                /* Otherwise, use placement new for creation */
                (void) new ( pNewLocation ) __ElementType (
                        std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                );

                /* Successful Result */
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

                /* If iterator invalid, cannot emplace before it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created */
                Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call dispatcher local new before address array handler */
                auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArray (
                        & iterator,
                        parameterCount,
                        ppElements
                );

                /* If status OK, initialize received memory with received values */
                if ( allocationStatus ) {
                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }

                /* Free temporary buffer and return status */
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

                /* If iterator invalid, cannot emplace after it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created */
                Size  const parameterCount  = sizeof ... ( __ArgumentTypes );
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call dispatcher local new after address array handler */
                auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newAfterArray (
                        & iterator,
                        parameterCount,
                        ppElements
                );

                /* If status OK, initialize received memory with received values */
                if ( allocationStatus ) {
                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );
                }

                /* Free temporary buffer and return status */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                return allocationStatus;
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: insertAllOfBefore (
                    Iterator        const & iterator,
                    __IterableType  const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant with RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size */
                return this->insertAllOfBefore (
                        iterator,
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: insertAllOfBefore (
                    Iterator        const & iterator,
                    __IterableType  const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant without RandomAccessIterator - 'operator -'. Call insertAllOfBefore without size, letting
                 * the function compute the distance between start and end */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfBefore with size */
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
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: insertAllOfAfter (
                    Iterator        const & iterator,
                    __IterableType  const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant with RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size */
                return this->insertAllOfAfter (
                        iterator,
                        iterable.begin(),
                        iterable.end(),
                        iterable.size()
                );
            }


            template <
                    typename __ReceiverType,        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType         /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                    cds :: meta :: EnableIf <
                            ! meta :: __IterableSizeAvailable < __IterableType > :: value
                    >
            > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: insertAllOfAfter (
                    Iterator        const & iterator,
                    __IterableType  const & iterable
            ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                /* Variant without RandomAccessIterator - 'operator -'. Call insertAllOfAfter without size, letting
                 * the function compute the distance between start and end */
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

                /* initializer_list has RandomAccessIterator - 'operator -'. Call insertAllOfAfter with size */
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

                /* If iterator invalid, cannot emplace before it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call dispatcher local new before address array handler */
                auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArray (
                        & iterator,
                        parameterCount,
                        ppElements
                );

                /* If status OK, Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                if ( allocationStatus ) {
                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }
                }

                /* Free temporary buffer and return status */
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

                /* If iterator invalid, cannot emplace before it */
                if ( ! static_cast < bool > ( iterator ) ) {
                    return false;
                }

                /* The number of received values is the numbers of elements to be created. If 0, compute */
                Size  const parameterCount  = count == 0ULL ? __IteratorDistance < __IteratorType > :: __compute ( begin, end ) : count;
                /* Allocate the buffer to store the addresses of the newly created memory spaces for the elements */
                auto        ppElements      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                /* Call dispatcher local new after address array handler */
                auto const allocationStatus = reinterpret_cast < __ReceiverType * > ( this )->__newAfterArray (
                        & iterator,
                        parameterCount,
                        ppElements
                );

                /* If status OK, Parse iterator range and call placement new operator at received memory with
                 * each iterator's value */
                if ( allocationStatus ) {
                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }
                }

                /* Free temporary buffer and return status */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                return allocationStatus;
            }

        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__ */
