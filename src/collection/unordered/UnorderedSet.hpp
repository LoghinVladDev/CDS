//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_UNORDEREDSET_HPP
#define CDS_UNORDEREDSET_HPP

#include <CDS/ListSet>
#include <CDS/Pointer>

namespace cds {

    template < typename T >
    class UnorderedSet : public ListSet<T>  {

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

    public:
        constexpr UnorderedSet() noexcept = default;

        __CDS_OptimalInline UnorderedSet( UnorderedSet const & set ) noexcept :
                ListSet<T>(set) {

            for ( auto const & it : set )
                this->insert(it);
        }

        constexpr UnorderedSet(UnorderedSet && moveSet) noexcept :
                ListSet<T>(std::forward < ListSet < T > > (moveSet)) {

        }

        __CDS_OptionalInline explicit UnorderedSet(
            Iterator const & from,
            Iterator const & to
        ) noexcept :
                ListSet<T>() {

            for ( auto it = from; it != to; ++ it )
                this->insert ( * it );
        }

        __CDS_OptionalInline explicit UnorderedSet(
            ConstIterator const & from,
            ConstIterator const & to
        ) noexcept :
                ListSet<T>() {

            for ( auto it = from; it != to; ++ it )
                this->insert ( * it );
        }

        __CDS_OptimalInline UnorderedSet ( InitializerList initializerList ) noexcept : // NOLINT(google-explicit-constructor)
                ListSet<T>() {

            for ( ElementCRef e : initializerList ) {
                this->insert(e);
            }
        }

        ~UnorderedSet() noexcept override = default;

    public:
        auto operator = ( Collection <T> const & c ) noexcept -> UnorderedSet & {
            if ( this == & c )
                return * this;

            this->clear();

            for ( auto & e : c )
                this->insert ( e );

            return * this;
        }

        __CDS_OptimalInline auto operator = ( UnorderedSet const & o ) noexcept -> UnorderedSet & {
            return this->operator=( (Collection<T> const &) ( o ) ); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptimalInline auto operator = ( UnorderedSet && set ) noexcept -> UnorderedSet & {
            if ( this == & set )
                return * this;

            this->clear();
            this->_pFront = exchange ( set._pFront, nullptr );
            this->_size = exchange ( set._size, 0 );

            return * this;
        }

        auto sequence () const & noexcept -> Sequence < UnorderedSet < T > const >;
        auto sequence () & noexcept -> Sequence < UnorderedSet < T > >;

        auto sequence () const && noexcept -> Sequence < UnorderedSet < T > const >;
        auto sequence () && noexcept -> Sequence < UnorderedSet < T > >;

        auto allocInsertGetPtr ( ElementCRef e __CDS_MaybeUnused ) noexcept -> ElementPtrRef override {
            auto head = this->_pFront;

            while ( head != nullptr ) {
                if (Type<ElementType>::compare(* head->data, e))
                    return head->data;
                head = head->pNext;
            }

            auto p = Memory :: instance().create < Node > ();
            p->pNext = this->_pFront;
            p->data = nullptr;
            this->_pFront = p;
            ++ this->_size;
            return this->_pFront->data;
        }
    };

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template < typename T >
    UnorderedSet ( std::initializer_list < T > ) -> UnorderedSet < T >;

}

#endif

__CDS_RegisterParseTypeTemplateT(UnorderedSet)

#endif //CDS_UNORDEREDSET_HPP
