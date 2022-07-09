//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__

#include "../../../../iterator/IteratorDistance.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertBefore (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertBefore (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAfter (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAfter (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceBefore (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    auto pNewLocation =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddressConst
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceAfter (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    auto const pNewLocation =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddressConst
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllBefore (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this ) ->*
                                    reinterpret_cast <
                                            void ( __ReceiverType :: * ) (
                                                    __GenericIterator,
                                                    Size,
                                                    __ElementType **
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllAfter (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this ) ->*
                                    reinterpret_cast <
                                            void ( __ReceiverType :: * ) (
                                                    __GenericIterator,
                                                    Size,
                                                    __ElementType **
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractConstIterator                           const & iterator,
                        std :: initializer_list < __ElementType >       const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractConstIterator                           const & iterator,
                        std :: initializer_list < __ElementType >       const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this ) ->*
                                    reinterpret_cast <
                                            void ( __ReceiverType :: * ) (
                                                    __GenericIterator,
                                                    Size,
                                                    __ElementType **
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! iterator.of ( reinterpret_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            (
                                    reinterpret_cast < __ReceiverType * > ( this ) ->*
                                    reinterpret_cast <
                                            void ( __ReceiverType :: * ) (
                                                    __GenericIterator,
                                                    Size,
                                                    __ElementType **
                                            )
                                    > (
                                            reinterpret_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertBefore (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertBefore (
                        ConstIterator const & iterator,
                        ElementType        && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceBefore (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAfter (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAfter (
                        ConstIterator   const & iterator,
                        ElementType          && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool {

                    return this->emplaceAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceBefore (
                        ConstIterator           const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newBeforeConst ( & iterator );
                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceAfter (
                        ConstIterator           const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    auto const pNewLocation = reinterpret_cast < __ReceiverType * > ( this )->__newAfterConst ( & iterator );
                    if ( pNewLocation == nullptr ) {
                        return false;
                    }

                    (void) new ( pNewLocation ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllBefore (
                        ConstIterator    const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArrayConst (
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
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllAfter (
                        ConstIterator    const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            reinterpret_cast < __ReceiverType * > ( this )->__newAfterArrayConst (
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
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfBefore (
                            iterator,
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    return this->insertAllOfAfter (
                            iterator,
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __LocalClientIteratorType  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            reinterpret_cast < __ReceiverType * > ( this )->__newBeforeArrayConst (
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __LocalClientIteratorType  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfAfter (
                        ConstIterator   const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( iterator == reinterpret_cast < __ReceiverType const * > ( this )->cend () ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    auto const allocationStatus =
                            reinterpret_cast < __ReceiverType * > ( this )->__newAfterArrayConst (
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

#endif // __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
