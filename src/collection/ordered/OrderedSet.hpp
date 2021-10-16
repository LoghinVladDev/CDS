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
    class __CDS_MaybeUnused DefaultSetComparator : public Comparator<T> {
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

    using ElementType                           = typename Set<T>::ElementType;
    using ElementRef        __CDS_MaybeUnused   = typename Set<T>::ElementRef;
    using ElementCRef                           = typename Set<T>::ElementCRef;
    using ElementMRef       __CDS_MaybeUnused   = typename Set<T>::ElementMRef;
    using ElementPtr        __CDS_MaybeUnused   = typename Set<T>::ElementPtr;
    using ElementPtrRef                         = typename Set<T>::ElementPtrRef;
    using ElementCPtr       __CDS_MaybeUnused   = typename Set<T>::ElementCPtr;

    using Node              __CDS_MaybeUnused   = typename Set<T>::Node;
    using NodePointer       __CDS_MaybeUnused   = typename Set<T>::NodePointer;
    using ConstNodePointer  __CDS_MaybeUnused   = typename Set<T>::ConstNodePointer;

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
        for (auto it = UniquePointer<decltype(&from)>(from.copy()); !it->equals(to); it->next())
            this->insert(it->value());
    }

    explicit OrderedSet (
        typename Collection<T>::ConstIterator const & from,
        typename Collection<T>::ConstIterator const & to
    ) noexcept : Set<T>() {
        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
            this->insert( it->value() );
    }

    OrderedSet ( std::initializer_list < T > const & initializerList ) noexcept : Set<T>() {
        for ( ElementCRef e : initializerList )
            this->insert(e);
    }

    ~OrderedSet() noexcept final = default;

private:
    auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef override;

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

    inline auto operator = ( OrderedSet const & o ) noexcept -> OrderedSet & { return this->operator=( (Collection<T> const &) ( o ) ); } // NOLINT(misc-unconventional-assign-operator)
    inline auto operator = ( OrderedSet && set ) noexcept -> OrderedSet & {
        if ( this == & set ) return * this;

        this->clear();

        this->_pFront = Utility :: exchange ( set._pFront, nullptr );
        this->_size = Utility :: exchange ( set._size, 0 );

        return * this;
    }

    auto sequence () const noexcept -> Sequence < const OrderedSet < T, C > >;
    auto sequence () noexcept -> Sequence < OrderedSet < T, C > >;
};


#define COMMA ,
template <class T, class C> __CDS_Requires(ValidSetComparator <T COMMA C>)
auto OrderedSet <T, C> ::allocInsertGetPtr(ElementCRef e) noexcept -> ElementPtrRef {
    C comparator;

    if ( this->empty() ) {
        this->_pFront = new Node;
        this->_pFront->data = nullptr;
        this->_size = 1ull;
        return this->_pFront->data;
    }

    if ( Type < T > :: compare( * this->_pFront->data, e ) ) return this->_pFront->data;

    if ( comparator ( e, * this->_pFront->data ) ) {
        auto p = new Node;
        p->pNext = this->_pFront;
        p->data = nullptr;
        this->_pFront = p;

        ++ this->_size;
        return this->_pFront->data;
    }

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: compare ( * head->pNext->data, e ) ) return head->pNext->data;

        if ( comparator ( e, * head->pNext->data ) ){
            auto p = new Node;
            p->data = nullptr;
            p->pNext = head->pNext;
            head->pNext = p;
            ++ this->_size;
            return head->pNext->data;
        }

        head = head->pNext;
    }

    auto p = new Node;
    p->pNext = nullptr;
    p->data = nullptr;
    head->pNext = p;
    ++ this->_size;
    return head->pNext->data;
}

namespace Utility {
    template<typename T, typename C> __CDS_Requires(ValidSetComparator <T COMMA C>)
    struct TypeParseTraits<OrderedSet<T, C>> {
        constexpr static StringLiteral name = "OrderedSet";
    };
}

#undef COMMA



#ifndef _OMIT_SEQUENCE_IMPL
#ifndef _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#define _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#include <CDS/Sequence>

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() const noexcept -> Sequence < const OrderedSet < T, C > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() noexcept -> Sequence < OrderedSet < T, C > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}
#endif
#endif

#endif //CDS_ORDEREDSET_HPP
