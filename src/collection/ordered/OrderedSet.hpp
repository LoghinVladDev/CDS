//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_ORDEREDSET_HPP
#define CDS_ORDEREDSET_HPP
#include <CDS/SetBase>

namespace dataTypes {
    template <class T>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        requires Comparable <T>
#endif
    class DefaultSetComparator : public Comparator<T> {
    public:
        auto inline operator () (T const & a, T const & b) const noexcept -> bool { return a < b; }
    };
}

#if defined(__cpp_concepts) && !defined(_MSC_VER)
template <class T, class C>
concept ValidSetComparator =
    std::is_base_of<Comparator<T>, C>::value ||
    std::is_invocable< C, T, T > :: type :: value;

#endif

template <class T, class C = dataTypes::DefaultSetComparator<T>>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires ValidSetComparator <T, C>
#endif
class OrderedSet final : public Set<T> {
public:
    using Reference         = typename Set<T>::Reference;
    using ConstReference    = typename Set<T>::ConstReference;
    using Pointer           = typename Set<T>::Pointer;
    using ConstPointer      = typename Set<T>::ConstPointer;

    using Node              = typename Set<T>::Node;
    using NodePointer       = typename Set<T>::NodePointer;
    using ConstNodePointer  = typename Set<T>::ConstNodePointer;

    OrderedSet() noexcept = default;
    OrderedSet(OrderedSet const & set) noexcept : Set<T>(set) {
        for ( auto it : set )
            this->insert(it);
    }

    OrderedSet(OrderedSet && moveSet) noexcept(false) : Set<T>(std::move(moveSet)) {}

    explicit OrderedSet (
        typename Collection<T>::Iterator const & from,
        typename Collection<T>::Iterator const & to
    ) noexcept : Set<T>() {
        for ( auto it = from; it != to; it ++ )
            this->insert( it.value() );}

    explicit OrderedSet (
        typename Collection<T>::ConstIterator const & from,
        typename Collection<T>::ConstIterator const & to
    ) noexcept : Set<T>() {
        for ( auto it = from; it != to; it ++ )
            this->insert( it.value() );
    }

    OrderedSet ( std::initializer_list < T > const & initializerList ) noexcept : Set<T>() {
        for ( ConstReference e : initializerList )
            this->insert(e);
    }

    ~OrderedSet() noexcept final = default;

public:
    OrderedSet & operator = ( Collection < T > const & c ) noexcept {
        if ( this == & c )
            return * this;

        this->clear();

        auto pBegin = Collection<T>::beginPtr(c);
        auto pEnd = Collection<T>::endPtr(c);
        for ( auto it = pBegin; ! it->equals(*pEnd); it->next() )
            this->insert( it->value() );

        delete pBegin;
        delete pEnd;

        return * this;
    }

    inline OrderedSet & operator = ( OrderedSet const & o ) noexcept { return this->operator=( (Collection<T> const &) ( o ) ); }

    auto insert ( ConstReference ) noexcept -> bool final;
    auto insert ( T && ) noexcept -> bool final;

//    auto view () const noexcept -> View < OrderedSet < T, C > >;

    auto sequence () const noexcept -> Sequence < const OrderedSet < T, C > >;
    auto sequence () noexcept -> Sequence < OrderedSet < T, C > >;
};

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::insert( ConstReference value) noexcept -> bool {
    C comparator;

    if ( this->empty() ) {
        this->_pFront = new Node { value, nullptr };
        this->_size = 1ull;
        return true;
    }

    if ( Type < T > ::deepCompare( this->_pFront->data, value ) ) return false;

    if ( comparator ( value, this->_pFront->data ) ) {
        this->_pFront = new Node { value, this->_pFront };
        this->_size ++;
        return true;
    }

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: deepCompare ( head->pNext->data, value ) ) return false;

        if ( comparator ( value, head->pNext->data ) ){
            head->pNext = new Node { value, head->pNext };
            this->_size ++;
            return true;
        }

        head = head->pNext;
    }

    head->pNext = new Node { value, nullptr };
    this->_size ++;
    return true;
}


template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::insert( T && value) noexcept -> bool {
    C comparator;

    if ( this->empty() ) {
        this->_pFront = new Node { std::move(value), nullptr };
        this->_size = 1ull;
        return true;
    }

    if ( Type < T > :: deepCompare ( this->_pFront->data, value ) ) return false;

    if ( comparator ( value, this->_pFront->data ) ) {
        this->_pFront = new Node { std::move(value), this->_pFront };
        this->_size ++;
        return true;
    }

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: deepCompare ( head->pNext->data, value ) ) return false;

        if ( comparator ( value, head->pNext->data ) ){
            head->pNext = new Node { std::move(value), head->pNext };
            this->_size ++;
            return true;
        }

        head = head->pNext;
    }

    head->pNext = new Node { std::move(value), nullptr };
    this->_size ++;
    return true;
}

//#include <CDS/View>
//template <class T, class C>
//#if defined(__cpp_concepts) && !defined(_MSC_VER)
//requires ValidSetComparator <T, C>
//#endif
//auto OrderedSet<T, C>::view() const noexcept -> View < OrderedSet < T, C > > {
//    return View(* this);
//}
#ifndef _OMIT_SEQUENCE_IMPL
#ifndef _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#define _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#include <CDS/Sequence>

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() const noexcept -> Sequence < const OrderedSet < T, C > > {
    return Sequence(* this);
}

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() noexcept -> Sequence < OrderedSet < T, C > > {
    return Sequence(* this);
}
#endif
#endif

#endif //CDS_ORDEREDSET_HPP
