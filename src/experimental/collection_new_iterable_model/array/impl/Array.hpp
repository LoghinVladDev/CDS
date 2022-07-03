//
// Created by loghin on 7/2/22.
//

#ifndef __CDS_EX_ARRAY_IMPL_HPP__
#define __CDS_EX_ARRAY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Size const Array < __ElementType > :: minCapacity;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> void ( Collection < __ElementType > :: * ) () {

            return this->__ls_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> void ( Collection < __ElementType > :: * ) () const {

            return this->__ls_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Array < __ElementType > :: Array () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: ~Array () noexcept {

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

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pData->_pBuffer );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( this->_pData );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: clear () noexcept -> void {

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

            this->_pData->_bufferOffset = this->_pData->_frontCapacity;
            this->_pData->_elementCount = 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: size () const noexcept -> Size {

            return this->_pData == nullptr ? 0ULL : this->_pData->_elementCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popFront () noexcept -> void {

            if ( this->empty() ) {
                return;
            }

            this->_pData->_pBuffer [ this->_pData->_bufferOffset ++ ].~__ElementType ();
            -- this->_pData->_elementCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popBack () noexcept -> void {

            if ( this->empty() ) {
                return;
            }

            this->_pData->_pBuffer [ this->_pData->_bufferOffset + -- this->_pData->_elementCount ].~__ElementType ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset + this->_pData->_elementCount - 1ULL ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset + this->_pData->_elementCount - 1ULL ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            if ( index < 0 ) {
                index += ( this->size() / (-index) ) * this->size();
            }

            if ( index >= static_cast < Index > ( this->size() ) ) {
                index = index % this->size();
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset + index ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return this->_pData->_pBuffer [ this->_pData->_bufferOffset + this->circularAdjustedIndex ( index ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( this->empty() ) {
                return false;
            }

            index = this->circularAdjustedIndex ( index );
            this->_pData->_pBuffer [ index ].~__ElementType ();

            auto const totalCapacity = this->_pData->_backCapacity + this->_pData->_frontCapacity;
            if ( this->_pData->_elementCount * 2ULL > totalCapacity ) {
                (void) std :: memcpy (
                        this->_pData->_pBuffer + this->_pData->_bufferOffset + index,
                        this->_pData->_pBuffer + this->_pData->_bufferOffset + index + 1,
                        sizeof ( ElementType ) * ( this->_pData->_elementCount - index - 1 )
                );

                -- this->_pData->_elementCount;
                return true;
            }

            auto newBackCapacity = cds :: minOf ( this->_pData->_elementCount - 1ULL, Array :: minCapacity );
            auto newBuffer = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType > ( newBackCapacity );
            (void) std :: memcpy (
                    newBuffer,
                    this->_pData->_pBuffer + this->_pData->_bufferOffset,
                    sizeof ( __ElementType ) * index
            );

            (void) std :: memcpy (
                    newBuffer + index,
                    this->_pData->_pBuffer + this->_pData->_bufferOffset + index + 1,
                    sizeof ( ElementType ) * ( this->_pData->_elementCount - index - 1 )
            );

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( cds :: exchange ( this->_pData->_pBuffer, newBuffer ) );

            --this->_pData->_elementCount;
            this->_pData->_backCapacity         = newBackCapacity;
            this->_pData->_backNextCapacity     = this->_pData->_backCapacity * 2ULL;
            this->_pData->_frontCapacity        = 0ULL;
            this->_pData->_frontNextCapacity    = Array :: minCapacity;
            this->_pData->_bufferOffset         = 0ULL;
            return true;
        }

    }
}

#endif // __CDS_EX_ARRAY_IMPL_HPP__
