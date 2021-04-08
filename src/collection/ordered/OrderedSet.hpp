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
        std::is_base_of < Comparator < T >, C >::value;
#endif

template <class T, class C = dataTypes::DefaultSetComparator<T>>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires ValidSetComparator <T, C>
#endif
class OrderedSet final : public SetBase<T> {
public:
    using Reference         = typename SetBase<T>::Reference;
    using ConstReference    = typename SetBase<T>::ConstReference;
    using Pointer           = typename SetBase<T>::Pointer;
    using ConstPointer      = typename SetBase<T>::ConstPointer;

    using Node              = typename SetBase<T>::Node;
    using NodePointer       = typename SetBase<T>::NodePointer;
    using ConstNodePointer  = typename SetBase<T>::ConstNodePointer;

    OrderedSet() noexcept = default;
    OrderedSet(OrderedSet const & set) noexcept : SetBase<T>(set) {}
    OrderedSet(OrderedSet && moveSet) noexcept(false) : SetBase<T>(moveSet) {}
    explicit OrderedSet (
        typename Collection<T>::Iterator const & from,
        typename Collection<T>::Iterator const & to
    ) noexcept : SetBase<T>() {
        for ( auto it = from; it != to; it ++ )
            this->insert( it.value() );}

    explicit OrderedSet (
        typename Collection<T>::ConstIterator const & from,
        typename Collection<T>::ConstIterator const & to
    ) noexcept : SetBase<T>() {
        for ( auto it = from; it != to; it ++ )
            this->insert( it.value() );
    }

    OrderedSet ( std::initializer_list < T > const & initializerList ) noexcept : SetBase<T>() {
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

    auto view () const noexcept -> View < OrderedSet < T, C > >;
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

    if ( this->_pFront->data == value ) return false;

    if ( comparator ( value, this->_pFront->data ) ) {
        this->_pFront = new Node { value, this->_pFront };
        this->_size ++;
        return true;
    }

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( head->pNext->data == value ) return false;

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

#include <CDS/View>
template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::view() const noexcept -> View < OrderedSet < T, C > > {
    return View(* this);
}

#endif //CDS_ORDEREDSET_HPP
