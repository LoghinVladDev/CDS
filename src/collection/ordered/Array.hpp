//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_ARRAY_HPP
#define CDS_ARRAY_HPP

#include <CDS/List>

template <class T>
class Array final : public List <T> {
private:
    T ** _pData     {nullptr };
    Size _capacity  { 0ull };

    using ElementType                   = typename List < T > :: ElementType;
    using ElementRef                    = typename List < T > :: ElementRef;
    using ElementCRef                   = typename List < T > :: ElementCRef;
    using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
    using ElementPtr                    = typename List < T > :: ElementPtr;
    using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
    using ElementCPtr                   = typename List < T > :: ElementCPtr;

    class IteratorBase;
    class ConstIteratorBase;

    __CDS_MaybeUnused auto expandWith ( Size ) noexcept -> void;

public:

    class Iterator;
    class ReverseIterator;
    class ConstIterator;
    class ConstReverseIterator;

    Array () noexcept = default;
    Array ( Array const & ) noexcept;
    Array ( Array && ) noexcept;

    Array (
        typename Collection<ElementType>::Iterator const &,
        typename Collection<ElementType>::Iterator const &
    ) noexcept;

    Array (
        typename Collection<ElementType>::ConstIterator const &,
        typename Collection<ElementType>::ConstIterator const &
    ) noexcept;

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    Array( std::initializer_list <ElementType> const & ) noexcept;

    explicit Array( Size, ElementCRef = ElementType () ) noexcept;

    ~Array () noexcept final;

private:
    inline auto beginPtr () noexcept -> Iterator * final { return new Iterator( this, 0 ); }
    inline auto endPtr () noexcept -> Iterator * final { return new Iterator(this, this->size()); }
    inline auto beginPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, 0 ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, this->size() ); }

public:
    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator { return Iterator ( this, 0 ); }
    constexpr auto begin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    constexpr auto cbegin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator ( this, this->size() ); }
    constexpr auto end () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }
    constexpr auto cend () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator { return ReverseIterator ( this, this->size () - 1 ); }
    constexpr auto rbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    __CDS_MaybeUnused constexpr auto crbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto rend() noexcept -> ReverseIterator { return ReverseIterator(this, -1); }
    constexpr auto rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }
    __CDS_MaybeUnused constexpr auto crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }

private:
    auto _resize ( Size ) noexcept -> void;

public:
    inline auto resize ( Size newSize ) noexcept -> void {
        this->_resize(newSize);
        this->_size = newSize;
    }

    auto shrinkToSize ( Size ) noexcept -> void;

    auto remove ( ElementCRef , Size ) noexcept -> bool final;
    auto removeLast ( ElementCRef ) noexcept -> bool final;

    auto removeOf ( Collection <ElementType> const &, Size ) noexcept -> bool final;
    auto removeLastOf ( Collection<ElementType> const & ) noexcept -> bool final;
    auto removeNotOf ( Collection<ElementType> const &, Size ) noexcept -> bool final;
    auto removeLastNotOf ( Collection<ElementType> const & ) noexcept -> bool final;

    auto remove ( typename Collection<ElementType>::Iterator const & ) noexcept(false) -> ElementType final;

    inline auto removeOf ( std::initializer_list<ElementType> const &, Size ) noexcept -> bool final;
    inline auto removeLastOf ( std::initializer_list<ElementType> const & ) noexcept -> bool final;
    inline auto removeNotOf ( std::initializer_list<ElementType> const &, Size ) noexcept -> bool final;
    inline auto removeLastNotOf ( std::initializer_list<ElementType> const & ) noexcept -> bool final;

    __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef final {
        if ( this->empty() )
            throw typename List<ElementType>::ListOutOfBounds();

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef final {
        if ( this->empty() )
            throw typename List<ElementType>::ListOutOfBounds();

        return * this->_pData[0];
    }

    __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef final {
        if ( this->empty() )
            throw typename List<ElementType>::ListOutOfBounds();

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef final {
        if (this->empty())
            throw typename List<ElementType>::ListOutOfBounds();

        return *this->_pData[0];
    }

    auto operator == (Array const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( o.size() != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
            if ( ! ( Type < T > :: compare ( i1.value(), i2.value() ) ) )
                return false;
        return true;
    }

    inline auto operator != (Array const & o) const noexcept -> bool {
        return ! ( * this == o );
    }
    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if (this == &o) return true;
        auto p = dynamic_cast < decltype(this) > ( &o );
        if (p == nullptr) return false;

        return this->operator==(*p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void final;
    auto contains ( ElementCRef ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( ElementCRef ) const noexcept -> Index final;
    auto index ( ElementRef ) noexcept -> Index final;

    __CDS_MaybeUnused auto indices ( ElementCRef ) const noexcept -> DoubleLinkedList < Index >;

private:
    auto pAt (Index) noexcept (false) -> ElementPtr override;
    auto pAt (Index) const noexcept (false) -> ElementCPtr override;

public:

    auto popFront () noexcept (false) -> ElementType final {
        if ( this->empty() )
            throw typename List<ElementType>::ListOutOfBounds();

        auto retVal = * this->_pData[0];

        auto p = this->_pData[0];

        for ( Index i = 0; i < this->size() - 1; i ++ )
            this->_pData[i] = this->_pData[i + 1];

        this->_pData[-- this->_size] = p;

        return retVal;
    }

    auto popBack () noexcept (false) -> ElementType final {
        if ( this->empty() )
            throw typename List<ElementType>::ListOutOfBounds();

        auto retVal = * this->_pData[this->size() - 1];

        this->_size --;

        return retVal;
    }

private:

    auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
    auto allocBackGetPtr () noexcept -> ElementPtrRef override;
    inline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
        return this->allocBackGetPtr();
    }

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#endif

    template < typename SortFunc >
    auto static quickSort ( Iterator, Iterator, SortFunc const & ) noexcept -> void;

    template < typename SortFunc >
    auto static quickSortPartition ( Iterator, Iterator, SortFunc const & ) noexcept -> Iterator;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic pop
#endif

public:
    template < typename SortFunc >
    auto sort ( SortFunc const & ) noexcept -> void;

    inline auto sort ( Comparator < ElementType > const & c ) noexcept -> void final {
        return this->sort ( [&c] (ElementCRef a, ElementCRef b) noexcept -> bool { return c(a, b); } );
    }

    Array & operator = ( Collection < ElementType > const & ) noexcept;
    inline Array & operator = ( Array const & o ) noexcept { return this->operator=( ( Collection<ElementType> const & )(o) ); } // NOLINT(bugprone-unhandled-self-assignment,misc-unconventional-assign-operator)

    auto sequence () const & noexcept -> Sequence < const Array < T > >;
    auto sequence () & noexcept -> Sequence < Array < T > >;
    auto sequence () const && noexcept -> Sequence < const Array < T > >;
    auto sequence () && noexcept -> Sequence < Array < T > >;
};

template <class T>
class Array<T>::IteratorBase : public Collection<T>::Iterator {
protected:
    friend class Array;
    Index mutable   _index  { 0ull };
    Array         * _pArray { nullptr };

    IteratorBase( IteratorBase const & ) noexcept = default;
    IteratorBase( IteratorBase && ) noexcept = default;
    explicit IteratorBase( Array * pArray, Index index ) noexcept :
            Collection<T>::Iterator( pArray ),
            _index(index),
            _pArray(pArray) { }

public:
    ~IteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprConditioned auto equals ( typename Collection<T>::Iterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < IteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    constexpr auto value () const noexcept -> ElementRef final { return (* this->_pArray)[this->_index]; }

    __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;
};

template <class T>
class Array<T>::ConstIteratorBase : public Collection<T>::ConstIterator {
protected:
    friend class Array;
    Index mutable _index  { 0ull };
    Array const * _pArray { nullptr };

    ConstIteratorBase( ConstIteratorBase const & ) noexcept = default;
    ConstIteratorBase( ConstIteratorBase && ) noexcept = default;
    explicit ConstIteratorBase (Array const * pArray, Index index) noexcept :
            Collection<T>::ConstIterator(pArray),
            _index(index),
            _pArray(pArray) { }

public:
    ~ConstIteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprConditioned auto equals ( typename Collection<T>::ConstIterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < ConstIteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    constexpr auto value () const noexcept -> ElementCRef final { return (* this->_pArray)[this->_index]; }

    __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;
};

template <class T>
class Array<T>::Iterator final : public IteratorBase {
public:
    Iterator ( Iterator const & ) noexcept = default;
    Iterator ( Iterator && ) noexcept = default;
    explicit Iterator ( Array * pArray, Index index ) noexcept : IteratorBase( pArray, index ) { }
    ~Iterator () noexcept final = default;

    __CDS_cpplang_NonConstConstexprMemberFunction Iterator & operator = ( Iterator const & o ) noexcept {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    inline auto operator == (Iterator const& o) const noexcept -> bool { return this->equals(o); }
    inline auto operator != (Iterator const& o) const noexcept -> bool { return !this->equals(o); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & final { this->_index ++; return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> Iterator & { this->_index --; return * this; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Iterator & override { return this->next(); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Iterator & { return this->prev(); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> Iterator { auto copy = * this; this->prev(); return copy; }

    __CDS_NoDiscard auto copy () const noexcept -> Iterator * override {
        return new Iterator ( * this );
    }
};

template <class T>
class Array<T>::ReverseIterator final : public IteratorBase {
public:
    ReverseIterator ( ReverseIterator const & ) noexcept = default;
    ReverseIterator ( ReverseIterator && ) noexcept = default;
    explicit ReverseIterator ( Array * pArray, Index index ) noexcept : IteratorBase( pArray, index ) { }
    ~ReverseIterator () noexcept final = default;

    __CDS_cpplang_NonConstConstexprMemberFunction ReverseIterator & operator = ( ReverseIterator const & o ) noexcept {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ReverseIterator & final { this->_index --; return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ReverseIterator & { this->_index ++; return * this; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ReverseIterator & final { this->next(); return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ReverseIterator & { return this->prev(); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ReverseIterator { auto copy = * this; this->prev(); return copy; }

    __CDS_NoDiscard auto copy () const noexcept -> ReverseIterator * override {
        return new ReverseIterator ( * this );
    }
};

template <class T>
class Array<T>::ConstIterator final : public ConstIteratorBase {
public:
    ConstIterator ( ConstIterator const & ) noexcept = default;
    ConstIterator ( ConstIterator && ) noexcept = default;
    explicit ConstIterator ( Array const * pArray, Index index ) noexcept : ConstIteratorBase( pArray, index ) { }
    ~ConstIterator () noexcept final = default;

    __CDS_cpplang_NonConstConstexprMemberFunction ConstIterator & operator = ( ConstIterator const & o ) noexcept {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstIterator & final { this->_index ++; return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ConstIterator & { this->_index --; return * this; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstIterator & override { this->next(); return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstIterator & { return this->prev(); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ConstIterator { auto copy = * this; this->prev(); return copy; }

    __CDS_NoDiscard auto copy () const noexcept -> ConstIterator * override {
        return new ConstIterator ( * this );
    }
};

template<class T>
class Array<T>::ConstReverseIterator final : public ConstIteratorBase {
public:
    ConstReverseIterator ( ConstReverseIterator const & ) noexcept = default;
    ConstReverseIterator ( ConstReverseIterator && ) noexcept = default;
    explicit ConstReverseIterator ( Array const * pArray, Index index ) noexcept : ConstIteratorBase( pArray, index ) { }
    ~ConstReverseIterator () noexcept final = default;

    __CDS_cpplang_NonConstConstexprMemberFunction ConstReverseIterator & operator = ( ConstReverseIterator const & o ) noexcept {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstReverseIterator & final { this->_index --; return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ConstReverseIterator & { this->_index ++; return * this; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstReverseIterator & { this->next(); return * this; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstReverseIterator & { return this->prev(); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ConstReverseIterator { auto copy = * this; this->prev(); return copy; }

    __CDS_NoDiscard auto copy () const noexcept -> ConstReverseIterator * override {
        return new ConstReverseIterator ( * this );
    }
};

template < typename T >
template < typename V, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type >
Array<T>::Array( std::initializer_list < ElementType > const & initializerList ) noexcept {
    for ( auto & e : initializerList )
        this->pushBack( e );
}

template <class T>
Array<T>::~Array() noexcept {
    for ( Index i = 0; i < this->_capacity; i++ )
        delete this->_pData[i];
    delete [] this->_pData;
}

template < typename T >
auto Array < T > :: allocFrontGetPtr () noexcept -> ElementPtrRef {
    auto newSize = this->_capacity + 1;
    T ** partBuffer = new T * [newSize];
    std::memcpy ( partBuffer + 1, this->_pData, this->_capacity * sizeof ( T * ) );

    delete [] this->_pData;
    this->_pData = partBuffer;

    ++ this->_size;
    this->_capacity = newSize;

    return (this->_pData[0] = nullptr);
}

template < typename T >
auto Array < T > :: allocBackGetPtr () noexcept -> ElementPtrRef {
    auto newSize = this->_capacity + 1;
    T ** newBuf = new T * [newSize];
    std::memcpy ( newBuf, this->_pData, this->_size * sizeof(T *) );
    std::memcpy ( newBuf + this->_size + 1, this->_pData + this->_size, ( this->_capacity - this->_size ) * sizeof(T *) );
    this->_capacity = newSize;
    delete [] this->_pData;
    this->_pData = newBuf;

    return (this->_pData[this->_size ++] = nullptr);
}

template <class T>
auto Array<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return {"[ ]"};

    std::stringstream out;
    out << "[ ";

    for ( const auto & e : (*this) )
        Type < T > :: streamPrint( out, e ) << ", ";

    auto s = out.str();
    return s.substr(0, s.length() - 2).append(" ]");
}

template <class T>
__CDS_MaybeUnused auto Array<T>::expandWith(Size requiredSize) noexcept -> void {
    if ( this->_size + requiredSize < this->_capacity ) return;
#if defined(_MSC_VER)
#pragma push_macro("max")
#undef max
#endif
    return this->_resize(std::max(this->_size + requiredSize, this->_capacity * 2));
#if defined(_MSC_VER)
#pragma pop_macro("max")
#endif
}

template <class T>
auto Array<T>::shrinkToSize(Size size) noexcept -> void {
    if ( this->_capacity <= size ) return;
    return this->_resize(size);
}

template <class T>
auto Array<T>::_resize(Size size) noexcept -> void {
    auto newMemory = new ElementType * [ size ];

    for ( Index i = 0; i < size; i++ ) {
        if ( i < this->_capacity )
            newMemory[i] = this->_pData[i];
        else
            newMemory[i] = new ElementType;
    }

    if ( this->_capacity > size )
        for ( auto i = static_cast < Index > ( size ); i < this->_capacity; i ++ )
            delete this->_pData[i];

    delete [] this->_pData;
    this->_pData = newMemory;
    this->_capacity = size;
}

template <class T>
Array<T>::Array( Array const & o ) noexcept {
    this->_resize(o._size);
    for ( Index i = 0; i < o._size; i++ )
        * this->_pData [i] = * o._pData[i];

    this->_size = o._size;
}

template <class T>
Array<T>::Array( Array && moveObj ) noexcept {
    this->_pData = exchange(moveObj._pData, nullptr);
    this->_size = exchange(moveObj._size, 0);
    this->_capacity = exchange(moveObj._capacity, 0);
}

#include <CDS/Pointer>
template <class T>
Array<T>::Array(
        typename Collection<ElementType>::Iterator const & from,
        typename Collection<ElementType>::Iterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template <class T>
Array<T>::Array(
        typename Collection<ElementType>::ConstIterator const & from,
        typename Collection<ElementType>::ConstIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template <class T>
Array<T>::Array ( Size size, ElementCRef defaultValue ) noexcept {
    this->_resize(size);
    this->_size = size;
    for ( Index i = 0; i < this->_size; i++ )
        * this->_pData[i] = defaultValue;
}

template <class T>
auto Array<T>::remove(ElementCRef e, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! Type < T > :: compare ( * this->_pData[i], e ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete this->_pData[i];
        }

    this->_capacity = this->size();
    this->_size = l;
    delete [] this->_pData;
    return removed;
}

#include <CDS/Range>
template <class T>
auto Array<T>::removeLast(ElementCRef e) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( Type < T > :: compare ( * this->_pData[i], e ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return true;
}

template <class T>
auto Array<T>::removeOf(Collection<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! elements.contains ( * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete this->_pData[i];
        }

    this->_capacity = this->size();
    this->_size = l;
    delete [] this->_pData;
    return removed;
}

template <class T>
auto Array<T>::removeOf(std::initializer_list<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! Collection < T > :: iListContains ( elements, * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete this->_pData[i];
        }

    this->_capacity = this->size();
    this->_size = l;
    delete [] this->_pData;
    return removed;
}

template <class T>
auto Array<T>::removeNotOf(Collection<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( elements.contains ( * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete this->_pData[i];
        }

    this->_capacity = this->size();
    this->_size = l;
    delete [] this->_pData;
    return removed;
}

template <class T>
auto Array<T>::removeNotOf(std::initializer_list<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( Collection < T > :: iListContains( elements, * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete this->_pData[i];
        }

    this->_capacity = this->size();
    this->_size = l;
    delete [] this->_pData;
    return removed;
}

template <class T>
auto Array<T>::removeLastOf(Collection<ElementType> const & elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( elements.contains( * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return true;
}

template <class T>
auto Array<T>::removeLastOf(std::initializer_list<ElementType> const & elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( Collection<T>::iListContains( elements, * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return true;
}

template <class T>
auto Array<T>::removeLastNotOf(Collection<ElementType> const & elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( ! elements.contains( * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return true;
}

template <class T>
auto Array<T>::removeLastNotOf(std::initializer_list<ElementType> const & elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( ! Collection < T > ::iListContains( elements, * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return true;
}

#include <CDS/Utility>
template <class T>
auto Array<T>::remove( typename Collection<ElementType>::Iterator const & it ) noexcept (false) -> ElementType {
    if ( ! Collection < T > :: iteratorIsOf (it, *this) )
        throw IllegalArgumentException("Iterator given is not of this collection");

    Index at = reinterpret_cast < Iterator const * > ( & it )->_index;

    if ( at < 0 || at >= this->size() )
        throw OutOfBoundsException(at, this->size());


    T retVal = * this->_pData[at];
    delete this->_pData[at];

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    -- this->_size;
    this->_capacity = this->size();
    return retVal;
}

template <class T>
auto Array<T>::clear() noexcept -> void {
    this->_size = 0;
}

template <class T>
auto Array<T>::makeUnique() noexcept -> void {
    T ** pNewData = new T * [this->size()];
    Size l = 0;

    static auto newArrContains = [](T ** p, Size l, ElementCRef e) noexcept -> bool {
        for ( Index i = 0; i < l; ++ i )
            if ( Type < T > :: compare ( * p[i], e ) )
                return true;
        return false;
    };

    for ( Index i = 0; i < this->size(); ++ i )
        if ( ! newArrContains(pNewData, l, * this->_pData[i]) )
            pNewData[l ++] = this->_pData[i];
        else
            delete this->_pData[i];

    this->_capacity = this->size();
    this->_size = l;
    this->_pData = pNewData;
}

template <class T>
auto Array<T>::contains( ElementCRef value ) const noexcept -> bool {
    for ( auto & e : * this ) // NOLINT(readability-use-anyofallof)
        if ( Type < T > :: compare ( e, value ) )
            return true;
    return false;
}

template <class T>
auto Array<T>::index( ElementCRef value ) const noexcept -> Index {
    Index i = 0;
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, value ) )
            return i;
        else
            i++;
    return -1;
}

template <class T>
auto Array<T>::index( ElementRef value ) noexcept -> Index {
    Index i = 0;
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, value ) )
            return i;
        else
            i++;
    return -1;
}

#include <CDS/LinkedList>

template <class T>
__CDS_MaybeUnused auto Array<T>::indices( ElementCRef value ) const noexcept -> DoubleLinkedList < Index > {
    DoubleLinkedList < Index > indices;

    Index i = 0;
    for ( auto & e : * this ) {
        if ( Type < T > :: compare ( e, value ) )
            indices.pushBack(i);
        i++;
    }

    return indices;
}

#include <CDS/Utility>
template < typename T >
auto Array < T > :: pAt ( Index i ) noexcept (false) -> ElementPtr {
    if ( i < 0 || this->_capacity <= i )
        throw OutOfBoundsException ( i, this->_capacity );

    return this->_pData[i];
}

template < typename T >
auto Array < T > :: pAt ( Index i ) const noexcept (false) -> ElementCPtr {
    if ( this->empty() )
        throw OutOfBoundsException ( i, 0 );

    if ( i < 0 )
        i += ( this->size() / (-i) ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_pData[i];
}

template <class T>
Array<T> & Array<T>::operator= (Collection<ElementType> const & c) noexcept {
    if ( this == & c ) return * this;

    this->clear();

    auto pBegin = Collection<T>::beginPtr(c);
    auto pEnd = Collection<T>::endPtr(c);

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        this->pushBack ( it->value() );

    delete pBegin;
    delete pEnd;
    return * this;
}

template <class T>
template <typename SortFunc>
__CDS_MaybeUnused auto Array<T>::quickSortPartition(
        Iterator from,
        Iterator to,
        SortFunc const & sortFunc
) noexcept -> Iterator {
    __CDS_cpplang_ConstexprLambda static auto swap = [] ( T & a, T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    Iterator partitionIterator ( from );
    Iterator previous (nullptr, -1);

    for ( auto it = from; it != to; it++ ) {
        if ( sortFunc ( it.value(), pivot ) ) {
            swap ( partitionIterator.value(), it.value() );
            previous = partitionIterator;
            partitionIterator.next();
        }
    }

    swap ( partitionIterator.value(), to.value() );
    if ( previous._index == -1 )
        return partitionIterator;
    return previous;
}

template <typename T>
template <typename SortFunc>
__CDS_MaybeUnused auto Array<T>::quickSort(
        Iterator from,
        Iterator to,
        SortFunc const & sortFunc
) noexcept -> void {
    __CDS_cpplang_ConstexprLambda static auto validIterator = []( Iterator & it ) noexcept->bool { return it._index >= 0 && it._index < it._pArray->_size; };

    auto next = to;
    if ( next._index < next._pArray->_size ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && validIterator(from) && validIterator(to) ) {
        auto partitionIterator = Array::quickSortPartition(from, to, sortFunc);

        Array::quickSort(from, partitionIterator, sortFunc);

        if ( ! validIterator(partitionIterator) )
            return;

        if ( partitionIterator == from ) {
            partitionIterator.next();
            if ( validIterator ( partitionIterator ) )
                Array::quickSort(partitionIterator, to, sortFunc);
            return;
        }

        partitionIterator.next();
        if ( ! validIterator(partitionIterator) )
            return;
        partitionIterator.next();
        Array::quickSort( partitionIterator, to, sortFunc );
    }
}

template <class T>
template < typename SortFunc >
auto Array<T>::sort(SortFunc const & sortFunc) noexcept -> void {
    if ( this->size() < 2 )
        return;

    Array::quickSort( this->begin(), -- this->end(), sortFunc );
}

#include <CDS/Sequence>

template < typename T >
auto Array < T > :: sequence () const & noexcept -> Sequence < const Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto Array < T > :: sequence () & noexcept -> Sequence < Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto Array < T > :: sequence () const && noexcept -> Sequence < const Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

template < typename T >
auto Array < T > :: sequence () && noexcept -> Sequence < Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

#if __CDS_cpplang_CTAD_available == true

template < typename T >
Array ( std::initializer_list < T > ) -> Array < T >;

#endif

#endif //CDS_ARRAY_HPP
