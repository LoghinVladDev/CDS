//
// Created by loghin on 7/5/22.
//

#ifndef __CDS_SHARED_ARRAY_IMPL_HPP__
#define __CDS_SHARED_ARRAY_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > Size const __Array <
                        __ElementType,
                        __equals
                > :: __a_minCapacity;


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_clear (
                        bool destroyBuffer
                ) noexcept -> void {

                    if ( this->_pData == nullptr ) {
                        return;
                    }

                    while ( this->_pData->_pFront != this->_pData->_pBack ) {
                        ( this->_pData->_pFront ++ )->~__ElementType ();
                    }

                    if ( destroyBuffer ) {

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pData->_pBuffer );
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( this->_pData );
                    } else {

                        this->_pData->_pFront           = this->_pData->_pBuffer + this->_pData->_frontCapacity;
                        this->_pData->_pBack            = this->_pData->_pFront;
                    }
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_size () const noexcept -> Size {

                    return
                            this->_pData == nullptr ?
                            0ULL                    :
                            this->_pData->_pBack - this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_remove (
                        Index index
                ) noexcept -> void {

                    auto const size = this->__a_size();

                    if ( size == 0ULL ) {
                        return;
                    }

                    if ( index == 0ULL ) {

                        ( this->_pData->_pFront ++ )->~__ElementType ();
                        return;
                    } else if ( index == size - 1ULL ) {

                        ( -- this->_pData->_pBack )->~__ElementType ();
                        return;
                    }

                    this->_pData->_pFront [ index ].~__ElementType ();
                    auto shiftLeftSide =
                            static_cast < Size > ( index ) <
                            this->__a_size() / 2ULL;

                    ElementType * pDestination  = nullptr;
                    ElementType * pSource       = nullptr;
                    Size          count         = 0ULL;

                    if ( shiftLeftSide ) {
                        pDestination = ++ this->_pData->_pFront;
                        pSource      = pDestination - 1ULL;
                        count        = static_cast < Size > ( index );
                    } else {
                        pDestination = this->_pData->_pFront + static_cast < Size > ( index );
                        pSource      = pDestination + 1ULL;
                        count        = size - static_cast < Size > ( index );

                        -- this->_pData->_pBack;
                    }

                    (void) std :: memcpy (
                            reinterpret_cast < void * > ( pDestination ),
                            reinterpret_cast < void const * > ( pSource ),
                            sizeof ( __ElementType ) * count
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_get (
                        Index index
                ) noexcept -> ElementType * {

                    if ( this->__a_size () == 0ULL ) {
                        return nullptr;
                    }

                    return this->_pData->_pFront + index;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_get (
                        Index index
                ) const noexcept -> ElementType const * {

                    if ( this->__a_size () == 0ULL ) {
                        return nullptr;
                    }

                    return this->_pData->_pFront + index;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_init () noexcept -> void {

                    this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                    (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                    this->_pData->_frontNextCapacity    = __Array :: __a_minCapacity;
                    this->_pData->_backNextCapacity     = __Array :: __a_minCapacity;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newFront () noexcept -> ElementType * {

                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    if ( this->_pData->_pFront == this->_pData->_pBuffer ) {

                        this->_pData->_frontNextCapacity    = cds :: maxOf ( this->_pData->_frontNextCapacity, __Array :: __a_minCapacity );

                        auto pNewBuffer                     = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontNextCapacity + this->_pData->_backCapacity
                        );

                        auto const size                     = this->__a_size();
                        auto const pNewFront                = pNewBuffer + this->_pData->_frontNextCapacity - this->_pData->_frontCapacity;

                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pNewFront ),
                                reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                sizeof ( __ElementType ) * size
                        );

                        this->_pData->_pBack                = pNewFront + size;
                        this->_pData->_pFront               = pNewFront;
                        this->_pData->_frontCapacity        = this->_pData->_frontNextCapacity;
                        this->_pData->_frontNextCapacity    = this->_pData->_frontNextCapacity * 2ULL;

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    return -- this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAddress (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> ElementType * {

                    (void) pReferenceElement;

                    * pNewElementCreated = true;
                    return this->__a_newBack();
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBack () noexcept -> ElementType * {

                    if ( this->_pData == nullptr ) {
                        this->__a_init ();
                    }

                    if ( this->_pData->_pBack == this->_pData->_pBuffer + this->_pData->_frontCapacity + this->_pData->_backCapacity ) {
                        this->_pData->_backNextCapacity = cds :: maxOf ( this->_pData->_backNextCapacity, __Array :: __a_minCapacity );

                        auto const pNewBuffer           = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        this->_pData->_pFront           = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack            = pNewBuffer + ( this->_pData->_pBack - this->_pData->_pBuffer );
                        this->_pData->_backCapacity     = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    return this->_pData->_pBack ++;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newFrontArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    if ( this->_pData->_pBuffer + count > this->_pData->_pFront ) {
                        this->_pData->_frontNextCapacity    = cds :: maxOf ( this->_pData->_frontNextCapacity, count + this->_pData->_frontCapacity );

                        auto pNewBuffer                     = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontNextCapacity + this->_pData->_backCapacity
                        );

                        auto const size                     = this->__a_size();
                        auto const pNewFront                = pNewBuffer + ( this->_pData->_frontNextCapacity - this->_pData->_frontCapacity ) + ( this->_pData->_pFront - this->_pData->_pBuffer );

                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pNewFront ),
                                reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                sizeof ( __ElementType ) * size
                        );

                        this->_pData->_pFront               = pNewFront;
                        this->_pData->_pBack                = pNewFront + size;
                        this->_pData->_frontCapacity        = this->_pData->_frontNextCapacity;
                        this->_pData->_frontNextCapacity    = this->_pData->_frontNextCapacity * 2ULL;

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ count - index - 1ULL ] = -- this->_pData->_pFront;
                    }
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBackArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    if ( this->_pData->_pBack + count > this->_pData->_pBuffer + this->_pData->_frontCapacity + this->_pData->_backCapacity ) {
                        this->_pData->_backNextCapacity = cds :: maxOf ( this->_pData->_backNextCapacity, this->_pData->_backCapacity + count );

                        auto pNewBuffer                 = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        this->_pData->_pFront           = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack            = pNewBuffer + ( this->_pData->_pBack - this->_pData->_pBuffer );
                        this->_pData->_backCapacity     = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ index ] = this->_pData->_pBack ++;
                    }
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBefore (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> ElementType * {

                    return nullptr;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeConst (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> ElementType * {

                    return nullptr;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfter (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> ElementType * {

                    return nullptr;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterConst (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> ElementType * {

                    return nullptr;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeArray (
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeArrayConst (
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterArray (
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterArrayConst (
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_begin () noexcept -> __a_Iterator {

                    return __a_Iterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_end () noexcept -> __a_Iterator {

                    return __a_Iterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_cbegin () const noexcept -> __a_ConstIterator {

                    return __a_ConstIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_cend () const noexcept -> __a_ConstIterator {

                    return __a_ConstIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_rbegin () noexcept -> __a_ReverseIterator {

                    return __a_ReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_rend () noexcept -> __a_ReverseIterator {

                    return __a_ReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_crbegin () const noexcept -> __a_ConstReverseIterator {

                    return __a_ConstReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_crend () const noexcept -> __a_ConstReverseIterator {

                    return __a_ConstReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_remove (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    auto const pElement = & iterator [ 0ULL ];
                    if ( this->_pData == nullptr || ! ( this->_pData->_pFront <= pElement && pElement < this->_pData->_pBack ) ) {
                        return false;
                    }

                    this->__a_remove ( static_cast < Index > ( pElement - this->_pData->_pFront ) );
                    return true;
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_remove (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> bool {

                    auto const pElement = & iterator [ 0ULL ];
                    if ( this->_pData == nullptr || ! ( this->_pData->_pFront <= pElement && pElement < this->_pData->_pBack ) ) {
                        return false;
                    }

                    this->__a_remove ( static_cast < Index > ( pElement - this->_pData->_pFront ) );
                    return true;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ARRAY_IMPL_HPP__
