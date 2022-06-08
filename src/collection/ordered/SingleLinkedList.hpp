//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_SINGLELINKEDLIST_HPP
#define CDS_SINGLELINKEDLIST_HPP

#include <CDS/List>

namespace cds {

    template < typename T >
    class SingleLinkedList : public List < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        using ElementType                   = typename List < T > :: ElementType;

    protected:
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

    protected:
        using DelegateIterator              = typename List < T > :: DelegateIterator;
        using DelegateConstIterator         = typename List < T > :: DelegateConstIterator;

    private:
        struct Node {
            ElementType * _data;
            Node        * _pNext;
        };

        Node * _pFront  {nullptr};
        Node * _pBack   {nullptr};

    protected:

        class SingleLinkedListDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < SingleLinkedList :: Node > _pNode;

        public:
            explicit constexpr SingleLinkedListDelegateIterator ( SingleLinkedList :: Node * pNode ) noexcept :
                    DelegateIterator (),
                    _pNode ( pNode ) {

            }

            __CDS_NoDiscard constexpr auto node () const noexcept -> Node * {
                return this->_pNode.get();
            }

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return this->_pNode != nullptr;
            }

            constexpr SingleLinkedListDelegateIterator ( SingleLinkedListDelegateIterator const & ) noexcept = default;
            constexpr SingleLinkedListDelegateIterator ( SingleLinkedListDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~SingleLinkedListDelegateIterator() noexcept override = default;

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> SingleLinkedListDelegateIterator & override {
                this->_pNode = this->_pNode->_pNext;
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pNode->_data;
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype (this) > ( & iterator );

                return this->_pNode == pIterator->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> SingleLinkedListDelegateIterator * override {
                return Memory :: instance() .create < SingleLinkedListDelegateIterator > ( * this );
            }
        };

        class SingleLinkedListDelegateConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < SingleLinkedList :: Node const > _pNode;

        public:
            explicit constexpr SingleLinkedListDelegateConstIterator ( SingleLinkedList :: Node const * pNode ) noexcept :
                    DelegateConstIterator (),
                    _pNode ( pNode ) {

            }

            constexpr SingleLinkedListDelegateConstIterator ( SingleLinkedListDelegateConstIterator const & ) noexcept = default;
            constexpr SingleLinkedListDelegateConstIterator ( SingleLinkedListDelegateConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~SingleLinkedListDelegateConstIterator() noexcept override = default;

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> SingleLinkedListDelegateConstIterator & override {
                this->_pNode = this->_pNode->_pNext;
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pNode->_data;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype (this) > ( & iterator );

                return this->_pNode == pIterator->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> SingleLinkedListDelegateConstIterator * override {
                return Memory :: instance() .create < SingleLinkedListDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SingleLinkedListDelegateIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SingleLinkedListDelegateIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                case DelegateIteratorRequestType :: BACKWARD_END:
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SingleLinkedListDelegateConstIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SingleLinkedListDelegateConstIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                case DelegateIteratorRequestType :: BACKWARD_END:
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

    public:
        constexpr static const Index INVALID_POS = -1;

        constexpr SingleLinkedList ( ) noexcept = default;
        SingleLinkedList ( SingleLinkedList const & ) noexcept;

        __CDS_cpplang_ConstexprConstructorNonEmptyBody SingleLinkedList ( SingleLinkedList && obj ) noexcept :
                List < T > ( std :: forward < List < T > > ( obj ) ),
                _pFront ( exchange( obj._pFront, nullptr ) ),
                _pBack ( exchange( obj._pBack, nullptr ) ) {

            this->_size = exchange( obj._size, 0 );
        }

        SingleLinkedList (
                Iterator const &,
                Iterator const &
        ) noexcept;

        SingleLinkedList (
                ConstIterator const &,
                ConstIterator const &
        ) noexcept;

        SingleLinkedList ( InitializerList ) noexcept; // NOLINT(google-explicit-constructor)

        ~SingleLinkedList() noexcept override;

    public:
        virtual auto remove (Index) noexcept -> bool;

        auto remove ( ElementCRef , Size ) noexcept -> bool override;
        auto removeLast ( ElementCRef ) noexcept -> bool override;

        auto removeOf ( Collection<T> const &, Size ) noexcept -> bool override;
        auto removeLastOf ( Collection<T> const & ) noexcept -> bool override;

        auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool override;
        auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool override;

        auto remove ( Iterator const & ) noexcept (false) -> T override;

        __CDS_OptimalInline auto removeOf ( InitializerList list, Size count ) noexcept -> bool override {
            return this->removeOf ( SingleLinkedList <T> (list), count );
        }

        __CDS_OptimalInline auto removeLastOf ( InitializerList list ) noexcept -> bool override {
            return this->removeLastOf ( SingleLinkedList<T> (list) );
        }

        __CDS_OptimalInline auto removeNotOf ( InitializerList list, Size count ) noexcept -> bool override {
            return this->removeNotOf( SingleLinkedList<T> (list), count );
        }

        __CDS_OptimalInline auto removeLastNotOf ( InitializerList list ) noexcept -> bool override {
            return this->removeLastNotOf( SingleLinkedList<T> (list) );
        }

        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_data;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_data;
        }

        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_data;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_data;
        }

        __CDS_NoDiscard auto operator == (SingleLinkedList const & list) const noexcept -> bool {
            if ( this == & list ) {
                return true;
            }

            if (this->size() != list.size() ) {
                return false;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                        aIt = this->begin(), aEnd = this->end(),
                        bIt = list.begin(), bEnd = list.end();
                    aIt != aEnd && bIt != bEnd;
                    ++ aIt, ++ bIt // NOLINT(clion-misra-cpp2008-5-18-1)
            ) {
                if ( ! Type < T > :: compare (* aIt, * bIt ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & object ) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < SingleLinkedList < T > const * > (& object);
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator==(* pObject);
        }

        auto clear () noexcept -> void final;
        auto makeUnique () noexcept -> void override;

        auto popFront () noexcept (false) -> ElementType override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            -- this->_size;

            auto node = this->_pFront;
            auto value = * node->_data;

            if ( this->size() == 0 ) {
                this->_pFront = nullptr;
                this->_pBack = nullptr;
            } else {
                this->_pFront = this->_pFront->_pNext;
            }

            Memory::instance().destroy ( node->_data );
            Memory::instance().destroy ( node );
            return value;
        }

        auto popBack () noexcept (false) -> ElementType override {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            if ( this->size() == 1 ) {
                auto value = * this->_pFront->_data;

                Memory::instance().destroy ( this->_pFront->_data );
                Memory::instance().destroy ( this->_pFront );

                this->_pFront = nullptr;
                this->_pBack = nullptr;
                this->_size = 0;

                return value;
            }

            auto pFront = this->_pFront;

            while (pFront->_pNext->_pNext != nullptr ) {
                pFront = pFront->_pNext;
            }

            auto value = * this->_pBack->_data;

            pFront->_pNext = nullptr;

            Memory :: instance().destroy ( this->_pBack->_data );
            Memory :: instance().destroy ( this->_pBack );
            this->_pBack = pFront;

            return value;
        }

    private:

        auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
        auto allocBackGetPtr () noexcept -> ElementPtrRef override;

        __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef element __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
            return this->allocBackGetPtr();
        }

        auto pAt (Index) noexcept (false) -> ElementPtr override;
        auto pAt (Index) const noexcept (false) -> ElementCPtr override;

    public:

        auto operator = ( Collection < T > const & ) noexcept -> SingleLinkedList &;

        __CDS_OptimalInline auto operator = ( SingleLinkedList const & list ) noexcept -> SingleLinkedList & {  // NOLINT(bugprone-unhandled-self-assignment)
            return this->operator= ( reinterpret_cast < Collection <T> const & > ( list ) ); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptimalInline auto operator = ( SingleLinkedList && list ) noexcept -> SingleLinkedList & {
            if ( this == & list ) {
                return * this;
            }

            this->clear();
            this->_pFront = exchange(list._pFront, nullptr );
            this->_pBack = exchange(list._pBack, nullptr );
            this->_size = exchange(list._size, 0 );

            return * this;
        }

        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < SingleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < SingleLinkedList < T > >;
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < SingleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < SingleLinkedList < T > >;

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index override {
            return this->size();
        }
    };

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList ( InitializerList initializerList __CDS_MaybeUnused ) noexcept {
        for ( auto const & element __CDS_MaybeUnused : initializerList ) {
            (void) this->pushBack(element);
        }
    }

    template < typename T >
    SingleLinkedList < T > :: ~SingleLinkedList() noexcept {
        this->clear();
    }

}

#include <sstream>

namespace cds {

    template < typename T >
    auto SingleLinkedList < T > :: remove ( Index index ) noexcept -> bool {
        if (index < 0 || index >= this->size() ) {
            return false;
        }

        if (index == 0 ) {
            (void) this->popFront();
            return true;
        }

        auto current = this->_pFront;
        Index currentIndex = 1;

        while ( current->_pNext != nullptr && currentIndex < index ) {
            current = current->_pNext;
            currentIndex ++;
        }

        auto toRemove = current->_pNext;

        current->_pNext = current->_pNext->_pNext;

        Memory :: instance().destroy ( toRemove->_data );
        Memory :: instance().destroy ( toRemove );
        return true;
    }

    template < typename T >
    auto SingleLinkedList < T > :: remove ( ElementCRef what, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        decltype (current) previous = nullptr;

        auto nextNode = [& current] () noexcept { current = current->_pNext; };

        while ( current != nullptr && count > 0u ) {
            if ( Type < T > :: compare ( * current->_data, what ) ) {
                auto after = current->_pNext;

                if ( previous == nullptr ) {
                    this->_pFront = after;
                } else {
                    previous->_pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = previous;
                }

                auto toRemove = current;

                count --;
                this->_size --;

                nextNode();

                Memory::instance().destroy ( toRemove->_data );
                Memory::instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            previous = current;
            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto SingleLinkedList < T > :: removeLast ( ElementCRef what ) noexcept -> bool {
        auto current = this->_pFront;
        decltype (current) previous = Type < T > :: compare ( * current->_data, what ) ? current : nullptr;

        auto nextNode = [& current] () noexcept  { current = current->_pNext; };

        if ( Type < T > :: compare ( * this->_pFront->_data, what ) ) {
            auto pFront = this->_pFront;

            this->_pFront = this->_pFront->_pNext;

            Memory :: instance().destroy (pFront->_data );
            Memory :: instance().destroy (pFront );
            this->_size --;

            if ( this->size() == 0 ) {
                this->_pBack = nullptr;
            }

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( Type < T > :: compare ( * current->_pNext->_data, what ) ) {
                previous = current;
            }

            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->_pNext == this->_pBack ) {
                this->_pBack = previous;
            }

            auto pNode = previous->_pNext;
            previous->_pNext = previous->_pNext->_pNext;
            Memory :: instance().destroy (pNode->_data );
            Memory :: instance().destroy (pNode );
            this->_size --;

            return true;
        }

        return false;
    }

    template < typename T >
    auto SingleLinkedList < T > :: removeOf ( Collection < T > const & from, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        decltype (current) previous = nullptr;

        auto nextNode = [& current] () noexcept { current = current->_pNext; };

        while ( current != nullptr && count > 0u ) {
            if ( from.contains( * current->_data ) ) {
                auto after = current->_pNext;

                if ( previous == nullptr ) {
                    this->_pFront = after;
                } else {
                    previous->_pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = previous;
                }

                auto toRemove = current;

                count --;
                this->_size --;

                nextNode();

                Memory :: instance().destroy ( toRemove->_data );
                Memory :: instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            previous = current;
            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto SingleLinkedList < T > :: removeLastOf ( Collection < T > const & from ) noexcept -> bool {
        auto current = this->_pFront;
        decltype (current) previous = from.contains(* current->_data) ? current : nullptr;

        auto nextNode = [& current] () noexcept {
            current = current->_pNext;
        };

        if ( from.contains(* this->_pFront->_data) ) {
            auto pFront = this->_pFront;

            this->_pFront = this->_pFront->_pNext;

            Memory :: instance().destroy (pFront->_data );
            Memory :: instance().destroy (pFront );

            -- this->_size;

            if ( this->size() == 0 ) {
                this->_pBack = nullptr;
            }

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( from.contains( * current->_pNext->_data ) ) {
                previous = current;
            }

            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->_pNext == this->_pBack ) {
                this->_pBack = previous;
            }

            auto pNode = previous->_pNext;
            previous->_pNext = previous->_pNext->_pNext;
            Memory :: instance().destroy (pNode->_data );
            Memory :: instance().destroy (pNode );
            this->_size --;

            return true;
        }

        return false;
    }

    template < typename T >
    auto SingleLinkedList < T > :: removeNotOf ( Collection < T > const & from, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        decltype (current) previous = nullptr;

        auto nextNode = [& current] () noexcept {
            current = current->_pNext;
        };

        while ( current != nullptr && count > 0u ) {
            if ( ! from.contains( * current->_data ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                auto after = current->_pNext;

                if ( previous == nullptr ) {
                    this->_pFront = after;
                } else {
                    previous->_pNext = after;
                }

                if ( after == nullptr ) {
                    this->_pBack = previous;
                }

                auto toRemove = current;

                -- count;
                -- this->_size;

                nextNode();

                Memory :: instance().destroy ( toRemove->_data );
                Memory :: instance().destroy ( toRemove );

                removalDone = true;
                continue;
            }

            previous = current;
            nextNode();
        }

        return removalDone;
    }

    template < typename T >
    auto SingleLinkedList < T > :: removeLastNotOf ( Collection < T > const & from ) noexcept -> bool {
        auto current = this->_pFront;
        decltype (current) previous = ! from.contains(* current->_data) ? current : nullptr; // NOLINT(clion-misra-cpp2008-5-3-1)

        auto nextNode = [& current] () noexcept {
            current = current->_pNext;
        };

        if ( ! from.contains(* this->_pFront->_data) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
            auto pFront = this->_pFront;

            this->_pFront = this->_pFront->_pNext;
            Memory::instance().destroy (pFront->_data );
            Memory::instance().destroy (pFront );
            --this->_size;

            if ( this->size() == 0 ) {
                this->_pBack = nullptr;
            }

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( ! from.contains( * current->_pNext->_data) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                previous = current;
            }

            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->_pNext == this->_pBack ) {
                this->_pBack = previous;
            }

            auto pNode = previous->_pNext;
            previous->_pNext = previous->_pNext->_pNext;
            Memory :: instance().destroy (pNode->_data );
            Memory :: instance().destroy (pNode );
            this->_size --;

            return true;
        }

        return false;
    }

    template < typename T >
    auto SingleLinkedList < T > :: remove ( Iterator const & iterator ) noexcept (false) -> T {
        if ( ! iterator.of (this ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
            throw IllegalArgumentException("Iterator not of this Collection");
        }

        if ( this->empty() ) {
            throw IllegalArgumentException("List is Empty");
        }

        auto pDelegate = reinterpret_cast < SingleLinkedListDelegateIterator * > ( Collection < T > :: acquireDelegate(iterator ) );

        if ( this->_pFront == pDelegate->node() ) {
            return this->popFront();
        }

        if ( this->_pBack == pDelegate->node() ) {
            return this->popBack();
        }

        for ( auto node = this->_pFront; node->_pNext != this->_pBack; node = node->_pNext ) { // NOLINT(clion-misra-cpp2008-6-5-2,clion-misra-cpp2008-6-5-4)
            if ( node->_pNext == pDelegate->node() ) {
                auto pNode = node->_pNext;
                node->_pNext = node->_pNext->_pNext;

                auto retVal = * pNode->_data;
                -- this->_size;
                Memory :: instance().destroy (pNode->_data );
                Memory :: instance().destroy (pNode );

                return retVal;
            }
        }

        throw IllegalArgumentException("Wrong List Iterator");
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList ( SingleLinkedList const & obj __CDS_MaybeUnused ) noexcept {
        for ( auto & element __CDS_MaybeUnused : obj ) {
            (void) this->pushBack(element);
        }
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList (
            Iterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            Iterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            (void) this->pushBack ( * it );
        }
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList (
            ConstIterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            ConstIterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            (void) this->pushBack ( * it );
        }
    }

    template < typename T >
    auto SingleLinkedList < T > :: clear () noexcept -> void {
        this->_size = 0;
        this->_pBack = nullptr;

        while ( this->_pFront != nullptr ) {
            auto pObject = this->_pFront;
            this->_pFront = this->_pFront->_pNext;
            Memory :: instance().destroy (pObject->_data );
            Memory :: instance().destroy (pObject );
        }
    }

    template < typename T >
    auto SingleLinkedList < T > :: makeUnique() noexcept -> void {
        SingleLinkedList newList;

        for ( auto const & element __CDS_MaybeUnused : * this ) {
            if ( ! newList.contains(element)) { // NOLINT(clion-misra-cpp2008-5-3-1)
                (void) newList.pushBack(element);
            }
        }

        * this = newList;
    }

    template < typename T >
    auto SingleLinkedList < T > :: operator = ( Collection < T > const & collection ) noexcept -> SingleLinkedList & {
        if ( this == & collection ) {
            return * this;
        }

        this->clear();

        collection.forEach([this](T const & element){
            (void) this->pushBack(element);
        });

        return * this;
    }

    template < typename T >
    auto SingleLinkedList < T > ::allocFrontGetPtr() noexcept -> ElementPtrRef {
        auto pNode = Memory :: instance ().create < Node > ();
        pNode->_data = nullptr;
        pNode->_pNext = this->_pFront;

        this->_pFront = pNode;

        ++ this->_size;
        if ( this->size() == 1 ) {
            this->_pBack = this->_pFront;
        }

        return this->_pFront->_data;
    }

    template < typename T >
    auto SingleLinkedList < T > ::allocBackGetPtr() noexcept -> ElementPtrRef {
        if ( this->empty() ) {
            return this->allocFrontGetPtr();
        }

        this->_pBack->_pNext = Memory :: instance().create < Node > ();
        this->_pBack->_pNext->_data = nullptr;
        this->_pBack->_pNext->_data = nullptr;

        this->_pBack = this->_pBack->_pNext;
        ++ this->_size;

        return this->_pBack->_data;
    }

}

#include <CDS/Sequence>

namespace cds {

    template < typename T >
    auto SingleLinkedList < T > :: sequence () const & noexcept -> Sequence < SingleLinkedList < T > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template < typename T >
    auto SingleLinkedList < T > :: sequence () & noexcept -> Sequence < SingleLinkedList < T > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template < typename T >
    auto SingleLinkedList < T > :: sequence () const && noexcept -> Sequence < SingleLinkedList < T > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template < typename T >
    auto SingleLinkedList < T > :: sequence () && noexcept -> Sequence < SingleLinkedList < T > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template < typename T >
    auto SingleLinkedList < T > :: pAt ( Index index __CDS_MaybeUnused ) noexcept(false) -> ElementPtr {
        if ( this->size() == 0 ) {
            throw OutOfBoundsException(index, 0);
        }

        if ( index < 0 ) {
            index += ((-index) / this->size() + 1) * this->size();
        }

        if ( index >= static_cast<Index>(this->size()) ) {
            index = index % this->size();
        }

        auto current __CDS_MaybeUnused = 0;
        for ( auto & element __CDS_MaybeUnused : (*this) ) {
            if ( current == index ) {
                return & element;
            }

            current ++;
        }

        return nullptr;
    }

    template < typename T >
    auto SingleLinkedList < T > :: pAt ( Index index __CDS_MaybeUnused ) const noexcept(false) -> ElementCPtr {
        if ( this->size() == 0 ) {
            throw OutOfBoundsException(index, 0);
        }

        if ( index < 0 ) {
            index += ((-index) / this->size() + 1) * this->size();
        }

        if ( index >= static_cast<Index>(this->size()) ) {
            index = index % this->size();
        }

        auto current __CDS_MaybeUnused = 0;
        for ( auto & element __CDS_MaybeUnused : (*this) ) {
            if ( current == index ) {
                return & element;
            }

            current ++;
        }

        return nullptr;
    }

}

__CDS_RegisterParseTypeTemplateT(SingleLinkedList) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_SINGLELINKEDLIST_HPP
