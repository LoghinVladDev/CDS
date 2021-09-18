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

    using Value                 = T;
    using ValueReference        = T &;
    using ValueConstReference   = T const &;

    class IteratorBase;
    class ConstIteratorBase;

    auto expandWith ( Size ) noexcept -> void;

public:

    class Iterator;
    class ReverseIterator;
    class ConstIterator;
    class ConstReverseIterator;

    Array () noexcept = default;
    Array ( Array const & ) noexcept;
    Array ( Array && ) noexcept;
    Array (
        typename Collection<Value>::Iterator const &,
        typename Collection<Value>::Iterator const &
    ) noexcept;
    Array (
        typename Collection<Value>::ConstIterator const &,
        typename Collection<Value>::ConstIterator const &
    ) noexcept;
    Array( std::initializer_list <Value> const & ) noexcept;
    explicit Array( Size, ValueConstReference = Value() ) noexcept;

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

    auto remove ( ValueConstReference , Size ) noexcept -> bool final;
    auto removeLast ( ValueConstReference ) noexcept -> bool final;

    auto removeOf ( Collection <Value> const &, Size ) noexcept -> bool final;
    auto removeLastOf ( Collection<Value> const & ) noexcept -> bool final;
    auto removeNotOf ( Collection<Value> const &, Size ) noexcept -> bool final;
    auto removeLastNotOf ( Collection<Value> const & ) noexcept -> bool final;

    auto replace ( ValueConstReference, ValueConstReference, Size ) noexcept -> void final;
    auto replaceLast ( ValueConstReference, ValueConstReference ) noexcept -> void final;

    auto replaceOf ( Collection<Value> const &, ValueConstReference , Size ) noexcept -> void final;
    auto replaceLastOf ( Collection<Value> const &, ValueConstReference ) noexcept -> void final;
    auto replaceNotOf ( Collection<Value> const &, ValueConstReference , Size ) noexcept -> void final;
    auto replaceLastNotOf ( Collection<Value> const &, ValueConstReference ) noexcept -> void final;

    auto remove ( typename Collection<Value>::Iterator const & ) noexcept(false) -> Value final;
    auto replace ( typename Collection<Value>::Iterator const &, ValueConstReference ) noexcept -> void final;
    auto insertBefore ( typename Collection<Value>::Iterator const &, ValueConstReference ) noexcept -> void final;
    auto insertAfter ( typename Collection<Value>::Iterator const &, ValueConstReference ) noexcept -> void final;

    inline auto removeOf ( std::initializer_list<Value> const & list, Size count ) noexcept -> bool final { return this->removeOf ( Array (list), count ); }
    inline auto removeLastOf ( std::initializer_list<Value> const & list ) noexcept -> bool final { return this->removeLastOf ( Array (list) ); }
    inline auto removeNotOf ( std::initializer_list<Value> const & list, Size count ) noexcept -> bool final { return this->removeNotOf( Array (list), count ); }
    inline auto removeLastNotOf ( std::initializer_list<Value> const & list ) noexcept -> bool final { return this->removeLastNotOf( Array (list) ); }

    inline virtual auto replaceOf ( std::initializer_list<Value> const & list, ValueConstReference with, Size count ) noexcept -> void final { return this->replaceOf( Array (list), with, count ); }
    inline virtual auto replaceLastOf ( std::initializer_list<Value> const & list, ValueConstReference with ) noexcept -> void final { return this->replaceLastOf( Array (list), with ); }
    inline virtual auto replaceNotOf ( std::initializer_list<Value> const & list, ValueConstReference with, Size count ) noexcept -> void final { return this->replaceNotOf( Array (list), with, count ); }
    inline virtual auto replaceLastNotOf ( std::initializer_list<Value> const & list, ValueConstReference with ) noexcept -> void final { return this->replaceLastNotOf( Array (list), with ); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ValueReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ValueReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[0];
    }

    __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ValueConstReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ValueConstReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[0];
    }

    __CDS_NoDiscard constexpr auto empty () const noexcept -> bool final {
        return this->_size == 0;
    }

    auto operator == (Array const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( o.size() != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
            if ( ! ( Type < T > :: compare ( i1.value(), i2.value() ) ) )
                return false;
        return true;
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if (this == &o) return true;
        auto p = dynamic_cast < decltype(this) > ( &o );
        if (p == nullptr) return false;

        return this->operator==(*p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void final;
    auto contains ( ValueConstReference ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( ValueConstReference ) const noexcept -> Index final;
    auto index ( ValueReference ) noexcept -> Index final;

    __CDS_MaybeUnused auto indices ( ValueConstReference ) const noexcept -> DoubleLinkedList < Index >;

    auto get ( Index ) noexcept (false) -> ValueReference final;
    auto get ( Index ) const noexcept (false) -> ValueConstReference final;

    auto set ( ValueConstReference, Index ) noexcept (false) -> ValueReference final;
    auto sub ( List < Value > &, Index, Index ) const noexcept (false) -> void final;

    __CDS_MaybeUnused inline auto sub ( Index from, Index to ) const noexcept(false) -> Array {
        Array array;
        this->sub( array, from, to );
        return array;
    }

    auto popFront () noexcept (false) -> Value final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        auto retVal = * this->_pData[0];

        auto p = this->_pData[0];

        for ( Index i = 0; i < this->size() - 1; i ++ )
            this->_pData[i] = this->_pData[i + 1];

        this->_pData[-- this->_size] = p;

        return retVal;
    }

    auto popBack () noexcept (false) -> Value final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        auto retVal = * this->_pData[this->size() - 1];

        this->_size --;

        return retVal;
    }

    auto pushFront ( ValueConstReference ) noexcept -> void final;
    auto pushBack ( ValueConstReference ) noexcept -> void final;

    auto pushFront ( Value && ) noexcept -> void final;
    auto pushBack ( Value && ) noexcept -> void final;

private:

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

    inline auto sort ( Comparator < Value > const & c ) noexcept -> void final {
        return this->sort ( [&c] (ValueConstReference a, ValueConstReference b) noexcept -> bool { return c(a, b); } );
    }

    Array & operator = ( Collection < Value > const & ) noexcept;
    inline Array & operator = ( Array const & o ) noexcept { return this->operator=( ( Collection<Value> const & )(o) ); } // NOLINT(bugprone-unhandled-self-assignment,misc-unconventional-assign-operator)

    auto sequence () const noexcept -> Sequence < const Array < T > >;
    auto sequence () noexcept -> Sequence < Array < T > >;
};

template <class T>
class Array<T>::IteratorBase : public Collection<T>::Iterator {
protected:
    friend class Array;
    Array mutable * _pArray { nullptr };
    Index mutable   _index  { 0ull };

    IteratorBase() noexcept = default;
    IteratorBase( IteratorBase const & ) noexcept = default;
    IteratorBase( IteratorBase && ) noexcept = default;
    explicit IteratorBase( Array * pArray, Index index ) noexcept :
            Collection<T>::Iterator(),
            _pArray(pArray),
            _index(index) { }

public:
    ~IteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprConditioned auto equals ( typename Collection<T>::Iterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < IteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    constexpr auto value () const noexcept -> ValueReference final { return (* this->_pArray)[this->_index]; }

    __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;
};

template <class T>
class Array<T>::ConstIteratorBase : public Collection<T>::ConstIterator {
protected:
    friend class Array;
    Array const * _pArray { nullptr };
    Index mutable _index  { 0ull };

    ConstIteratorBase() noexcept = default;
    ConstIteratorBase( ConstIteratorBase const & ) noexcept = default;
    ConstIteratorBase( ConstIteratorBase && ) noexcept = default;
    explicit ConstIteratorBase (Array const * pArray, Index index) noexcept :
            Collection<T>::ConstIterator(),
            _pArray(pArray),
            _index(index) { }

public:
    ~ConstIteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprConditioned auto equals ( typename Collection<T>::ConstIterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < ConstIteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    constexpr auto value () const noexcept -> ValueConstReference final { return (* this->_pArray)[this->_index]; }

    __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;
};

template <class T>
class Array<T>::Iterator final : public IteratorBase {
public:
    Iterator () noexcept = default;
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
    ReverseIterator () noexcept = default;
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
    ConstIterator () noexcept = default;
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
    ConstReverseIterator () noexcept = default;
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

template <class T>
Array<T>::Array( std::initializer_list < Value > const & initializerList ) noexcept {
    for ( auto & e : initializerList )
        this->pushBack( e );
}

template <class T>
Array<T>::~Array() noexcept {
    for ( Index i = 0; i < this->_capacity; i++ )
        delete this->_pData[i];
    delete [] this->_pData;
}

template <class T>
auto Array<T>::pushFront( ValueConstReference value ) noexcept -> void {
    this->expandWith( 1 );

    auto p = this->_pData[this->_size];
    * p = value;

    for ( Index i = this->_size; i >= 1; i-- )
        this->_pData[i] = this->_pData[i - 1];

    this->_pData[0] = p;
    this->_size++;
}

template <class T>
auto Array<T>::pushFront( Value && moveValue ) noexcept -> void {
    this->expandWith( 1 );

    auto p = this->_pData[this->_size];
    * p = std::move(moveValue);

    for ( Index i = this->_size; i >= 1; i-- )
        this->_pData[i] = this->_pData[i - 1];

    this->_pData[0] = p;
    this->_size++;
}

template <class T>
auto Array<T>::pushBack(ValueConstReference value) noexcept -> void {
    this->expandWith( 1 );

    * this->_pData[this->_size ++] = value;
}

template <class T>
auto Array<T>::pushBack(Value && moveValue) noexcept -> void {
    this->expandWith( 1 );

    * this->_pData[this->_size ++] = std::move(moveValue);
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
auto Array<T>::expandWith(Size requiredSize) noexcept -> void {
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
    auto newMemory = new Value * [ size ];

    for ( Index i = 0; i < size; i++ ) {
        if ( i < this->_capacity )
            newMemory[i] = this->_pData[i];
        else
            newMemory[i] = new Value;
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
        typename Collection<Value>::Iterator const & from,
        typename Collection<Value>::Iterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template <class T>
Array<T>::Array(
        typename Collection<Value>::ConstIterator const & from,
        typename Collection<Value>::ConstIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template <class T>
Array<T>::Array ( Size size, ValueConstReference defaultValue ) noexcept {
    this->_resize(size);
    this->_size = size;
    for ( Index i = 0; i < this->_size; i++ )
        * this->_pData[i] = defaultValue;
}

template <class T>
auto Array<T>::remove(ValueConstReference e, Size count) noexcept -> bool {
    Array without;

    for ( auto & it : * this )
        if ( Type < T > :: compare ( it, e ) && count > 0 )
            count--;
        else
            without.pushBack( it );

    auto removed = without.size() != this->size();

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::removeLast(ValueConstReference e) noexcept -> bool {
    Array without;
    bool removed = false;

    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( Type < T > :: compare ( it.value(), e ) && ! removed )
            removed = true;
        else
            without.pushFront( it.value() );

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::removeOf(Collection<Value> const & elements, Size count) noexcept -> bool {
    Array without;

    for ( auto & it : * this )
        if ( elements.contains(it) && count > 0 )
            count --;
        else
            without.pushBack(it);

    auto removed = without.size() != this->size();

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::removeNotOf(Collection<Value> const & elements, Size count) noexcept -> bool {
    Array without;

    for ( auto & it : * this )
        if ( ! elements.contains(it) && count > 0 )
            count --;
        else
            without.pushBack(it);

    auto removed = without.size() != this->size();

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::removeLastOf(Collection<Value> const & elements) noexcept -> bool {
    Array without;
    bool removed = false;

    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( elements.contains(it.value()) && ! removed )
            removed = true;
        else
            without.pushBack(it.value());

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::removeLastNotOf(Collection<Value> const & elements) noexcept -> bool {
    Array without;
    bool removed = false;

    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( ! elements.contains(it.value()) && ! removed )
            removed = true;
        else
            without.pushBack(it.value());

    * this = without;
    return removed;
}

template <class T>
auto Array<T>::replace(ValueConstReference what, ValueConstReference with, Size count) noexcept -> void {
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, what ) && count > 0 ) {
            e = with;
            count --;
        } else if ( count == 0 )
            break;
}

template <class T>
auto Array<T>::replaceOf(Collection<Value> const & what, ValueConstReference with, Size count) noexcept -> void {
    for ( auto & e : * this )
        if ( what.contains(e) && count > 0 ) {
            e = with;
            count --;
        } else if ( count == 0 )
            break;
}

template <class T>
auto Array<T>::replaceNotOf(Collection<Value> const & what, ValueConstReference with, Size count) noexcept -> void {
    for ( auto & e : * this )
        if ( ! what.contains(e) && count > 0 ) {
            e = with;
            count --;
        } else if ( count == 0 )
            break;
}

template <class T>
auto Array<T>::replaceLast(ValueConstReference what, ValueConstReference with) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( Type < T > :: compare ( it.value(), what ) ) {
            it.value() = with;
            break;
        }
}

template <class T>
auto Array<T>::replaceLastOf(Collection<Value> const & what, ValueConstReference with) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( what.contains(it.value())  ) {
            it.value() = with;
            break;
        }
}

template <class T>
auto Array<T>::replaceLastNotOf(Collection<Value> const & what, ValueConstReference with) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it ++ )
        if ( ! what.contains(it.value())  ) {
            it.value() = with;
            break;
        }
}

template <class T>
auto Array<T>::remove( typename Collection<Value>::Iterator const & it ) noexcept (false) -> Value {
    if ( this->empty() )
        throw typename List<Value>::ListOutOfBounds();

    Array without;

    for (auto i = this->begin(); i != this->end(); i ++ )
        if ( ! i.equals(it) )
            without.pushBack(i.value());

    auto v = it.value();

    * this = without;

    return v;
}

template <class T>
auto Array<T>::replace ( typename Collection<Value>::Iterator const & iterator, ValueConstReference value ) noexcept -> void {
    iterator.value() = value;
}

template <class T>
auto Array<T>::insertBefore( typename Collection<Value>::Iterator const & iterator, ValueConstReference value) noexcept -> void {
    Array newArray;

    auto it = this->begin();
    while ( it != this->end() && ! ( Type < T > :: compare ( it.value(), value )) ) {
        newArray.pushBack(it.value());
        it ++;
    }

    newArray.pushBack( value );

    while ( it != this->end() ) {
        newArray.pushBack(it.value());
        it ++;
    }

    * this = newArray;
}

template <class T>
auto Array<T>::insertAfter(typename Collection<Value>::Iterator const & iterator, ValueConstReference value) noexcept -> void {
    Array newArray;

    auto it = this->begin();
    while ( it != this->end() && ! ( Type < T > :: compare ( it.value(), value ) ) ) {
        newArray.pushBack(it.value());
        it ++;
    }

    newArray.pushBack(it.value());
    it ++;

    newArray.pushBack( value );

    while ( it != this->end() ) {
        newArray.pushBack(it.value());
        it ++;
    }

    * this = newArray;
}

template <class T>
auto Array<T>::clear() noexcept -> void {
    this->_size = 0;
}

template <class T>
auto Array<T>::makeUnique() noexcept -> void {
    Array newArray;

    for ( auto & e : * this )
        if ( ! newArray.contains(e) )
            newArray.pushBack( e );

    * this = newArray;
}

template <class T>
auto Array<T>::contains( ValueConstReference value ) const noexcept -> bool {
    for ( auto & e : * this ) // NOLINT(readability-use-anyofallof)
        if ( Type < T > :: compare ( e, value ) )
            return true;
    return false;
}

template <class T>
auto Array<T>::index( ValueConstReference value ) const noexcept -> Index {
    Index i = 0;
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, value ) )
            return i;
        else
            i++;
    return -1;
}

template <class T>
auto Array<T>::index( ValueReference value ) noexcept -> Index {
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
__CDS_MaybeUnused auto Array<T>::indices( ValueConstReference value ) const noexcept -> DoubleLinkedList < Index > {
    DoubleLinkedList < Index > indices;

    Index i = 0;
    for ( auto & e : * this ) {
        if ( Type < T > :: compare ( e, value ) )
            indices.pushBack(i);
        i++;
    }

    return indices;
}

template <class T>
auto Array<T>::get(Index i) noexcept (false) -> ValueReference {
    if ( i < 0 || this->_capacity <= i )
        throw typename List<Value>::ListOutOfBounds();

    return * this->_pData[i];
}

template <class T>
auto Array<T>::get(Index i) const noexcept (false) -> ValueConstReference {
    if ( i < 0 || this->_capacity <= i )
        throw typename List<Value>::ListOutOfBounds();

    return * this->_pData[i];
}

template <class T>
auto Array<T>::set( ValueConstReference v, Index i ) noexcept (false) -> ValueReference {
    if ( i < 0 || this->_capacity <= i )
        throw typename List<Value>::ListOutOfBounds();

    return ( * this->_pData[i] = v );
}

template <class T>
auto Array<T>::sub( List<Value> & container, Index from, Index to ) const noexcept(false) -> void {
//    auto swap = [] ( auto & a, auto & b ) { auto aux = a; a = b; b = aux; };
    if ( from > to )
        std::swap ( from, to );

    if ( from < 0 ) from = 0;
    if ( to >= this->_capacity ) to = this->_capacity;

    container.clear();

    for ( Index i = from; i < to; i++ )
        container.pushBack( * this->_pData[i] );
}

template <class T>
Array<T> & Array<T>::operator= (Collection<T> const & c) noexcept {
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
    Iterator previous;
    previous._index = -1;

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
auto Array < T > :: sequence () const noexcept -> Sequence < const Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto Array < T > :: sequence () noexcept -> Sequence < Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

#endif //CDS_ARRAY_HPP
