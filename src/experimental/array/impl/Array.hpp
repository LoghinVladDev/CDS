//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_IMPL_HPP__
#define __CDS_ARRAY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Size const Array < __ElementType > :: minCapacity;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > {

            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                    return Memory :: instance().create < ArrayDelegateIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: ForwardEnd:
                    return Memory :: instance().create < ArrayDelegateIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < ArrayDelegateIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < ArrayDelegateIterator > ( this, -1, false );
            }

            return nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                    return Memory :: instance().create < ArrayDelegateConstIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: ForwardEnd:
                    return Memory :: instance().create < ArrayDelegateConstIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < ArrayDelegateConstIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < ArrayDelegateConstIterator > ( this, -1, false );
            }

            return nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: initializeByCopy (
                Array < __ElementType > const & array
        ) noexcept -> void {

            static_assert ( meta :: isCopyConstructible < __ElementType > (), "Cannot copy an array of given Type, Type has no Copy Constructor" );
            for ( Index i = 0; i < static_cast < Index > ( array.size() ); ++ i ) {
                this->_pData[i].construct ( array._pData[i]->data() );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline Array < __ElementType > :: Array (
                Array < __ElementType > const & array
        ) noexcept :
                List < __ElementType > ( array ),
                _capacity ( maxOf ( array.List < __ElementType > :: size(), Array :: minCapacity ) ),
                _pData ( array.List < __ElementType > :: empty() ? nullptr : cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( maxOf ( array.List < __ElementType > :: size(), Array :: minCapacity ) ) ){

            this->initializeByCopy ( array );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Array < __ElementType > :: Array (
                Array < __ElementType > && array
        ) noexcept :
                List < __ElementType > ( cds :: forward < List < __ElementType > > ( array ) ),
                _pData ( cds :: exchange ( array._pData, nullptr ) ),
                _capacity ( cds :: exchange ( array._capacity, 0ULL ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                __IteratorType const & begin,
                __IteratorType const & end
        ) noexcept {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->pushBack ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                InitializerList const & initializerList
        ) noexcept :
                List < __ElementType > ( static_cast < Size > ( initializerList.size() ) ),
                _capacity ( maxOf ( initializerList.size(), Array :: minCapacity ) ),
                _pData ( initializerList.size() == 0ULL ? nullptr : cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( maxOf ( initializerList.size(), Array :: minCapacity ) ) ) {

            Index i = 0;
            for ( auto const & element : initializerList ) {
                this->_pData [ i ++ ].construct ( element );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                Size size
        ) noexcept :
                List < __ElementType > ( size ),
                _capacity ( maxOf ( size, Array :: minCapacity ) ),
                _pData ( size == 0ULL ? nullptr : cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( maxOf ( size, Array :: minCapacity ) ) ) {

            for ( Index index = 0; index < this->size(); ++ index ) {
                this->_pData [ index ].construct ();
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                Size                size,
                ElementType const & defaultValue
        ) noexcept :
                List < __ElementType > ( size ),
                _capacity ( maxOf ( size, Array :: minCapacity ) ),
                _pData ( size == 0ULL ? nullptr : cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( maxOf ( size, Array :: minCapacity ) ) ) {

            for ( Index index = 0; index < this->size(); ++ index ) {
                this->_pData [ index ].construct ( defaultValue );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                Collection < __OtherElementType > const & collection
        ) noexcept :
                List < __ElementType > ( collection.size() ),
                _capacity ( maxOf ( collection.size(), Array :: minCapacity ) ),
                _pData ( collection.empty() ? nullptr : cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( maxOf ( collection.size(), Array :: minCapacity ) ) ) {

            Index index = 0;
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator, ++ index ) {
                this->_pData [ index ].construct ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: ~Array () noexcept {
            for ( Index i = 0U; i < this->_size; ++ i ) {
                this->_pData [i].destruct();
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pData );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: resize (
                Size size
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                this->_pData [ index ].destruct();
            }

            for ( Size index = this->size(); index < minOf ( size, this->_capacity ); ++ index ) {
                this->_pData [ index ].construct ();
            }

            this->_size = size;
            auto newCapacity = maxOf ( size, Array :: minCapacity );

            if ( newCapacity == this->_capacity ) {
                return;
            }

            this->_pData = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray < __ElementType * > ( this->_pData, newCapacity );

            for ( Size index = minOf ( size, this->_capacity ); index < size; ++ index ) {
                this->_pData [ index ].construct();
            }

            this->_capacity = newCapacity;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: resize (
                Size                size,
                ElementType const & defaultValue
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                this->_pData [ index ].destruct();
            }

            for ( Size index = this->size(); index < minOf ( size, this->_capacity ); ++ index ) {
                this->_pData [ index ].construct ( defaultValue );
            }

            this->_size = size;
            auto newCapacity = maxOf ( size, Array :: minCapacity );

            if ( newCapacity == this->_capacity ) {
                return;
            }

            this->_pData = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray < __ElementType * > ( this->_pData, newCapacity );

            for ( Size index = minOf ( size, this->_capacity ); index < size; ++ index ) {
                this->_pData [ index ].construct ( defaultValue );
            }

            this->_capacity = newCapacity;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: shrink (
                Size size
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                this->_pData [ index ].destruct();
            }

            this->_size = minOf ( size, this->size() );

            if ( size == this->_capacity ) {
                return;
            }

            auto newCapacity = maxOf ( minOf ( this->_capacity, size ), Array :: minCapacity );
            this->_pData = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray < __ElementType * > ( this->_pData, newCapacity );

            this->_capacity = newCapacity;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( index < 0 || index >= this->_size ) {
                return false;
            }

            this->_pData [ index ].destruct();

            if ( this->size() * 2 > this->_capacity || this->_capacity <= Array :: minCapacity ) {

                std :: memcpy (
                        this->_pData + index,
                        this->_pData + index + 1,
                        sizeof ( NodeType ) * ( this->_size - index - 1 )
                );

                -- this->_size;
                return true;
            }

            auto newBuf = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( this->size() - 1 );
            (void) std::memcpy ( newBuf, this->_pData, index * sizeof ( NodeType ) );
            (void) std::memcpy ( newBuf + index, this->_pData + index + 1, ( this->size() - index - 1 ) * sizeof ( NodeType ) );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( exchange ( this->_pData, newBuf ) );

            this->_capacity = -- this->_size;
            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Collection < Index > const & indices
        ) noexcept -> Size {

            if ( indices.empty() || this->empty() ) {
                return 0U;
            }

            auto pUsedValues = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType * > ( this->size() );
            Size newLen = 0U;

            for ( Index index = 0, len = static_cast < Index > ( this->size() ); index < len; ++ index ) {
                if ( ! indices.contains ( index ) ) {
                    pUsedValues [ newLen ++ ] = & this->_pData [ index ];
                } else {
                    this->_pData [ index ].destruct();
                }
            }

            this->_capacity = maxOf ( newLen, Array :: minCapacity );
            auto adjustedBuf    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( this->_capacity );
            auto removedCount   = this->size() - newLen;

            this->_size = 0ULL;
            for ( Size index = 0ULL; index < newLen; ++ index ) {

                (void) std :: memcpy (
                        & this->_pData [ this->_size ++ ]._data,
                        pUsedValues [ index ]->_data,
                        sizeof ( NodeType )
                );
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( cds :: exchange ( this->_pData, adjustedBuf ) );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pUsedValues );

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                std :: initializer_list < Index > const & indices
        ) noexcept -> Size {

            if ( indices.size() == 0ULL || this->empty() ) {
                return 0U;
            }

            auto pUsedValues = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType * > ( this->size() );
            Size newLen = 0U;

            for ( Index index = 0, len = static_cast < Index > ( this->size() ); index < len; ++ index ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( indices, index ) ) {
                    pUsedValues [ newLen ++ ] = & this->_pData [ index ];
                } else {
                    this->_pData [ index ].destruct();
                }
            }

            this->_capacity = maxOf ( newLen, Array :: minCapacity );
            auto adjustedBuf    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( this->_capacity );
            auto removedCount   = this->size() - newLen;

            this->_size = 0ULL;
            for ( Size index = 0ULL; index < newLen; ++ index ) {

                (void) std :: memcpy (
                        & this->_pData [ this->_size ++ ]._data,
                        pUsedValues [ index ]->_data,
                        sizeof ( NodeType )
                );
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( cds :: exchange ( this->_pData, adjustedBuf ) );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pUsedValues );

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->removeAt ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->removeAt ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->removeAt ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->removeAt ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            Array < Index > indices;
            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->removeAt ( indices );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Array < Index > indices;
            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->removeAt ( indices );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Array < Index > indices;
            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->removeAt ( indices );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Array < Index > indices;
            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->removeAt ( indices );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                Index index
        ) noexcept -> ElementType * {

            if ( this->_size < this->_capacity ) {
                (void) std :: memmove (
                        this->_pData + index + 1,
                        this->_pData + index,
                        sizeof ( NodeType ) * ( this->_size - index )
                );

                ++ this->_size;
                return & this->_pData [ index ].data();
            }

            auto newCap = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( newCap );

            (void) std :: memcpy ( newBuf, this->_pData, sizeof ( NodeType ) * index );
            (void) std :: memcpy ( newBuf + index + 1, this->_pData + index, sizeof ( NodeType ) * ( static_cast < Index > ( this->_size ) - index ) );

            this->_capacity = newCap;
            ++ this->_size;
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( cds :: exchange ( this->_pData, newBuf ) );

            return & this->_pData [ index ].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                Index index
        ) noexcept -> ElementType * {

            if ( this->_size < this->_capacity ) {
                (void) std :: memmove (
                        this->_pData + index + 2,
                        this->_pData + index + 1,
                        sizeof ( NodeType ) * ( this->_size - index - 1 )
                );

                ++ this->_size;
                return & this->_pData [ index + 1 ].data();
            }

            auto newCap = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( newCap );

            (void) std :: memcpy ( newBuf, this->_pData, sizeof ( NodeType ) * ( index + 1 ) );
            (void) std :: memcpy ( newBuf + index + 2, this->_pData + index + 1, sizeof ( NodeType ) * ( static_cast < Index > ( this->_size ) - index - 1 ) );

            this->_capacity = newCap;
            ++ this->_size;
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( cds :: exchange ( this->_pData, newBuf ) );

            return & this->_pData [ index + 1 ].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBack () noexcept -> ElementType * {

            if ( this->_size < this->_capacity ) {
                return & this->_pData [ this->_size ++ ].data();
            }

            this->_capacity = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            this->_pData = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray < NodeType > ( this->_pData, this->_capacity );

            return & this->_pData [ this->_size ++ ].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewFront () noexcept -> ElementType * {

            if ( this->_size < this->_capacity ) {

                (void) std :: memmove ( this->_pData + 1, this->_pData, sizeof ( NodeType ) * this->_size );
                ++ this->_size;

                return & this->_pData[0].data();
            }

            auto newSize = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( newSize );
            (void) std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( NodeType ) );
            (void) std::memset ( newBuf + 1 + this->_size, 0, ( newSize - this->_size - 1 ) * sizeof ( NodeType ) );

            this->_capacity = newSize;
            this->_size ++;
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( exchange ( this->_pData, newBuf ) );

            return & this->_pData[0].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                Iterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                Iterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ConstIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ConstIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return this->_pData[0].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return this->_pData[0].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return this->_pData[this->_size - 1].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return this->_pData[this->_size - 1].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            if (index < 0 ) {
                index += (this->size() / (-index) ) * this->size();
            }

            if (index >= static_cast<Index>(this->size()) ) {
                index = index % this->size();
            }

            return this->_pData [ index ].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            if (index < 0 ) {
                index += (this->size() / (-index) ) * this->size();
            }

            if (index >= static_cast<Index>(this->size()) ) {
                index = index % this->size();
            }

            return this->_pData[index].data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: operator == (
                Array const & array
        ) const noexcept -> bool {

            if ( this == & array ) {
                return true;
            }

            if ( this->size() != array.size() ) {
                return false;
            }

            for ( Index parseIndex = 0; parseIndex < this->size(); ++ parseIndex ) {
                if ( ! meta :: equals ( this->_pData [ parseIndex ].data(), array._pData [ parseIndex ].data() ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: operator != (
                Array const & array
        ) const noexcept -> bool {

            return ! this->operator == ( array );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: clear () noexcept -> void {

            for ( Index i = 0; i < this->_size; ++ i ) {
                this->_pData [ i ].destruct();
            }

            this->_size = 0;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: makeUnique () noexcept -> void {

            auto pNewData = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > ( cds :: maxOf (this->size(), Array :: minCapacity ) );
            Size newLength = 0u;

            auto newArrContains = [](
                    NodeType          * pNodes,
                    Size                arrayLength,
                    NodeType    const & element
            ) noexcept -> bool {
                for (Size i = 0u; i < arrayLength; ++ i ) {
                    if ( meta :: equals ( pNodes[i].data(), element.data() ) ) {
                        return true;
                    }
                }

                return false;
            };

            for ( Index i = 0; i < this->size(); ++ i ) {
                if ( ! newArrContains ( pNewData, newLength, this->_pData[i] ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    (void) std :: memcpy (
                            pNewData [ i ]._data,
                            this->_pData [ i ]._data,
                            sizeof ( NodeType )
                    );
                } else {
                    this->_pData [ i ].destruct();
                }
            }

            (void) std :: memset (pNewData + newLength, 0, ( this->size() - newLength ) * sizeof ( NodeType ) );

            this->_capacity = this->size();
            this->_size     = newLength;

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( exchange ( this->_pData, pNewData ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popFront () noexcept -> void {

            if ( this->empty() ) {
                return;
            }

            this->_pData [0].destruct();

            (void) std :: memcpy (
                    this->_pData,
                    this->_pData + 1,
                    sizeof ( NodeType ) * ( this->_size - 1 )
            );

            -- this->_size;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popBack () noexcept -> void {

            if ( this->empty() ) {
                return;
            }

            this->_pData [ -- this->_size ].destruct();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: operator = (
                Array const & array
        ) noexcept -> Array & {

            if ( this == & array ) {
                return * this;
            }

            this->clear();

            this->_capacity = maxOf ( array.size(), Array :: minCapacity );
            this->_size     = array.size();
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                    exchange (
                            this->_pData,
                            cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > (
                                    this->_capacity
                            )
                    )
            );

            for ( Size index = 0; index < array.size(); ++ index ) {
                this->_pData [ index ].construct ( array._pData [ index ].data() );
            }

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: operator = (
                Array && array
        ) noexcept -> Array & {

            if ( this == & array ) {
                return * this;
            }

            this->clear();

            this->_capacity = exchange ( array._capacity, 0ULL );
            this->_size     = exchange ( array._size, 0ULL );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                    cds :: exchange (
                            this->_pData,
                            cds :: exchange (
                                    array._pData,
                                    nullptr
                            )
                    )
            );

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> Array & {

            if ( this == & collection ) {
                return * this;
            }

            this->clear();

            this->_capacity = maxOf ( collection.size(), Array :: minCapacity );
            this->_size     = collection.size();
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                    cds :: exchange (
                            this->_pData,
                            cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < NodeType > (
                                    this->_capacity
                            )
                    )
            );

            Size index = 0ULL;
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator, ++ index ) {
                this->_pData [ index ].construct ( * iterator );
            }

            return * this;
        }

    }
}

#endif // __CDS_ARRAY_IMPL_HPP__
