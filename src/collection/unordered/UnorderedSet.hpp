//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_UNORDEREDSET_HPP
#define CDS_UNORDEREDSET_HPP

#include <CDS/SetBase>

template <class T>
class UnorderedSet final : public SetBase<T>  {
public:

    using Reference         = typename SetBase<T>::Reference;
    using ConstReference    = typename SetBase<T>::ConstReference;
    using Pointer           = typename SetBase<T>::Pointer;
    using ConstPointer      = typename SetBase<T>::ConstPointer;

    using Node              = typename SetBase<T>::Node;
    using NodePointer       = typename SetBase<T>::NodePointer;
    using ConstNodePointer  = typename SetBase<T>::ConstNodePointer;

    UnorderedSet() noexcept = default;
    UnorderedSet(UnorderedSet const & set) noexcept : SetBase<T>(set) {
        for ( auto it : set )
            this->insert(it);
    }

    UnorderedSet(UnorderedSet && moveSet) noexcept(false) : SetBase<T>(std::move(moveSet)) {

    }

    explicit UnorderedSet(
        typename Collection<T>::Iterator const & from,
        typename Collection<T>::Iterator const & to
    ) noexcept : SetBase<T>() {
        for ( auto it = from; it != to; it++ )
            this->insert(it.value());
    }

    explicit UnorderedSet(
        typename Collection<T>::ConstIterator const & from,
        typename Collection<T>::ConstIterator const & to
    ) noexcept : SetBase<T>() {
        for ( auto it = from; it != to; it++ )
            this->insert(it.value());
    }

    UnorderedSet ( std::initializer_list < T > const & initializerList ) noexcept : SetBase<T>() {
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

    inline UnorderedSet & operator = ( UnorderedSet const & o ) noexcept { return this->operator=( (Collection<T> const &) ( o ) ); }

    auto insert ( ConstReference ) noexcept -> bool final;
    auto insert ( T && ) noexcept -> bool final;

//    auto view () const noexcept -> View < UnorderedSet < T > >;

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

//#include <CDS/View>
//template <class T>
//auto UnorderedSet<T>::view() const noexcept -> View<UnorderedSet<T>> {
//    return View(*this);
//}

#ifndef _OMIT_SEQUENCE_IMPL
#ifndef _CDS_UNORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#define _CDS_UNORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#include <CDS/Sequence>

template <class T>
auto UnorderedSet<T>::sequence() const noexcept -> Sequence< const UnorderedSet<T>> {
    return Sequence(*this);
}

template <class T>
auto UnorderedSet<T>::sequence() noexcept -> Sequence<UnorderedSet<T>> {
    return Sequence(*this);
}
#endif

#endif

template < typename T >
UnorderedSet ( std::initializer_list < T > ) -> UnorderedSet < T >;

#endif //CDS_UNORDEREDSET_HPP
