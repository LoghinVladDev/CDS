//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_ORDEREDSET_HPP
#define CDS_ORDEREDSET_HPP

#include <CDS/ListSet>
#include <CDS/Comparator>

namespace cds {

    template <class T, class C = utility :: DefaultSetComparator < T > > __CDS_Requires ( ValidSetComparator < T, C > )
    class OrderedSet : public ListSet<T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)

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
        __CDS_OptimalInline OrderedSet(OrderedSet const & set __CDS_MaybeUnused) noexcept :
                ListSet<T>(set) {

            for ( auto const & element __CDS_MaybeUnused : set ) {
                this->insert(element);
            }
        }

        constexpr OrderedSet(OrderedSet && moveSet) noexcept :
                ListSet<T>(std::forward < ListSet < T > > ( moveSet )) {

        }

        __CDS_OptionalInline explicit OrderedSet (
            Iterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            Iterator const & until
        ) noexcept :
                ListSet<T>() {

            for (auto it = from; it != until; ++ it ) {
                this->insert( * it );
            }
        }

        __CDS_OptionalInline explicit OrderedSet (
            ConstIterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            ConstIterator const & until
        ) noexcept :
                ListSet<T>() {

            for (auto it = from; it != until; ++ it ) {
                this->insert( * it );
            }
        }

        __CDS_OptimalInline OrderedSet ( InitializerList initializerList __CDS_MaybeUnused ) noexcept : // NOLINT(google-explicit-constructor)
                ListSet<T>() {

            for ( ElementCRef element __CDS_MaybeUnused : initializerList ) {
                this->insert(element);
            }
        }

        ~OrderedSet() noexcept override = default;

    private:
        auto allocInsertGetPtr ( ElementCRef ) noexcept -> ElementPtrRef override;

    public:
        auto operator = ( Collection < T > const & collection __CDS_MaybeUnused ) noexcept -> OrderedSet & {
            if ( this == & collection ) {
                return *this;
            }

            this->clear();

            for ( auto const & element __CDS_MaybeUnused : collection ) {
                this->insert(element);
            }

            return * this;
        }

        __CDS_OptimalInline auto operator = ( OrderedSet const & set ) noexcept -> OrderedSet & {
            return this->operator =( reinterpret_cast < Collection < T > const & > ( set ) ); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptimalInline auto operator = ( OrderedSet && set ) noexcept -> OrderedSet & {
            if ( this == & set ) {
                return *this;
            }

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
    auto OrderedSet <T, C> ::allocInsertGetPtr(ElementCRef element) noexcept -> ElementPtrRef {
        C comparator;

        if ( this->empty() ) {
            this->_pFront = Memory :: instance().create < Node > ();
            this->_pFront->data = nullptr;
            this->_size = 1ull;
            return this->_pFront->data;
        }

        if ( Type < T > :: compare(* this->_pFront->data, element ) ) {
            return this->_pFront->data;
        }

        if ( comparator (element, * this->_pFront->data ) ) {
            auto pNode = Memory :: instance().create < Node > ();
            pNode->pNext = this->_pFront;
            pNode->data = nullptr;
            this->_pFront = pNode;

            ++ this->_size;
            return this->_pFront->data;
        }

        auto head = this->_pFront;
        while ( head->pNext != nullptr ) {
            if ( Type < T > :: compare (* head->pNext->data, element ) ) {
                return head->pNext->data;
            }

            if ( comparator (element, * head->pNext->data ) ){
                auto pNode = Memory :: instance().create < Node > ();
                pNode->data = nullptr;
                pNode->pNext = head->pNext;
                head->pNext = pNode;
                ++ this->_size;
                return head->pNext->data;
            }

            head = head->pNext;
        }

        auto pNode = Memory :: instance().create < Node > ();
        pNode->pNext = nullptr;
        pNode->data = nullptr;
        head->pNext = pNode;
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

#endif //CDS_ORDEREDSET_HPP
