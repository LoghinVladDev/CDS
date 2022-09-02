/*
 * Created by loghin on 7/5/22.
 */

#ifndef __CDS_SHARED_ARRAY_IMPL_HPP__
#define __CDS_SHARED_ARRAY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > Size const __Array <
                        __ElementType,
                        __equals
                > :: __a_minCapacity;


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __Array <
                        __ElementType,
                        __equals
                > :: __Array () noexcept = default;


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline __Array <
                        __ElementType,
                        __equals
                > :: __Array (
                        __Array const & array
                ) noexcept {

                    /* use internal function to copy array data, since new array is cleared */
                    this->__a_copy ( array );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __Array <
                        __ElementType,
                        __equals
                > :: __Array (
                        __Array && array
                ) noexcept :
                        _pData ( cds :: exchange ( array._pData, nullptr ) ) {

                    /* move directly array data */
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_clear (
                        bool destroyBuffer
                ) noexcept -> void {

                    /* If no data / already clear, do nothing */
                    if ( this->_pData == nullptr ) {
                        return;
                    }

                    /* clear the contents of the whole array */
                    while ( this->_pData->_pFront != this->_pData->_pBack ) {
                        ( this->_pData->_pFront ++ )->~__ElementType ();
                    }

                    /* If destroying buffer, destroy buffer and data contents, otherwise, just reset buffer front and back */
                    if ( destroyBuffer ) {

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pData->_pBuffer );
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( this->_pData );
                    } else {

                        this->_pData->_pFront           = this->_pData->_pBuffer + this->_pData->_frontCapacity;
                        this->_pData->_pBack            = this->_pData->_pFront;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_size () const noexcept -> Size {

                    /* if data empty, size is 0. Otherwise, distance from back to front */
                    return
                            this->_pData == nullptr ?
                            0ULL                    :
                            this->_pData->_pBack - this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_remove (
                        Index index
                ) noexcept -> void {

                    /* acquire size for later use */
                    auto const size = this->__a_size();

                    /* if empty, do nothing */
                    if ( size == 0ULL ) {
                        return;
                    }

                    /* if removal of front, delete front, advance front pointer, return
                     * if removal of back, delete back, reverse back pointer, return */
                    if ( index == 0ULL ) {

                        ( this->_pData->_pFront ++ )->~__ElementType ();
                        return;
                    } else if ( index == size - 1ULL ) {

                        ( -- this->_pData->_pBack )->~__ElementType ();
                        return;
                    }

                    /* otherwise, destroy element and decide which size is easier to shift ( fewer operations ) */
                    this->_pData->_pFront [ index ].~__ElementType ();
                    auto shiftLeftSide =
                            static_cast < Size > ( index ) <
                            this->__a_size() / 2ULL;

                    /* find information regarding where to move, from where to move and how many elements */
                    ElementType * pDestination  = nullptr;
                    ElementType * pSource       = nullptr;
                    Size          count         = 0ULL;

                    /* if shifting left, destination is after front. source is previous front. count is determined by given index
                     * if shifting right, destination is front + index, source is one after destination, count is size - index */
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

                    /* execute the move of the elements */
                    (void) std :: memmove (
                            reinterpret_cast < void * > ( pDestination ),
                            reinterpret_cast < void const * > ( pSource ),
                            sizeof ( __ElementType ) * count
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_get (
                        Index index
                ) noexcept -> ElementType * {

                    /* element requested is offset 'index' from 'front' */
                    return this->_pData->_pFront + index;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_get (
                        Index index
                ) const noexcept -> ElementType const * {

                    /* element requested is offset 'index' from 'front' */
                    return this->_pData->_pFront + index;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_init () noexcept -> void {

                    /* acquire new memory for array container and clear it */
                    this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                    (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                    /* set future capacities */
                    this->_pData->_frontNextCapacity    = __Array :: __a_minCapacity;
                    this->_pData->_backNextCapacity     = __Array :: __a_minCapacity;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newFront () noexcept -> ElementType * {

                    /* if empty, initialize */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    /* if no space available in front, enlarge front */
                    if ( this->_pData->_pFront == this->_pData->_pBuffer ) {

                        /* acquire next capacity */
                        this->_pData->_frontNextCapacity    = cds :: maxOf ( this->_pData->_frontNextCapacity, __Array :: __a_minCapacity );

                        /* acquire new buffer */
                        auto pNewBuffer                     = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontNextCapacity + this->_pData->_backCapacity
                        );

                        /* store current size and compute new front in new buffer */
                        auto const size                     = this->__a_size();
                        auto const pNewFront                = pNewBuffer + this->_pData->_frontNextCapacity - this->_pData->_frontCapacity;

                        /* copy data from old buffer to new */
                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pNewFront ),
                                reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                sizeof ( __ElementType ) * size
                        );

                        /* set other values. back in new buffer, front and capacities */
                        this->_pData->_pBack                = pNewFront + size;
                        this->_pData->_pFront               = pNewFront;
                        this->_pData->_frontCapacity        = this->_pData->_frontNextCapacity;
                        this->_pData->_frontNextCapacity    = this->_pData->_frontNextCapacity * 2ULL;

                        /* clear old buffer and store new one */
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    /* update front to allow for one more element and return address of new space */
                    return -- this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAddress (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> ElementType * {

                    /* pReferenceElement is unused */
                    (void) pReferenceElement;

                    /* element always created. return address with newBack */
                    * pNewElementCreated = true;
                    return this->__a_newBack();
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBack () noexcept -> ElementType * {

                    /* if empty, initialize */
                    if ( this->_pData == nullptr ) {
                        this->__a_init ();
                    }

                    /* if back is at end of buffer => no space */
                    if ( this->_pData->_pBack == this->_pData->_pBuffer + this->_pData->_frontCapacity + this->_pData->_backCapacity ) {

                        /* compute next capacity */
                        this->_pData->_backNextCapacity = cds :: maxOf ( this->_pData->_backNextCapacity, __Array :: __a_minCapacity );

                        /* reallocate buffer to greater size */
                        auto const pNewBuffer           = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        /* reallocation could create a new buffer, so reset front and back. Also update back capacity and next capacity, and buffer */
                        this->_pData->_pFront           = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack            = pNewBuffer + ( this->_pData->_pBack - this->_pData->_pBuffer );
                        this->_pData->_backCapacity     = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    /* return address to back ( as it already contained uninitialized memory space ) and increase it */
                    return this->_pData->_pBack ++;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newFrontArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    /* if empty, initialize */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    /* if no space available in front, enlarge front */
                    if ( this->_pData->_pBuffer + count > this->_pData->_pFront ) {

                        /* acquire next capacity */
                        this->_pData->_frontNextCapacity    = cds :: maxOf ( this->_pData->_frontNextCapacity, count + this->_pData->_frontCapacity );

                        /* acquire new buffer */
                        auto pNewBuffer                     = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontNextCapacity + this->_pData->_backCapacity
                        );

                        /* store current size and compute new front in new buffer */
                        auto const size                     = this->__a_size();
                        auto const pNewFront                = pNewBuffer + ( this->_pData->_frontNextCapacity - this->_pData->_frontCapacity ) + ( this->_pData->_pFront - this->_pData->_pBuffer );

                        /* copy data from old buffer to new */
                        (void) std :: memcpy (
                                reinterpret_cast < void * > ( pNewFront ),
                                reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                sizeof ( __ElementType ) * size
                        );

                        /* set other values. back in new buffer, front and capacities */
                        this->_pData->_pFront               = pNewFront;
                        this->_pData->_pBack                = pNewFront + size;
                        this->_pData->_frontCapacity        = this->_pData->_frontNextCapacity;
                        this->_pData->_frontNextCapacity    = this->_pData->_frontNextCapacity * 2ULL;

                        /* clear old buffer and store new one */
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    /* for a given count of elements, decrease front pointer and store address value to be returned via parameter */
                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ count - index - 1ULL ] = -- this->_pData->_pFront;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBackArray (
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void {

                    /* if empty, initialize */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    /* if back + count is after end of buffer => no space */
                    if ( this->_pData->_pBack + count > this->_pData->_pBuffer + this->_pData->_frontCapacity + this->_pData->_backCapacity ) {

                        /* compute next capacity */
                        this->_pData->_backNextCapacity = cds :: maxOf ( this->_pData->_backNextCapacity, this->_pData->_backCapacity + count );

                        /* reallocate buffer to greater size */
                        auto pNewBuffer                 = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        /* reallocation could create a new buffer, so reset front and back. Also update back capacity and next capacity, and buffer */
                        this->_pData->_pFront           = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack            = pNewBuffer + ( this->_pData->_pBack - this->_pData->_pBuffer );
                        this->_pData->_backCapacity     = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    /* for a given count of elements, store the address of back ( as already uninitialized ) and increase it */
                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ index ] = this->_pData->_pBack ++;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBefore (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> ElementType * {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement > this->_pData->_pBack ) {
                        return nullptr;
                    }

                    /* if address is of the first element, return new front */
                    if ( pElement == this->_pData->_pFront ) {
                        return this->__a_newFront ();
                    }

                    /* if address is after the last element, return new back */
                    if ( pElement == this->_pData->_pBack ) {
                        return this->__a_newBack ();
                    }

                    /* otherwise, create a new element at the index of the address in the array */
                    return this->__a_newAt ( pElement - this->_pData->_pFront );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeConst (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> ElementType * {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement > this->_pData->_pBack ) {
                        return nullptr;
                    }

                    /* if address is of the first element, return new front */
                    if ( pElement == this->_pData->_pFront ) {
                        return this->__a_newFront ();
                    }

                    /* if address is after the last element, return new back */
                    if ( pElement == this->_pData->_pBack ) {
                        return this->__a_newBack ();
                    }

                    /* otherwise, create a new element at the index of the address in the array */
                    return this->__a_newAt ( pElement - this->_pData->_pFront );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfter (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> ElementType * {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement >= this->_pData->_pBack ) {
                        return nullptr;
                    }

                    /* if address is of the last element, return new back */
                    if ( pElement + 1ULL == this->_pData->_pBack ) {
                        return this->__a_newBack ();
                    }

                    /* otherwise, create a new element at the index of the address in the array */
                    return this->__a_newAt ( pElement - this->_pData->_pFront + 1ULL );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterConst (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> ElementType * {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement >= this->_pData->_pBack ) {
                        return nullptr;
                    }

                    /* if address is of the last element, return new back */
                    if ( pElement + 1ULL == this->_pData->_pBack ) {
                        return this->__a_newBack ();
                    }

                    /* otherwise, create a new element at the index of the address in the array */
                    return this->__a_newAt ( pElement - this->_pData->_pFront + 1ULL );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeArray (
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement > this->_pData->_pBack ) {
                        return false;
                    }

                    if ( pElement == this->_pData->_pFront ) {

                        /* if address is of the first element, return new front array */
                        this->__a_newFrontArray (
                                count,
                                ppElements
                        );

                    } else if ( pElement == this->_pData->_pBack ) {

                        /* if address is after the last element, return new back */
                        this->__a_newBackArray (
                                count,
                                ppElements
                        );

                    } else {

                        /* otherwise, create a new element array of elements at the index of the address in the array */
                        this->__a_newArrayAt (
                                pElement - this->_pData->_pFront,
                                count,
                                ppElements
                        );

                    }

                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBeforeArrayConst (
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement > this->_pData->_pBack ) {
                        return false;
                    }

                    if ( pElement == this->_pData->_pFront ) {

                        /* if address is of the first element, return new front array */
                        this->__a_newFrontArray (
                                count,
                                ppElements
                        );

                    } else if ( pElement == this->_pData->_pBack ) {

                        /* if address is after the last element, return new back */
                        this->__a_newBackArray (
                                count,
                                ppElements
                        );

                    } else {

                        /* otherwise, create a new element array of elements at the index of the address in the array */
                        this->__a_newArrayAt (
                                pElement - this->_pData->_pFront,
                                count,
                                ppElements
                        );
                    }

                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterArray (
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement >= this->_pData->_pBack ) {
                        return false;
                    }

                    if ( pElement + 1ULL == this->_pData->_pBack ) {

                        /* if address is of the last element, return new back array */
                        this->__a_newBackArray (
                                count,
                                ppElements
                        );

                    } else {

                        /* otherwise, create a new element array of elements at the index of the address in the array */
                        this->__a_newArrayAt (
                                pElement - this->_pData->_pFront + 1ULL,
                                count,
                                ppElements
                        );
                    }

                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAfterArrayConst (
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool {

                    /* acquire address indicated by the iterator */
                    auto pElement = & iterator [0ULL];

                    /* if array is empty or address is out of bounds, no new element created */
                    if ( this->_pData == nullptr || pElement < this->_pData->_pFront || pElement >= this->_pData->_pBack ) {
                        return false;
                    }

                    if ( pElement + 1ULL == this->_pData->_pBack ) {

                        /* if address is of the last element, return new back array */
                        this->__a_newBackArray (
                                count,
                                ppElements
                        );

                    } else {

                        /* otherwise, create a new element array of elements at the index of the address in the array */
                        this->__a_newArrayAt (
                                pElement - this->_pData->_pFront + 1ULL,
                                count,
                                ppElements
                        );
                    }

                    /* regardless of branch, result is positive */
                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newAt (
                        Index index
                ) noexcept -> __ElementType * {

                    /* if empty, cannot insert at any index other than 0 */
                    if ( this->_pData == nullptr && index != 0 ) {
                        return nullptr;
                    }

                    /* needed to decide : the shift direction of current elements ( less move operations ), current capacity, current size */
                    auto const fullCapacity     = this->_pData->_frontCapacity + this->_pData->_backCapacity;
                    auto const size             = this->__a_size();

                    /* decision to shift is always right, based on lower argument */
                    auto const shouldShiftLeft  = static_cast < Size > ( index ) < size;
                    auto const canShiftLeft     = this->_pData->_pBuffer < this->_pData->_pFront;
                    auto       canShiftRight    = this->_pData->_pBack < this->_pData->_pBuffer + fullCapacity;

                    /* if it is not possible to shift any direction, reallocation required */
                    if ( ! canShiftLeft && ! canShiftRight ) {

                        /** choose to shift right always due to realloc being potentially faster. Reallocation in
                          * front requires a full memcpy of the array data
                          * investigation required as to what could be potentially faster */

                        /* realloc will always increase back capacity */
                        auto const pNewBuffer               = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        /* update allocation parameters. Potential new buffer due to realloc */
                        this->_pData->_pFront               = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack                = this->_pData->_pFront + size;
                        this->_pData->_backCapacity         = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity     = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer              = pNewBuffer;
                    }

                    /* based on possibility and intention, decide shift direction */
                    auto const shiftLeft =
                            canShiftLeft &&
                            shouldShiftLeft;

                    __ElementType * pDestination;
                    __ElementType * pSource;
                    Size            count;

                    if ( shiftLeft ) {

                        /* if left, destination is before front */
                        pDestination = -- this->_pData->_pFront;
                        pSource      = pDestination + 1ULL;
                        count        = index;

                    } else {

                        /* otherwise, destination is after given index */
                        pDestination = this->_pData->_pFront + index + 1;
                        pSource      = pDestination - 1ULL;
                        count        = size - static_cast < Size > ( index );

                        ++ this->_pData->_pBack;
                    }

                    /* apply memmove due to potential realloc, same buffer, potential overlap */
                    (void) std :: memmove (
                            reinterpret_cast < void * > ( pDestination ),
                            reinterpret_cast < void const * > ( pSource ),
                            sizeof ( __ElementType ) * count
                    );

                    /* the only uninitialized space will be at front + index. Return to be initialized */
                    return this->_pData->_pFront + index;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newArrayAt (
                        Index index,
                        Size count,
                        __ElementType ** ppElements
                ) noexcept -> void {

                    /* if empty, cannot insert at any index other than 0 */
                    if ( this->_pData == nullptr && index != 0 ) {
                        return;
                    }

                    /* needed to decide : the shift direction of current elements ( less move operations ), current capacity, current size */
                    auto const fullCapacity     = this->_pData->_frontCapacity + this->_pData->_backCapacity;
                    auto const size             = this->__a_size();

                    /* decision to shift is always right, based on lower argument */
                    auto const shouldShiftLeft  = static_cast < Size > ( index ) < size;
                    auto const canShiftLeft     = this->_pData->_pBuffer + count <= this->_pData->_pFront;
                    auto       canShiftRight    = this->_pData->_pBack + count <= this->_pData->_pBuffer + fullCapacity;

                    /* a special case exists when there is not enough space for a complete shift, but
                     * there is enough space to shift both ends to cover for the new required element count */
                    auto const canShiftBoth     = count + size <= fullCapacity;

                    /* if no shift possible, realloc */
                    if ( ! canShiftLeft && ! canShiftRight && ! canShiftBoth ) {

                        /** choose to shift right always due to realloc being potentially faster. Reallocation in
                          * front requires a full memcpy of the array data
                          * investigation required as to what could be potentially faster */

                        this->_pData->_backNextCapacity     = cds :: maxOf ( this->_pData->_backNextCapacity, count + this->_pData->_pBuffer + fullCapacity - this->_pData->_pBack );

                        /* realloc will always increase back capacity */
                        auto const pNewBuffer               = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backNextCapacity
                        );

                        /* update allocation parameters. Potential new buffer due to realloc */
                        this->_pData->_pFront               = pNewBuffer + ( this->_pData->_pFront - this->_pData->_pBuffer );
                        this->_pData->_pBack                = this->_pData->_pFront + size;
                        this->_pData->_backCapacity         = this->_pData->_backNextCapacity;
                        this->_pData->_backNextCapacity     = this->_pData->_backNextCapacity * 2ULL;
                        this->_pData->_pBuffer              = pNewBuffer;

                        /* since a realloc occurred, a shift can be done to the right */
                        canShiftRight                       = true;
                    }

                    /* will store the address of the start of the newly created element space */
                    __ElementType * pCreationSpace;

                    /* if complete shift can be done */
                    if ( canShiftLeft || canShiftRight ) {

                        /* based on possibility and intention, decide shift direction */
                        auto const shiftLeft =
                                canShiftLeft &&
                                shouldShiftLeft;

                        __ElementType * pDestination;
                        __ElementType * pSource;
                        Size            shiftCount;

                        if ( shiftLeft ) {

                            /* if left, destination is before front */
                            pDestination            = this->_pData->_pFront - count,
                            pSource                 = this->_pData->_pFront;
                            shiftCount              = index;

                            /* creation space will be at the source + index - count of the move, as those elements will be moved */
                            pCreationSpace          = pSource + index - count;
                            this->_pData->_pFront  -= count;

                        } else {

                            /* otherwise, destination is 'count' positions after given index, where count is the number of newly added elements */
                            pDestination            = this->_pData->_pFront + index + count;
                            pSource                 = this->_pData->_pFront + index;
                            shiftCount              = size - static_cast < Size > ( index );

                            /* creation space will be at the source of the move, as those elements will be moved */
                            pCreationSpace          = this->_pData->_pFront + index;
                            this->_pData->_pBack   += count;
                        }

                        /* apply memmove, as overlap is possible due to no/a potential realloc on the same buffer */
                        (void) std :: memmove (
                                reinterpret_cast < void * > ( pDestination ),
                                reinterpret_cast < void const * > ( pSource ),
                                sizeof ( __ElementType ) * shiftCount
                        );
                    } else {

                        /* otherwise, shifting both ways is possible. Always shift right more, as a next-right reallocation is more cost-effective due to realloc */
                        auto const rightShiftCount = count - ( this->_pData->_pBuffer + fullCapacity - this->_pData->_pBack );
                        /* remaining elements are shifted left */
                        auto const leftShiftCount  = count - rightShiftCount;

                        /* apply move right */
                        (void) std :: memmove (
                                reinterpret_cast < void * > (this->_pData->_pFront + index + rightShiftCount),
                                reinterpret_cast < void const * > (this->_pData->_pFront + index),
                                sizeof ( __ElementType ) * rightShiftCount
                        );

                        /* apply move left */
                        (void) std :: memmove (
                                reinterpret_cast < void * > (this->_pData->_pFront - leftShiftCount),
                                reinterpret_cast < void const * > (this->_pData->_pFront),
                                sizeof ( __ElementType ) * leftShiftCount
                        );

                        /* store the creation space, at front + index */
                        pCreationSpace          = this->_pData->_pFront + index;

                        /* update both front and back */
                        this->_pData->_pFront  -= leftShiftCount;
                        this->_pData->_pBack   += rightShiftCount;
                    }

                    /* for each of the newly created space, store the addresses to be returned via the out ppElements parameter */
                    for ( Size spaceIndex = 0ULL; spaceIndex < count; ++ spaceIndex ) {
                        ppElements [ spaceIndex ] = pCreationSpace ++;
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_begin () noexcept -> __a_Iterator {

                    /* forward begin iterator is at front, if applicable. nullptr otherwise */
                    return __a_Iterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_end () noexcept -> __a_Iterator {

                    /* forward end iterator is after back, if applicable. nullptr otherwise */
                    return __a_Iterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_cbegin () const noexcept -> __a_ConstIterator {

                    /* forward begin iterator is at front, if applicable. nullptr otherwise */
                    return __a_ConstIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_cend () const noexcept -> __a_ConstIterator {

                    /* forward end iterator is after back, if applicable. nullptr otherwise */
                    return __a_ConstIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_rbegin () noexcept -> __a_ReverseIterator {

                    /* backward begin iterator is at back, if applicable. nullptr otherwise */
                    return __a_ReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_rend () noexcept -> __a_ReverseIterator {

                    /* backward end iterator is before front, if applicable. nullptr otherwise */
                    return __a_ReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_crbegin () const noexcept -> __a_ConstReverseIterator {

                    /* backward begin iterator is at back, if applicable. nullptr otherwise */
                    return __a_ConstReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pBack - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_crend () const noexcept -> __a_ConstReverseIterator {

                    /* backward end iterator is before front, if applicable. nullptr otherwise */
                    return __a_ConstReverseIterator (
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront - 1ULL
                    );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_removeIterator (
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    /* Function called to remove an iterator, will call the base remove at index function */
                    /* acquire address of the element. */
                    auto const pElement = & iterator [ 0ULL ];

                    /* if invalid or out of bounds, not possible */
                    if ( this->_pData == nullptr || ! ( this->_pData->_pFront <= pElement && pElement < this->_pData->_pBack ) ) {
                        return false;
                    }

                    /* remove at index, acquired from element address - front address */
                    this->__a_remove ( static_cast < Index > ( pElement - this->_pData->_pFront ) );
                    /* successful at this point */
                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_removeConstIterator (
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> bool {

                    /* Function called to remove an iterator, will call the base remove at index function */
                    /* acquire address of the element. */
                    auto const pElement = & iterator [ 0ULL ];

                    /* if invalid or out of bounds, not possible */
                    if ( this->_pData == nullptr || ! ( this->_pData->_pFront <= pElement && pElement < this->_pData->_pBack ) ) {
                        return false;
                    }

                    /* remove at index, acquired from element address - front address */
                    this->__a_remove ( static_cast < Index > ( pElement - this->_pData->_pFront ) );
                    /* successful at this point */
                    return true;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_removeIteratorArray (
                        AbstractAddressIterator < __ElementType >   const * const * ppIterators,
                        Size                                                        iteratorCount
                ) noexcept -> Size {

                    /** removal of multiple iterators can go one of two ways
                     * 1. create a new buffer to move remaining elements, if capacity is twice more than remaining elements
                     * 2. move the remaining elements to the spaces previously occupied by the removed elements, keeping in mind that iterators point at in-array addresses
                     * regardless, the received iterator array will be ordered by their array order
                     * */

                    /* first test scenario 1, compute required size */
                    auto const  currentSize     = this->__a_size();
                    auto const  requiredSize    = currentSize - iteratorCount;
                    Size        iteratorIndex   = 0ULL;

                    /* if scenario 1 applicable */
                    if ( this->_pData->_frontCapacity + this->_pData->_backCapacity > cds :: maxOf ( requiredSize * 2ULL, __Array :: __a_minCapacity ) ) {

                        /* start with a buffer with no front capacity, only back, based on max ( min size, required )  */
                        this->_pData->_frontCapacity        = 0ULL;
                        this->_pData->_backCapacity         = cds :: maxOf ( __Array :: __a_minCapacity, requiredSize );
                        this->_pData->_frontNextCapacity    = __Array :: __a_minCapacity;
                        this->_pData->_backNextCapacity     = this->_pData->_backCapacity * 2ULL;

                        /* allocate a new smaller buffer */
                        auto pNewBuffer = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );

                        /* start with the new empty buffer */
                        auto pNewFront  = pNewBuffer;
                        auto pNewBack   = pNewFront;

                        /* parse current elements */
                        while ( this->_pData->_pFront != this->_pData->_pBack && iteratorIndex < iteratorCount ) {

                            if ( & ( * ( * ppIterators [ iteratorIndex ] ) ) == this->_pData->_pFront ) {

                                /* if address of element at iterator is equal to current element address, destroy element and go to next iterator */
                                this->_pData->_pFront->~__ElementType();
                                ++ iteratorIndex;
                            } else {

                                /* otherwise, move and increase the new back pointer */
                                (void) std :: memcpy (
                                        reinterpret_cast < void * > ( pNewBack ++ ),
                                        reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                        sizeof ( __ElementType )
                                );
                            }

                            /* go to next element, use current front pointer as current buffer will be discarded in the end */
                            ++ this->_pData->_pFront;
                        }

                        /* if all iterators have been consumed, move remaining elements */
                        if ( this->_pData->_pFront != this->_pData->_pBack ) {

                            auto const remaining = this->_pData->_pBack - this->_pData->_pFront;
                            (void) std :: memcpy (
                                    reinterpret_cast < void * > ( pNewBack ),
                                    reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                    sizeof ( __ElementType ) * ( remaining )
                            );

                            pNewBack += remaining;
                        }

                        /* update complete, discard old buffer and update front, back and buffer pointer values */
                        this->_pData->_pFront   = pNewFront;
                        this->_pData->_pBack    = pNewBack;
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange (
                                        this->_pData->_pBuffer,
                                        pNewBuffer
                                )
                        );

                        /* removed elements are acquired with difference between starting size and new size */
                        return currentSize - requiredSize;
                    }

                    /* otherwise, scenario 2. Start clearing at the front, while applicable. While
                     * iterators point to elements in front, remove and move to next. Also advance front in this
                     * scenario */
                    while ( iteratorIndex < iteratorCount && this->_pData->_pFront == & ( * ( * ppIterators [ iteratorIndex ] ) ) ) {
                        ( this->_pData->_pFront ++ )->~__ElementType ();
                        ++ iteratorIndex;
                    }

                    /* keep in mind the number of elements removed from the front */
                    auto const  frontRemoved    = iteratorIndex;

                    /* use two pointers, one for current inspected element, one for the last valid move location
                     * pCopyFront will always be behind or equal to pFront
                     * When they are equal, no move is done, as no elements have been yet removed
                     * When they are not equal, no overlap can happen as iterators will point to yet-unmoved locations */
                    auto        pFront          = this->_pData->_pFront;
                    auto        pCopyFront      = this->_pData->_pFront;

                    /* while iterators exist and array has not been completely parsed */
                    while ( pFront != this->_pData->_pBack && iteratorIndex < iteratorCount ) {

                        if ( pFront == & ( * ( * ppIterators [ iteratorIndex ] ) ) ) {

                            /* if current element is to be removed, destroy it and advance to the next iterator */
                            ( pFront )->~__ElementType ();
                            ++ iteratorIndex;
                        } else if ( pFront != pCopyFront ) {

                            /* if a removal was previously done, pCopyFront will be behind, and will always indicate to
                             * safe-to-copy, no overlap memory. Use memcpy. Increase pCopyFront to indicate the next
                             * safe-to-copy memory space */
                            (void) std :: memcpy (
                                    reinterpret_cast < void * > ( pCopyFront ++ ),
                                    reinterpret_cast < void const * > ( pFront ),
                                    sizeof ( __ElementType )
                            );
                        } else {

                            /* otherwise, no removal to do, no removal previously done, only advance pCopyFront */
                            pCopyFront ++;
                        }

                        /* always increase lookahead pointer */
                        ++ pFront;
                    }

                    /* if iterators are finished, but lookahead is incomplete, and there have been elements removed
                     * ( pCopyFront is different to pFront ), some elements still have to be moved */
                    if ( pFront != this->_pData->_pBack && pCopyFront != pFront ) {

                        /* remaining elements are determined with back - front */
                        auto const remaining = this->_pData->_pBack - pFront;

                        /* use memmove, potential overlap */
                        (void) std :: memmove (
                                reinterpret_cast < void * > ( pCopyFront ),
                                reinterpret_cast < void const * > ( pFront ),
                                sizeof ( __ElementType ) * remaining
                        );
                    }

                    /* removed at the back is determined by offset from copyFront and front. ( copyFront increased when no remove is done ) */
                    auto const backRemoved = pFront - pCopyFront;

                    /* elements have been shifted left, so decrease back pointer */
                    this->_pData->_pBack -= backRemoved;

                    /* removed = frontRemoved + backRemoved */
                    return backRemoved + frontRemoved;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_removeConstIteratorArray (
                        AbstractAddressIterator < __ElementType const > const * const * ppIterators,
                        Size                                                            iteratorCount
                ) noexcept -> Size {

                    /** removal of multiple iterators can go one of two ways
                     * 1. create a new buffer to move remaining elements, if capacity is twice more than remaining elements
                     * 2. move the remaining elements to the spaces previously occupied by the removed elements, keeping in mind that iterators point at in-array addresses
                     * regardless, the received iterator array will be ordered by their array order
                     * */

                    /* first test scenario 1, compute required size */
                    auto const  currentSize     = this->__a_size();
                    auto const  requiredSize    = currentSize - iteratorCount;
                    Size        iteratorIndex   = 0ULL;

                    /* if scenario 1 applicable */
                    if ( this->_pData->_frontCapacity + this->_pData->_backCapacity > cds :: maxOf ( requiredSize * 2ULL, __Array :: __a_minCapacity ) ) {

                        /* start with a buffer with no front capacity, only back, based on max ( min size, required )  */
                        this->_pData->_frontCapacity        = 0ULL;
                        this->_pData->_backCapacity         = cds :: maxOf ( __Array :: __a_minCapacity, requiredSize );
                        this->_pData->_frontNextCapacity    = __Array :: __a_minCapacity;
                        this->_pData->_backNextCapacity     = this->_pData->_backCapacity * 2ULL;

                        /* allocate a new smaller buffer */
                        auto pNewBuffer = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );

                        /* start with the new empty buffer */
                        auto pNewFront  = pNewBuffer;
                        auto pNewBack   = pNewFront;

                        /* parse current elements */
                        while ( this->_pData->_pFront != this->_pData->_pBack && iteratorIndex < iteratorCount ) {

                            if ( & ( * ( * ppIterators [ iteratorIndex ] ) ) == this->_pData->_pFront ) {

                                /* if address of element at iterator is equal to current element address, destroy element and go to next iterator */
                                this->_pData->_pFront->~__ElementType();
                                ++ iteratorIndex;
                            } else {

                                /* otherwise, move and increase the new back pointer */
                                (void) std :: memcpy (
                                        reinterpret_cast < void * > ( pNewBack ++ ),
                                        reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                        sizeof ( __ElementType )
                                );
                            }

                            /* go to next element, use current front pointer as current buffer will be discarded in the end */
                            ++ this->_pData->_pFront;
                        }

                        /* if all iterators have been consumed, move remaining elements */
                        if ( this->_pData->_pFront != this->_pData->_pBack ) {

                            auto const remaining = this->_pData->_pBack - this->_pData->_pFront;
                            (void) std :: memcpy (
                                    reinterpret_cast < void * > ( pNewBack ),
                                    reinterpret_cast < void const * > ( this->_pData->_pFront ),
                                    sizeof ( __ElementType ) * ( remaining )
                            );

                            pNewBack += remaining;
                        }

                        /* update complete, discard old buffer and update front, back and buffer pointer values */
                        this->_pData->_pFront   = pNewFront;
                        this->_pData->_pBack    = pNewBack;
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange (
                                        this->_pData->_pBuffer,
                                        pNewBuffer
                                )
                        );

                        /* removed elements are acquired with difference between starting size and new size */
                        return currentSize - requiredSize;
                    }

                    /* otherwise, scenario 2. Start clearing at the front, while applicable. While
                     * iterators point to elements in front, remove and move to next. Also advance front in this
                     * scenario */
                    while ( iteratorIndex < iteratorCount && this->_pData->_pFront == & ( * ( * ppIterators [ iteratorIndex ] ) ) ) {
                        ( this->_pData->_pFront ++ )->~__ElementType ();
                        ++ iteratorIndex;
                    }

                    /* keep in mind the number of elements removed from the front */
                    auto const  frontRemoved    = iteratorIndex;

                    /* use two pointers, one for current inspected element, one for the last valid move location
                     * pCopyFront will always be behind or equal to pFront
                     * When they are equal, no move is done, as no elements have been yet removed
                     * When they are not equal, no overlap can happen as iterators will point to yet-unmoved locations */
                    auto        pFront          = this->_pData->_pFront;
                    auto        pCopyFront      = this->_pData->_pFront;

                    /* while iterators exist and array has not been completely parsed */
                    while ( pFront != this->_pData->_pBack && iteratorIndex < iteratorCount ) {

                        if ( pFront == & ( * ( * ppIterators [ iteratorIndex ] ) ) ) {

                            /* if current element is to be removed, destroy it and advance to the next iterator */
                            ( pFront )->~__ElementType ();
                            ++ iteratorIndex;
                        } else if ( pFront != pCopyFront ) {

                            /* if a removal was previously done, pCopyFront will be behind, and will always indicate to
                             * safe-to-copy, no overlap memory. Use memcpy. Increase pCopyFront to indicate the next
                             * safe-to-copy memory space */
                            (void) std :: memcpy (
                                    reinterpret_cast < void * > ( pCopyFront ++ ),
                                    reinterpret_cast < void const * > ( pFront ),
                                    sizeof ( __ElementType )
                            );
                        } else {

                            /* otherwise, no removal to do, no removal previously done, only advance pCopyFront */
                            pCopyFront ++;
                        }

                        /* always increase lookahead pointer */
                        ++ pFront;
                    }

                    /* if iterators are finished, but lookahead is incomplete, and there have been elements removed
                     * ( pCopyFront is different to pFront ), some elements still have to be moved */
                    if ( pFront != this->_pData->_pBack ) {

                        /* remaining elements are determined with back - front */
                        auto const remaining = this->_pData->_pBack - pFront;

                        /* use memmove, potential overlap */
                        (void) std :: memmove (
                                reinterpret_cast < void * > ( pCopyFront ),
                                reinterpret_cast < void const * > ( pFront ),
                                sizeof ( __ElementType ) * remaining
                        );
                    }

                    /* removed at the back is determined by offset from copyFront and front. ( copyFront increased when no remove is done ) */
                    auto const backRemoved = pFront - pCopyFront;

                    /* elements have been shifted left, so decrease back pointer */
                    this->_pData->_pBack -= backRemoved;

                    /* removed = frontRemoved + backRemoved */
                    return backRemoved + frontRemoved;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_data () const noexcept -> __ElementType const * {

                    /* when applicable, return the address to the front of the buffer. Otherwise, nullptr as there is no data */
                    return
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_data () noexcept -> __ElementType * {

                    /* when applicable, return the address to the front of the buffer. Otherwise, nullptr as there is no data */
                    return
                            this->_pData == nullptr ?
                            nullptr                 :
                            this->_pData->_pFront;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDefaultConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_resize (
                        Size size
                ) noexcept -> void {

                    /* if no data exists, initialize allocation data */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    /* acquire current size */
                    auto const currentSize = this->__a_size();

                    /* clear elements found after the new end, if applicable ( new size < actual size ) */
                    for ( Size index = size; index < currentSize; ++ index ) {

                        /* decrease back, destroy each */
                        ( -- this->_pData->_pBack )->~__ElementType ();
                    }

                    /* acquire pointer at the actual buffer end */
                    auto const pEnd = this->_pData->_pBuffer + this->_pData->_backCapacity + this->_pData->_frontCapacity;

                    /* if size does not fit between front and actual memory end, reallocation required. Do not shift, as it is time-ineffective */
                    if ( size > pEnd - this->_pData->_pFront ) {

                        /* new back capacity is max ( next, size + required ) */
                        this->_pData->_backCapacity     = cds :: maxOf ( this->_pData->_backNextCapacity, this->_pData->_backCapacity + ( size - currentSize ) );
                        auto const pNewBuffer           = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_backCapacity + this->_pData->_backCapacity
                        );

                        /* update memory & allocation parameters */
                        this->_pData->_backNextCapacity = this->_pData->_backCapacity * 2ULL;
                        this->_pData->_pFront           = pNewBuffer + this->_pData->_pFront - this->_pData->_pBuffer;
                        this->_pData->_pBack            = pNewBuffer + this->_pData->_pBack - this->_pData->_pBuffer;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    /* initialize new memory space with default constructor,
                     * if applicable ( new size > actual size ) */
                    for ( Size index = currentSize; index < size; ++ index ) {
                        new ( this->_pData->_pBack ++ ) __ElementType ();
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_resize (
                        Size                    size,
                        __ElementType   const & defaultValue
                ) noexcept -> void {

                    /* if no data exists, initialize allocation data */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    }

                    /* acquire current size */
                    auto const currentSize = this->__a_size();

                    /* clear elements found after the new end, if applicable ( new size < actual size ) */
                    for ( Size index = size; index < currentSize; ++ index ) {

                        /* decrease back, destroy each */
                        ( -- this->_pData->_pBack )->~__ElementType ();
                    }

                    /* acquire pointer at the actual buffer end */
                    auto const pEnd = this->_pData->_pBuffer + this->_pData->_backCapacity + this->_pData->_frontCapacity;

                    /* if size does not fit between front and actual memory end, reallocation required. Do not shift, as it is time-ineffective */
                    if ( size > pEnd - this->_pData->_pFront ) {

                        /* new back capacity is max ( next, size + required ) */
                        this->_pData->_backCapacity     = cds :: maxOf ( this->_pData->_backNextCapacity, this->_pData->_backCapacity + ( size - currentSize ) );
                        auto const pNewBuffer           = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_backCapacity + this->_pData->_backCapacity
                        );

                        /* update memory & allocation parameters */
                        this->_pData->_backNextCapacity = this->_pData->_backCapacity * 2ULL;
                        this->_pData->_pFront           = pNewBuffer + this->_pData->_pFront - this->_pData->_pBuffer;
                        this->_pData->_pBack            = pNewBuffer + this->_pData->_pBack - this->_pData->_pBuffer;
                        this->_pData->_pBuffer          = pNewBuffer;
                    }

                    /* initialize new memory space with copy constructor with default value,
                     * if applicable ( new size > actual size ) */
                    for ( Size index = currentSize; index < size; ++ index ) {
                        new ( this->_pData->_pBack ++ ) __ElementType ( defaultValue );
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_shrink (
                        Size size
                ) noexcept -> void {

                    /* if no data exists, no shrink required */
                    if ( this->_pData == nullptr ) {
                        return;
                    }

                    /* acquire intended new back address */
                    auto pEnd = this->_pData->_pFront + size;

                    /* while actual back > new back */
                    while ( this->_pData->_pBack > pEnd ) {

                        /* destroy elements at back and decrease the back pointer */
                        ( -- this->_pData->_pBack )->~__ElementType ();
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_reserve (
                        Size size
                ) noexcept -> void {

                    if ( this->_pData == nullptr ) {

                        /* if nothing exists already, initialize */
                        this->__a_init();
                    } else if ( this->_pData->_backCapacity > size ) {

                        /* if buffer can already contain required element count and was previously initialized ( buffer exists ), do nothing */
                        return;
                    }

                    /* increase back capacity, reallocate buffer, but do not initialize elements */
                    this->_pData->_backCapacity = cds :: maxOf ( this->_pData->_backNextCapacity, size );
                    auto const pNewBuffer       = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                            this->_pData->_pBuffer,
                            this->_pData->_backCapacity + this->_pData->_frontCapacity
                    );

                    /* update memory parameters */
                    this->_pData->_pFront           = pNewBuffer + this->_pData->_pFront - this->_pData->_pBuffer;
                    this->_pData->_pBack            = pNewBuffer + this->_pData->_pBack - this->_pData->_pBuffer;
                    this->_pData->_backNextCapacity = this->_pData->_backCapacity * 2ULL;
                    this->_pData->_pBuffer          = pNewBuffer;
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_copy (
                        __Array const & array
                ) noexcept -> void {

                    /* if no memory data exists, initialize. Otherwise, clear only buffer data */
                    if ( this->_pData == nullptr ) {
                        this->__a_init();
                    } else {
                        this->__a_clear(false);
                    }

                    /* use copy without clear requirement, since cleanup was already done above */
                    this->__a_copyCleared ( array );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __TElementType,                                        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        >
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_copyCleared (
                        __Array const & array
                ) noexcept -> void {

                    /* acquire given array size */
                    auto const requiredSize = array.__a_size();

                    /* if elements do not fit */
                    if ( this->_pData->_frontCapacity + this->_pData->_backCapacity < requiredSize ) {

                        /* reallocate, as front space will not be created in copy */
                        this->_pData->_backCapacity = cds :: maxOf ( requiredSize, __Array :: __a_minCapacity );
                        this->_pData->_pBuffer      = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_backCapacity
                        );
                    } else {

                        /* otherwise, move elements at the front, all front space becomes space at the back */
                        this->_pData->_backCapacity += this->_pData->_frontCapacity;
                    }

                    /* update memory parameters */
                    this->_pData->_backNextCapacity     = this->_pData->_backCapacity * 2ULL;
                    this->_pData->_frontCapacity        = 0ULL;
                    this->_pData->_frontNextCapacity    = __Array :: __a_minCapacity;
                    this->_pData->_pFront               = this->_pData->_pBuffer;
                    this->_pData->_pBack                = this->_pData->_pBuffer + requiredSize;

                    /* copy one-by-one with copy constructor */
                    for ( Size index = 0ULL; index < requiredSize; ++ index ) {
                        new ( this->_pData->_pFront + index ) __ElementType ( * ( array._pData->_pFront + index ) );
                    }
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __Array <
                        __ElementType,
                        __equals
                > :: __a_move (
                        __Array && array
                ) noexcept -> void {

                    /* clear whole memory contents, including memory data */
                    this->__a_clear ( true );

                    /* use move cleared */
                    this->__a_moveCleared ( std :: move ( array ) );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __Array <
                        __ElementType,
                        __equals
                > :: __a_moveCleared (
                        __Array && array
                ) noexcept -> void {

                    /* acquire memory data of given array. */
                    this->_pData = cds :: exchange ( array._pData, nullptr );
                }


                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __Array <
                        __ElementType,
                        __equals
                > :: __a_equals (
                        __Array const & array
                ) const noexcept -> bool {

                    /* self comparison, memory data can be used directly to check the case of null arrays */
                    if ( this->_pData == array._pData ) {
                        return true;
                    }

                    /* if only one is not initialized, not equal */
                    if ( this->_pData == nullptr || array._pData == nullptr ) {
                        return false;
                    }

                    auto const thisSize     = this->__a_size();
                    auto const otherSize    = array.__a_size();

                    /* different sizes => not equal */
                    if ( thisSize != otherSize ) {
                        return false;
                    }

                    /* otherwise, start parsing */
                    auto const thisFront    = this->_pData->_pFront;
                    auto const otherFront   = array._pData->_pFront;

                    /* equal in size, so only use this array's end as parse limit */
                    while ( thisFront != this->_pData->_pBack ) {

                        /* if any element is not equal to the other, not equal */
                        if ( ! __equals ( * thisFront, * otherFront ) ) {
                            return false;
                        }

                        /* otherwise, go ahead in both arrays */
                        ++ thisFront;
                        ++ otherFront;
                    }

                    /* parse ended and no return => all elements are equal */
                    return true;
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_ARRAY_IMPL_HPP__ */
