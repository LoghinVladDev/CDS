//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LINKEDLIST_HPP
#define CDS_LINKEDLIST_HPP

#include <std-types.h>
#include <List.hpp>
#include <initializer_list>
#include <concepts>

#include <LinkedListPublic.hpp>


template <class T>
class DoubleLinkedList final : public List<T> {
private:
    using Node = dataTypes::DoubleListNode<T>;

    Node * _pFront  { nullptr };
    Node * _pBack   { nullptr };

private:

    class IteratorBase : public Collection<T>::Iterator {
    protected:
        mutable Node * _pNode { nullptr };

        IteratorBase() noexcept = default;
        IteratorBase( const IteratorBase & ) noexcept = default;
        IteratorBase(IteratorBase && ) noexcept = default;
        explicit IteratorBase ( Node * pNode ) : Collection<T>::Iterator() {
            this->_pNode = pNode;
        }

    public:
        ~IteratorBase () override = default;

        constexpr inline auto equals ( const typename Collection<T>::Iterator & o ) const noexcept -> bool final { return dynamic_cast < const IteratorBase & > ( o )._pNode == this->_pNode;}
        constexpr inline auto value () const noexcept -> T& final { return this->_pNode->data; }
    };

    class ConstIteratorBase : public Collection<T>::ConstIterator {
    protected:
        const Node * _pNode { nullptr };

        ConstIteratorBase() noexcept = default;
        ConstIteratorBase( const ConstIteratorBase & ) noexcept = default;
        ConstIteratorBase(ConstIteratorBase && ) noexcept = default;
        explicit ConstIteratorBase ( const Node * pNode ) : Collection<T>::ConstIterator() {
            this->_pNode = pNode;
        }

    public:
        ~ConstIteratorBase () override = default;

        constexpr inline auto equals ( const typename Collection<T>::ConstIterator & o ) const noexcept -> bool final { return this->_pNode == dynamic_cast < const ConstIteratorBase & > ( o )._pNode; }
        constexpr inline auto value () const noexcept -> const T& final { return this->_pNode->data; }
    };

public:

    class Iterator final : public IteratorBase{
    public:
        Iterator() noexcept = default;
        Iterator( const Iterator & ) noexcept = default;
        Iterator( Iterator && ) noexcept = default;

        inline Iterator & operator = ( const Iterator & o ) noexcept {
            this->_pNode = o._pNode;
            return * this;
        }

        constexpr inline auto operator ++ () noexcept -> Iterator & { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
        explicit Iterator( Node * pNode ) : IteratorBase ( pNode ) { }
        constexpr inline auto next () noexcept -> Iterator & final { this->_pNode = this->_pNode->pNext; return * this; }
        ~Iterator() noexcept final = default;
    };

    class ReverseIterator final : public IteratorBase {
    public:
        ReverseIterator() noexcept = default;
        ReverseIterator( const ReverseIterator & ) noexcept = default;
        ReverseIterator( ReverseIterator && ) noexcept = default;

        inline ReverseIterator & operator = ( const ReverseIterator & o ) noexcept {
            this->_pNode = o._pNode;
            return * this;
        }

        constexpr inline auto operator ++ () noexcept -> ReverseIterator & { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
        explicit ReverseIterator ( Node * pNode ) : IteratorBase( pNode ) { }
        constexpr inline auto next () noexcept -> ReverseIterator & final { this->_pNode = this->_pNode->pPrevious; return * this; }
        ~ReverseIterator() noexcept final = default;
    };

    class ConstIterator final : public ConstIteratorBase {
    public:
        ConstIterator() noexcept = default;
        ConstIterator( const ConstIterator & ) noexcept = default;
        ConstIterator( ConstIterator && ) noexcept = default;

        inline ConstIterator & operator = ( const ConstIterator & o ) noexcept {
            this->_pNode = o._pNode;
            return * this;
        }

        constexpr inline auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
        explicit ConstIterator ( const Node * pNode ) : ConstIteratorBase( pNode ) { }
        constexpr inline auto next () noexcept -> ConstIterator & final { this->_pNode = this->_pNode->pNext; return * this; }
        ~ConstIterator() noexcept final = default;
    };

    class ConstReverseIterator final : public ConstIteratorBase {
    public:
        ConstReverseIterator() noexcept = default;
        ConstReverseIterator( const ConstReverseIterator & ) noexcept = default;
        ConstReverseIterator( ConstReverseIterator && ) noexcept = default;

        inline ConstReverseIterator & operator = ( const ConstReverseIterator & o ) noexcept {
            this->_pNode = o._pNode;
            return * this;
        }

        constexpr inline auto operator ++ () noexcept -> ConstReverseIterator & { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }
        explicit ConstReverseIterator ( const Node * pNode ) : ConstIteratorBase( pNode ) { }
        constexpr inline auto next () noexcept -> ConstReverseIterator & final { this->_pNode = this->_pNode->pPrevious; return * this; }
        ~ConstReverseIterator() noexcept final = default;
    };

    DoubleLinkedList(  ) noexcept = default;
    DoubleLinkedList( const DoubleLinkedList & ) noexcept;
    DoubleLinkedList( DoubleLinkedList && ) noexcept;
    DoubleLinkedList(
            const typename Collection<T>::Iterator &,
            const typename Collection<T>::Iterator &
    ) noexcept;

    DoubleLinkedList(
            const typename Collection<T>::ConstIterator &,
            const typename Collection<T>::ConstIterator &
    ) noexcept;
    DoubleLinkedList( const std::initializer_list < T > & ) noexcept;

    ~DoubleLinkedList() noexcept final;

private:
    inline auto beginPtr () noexcept -> Iterator * final { return new Iterator( this->_pFront ); }
    inline auto endPtr () noexcept -> Iterator * final { return new Iterator(nullptr ); }
    inline auto beginPtr () const noexcept -> ConstIterator * final  { return new ConstIterator( this->_pFront ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator(nullptr ); }

//    auto findPtr ( T & ) noexcept -> Iterator & final {return this->front();}
//    auto findPtr ( const T & ) const noexcept -> ConstIterator & final {return this->front();}

public:
    constexpr inline auto begin () noexcept -> Iterator { return Iterator(this->_pFront); }
    constexpr inline auto end () noexcept -> Iterator { return Iterator(nullptr); }
    constexpr inline auto begin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront); }
    constexpr inline auto end () const noexcept -> ConstIterator { return ConstIterator (nullptr); }
    constexpr inline auto cbegin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront); }
    constexpr inline auto cend () const noexcept -> ConstIterator { return ConstIterator (nullptr); }

    constexpr inline auto rbegin () noexcept -> ReverseIterator { return ReverseIterator(this->_pBack); }
    constexpr inline auto rend () noexcept -> ReverseIterator { return ReverseIterator(nullptr); }
    constexpr inline auto rbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->_pBack); }
    constexpr inline auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (nullptr); }
    constexpr inline auto crbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->_pBack); }
    constexpr inline auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (nullptr); }

    auto remove ( const T &, Size ) noexcept -> bool final;
    auto removeLast ( const T & ) noexcept -> bool final;

    auto removeOf ( const Collection<T> &, Size ) noexcept -> bool final;
    auto removeLastOf ( const Collection<T> & ) noexcept -> bool final;

    auto removeNotOf ( const Collection<T> &, Size ) noexcept -> bool final;
    auto removeLastNotOf ( const Collection<T> & ) noexcept -> bool final;

    auto replace ( const T &, const T &, Size ) noexcept -> void final;
    auto replaceLast ( const T &, const T & ) noexcept -> void final;

    auto replaceOf ( const Collection<T> &, const T &, Size ) noexcept -> void final;
    auto replaceLastOf ( const Collection<T> &, const T & ) noexcept -> void final;

    auto replaceNotOf ( const Collection<T> &, const T &, Size ) noexcept -> void final;
    auto replaceLastNotOf ( const Collection<T> &, const T & ) noexcept -> void final;

    auto remove ( const typename Collection<T>::Iterator & ) noexcept (false) -> T final;
    auto replace( const typename Collection<T>::Iterator &, const T & ) noexcept -> void final;
    auto insertBefore( const typename Collection<T>::Iterator &, const T & ) noexcept -> void final;
    auto insertAfter( const typename Collection<T>::Iterator &, const T & ) noexcept -> void final;

    inline auto removeOf ( const std::initializer_list<T> & list, Size count ) noexcept -> bool final { return this->removeOf ( DoubleLinkedList <T> (list), count ); }
    inline auto removeLastOf ( const std::initializer_list<T> & list ) noexcept -> bool final { return this->removeLastOf ( DoubleLinkedList<T> (list) ); }

    inline auto removeNotOf ( const std::initializer_list<T> & list, Size count ) noexcept -> bool final { return this->removeNotOf( DoubleLinkedList<T> (list), count ); }
    inline auto removeLastNotOf ( const std::initializer_list<T> & list ) noexcept -> bool final { return this->removeLastNotOf( DoubleLinkedList<T> (list) ); }

    inline virtual auto replaceOf ( const std::initializer_list<T> & list, const T & with, Size count ) noexcept -> void final { return this->replaceOf( DoubleLinkedList<T> (list), with, count ); }
    inline virtual auto replaceLastOf ( const std::initializer_list<T> & list, const T & with ) noexcept -> void final { return this->replaceLastOf( DoubleLinkedList<T> (list), with ); }

    inline virtual auto replaceNotOf ( const std::initializer_list<T> & list, const T & with, Size count ) noexcept -> void final { return this->replaceNotOf( DoubleLinkedList<T> (list), with, count ); }
    inline virtual auto replaceLastNotOf ( const std::initializer_list<T> & list, const T & with ) noexcept -> void final { return this->replaceLastNotOf( DoubleLinkedList<T> (list), with ); }

    constexpr inline auto back () noexcept (false) -> T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return this->_pBack->data;
    }

    constexpr inline auto front () noexcept (false) -> T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return this->_pFront->data;
    }

    constexpr inline auto back () const noexcept (false) -> const T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return this->_pBack->data;
    }

    constexpr inline auto front () const noexcept (false) -> const T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return this->_pFront->data;
    }

    [[nodiscard]] constexpr inline auto empty () const noexcept -> bool final {
        return this->_size == 0 && this->_pFront == nullptr && this->_pBack == nullptr;
    }

    auto operator == (Object const & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype(this) > ( & o );
        if ( p == nullptr ) return false;
        if ( p->size () != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = p->begin(); i1 != this->end() && i2 != p->end(); i1++, i2++ )
            if ( ! ( i1.value() == i2.value() ) )
                return false;
        return true;
    }

    auto clear () noexcept -> void final;
    auto makeUnique ()  noexcept -> void final;
    auto contains ( const T & ) const noexcept -> bool final;

    [[nodiscard]] auto toString () const noexcept -> String final;

    auto index ( T const & ) const noexcept -> Index final;

    auto get ( Index ) noexcept (false) -> T & final;
    auto get ( Index ) const noexcept (false) -> const T & final;

    auto set ( const T &, Index ) noexcept (false) -> T & final;
    auto sub ( List <T> &, Index, Index ) const noexcept (false) -> void final;
    inline auto sub ( Index from, Index to ) const noexcept (false) -> DoubleLinkedList < T > {
        DoubleLinkedList < T > list;
        this->sub ( list, from, to );
        return list;
    }

    auto popFront ( ) noexcept (false) -> T final {
        if ( this->empty () )
            throw typename List<T>::ListOutOfBounds();

        this->_size --;

        auto node = this->_pFront;
        T value = node->data;

        if ( this->size() == 0 ) {
            this->_pFront = this->_pBack = nullptr;
            delete node;
            return value;
        }

        this->_pFront = this->_pFront->pNext;
        delete node;
        this->_pFront->pPrevious = nullptr;

        return value;
    }

    auto popBack ( ) noexcept (false) -> T final {
        if ( this->empty () )
            throw typename List<T>::ListOutOfBounds();

        this->_size --;

        auto node = this->_pBack;
        T value = node->data;

        if ( this->size() == 0 ) {
            this->_pBack = this->_pFront = nullptr;
            delete node;
            return value;
        }

        this->_pBack = this->_pBack->pPrevious;
        delete node;
        this->_pBack->pNext = nullptr;

        return value;
    }

    auto pushFront ( const T & ) noexcept -> void final;
    auto pushBack ( const T & ) noexcept -> void final;

    auto pushFront ( T && ) noexcept -> void final;
    auto pushBack ( T && ) noexcept -> void final;

private:

#define GEN_QUICKSORT_FUNCTION(_paramType, _exceptSpec) \
    auto static quickSort ( Iterator, Iterator, dataTypes::_paramType ) _exceptSpec -> void; \
    auto static quickSortPartition ( Iterator, Iterator, dataTypes::_paramType ) _exceptSpec -> Iterator;

    GEN_QUICKSORT_FUNCTION(ValueCompareFunction<T>, noexcept)
    GEN_QUICKSORT_FUNCTION(ReferenceCompareFunction<T>, noexcept)
    GEN_QUICKSORT_FUNCTION(ConstReferenceCompareFunction<T>, noexcept)

    GEN_QUICKSORT_FUNCTION(ThrowValueCompareFunction<T>, noexcept (false) )
    GEN_QUICKSORT_FUNCTION(ThrowReferenceCompareFunction<T>, noexcept (false) )
    GEN_QUICKSORT_FUNCTION(ThrowConstReferenceCompareFunction<T>, noexcept (false) )

#undef GEN_QUICKSORT_FUNCTION

    auto static quickSort ( Iterator, Iterator, auto ) noexcept -> void;
    auto static quickSortPartition ( Iterator, Iterator, auto ) noexcept -> Iterator;

public:

#define GEN_SORT_FUNC(_paramType, _exceptSpec) \
    auto sort ( dataTypes::_paramType ) _exceptSpec -> void final;

    GEN_SORT_FUNC(ValueCompareFunction<T>, noexcept)
    GEN_SORT_FUNC(ReferenceCompareFunction<T>, noexcept)
    GEN_SORT_FUNC(ConstReferenceCompareFunction <T> = [](const T & a, const T & b) noexcept -> bool { return a < b; }, noexcept)

    GEN_SORT_FUNC(ThrowValueCompareFunction<T>, noexcept (false) )
    GEN_SORT_FUNC(ThrowReferenceCompareFunction<T>, noexcept (false) )
    GEN_SORT_FUNC(ThrowConstReferenceCompareFunction<T>, noexcept (false) )

#undef GEN_SORT_FUNC

    inline auto sort ( const Comparator < T > & c) noexcept -> void final {
        auto f = ( [&c] (T const & a, T const & b) noexcept -> bool { return c(a, b); } );
        return this->sort(f);
    }

    auto sort ( auto func ) noexcept -> void;

    DoubleLinkedList & operator = ( const Collection <T> & ) noexcept;
    inline DoubleLinkedList & operator = ( const DoubleLinkedList <T> & o ) noexcept {
        return this->operator= ( (Collection<T> const & ) ( o ));
    }
};

template <class T>
DoubleLinkedList<T>::DoubleLinkedList( const std::initializer_list < T > & initializerList ) noexcept {
    for ( const auto & e : initializerList )
        this->pushBack( e );
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() noexcept {
    this->clear();
}

template <class T>
auto DoubleLinkedList<T>::pushFront(const T & value) noexcept -> void {
    auto newNode = new dataTypes::DoubleListNode<T> {value, this->_pFront, nullptr};
    if ( this->_pFront != nullptr )
        this->_pFront->pPrevious = newNode;

    this->_pFront = newNode;

    if ( this->_pBack == nullptr )
        this->_pBack = newNode;

    this->_size ++;
}

template <class T>
auto DoubleLinkedList<T>::pushBack(const T & value) noexcept -> void {
    auto newNode = new dataTypes::DoubleListNode<T> {
        value, nullptr, this->_pBack
    };

    if ( this->_pBack != nullptr )
        this->_pBack->pNext = newNode;

    this->_pBack = newNode;

    if ( this->_pFront == nullptr )
        this->_pFront = newNode;

    this->_size ++;
}

template <class T>
auto DoubleLinkedList<T>::pushFront(T && value) noexcept -> void {
    auto newNode = new dataTypes::DoubleListNode<T> {value, this->_pFront, nullptr};
    if ( this->_pFront != nullptr )
        this->_pFront->pPrevious = newNode;

    this->_pFront = newNode;

    if ( this->_pBack == nullptr )
        this->_pBack = newNode;

    this->_size ++;
}

template <class T>
auto DoubleLinkedList<T>::pushBack(T && value) noexcept -> void {
    auto newNode = new dataTypes::DoubleListNode<T> {
        value, nullptr, this->_pBack
    };

    if ( this->_pBack != nullptr )
        this->_pBack->pNext = newNode;

    this->_pBack = newNode;

    if ( this->_pFront == nullptr )
        this->_pFront = newNode;

    this->_size ++;
}

#include <sstream>
#include <typeinfo>
template <class T>
auto DoubleLinkedList<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return String("[ ]");

    std::stringstream out;
    out << "[ ";

    for ( const auto & e : (*this) )
        out << e << ", ";

    auto s = out.str();
    return String(s.substr(0, s.length() - 2).append(" ]"));
}

template <class T>
auto DoubleLinkedList<T>::remove(const T & what, Size count) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( current->data == what ) {
            auto before = current->pPrevious;
            auto after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto toRemove = current;

            count--;
            nextNode();

            this->_size--;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template <class T>
auto DoubleLinkedList<T>::removeLast(const T & what ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( current->data == what ) {
            auto * before = current->pPrevious;
            auto * after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto * toRemove = current;

            nextNode();

            this->_size--;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template <class T>
auto DoubleLinkedList<T>::removeOf ( const Collection<T> & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( from.contains( current->data ) ) {
            auto before = current->pPrevious;
            auto after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto toRemove = current;

            count--;
            nextNode();

            this->_size--;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template <class T>
auto DoubleLinkedList<T>::removeLastOf ( const Collection<T> & from ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( from.contains( current->data ) ) {
            auto * before = current->pPrevious;
            auto * after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto * toRemove = current;

            nextNode();

            this->_size--;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template<class T>
auto DoubleLinkedList<T>::removeNotOf ( const Collection<T> & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( ! from.contains( current->data ) ) {
            auto before = current->pPrevious;
            auto after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto toRemove = current;

            count--;
            nextNode();

            this->_size--;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template<class T>
auto DoubleLinkedList<T>::removeLastNotOf( const Collection<T> & from ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( ! from.contains( current->data ) ) {
            auto * before = current->pPrevious;
            auto * after = current->pNext;

            if ( before == nullptr )
                this->_pFront = after;
            else
                before->pNext = after;

            if ( after == nullptr )
                this->_pBack = before;
            else
                after->pPrevious = before;

            auto * toRemove = current;

            nextNode();

            this->_size--;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template<class T>
auto DoubleLinkedList<T>::replace ( const T & what, const T & with, Size count ) noexcept -> void {
    for ( int replacedCount = 0; auto & e : (*this) )
        if ( replacedCount < count ) {
            if ( e == what ) {
                e = with;
                replacedCount ++;
            }
        } else
            return;
}

template<class T>
auto DoubleLinkedList<T>::replaceLast ( const T & what, const T & with ) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( it.value() == what ) {
            it.value () = with;
            return;
        }
}

template<class T>
auto DoubleLinkedList<T>::replaceOf ( const Collection<T> & from, const T & with, Size count ) noexcept -> void {
    for ( int replacedCount = 0; auto & e : (*this) )
        if ( replacedCount < count ) {
            if ( from.contains(e) ) {
                e = with;
                replacedCount ++;
            }
        } else
            return;
}

template<class T>
auto DoubleLinkedList<T>::replaceLastOf ( const Collection<T> & from, const T & with ) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( from.contains( it.value() ) ) {
            it.value () = with;
            return;
        }
}

template<class T>
auto DoubleLinkedList<T>::replaceNotOf ( const Collection<T> & from, const T & with, Size count ) noexcept -> void {
    for ( int replacedCount = 0; auto & e : (*this) )
        if ( replacedCount < count ) {
            if ( ! from.contains(e) ) {
                e = with;
                replacedCount ++;
            }
        } else
            return;
}

template<class T>
auto DoubleLinkedList<T>::replaceLastNotOf ( const Collection<T> & from, const T & with ) noexcept -> void {
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( ! from.contains( it.value() ) ) {
            it.value () = with;
            return;
        }
}

template<class T>
auto DoubleLinkedList<T>::remove ( const typename Collection<T>::Iterator & it ) noexcept (false) -> T {
    if ( this->empty() )
        throw typename List<T>::ListOutOfBounds();

    if ( this->begin() == it ) {
        auto node = this->_pFront;
        auto retVal = node->data;
        this->_pFront = node->pNext;
        this->_pFront->pPrevious = nullptr;

        if ( this->size() == 1 )
            this->_pBack = this->_pFront;

        this->_size--;
        delete node;
        return retVal;
    }

    if ( Iterator(this->_pBack) == it ) {
        auto node = this->_pBack;
        auto retVal = node->data;
        this->_pBack = node->pPrevious;
        this->_pBack->pNext = nullptr;

        if ( this->size() == 1 )
            this->_pFront = this->_pBack;

        this->_size--;
        delete node;
        return retVal;
    }

    for ( auto node = this->_pFront->pNext; node != this->_pBack; node = node->pNext ) {
        if ( Iterator ( node ) == it ) {
            auto before = node->pPrevious;
            auto next = node->pNext;

            before->pNext = next;
            next->pPrevious = before;

            auto retVal = node->data;
            this->_size--;
            delete node;

            return retVal;
        }
    }

    throw std::runtime_error("impossible error");
}

template<class T>
auto DoubleLinkedList<T>::replace( const typename Collection<T>::Iterator & where, const T & with ) noexcept -> void {
    where.value() = with;
}

template<class T>
auto DoubleLinkedList<T>::insertBefore( const typename Collection<T>::Iterator & where, const T & what ) noexcept -> void {
    if ( this->empty() || this->begin() == where )
        return this->pushFront( what );

    if ( this->end() == where )
        return this->pushBack( what );

    if ( Iterator(this->_pBack) == where ) {
        auto after = this->_pBack;
        auto before = this->_pBack->pPrevious;

        auto node = new dataTypes::DoubleListNode<T> { what, after, before };

        before->pNext = node;
        after->pPrevious = node;

        this->_size ++;

        return;
    }

    for( auto node = this->_pFront->pNext; node != this->_pBack; node ++ )
        if ( Iterator(node) == where ) {
            auto before = node->pPrevious;
            auto after = node;

            auto newNode = new dataTypes::DoubleListNode<T> { what, after, before };

            before->pNext = newNode;
            after->pPrevious = newNode;

            this->_size ++;

            return;
        }
}

template <class T>
auto DoubleLinkedList<T>::insertAfter( const typename Collection<T>::Iterator & where, const T & what ) noexcept -> void {
    if ( this->empty() )
        return this->pushFront( what );

    if ( this->end() == where )
        return this->pushBack( what );

    if ( Iterator(this->_pBack) == where ) {
        return this->pushBack( what );
    }

    if ( where == this->begin() ) {
        auto after = this->_pFront->pNext;
        auto before = this->_pFront;

        auto node = new dataTypes::DoubleListNode<T> { what, after, before };

        before->pNext = node;
        after->pPrevious = node;

        this->_size ++;

        return;
    }

    for( auto node = this->_pFront->pNext; node != this->_pBack; node ++ )
        if ( Iterator(node) == where ) {
            auto before = node;
            auto after = node->pNext;

            auto newNode = new dataTypes::DoubleListNode<T> {what, after, before};

            before->pNext = newNode;
            after->pPrevious = newNode;

            this->_size ++;

            return;
        }
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & obj) noexcept {
    for ( const auto & e : obj )
        this->pushBack(e);
}

#include <NotImplementedException.h>
template <class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList && l) noexcept {
    while ( ! l.empty() )
        this->pushBack( l.popFront() );
}

template <class T>
auto DoubleLinkedList<T>::clear() noexcept -> void {
    while ( this->_pFront != nullptr ) {
        auto current = this->_pFront;
        this->_pFront = this->_pFront->pNext;
        delete current;
    }
    this->_pBack = nullptr;

    this->_size = 0;
}

template <class T>
auto DoubleLinkedList<T>::makeUnique() noexcept -> void {
    DoubleLinkedList<T> uniqueList;

    for ( const auto & e : (*this) )
        if ( ! uniqueList.contains(e) )
            uniqueList.pushBack (e);

    * this = uniqueList;
}

template <class T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator =(const Collection<T> & c) noexcept {
    if ( this == & c )
        return * this;

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
auto DoubleLinkedList<T>::contains(const T & what) const noexcept -> bool {
    for ( const auto & e : (*this) )
        if ( e == what )
            return true;
    return false;
}

template <class T>
auto DoubleLinkedList<T>::get(Index pos) noexcept (false)  -> T & {
    if ( this->size() == 0 )
        return this->front();

    if ( pos < 0 )
        pos += ( (-pos) / this->size() + 1 ) * this->size();
    if ( pos >= this->size() )
        pos = pos % this->size();

    for ( auto current = 0; auto & e : (*this) ) {
        if ( current == pos )
            return e;
        current ++;
    }

    return this->front();
}

template <class T>
auto DoubleLinkedList<T>::get(Index pos) const noexcept (false)  -> const T & {
    if ( this->size() == 0 )
        return this->front();

    if ( pos < 0 )
        pos += ( this->size() / (-pos) ) * this->size();
    if ( pos >= this->size() )
        pos = pos % this->size();

    for ( auto current = 0; auto & e : (*this) ) {
        if ( current == pos )
            return e;
        current ++;
    }

    return this->front();
}

template <class T>
auto DoubleLinkedList<T>::set(const T & value, Index pos) noexcept (false) -> T & {
    if ( this->size() == 0 )
        return this->front();

    if ( pos < 0 )
        pos += ( this->size() / (-pos) ) * this->size();
    if ( pos >= this->size() )
        pos = pos % this->size();

    for ( auto current = 0; auto & e : (*this) ) {
        if ( current == pos ) {
            e = value;
            return e;
        }
        current ++;
    }
    return this->_pFront->data;
}

template <class T>
auto DoubleLinkedList<T>::sub(List<T> & l, Index from, Index to) const noexcept (false) -> void {
    l.clear();

    if ( to == UINT64_MAX )
        to = this->size ();

    for ( int i = from; i < to; i++ )
        l.pushBack(this->get(i));
}


#define FORCE_COMMA ,

#define _GEN_QUICKSORT_PARTITION_FUNCTION(_paramType, _paramName, _exceptSpec)     \
    template <class T>              \
    auto DoubleLinkedList<T>::quickSortPartition (                             \
    typename DoubleLinkedList<T>::Iterator from,                               \
    typename DoubleLinkedList<T>::Iterator to,                                 \
    typename dataTypes::_paramType <T> _paramName                              \
    ) _exceptSpec -> DoubleLinkedList<T>::Iterator

#define _GEN_QUICKSORT_PARTITION_FUNCTIONS(_paramName, _impl)                           \
    _GEN_QUICKSORT_PARTITION_FUNCTION(ValueCompareFunction, _paramName, noexcept) _impl \
    _GEN_QUICKSORT_PARTITION_FUNCTION(ReferenceCompareFunction, _paramName, noexcept)   _impl\
    _GEN_QUICKSORT_PARTITION_FUNCTION(ConstReferenceCompareFunction, _paramName, noexcept)   _impl\
    _GEN_QUICKSORT_PARTITION_FUNCTION(ThrowValueCompareFunction, _paramName, noexcept (false))   _impl\
    _GEN_QUICKSORT_PARTITION_FUNCTION(ThrowReferenceCompareFunction, _paramName, noexcept (false))   _impl\
    _GEN_QUICKSORT_PARTITION_FUNCTION(ThrowConstReferenceCompareFunction, _paramName, noexcept (false))   _impl

_GEN_QUICKSORT_PARTITION_FUNCTIONS(compareFunction, {
    auto swap = [] ( T & a FORCE_COMMA T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    typename DoubleLinkedList<T>::Iterator partitionIterator(from);

    decltype (partitionIterator) previous;

    for ( auto it = from; it != to; it++ ) {
        if ( compareFunction ( it.value() FORCE_COMMA pivot ) ) {
            swap ( partitionIterator.value() FORCE_COMMA it.value() );
            previous = partitionIterator;
            partitionIterator.next();
        }
    }

    swap ( partitionIterator.value() FORCE_COMMA to.value() );
    if ( previous == Iterator(nullptr) )
        return partitionIterator;
    return previous;
})

#undef _GEN_QUICKSORT_PARTITION_FUNCTIONS
#undef _GEN_QUICKSORT_PARTITION_FUNCTION

#define _GEN_QUICKSORT_FUNCTION(_paramType, _paramName, _exceptSpec)           \
template <class T>                \
auto DoubleLinkedList<T>::quickSort (                                      \
typename DoubleLinkedList<T>::Iterator from,                               \
typename DoubleLinkedList<T>::Iterator to,                                 \
typename dataTypes::_paramType<T> _paramName                              \
) _exceptSpec -> void

#define _GEN_QUICKSORT_FUNCTIONS(_paramName, _impl) \
    _GEN_QUICKSORT_FUNCTION(ValueCompareFunction, _paramName, noexcept) _impl \
    _GEN_QUICKSORT_FUNCTION(ReferenceCompareFunction, _paramName, noexcept) _impl \
    _GEN_QUICKSORT_FUNCTION(ConstReferenceCompareFunction, _paramName, noexcept) _impl \
    _GEN_QUICKSORT_FUNCTION(ThrowValueCompareFunction, _paramName, noexcept (false)) _impl \
    _GEN_QUICKSORT_FUNCTION(ThrowReferenceCompareFunction, _paramName, noexcept (false)) _impl \
    _GEN_QUICKSORT_FUNCTION(ThrowConstReferenceCompareFunction, _paramName, noexcept (false)) _impl

_GEN_QUICKSORT_FUNCTIONS(compareFunction,{
    auto next = to;
    if ( next != Iterator(nullptr) ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && from != Iterator(nullptr) && to != Iterator(nullptr) ) {
        auto partitionIterator = DoubleLinkedList<T>::quickSortPartition(from FORCE_COMMA to FORCE_COMMA compareFunction);

        DoubleLinkedList<T>::quickSort(from FORCE_COMMA partitionIterator FORCE_COMMA compareFunction);

        if ( partitionIterator == Iterator(nullptr) )
            return;

        if (partitionIterator == from) {
            partitionIterator.next();
            if ( partitionIterator != Iterator(nullptr) )
                DoubleLinkedList<T>::quickSort(partitionIterator FORCE_COMMA to FORCE_COMMA compareFunction);
            return;
        }

        partitionIterator.next();
        if ( partitionIterator == Iterator(nullptr) )
            return;
        partitionIterator.next();
        DoubleLinkedList<T>::quickSort ( partitionIterator FORCE_COMMA to FORCE_COMMA compareFunction );
    }
} )

#undef _GEN_QUICKSORT_FUNCTIONS
#undef _GEN_QUICKSORT_FUNCTION

#define _GEN_SORT_FUNCTION(_paramType, _paramName, _impl, _noexceptSpec) \
    template <class T> \
    auto DoubleLinkedList<T>::sort( typename dataTypes::_paramType<T> _paramName ) _noexceptSpec -> void _impl

#define _GEN_SORT_FUNCTIONS(_paramName, _impl) \
    _GEN_SORT_FUNCTION(ValueCompareFunction, _paramName, _impl, noexcept) \
    _GEN_SORT_FUNCTION(ReferenceCompareFunction, _paramName, _impl, noexcept) \
    _GEN_SORT_FUNCTION(ConstReferenceCompareFunction, _paramName, _impl, noexcept) \
    _GEN_SORT_FUNCTION(ThrowValueCompareFunction, _paramName, _impl, noexcept (false)) \
    _GEN_SORT_FUNCTION(ThrowReferenceCompareFunction, _paramName, _impl, noexcept (false)) \
    _GEN_SORT_FUNCTION(ThrowConstReferenceCompareFunction, _paramName, _impl, noexcept (false))

_GEN_SORT_FUNCTIONS(compareFunction,{
    if ( this->size() < 2 )
        return;

    decltype (this->begin()) current;
    decltype (current) previous;
    for ( current = this->begin(); current != this->end(); current ++ )
        previous = current;

    quickSort ( this->begin() FORCE_COMMA previous FORCE_COMMA compareFunction );
})

template <class T>
auto DoubleLinkedList<T>::sort(auto func) noexcept -> void {
    if ( this->size() < 2 )
        return;

    decltype (this->begin()) current;
    decltype (current) previous;
    for ( current = this->begin(); current != this->end(); current ++ )
        previous = current;

    quickSort ( this->begin() , previous , func );
}

template <class T>
auto DoubleLinkedList<T>::quickSort(
        DoubleLinkedList::Iterator from,
        DoubleLinkedList::Iterator to,
        auto func
) noexcept -> void {
    auto next = to;
    if ( next != Iterator(nullptr) ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && from != Iterator(nullptr) && to != Iterator(nullptr) ) {
        auto partitionIterator = DoubleLinkedList<T >::quickSortPartition(from , to , func);

        DoubleLinkedList<T >::quickSort(from , partitionIterator , func);

        if ( partitionIterator == Iterator(nullptr) )
            return;

        if (partitionIterator == from) {
            partitionIterator.next();
            if ( partitionIterator != Iterator(nullptr) )
                DoubleLinkedList<T >::quickSort(partitionIterator , to , func);
            return;
        }

        partitionIterator.next();
        if ( partitionIterator == Iterator(nullptr) )
            return;
        partitionIterator.next();
        DoubleLinkedList<T >::quickSort ( partitionIterator , to , func );
    }
}

template <class T>
auto DoubleLinkedList<T>::quickSortPartition(
        DoubleLinkedList::Iterator from,
        DoubleLinkedList::Iterator to,
        auto func
) noexcept -> Iterator {
    auto swap = [] ( T & a , T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    typename DoubleLinkedList<T >::Iterator partitionIterator(from);

    decltype (partitionIterator) previous;

    for ( auto it = from; it != to; it++ ) {
        if ( func ( it.value() , pivot ) ) {
            swap ( partitionIterator.value() , it.value() );
            previous = partitionIterator;
            partitionIterator.next();
        }
    }

    swap ( partitionIterator.value() , to.value() );
    if ( previous == Iterator(nullptr) )
        return partitionIterator;
    return previous;
}



#undef _GEN_SORT_FUNCTIONS
#undef _GEN_SORT_FUNCTION

#undef FORCE_COMMA

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(
        const typename Collection<T>::Iterator & from,
        const typename Collection<T>::Iterator & to
) noexcept {
    for ( auto it = from; it != to; it ++ )
        this->pushBack(it);
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(
        const typename Collection<T>::ConstIterator & from,
        const typename Collection<T>::ConstIterator & to
) noexcept {
    for ( auto it = from; it != to; it++ )
        this->pushBack(it);
}

template<class T>
auto DoubleLinkedList<T>::index(const T & e) const noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( item == e )
            return current;
        else
            current ++;

    return -1;
}

#endif //CDS_LINKEDLIST_HPP
