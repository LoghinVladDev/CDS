//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__

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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceBefore (
                        AbstractIterator        const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    (void) new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddress
                                            )
                                    )
                            ) (
                                    iterator._pDelegate->iterator()
                            )
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: emplaceAfter (
                        AbstractIterator        const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    (void) new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddress
                                            )
                                    )
                            ) (
                                    iterator._pDelegate->iterator()
                            )
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );

                    return true;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllBefore (
                        AbstractIterator    const &     iterator,
                        __ArgumentTypes          && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            __GenericIterator,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllAfter (
                        AbstractIterator    const &     iterator,
                        __ArgumentTypes          && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            __GenericIterator,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator    const & iterator,
                        __IterableType      const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    this->insertAllOfBefore (
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
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator                            const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    this->insertAllOfBefore (
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
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator    const & iterator,
                        __IterableType      const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    this->insertAllOfAfter (
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
                > __CDS_OptimalInline auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator                            const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    this->insertAllOfAfter (
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
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfBefore (
                        AbstractIterator    const & iterator,
                        __IteratorType      const & begin,
                        __IteratorType      const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            __GenericIterator,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType              // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType
                > :: insertAllOfAfter (
                        AbstractIterator    const & iterator,
                        __IteratorType      const & begin,
                        __IteratorType      const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( ! iterator.of ( static_cast < __ReceiverType const * > ( this ) ) || ! iterator.valid() ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    (
                            static_cast < __ReceiverType * > ( this ) ->*
                            reinterpret_cast <
                                    void ( __ReceiverType :: * ) (
                                            __GenericIterator,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArray
                                    )
                            )
                    ) (
                            iterator._pDelegate->iterator(),
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
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
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceBefore (
                        Iterator                const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    (void) new (
                            static_cast < __ReceiverType * > ( this )->__newBefore ( & iterator )
                    ) __ElementType (
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
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: emplaceAfter (
                        Iterator                const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    (void) new (
                            static_cast < __ReceiverType * > ( this )->__newAfter ( & iterator )
                    ) __ElementType (
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
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllBefore (
                        Iterator        const &     iterator,
                        __ArgumentTypes      && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBeforeArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllAfter (
                        Iterator         const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newAfterArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    cds :: __hidden :: __impl :: __allocation :: __forwardIntoArray (
                            ppElements,
                            std :: forward < __ArgumentTypes > ( values ) ...
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                    return true;
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        Iterator        const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    this->insertAllOfBefore (
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
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfBefore (
                        Iterator                                    const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    this->insertAllOfBefore (
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
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        Iterator        const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool {

                    this->insertAllOfAfter (
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
                > __CDS_OptimalInline auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __IteratorType
                > :: insertAllOfAfter (
                        Iterator                                    const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool {

                    this->insertAllOfAfter (
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
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfBefore (
                        Iterator        const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBeforeArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __LocalClientIteratorType  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __LocalClientIteratorType
                > :: insertAllOfAfter (
                        Iterator        const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool {

                    if ( iterator == static_cast < __ReceiverType * > ( this )->end () ) {
                        return false;
                    }

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newAfterArray (
                            & iterator,
                            parameterCount,
                            ppElements
                    );

                    Size index = 0ULL;
                    for ( auto lIterator = begin; lIterator != end; ++ lIterator ) {
                        (void) new ( ppElements [ index ++ ] ) __ElementType ( * lIterator );
                    }

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( ppElements );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
