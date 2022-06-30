//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__
#define __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__

#include "../../../iterator/IteratorDistance.hpp"

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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertBefore (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->insertBefore (
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
                        __ReceiverType,
                        __ElementType,
                        __ReturnType
                > :: insertAfter (
                        AbstractConstIterator const & iterator,
                        ElementType                && element
                ) noexcept (false) -> ElementReference {

                    return this->insertAfter (
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                                    __AbstractDelegateIterator < __ElementType const > const *
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newBeforeAddressConst
                                            )
                                    )
                            ) (
                                    iterator._pDelegate
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                                    __AbstractDelegateIterator < __ElementType const > const *
                                            )
                                    > (
                                            static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_newAfterAddressConst
                                            )
                                    )
                            ) (
                                    iterator._pDelegate
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                            __AbstractDelegateIterator < __ElementType const > const *,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
                                    )
                            )
                    ) (
                            iterator._pDelegate,
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                            __AbstractDelegateIterator < __ElementType const > const *,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
                                    )
                            )
                    ) (
                            iterator._pDelegate,
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > __CDS_OptimalInline auto __AbstractConstIteratorRelativeInsertionClient <
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                            __AbstractDelegateIterator < __ElementType const > const *,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newBeforeAddressArrayConst
                                    )
                            )
                    ) (
                            iterator._pDelegate,
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
                > auto __AbstractConstIteratorRelativeInsertionClient <
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
                                            __AbstractDelegateIterator < __ElementType const > const *,
                                            Size,
                                            __ElementType **
                                    )
                            > (
                                    static_cast < __ReceiverType * > ( this )->__cicch_obtainGenericHandler (
                                            __CollectionInternalRequestType :: __cirt_newAfterAddressArrayConst
                                    )
                            )
                    ) (
                            iterator._pDelegate,
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

#endif // __CDS_SHARED_ABSTRACT_CONST_ITERATOR_RELATIVE_INSERTION_CLIENT_IMPL_HPP__
