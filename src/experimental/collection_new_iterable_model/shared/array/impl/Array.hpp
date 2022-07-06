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

                    for (
                            Size
                                    index   = this->_pData->_bufferOffset,
                                    length  = this->_pData->_elementCount + this->_pData->_bufferOffset;

                            index < length;
                            ++ index
                    ) {
                        this->_pData->_pBuffer [ index ].~__ElementType ();
                    }

                    if ( destroyBuffer ) {

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pData->_pBuffer );
                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( this->_pData );
                    } else {

                        this->_pData->_bufferOffset = this->_pData->_frontCapacity;
                        this->_pData->_elementCount = 0ULL;
                    }
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __Array <
                        __ElementType,
                        __equals
                > :: __a_size () const noexcept -> Size {

                    return this->_pData == nullptr ? 0ULL : this->_pData->_elementCount;
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

                    if ( this->__a_size() == 0ULL ) {
                        return;
                    }

                    if ( index == 0ULL ) {

                        this->_pData->_pBuffer [ this->_pData->_bufferOffset ++ ].~__ElementType ();
                        -- this->_pData->_elementCount;
                        return;
                    } else if ( index == this->_pData->_elementCount - 1ULL ) {

                        this->_pData->_pBuffer [ this->_pData->_bufferOffset + -- this->_pData->_elementCount ].~__ElementType ();
                        return;
                    }

                    this->_pData->_pBuffer [ index ].~__ElementType ();
                    auto shiftLeftSide = static_cast < Size > ( index ) < ( this->_pData->_elementCount + this->_pData->_bufferOffset  ) / 2;

                    ElementType * pDestination  = nullptr;
                    ElementType * pSource       = nullptr;
                    Size          count         = 0ULL;

                    if ( shiftLeftSide ) {
                        pDestination = this->_pData->_pBuffer + this->_pData->_bufferOffset + 1ULL;
                        pSource      = pDestination - 1ULL;
                        count        = static_cast < Size > ( index );

                        ++ this->_pData->_bufferOffset;
                    } else {
                        pDestination = this->_pData->_pBuffer + this->_pData->_bufferOffset + static_cast < Size > ( index );
                        pSource      = pDestination + 1ULL;
                        count        = this->_pData->_elementCount - static_cast < Size > ( index );
                    }

                    (void) std :: memcpy (
                            pDestination,
                            pSource,
                            count * sizeof ( __ElementType )
                    );

                    -- this->_pData->_elementCount;
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

                    return & this->_pData->_pBuffer [ this->_pData->_bufferOffset + static_cast < Size > ( index ) ];
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

                    return & this->_pData->_pBuffer [ this->_pData->_bufferOffset + static_cast < Size > ( index ) ];
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newFront () noexcept -> ElementType * {

                    if ( this->_pData == nullptr ) {
                        this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                        (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                        this->_pData->_frontNextCapacity = __Array :: __a_minCapacity;
                    }

                    if ( this->_pData->_bufferOffset == 0ULL ) {

                        this->_pData->_frontCapacity        = cds :: maxOf ( this->_pData->_frontNextCapacity, __Array :: __a_minCapacity );
                        this->_pData->_frontNextCapacity    = 2ULL * this->_pData->_frontCapacity;

                        auto pNewBuffer = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );

                        this->_pData->_bufferOffset          = this->_pData->_frontCapacity;

                        (void) std :: memcpy (
                                pNewBuffer + this->_pData->_bufferOffset,
                                this->_pData->_pBuffer,
                                sizeof ( __ElementType ) * this->_pData->_elementCount
                        );

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    ++ this->_pData->_elementCount;
                    return & this->_pData->_pBuffer [ -- this->_pData->_bufferOffset ];
                }


                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > auto __Array <
                        __ElementType,
                        __equals
                > :: __a_newBack () noexcept -> ElementType * {

                    if ( this->_pData == nullptr ) {
                        this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                        (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                        this->_pData->_backNextCapacity = __Array :: __a_minCapacity;
                    }

                    if ( this->_pData->_elementCount - ( this->_pData->_frontCapacity - this->_pData->_bufferOffset ) >= this->_pData->_backCapacity ) {
                        this->_pData->_backCapacity     = cds :: maxOf ( this->_pData->_backNextCapacity, __Array :: __a_minCapacity );
                        this->_pData->_backNextCapacity = 2ULL * this->_pData->_backNextCapacity;

                        this->_pData->_pBuffer = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );
                    }

                    return & this->_pData->_pBuffer [ this->_pData->_bufferOffset + this->_pData->_elementCount ++ ];
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
                        this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                        (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                        this->_pData->_frontNextCapacity = __Array :: __a_minCapacity;
                    }

                    if ( this->_pData->_bufferOffset < count ) {

                        auto oldFrontCapacity               = this->_pData->_frontCapacity;
                        this->_pData->_frontCapacity        = cds :: maxOf ( this->_pData->_frontNextCapacity, count + this->_pData->_frontCapacity, __Array :: __a_minCapacity );
                        this->_pData->_frontNextCapacity    = 2ULL * this->_pData->_frontCapacity;

                        auto pNewBuffer = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > (
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );

                        auto oldOffset                      = this->_pData->_bufferOffset;
                        this->_pData->_bufferOffset        += this->_pData->_frontCapacity - oldFrontCapacity;

                        (void) std :: memcpy (
                                pNewBuffer + this->_pData->_bufferOffset,
                                this->_pData->_pBuffer + oldOffset,
                                sizeof ( __ElementType ) * this->_pData->_elementCount
                        );

                        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                                cds :: exchange ( this->_pData->_pBuffer, pNewBuffer )
                        );
                    }

                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ count - index - 1ULL ] = & this->_pData->_pBuffer [ -- this->_pData->_bufferOffset ];
                    }

                    this->_pData->_elementCount += count;
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
                        this->_pData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __ArrayImplDataContainer > ();
                        (void) std :: memset ( this->_pData, 0, sizeof ( __ArrayImplDataContainer ) );

                        this->_pData->_backNextCapacity = __Array :: __a_minCapacity;
                    }

                    if ( this->_pData->_elementCount + count - ( this->_pData->_frontCapacity - this->_pData->_bufferOffset ) > this->_pData->_backCapacity ) {

                        this->_pData->_backCapacity     = cds :: maxOf ( this->_pData->_backNextCapacity, count + this->_pData->_backCapacity, __Array :: __a_minCapacity );
                        this->_pData->_backNextCapacity = 2ULL * this->_pData->_backNextCapacity;

                        this->_pData->_pBuffer = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                this->_pData->_pBuffer,
                                this->_pData->_frontCapacity + this->_pData->_backCapacity
                        );
                    }

                    for ( Size index = 0ULL; index < count; ++ index ) {
                        ppElements [ index ] = & this->_pData->_pBuffer [ this->_pData->_bufferOffset + this->_pData->_elementCount ++ ];
                    }
                }

            }
        }
    }
}

#endif // __CDS_SHARED_ARRAY_IMPL_HPP__
