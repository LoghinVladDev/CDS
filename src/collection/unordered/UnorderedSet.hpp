//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_UNORDEREDSET_HPP
#define CDS_UNORDEREDSET_HPP

#include <CDS/SetBase>

template <class T>
class UnorderedSet final : public Set<T>  {
public:

    using Reference                             = typename Set<T>::Reference;
    using ConstReference                        = typename Set<T>::ConstReference;
    using Pointer                               = typename Set<T>::Pointer;
    using ConstPointer     __CDS_MaybeUnused    = typename Set<T>::ConstPointer;

    using Node                                  = typename Set<T>::Node;
    using NodePointer      __CDS_MaybeUnused    = typename Set<T>::NodePointer;
    using ConstNodePointer __CDS_MaybeUnused    = typename Set<T>::ConstNodePointer;

    UnorderedSet() noexcept = default;
    UnorderedSet(UnorderedSet const & set) noexcept : Set<T>(set) {
        for ( auto it : set )
            this->insert(it);
    }

    UnorderedSet(UnorderedSet && moveSet) noexcept(false) : Set<T>(std::move(moveSet)) {

    }

    explicit UnorderedSet(
        typename Collection<T>::Iterator const & from,
        typename Collection<T>::Iterator const & to
    ) noexcept : Set<T>() {
        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
            this->insert( it->value() );
    }

    explicit UnorderedSet(
        typename Collection<T>::ConstIterator const & from,
        typename Collection<T>::ConstIterator const & to
    ) noexcept : Set<T>() {
        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
            this->insert( it->value() );
    }

    UnorderedSet ( std::initializer_list < T > const & initializerList ) noexcept : Set<T>() {
        for ( ConstReference e : initializerList ) {
            this->insert(e);
        }
    }

    ~UnorderedSet() noexcept final = default;

public:
    UnorderedSet & operator = ( Collection <T> const & c ) noexcept {
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

    inline UnorderedSet & operator = ( UnorderedSet const & o ) noexcept { return this->operator=( (Collection<T> const &) ( o ) ); } // NOLINT(misc-unconventional-assign-operator)

    auto insert ( ConstReference ) noexcept -> bool final;
    auto insert ( T && ) noexcept -> bool final;

    auto sequence () const noexcept -> Sequence < const UnorderedSet < T > >;
    auto sequence () noexcept -> Sequence < UnorderedSet < T > >;
};

template <class T>
auto UnorderedSet<T>::insert(ConstReference v) noexcept -> bool {
    if ( this->contains(v) )
        return false;

    this->_pFront = new Node { v, this->_pFront };
    this->_size++;

    return true;
}

template <class T>
auto UnorderedSet<T>::insert(T && v) noexcept -> bool {
    if ( this->contains(v) )
        return false;

    this->_pFront = new Node { std::move(v), this->_pFront };
    this->_size++;

    return true;
}

#ifndef _OMIT_SEQUENCE_IMPL
#ifndef _CDS_UNORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#define _CDS_UNORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#include <CDS/Sequence>

template <class T>
auto UnorderedSet<T>::sequence() const noexcept -> Sequence< const UnorderedSet<T>> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template <class T>
auto UnorderedSet<T>::sequence() noexcept -> Sequence<UnorderedSet<T>> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}
#endif

#endif

#if __CDS_cpplang_CTAD_available == true

template < typename T >
UnorderedSet ( std::initializer_list < T > ) -> UnorderedSet < T >;

#endif

#endif //CDS_UNORDEREDSET_HPP
