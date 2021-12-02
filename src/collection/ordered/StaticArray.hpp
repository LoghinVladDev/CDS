//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_STATICARRAY_HPP
#define CDS_STATICARRAY_HPP

#include <CDS/List>
#include <CDS/Memory>

namespace cds {

    template < typename T, Size capacity >
    class __CDS_MaybeUnused StaticArray : public List < T > {
    private:
        T * _pData[capacity];

    public:
        using ElementType                   = typename List < T > :: ElementType;

    private:
        using ElementRef                    = typename List < T > :: ElementRef;
        using ElementCRef                   = typename List < T > :: ElementCRef;
        using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
        using ElementPtr                    = typename List < T > :: ElementPtr;
        using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
        using ElementCPtr                   = typename List < T > :: ElementCPtr;

    public:
        using Iterator                      = typename List < T > :: Iterator;
        using ConstIterator                 = typename List < T > :: ConstIterator;

        using ReverseIterator               = typename List < T > :: ReverseIterator;
        using ConstReverseIterator          = typename List < T > :: ConstReverseIterator;

    private:
        using DelegateIterator              = typename List < T > :: DelegateIterator;
        using DelegateConstIterator         = typename List < T > :: DelegateConstIterator;

        using InitializerList               = typename List < T > :: InitializerList;

    public:

        constexpr StaticArray () noexcept {
            std :: memset ( this->_pData, 0, sizeof ( T * ) * capacity );
        }

        __CDS_OptimalInline StaticArray ( StaticArray const & array ) noexcept { // NOLINT(google-explicit-constructor)
            for ( Index i = 0; i < array._size; ++ i )
                this->_pData[ i ] = Memory :: instance () . create < T > ( * array._pData[ i ] );

            this->_size = array._size;
            std :: memset ( this->_pData + this->_size, 0, sizeof ( T * ) * ( capacity - this->_size ) );
        }

        constexpr StaticArray ( StaticArray && array ) noexcept {
            std :: memcpy ( this->_pData, array._pData, sizeof ( T * ) * capacity );
            std :: memset ( array._pData, 0, sizeof ( T * ) * capacity );

            this->_size = exchange ( array._size, 0 );
        }

        template < Size otherCapacity >
        __CDS_OptimalInline explicit StaticArray ( StaticArray < T, otherCapacity > const & array ) noexcept {
            auto const copyCount = std :: min ( capacity, array._size );
            auto const clearCount = std :: max ( capacity, array._size );

            for ( Index i = 0; i < copyCount; ++ i )
                this->_pData[ i ] = Memory :: instance () .create < T > ( * array._pData[i] );

            this->_size = copyCount;
            if ( clearCount > copyCount )
                std :: memset ( this->_pData + copyCount, 0, sizeof ( T * ) * ( clearCount - copyCount ) );
        }

        template < Size otherCapacity >
        constexpr explicit StaticArray ( StaticArray < T, otherCapacity > && array ) noexcept {
            auto const copyCount = std :: min ( capacity, array._size );
            auto const clearCount = std :: max ( capacity, array._size );

            std :: memcpy ( this->_pData, array._pData, sizeof ( T * ) * copyCount );
            std :: memset ( array._pData, 0, sizeof ( T * ) * clearCount );

            if ( clearCount > copyCount )
                std :: memset ( this->_pData + copyCount, 0, sizeof ( T * ) * ( clearCount - copyCount ) );

            this->_size = exchange ( array._size, 0 );
        }

        __CDS_OptimalInline ~StaticArray () noexcept override {
            for ( Index i = 0; i < this->_size; ++ i )
                Memory :: instance () . destroy ( this->_pData[i] );
        }

        __CDS_OptimalInline explicit StaticArray ( Collection < T > const & collection ) noexcept : StaticArray() {
            for ( auto const & e : collection )
                this->add ( e );
        }

        __CDS_OptimalInline StaticArray ( Iterator const & begin, Iterator const & end ) noexcept : StaticArray() {
            for ( auto it = begin; it != end; ++ it )
                this->add ( * it );
        }

        __CDS_OptimalInline StaticArray ( ConstIterator const & begin, ConstIterator const & end ) noexcept : StaticArray() {
            for ( auto it = begin; it != end; ++ it )
                this->add ( * it );
        }

        auto remove ( ElementCRef element, Size count ) noexcept -> bool final {
            bool removed = false;

            T * newBuffer [ capacity ];

            Index i = 0, l = 0, c = 0;
            for (; i < this->size() && c < count; i++)
                if ( ! Type < T > :: compare ( * this->_pData[i], element ) ) {
                    newBuffer[l++] = this->_pData[i];
                } else {
                    removed = true;
                    ++ c;
                    Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );
                }

            this->_size = l;

            std :: memcpy ( this->_pData, newBuffer, l * sizeof ( T * ) );
            std :: memset ( this->_pData + l, 0, ( capacity - l ) * sizeof ( T * ) );

            return removed;
        }

        auto removeLast ( ElementCRef ) noexcept -> bool final;

        auto removeOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
        auto removeLastOf ( Collection < ElementType > const & ) noexcept -> bool final;
        auto removeNotOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
        auto removeLastNotOf ( Collection < ElementType > const & ) noexcept -> bool final;

        auto remove ( Iterator const & ) noexcept(false) -> ElementType final;

        auto removeOf ( InitializerList, Size ) noexcept -> bool final;
        auto removeLastOf ( InitializerList ) noexcept -> bool final;
        auto removeNotOf ( InitializerList, Size ) noexcept -> bool final;
        auto removeLastNotOf ( InitializerList ) noexcept -> bool final;

        __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            return * this->_pData[this->_size - 1];
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            return * this->_pData[0];
        }

        __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            return * this->_pData[this->_size - 1];
        }

        __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef final {
            if (this->empty())
                throw OutOfBoundsException("Array is Empty");

            return *this->_pData[0];
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( StaticArray const & array ) const noexcept -> bool {
            if ( this == & array ) return true;
            if ( this->size() != array.size() ) return false;

            for (
                    auto
                        a = this->begin(), aEnd = this->end(),
                        b = array.begin(), bEnd = array.end();
                    a != aEnd && b != bEnd;
                    ++ a, ++ b
            )
                if ( ! Type < T > :: compare ( * a, * b ) )
                    return false;
            return true;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( StaticArray const & array ) const noexcept -> bool {
            return ! this->operator== ( array );
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & o ) const noexcept -> bool final {
            if (this == &o) return true;
            auto p = dynamic_cast < decltype(this) > ( &o );
            if (p == nullptr) return false;

            return this->operator==(*p);
        }

        auto clear () noexcept -> void final {
            for ( Index i = 0; i < this->size(); ++ i )
                Memory :: instance().destroy ( this->_pData[i] );

            this->_size = 0;
        }

        auto makeUnique () noexcept -> void final {
            T * pTempBuffer [ capacity ];
            Size l = 0;

            static auto newArrContains = [](T ** p, Size l, ElementCRef e) noexcept -> bool {
                for ( Index i = 0; i < l; ++ i )
                    if ( Type < T > :: compare ( * p[i], e ) )
                        return true;
                return false;
            };

            for ( Index i = 0; i < this->size(); ++ i )
                if ( newArrContains ( pTempBuffer, l, * this->_pData[i] ) )
                    Memory :: instance() .destroy ( this->_pData[i] );
                else
                    pTempBuffer [ ++ l ] = this->_pData[i];

            std :: memcpy ( this->_pData, pTempBuffer, sizeof ( T * ) * l );
            std :: memset ( this->_pData + l, 0, sizeof ( T * ) * ( capacity - l ) );

            this->_size = l;
        }

        __CDS_MaybeUnused auto indices ( ElementCRef value ) const noexcept -> DoubleLinkedList < T > {
            DoubleLinkedList < Index > indices;

            for ( Index i = 0; i < this->_size; ++ i )
                if ( Type < T > :: compare ( * this->_pData[i], value ) )
                    indices.pushBack(i);

            return indices;
        }

    private:
        auto pAt ( Index index ) noexcept (false) -> ElementPtr final {
            if ( this->empty() )
                throw OutOfBoundsException (index, 0 );

            if (index < 0 )
                index += (this->size() / (-index) ) * this->size();
            if (index >= static_cast<Index>(this->size()) )
                index = index % this->size();

            return this->_pData[index];
        }

        auto pAt ( Index index ) const noexcept (false) -> ElementPtr final {
            if ( this->empty() )
                throw OutOfBoundsException (index, 0 );

            if (index < 0 )
                index += (this->size() / (-index) ) * this->size();
            if (index >= static_cast<Index>(this->size()) )
                index = index % this->size();

            return this->_pData[index];
        }

    public:
        __CDS_OptionalInline auto popFront () noexcept (false) -> ElementType final {
            if ( this->empty() )
                throw OutOfBoundsException ( "Array is Empty" );

            auto retVal = * this->_pData[0];
            Memory :: instance() . destroy ( exchange ( this->_pData[0], nullptr ) );

            for ( Index i = 0; i < this->size() - 1; ++ i )
                this->_pData[i] = this->_pData[i + 1];

            this->_pData[-- this->_size] = nullptr;
            return retVal;
        }

        __CDS_OptionalInline auto popBack () noexcept (false) -> ElementType final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            auto v = * this->_pData[--this->_size];
            Memory :: instance().destroy ( exchange(this->_pData[this->_size], nullptr) );

            return v;
        }

    private:

        class StaticArrayDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < StaticArray >  _pArray     {nullptr};
            Index                           _index      {0};
            bool                            _forward    {false};

        public:
            constexpr StaticArrayDelegateIterator ( StaticArray * pArray, Index index, bool forward ) noexcept :
                    DelegateIterator (),
                    _pArray ( pArray ),
                    _index ( index ),
                    _forward ( forward ) {

            }

            constexpr StaticArrayDelegateIterator( StaticArrayDelegateIterator const & ) noexcept = default;
            constexpr StaticArrayDelegateIterator( StaticArrayDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~StaticArrayDelegateIterator() noexcept override = default;

            __CDS_NoDiscard constexpr auto index () const noexcept -> Index {
                return this->_index;
            }

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return
                    this->_pArray != nullptr &&
                    this->_index >= 0 && this->_idex < this->_pArray->size();
            }

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> StaticArrayDelegateIterator & override {
                (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> StaticArrayDelegateIterator & override {
                (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pArray->_pData[ this->_index ];
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return this->_pArray == p->_pArray && this->_index == p->_index;
            }

            __CDS_OptimalInline auto copy () const noexcept -> StaticArrayDelegateIterator * override {
                return Memory :: instance () . create < StaticArrayDelegateIterator > ( * this );
            }
        };

        class StaticArrayDelegateConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < StaticArray const >    _pArray     {nullptr};
            Index                                   _index      {0};
            bool                                    _forward    {false};

        public:
            constexpr StaticArrayDelegateConstIterator ( StaticArray const * pArray, Index index, bool forward ) noexcept :
                    DelegateConstIterator (),
                    _pArray ( pArray ),
                    _index ( index ),
                    _forward ( forward ) {

            }

            constexpr StaticArrayDelegateConstIterator( StaticArrayDelegateConstIterator const & ) noexcept = default;
            constexpr StaticArrayDelegateConstIterator( StaticArrayDelegateConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~StaticArrayDelegateConstIterator() noexcept override = default;

            __CDS_NoDiscard constexpr auto index () const noexcept -> Index {
                return this->_index;
            }

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return
                    this->_pArray != nullptr &&
                    this->_index >= 0 && this->_idex < this->_pArray->size();
            }

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> StaticArrayDelegateConstIterator & override {
                (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> StaticArrayDelegateConstIterator & override {
                (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pArray->_pData[ this->_index ];
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return this->_pArray == p->_pArray && this->_index == p->_index;
            }

            __CDS_OptimalInline auto copy () const noexcept -> StaticArrayDelegateConstIterator * override {
                return Memory :: instance () . create < StaticArrayDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> DelegateIterator * override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < StaticArrayDelegateIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < StaticArrayDelegateIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                    return Memory :: instance () . create < StaticArrayDelegateIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END:
                    return Memory :: instance () . create < StaticArrayDelegateIterator > ( this, -1, false );
                default:
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> DelegateConstIterator * override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < StaticArrayDelegateConstIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < StaticArrayDelegateConstIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                    return Memory :: instance () . create < StaticArrayDelegateConstIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END:
                    return Memory :: instance () . create < StaticArrayDelegateConstIterator > ( this, -1, false );
                default:
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto allocFrontGetPtr () noexcept -> ElementPtrRef final {
            if ( this->_size >= capacity )
                return this->_pData[0];

            for ( Index i = this->_size; i > 0; -- i )
                this->_pData[i] = this->_pData[i - 1];

            ++ this->_size;

            return ( this->_pData[0] = nullptr );
        }

        __CDS_OptimalInline auto allocBackGetPtr () noexcept -> ElementPtrRef final {
            if ( this->_size >= capacity )
                return this->_pData[this->_size - 1];

            return ( this->_pData[ this->_size ++ ] = nullptr );
        }

        __CDS_OptimalInline auto allocInsertGetPtr ( ElementCRef e __CDS_MaybeUnused ) noexcept -> ElementPtrRef final {
            return this->allocBackGetPtr();
        }

    public:

        auto operator = ( Collection < ElementType > const & collection ) noexcept -> StaticArray & {
            if ( this == & collection ) return * this;

            this->clear();

            Index i = 0;
            for ( auto const & e : collection ) {
                this->pushBack ( e );
                ++ i;

                if ( i >= capacity )
                    break;
            }

            return * this;
        }

        auto operator = ( StaticArray const & array ) noexcept -> StaticArray & {
            if ( this == & array ) return * this;

            this->clear();
            for ( Index i = 0; i < array._size; ++ i )
                this->_pData[i] = Memory :: instance () . create < ElementType > ( * array._pData[i] );

            this->_size = array._size;
            return * this;
        }

        auto operator = ( StaticArray && array ) noexcept -> StaticArray & {
            if ( this == & array ) return * this;

            this->clear();
            std :: memcpy ( this->_pData, array._pData, sizeof ( T * ) * capacity );
            std :: memset ( array._pData, 0, sizeof ( T * ) * capacity );
            return * this;
        }

        template < Size otherCapacity >
        auto operator = ( StaticArray const & array ) noexcept -> StaticArray & {
            if ( this == & array ) return * this;

            auto const copyCount = std :: min ( capacity, array._size );
            auto const clearCount = std :: max ( capacity, array._size );

            this->clear();
            for ( Index i = 0; i < copyCount; ++ i )
                this->_pData[i] = Memory :: instance () . create < ElementType > ( * array._pData[i] );

            this->_size = copyCount;
            if ( clearCount > copyCount )
                std :: memset ( this->_pData + copyCount, 0, sizeof ( T * ) * ( clearCount - copyCount ) );

            return * this;
        }

        template < Size otherCapacity >
        auto operator = ( StaticArray && array ) noexcept -> StaticArray & {
            if ( this == & array ) return * this;

            auto const copyCount = std :: min ( capacity, array._size );
            auto const clearCount = std :: max ( capacity, array._size );

            this->clear();

            std :: memcpy ( this->_pData, array._pData, sizeof ( T * ) * copyCount );
            std :: memset ( array._pData, 0, sizeof ( T * ) * clearCount );

            if ( clearCount > copyCount )
                std :: memset ( this->_pData + copyCount, 0, sizeof ( T * ) * ( clearCount - copyCount ) );

            this->_size = exchange ( array._size, 0 );

            return * this;
        }

        auto sequence () const & noexcept -> Sequence < StaticArray < T, capacity > const >;
        auto sequence () & noexcept -> Sequence < StaticArray < T, capacity > >;
        auto sequence () const && noexcept -> Sequence < StaticArray < T, capacity > const >;
        auto sequence () && noexcept -> Sequence < StaticArray < T, capacity > >;
    };
}

#if defined(CDS_SEQUENCE_HPP) && !defined(CDS_STATICARRAY_SEQUENCE)
#define CDS_STATICARRAY_SEQUENCE

namespace cds {

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () const & noexcept -> Sequence < StaticArray < T, capacity > const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () & noexcept -> Sequence < StaticArray < T, capacity > > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () const && noexcept -> Sequence < StaticArray < T, capacity > const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () && noexcept -> Sequence < StaticArray < T, capacity > > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

}

#endif

namespace cds {

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeLast ( ElementCRef e ) noexcept -> bool {
        Index at = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i )
            if ( Type < T > :: compare ( * this->_pData[i], e ) ) {
                at = i;
                break;
            }

        if ( at == -1 ) return false;

        Memory :: instance().destroy ( this->_pData[at] );

        T * tempBuffer [ capacity ];
        std :: memcpy ( tempBuffer, this->_pData + at + 1, ( this->_size - at - 1 ) * sizeof ( T * ) );
        std :: memcpy ( this->_pData + at, tempBuffer, ( this->_size - at - 1 ) * sizeof ( T * ) );

        this->_pData [ -- this->_size ] = nullptr;
        return true;
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeOf ( Collection < ElementType > const &, Size ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeLastOf ( Collection < ElementType > const & ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeNotOf ( Collection < ElementType > const &, Size ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeLastNotOf ( Collection < ElementType > const & ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: remove ( Iterator const & ) noexcept(false) -> ElementType {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeOf ( InitializerList, Size ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeLastOf ( InitializerList ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeNotOf ( InitializerList, Size ) noexcept -> bool {

    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: removeLastNotOf ( InitializerList ) noexcept -> bool {

    }


}

#endif //CDS_STATICARRAY_HPP
