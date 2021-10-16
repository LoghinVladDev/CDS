//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_UNORDEREDSET_HPP
#define CDS_UNORDEREDSET_HPP

#include <CDS/SetBase>
#include <CDS/Pointer>

template <class T>
class UnorderedSet final : public Set<T>  {
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
        for ( ElementCRef e : initializerList ) {
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

    inline auto operator = ( UnorderedSet const & o ) noexcept -> UnorderedSet & { return this->operator=( (Collection<T> const &) ( o ) ); } // NOLINT(misc-unconventional-assign-operator)
    inline auto operator = ( UnorderedSet && set ) noexcept -> UnorderedSet & {
        if ( this == & set ) return * this;

        this->_pFront = Utility :: exchange ( set._pFront, nullptr );
        this->_size = Utility :: exchange ( set._size, 0 );

        return * this;
    }

    auto sequence () const noexcept -> Sequence < const UnorderedSet < T > >;
    auto sequence () noexcept -> Sequence < UnorderedSet < T > >;

    auto allocInsertGetPtr ( ElementCRef e __CDS_MaybeUnused ) noexcept -> ElementPtrRef {
        auto head = this->_pFront;
        while ( head != nullptr ) {
            if (Type<ElementType>::compare(* head->data, e))
                return head->data;
            head = head->pNext;
        }

        auto p = new Node;
        p->pNext = this->_pFront;
        p->data = nullptr;
        this->_pFront = p;
        ++ this->_size;
        return this->_pFront->data;
    }
};


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

__CDS_RegisterParseTypeTemplateT(UnorderedSet)

#endif //CDS_UNORDEREDSET_HPP
