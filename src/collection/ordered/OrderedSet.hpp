//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_ORDEREDSET_HPP
#define CDS_ORDEREDSET_HPP
#include <CDS/ListSet>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class T> __CDS_Requires( Comparable <T> )
        class __CDS_MaybeUnused DefaultSetComparator : public Comparator<T> {
        public:
            __CDS_OptimalInline auto operator () (T const & a, T const & b) const noexcept -> bool { return a < b; }
        };

    }
}

#if __CDS_cpplang_Concepts_available

namespace cds {

template <class T, class C>
concept ValidSetComparator =
    std::is_base_of<Comparator<T>, C>::value ||
    std::is_invocable< C, T, T > :: type :: value;

}

#endif

namespace cds {

    template <class T, class C = utility :: DefaultSetComparator < T > > __CDS_Requires ( ValidSetComparator < T, C > )
    class OrderedSet : public ListSet<T> {

    public:
        using ElementType                           = typename ListSet<T>::ElementType;

    private:
        using ElementRef        __CDS_MaybeUnused   = typename ListSet<T>::ElementRef;
        using ElementCRef                           = typename ListSet<T>::ElementCRef;
        using ElementMRef       __CDS_MaybeUnused   = typename ListSet<T>::ElementMRef;
        using ElementPtr        __CDS_MaybeUnused   = typename ListSet<T>::ElementPtr;
        using ElementPtrRef                         = typename ListSet<T>::ElementPtrRef;
        using ElementCPtr       __CDS_MaybeUnused   = typename ListSet<T>::ElementCPtr;

        using Node              __CDS_MaybeUnused   = typename ListSet<T>::Node;
        using NodePointer       __CDS_MaybeUnused   = typename ListSet<T>::NodePointer;
        using ConstNodePointer  __CDS_MaybeUnused   = typename ListSet<T>::ConstNodePointer;

        using InitializerList                       = typename ListSet<T>::InitializerList;

    public:
        using Iterator                  = typename Collection < T > :: Iterator;
        using ConstIterator             = typename Collection < T > :: ConstIterator;

        using ReverseIterator           = typename Collection < T > :: ReverseIterator;
        using ConstReverseIterator      = typename Collection < T > :: ConstReverseIterator;

        constexpr OrderedSet() noexcept = default;
        __CDS_OptimalInline OrderedSet(OrderedSet const & set) noexcept :
                ListSet<T>(set) {

            for ( auto const & e : set )
                this->insert( e );
        }

        constexpr OrderedSet(OrderedSet && moveSet) noexcept :
                ListSet<T>(std::forward < ListSet < T > > ( moveSet )) {

        }

        __CDS_OptionalInline explicit OrderedSet (
            Iterator from,
            Iterator to
        ) noexcept :
                ListSet<T>() {

            for ( auto it = from; it != to; ++ it )
                this->insert ( * it );
        }

        __CDS_OptionalInline explicit OrderedSet (
            ConstIterator from,
            ConstIterator to
        ) noexcept :
                ListSet<T>() {

            for ( auto it = from; it != to; ++ it )
                this->insert ( * it );
        }

        __CDS_OptimalInline OrderedSet ( InitializerList initializerList ) noexcept : // NOLINT(google-explicit-constructor)
                ListSet<T>() {

            for ( ElementCRef e : initializerList )
                this->insert(e);
        }

        ~OrderedSet() noexcept override = default;

    private:
        auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef override;

    public:
        auto operator = ( Collection < T > const & c ) noexcept -> OrderedSet & {
            if ( this == & c )
                return * this;

            this->clear();

            for ( auto const & e : c )
                this->insert( e );

            return * this;
        }

        __CDS_OptimalInline auto operator = ( OrderedSet const & o ) noexcept -> OrderedSet & {
            return this->operator =( (Collection<T> const &) ( o ) ); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptimalInline auto operator = ( OrderedSet && set ) noexcept -> OrderedSet & {
            if ( this == & set ) return * this;

            this->clear();

            this->_pFront = exchange ( set._pFront, nullptr );
            this->_size = exchange ( set._size, 0 );

            return * this;
        }

        auto sequence () const && noexcept -> Sequence < OrderedSet < T, C > const >;
        auto sequence () && noexcept -> Sequence < OrderedSet < T, C > >;
        auto sequence () const & noexcept -> Sequence < OrderedSet < T, C > const >;
        auto sequence () & noexcept -> Sequence < OrderedSet < T, C > >;
    };

}

namespace cds {

    template <class T, class C> __CDS_Requires(ValidSetComparator < T, C >)
    auto OrderedSet <T, C> ::allocInsertGetPtr(ElementCRef e) noexcept -> ElementPtrRef {
        C comparator;

        if ( this->empty() ) {
            this->_pFront = Memory :: instance().create < Node > ();
            this->_pFront->data = nullptr;
            this->_size = 1ull;
            return this->_pFront->data;
        }

        if ( Type < T > :: compare( * this->_pFront->data, e ) ) return this->_pFront->data;

        if ( comparator ( e, * this->_pFront->data ) ) {
            auto p = Memory :: instance().create < Node > ();
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
                auto p = Memory :: instance().create < Node > ();
                p->data = nullptr;
                p->pNext = head->pNext;
                head->pNext = p;
                ++ this->_size;
                return head->pNext->data;
            }

            head = head->pNext;
        }

        auto p = Memory :: instance().create < Node > ();
        p->pNext = nullptr;
        p->data = nullptr;
        head->pNext = p;
        ++ this->_size;
        return head->pNext->data;
    }

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<typename T, typename C> __CDS_Requires(ValidSetComparator < T, C >)
        struct TypeParseTraits<OrderedSet<T, C>> {
            constexpr static StringLiteral name = "OrderedSet";
        };

    }
}

#ifndef _OMIT_SEQUENCE_IMPL
#ifndef _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#define _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
#include <CDS/Sequence>

namespace cds {

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() const & noexcept -> Sequence < OrderedSet < T, C > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() & noexcept -> Sequence < OrderedSet < T, C > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() const && noexcept -> Sequence < OrderedSet < T, C > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() && noexcept -> Sequence < OrderedSet < T, C > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

}

#endif
#endif

#endif //CDS_ORDEREDSET_HPP
