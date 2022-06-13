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
                this->_pData[i] = Memory :: instance().create < __ElementType > ( * array._pData[i] );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline Array < __ElementType > :: Array (
                Array < __ElementType > const & array
        ) noexcept :
                List < __ElementType > ( array ),
                _capacity ( maxOf ( array.List < __ElementType > :: size(), Array :: minCapacity ) ),
                _pData ( array.List < __ElementType > :: empty() ? nullptr : Memory :: instance().createArray < __ElementType * > ( maxOf ( array.List < __ElementType > :: size(), Array :: minCapacity ) ) ){

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
                _pData ( Memory :: instance().createArray < __ElementType * > ( maxOf ( initializerList.size(), Array :: minCapacity ) ) ) {

            Index i = 0;
            for ( auto const & element : initializerList ) {
                this->_pData [ i ++ ] = Memory :: instance().create < __ElementType > ( element );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                Size size
        ) noexcept :
                List < __ElementType > ( size ),
                _capacity ( maxOf ( size, Array :: minCapacity ) ),
                _pData ( Memory :: instance().createArray < __ElementType * > ( maxOf ( size, Array :: minCapacity ) ) ) {

            for ( Index index = 0; index < this->size(); ++ index ) {
                this->_pData [ index ] = Memory :: instance().create < __ElementType > ();
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
                _pData ( Memory :: instance().createArray < __ElementType * > ( maxOf ( size, Array :: minCapacity ) ) ) {

            for ( Index index = 0; index < this->size(); ++ index ) {
                this->_pData [ index ] = Memory :: instance().create < __ElementType > ( defaultValue );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: Array (
                Collection < __OtherElementType > const & collection
        ) noexcept :
                List < __ElementType > ( collection.size() ),
                _capacity ( maxOf ( collection.size(), Array :: minCapacity ) ),
                _pData ( Memory :: instance().createArray < __ElementType * > ( maxOf ( collection.size(), Array :: minCapacity ) ) ) {

            Index index = 0;
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator, ++ index ) {
                this->_pData [ index ] = Memory :: instance().create < __ElementType > ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: ~Array () noexcept {
            for ( Index i = 0U; i < this->_size; ++ i ) {
                Memory :: instance().destroy ( this->_pData[i] );
            }

            Memory :: instance().destroyArray ( this->_pData );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isDefaultConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: resize (
                Size size
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                delete exchange ( this->_pData[index], nullptr );
            }

            for ( Size index = this->size(); index < minOf ( size, this->_capacity ); ++ index ) {
                this->_pData[index] = Memory :: instance().create < __ElementType > ();
            }

            this->_size = size;
            auto newCapacity = maxOf ( size, Array :: minCapacity );

            if ( newCapacity == this->_capacity ) {
                return;
            }

            auto newBuffer = Memory :: instance().createArray < __ElementType * > ( newCapacity );
            for ( Size index = 0; index < minOf ( size, this->_capacity ); ++ index ) {
                newBuffer [ index ] = this->_pData [ index ];
            }

            for ( Size index = minOf ( size, this->_capacity ); index < size; ++ index ) {
                newBuffer [ index ] = Memory :: instance().create < __ElementType > ();
            }

            this->_capacity = newCapacity;
            Memory :: instance().destroyArray ( exchange ( this->_pData, newBuffer ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: resize (
                Size                size,
                ElementType const & defaultValue
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                delete exchange ( this->_pData[index], nullptr );
            }

            for ( Size index = this->size(); index < minOf ( size, this->_capacity ); ++ index ) {
                this->_pData[index] = Memory :: instance().create < __ElementType > ( defaultValue );
            }

            this->_size = size;
            auto newCapacity = maxOf ( size, Array :: minCapacity );

            if ( newCapacity == this->_capacity ) {
                return;
            }

            auto newBuffer = Memory :: instance().createArray < __ElementType * > ( newCapacity );
            for ( Size index = 0; index < minOf ( size, this->_capacity ); ++ index ) {
                newBuffer [ index ] = this->_pData [ index ];
            }

            for ( Size index = minOf ( size, this->_capacity ); index < size; ++ index ) {
                newBuffer [ index ] = Memory :: instance().create < __ElementType > ( defaultValue );
            }

            this->_capacity = newCapacity;
            Memory :: instance().destroyArray ( exchange ( this->_pData, newBuffer ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: shrink (
                Size size
        ) noexcept -> void {

            for ( Size index = size; index < this->size(); ++ index ) {
                delete exchange ( this->_pData [ index ], nullptr );
            }

            this->_size = minOf ( size, this->size() );

            if ( size == this->_capacity ) {
                return;
            }

            auto newCapacity = maxOf ( minOf ( this->_capacity, size ), Array :: minCapacity );
            auto newBuffer = Memory :: instance().createArray < __ElementType * > ( newCapacity );

            for ( Size index = 0; index < this->size(); ++ index ) {
                newBuffer [ index ] = this->_pData [ index ];
            }

            Memory :: instance().destroyArray ( exchange ( this->_pData, newBuffer ) );
            this->_capacity = newCapacity;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( index < 0 || index >= this->_size ) {
                return false;
            }

            Memory :: instance().destroy ( exchange ( this->_pData [ index ], nullptr ) );

            if ( this->size() * 2 > this->_capacity || this->_capacity <= Array :: minCapacity ) {

                for ( auto copyIndex = index, len = static_cast < Index > ( this->size() ) - 1; copyIndex < len; ++ copyIndex ) {
                    this->_pData [ copyIndex ] = this->_pData [ copyIndex + 1 ];
                }

                -- this->_size;
                return true;
            }

            auto newBuf = Memory :: instance().createArray < __ElementType * > ( this->size() - 1 );
            (void) std::memcpy ( newBuf, this->_pData, index * sizeof ( __ElementType * ) );
            (void) std::memcpy ( newBuf + index, this->_pData + index + 1, (this->size() - index - 1) * sizeof(__ElementType *) );
            Memory :: instance().destroyArray( exchange ( this->_pData, newBuf ) );

            this->_capacity = -- this->_size;
            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Collection < Index > const & indices
        ) noexcept -> Size {

            if ( indices.empty() ) {
                return 0U;
            }

            auto newBuf = Memory :: instance().createArray < __ElementType * > ( this->size() );
            auto newLen = 0U;

            for ( Index index = 0, len = static_cast < Index > ( this->size() ); index < len; ++ index ) {
                if ( ! indices.contains ( index ) ) {
                    newBuf [ newLen ++ ] = this->_pData [ index ];
                } else {
                    Memory :: instance ().destroy ( this->_pData [ index ] );
                }
            }

            auto adjustedBuf    = Memory :: instance().createArray < __ElementType * > ( newLen );
            auto removedCount   = this->size() - newLen;
            (void) std :: memcpy ( adjustedBuf, newBuf, newLen * sizeof ( __ElementType * ) );

            Memory :: instance ().destroyArray ( cds :: exchange ( this->_pData, adjustedBuf ) );
            Memory :: instance ().destroyArray ( newBuf );

            this->_size     = newLen;
            this->_capacity = newLen;

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                std :: initializer_list < Index > const & indices
        ) noexcept -> Size {

            if ( indices.size() == 0 ) {
                return 0U;
            }

            auto newBuf = Memory :: instance().createArray < __ElementType * > ( this->size() );
            auto newLen = 0U;

            for ( Index index = 0, len = static_cast < Index > ( this->size() ); index < len; ++ index ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( indices, index ) ) {
                    newBuf [ newLen ++ ] = this->_pData [ index ];
                } else {
                    Memory :: instance ().destroy ( this->_pData [ index ] );
                }
            }

            auto adjustedBuf    = Memory :: instance().createArray < __ElementType * > ( newLen );
            auto removedCount   = this->size() - newLen;
            (void) std :: memcpy ( adjustedBuf, newBuf, newLen * sizeof ( __ElementType * ) );

            Memory :: instance ().destroyArray ( cds :: exchange ( this->_pData, adjustedBuf ) );
            Memory :: instance ().destroyArray ( newBuf );

            this->_size     = newLen;
            this->_capacity = newLen;

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
        ) noexcept -> ElementType * & {

            if ( this->_size < this->_capacity ) {
                for ( auto moveIndex = static_cast < Index > ( this->_size ), until = index; moveIndex > until; -- moveIndex ) {
                    this->_pData [ moveIndex ] = this->_pData [ moveIndex - 1 ];
                }

                ++ this->_size;
                return this->_pData [ index ] = nullptr;
            }

            auto newCap = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = Memory :: instance ().createArray < __ElementType * > ( newCap );

            (void) std :: memcpy ( newBuf - index, this->_pData, sizeof ( __ElementType * ) * ( index - 1 ) );
            (void) std :: memcpy ( newBuf + index + 1, this->_pData + index, sizeof ( __ElementType * ) * ( static_cast < Index > ( this->_size ) - index + 1 ) );

            this->_capacity = newCap;
            ++ this->_size;
            Memory :: instance().destroyArray ( cds :: exchange ( this->_pData, newBuf ) );

            return this->_pData [ index ] = nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                Index index
        ) noexcept -> ElementType * & {

            if ( this->_size < this->_capacity ) {
                for ( auto moveIndex = static_cast < Index > ( this->_size ), until = index + 1; moveIndex > until; -- moveIndex ) {
                    this->_pData [ moveIndex ] = this->_pData [ moveIndex - 1 ];
                }

                ++ this->_size;
                return this->_pData [ index + 1 ] = nullptr;
            }

            auto newCap = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = Memory :: instance ().createArray < __ElementType * > ( newCap );

            (void) std :: memcpy ( newBuf, this->_pData, sizeof ( __ElementType * ) * index );
            (void) std :: memcpy ( newBuf + index + 2, this->_pData + index + 1, sizeof ( __ElementType * ) * ( static_cast < Index > ( this->_size ) - index ) );

            this->_capacity = newCap;
            ++ this->_size;
            Memory :: instance().destroyArray ( cds :: exchange ( this->_pData, newBuf ) );

            return this->_pData [ index + 1 ] = nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBack () noexcept -> ElementType * & {

            if ( this->_size < this->_capacity ) {
                this->_pData [ this->_size ] = nullptr;
                return this->_pData [ this->_size ++ ];
            }

            auto newSize = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            __ElementType ** newBuf = Memory :: instance ().createArray < __ElementType * > (newSize);

            (void) std :: memcpy ( newBuf, this->_pData, this->_size * sizeof(__ElementType *) );
            (void) std :: memset ( newBuf + this->_size, 0, ( newSize - this->_size ) * sizeof ( __ElementType * ) );

            this->_capacity = newSize;
            Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );

            this->_pData [ this->_size ] = nullptr;
            return this->_pData [ this->_size ++ ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewFront () noexcept -> ElementType * & {

            if ( this->_size < this->_capacity ) {
                for ( Index i = this->_size; i > 0; -- i ) {
                    this->_pData[i] = this->_pData[i - 1];
                }

                ++ this->_size;

                this->_pData[0] = nullptr;
                return this->_pData[0];
            }

            auto newSize = maxOf ( this->_capacity * 2, this->_size + 1, Array :: minCapacity );
            auto newBuf = Memory :: instance().createArray < __ElementType * > ( newSize );
            (void) std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( __ElementType * ) );
            (void) std::memset ( newBuf + 1 + this->_size, 0, (newSize - this->_size - 1) * sizeof(__ElementType *) );

            this->_capacity = newSize;
            this->_size ++;

            Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

            this->_pData[0] = nullptr;
            return this->_pData[0];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                Iterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                Iterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ConstIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ConstIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewBefore (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: pNewAfter (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->index() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[0];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[0];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
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

            return * this->_pData[index];
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

            return * this->_pData[index];
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
                if ( ! meta :: equals ( * this->_pData [ parseIndex ], * array._pData [ parseIndex ] ) ) {
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
                Memory :: instance().destroy ( exchange ( this->_pData[i], nullptr ) );
            }

            this->_size = 0;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: makeUnique () noexcept -> void {

            __ElementType ** pNewData = Memory :: instance().createArray < __ElementType * > (this->size());
            Size newLength = 0u;

            static auto newArrContains = [](
                    __ElementType                ** pArray,
                    Size                arrayLength,
                    ElementType const & element
            ) noexcept -> bool {
                for (Size i = 0u; i < arrayLength; ++ i ) {
                    if ( meta :: equals (* pArray[i], element ) ) {
                        return true;
                    }
                }

                return false;
            };

            for ( Index i = 0; i < this->size(); ++ i ) {
                if ( ! newArrContains(pNewData, newLength, * this->_pData[i]) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    pNewData[ ++ newLength ] = this->_pData[i];
                } else {
                    Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );
                }
            }

            (void) std :: memset (pNewData + newLength, 0, (this->size() - newLength) * sizeof(__ElementType *) );

            this->_capacity = this->size();
            this->_size = newLength;

            Memory :: instance().destroyArray( exchange ( this->_pData, pNewData ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popFront () noexcept -> void {

            Memory :: instance().destroy ( exchange(this->_pData[0], nullptr) );

            for ( Index i = 0; i < this->size() - 1; i ++ ) {
                this->_pData[i] = this->_pData[i + 1];
            }

            this->_pData[-- this->_size] = nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popBack () noexcept -> void {

            Memory :: instance().destroy ( exchange(this->_pData[--this->_size], nullptr) );
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
            Memory :: instance().destroyArray ( exchange ( this->_pData, Memory :: instance().createArray < __ElementType * > ( this->_capacity ) ) );

            for ( Size index = 0; index < array.size(); ++ index ) {
                this->_pData [ index ] = Memory :: instance().create ( * array._pData [ index ] );
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
            Memory :: instance().destroyArray ( exchange ( this->_pData, exchange ( array._pData, nullptr ) ) );

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
            Memory :: instance().destroyArray ( exchange ( this->_pData, Memory :: instance().createArray < __ElementType * > ( this->_capacity ) ) );

            Size index = 0ULL;
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator, ++ index ) {
                this->_pData [ index ] = Memory :: instance().create ( * iterator );
            }

            return * this;
        }

    }
}

#endif // __CDS_ARRAY_IMPL_HPP__
