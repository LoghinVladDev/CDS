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
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertBefore (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBefore (
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAfter (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceAfter (
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
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceBefore (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddressConst
                                            )
                                    )
                            ) (
                                    iterator._pDelegate->iterator()
                            )
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
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: emplaceAfter (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            (
                                    static_cast < __ReceiverType * > ( this )->*
                                    reinterpret_cast <
                                            __ElementType * ( __ReceiverType :: * ) (
                                                    __GenericIterator
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddressConst
                                            )
                                    )
                            ) (
                                    iterator._pDelegate->iterator()
                            )
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
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllBefore (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept (false) -> void {

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
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
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
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllAfter (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept (false) -> void {

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
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
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
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
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
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept (false) -> void {

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
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
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
                }


                template <
                        typename __ReceiverType,            // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType               // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __AbstractConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IteratorType          const & begin,
                        __IteratorType          const & end
                ) noexcept (false) -> void {

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
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
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
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertBefore (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBefore (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertBefore (
                        ConstIterator const & iterator,
                        ElementType        && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceBefore (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAfter (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceAfter (
                            iterator,
                            element
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAfter (
                        ConstIterator   const & iterator,
                        ElementType          && element
                ) noexcept (false) -> ElementReference {

                    return this->emplaceAfter (
                            iterator,
                            std :: move ( element )
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: emplaceBefore (
                        ConstIterator           const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            static_cast < __ReceiverType * > ( this )->__newBeforeConst ( & iterator )
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,      // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType     // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __EmplaceArgumentTypes // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: emplaceAfter (
                        ConstIterator           const &     iterator,
                        __EmplaceArgumentTypes       && ... parameters
                ) noexcept (false) -> ElementReference {

                    return * new (
                            static_cast < __ReceiverType * > ( this )->__newAfterConst ( & iterator )
                    ) __ElementType (
                            std :: forward < __EmplaceArgumentTypes > ( parameters ) ...
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllBefore (
                        ConstIterator    const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept (false) -> void {

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBeforeArrayConst (
                            & iterator,
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
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename ... __ArgumentTypes        // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllAfter (
                        ConstIterator    const &     iterator,
                        __ArgumentTypes       && ... values
                ) noexcept (false) -> void {

                    Size  const parameterCount = sizeof ... ( __ArgumentTypes );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newAfterArrayConst (
                            & iterator,
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
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept (false) -> void {

                    this->insertAllOfBefore (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllOfBefore (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept (false) -> void {

                    this->insertAllOfBefore (
                            iterator,
                            list.begin(),
                            list.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IterableType             // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllOfAfter (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept (false) -> void {

                    this->insertAllOfAfter (
                            iterator,
                            iterable.begin(),
                            iterable.end()
                    );
                }


                template <
                        typename __ReceiverType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType,          // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType         // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __TElementType,            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __IteratorType
                > :: insertAllOfAfter (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
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
                        typename __ReturnType,              // NOLINT(bugprone-reserved-identifier)
                        typename __LocalClientIteratorType  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __LocalClientIteratorType
                > :: insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept (false) -> void {

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newBeforeArrayConst (
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
                        typename __ReturnType,              // NOLINT(bugprone-reserved-identifier)
                        typename __LocalClientIteratorType  // NOLINT(bugprone-reserved-identifier)
                > template <
                        typename __IteratorType             // NOLINT(bugprone-reserved-identifier)
                > auto __LocalConstIteratorRelativeInsertionPrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType,
                        __LocalClientIteratorType
                > :: insertAllOfAfter (
                        ConstIterator   const & iterator,
                        __IteratorType  const & begin,
                        __IteratorType  const & end
                ) noexcept (false) -> void {

                    Size  const parameterCount = __IteratorDistance < __IteratorType > :: __compute ( begin, end );
                    auto        ppElements = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType * > ( parameterCount );

                    static_cast < __ReceiverType * > ( this )->__newAfterArrayConst (
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

#endif // __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_IMPL_HPP__
