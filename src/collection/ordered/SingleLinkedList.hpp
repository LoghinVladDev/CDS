//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_SINGLELINKEDLIST_HPP
#define CDS_SINGLELINKEDLIST_HPP

#include <CDS/List>

template < typename T >
class SingleLinkedList : public List < T > {
public:
    using ElementType                   = typename List < T > :: ElementType;

protected:
    using ElementRef __CDS_MaybeUnused  = typename List < T > :: ElementRef;
    using ElementCRef                   = typename List < T > :: ElementCRef;
    using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
    using ElementPtr                    = typename List < T > :: ElementPtr;
    using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
    using ElementCPtr                   = typename List < T > :: ElementCPtr;

    using CollectionIterator            = typename List < T > :: CollectionIterator;
    using ConstCollectionIterator       = typename List < T > :: ConstCollectionIterator;
    using InitializerList               = typename List < T > :: InitializerList;

private:
    struct Node {
        ElementPtr  _data  {nullptr};
        Node      * _pNext {nullptr};

        constexpr Node () noexcept = default;

        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Node * & { return this->_pNext; }
        constexpr auto next () const noexcept -> Node const * & { return this->_pNext; }

        __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> T * & { return this->_data; }
        constexpr auto data () const noexcept -> T const * & { return this->_data; }
    };

    Node * _pFront {nullptr};
    Node * _pBack {nullptr};

public:

    class IteratorBase;
    class ConstIteratorBase;
    class Iterator;
    class ConstIterator;

    constexpr static const Index INVALID_POS = -1;

    constexpr SingleLinkedList ( ) noexcept = default;
    SingleLinkedList ( SingleLinkedList const & ) noexcept;

    __CDS_cpplang_ConstexprConstructorNonEmptyBody SingleLinkedList ( SingleLinkedList && obj ) noexcept :
            List < T > ( std :: forward ( obj ) ),
            _pFront ( Utility::exchange( obj._pFront, nullptr ) ),
            _pBack ( Utility::exchange( obj._pBack, nullptr ) ) {

        this->_size = Utility::exchange( obj._size, 0 );
    }

    SingleLinkedList (
            CollectionIterator const &,
            CollectionIterator const &
    ) noexcept;

    SingleLinkedList (
            ConstCollectionIterator const &,
            ConstCollectionIterator const &
    ) noexcept;

    SingleLinkedList ( InitializerList ) noexcept; // NOLINT(google-explicit-constructor)

    ~SingleLinkedList() noexcept override;

private:
    auto beginPtr () noexcept -> Iterator * final;
    auto endPtr () noexcept -> Iterator * final;
    auto beginPtr () const noexcept -> ConstIterator * final;
    auto endPtr () const noexcept -> ConstIterator * final;

public:
    auto begin () noexcept -> Iterator;
    auto end () noexcept -> Iterator;

    auto begin () const noexcept -> ConstIterator;
    auto end () const noexcept -> ConstIterator;
    auto cbegin () const noexcept -> ConstIterator;
    auto cend () const noexcept -> ConstIterator;

    virtual auto remove (Index) noexcept -> bool;

    auto remove ( ElementCRef , Size ) noexcept -> bool override;
    auto removeLast ( ElementCRef ) noexcept -> bool override;

    auto removeOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastOf ( Collection<T> const & ) noexcept -> bool override;

    auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool override;

    auto remove ( CollectionIterator const & ) noexcept (false) -> T override;

    __CDS_OptimalInline auto removeOf ( InitializerList list, Size count ) noexcept -> bool override {
        return this->removeOf ( SingleLinkedList <T> (list), count );
    }

    __CDS_OptimalInline auto removeLastOf ( InitializerList list ) noexcept -> bool override {
        return this->removeLastOf ( SingleLinkedList<T> (list) );
    }

    __CDS_OptimalInline auto removeNotOf ( InitializerList list, Size count ) noexcept -> bool override {
        return this->removeNotOf( SingleLinkedList<T> (list), count );
    }

    __CDS_OptimalInline auto removeLastNotOf ( InitializerList list ) noexcept -> bool override {
        return this->removeLastNotOf( SingleLinkedList<T> (list) );
    }

    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        return * this->_pBack->data();
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        return * this->_pBack->data();
    }

    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        return * this->_pFront->data();
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        return * this->_pFront->data();
    }

    __CDS_NoDiscard auto operator == (SingleLinkedList const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( this->size() != o.size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); ++ i1, ++ i2 )
            if ( ! Type < T > :: compare ( i1.value(), i2.value() ) )
                return false;

        return true;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & o ) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > (& o);
        if ( p == nullptr ) return false;

        return this->operator==(* p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void override;
    auto contains ( ElementCRef ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( ElementRef ) noexcept -> Index override;
    auto index ( ElementCRef ) const noexcept -> Index override;

    auto popFront () noexcept (false) -> ElementType override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        -- this->_size;

        auto node = this->_pFront;
        auto value = * node->_data;

        if ( this->size() == 0 )
            this->_pFront = this->_pBack = nullptr;
        else
            this->_pFront = this->_pFront->_pNext;

        Memory::instance().destroy ( node->data() );
        Memory::instance().destroy ( node );
        return value;
    }

    auto popBack () noexcept (false) -> ElementType override {
        if ( this->empty() )
            throw OutOfBoundsException ( "List is Empty" );

        if ( this->size() == 1 ) {
            auto v = * this->_pFront->_data;

            Memory::instance().destroy ( this->_pFront->data() );
            Memory::instance().destroy ( this->_pFront );

            this->_pFront = this->_pBack = nullptr;
            this->_size = 0;

            return v;
        }

        auto p = this->_pFront;

        while ( p->_pNext->_pNext != nullptr )
            p = p->_pNext;

        auto v = * this->_pBack->_data;

        p->_pNext = nullptr;

        Memory :: instance().destroy ( this->_pBack->data() );
        Memory :: instance().destroy ( this->_pBack );
        this->_pBack = p;

        return v;
    }

private:

    auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
    auto allocBackGetPtr () noexcept -> ElementPtrRef override;

    __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
        return this->allocBackGetPtr();
    }

    auto pAt (Index) noexcept (false) -> ElementPtr override;
    auto pAt (Index) const noexcept (false) -> ElementCPtr override;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#endif

    template < typename SortFunction >
    auto static quickSort ( Iterator, Iterator, SortFunction const & ) noexcept -> void;

    template < typename SortFunction >
    auto static quickSortPartition ( Iterator, Iterator, SortFunction const & ) noexcept -> Iterator;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic pop
#endif 

public:
    template < typename SortFunction >
    auto sort ( SortFunction const & f ) noexcept -> void;

    __CDS_MaybeUnused auto sort ( Comparator < T > const & comparator ) noexcept -> void {
        return this->sort([& comparator](T const & a, T const & b) noexcept -> bool { return comparator (a, b); });
    }

    auto operator = ( Collection < T > const & ) noexcept -> SingleLinkedList &;

    __CDS_OptimalInline auto operator = ( SingleLinkedList const & o ) noexcept -> SingleLinkedList & {  // NOLINT(bugprone-unhandled-self-assignment)
        return this->operator= ( (Collection <T> const &)o ); // NOLINT(misc-unconventional-assign-operator)
    }

    __CDS_OptimalInline auto operator = ( SingleLinkedList && o ) noexcept -> SingleLinkedList & {
        if ( this == & o ) return * this;

        this->clear();
        this->_pFront = Utility::exchange( o._pFront, nullptr );
        this->_pBack = Utility::exchange( o._pBack, nullptr );
        this->_size = Utility::exchange( o._size, 0 );

        return * this;
    }

    __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < SingleLinkedList < T > const >;
    __CDS_NoDiscard auto sequence () & noexcept -> Sequence < SingleLinkedList < T > >;
    __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < SingleLinkedList < T > const >;
    __CDS_NoDiscard auto sequence () && noexcept -> Sequence < SingleLinkedList < T > >;

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> SingleLinkedList < T > * override {
        return Memory :: instance().create < SingleLinkedList > (* this);
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index override {
        return this->size();
    }
};

template < typename T >
class SingleLinkedList < T > :: IteratorBase : public Collection < T > :: Iterator {
protected:
    Node mutable * _pNode {nullptr};

    constexpr IteratorBase ( IteratorBase const & ) noexcept = default;
    constexpr IteratorBase ( IteratorBase && ) noexcept = default;

    constexpr explicit IteratorBase ( Node * pNode, SingleLinkedList < T > * pList ) noexcept :
            Collection < T > :: Iterator (pList),
            _pNode (pNode) {

    }

public:
    constexpr IteratorBase () noexcept = delete;
    __CDS_cpplang_ConstexprDestructor ~IteratorBase () noexcept override = default;

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( CollectionIterator const & it ) const noexcept -> bool final {
        if ( this == & it ) return true;
        auto p = dynamic_cast < decltype (this) > ( & it );
        if ( p == nullptr ) return false;

        return this->_pNode == p->_pNode;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef final {
        return * this->_pNode->_data;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto copy () const noexcept -> IteratorBase * override = 0;
};

template < typename T >
class SingleLinkedList < T > :: ConstIteratorBase : public Collection < T > :: ConstIterator {
protected:
    Node const * _pNode {nullptr};

    constexpr ConstIteratorBase( ConstIteratorBase const & ) noexcept = default;
    constexpr ConstIteratorBase( ConstIteratorBase && ) noexcept = default;

    constexpr explicit ConstIteratorBase ( Node const * pNode, SingleLinkedList < T > const * pList ) noexcept :
            Collection<T>::ConstIterator(pList),
            _pNode(pNode) {

    }

public:
    constexpr ConstIteratorBase() noexcept = delete;
    __CDS_cpplang_ConstexprDestructor ~ConstIteratorBase() noexcept override = default;

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( ConstCollectionIterator const & it ) const noexcept -> bool final {
        if ( this == & it ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & it );
        if ( p == nullptr ) return false;

        return this->_pNode == p->_pNode;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef final {
        return * this->_pNode->_data;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto copy () const noexcept -> ConstIteratorBase * override = 0;
};

template < typename T >
class SingleLinkedList < T > :: Iterator : public SingleLinkedList < T > :: IteratorBase {
public:
    constexpr Iterator () noexcept = delete;
    constexpr Iterator ( Iterator const & ) noexcept = default;
    constexpr Iterator ( Iterator && ) noexcept = default;

    constexpr explicit Iterator (Node * pNode, SingleLinkedList < T > * pList) noexcept :
            SingleLinkedList<T>::IteratorBase(pNode, pList) {

    }

    __CDS_cpplang_ConstexprDestructor ~Iterator () noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Iterator const & o ) noexcept -> Iterator & {
        this->_pNode = o._pNode;
        return * this;
    }

    __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> Iterator & final {
        return this->next();
    }

    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Iterator {
        auto copy = * this;
        this->next();
        return copy;
    }

    __CDS_cpplang_ConstexprOverride auto next () noexcept -> Iterator & final {
        this->_pNode = this->_pNode->_pNext;
        return * this;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Iterator * override {
        return Memory :: instance().create < Iterator > ( * this );
    }
};

template < typename T >
class SingleLinkedList < T > :: ConstIterator : public SingleLinkedList < T > :: ConstIteratorBase {
public:
    constexpr ConstIterator () noexcept = default;
    constexpr ConstIterator ( ConstIterator const & ) noexcept = default;
    constexpr ConstIterator ( ConstIterator && ) noexcept = default;

    constexpr explicit ConstIterator ( Node const * pNode, SingleLinkedList < T > const * pList ) noexcept :
            SingleLinkedList<T>::ConstIteratorBase (pNode, pList) {

    }

    __CDS_cpplang_ConstexprDestructor ~ConstIterator() noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstIterator const & o ) noexcept -> ConstIterator & {
        this->_pNode = o._pNode;
        return * this;
    }

    __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> ConstIterator & override {
        return this->next();
    }

    __CDS_OptimalInline auto operator ++ (int) noexcept -> ConstIterator {
        auto copy = * this;
        this->next();
        return * this;
    }

    __CDS_cpplang_ConstexprOverride auto next () noexcept -> ConstIterator & final {
        this->_pNode = this->_pNode->_pNext;
        return * this;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstIterator * override {
        return Memory :: instance().create < ConstIterator > ( * this );
    }
};

template < typename T >
SingleLinkedList < T > :: SingleLinkedList ( InitializerList initializerList ) noexcept {
    for ( auto const & e : initializerList )
        this->pushBack(e);
}

template < typename T >
SingleLinkedList < T > :: ~SingleLinkedList() noexcept {
    this->clear();
}

#include <sstream>
template < typename T >
auto SingleLinkedList < T > :: toString () const noexcept -> String {
    if ( this->empty() ) return {"[ ]"};

    std::stringstream out;
    out << "[ ";

    for ( auto const & e : * this )
        Type < T > ::streamPrint( out, e ) << ", ";

    auto s = out.str();
    return s.substr(0, s.length() - 2).append(" ]");
}

template < typename T >
auto SingleLinkedList < T > :: remove ( Index i ) noexcept -> bool {
    if ( i < 0 || i >= this->size() ) return false;
    if ( i == 0 ) { this->popFront(); return true; }

    auto current = this->_pFront;
    Index currentIndex = 1;

    while ( current->next() != nullptr && currentIndex < i ) {
        current = current->next();
        currentIndex ++;
    }

    auto toRemove = current->next();

    current->next() = current->next()->next();

    Memory :: instance().destroy ( toRemove->data() );
    Memory :: instance().destroy ( toRemove );
    return true;
}

template < typename T >
auto SingleLinkedList < T > :: remove ( ElementCRef what, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    decltype (current) previous = nullptr;

    auto nextNode = [& current] () noexcept { current = current->next(); };

    while ( current != nullptr && count > 0 ) {
        if ( Type < T > :: compare ( * current->data(), what ) ) {
            auto after = current->next();

            if ( previous == nullptr )
                this->_pFront = after;
            else
                previous->next() = after;

            if ( after == nullptr )
                this->_pBack = previous;

            auto toRemove = current;

            count --;
            this->_size --;

            nextNode();

            Memory::instance().destroy ( toRemove->data() );
            Memory::instance().destroy ( toRemove );

            removalDone = true;
            continue;
        }

        previous = current;
        nextNode();
    }

    return removalDone;
}

template < typename T >
auto SingleLinkedList < T > :: removeLast ( ElementCRef what ) noexcept -> bool {
    auto current = this->_pFront;
    decltype (current) previous = Type < T > :: compare ( * current->data(), what ) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( Type < T > :: compare ( * this->_pFront->data(), what ) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();

        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );
        this->_size --;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( Type < T > :: compare ( * current->next()->data(), what ) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );
        this->_size --;

        return true;
    }

    return false;
}

template < typename T >
auto SingleLinkedList < T > :: removeOf ( Collection < T > const & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    decltype (current) previous = nullptr;

    auto nextNode = [& current] () noexcept { current = current->next(); };

    while ( current != nullptr && count > 0 ) {
        if ( from.contains( * current->data() ) ) {
            auto after = current->next();

            if ( previous == nullptr )
                this->_pFront = after;
            else
                previous->next() = after;

            if ( after == nullptr )
                this->_pBack = previous;

            auto toRemove = current;

            count --;
            this->_size --;

            nextNode();

            Memory :: instance().destroy ( toRemove->data() );
            Memory :: instance().destroy ( toRemove );

            removalDone = true;
            continue;
        }

        previous = current;
        nextNode();
    }

    return removalDone;
}

template < typename T >
auto SingleLinkedList < T > :: removeLastOf ( Collection < T > const & from ) noexcept -> bool {
    auto current = this->_pFront;
    decltype (current) previous = from.contains(* current->data()) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( from.contains(* this->_pFront->data()) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();

        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );

        -- this->_size;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( from.contains( * current->next()->data( )) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );
        this->_size --;

        return true;
    }

    return false;
}

template < typename T >
auto SingleLinkedList < T > :: removeNotOf ( Collection < T > const & from, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    decltype (current) previous = nullptr;

    auto nextNode = [& current] () noexcept { current = current->next(); };

    while ( current != nullptr && count > 0 ) {
        if ( ! from.contains( * current->data() ) ) {
            auto after = current->next();

            if ( previous == nullptr )
                this->_pFront = after;
            else
                previous->next() = after;

            if ( after == nullptr )
                this->_pBack = previous;

            auto toRemove = current;

            -- count;
            -- this->_size;

            nextNode();

            Memory :: instance().destroy ( toRemove->data() );
            Memory :: instance().destroy ( toRemove );

            removalDone = true;
            continue;
        }

        previous = current;
        nextNode();
    }

    return removalDone;
}

template < typename T >
auto SingleLinkedList < T > :: removeLastNotOf ( Collection < T > const & from ) noexcept -> bool {
    auto current = this->_pFront;
    decltype (current) previous = ! from.contains(* current->data()) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( ! from.contains(* this->_pFront->data()) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();
        Memory::instance().destroy ( p->data() );
        Memory::instance().destroy ( p );
        --this->_size;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( ! from.contains( * current->next()->data( )) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );
        this->_size --;

        return true;
    }

    return false;
}

template < typename T >
auto SingleLinkedList < T > :: remove ( CollectionIterator const & it ) noexcept (false) -> T {
    if ( this->empty() )
        throw typename List < T > :: ListOutOfBounds ();

    if ( this->begin() == it )
        return this->popFront();


    if ( Iterator ( this->_pBack, this ) == it )
        return this->popBack();

    for ( auto node = this->_pFront; node->next() != this->_pBack; node = node->next() ) {
        if ( Iterator ( node->next(), this ) == it ) {
            auto p = node->next();
            node->next() = node->next()->next();

            auto retVal = * p->data();
            -- this->_size;
            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );

            return retVal;
        }
    }

    throw std::runtime_error("Wrong List Iterator");
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList ( SingleLinkedList const & obj ) noexcept {
    for ( auto & e : obj ) this->pushBack(e);
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList (
        CollectionIterator const & from,
        CollectionIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ) ; ! it->equals(to); it->next() )
        this->pushBack(it->value());
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList (
        ConstCollectionIterator const & from,
        ConstCollectionIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ) ; ! it->equals(to); it->next() )
        this->pushBack(it->value());
}

template < typename T >
auto SingleLinkedList < T > :: beginPtr () noexcept -> Iterator * {
    return Memory :: instance().create < Iterator > ( this->_pFront, this );
}

template < typename T >
auto SingleLinkedList < T > :: endPtr () noexcept -> Iterator * {
    return Memory :: instance().create < Iterator > ( nullptr, this );
}

template < typename T >
auto SingleLinkedList < T > :: beginPtr () const noexcept -> ConstIterator * {
    return Memory :: instance().create < ConstIterator > ( this->_pFront, this );
}

template < typename T >
auto SingleLinkedList < T > :: endPtr () const noexcept -> ConstIterator * {
    return Memory :: instance().create < ConstIterator > ( nullptr, this );
}

template < typename T >
auto SingleLinkedList < T > :: begin () noexcept -> Iterator {
    return Iterator ( this->_pFront, this );
}

template < typename T >
auto SingleLinkedList < T > :: end () noexcept -> Iterator {
    return Iterator ( nullptr, this );
}

template < typename T >
auto SingleLinkedList < T > :: begin () const noexcept -> ConstIterator {
    return ConstIterator ( this->_pFront, this );
}

template < typename T >
auto SingleLinkedList < T > :: end () const noexcept -> ConstIterator {
    return ConstIterator ( nullptr, this );
}

template < typename T >
auto SingleLinkedList < T > :: cbegin () const noexcept -> ConstIterator {
    return ConstIterator ( this->_pFront, this );
}

template < typename T >
auto SingleLinkedList < T > :: cend () const noexcept -> ConstIterator {
    return ConstIterator ( nullptr, this );
}

template < typename T >
auto SingleLinkedList < T > :: clear () noexcept -> void {
    this->_size = 0;
    this->_pBack = nullptr;

    while ( this->_pFront != nullptr ) {
        auto p = this->_pFront;
        this->_pFront = this->_pFront->next();
        Memory :: instance().destroy ( p->data() );
        Memory :: instance().destroy ( p );
    }
}

template < typename T >
auto SingleLinkedList < T > :: makeUnique() noexcept -> void {
    SingleLinkedList newList;

    for ( auto const & e : * this )
        if ( ! newList.contains(e) )
            newList.pushBack (e);

    * this = newList;
}

template < typename T >
auto SingleLinkedList < T > :: contains ( ElementCRef element ) const noexcept -> bool {
    for ( auto const & i : * this )
        if ( Type < T > :: compare ( i, element ) )
            return true;
    return false;
}

template < typename T >
auto SingleLinkedList < T > :: index ( ElementCRef element ) const noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: compare ( item, element ) )
            return current;
        else
            ++ current;

    return INVALID_POS;
}

template < typename T >
auto SingleLinkedList < T > :: index ( ElementRef element ) noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: compare ( item, element ) )
            return current;
        else
            ++ current;

    return INVALID_POS;
}

template < typename T >
template < typename SortFunction >
auto SingleLinkedList < T > :: sort ( SortFunction const & function ) noexcept -> void {
    if ( this->size() < 2 ) return;

    Iterator current(nullptr, nullptr);
    Iterator previous(nullptr, nullptr);

    for ( current = this->begin(); current != this->end (); ++ current )
        previous = current;

    SingleLinkedList < T > :: quickSort ( this->begin(), previous, function );
}

template < typename T >
template < typename SortFunction >
__CDS_MaybeUnused auto SingleLinkedList < T > :: quickSort (
    Iterator from,
    Iterator to,
    SortFunction const & f
) noexcept -> void {auto next = to;
    if ( next != Iterator(nullptr, nullptr) ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && from != Iterator(nullptr, nullptr) && to != Iterator(nullptr, nullptr) ) {
        auto partitionIterator = SingleLinkedList<T >::quickSortPartition(from , to , f);

        SingleLinkedList<T >::quickSort(from , partitionIterator , f);

        if ( partitionIterator == Iterator(nullptr, nullptr) )
            return;

        if (partitionIterator == from) {
            partitionIterator.next();
            if ( partitionIterator != Iterator(nullptr, nullptr) )
                SingleLinkedList<T >::quickSort(partitionIterator , to , f);
            return;
        }

        partitionIterator.next();
        if ( partitionIterator == Iterator(nullptr, nullptr) )
            return;
        partitionIterator.next();
        SingleLinkedList<T >::quickSort ( partitionIterator , to , f );
    }
}

template < typename T >
template < typename SortFunction >
__CDS_MaybeUnused auto SingleLinkedList < T > ::quickSortPartition(
        Iterator from,
        Iterator to,
        SortFunction const & f
) noexcept -> Iterator {
    auto swap = [] ( T & a , T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    typename SingleLinkedList <T >::Iterator partitionIterator(from);

    Iterator previous (nullptr, nullptr);

    for ( auto it = from; it != to; it++ ) {
        if ( f ( it.value() , pivot ) ) {
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

template < typename T >
auto SingleLinkedList < T > :: operator = ( Collection < T > const & collection ) noexcept -> SingleLinkedList & {
    if ( this == & collection )
        return * this;

    this->clear();

    collection.forEach([this](T const & e){this->pushBack(e);});

    return * this;
}

template < typename T >
auto SingleLinkedList < T > ::allocFrontGetPtr() noexcept -> ElementPtrRef {
    auto p = Memory :: instance ().create < Node > ();
    p->data() = nullptr;
    p->next() = this->_pFront;

    this->_pFront = p;

    ++ this->_size;
    if ( this->size() == 1 )
        this->_pBack = this->_pFront;

    return this->_pFront->data();
}

template < typename T >
auto SingleLinkedList < T > ::allocBackGetPtr() noexcept -> ElementPtrRef {
    if ( this->empty() ) return this->allocFrontGetPtr();

    this->_pBack->next() = Memory :: instance().create < Node > ();
    this->_pBack->next()->data() = nullptr;
    this->_pBack->next()->next() = nullptr;

    this->_pBack = this->_pBack->_pNext;
    ++ this->_size;

    return this->_pBack->data();
}

#include <CDS/Sequence>

template < typename T >
auto SingleLinkedList < T > :: sequence () const & noexcept -> Sequence < SingleLinkedList < T > const > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto SingleLinkedList < T > :: sequence () & noexcept -> Sequence < SingleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto SingleLinkedList < T > :: sequence () const && noexcept -> Sequence < SingleLinkedList < T > const > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

template < typename T >
auto SingleLinkedList < T > :: sequence () && noexcept -> Sequence < SingleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

template < typename T >
auto SingleLinkedList < T > :: pAt (Index index) noexcept(false) -> ElementPtr {
    if ( this->size() == 0 )
        throw OutOfBoundsException(index, 0);

    if ( index < 0 )
        index += ( (-index) / this->size() + 1 ) * this->size();
    if ( index >= static_cast<Index>(this->size()) )
        index = index % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == index )
            return & e;
        current ++;
    }

    return nullptr;
}

template < typename T >
auto SingleLinkedList < T > :: pAt (Index index) const noexcept(false) -> ElementCPtr {
    if ( this->size() == 0 )
        throw OutOfBoundsException(index, 0);

    if ( index < 0 )
        index += ( (-index) / this->size() + 1 ) * this->size();
    if ( index >= static_cast<Index>(this->size()) )
        index = index % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == index )
            return & e;
        current ++;
    }

    return nullptr;
}

__CDS_RegisterParseTypeTemplateT(SingleLinkedList)

#endif //CDS_SINGLELINKEDLIST_HPP
