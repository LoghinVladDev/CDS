//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_SINGLELINKEDLIST_HPP
#define CDS_SINGLELINKEDLIST_HPP

#include <CDS/List>

template < typename T >
class SingleLinkedList : public List < T > {
private:
    struct Node {
        T       _data;
        Node  * _pNext {nullptr};

        Node (T const & data, Node * pNext) noexcept :
                _data(data),
                _pNext(pNext) {

        }

        Node (T && data, Node * pNext) noexcept :
                _data(std::move(data)),
                _pNext(pNext) {

        }

        constexpr auto next () noexcept -> Node * & { return this->_pNext; }
        constexpr auto next () const noexcept -> Node const * & { return this->_pNext; }

        constexpr auto data () noexcept -> T & { return this->_data; }
        constexpr auto data () const noexcept -> T const & { return this->_data; }
    };

    Node * _pFront {nullptr};
    Node * _pBack {nullptr};

public:

    class IteratorBase;
    class ConstIteratorBase;
    class Iterator;
    class ConstIterator;

    constexpr static const Index INVALID_POS = -1;

    SingleLinkedList ( ) noexcept = default;
    SingleLinkedList ( SingleLinkedList const & ) noexcept;
    
    SingleLinkedList ( SingleLinkedList && obj ) noexcept :
            List < T > ( obj ),
            _pFront ( std::exchange( obj._pFront, nullptr ) ),
            _pBack ( std::exchange( obj._pBack, nullptr ) ) {
        this->_size = std::exchange( obj._size, 0 );
    }

    SingleLinkedList (
            typename Collection < T > :: Iterator const &,
            typename Collection < T > :: Iterator const &
    ) noexcept;

    SingleLinkedList (
            typename Collection < T > :: ConstIterator const &,
            typename Collection < T > :: ConstIterator const &
    ) noexcept;

    SingleLinkedList ( std::initializer_list < T > const & ) noexcept;

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

    auto remove ( T const &, Size ) noexcept -> bool override;
    auto removeLast ( T const & ) noexcept -> bool override;

    auto removeOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastOf ( Collection<T> const & ) noexcept -> bool override;

    auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool override;

    auto replace ( T const &, T const &, Size ) noexcept -> void override;
    auto replaceLast ( T const &, T const & ) noexcept -> void override;

    auto replaceOf ( Collection<T> const &, T const &, Size ) noexcept -> void override;
    auto replaceLastOf ( Collection<T> const &, T const & ) noexcept -> void override;

    auto replaceNotOf ( Collection<T> const &, T const &, Size ) noexcept -> void override;
    auto replaceLastNotOf ( Collection<T> const &, T const & ) noexcept -> void override;

    auto remove ( typename Collection<T>::Iterator const & ) noexcept (false) -> T override;
    auto replace( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;
    auto insertBefore( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;
    auto insertAfter( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;

    inline auto removeOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->removeOf ( SingleLinkedList <T> (list), count ); }
    inline auto removeLastOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->removeLastOf ( SingleLinkedList<T> (list) ); }

    inline auto removeNotOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->removeNotOf( SingleLinkedList<T> (list), count ); }
    inline auto removeLastNotOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->removeLastNotOf( SingleLinkedList<T> (list) ); }

    inline auto replaceOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->replaceOf( SingleLinkedList<T> (list), with, count ); }
    inline auto replaceLastOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->replaceLastOf( SingleLinkedList<T> (list), with ); }

    inline auto replaceNotOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->replaceNotOf( SingleLinkedList<T> (list), with, count ); }
    inline auto replaceLastNotOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->replaceLastNotOf( SingleLinkedList<T> (list), with ); }

    __CDS_NoDiscard constexpr auto back () noexcept (false) -> T & override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        return this->_pBack->_data;
    }

    __CDS_NoDiscard constexpr auto back () const noexcept (false) -> T const & override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        return this->_pBack->_data;
    }

    __CDS_NoDiscard constexpr auto front () noexcept (false) -> T & override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        return this->_pFront->data();
    }

    __CDS_NoDiscard constexpr auto front () const noexcept (false) -> T const & override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        return this->_pFront->data();
    }

    __CDS_NoDiscard constexpr auto empty () const noexcept -> bool final {
        return this->_size == 0 && this->_pFront == nullptr;
    }

    __CDS_NoDiscard auto operator == (SingleLinkedList const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( this->size() != o.size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); ++ i1, ++ i2 )
            if __CDS_cpplang_IfConstexpr ( Type < T > :: hasEqualityOperator ) {
                if ( !(i1.value() == i2.value()) )
                    return false;
            } else if __CDS_cpplang_IfConstexpr ( Type < T > :: objectDerived ) {
                if ( ! i1.value().equals (i2.value()) )
                    return false;
            } else
                return i1 == i2;

        return true;
    }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > (& o);
        if ( p == nullptr ) return false;

        return this->operator==(* p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void override;
    auto contains ( T const & ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( T & ) noexcept -> Index override;
    auto index ( T const & ) const noexcept -> Index override;

    auto get ( Index ) noexcept (false) -> T & override;
    auto get ( Index ) const noexcept (false) -> T const & override;

    auto set ( T const &, Index ) noexcept (false) -> T & override;

    auto sub ( List < T > &, Index, Index ) const noexcept(false) -> void override;

    __CDS_MaybeUnused virtual auto sub (Index from, Index to) const noexcept (false) -> SingleLinkedList < T > {
        SingleLinkedList < T > list;
        this->sub( list, from, to );
        return list;
    }

    auto popFront () noexcept (false) -> T override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        this->_size --;

        auto node = this->_pFront;
        auto value = node->_data;

        if ( this->size() == 0 )
            this->_pFront = this->_pBack = nullptr;
        else
            this->_pFront = this->_pFront->_pNext;

        delete node;
        return value;
    }

    auto popBack () noexcept (false) -> T override {
        if ( this->empty() )
            throw typename List < T > :: ListOutOfBounds ();

        if ( this->size() == 1 ) {
            auto v = this->_pFront->_data;

            delete this->_pFront;

            this->_pFront = this->_pBack = nullptr;
            this->_size = 0;

            return v;
        }

        auto p = this->_pFront;

        while ( p->_pNext->_pNext != nullptr )
            p = p->_pNext;

        auto v = this->_pBack->_data;

        p->_pNext = nullptr;

        delete this->_pBack;
        this->_pBack = p;

        return v;
    }

    auto pushBack ( T const & ) noexcept -> void override;
    auto pushBack ( T && ) noexcept -> void override;
    auto pushFront ( T const & ) noexcept -> void override;
    auto pushFront ( T && ) noexcept -> void override;

private:

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

    template < typename SortFunction >
    auto static quickSort ( Iterator, Iterator, SortFunction const & ) noexcept -> void;

    template < typename SortFunction >
    auto static quickSortPartition ( Iterator, Iterator, SortFunction const & ) noexcept -> Iterator;

#pragma clang diagnostic pop

public:
    template < typename SortFunction >
    auto sort ( SortFunction const & f ) noexcept -> void;

    auto sort ( Comparator < T > const & comparator ) noexcept -> void override {
        return this->sort([& comparator](T const & a, T const & b) noexcept -> bool { return comparator (a, b); });
    }

    auto operator = ( Collection < T > const & ) noexcept -> SingleLinkedList &;

    inline auto operator = ( SingleLinkedList const & o ) noexcept -> SingleLinkedList & { return this->operator= ( (Collection <T> const &)o ); }// NOLINT(misc-unconventional-assign-operator,bugprone-unhandled-self-assignment)

    constexpr auto operator = ( SingleLinkedList && o ) noexcept -> SingleLinkedList & {
        if ( this == & o ) return * this;

        this->_pFront = std::exchange( o._pFront, nullptr );
        this->_pBack = std::exchange( o._pBack, nullptr );
        this->_size = std::exchange( o._size, 0 );

        return * this;
    }

    __CDS_NoDiscard auto sequence () const noexcept -> Sequence < SingleLinkedList < T > const >;
    __CDS_NoDiscard auto sequence () noexcept -> Sequence < SingleLinkedList < T > >;

    __CDS_NoDiscard auto copy () const noexcept -> SingleLinkedList < T > * override { return new SingleLinkedList (* this); }
    __CDS_NoDiscard auto hash () const noexcept -> Index override { return this->size(); }
};

template < typename T >
class SingleLinkedList < T > :: IteratorBase : public Collection < T > :: Iterator {
protected:
    mutable Node * _pNode {nullptr};

    IteratorBase () noexcept = default;
    IteratorBase ( IteratorBase const & ) noexcept = default;
    IteratorBase ( IteratorBase && ) noexcept = default;

    explicit IteratorBase ( Node * pNode ) noexcept :
            Collection < T > :: Iterator (),
            _pNode (pNode) {

    }

public:
    ~IteratorBase () noexcept override = default;

    __CDS_NoDiscard constexpr auto equals ( typename Collection < T > :: Iterator const & it ) const noexcept -> bool final {
        if ( this == & it ) return true;
        auto p = dynamic_cast < decltype (this) > ( & it );
        if ( p == nullptr ) return false;

        return this->_pNode == p->_pNode;
    }

    __CDS_NoDiscard constexpr auto value () const noexcept -> T & final { return this->_pNode->_data; }

    __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;
};

template < typename T >
class SingleLinkedList < T > :: ConstIteratorBase : public Collection < T > :: ConstIterator {
protected:
    Node const * _pNode {nullptr};

    ConstIteratorBase() noexcept = default;
    ConstIteratorBase( ConstIteratorBase const & ) noexcept = default;
    ConstIteratorBase( ConstIteratorBase && ) noexcept = default;

    explicit ConstIteratorBase ( Node const * pNode ) noexcept :
            Collection<T>::ConstIterator(),
            _pNode(pNode) {

    }

public:
    ~ConstIteratorBase() noexcept override = default;

    __CDS_NoDiscard constexpr auto equals ( typename Collection < T > :: ConstIterator const & it ) const noexcept -> bool final {
        if ( this == & it ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & it );
        if ( p == nullptr ) return false;

        return this->_pNode == p->_pNode;
    }

    __CDS_NoDiscard constexpr auto value () const noexcept -> T const & final { return this->_pNode->_data; }

    __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;
};

template < typename T >
class SingleLinkedList < T > :: Iterator final : public SingleLinkedList < T > :: IteratorBase {
public:
    Iterator () noexcept = default;
    Iterator ( Iterator const & ) noexcept = default;
    Iterator ( Iterator && ) noexcept = default;

    explicit Iterator (Node * pNode) noexcept :
            SingleLinkedList<T>::IteratorBase(pNode) {

    }

    ~Iterator () noexcept final = default;

    constexpr auto operator = ( Iterator const & o ) noexcept -> Iterator & {
        this->_pNode = o._pNode;
        return * this;
    }

    constexpr auto operator ++ () noexcept -> Iterator & final { this->next(); return * this; }
    inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
    constexpr auto next () noexcept -> Iterator & final { this->_pNode = this->_pNode->_pNext; return * this; }

    __CDS_NoDiscard inline auto copy () const noexcept -> Iterator * override {
        return new Iterator ( * this );
    }
};

template < typename T >
class SingleLinkedList < T > :: ConstIterator final : public SingleLinkedList < T > :: ConstIteratorBase {
public:
    ConstIterator () noexcept = default;
    ConstIterator ( ConstIterator const & ) noexcept = default;
    ConstIterator ( ConstIterator && ) noexcept = default;

    explicit ConstIterator ( Node const * pNode ) noexcept :
            SingleLinkedList<T>::ConstIteratorBase (pNode) {

    }

    ~ConstIterator() noexcept final = default;

    constexpr auto operator = ( ConstIterator const & o ) noexcept -> ConstIterator & {
        this->_pNode = o._pNode;
        return * this;
    }

    constexpr auto operator ++ () noexcept -> ConstIterator & override { return this->next(); }
    inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return * this; }
    constexpr auto next () noexcept -> ConstIterator & final { this->_pNode = this->_pNode->_pNext; return * this; }

    __CDS_NoDiscard inline auto copy () const noexcept -> ConstIterator * override {
        return new ConstIterator ( * this );
    }
};

template < typename T >
SingleLinkedList < T > :: SingleLinkedList ( std::initializer_list < T > const & initializerList ) noexcept {
    for ( auto const & e : initializerList )
        this->pushBack(e);
}

template < typename T >
SingleLinkedList < T > :: ~SingleLinkedList() noexcept {
    this->clear();
}

template < typename T >
auto SingleLinkedList < T > :: pushFront ( T const & value ) noexcept -> void {
    this->_pFront = new Node ( value, this->_pFront );

    this->_size ++;
    if ( this->size() == 1 )
        this->_pBack = this->_pFront;
}

template < typename T >
auto SingleLinkedList < T > :: pushFront ( T && value ) noexcept -> void {
    this->_pFront = new Node ( value, this->_pFront );

    this->_size ++;
    if ( this->size() == 1 )
        this->_pBack = this->_pFront;
}

template < typename T >
auto SingleLinkedList < T > :: pushBack ( T const & value ) noexcept -> void {
    if ( this->empty() ) return this->pushFront( value );

    this->_pBack->_pNext = new Node ( value, nullptr );
    this->_pBack = this->_pBack->_pNext;
    this->_size++;
}

template < typename T >
auto SingleLinkedList < T > :: pushBack ( T && value ) noexcept -> void {
    if ( this->empty() ) return this->pushFront(value);

    this->_pBack->_pNext = new Node ( value, nullptr );
    this->_pBack = this->_pBack->_pNext;
    this->_size++;
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

    delete toRemove;
    return true;
}

template < typename T >
auto SingleLinkedList < T > :: remove ( T const & what, Size count ) noexcept -> bool {
    bool removalDone = false;

    auto current = this->_pFront;
    decltype (current) previous = nullptr;

    auto nextNode = [& current] () noexcept { current = current->next(); };

    while ( current != nullptr && count > 0 ) {
        if ( Type < T > :: deepCompare ( current->data(), what ) ) {
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
            delete toRemove;

            removalDone = true;
            continue;
        }

        previous = current;
        nextNode();
    }

    return removalDone;
}

template < typename T >
auto SingleLinkedList < T > :: removeLast ( T const & what ) noexcept -> bool {
    auto current = this->_pFront;
    decltype (current) previous = Type < T > :: deepCompare ( current->data(), what ) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( Type < T > :: deepCompare ( this->_pFront->_data, what ) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();
        delete p;
        this->_size --;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( Type < T > :: deepCompare ( current->next()->data(), what ) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        delete p;
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
        if ( from.contains( current->data() ) ) {
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
            delete toRemove;

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
    decltype (current) previous = from.contains(current->data()) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( from.contains(this->_pFront->data()) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();
        delete p;
        this->_size --;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( from.contains( current->next()->data( )) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        delete p;
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
        if ( ! from.contains( current->data() ) ) {
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
            delete toRemove;

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
    decltype (current) previous = ! from.contains(current->data()) ? current : nullptr;

    auto nextNode = [& current] () noexcept  { current = current->next(); };

    if ( ! from.contains(this->_pFront->data()) ) {
        auto p = this->_pFront;

        this->_pFront = this->_pFront->next();
        delete p;
        this->_size --;

        if ( this->size() == 0 ) this->_pBack = nullptr;

        return true;
    }

    while ( current->_pNext != nullptr ) {
        if ( ! from.contains( current->next()->data( )) ) previous = current;
        nextNode();
    }

    if ( previous != nullptr ) {
        if ( previous->next() == this->_pBack ) this->_pBack = previous;

        auto p = previous->next();
        previous->next () = previous -> next () -> next ();
        delete p;
        this->_size --;

        return true;
    }

    return false;
}

template < typename T >
auto SingleLinkedList < T > :: replace ( T const & what, T const & with, Size count ) noexcept -> void {
    int replacedCount = 0;

    for ( auto & e : (*this) )
        if ( replacedCount < count ) {
            if ( Type < T > :: deepCompare ( e, what ) ) {
                e = with;
                replacedCount ++;
            }
        } else
            return;
}

template < typename T >
auto SingleLinkedList < T > :: replaceLast ( T const & what, T const & with ) noexcept -> void {
    auto current = this->_pFront;
    decltype ( current ) lastOccurrence = nullptr;

    while ( current != nullptr ) {
        if ( Type < T > :: deepCompare ( current->data(), what ) )
            lastOccurrence = current;
        current = current->next();
    }

    if ( lastOccurrence != nullptr )
        lastOccurrence->data() = with;
}

template < typename T >
auto SingleLinkedList < T > :: replaceOf ( Collection < T > const & from, T const & with, Size count ) noexcept -> void {
    int replaceCount = 0;

    for ( auto & e : * this )
        if ( replaceCount < count ) {
            if (from.contains(e)) {
                e = with;
                replaceCount++;
            }
        } else
            return;
}

template < typename T >
auto SingleLinkedList < T > :: replaceLastOf ( Collection < T > const & from, T const & with ) noexcept -> void {
    auto current = this->_pFront;
    decltype ( current ) lastOccurrence = nullptr;

    while ( current != nullptr ) {
        if ( from.contains ( current->data() ) )
            lastOccurrence = current;
        current = current->next();
    }

    if ( lastOccurrence != nullptr )
        lastOccurrence->data() = with;
}

template < typename T >
auto SingleLinkedList < T > :: replaceNotOf ( Collection < T > const & from, T const & with, Size count ) noexcept -> void {
    int replaceCount = 0;

    for ( auto & e : * this )
        if ( replaceCount < count ) {
            if ( ! from.contains(e)) {
                e = with;
                replaceCount++;
            }
        } else
            return;
}

template < typename T >
auto SingleLinkedList < T > :: replaceLastNotOf ( Collection < T > const & from, T const & with ) noexcept -> void {
    auto current = this->_pFront;
    decltype ( current ) lastOccurrence = nullptr;

    while ( current != nullptr ) {
        if ( ! from.contains ( current->data() ) )
            lastOccurrence = current;
        current = current->next();
    }

    if ( lastOccurrence != nullptr )
        lastOccurrence->data() = with;
}

template < typename T >
auto SingleLinkedList < T > :: remove ( typename Collection < T > :: Iterator const & it ) noexcept (false) -> T {
    if ( this->empty() )
        throw typename List < T > :: ListOutOfBounds ();

    if ( this->begin() == it )
        return this->popFront();


    if ( Iterator ( this->_pBack ) == it )
        return this->popBack();

    for ( auto node = this->_pFront; node->next() != this->_pBack; node = node->next() ) {
        if ( Iterator ( node->next() ) == it ) {
            auto p = node->next();
            node->next() = node->next()->next();

            auto retVal = p->data();
            this->_size--;
            delete p;

            return retVal;
        }
    }

    throw std::runtime_error("Wrong List Iterator");
}

template < typename T >
auto SingleLinkedList < T > :: replace ( typename Collection < T > :: Iterator const & where, T const & with ) noexcept -> void {
    where.value() = with;
}

template < typename T >
auto SingleLinkedList < T > :: insertBefore ( typename Collection < T > :: Iterator const & where, T const & what ) noexcept -> void {
    if ( this->empty() || this->begin() == where )
        return this->pushFront( what );

    if ( this->end() == where )
        return this->pushBack( what );

    for ( auto node = this->_pFront; node != this->_pBack->next(); node = node->next() )
        if ( Iterator ( node->_pNext ) == where ) {
            auto before = node;
            auto after = node->next();

            before->next() = new Node ( what, after );

            this->_size ++;

            return;
        }
}

template < typename T >
auto SingleLinkedList < T > :: insertAfter(typename Collection<T>::Iterator const & where, T const & what) noexcept -> void {
    if ( this->empty() ) return this->pushFront(what);

    if ( this->begin() == where ) {
        this->_pFront->next() = new Node (what, this->_pFront->next()->next());
        this->_size ++;

        return;
    }

    if ( Iterator (this->_pBack) == where )
        return this->pushBack(what);

    for ( auto node = this->_pFront->next(); node->next() != nullptr; node = node->next() ) {
        if ( Iterator ( node ) == where ) {
            auto before = node;
            auto after = node->next();

            before->next() = new Node (what, after);

            this->_size ++;

            return;
        }
    }
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList ( SingleLinkedList const & obj ) noexcept {
    for ( auto & e : obj ) this->pushBack(e);
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList (
        typename Collection < T > :: Iterator const & from,
        typename Collection < T > :: Iterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ) ; ! it->equals(to); it->next() )
        this->pushBack(it->value());
}

template < typename T >
SingleLinkedList < T > :: SingleLinkedList (
        typename Collection < T > :: ConstIterator const & from,
        typename Collection < T > :: ConstIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ) ; ! it->equals(to); it->next() )
        this->pushBack(it->value());
}

template < typename T >
auto SingleLinkedList < T > :: beginPtr () noexcept -> Iterator * {
    return new Iterator ( this->_pFront );
}

template < typename T >
auto SingleLinkedList < T > :: endPtr () noexcept -> Iterator * {
    return new Iterator ( nullptr );
}

template < typename T >
auto SingleLinkedList < T > :: beginPtr () const noexcept -> ConstIterator * {
    return new ConstIterator ( this->_pFront );
}

template < typename T >
auto SingleLinkedList < T > :: endPtr () const noexcept -> ConstIterator * {
    return new ConstIterator ( nullptr );
}

template < typename T >
auto SingleLinkedList < T > :: begin () noexcept -> Iterator {
    return Iterator ( this->_pFront );
}

template < typename T >
auto SingleLinkedList < T > :: end () noexcept -> Iterator {
    return Iterator ( nullptr );
}

template < typename T >
auto SingleLinkedList < T > :: begin () const noexcept -> ConstIterator {
    return ConstIterator ( this->_pFront );
}

template < typename T >
auto SingleLinkedList < T > :: end () const noexcept -> ConstIterator {
    return ConstIterator ( nullptr );
}

template < typename T >
auto SingleLinkedList < T > :: cbegin () const noexcept -> ConstIterator {
    return ConstIterator ( this->_pFront );
}

template < typename T >
auto SingleLinkedList < T > :: cend () const noexcept -> ConstIterator {
    return ConstIterator ( nullptr );
}

template < typename T >
auto SingleLinkedList < T > :: clear () noexcept -> void {
    this->_size = 0;
    this->_pBack = nullptr;

    while ( this->_pFront != nullptr ) {
        auto p = this->_pFront;
        this->_pFront = this->_pFront->next();
        delete p;
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
auto SingleLinkedList < T > :: contains ( T const & element ) const noexcept -> bool {
    for ( auto const & i : * this )
        if ( Type < T > :: compare ( i, element ) )
            return true;
    return false;
}

template < typename T >
auto SingleLinkedList < T > :: index ( T const & element ) const noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: deepCompare ( item, element ) )
            return current;
        else
            current ++;

    return INVALID_POS;
}

template < typename T >
auto SingleLinkedList < T > :: index ( T & element ) noexcept -> Index {
    Index current = 0;

    for ( auto & item : (*this) )
        if ( Type < T > :: deepCompare ( item, element ) )
            return current;
        else
            current ++;

    return INVALID_POS;
}

template < typename T >
auto SingleLinkedList < T > :: get ( Index index ) noexcept (false) -> T & {
    if ( this->size() == 0 )
        return this->front();

    if ( index < 0 )
        index += ( (-index) / this->size() + 1 ) * this->size();
    if ( index >= static_cast<Index>(this->size()) )
        index = index % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == index )
            return e;
        current ++;
    }

    return this->front();
}

template < typename T >
auto SingleLinkedList < T > :: get ( Index index ) const noexcept (false) -> T const & {
    if ( this->size() == 0 )
        return this->front();

    if ( index < 0 )
        index += ( (-index) / this->size() + 1 ) * this->size();
    if ( index >= static_cast<Index>(this->size()) )
        index = index % this->size();

    auto current = 0;
    for ( auto & e : (*this) ) {
        if ( current == index )
            return e;
        current ++;
    }

    return this->front();
}

template < typename T >
auto SingleLinkedList < T > :: set ( T const & element, Index at ) noexcept (false) -> T & {
    if ( this->size() == 0 )
        return this->front();

    if ( at < 0 )
        at += ( this->size() / (-at) ) * this->size();
    if ( at >= static_cast<Index>(this->size()) )
        at = at % this->size();

    Index current = 0;
    for ( auto & e : (*this) ) {
        if ( current == at ) {
            e = element;
            return e;
        }
        current ++;
    }
    return this->_pFront->data();
}

template < typename T >
auto SingleLinkedList < T > :: sub ( List < T > & list, Index from, Index to ) const noexcept (false) -> void {
    list.clear();

    if ( to == UINT64_MAX )
        to = this->size ();

    for ( Index i = from; i < to; i++ )
        list.pushBack(this->get(i));
}

template < typename T >
template < typename SortFunction >
auto SingleLinkedList < T > :: sort ( SortFunction const & function ) noexcept -> void {
    if ( this->size() < 2 ) return;

    decltype (this->begin()) current;
    decltype (current) previous;

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
    if ( next != Iterator(nullptr) ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && from != Iterator(nullptr) && to != Iterator(nullptr) ) {
        auto partitionIterator = SingleLinkedList<T >::quickSortPartition(from , to , f);

        SingleLinkedList<T >::quickSort(from , partitionIterator , f);

        if ( partitionIterator == Iterator(nullptr) )
            return;

        if (partitionIterator == from) {
            partitionIterator.next();
            if ( partitionIterator != Iterator(nullptr) )
                SingleLinkedList<T >::quickSort(partitionIterator , to , f);
            return;
        }

        partitionIterator.next();
        if ( partitionIterator == Iterator(nullptr) )
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

    decltype (partitionIterator) previous;

    for ( auto it = from; it != to; it++ ) {
        if ( f ( it.value() , pivot ) ) {
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

template < typename T >
auto SingleLinkedList < T > :: operator = ( Collection < T > const & collection ) noexcept -> SingleLinkedList & {
    if ( this == & collection )
        return * this;

    this->clear();

    for ( auto it = UniquePointer < decltype ( & Collection < T > :: beginPtr ) > ( Collection < T > :: beginPtr(collection) ), end = UniquePointer < decltype ( & Collection < T > :: endPtr ) > ( Collection < T > :: endPtr(collection) ); ! it->equals ( * end ); it->next() )
        this->pushBack( it->value() );

    return * this;
}

#include <CDS/Sequence>

template < typename T >
auto SingleLinkedList < T > :: sequence () const noexcept -> Sequence < const SingleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto SingleLinkedList < T > :: sequence () noexcept -> Sequence < SingleLinkedList < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

#endif //CDS_SINGLELINKEDLIST_HPP
