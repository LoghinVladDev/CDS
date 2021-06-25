//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_STATICARRAY_HPP
#define CDS_STATICARRAY_HPP

#include <CDS/LinkedList>
#include <CDS/Array>

template <class T, Size n>
class StaticArray final : public List <T> {
private:
    T ** _pData     {nullptr };

    using Value                 = T;
    using ValueReference        = T &;
    using ValueConstReference   = T const &;

    class IteratorBase;
    class ConstIteratorBase;

public:

    class Iterator final : public IteratorBase {
    public:
        Iterator () noexcept = default;
        Iterator ( Iterator const & ) noexcept = default;
        Iterator ( Iterator && ) noexcept = default;
        explicit Iterator ( StaticArray * pArray, Index index ) noexcept : IteratorBase( pArray, index ) { }
        ~Iterator () noexcept final = default;

        constexpr Iterator & operator = ( Iterator const & o ) noexcept {
            if ( this == & o ) return * this;

            this->_pArray = o._pArray;
            this->_index = o._index;
            return * this;
        }

        constexpr auto next () noexcept -> Iterator & final { this->_index ++; return * this; }
        constexpr auto prev () noexcept -> Iterator & { this->_index --; return * this; }

        constexpr auto operator ++ () noexcept -> Iterator & { return this->next(); }
        constexpr auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
        constexpr auto operator -- () noexcept -> Iterator & { return this->prev(); }
        constexpr auto operator -- (int) noexcept -> Iterator { auto copy = * this; this->prev(); return copy; }
    };

    class ReverseIterator final : public IteratorBase {
    public:
        ReverseIterator () noexcept = default;
        ReverseIterator ( ReverseIterator const & ) noexcept = default;
        ReverseIterator ( ReverseIterator && ) noexcept = default;
        explicit ReverseIterator ( StaticArray * pArray, Index index ) noexcept : IteratorBase( pArray, index ) { }
        ~ReverseIterator () noexcept final = default;

        constexpr ReverseIterator & operator = ( ReverseIterator const & o ) noexcept {
            if ( this == & o ) return * this;

            this->_pArray = o._pArray;
            this->_index = o._index;
            return * this;
        }

        constexpr auto next () noexcept -> ReverseIterator & final { this->_index --; return * this; }
        constexpr auto prev () noexcept -> ReverseIterator & { this->_index ++; return * this; }

        constexpr auto operator ++ () noexcept -> ReverseIterator & { this->next(); return * this; }
        constexpr auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
        constexpr auto operator -- () noexcept -> Iterator & { return this->prev(); }
        constexpr auto operator -- (int) noexcept -> Iterator { auto copy = * this; this->prev(); return copy; }
    };

    class ConstIterator final : public ConstIteratorBase {
    public:
        ConstIterator () noexcept = default;
        ConstIterator ( ConstIterator const & ) noexcept = default;
        ConstIterator ( ConstIterator && ) noexcept = default;
        explicit ConstIterator ( StaticArray const * pArray, Index index ) noexcept : ConstIteratorBase( pArray, index ) { }
        ~ConstIterator () noexcept final = default;

        constexpr ConstIterator & operator = ( ConstIterator const & o ) noexcept {
            if ( this == & o ) return * this;

            this->_pArray = o._pArray;
            this->_index = o._index;
            return * this;
        }

        constexpr auto next () noexcept -> ConstIterator & final { this->_index ++; return * this; }
        constexpr auto prev () noexcept -> ConstIterator & { this->_index --; return * this; }

        constexpr auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }
        constexpr auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
        constexpr auto operator -- () noexcept -> Iterator & { return this->prev(); }
        constexpr auto operator -- (int) noexcept -> Iterator { auto copy = * this; this->prev(); return copy; }
    };

    class ConstReverseIterator final : public ConstIteratorBase {
    public:
        ConstReverseIterator () noexcept = default;
        ConstReverseIterator ( ConstReverseIterator const & ) noexcept = default;
        ConstReverseIterator ( ConstReverseIterator && ) noexcept = default;
        explicit ConstReverseIterator ( StaticArray const * pArray, Index index ) noexcept : ConstIteratorBase( pArray, index ) { }
        ~ConstReverseIterator () noexcept final = default;

        constexpr ConstReverseIterator & operator = ( ConstReverseIterator const & o ) noexcept {
            if ( this == & o ) return * this;

            this->_pArray = o._pArray;
            this->_index = o._index;
            return * this;
        }

        constexpr auto next () noexcept -> ConstReverseIterator & final { this->_index --; return * this; }
        constexpr auto prev () noexcept -> ConstReverseIterator & { this->_index ++; return * this; }
        constexpr auto operator ++ () noexcept -> ConstReverseIterator & { this->next(); return * this; }
        constexpr auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }

        constexpr auto operator -- () noexcept -> Iterator & { return this->prev(); }
        constexpr auto operator -- (int) noexcept -> Iterator { auto copy = * this; this->prev(); return copy; }
    };

    StaticArray() noexcept = default;
    StaticArray( StaticArray const & ) noexcept;
    StaticArray( StaticArray && ) noexcept;
    StaticArray(
            typename Collection<Value>::Iterator const &,
            typename Collection<Value>::Iterator const &
    ) noexcept;
    StaticArray(
            typename Collection<Value>::ConstIterator const &,
            typename Collection<Value>::ConstIterator const &
    ) noexcept;

    StaticArray( std::initializer_list <Value> const & values ) noexcept {
        Index i = 0;
        for ( auto const & e : values )
            this->operator[](i++) = e;
    }

    explicit StaticArray( ValueConstReference ) noexcept;

    ~StaticArray() noexcept final;

private:
    inline auto beginPtr () noexcept -> Iterator * final { return new Iterator( this, 0 ); }
    inline auto endPtr () noexcept -> Iterator * final { return new Iterator(this, this->size()); }
    inline auto beginPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, 0 ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, this->size()); }

public:
    constexpr auto begin () noexcept -> Iterator { return Iterator ( this, 0 ); }
    constexpr auto begin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    constexpr auto cbegin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    constexpr auto end () noexcept -> Iterator { return Iterator ( this, this->size() ); }
    constexpr auto end () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }
    constexpr auto cend () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }

    constexpr auto rbegin () noexcept -> ReverseIterator { return ReverseIterator ( this, this->size () - 1 ); }
    constexpr auto rbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    constexpr auto crbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    constexpr auto rend() noexcept -> ReverseIterator { return ReverseIterator(this, -1); }
    constexpr auto rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }
    constexpr auto crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }

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

    [[nodiscard]] inline auto size() const noexcept -> Size { return n; }

    constexpr auto back () noexcept (false) -> ValueReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();
        return * this->_pData[n - 1];
    }

    constexpr auto front () noexcept (false) -> ValueReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[0];
    }

    constexpr auto back () const noexcept (false) -> ValueConstReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[n - 1];
    }

    constexpr auto front () const noexcept (false) -> ValueConstReference final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        return * this->_pData[0];
    }

    [[nodiscard]] constexpr auto empty () const noexcept -> bool final {
        return n == 0;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
    auto operator == (StaticArray const & o) const noexcept -> bool {
        if ( this == & o ) return false;
        if ( o.size() != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
            if ( ! ( i1.value() == i2.value() ) )
                return false;
        return true;
    }

    [[nodiscard]] auto equals (Object const & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype(this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(* p);
    }
#pragma clang diagnostic pop

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void final;
    auto contains ( ValueConstReference ) const noexcept -> bool final;
    [[nodiscard]] auto toString () const noexcept -> String final;

    auto index ( ValueConstReference ) const noexcept -> Index final;
    auto indices ( ValueConstReference ) const noexcept -> DoubleLinkedList < Index >;

    auto get ( Index ) noexcept (false) -> ValueReference final;
    auto get ( Index ) const noexcept (false) -> ValueConstReference final;

    auto set ( ValueConstReference, Index ) noexcept (false) -> ValueReference final;
    auto sub ( List < Value > &, Index, Index ) const noexcept (false) -> void final;

    inline auto sub ( Index from, Index to ) const noexcept(false) -> StaticArray {
        Array < T > array;
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

        this->_pData[n - 1] = p;
        * this->_pData[n - 1] = Value();

        return retVal;
    }

    auto popBack () noexcept (false) -> Value final {
        if ( this->empty() )
            throw typename List<Value>::ListOutOfBounds();

        auto retVal = * this->_pData[this->size() - 1];
        * this->_pData[this->size() - 1] = Value();

        return retVal;
    }

    auto pushFront ( ValueConstReference ) noexcept -> void final;
    auto pushBack ( ValueConstReference ) noexcept -> void final;

    auto pushFront ( Value && ) noexcept -> void final;
    auto pushBack ( Value && ) noexcept -> void final;

private:
    auto static quickSort ( Iterator, Iterator, auto ) noexcept -> void;
    auto static quickSortPartition ( Iterator, Iterator, auto ) noexcept -> Iterator;

public:
    auto sort ( auto func ) noexcept -> void;

    inline auto sort ( Comparator<Value> const & c ) noexcept -> void final {
        return this->sort ( [&c] (ValueConstReference a, ValueConstReference b) noexcept -> bool { return c(a, b); } );
    }

    StaticArray & operator = ( Collection<Value> const & ) noexcept;
    inline StaticArray & operator = ( StaticArray const & o ) noexcept { return this->operator=( ( Collection<Value> const & )(o) ); } // NOLINT(bugprone-unhandled-self-assignment,misc-unconventional-assign-operator)

    [[nodiscard]] auto view () const noexcept -> View < StaticArray < T, n > >;

    [[nodiscard]] auto sequence () const noexcept -> Sequence < const StaticArray < T, n > >;
    [[nodiscard]] auto sequence () noexcept -> Sequence < StaticArray < T, n > >;
};

#include <CDS/View>
template <class T, Size n>
auto StaticArray<T, n>::view() const noexcept -> View < StaticArray <T, n > > {
    return View(*this);
}

#include <CDS/Sequence>

template <class T, Size n>
auto StaticArray<T, n>::sequence() const noexcept -> Sequence < const StaticArray <T, n > > {
    return Sequence(*this);
}

template <class T, Size n>
auto StaticArray<T, n>::sequence() noexcept -> Sequence < StaticArray <T, n> > {
    return Sequence(*this);
}

template <typename T>
StaticArray (std::initializer_list<T> l) -> StaticArray < T, l.size() >;


#endif //CDS_STATICARRAY_HPP
