//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_IMPL_HPP__
#define __CDS_ARRAY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        Array < T > :: ~Array () noexcept {
            for ( Index i = 0U; i < this->_capacity; ++ i ) {
                Memory :: instance().destroy ( this->_pData[i] );
            }

            Memory :: instance().destroyArray ( this->_pData );
        }

        template < typename T >
        Array < T > :: Array ( InitializerList const & initializerList ) noexcept :
                List < T > ( static_cast < Size > ( initializerList.size() ) ),
                _capacity ( initializerList.size() ),
                _pData ( Memory :: instance().createArray < T * > ( initializerList.size() ) ) {

            Index i = 0;
            for ( auto const & element : initializerList ) {
                this->_pData [ i ++ ] = Memory :: instance().create < T > ( element );
            }
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: equals ( Object const & object ) const noexcept -> bool {
            return this->List < T > :: equals ( object );
        }

        template < typename T >
        __CDS_OptimalInline Array < T > :: Array ( Array < T > const & array ) noexcept :
                List < T > ( array ),
                _capacity ( array.List < T > :: size() ),
                _pData ( array.List < T > :: empty() ? nullptr : Memory :: instance().createArray < T * > ( array.List < T > :: size() ) ){

            this->initializeByCopy ( array );
        }

        template < typename T >
        constexpr Array < T > :: Array ( Array < T > && array ) noexcept :
                List < T > ( cds :: forward < List < T > > ( array ) ),
                _pData ( cds :: exchange ( array._pData, nullptr ) ),
                _capacity ( cds :: exchange ( array._capacity, 0ULL ) ) {

        }

        template < typename T >
        auto Array < T > :: initializeByCopy ( Array < T > const & array ) noexcept -> void {
            static_assert ( Type < T > :: copyConstructible, "Cannot copy an array of given Type, Type has no Copy Constructor" );
            for ( Index i = 0; i < static_cast < Index > ( array.size() ); ++ i ) {
                this->_pData[i] = Memory :: instance().create < T > ( * array._pData[i] );
            }
        }

        template < typename T >
        auto Array < T > :: delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> cds :: UniquePointer < DelegateIterator > {
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
        }

        template < typename T >
        auto Array < T > :: delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {
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
        }

        template < typename T >
        auto Array < T > :: remove ( Index index ) noexcept -> bool {
            if ( index < 0 || index >= this->_size ) {
                return false;
            }

            Memory :: instance().destroy ( exchange ( this->_pData [ index ], nullptr ) );

            if ( this->size() * 2 > this->_capacity ) {

                for ( auto copyIndex = index, len = static_cast < Index > ( this->size() ) - 1; index < len; ++ index ) {
                    this->_pData [ copyIndex ] = this->_pData [ copyIndex + 1 ];
                }

                -- this->_size;
                return true;
            }

            auto newBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
            (void) std::memcpy ( newBuf, this->_pData, index * sizeof ( T * ) );
            (void) std::memcpy ( newBuf + index, this->_pData + index + 1, (this->size() - index - 1) * sizeof(T *) );
            Memory :: instance().destroyArray( exchange ( this->_pData, newBuf ) );

            this->_capacity = -- this->_size;
            return true;
        }

        template < typename T >
        auto Array < T > :: remove ( Iterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index();
        }

        template < typename T >
        auto Array < T > :: remove ( ConstIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index();
        }

        template < typename T >
        auto Array < T > :: remove ( ReverseIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index();
        }

        template < typename T >
        auto Array < T > :: remove ( ConstReverseIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index();
        }

        template < typename T >
        auto Array < T > :: clear () noexcept -> void {
            for ( Index i = 0; i < this->_size; ++ i ) {
                Memory :: instance().destroy ( exchange ( this->_pData[i], nullptr ) );
            }

            this->_size = 0;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: get ( Index index ) noexcept (false) -> ElementType & {
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

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: get ( Index index ) const noexcept (false) -> ElementType const & {
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

        template < typename T >
        auto Array < T > :: popFront () noexcept -> void {
            Memory :: instance().destroy ( exchange(this->_pData[0], nullptr) );

            for ( Index i = 0; i < this->size() - 1; i ++ ) {
                this->_pData[i] = this->_pData[i + 1];
            }

            this->_pData[-- this->_size] = nullptr;
        }

        template < typename T >
        auto Array < T > :: popBack () noexcept -> void {
            Memory :: instance().destroy ( exchange(this->_pData[--this->_size], nullptr) );
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: front () noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[0];
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: front () const noexcept (false) -> ElementType const & {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[0];
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: back () noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: back () const noexcept (false) -> ElementType const & {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
        }

        template < typename T >
        auto Array < T > :: makeUnique () noexcept -> void {
            T ** pNewData = Memory :: instance().createArray < T * > (this->size());
            Size newLength = 0u;

            static auto newArrContains = [](
                    T                ** pArray,
                    Size                arrayLength,
                    ElementType const & element
            ) noexcept -> bool {
                for (Size i = 0u; i < arrayLength; ++ i ) {
                    if ( Type < T > :: compare (* pArray[i], element ) ) {
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

            (void) std :: memset (pNewData + newLength, 0, (this->size() - newLength) * sizeof(T *) );

            this->_capacity = this->size();
            this->_size = newLength;

            Memory :: instance().destroyArray( exchange ( this->_pData, pNewData ) );
        }

        template < typename T >
        auto Array < T > :: remove ( Collection < Index > const & indices ) noexcept -> Size {
            if ( indices.empty() ) {
                return 0U;
            }

            auto newBuf = Memory :: instance().createArray < T * > ( this->size() );
            auto newLen = 0U;

            for ( Index index = 0, len = static_cast < Index > ( this->size() ); index < len; ++ index ) {
                if ( ! indices.contains ( index ) ) {
                    newBuf [ newLen ++ ] = this->_pData [ index ];
                } else {
                    Memory :: instance ().destroy ( this->_pData [ index ] );
                }
            }

            auto adjustedBuf    = Memory :: instance().createArray < T * > ( newLen );
            auto removedCount   = this->size() - newLen;
            (void) std :: memcpy ( adjustedBuf, newBuf, this->size() * sizeof ( T * ) );

            Memory :: instance ().destroyArray ( cds :: exchange ( this->_pData, adjustedBuf ) );
            Memory :: instance ().destroyArray ( newBuf );

            this->_size     = newLen;
            this->_capacity = newLen;

            return removedCount;
        }

        template < typename T >
        auto Array < T > :: remove ( Collection < Iterator > const & iterators ) noexcept -> Size {
            Array < Index > indices;

            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
                if ( iterator->of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( Collection < ConstIterator > const & iterators ) noexcept -> Size {
            Array < Index > indices;

            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
                if ( iterator->of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( Collection < ReverseIterator > const & iterators ) noexcept -> Size {
            Array < Index > indices;

            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
                if ( iterator->of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( Collection < ConstReverseIterator > const & iterators ) noexcept -> Size {
            Array < Index > indices;

            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
                if ( iterator->of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( Iterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            Array < Index > indices;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( ConstIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            Array < Index > indices;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( ReverseIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            Array < Index > indices;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        auto Array < T > :: remove ( ConstReverseIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            Array < Index > indices;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    indices.pushBack ( reinterpret_cast < ArrayDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( pIterators[index] ) )->index() );
                }
            }

            return this->remove ( indices );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBack () noexcept -> ElementType * & {
            if ( this->_size < this->_capacity ) {
                this->_pData [ this->_size ] = nullptr;
                return this->_pData [ this->_size ++ ];
            }

            auto newSize = std :: max ( this->_capacity * 2, this->_size + 1 );
            T ** newBuf = Memory :: instance ().createArray < T * > (newSize);

            (void) std :: memcpy ( newBuf, this->_pData, this->_size * sizeof(T *) );
            (void) std :: memset ( newBuf + this->_size, 0, ( newSize - this->_size ) * sizeof (T*) );

            this->_capacity = newSize;
            Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );

            this->_pData [ this->_size ] = nullptr;
            return this->_pData [ this->_size ++ ];
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewFront () noexcept -> ElementType * & {
            if ( this->_size < this->_capacity ) {
                for ( Index i = this->_size; i > 0; -- i ) {
                    this->_pData[i] = this->_pData[i - 1];
                }

                ++ this->_size;

                this->_pData[0] = nullptr;
                return this->_pData[0];
            }

            auto newSize = this->_capacity * 2;
            auto newBuf = Memory :: instance().createArray < T * > ( newSize );
            (void) std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( T * ) );
            (void) std::memset ( newBuf + 1 + this->_size, 0, (newSize - this->_size - 1) * sizeof(T *) );

            this->_capacity = newSize;
            this->_size ++;

            Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

            this->_pData[0] = nullptr;
            return this->_pData[0];
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBefore ( Iterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewAfter ( Iterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBefore ( ConstIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewAfter ( ConstIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBefore ( ReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( List < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewAfter ( ReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( List < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBefore ( ConstReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewAfter ( ConstReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < ArrayDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->index() );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewAfter ( Index index ) noexcept -> ElementType * & {
            if ( this->_size < this->_capacity ) {
                for ( auto moveIndex = static_cast < Index > ( this->_size ), until = index + 1; moveIndex > until; -- moveIndex ) {
                    this->_pData [ moveIndex ] = this->_pData [ moveIndex - 1 ];
                }

                ++ this->_size;
                return this->_pData [ index + 1 ] = nullptr;
            }

            auto newCap = std :: max ( this->_capacity * 2, this->_size + 1 );
            auto newBuf = Memory :: instance ().createArray < T * > ( newCap );

            (void) std :: memcpy ( newBuf, this->_pData, sizeof ( T * ) * ( index ) );
            (void) std :: memcpy ( newBuf + index + 2, this->_pData + index + 1, sizeof ( T * ) * ( static_cast < Index > ( this->_size ) - index ) );

            this->_capacity = newCap;
            ++ this->_size;
            Memory :: instance().destroyArray ( cds :: exchange ( this->_pData, newBuf ) );

            return this->_pData [ index + 1 ] = nullptr;
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: pNewBefore ( Index index ) noexcept -> ElementType * & {
            if ( this->_size < this->_capacity ) {
                for ( auto moveIndex = static_cast < Index > ( this->_size ), until = index; moveIndex > until; -- moveIndex ) {
                    this->_pData [ moveIndex ] = this->_pData [ moveIndex - 1 ];
                }

                ++ this->_size;
                return this->_pData [ index ] = nullptr;
            }

            auto newCap = std :: max ( this->_capacity * 2, this->_size + 1 );
            auto newBuf = Memory :: instance ().createArray < T * > ( newCap );

            (void) std :: memcpy ( newBuf - index, this->_pData, sizeof ( T * ) * ( index - 1 ) );
            (void) std :: memcpy ( newBuf + index + 1, this->_pData + index, sizeof ( T * ) * ( static_cast < Index > ( this->_size ) - index + 1 ) );

            this->_capacity = newCap;
            ++ this->_size;
            Memory :: instance().destroyArray ( cds :: exchange ( this->_pData, newBuf ) );

            return this->_pData [ index ] = nullptr;
        }

    }
}

#endif // __CDS_ARRAY_IMPL_HPP__
