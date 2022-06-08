//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_DOUBLELINKEDLIST_HPP
#define CDS_DOUBLELINKEDLIST_HPP

#include <CDS/List>
#include <CDS/Concepts>

#include <CDS/Traits>
#include <CDS/Memory>

#include <CDS/Hasher>

namespace cds {

    template < typename T >
    class DoubleLinkedList : public List < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        using ElementType                   = typename List < T > :: ElementType;

    private:
        using ElementRef __CDS_MaybeUnused  = typename List < T > :: ElementRef;
        using ElementCRef                   = typename List < T > :: ElementCRef;
        using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
        using ElementPtr                    = typename List < T > :: ElementPtr;
        using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
        using ElementCPtr                   = typename List < T > :: ElementCPtr;

        using InitializerList               = typename List < T > :: InitializerList;

    public:
        using Iterator                      = typename List < T > :: Iterator;
        using ConstIterator                 = typename List < T > :: ConstIterator;

        using ReverseIterator               = typename List < T > :: ReverseIterator;
        using ConstReverseIterator          = typename List < T > :: ConstReverseIterator;

    private:
        using DelegateIterator              = typename List < T > :: DelegateIterator;
        using DelegateConstIterator         = typename List < T > :: DelegateConstIterator;


        struct Node {
            ElementType * data;

            Node        * pNext;
            Node        * pPrevious;
        };

        Node * _pFront  { nullptr };
        Node * _pBack   { nullptr };

        class DoubleLinkedListDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < DoubleLinkedList::Node >   _pNode;
            bool                                        _forward;

        public:
            constexpr DoubleLinkedListDelegateIterator ( DoubleLinkedList::Node * pNode, bool forward ) noexcept :
                    DelegateIterator (),
                    _pNode ( pNode ),
                    _forward ( forward ) {

            }

            constexpr DoubleLinkedListDelegateIterator ( DoubleLinkedListDelegateIterator const & ) noexcept = default;
            constexpr DoubleLinkedListDelegateIterator ( DoubleLinkedListDelegateIterator && ) noexcept = default;

            __CDS_cpplang_VirtualConstexpr ~DoubleLinkedListDelegateIterator () noexcept override = default;

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return this->_pNode != nullptr;
            }

            __CDS_cpplang_VirtualConstexpr auto next () noexcept -> DoubleLinkedListDelegateIterator & override {
                (void) ( this->_forward ? ( this->_pNode = this->_pNode->pNext ) : ( this->_pNode = this->_pNode->pPrevious ) );
                return * this;
            }

            __CDS_cpplang_VirtualConstexpr auto previous () noexcept -> DoubleLinkedListDelegateIterator & override {
                (void) ( this->_forward ? ( this->_pNode = this->_pNode->pPrevious ) : ( this->_pNode = this->_pNode->pNext ) );
                return * this;
            }

            __CDS_cpplang_VirtualConstexpr auto value () const noexcept -> ElementRef override {
                return * this->_pNode->data;
            }

            __CDS_NoDiscard constexpr auto node () const noexcept -> DoubleLinkedList :: Node * {
                return this->_pNode.get();
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pObject->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> DoubleLinkedListDelegateIterator * override {
                return Memory :: instance() . create < DoubleLinkedListDelegateIterator > ( * this );
            }
        };

        class DoubleLinkedListConstDelegateIterator : public DelegateConstIterator {
        private:
            ForeignPointer < DoubleLinkedList::Node const > _pNode;
            bool                                            _forward;

        public:
            constexpr DoubleLinkedListConstDelegateIterator ( DoubleLinkedList::Node const * pNode, bool forward ) noexcept :
                    DelegateConstIterator (),
                    _pNode ( pNode ),
                    _forward ( forward ) {

            }

            constexpr DoubleLinkedListConstDelegateIterator ( DoubleLinkedListConstDelegateIterator const & ) noexcept = default;
            constexpr DoubleLinkedListConstDelegateIterator ( DoubleLinkedListConstDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~DoubleLinkedListConstDelegateIterator () noexcept override = default;

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> DoubleLinkedListConstDelegateIterator & override {
                (void) ( this->_forward ? ( this->_pNode = this->_pNode->pNext ) : ( this->_pNode = this->_pNode->pPrevious ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> DoubleLinkedListConstDelegateIterator & override {
                (void) ( this->_forward ? ( this->_pNode = this->_pNode->pPrevious ) : ( this->_pNode = this->_pNode->pNext ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pNode->data;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pObject->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> DoubleLinkedListConstDelegateIterator * override {
                return Memory :: instance() . create < DoubleLinkedListConstDelegateIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListDelegateIterator > ( this->_pFront, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListDelegateIterator > ( nullptr, true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListDelegateIterator > ( this->_pBack, false );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListDelegateIterator > ( nullptr, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListConstDelegateIterator > ( this->_pFront, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListConstDelegateIterator > ( nullptr, true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListConstDelegateIterator > ( this->_pBack, false );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < DoubleLinkedListConstDelegateIterator > ( nullptr, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

    public:
        constexpr DoubleLinkedList( ) noexcept = default;
        DoubleLinkedList( const DoubleLinkedList & ) noexcept;

        __CDS_cpplang_ConstexprConstructorNonEmptyBody DoubleLinkedList( DoubleLinkedList && list ) noexcept:
                _pFront(exchange(list._pFront, nullptr)),
                _pBack(exchange(list._pBack, nullptr)){

            this->_size = exchange(list._size, 0);
        }

        DoubleLinkedList(
                Iterator const &,
                Iterator const &
        ) noexcept;

        DoubleLinkedList(
                ConstIterator const &,
                ConstIterator const &
        ) noexcept;

        DoubleLinkedList( InitializerList ) noexcept; // NOLINT(google-explicit-constructor)

        ~DoubleLinkedList() noexcept override;

    public:
        auto remove (Index) noexcept -> bool;

        auto remove ( ElementCRef, Size ) noexcept -> bool final;
        auto removeLast ( ElementCRef ) noexcept -> bool final;

        auto removeOf ( Collection<T> const &, Size ) noexcept -> bool final;
        auto removeLastOf ( Collection<T> const & ) noexcept -> bool final;

        auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool final;
        auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool final;

        auto remove ( Iterator const & ) noexcept (false) -> T final;

        __CDS_OptimalInline auto removeOf ( InitializerList list, Size count ) noexcept -> bool final {
            return this->removeOf ( DoubleLinkedList <T> (list), count );
        }

        __CDS_OptimalInline auto removeLastOf ( InitializerList list ) noexcept -> bool final {
            return this->removeLastOf ( DoubleLinkedList<T> (list) );
        }

        __CDS_OptimalInline auto removeNotOf ( InitializerList list, Size count ) noexcept -> bool final {
            return this->removeNotOf( DoubleLinkedList<T> (list), count );
        }

        __CDS_OptimalInline auto removeLastNotOf ( InitializerList list ) noexcept -> bool final {
            return this->removeLastNotOf( DoubleLinkedList<T> (list) );
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->data;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->data;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->data;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->data;
        }

        auto operator == (DoubleLinkedList const & list) const noexcept -> bool {
            if ( this == & list ) {
                return true;
            }

            if (list.size () != this->size() ) {
                return false;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                        aIt = this->begin(), aEnd = this->end(),
                        bIt = list.begin(), bEnd = list.end();
                    aIt != aEnd && bIt != bEnd;
                    ++ aIt, ++ bIt // NOLINT(clion-misra-cpp2008-5-18-1)
            ) {
                if ( ! ( Type < T > :: compare (* aIt, * bIt ) ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_OptimalInline auto operator != (DoubleLinkedList const & list) const noexcept -> bool {
            return ! this->operator==(list) ; // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals (Object const & object) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < DoubleLinkedList < T > const * > ( & object );
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator==(* pObject);
        }

        auto clear () noexcept -> void final;
        auto makeUnique ()  noexcept -> void final;

        auto popFront ( ) noexcept (false) -> ElementType final {
            if ( this->empty () ) {
                throw OutOfBoundsException("List is Empty");
            }

            this->_size --;

            auto node = this->_pFront;
            T value = * node->data;

            if ( this->size() == 0 ) {
                this->_pFront   = nullptr;
                this->_pBack    = nullptr;

                Memory :: instance().destroy ( node->data );
                Memory :: instance().destroy ( node );

                return value;
            }

            this->_pFront = this->_pFront->pNext;
            Memory :: instance().destroy ( node->data );
            Memory :: instance().destroy ( node );
            this->_pFront->pPrevious = nullptr;

            return value;
        }

        auto popBack ( ) noexcept (false) -> ElementType final {
            if ( this->empty () ) {
                throw OutOfBoundsException("List is Empty");
            }

            this->_size --;

            auto node = this->_pBack;
            T value = * node->data;

            if ( this->size() == 0 ) {
                this->_pBack = nullptr;
                this->_pFront = nullptr;

                Memory :: instance().destroy ( node->data );
                Memory :: instance().destroy ( node );
                return value;
            }

            this->_pBack = this->_pBack->pPrevious;
            Memory :: instance().destroy ( node->data );
            Memory :: instance().destroy ( node );
            this->_pBack->pNext = nullptr;

            return value;
        }

    private:

        template < typename K, typename V, typename H > __CDS_Requires (
            UniqueIdentifiable < K > &&
            HashCalculatorHasBoundaryFunction < H >
        ) friend class HashMap;

        auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
        auto allocBackGetPtr () noexcept -> ElementPtrRef override;

        __CDS_OptimalInline auto allocInsertGetPtr ( ElementCRef element __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
            return this->allocBackGetPtr();
        }

        auto pAt (Index) noexcept (false) -> ElementPtr override;
        auto pAt (Index) const noexcept (false) -> ElementCPtr override;

    public:
        auto operator = ( Collection <T> const & ) noexcept -> DoubleLinkedList &;

        __CDS_OptimalInline auto operator = ( DoubleLinkedList <T> const & list ) noexcept -> DoubleLinkedList & {  // NOLINT(bugprone-unhandled-self-assignment)
            return this->operator= ( reinterpret_cast < Collection<T> const & > ( list )); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( DoubleLinkedList && list ) noexcept -> DoubleLinkedList & {
            if ( this == & list ) {
                return * this;
            }

            this->clear();
            this->_pFront = exchange(list._pFront, nullptr);
            this->_pBack = exchange(list._pBack, nullptr);
            this->_size = exchange(list._size, 0);

            return * this;
        }

        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < DoubleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < DoubleLinkedList < T > >;
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < DoubleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < DoubleLinkedList < T > >;
    };

}

namespace cds {

    template < typename T >
    DoubleLinkedList<T>::DoubleLinkedList( InitializerList initializerList __CDS_MaybeUnused ) noexcept {
        for ( const auto & element __CDS_MaybeUnused : initializerList ) {
            this->add (element );
        }
    }

    template < typename T >
    DoubleLinkedList<T>::~DoubleLinkedList() noexcept {
        this->clear();
    }

    template < typename T >
    auto DoubleLinkedList < T > ::allocBackGetPtr() noexcept -> ElementPtrRef {
        auto newNode = Memory::instance().create < Node > ();
        newNode->pNext = nullptr;
        newNode->pPrevious = this->_pBack;
        newNode->data = nullptr;

        if ( this->_pBack != nullptr ) {
            this->_pBack->pNext = newNode;
        }

        this->_pBack = newNode;

        if ( this->_pFront == nullptr ) {
            this->_pFront = newNode;
        }

        ++ this->_size;

        return newNode->data;
    }

    template < typename T >
    auto DoubleLinkedList < T > ::allocFrontGetPtr() noexcept -> ElementPtrRef {
        auto newNode = Memory :: instance().create < Node > ();
        newNode->pNext = this->_pFront;
        newNode->pPrevious = nullptr;
        newNode->data = nullptr;

        if ( this->_pFront != nullptr ) {
            this->_pFront->pPrevious = newNode;
        }

        this->_pFront = newNode;

        if ( this->_pBack == nullptr ) {
            this->_pBack = newNode;
        }

        ++ this->_size;

        return newNode->data;
    }

}

#include <sstream>

namespace cds {

    template < typename T >
    auto DoubleLinkedList<T>::remove(Index index) noexcept -> bool {
        if (index < 0 || index >= this->size() ) {
            return false;
        }

        if (index == 0 ) {
            this->popFront();
            return true;
        }

        auto current = this->_pFront;
        Index currentIndex = 1;

        while ( current->pNext != nullptr && currentIndex < index ) {
            current = current->pNext;
            currentIndex ++;
        }

        auto toRemove = current->pNext;

        current->pNext->pNext->pPrevious = current;
        current->pNext = current->pNext->pNext;

        Memory :: instance().destroy ( toRemove->data );
        Memory :: instance().destroy ( toRemove );

        return true;
    }

}

#include <CDS/Traits>

namespace cds {

    template < typename T >
    auto DoubleLinkedList<T>::remove(ElementCRef what, Size count) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        auto nextNode = [& current] () noexcept {
            current = current->pNext;
        };

        while ( current != nullptr && count > 0u ) {
            if ( Type < T > :: compare ( * current->data, what ) ) {
                auto before = current->pPrevious;
                auto after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto toRemove = current;

                -- count;
                nextNode();

                -- this->_size;

                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto DoubleLinkedList<T>::removeLast(ElementCRef what ) noexcept -> bool {
        auto * current = this->_pBack;
        auto nextNode = [& current] () noexcept {
            current = current->pPrevious;
        };

        while ( current != nullptr ) {
            if ( Type < T > :: compare ( * current->data, what ) ) {
                auto * before = current->pPrevious;
                auto * after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto * toRemove = current;

                nextNode();

                -- this->_size;

                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );
                return true;
            }

            nextNode();
        }

        return false;
    }

    template < typename T >
    auto DoubleLinkedList<T>::removeOf ( Collection<T> const & from, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        auto nextNode = [& current] () noexcept {
            current = current->pNext;
        };

        while ( current != nullptr && count > 0u ) {
            if ( from.contains( * current->data ) ) {
                auto before = current->pPrevious;
                auto after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto toRemove = current;

                -- count;
                nextNode();

                -- this->_size;

                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto DoubleLinkedList<T>::removeLastOf ( Collection<T> const & from ) noexcept -> bool {
        auto * current = this->_pBack;
        auto nextNode = [& current] () noexcept {
            current = current->pPrevious;
        };

        while ( current != nullptr ) {
            if ( from.contains( * current->data ) ) {
                auto * before = current->pPrevious;
                auto * after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto * toRemove = current;

                nextNode();

                -- this->_size;

                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );
                return true;
            }

            nextNode();
        }

        return false;
    }

    template < typename T >
    auto DoubleLinkedList<T>::removeNotOf ( Collection<T> const & from, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        auto nextNode = [& current] () noexcept {
            current = current->pNext;
        };

        while ( current != nullptr && count > 0u ) {
            if ( ! from.contains( * current->data ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                auto before = current->pPrevious;
                auto after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto toRemove = current;

                -- count;
                nextNode();

                -- this->_size;

                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto DoubleLinkedList<T>::removeLastNotOf( Collection<T> const & from ) noexcept -> bool {
        auto * current = this->_pBack;
        auto nextNode = [& current] () noexcept {
            current = current->pPrevious;
        };

        while ( current != nullptr ) {
            if ( ! from.contains( * current->data ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                auto * before = current->pPrevious;
                auto * after = current->pNext;

                if ( before == nullptr ) {
                    this->_pFront = after;
                } else {
                    before->pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = before;
                } else {
                    after->pPrevious = before;
                }

                auto * toRemove = current;

                nextNode();

                -- this->_size;
                Memory :: instance().destroy ( toRemove->data );
                Memory :: instance().destroy ( toRemove );
                return true;
            }

            nextNode();
        }

        return false;
    }

    template < typename T >
    auto DoubleLinkedList<T>::remove ( Iterator const & iterator ) noexcept (false) -> T {
        if ( ! iterator.of (this ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
            throw IllegalArgumentException("Iterator is not of this Collection");
        }

        if ( this->empty() ) {
            throw OutOfBoundsException("List is Empty");
        }

        auto pDelegate = reinterpret_cast < DoubleLinkedListDelegateIterator * > ( Collection < T > ::acquireDelegate (iterator ) );

        if ( pDelegate->node() == this->_pFront ) {
            return this->popFront();
        }

        if ( pDelegate->node() == this->_pBack ) {
            return this->popBack();
        }

        /// remove by using previous & next instead
        for ( auto node = this->_pFront->pNext; node != this->_pBack; node = node->pNext ) { // NOLINT(clion-misra-cpp2008-6-5-2,clion-misra-cpp2008-6-5-4)
            if ( pDelegate->node() == node ) {
                auto before = node->pPrevious;
                auto next = node->pNext;

                before->pNext = next;
                next->pPrevious = before;

                auto retVal = * node->data;
                -- this->_size;

                Memory :: instance().destroy ( node->data );
                Memory :: instance().destroy ( node );

                return retVal;
            }
        }

        throw IllegalArgumentException ("Wrong List Iterator");
    }

    template < typename T >
    DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const & obj __CDS_MaybeUnused) noexcept {
        for ( const auto & element __CDS_MaybeUnused : obj ) {
            (void) this->pushBack(element);
        }
    }

    template < typename T >
    auto DoubleLinkedList<T>::clear() noexcept -> void {
        while ( this->_pFront != nullptr ) {
            auto current = this->_pFront;
            this->_pFront = this->_pFront->pNext;

            Memory :: instance().destroy (current->data);
            Memory :: instance().destroy (current);
        }

        this->_pBack = nullptr;
        this->_size = 0;
    }

    template < typename T >
    auto DoubleLinkedList<T>::makeUnique() noexcept -> void {
        DoubleLinkedList<T> uniqueList;

        for ( const auto & element __CDS_MaybeUnused : (*this) ) {
            if ( ! uniqueList.contains(element)) { // NOLINT(clion-misra-cpp2008-5-3-1)
                uniqueList.pushBack(element);
            }
        }

        * this = uniqueList;
    }

    template < typename T >
    auto DoubleLinkedList<T>::operator =(Collection <T> const & collection __CDS_MaybeUnused) noexcept -> DoubleLinkedList<T> & {
        if ( this == & collection ) {
            return * this;
        }

        this->clear();
        for ( auto & element __CDS_MaybeUnused : collection ) {
            (void) this->pushBack (element );
        }

        return * this;
    }

}

#include <CDS/Utility>

namespace cds {

    template < typename T >
    auto DoubleLinkedList < T > :: pAt ( Index pos __CDS_MaybeUnused ) noexcept (false) -> ElementPtr {
        if ( this->empty() ) {
            throw OutOfBoundsException(pos, 0);
        }

        if ( pos < 0 ) {
            pos += ((-pos) / this->size() + 1) * this->size();
        }

        if ( pos >= static_cast<Index>(this->size()) ) {
            pos = pos % this->size();
        }

        auto current __CDS_MaybeUnused = 0;
        for ( auto & element __CDS_MaybeUnused : (*this) ) {
            if ( current == pos ) {
                return & element;
            }

            ++ current ;
        }

        return nullptr;
    }

}

#include <CDS/Utility>

namespace cds {

    template < typename T >
    auto DoubleLinkedList < T > :: pAt ( Index pos __CDS_MaybeUnused ) const noexcept (false) -> ElementCPtr {
        if ( this->empty() ) {
            throw OutOfBoundsException(pos, 0);
        }

        if ( pos < 0 ) {
            pos += ((-pos) / this->size() + 1) * this->size();
        }

        if ( pos >= static_cast<Index>(this->size()) ) {
            pos = pos % this->size();
        }

        auto current __CDS_MaybeUnused = 0;
        for ( auto & element __CDS_MaybeUnused : (*this) ) {
            if ( current == pos ) {
                return & element;
            }

            ++ current ;
        }

        return nullptr;
    }

    template < typename T >
    DoubleLinkedList<T>::DoubleLinkedList(
            Iterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            Iterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            (void) this->pushBack ( * it );
        }
    }

    template < typename T >
    DoubleLinkedList<T>::DoubleLinkedList(
            ConstIterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            ConstIterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            (void) this->pushBack ( * it );
        }
    }

}

#if ! defined(__CDS_LateInclude_Sequence)
#include <CDS/Sequence>
#endif

namespace cds {

    template < typename T >
    auto DoubleLinkedList < T > :: sequence () const & noexcept -> Sequence < DoubleLinkedList < T > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template < typename T >
    auto DoubleLinkedList < T > :: sequence () & noexcept -> Sequence < DoubleLinkedList < T > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template < typename T >
    auto DoubleLinkedList < T > :: sequence () const && noexcept -> Sequence < DoubleLinkedList < T > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template < typename T >
    auto DoubleLinkedList < T > :: sequence () && noexcept -> Sequence < DoubleLinkedList < T > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    inline auto String::split(ElementType token, Size limit) const noexcept -> DoubleLinkedList < String > {
        Index splitIndex = 0;
        if (limit < 1u ) {
            limit = limits :: U32_MAX;
        }

        DoubleLinkedList < String > segments;
        if ( this->empty() ) {
            return segments;
        }

        String currentSegment;

        for ( auto character : (*this) ) {
            if (character != token || splitIndex >= static_cast<Index>(limit) - 1 ) {
                currentSegment += character;
            } else {
                if ( currentSegment.empty() ) {
                    continue;
                }

                splitIndex ++;
                (void) segments.pushBack ( currentSegment );
                currentSegment.clear();
            }
        }

        if ( ! currentSegment.empty() ) {
            (void) segments.pushBack(currentSegment);
        }

        return segments;
    }

    __CDS_MaybeUnused inline auto String::lines() const noexcept -> DoubleLinkedList < String >{
        return this->split("\n\r");
    }

    inline auto String::split(String const & delim, Size limit) const noexcept -> DoubleLinkedList < String > {
        Index splitIndex = 0;
        if (limit < 1u ) {
            limit = limits :: U64_MAX;
        }

        DoubleLinkedList < String > segments;
        if ( this->empty() ) {
            return segments;
        }

        String currentSegment;

        for ( auto character : (*this) ) {
            if (! delim.contains(character) || splitIndex >= static_cast<Index>(limit) - 1 ) {
                currentSegment += character;
            } else {
                splitIndex ++;
                if ( ! currentSegment.empty() ) {
                    (void) segments.pushBack(currentSegment);
                }

                currentSegment.clear();
            }
        }

        if ( ! currentSegment.empty() ) {
            (void) segments.pushBack(currentSegment);
        }
        return segments;
    }

    __CDS_MaybeUnused inline auto String::splitByString(String const & token, Size limit) const noexcept -> DoubleLinkedList < String > {
        String copy = * this;
        auto locations = this->find(token);

        auto index = static_cast < Index > (locations.size()) - 1;
        for ( auto it = locations.rbegin(); it != locations.rend(); ++it, --index ) { // NOLINT(clion-misra-cpp2008-5-18-1)
            if (static_cast < Size > ( index + 1 ) < limit ) {
                (void) copy.replace(* it, token.length(), "\x01");
            }
        }

        return copy.split('\x01');
    }

    inline auto String::find (ElementType element) const noexcept -> DoubleLinkedList < Index > {
        DoubleLinkedList < Index > indices;

        Index index = 0;
        for ( auto character : (*this) ) {
            if (character == element ) {
                (void) indices.pushBack(index);
            }

            index++;
        }

        return indices;
    }

    __CDS_MaybeUnused inline auto String::findOf (String const & string) const noexcept -> DoubleLinkedList < Index > {
        DoubleLinkedList < Index > indices;

        Index index = 0;
        for ( auto character : (*this) ) {
            if ( string.contains(character) ) {
                (void) indices.pushBack(index);
            }

            index++;
        }

        return indices;
    }

    __CDS_MaybeUnused inline auto String::findNotOf (String const & string) const noexcept -> DoubleLinkedList < Index > {
        DoubleLinkedList < Index > indices;

        Index index = 0;
        for ( auto character : (*this) ) {
            if ( ! string.contains(character) ) {
                (void) indices.pushBack(index);
            }

            index++;
        }

        return indices;
    }

    inline auto String::find (String const & string) const noexcept -> DoubleLinkedList < Index > {
    #if !defined(_MSC_VER)
        Index lpsArray [string.size()];
    #else
        auto lpsArray = Memory :: instance().createArray < Index > (this->size());
    #endif
        (void) std::memset(reinterpret_cast < void * > ( lpsArray ), 0, sizeof(Index) * string.size()); // NOLINT(clion-misra-cpp2008-5-2-12)

        auto computeLPSArray = [& string, &lpsArray] () {
            Index len = 0;
            lpsArray[0] = 0;

            Index index = 1;
            while (index < static_cast<Index>(string.size()) ) {
                if (string._p[index] == string._p[len] ) {
                    len ++;
                    lpsArray[index] = len;
                    index ++;
                } else {
                    if ( len != 0 ) {
                        len = lpsArray[len - 1];
                    } else {
                        lpsArray[index] = 0;
                        index ++;
                    }
                }
            }
        };

        computeLPSArray();

        DoubleLinkedList < Index > indices;
        Index headIndex = 0;
        Index aheadIndex = 0;

        while (headIndex < static_cast<Index>(this->size()) ) {
            if (string._p[aheadIndex] == this->_p[headIndex] ) {
                headIndex ++; aheadIndex ++;
            }

            if (aheadIndex == static_cast<Index>(string.size()) ) {
                (void) indices.pushBack(headIndex - aheadIndex);
                aheadIndex = lpsArray[aheadIndex - 1];
            } else if (headIndex < static_cast<Index>(this->size()) && this->_p[headIndex] != string._p[aheadIndex] ) {
                if (aheadIndex != 0 ) {
                    aheadIndex = lpsArray[aheadIndex - 1];
                } else {
                    ++ headIndex;
                }
            } else {
                /// do nothing
            }
        }

    #if !defined(_MSC_VER)
    #else
        Memory :: instance().destroyArray ( lpsArray );
    #endif
        return indices;
    }

}

namespace cds {

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: find ( ElementCRef element, Size count ) noexcept -> DoubleLinkedList < Iterator > {
        DoubleLinkedList < Iterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( Type < ElementType > :: compare ( element, * it ) && added < count ) {
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: findOf ( Collection < ElementType > const & elements, Size count ) noexcept -> DoubleLinkedList < Iterator > {
        DoubleLinkedList < Iterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( elements.contains ( * it ) && added < count ) {
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: findNotOf ( Collection < ElementType > const & elements, Size count ) noexcept -> DoubleLinkedList < Iterator > {
        DoubleLinkedList < Iterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( ! elements.contains ( * it ) && added < count ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: find ( ElementCRef element, Size count ) const noexcept -> DoubleLinkedList < ConstIterator > {
        DoubleLinkedList < ConstIterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( Type < ElementType > :: compare ( element, * it ) && added < count ) {
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: findOf ( Collection < ElementType > const & elements, Size count ) const noexcept -> DoubleLinkedList < ConstIterator > {
        DoubleLinkedList < ConstIterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( elements.contains ( * it ) && added < count ) {
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

    template < typename T >
    __CDS_MaybeUnused auto List < T > :: findNotOf ( Collection < ElementType > const & elements, Size count ) const noexcept -> DoubleLinkedList < ConstIterator > {
        DoubleLinkedList < ConstIterator > iterators;
        Size added = 0u;

        for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
            if ( ! elements.contains ( * it ) && added < count ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                iterators.add(it);
                ++ added;
            } else if ( added >= count ) {
                break;
            } else {
                /// do nothing
            }
        }

        return iterators;
    }

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template < typename T >
    DoubleLinkedList ( std::initializer_list < T > ) -> DoubleLinkedList < T >;

}

#endif

__CDS_RegisterParseTypeTemplateT(DoubleLinkedList) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_DOUBLELINKEDLIST_HPP
