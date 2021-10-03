//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LINKEDLIST_HPP
#define CDS_LINKEDLIST_HPP

#include <CDS/List>
#include <initializer_list>
#include <CDS/Concepts>

#include "./LinkedListPublic.hpp"

#include <CDS/Traits>

template <class T>
class DoubleLinkedList final : public List<T> {
private:
    struct DoubleListNode { // NOLINT(cppcoreguidelines-pro-type-member-init)
        T                  * data        {nullptr};

        DoubleListNode     * pNext       {nullptr};
        DoubleListNode     * pPrevious   {nullptr};

#if __CDS_cpplang_StructBracesInitialization_available == false

        DoubleListNode () noexcept = default;
        __CDS_MaybeUnused DoubleListNode ( T && data, DoubleListNode * pNext, DoubleListNode * pPrev ) noexcept : data(std::move(data)), pNext(pNext), pPrevious(pPrev) { }
        __CDS_MaybeUnused DoubleListNode ( T const & data, DoubleListNode * pNext, DoubleListNode * pPrev ) noexcept : data(data), pNext(pNext), pPrevious(pPrev) { }

#endif

    };

    using Node = DoubleListNode;

    Node * _pFront  { nullptr };
    Node * _pBack   { nullptr };

private:

    class IteratorBase : public Collection<T>::Iterator {
    protected:
        mutable Node * _pNode { nullptr };

        IteratorBase( const IteratorBase & ) noexcept = default;
        IteratorBase(IteratorBase && ) noexcept = default;
        explicit IteratorBase ( Node * pNode, DoubleLinkedList < T > const * pList ) noexcept :
                Collection<T>::Iterator( (Collection < T > *) pList ),
                _pNode(pNode) {

        }

    public:
        ~IteratorBase () noexcept override = default;

        auto operator ++ () noexcept -> IteratorBase & override = 0;

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( const typename Collection<T>::Iterator & o ) const noexcept -> bool final { return dynamic_cast < const IteratorBase & > ( o )._pNode == this->_pNode;}
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> T& final { return * this->_pNode->data; }

        __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;

        auto next () noexcept -> IteratorBase & override = 0;
    };

    class ConstIteratorBase : public Collection<T>::ConstIterator {
    protected:
        const Node * _pNode { nullptr };

        ConstIteratorBase( const ConstIteratorBase & ) noexcept = default;
        ConstIteratorBase(ConstIteratorBase && ) noexcept = default;
        explicit ConstIteratorBase ( const Node * pNode, DoubleLinkedList < T > const * pList ) :
                Collection<T>::ConstIterator( ( Collection < T > const * ) pList),
                _pNode (pNode) {

        }

    public:
        ~ConstIteratorBase () override = default;

        auto operator ++ () noexcept -> ConstIteratorBase & override = 0;

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( const typename Collection<T>::ConstIterator & o ) const noexcept -> bool final { return this->_pNode == dynamic_cast < const ConstIteratorBase & > ( o )._pNode; }
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> const T& final { return * this->_pNode->data; }

        __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;

        auto next () noexcept -> ConstIteratorBase & override = 0;
    };

public:

    using ElementType                   = typename List < T > :: ElementType;
    using ElementRef __CDS_MaybeUnused  = typename List < T > :: ElementRef;
    using ElementCRef                   = typename List < T > :: ElementCRef;
    using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
    using ElementPtr                    = typename List < T > :: ElementPtr;
    using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
    using ElementCPtr                   = typename List < T > :: ElementCPtr;

    class Iterator final : public IteratorBase{
    public:

        Iterator( const Iterator & ) noexcept = default;
        Iterator( Iterator && ) noexcept = default;

        inline Iterator & operator = ( const Iterator & o ) noexcept {
            this->Collection<T>::Iterator::operator=(o);

            this->_pNode = o._pNode;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Iterator & final { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
        explicit Iterator( Node * pNode, DoubleLinkedList < T > const * pList ) : IteratorBase ( pNode, pList ) { }
        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & final { this->_pNode = this->_pNode->pNext; return * this; }
        ~Iterator() noexcept final = default;

        __CDS_NoDiscard inline auto copy () const noexcept -> Iterator * override {
            return new Iterator ( * this );
        }
    };

    class ReverseIterator final : public IteratorBase {
    public:

        ReverseIterator( const ReverseIterator & ) noexcept = default;
        ReverseIterator( ReverseIterator && ) noexcept = default;

        inline ReverseIterator & operator = ( const ReverseIterator & o ) noexcept {
            this->Collection<T>::Iterator::operator=(o);
            this->_pNode = o._pNode;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ReverseIterator & override { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
        explicit ReverseIterator ( Node * pNode, DoubleLinkedList < T > const * pList ) : IteratorBase( pNode, pList ) { }
        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ReverseIterator & final { this->_pNode = this->_pNode->pPrevious; return * this; }
        ~ReverseIterator() noexcept final = default;

        __CDS_NoDiscard inline auto copy () const noexcept -> ReverseIterator * override {
            return new ReverseIterator ( * this );
        }
    };

    class ConstIterator final : public ConstIteratorBase {
    public:

        ConstIterator( const ConstIterator & ) noexcept = default;
        ConstIterator( ConstIterator && ) noexcept = default;

        inline ConstIterator & operator = ( const ConstIterator & o ) noexcept {
            this->Collection<T>::ConstIterator::operator=(o);
            this->_pNode = o._pNode;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstIterator & override { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
        explicit ConstIterator ( Node const * pNode, DoubleLinkedList < T > const * pList ) : ConstIteratorBase( pNode, pList ) { }
        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstIterator & final { this->_pNode = this->_pNode->pNext; return * this; }
        ~ConstIterator() noexcept final = default;

        __CDS_NoDiscard inline auto copy () const noexcept -> ConstIterator * override {
            return new ConstIterator ( * this );
        }
    };

    class ConstReverseIterator final : public ConstIteratorBase {
    public:

        ConstReverseIterator( const ConstReverseIterator & ) noexcept = default;
        ConstReverseIterator( ConstReverseIterator && ) noexcept = default;

        inline ConstReverseIterator & operator = ( const ConstReverseIterator & o ) noexcept {
            this->Collection<T>::ConstIterator::operator=(o);
            this->_pNode = o._pNode;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstReverseIterator & override { this->next(); return * this; }

        inline auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }
        explicit ConstReverseIterator ( Node const * pNode, DoubleLinkedList < T > const * pList ) : ConstIteratorBase( pNode, pList ) { }
        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstReverseIterator & final { this->_pNode = this->_pNode->pPrevious; return * this; }
        ~ConstReverseIterator() noexcept final = default;

        __CDS_NoDiscard inline auto copy () const noexcept -> ConstReverseIterator * override {
            return new ConstReverseIterator ( * this );
        }
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
    __CDS_NoDiscard inline auto beginPtr () noexcept -> Iterator * final { return new Iterator( this->_pFront, this ); }
    __CDS_NoDiscard inline auto endPtr () noexcept -> Iterator * final { return new Iterator(nullptr, this ); }
    __CDS_NoDiscard inline auto beginPtr () const noexcept -> ConstIterator * final  { return new ConstIterator( this->_pFront, this ); }
    __CDS_NoDiscard inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator(nullptr, this ); }

//    auto findPtr ( T & ) noexcept -> Iterator & final {return this->front();}
//    auto findPtr ( const T & ) const noexcept -> ConstIterator & final {return this->front();}

public:
    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator { return Iterator(this->_pFront, this); }
    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator(nullptr, this); }
    __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront, this); }
    __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator { return ConstIterator (nullptr, this); }
    __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront, this); }
    __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator { return ConstIterator (nullptr, this); }

    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator { return ReverseIterator(this->_pBack, this); }
    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rend () noexcept -> ReverseIterator { return ReverseIterator(nullptr, this); }
    __CDS_NoDiscard constexpr auto rbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->_pBack, this); }
    __CDS_NoDiscard constexpr auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (nullptr, this); }
    __CDS_NoDiscard constexpr auto crbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->_pBack, this); }
    __CDS_NoDiscard constexpr auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (nullptr, this); }

    auto remove (Index) noexcept -> bool;

    auto remove ( ElementCRef, Size ) noexcept -> bool final;
    auto removeLast ( ElementCRef ) noexcept -> bool final;

    auto removeOf ( Collection<T> const &, Size ) noexcept -> bool final;
    auto removeLastOf ( Collection<T> const & ) noexcept -> bool final;

    auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool final;
    auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool final;

    auto remove ( typename Collection<T>::Iterator const & ) noexcept (false) -> T final;

    inline auto removeOf ( const std::initializer_list<T> & list, Size count ) noexcept -> bool final { return this->removeOf ( DoubleLinkedList <T> (list), count ); }
    inline auto removeLastOf ( const std::initializer_list<T> & list ) noexcept -> bool final { return this->removeLastOf ( DoubleLinkedList<T> (list) ); }

    inline auto removeNotOf ( const std::initializer_list<T> & list, Size count ) noexcept -> bool final { return this->removeNotOf( DoubleLinkedList<T> (list), count ); }
    inline auto removeLastNotOf ( const std::initializer_list<T> & list ) noexcept -> bool final { return this->removeLastNotOf( DoubleLinkedList<T> (list) ); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return * this->_pBack->data;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return * this->_pFront->data;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> const T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return * this->_pBack->data;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> const T & final {
        if ( this->empty() )
            throw typename List<T>::ListOutOfBounds();

        return * this->_pFront->data;
    }

    auto operator == (DoubleLinkedList const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( o.size () != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
            if ( ! ( Type < T > :: compare ( i1.value(), i2.value() ) ) )
                return false;
        return true;
    }

    inline auto operator != (DoubleLinkedList const & o) const noexcept -> bool {
        return ! ( * this == o );
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype(this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(* p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique ()  noexcept -> void final;
    auto contains ( const T & ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( T & ) noexcept -> Index final;
    auto index ( T const & ) const noexcept -> Index final;

    auto popFront ( ) noexcept (false) -> T final {
        if ( this->empty () )
            throw typename List<T>::ListOutOfBounds();

        this->_size --;

        auto node = this->_pFront;
        T value = * node->data;

        if ( this->size() == 0 ) {
            this->_pFront = this->_pBack = nullptr;

            delete node->data;
            delete node;

            return value;
        }

        this->_pFront = this->_pFront->pNext;
        delete node->data;
        delete node;
        this->_pFront->pPrevious = nullptr;

        return value;
    }

    auto popBack ( ) noexcept (false) -> T final {
        if ( this->empty () )
            throw typename List<T>::ListOutOfBounds();

        this->_size --;

        auto node = this->_pBack;
        T value = * node->data;

        if ( this->size() == 0 ) {
            this->_pBack = this->_pFront = nullptr;
            delete node->data;
            delete node;
            return value;
        }

        this->_pBack = this->_pBack->pPrevious;
        delete node->data;
        delete node;
        this->_pBack->pNext = nullptr;

        return value;
    }

private:

    template < typename K, typename V, typename H > __CDS_Requires(
        UniqueIdentifiable < K > &&
        HashCalculatorHasBoundaryFunction < H >
    ) friend class HashMap;

    auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
    auto allocBackGetPtr () noexcept -> ElementPtrRef override;

    inline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
        return this->allocBackGetPtr();
    }

    auto pAt (Index) noexcept (false) -> ElementPtr override;
    auto pAt (Index) const noexcept (false) -> ElementCPtr override;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#endif

    template < typename SortFunc >
    auto static quickSort ( Iterator, Iterator, SortFunc const & ) noexcept -> void; // NOLINT(misc-no-recursion)

    template < typename SortFunc >
    auto static quickSortPartition ( Iterator, Iterator, SortFunc const & ) noexcept -> Iterator;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic pop
#endif

public:

    inline auto sort ( Comparator < T > const & c) noexcept -> void final {
        auto f = ( [&c] (T const & a, T const & b) noexcept -> bool { return c(a, b); } );
        return this->sort(f);
    }

    template < typename SortFunc >
    auto sort ( SortFunc const & ) noexcept -> void;


    DoubleLinkedList & operator = ( const Collection <T> & ) noexcept;
    inline DoubleLinkedList & operator = ( const DoubleLinkedList <T> & o ) noexcept {  // NOLINT(bugprone-unhandled-self-assignment)
        return this->operator= ( (Collection<T> const & ) ( o )); // NOLINT(misc-unconventional-assign-operator)
    }

    DoubleLinkedList & operator = ( DoubleLinkedList && o ) noexcept {
        if ( this == & o ) return * this;

        this->_pFront = exchange(o._pFront, nullptr);
        this->_pBack = exchange(o._pBack, nullptr);
        this->_size = exchange(o._size, 0);

        return * this;
    }

    __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < const DoubleLinkedList < T > >;
    __CDS_NoDiscard auto sequence () & noexcept -> Sequence < DoubleLinkedList < T > >;
    __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < const DoubleLinkedList < T > >;
    __CDS_NoDiscard auto sequence () && noexcept -> Sequence < DoubleLinkedList < T > >;
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

template < typename T >
auto DoubleLinkedList < T > ::allocBackGetPtr() noexcept -> ElementPtrRef {
    auto newNode = new DoubleListNode;
    newNode->pNext = nullptr;
    newNode->pPrevious = this->_pBack;
    newNode->data = nullptr;

    if ( this->_pBack != nullptr )
        this->_pBack->pNext = newNode;

    this->_pBack = newNode;

    if ( this->_pFront == nullptr )
        this->_pFront = newNode;

    ++ this->_size;

    return newNode->data;
}

template < typename T >
auto DoubleLinkedList < T > ::allocFrontGetPtr() noexcept -> ElementPtrRef {
    auto newNode = new DoubleListNode;
    newNode->pNext = this->_pFront;
    newNode->pPrevious = nullptr;
    newNode->data = nullptr;

    if ( this->_pFront != nullptr )
        this->_pFront->pPrevious = newNode;

    this->_pFront = newNode;

    if ( this->_pBack == nullptr )
        this->_pBack = newNode;

    ++ this->_size;

    return newNode->data;
}

#include <sstream>
#include <typeinfo>
template <class T>
auto DoubleLinkedList<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return {"[ ]"};

    std::stringstream out;
    out << "[ ";

    for ( const auto & e : (*this) )
        Type < T > ::streamPrint( out, e ) << ", ";

    auto s = out.str();
    return {s.substr(0, s.length() - 2).append(" ]")};
}

template < typename T >
auto DoubleLinkedList<T>::remove(Index i) noexcept -> bool {
    if ( i < 0 || i >= this->size() ) return false;
    if ( i == 0 ) { this->popFront(); return true; }

    auto current = this->_pFront;
    Index currentIndex = 1;

    while ( current->pNext != nullptr && currentIndex < i ) {
        current = current->pNext;
        currentIndex ++;
    }

    auto toRemove = current->pNext;

    current->pNext->pNext->pPrevious = current;
    current->pNext = current->pNext->pNext;

    delete toRemove->data;
    delete toRemove;

    return true;
}

#include <CDS/Traits>
template <class T>
auto DoubleLinkedList<T>::remove(ElementCRef what, Size count) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( Type < T > :: compare ( * current->data, what ) ) {
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

            -- count;
            nextNode();

            -- this->_size;

            delete toRemove->data;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template <class T>
auto DoubleLinkedList<T>::removeLast(ElementCRef what ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( Type < T > :: compare ( * current->data, what ) ) {
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

            -- this->_size;

            delete toRemove->data;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template <class T>
auto DoubleLinkedList<T>::removeOf ( Collection<T> const & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( from.contains( * current->data ) ) {
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

            -- count;
            nextNode();

            -- this->_size;

            delete toRemove->data;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template <class T>
auto DoubleLinkedList<T>::removeLastOf ( Collection<T> const & from ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( from.contains( * current->data ) ) {
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

            -- this->_size;

            delete toRemove->data;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template<class T>
auto DoubleLinkedList<T>::removeNotOf ( Collection<T> const & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    auto nextNode = [& current] () noexcept { current = current->pNext; };

    while ( current != nullptr && count > 0 ) {
        if ( ! from.contains( * current->data ) ) {
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

            -- count;
            nextNode();

            -- this->_size;

            delete toRemove->data;
            delete toRemove;

            removalDone = true;
            continue;
        }

        nextNode();
    }

    return removalDone;
}

template<class T>
auto DoubleLinkedList<T>::removeLastNotOf( Collection<T> const & from ) noexcept -> bool {
    auto * current = this->_pBack;
    auto nextNode = [& current] () noexcept { current = current->pPrevious; };

    while ( current != nullptr ) {
        if ( ! from.contains( * current->data ) ) {
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

            -- this->_size;
            delete toRemove->data;
            delete toRemove;
            return true;
        }

        nextNode();
    }

    return false;
}

template<class T>
auto DoubleLinkedList<T>::remove ( const typename Collection<T>::Iterator & it ) noexcept (false) -> T {
    if ( this->empty() )
        throw typename List<T>::ListOutOfBounds();

    if ( this->begin() == it ) {
        auto node = this->_pFront;
        auto retVal = * node->data;
        this->_pFront = node->pNext;
        this->_pFront->pPrevious = nullptr;

        if ( this->size() == 1 )
            this->_pBack = this->_pFront;

        -- this->_size;
        delete node->data;
        delete node;
        return retVal;
    }

    if ( Iterator(this->_pBack, this) == it ) {
        auto node = this->_pBack;
        auto retVal = * node->data;
        this->_pBack = node->pPrevious;
        this->_pBack->pNext = nullptr;

        if ( this->size() == 1 )
            this->_pFront = this->_pBack;

        -- this->_size;
        delete node->data;
        delete node;
        return retVal;
    }

    for ( auto node = this->_pFront->pNext; node != this->_pBack; node = node->pNext ) {
        if ( Iterator ( node, this ) == it ) {
            auto before = node->pPrevious;
            auto next = node->pNext;

            before->pNext = next;
            next->pPrevious = before;

            auto retVal = * node->data;
            -- this->_size;

            delete node->data;
            delete node;

            return retVal;
        }
    }

    throw std::runtime_error("Wrong List Iterator");
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList & obj) noexcept {
    for ( const auto & e : obj )
        this->pushBack(e);
}

#include <CDS/NotImplementedException>
template <class T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList && l) noexcept :
        _pFront(exchange(l._pFront, nullptr)),
        _pBack(exchange(l._pBack, nullptr)){
    this->_size = exchange(l._size, 0);
}

template <class T>
auto DoubleLinkedList<T>::clear() noexcept -> void {
    while ( this->_pFront != nullptr ) {
        auto current = this->_pFront;
        this->_pFront = this->_pFront->pNext;

        delete current->data;
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
    for ( const auto & e : (*this) ) // NOLINT(readability-use-anyofallof)
        if ( Type < T > :: compare ( e, what ) )
            return true;
    return false;
}

#include <CDS/Utility>
template < typename T >
auto DoubleLinkedList < T > :: pAt ( Index pos ) noexcept (false) -> ElementPtr {
    if ( this->empty() )
        throw OutOfBoundsException(pos, 0);

    if ( pos < 0 )
        pos += ( (-pos) / this->size() + 1 ) * this->size();
    if ( pos >= static_cast<Index>(this->size()) )
        pos = pos % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == pos )
            return & e;
        ++ current ;
    }

    return nullptr;
}

#include <CDS/Utility>
template < typename T >
auto DoubleLinkedList < T > :: pAt ( Index pos ) const noexcept (false) -> ElementCPtr {
    if ( this->empty() )
        throw OutOfBoundsException(pos, 0);

    if ( pos < 0 )
        pos += ( (-pos) / this->size() + 1 ) * this->size();
    if ( pos >= static_cast<Index>(this->size()) )
        pos = pos % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == pos )
            return & e;
        ++ current ;
    }

    return nullptr;
}

template <class T>
template < typename SortFunc >
__CDS_MaybeUnused auto DoubleLinkedList < T >::sort ( SortFunc const & func ) noexcept -> void {
    if ( this->size() < 2 )
        return;

    auto previous = this->begin();
    for ( auto current = this->begin(); current != this->end(); ++ current )
        previous = current;

    quickSort ( this->begin() , previous , func );
}

template <class T>
template <typename SortFunc>
auto DoubleLinkedList<T>::quickSort(
        DoubleLinkedList::Iterator from,
        DoubleLinkedList::Iterator to,
        SortFunc const & func
) noexcept -> void {
    auto next = to;
    if ( next != Iterator(nullptr, nullptr) ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && from != Iterator(nullptr, nullptr) && to != Iterator(nullptr, nullptr) ) {
        auto partitionIterator = DoubleLinkedList<T >::quickSortPartition(from , to , func);

        DoubleLinkedList<T >::quickSort(from , partitionIterator , func);

        if ( partitionIterator == Iterator(nullptr, nullptr) )
            return;

        if (partitionIterator == from) {
            partitionIterator.next();
            if ( partitionIterator != Iterator(nullptr, nullptr) )
                DoubleLinkedList<T >::quickSort(partitionIterator , to , func);
            return;
        }

        partitionIterator.next();
        if ( partitionIterator == Iterator(nullptr, nullptr) )
            return;
        partitionIterator.next();
        DoubleLinkedList<T >::quickSort ( partitionIterator , to , func );
    }
}

template <class T>
template < typename SortFunc >
auto DoubleLinkedList<T>::quickSortPartition(
        DoubleLinkedList::Iterator from,
        DoubleLinkedList::Iterator to,
        SortFunc const & func
) noexcept -> Iterator {
    auto swap = [] ( T & a , T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    typename DoubleLinkedList<T >::Iterator partitionIterator(from);

    auto previous = Iterator(nullptr, nullptr);

    for ( auto it = from; it != to; ++ it ) {
        if ( func ( it.value() , pivot ) ) {
            swap ( partitionIterator.value() , it.value() );
            previous = partitionIterator;
            partitionIterator.next();
        }
    }

    swap ( partitionIterator.value() , to.value() );
    if ( previous == Iterator(nullptr, nullptr) )
        return partitionIterator;
    return previous;
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(
        const typename Collection<T>::Iterator & from,
        const typename Collection<T>::Iterator & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(
        const typename Collection<T>::ConstIterator & from,
        const typename Collection<T>::ConstIterator & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template<class T>
auto DoubleLinkedList<T>::index(T const & e) const noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: compare ( item, e ) )
            return current;
        else
            ++ current;

    return -1;
}

template<class T>
auto DoubleLinkedList<T>::index(T & e) noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: compare ( item, e ) )
            return current;
        else
            ++ current;

    return -1;
}

#include <CDS/Sequence>

template < typename T >
auto DoubleLinkedList < T > :: sequence () const & noexcept -> Sequence < const DoubleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto DoubleLinkedList < T > :: sequence () & noexcept -> Sequence < DoubleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto DoubleLinkedList < T > :: sequence () const && noexcept -> Sequence < const DoubleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

template < typename T >
auto DoubleLinkedList < T > :: sequence () && noexcept -> Sequence < DoubleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

inline auto String::split(ElementType token, Size limit) const noexcept -> LinkedList < String > {
    Index splitIndex = 0;
    if (limit < 1 )
        limit = UINT32_MAX;

    LinkedList < String > segments;
    if ( this->empty() )
        return segments;

    String currentSegment;

    for ( auto c : (*this) ) {
        if ( c != token || splitIndex >= static_cast<Index>(limit) - 1 )
            currentSegment += c;
        else {
            if ( currentSegment.empty() )
                continue;

            splitIndex ++;
            segments.pushBack ( currentSegment );
            currentSegment.clear();
        }
    }

    if ( ! currentSegment.empty() )
        segments.pushBack ( currentSegment );
    return segments;
}

__CDS_MaybeUnused inline auto String::lines() const noexcept -> LinkedList < String >{
    return this->split("\n\r");
}

inline auto String::split(const String & delim, Size limit) const noexcept -> LinkedList < String > {
    Index splitIndex = 0;
    if (limit < 1 )
        limit = INT64_MAX;

    LinkedList < String > segments;
    if ( this->empty() )
        return segments;

    String currentSegment;

    for ( auto c : (*this) ) {
        if ( ! delim.contains(c) || splitIndex >= static_cast<Index>(limit) - 1 )
            currentSegment += c;
        else {
            splitIndex ++;
            if ( ! currentSegment.empty() )
                segments.pushBack ( currentSegment );
            currentSegment.clear();
        }
    }

    if ( ! currentSegment.empty() )
        segments.pushBack ( currentSegment );
    return segments;
}

__CDS_MaybeUnused inline auto String::splitByString(String const & token, Size limit) const noexcept -> LinkedList < String > {
    String copy = * this;
    auto locations = this->find(token);

    auto i = static_cast < Index > (locations.size()) - 1;
    for ( auto it = locations.rbegin(); it != locations.rend(); ++it, --i )
        if ( i + 1 < limit )
            copy.replace(it.value(), token.length(), "\001");

    return copy.split('\001');
}

inline auto String::find (ElementType e) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( c == e )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

inline auto String::findOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

inline auto String::findNotOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( ! s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

inline auto String::find (String const & o) const noexcept -> LinkedList < Index > {
#if !defined(_MSC_VER)
    Index lpsArray [o.size()];
#else
    auto lpsArray = new Index[this->size()];
#endif
    std::memset(lpsArray, 0, sizeof(Index) * o.size());

    auto computeLPSArray = [& o, &lpsArray] () {
        Index len = 0;
        lpsArray[0] = 0;

        Index i = 1;
        while ( i < static_cast<Index>(o.size()) ) {
            if ( o._p[i] == o._p[len] ) {
                len ++;
                lpsArray[i] = len;
                i ++;
            } else {
                if ( len != 0 )
                    len = lpsArray[len - 1];
                else {
                    lpsArray[i] = 0;
                    i ++;
                }
            }
        }
    };

    computeLPSArray();

    LinkedList < Index > indices;
    Index i = 0, j = 0;
    while ( i < static_cast<Index>(this->size()) ) {
        if ( o._p[j] == this->_p[i] ) {
            i ++; j ++;
        }

        if ( j == static_cast<Index>(o.size()) ) {
            indices.pushBack(i - j);
            j = lpsArray[j - 1];
        } else if ( i < static_cast<Index>(this->size()) && this->_p[i] != o._p[j] ) {
            if ( j != 0 )
                j = lpsArray[j - 1];
            else
                i ++;
        }
    }

#if !defined(_MSC_VER)
#else
    delete [] lpsArray;
#endif
    return indices;
}

#if __CDS_cpplang_CTAD_available == true

template < typename T >
DoubleLinkedList ( std::initializer_list < T > ) -> DoubleLinkedList < T >;

#endif

#include "SingleLinkedList.hpp"


#endif //CDS_LINKEDLIST_HPP
