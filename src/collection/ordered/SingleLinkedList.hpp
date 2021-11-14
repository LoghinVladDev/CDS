//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_SINGLELINKEDLIST_HPP
#define CDS_SINGLELINKEDLIST_HPP

#include <CDS/List>

namespace cds {

    template < typename T >
    class SingleLinkedList : public List < T > {
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
            ElementPtr  _data  {nullptr};
            Node      * _pNext {nullptr};

            constexpr Node () noexcept = default;

        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Node * & { return this->_pNext; }
        constexpr auto next () const noexcept -> Node const * const & { return this->_pNext; }

        __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> T * & { return this->_data; }
        constexpr auto data () const noexcept -> T const * const & { return this->_data; }
    };

        Node * _pFront {nullptr};
        Node * _pBack {nullptr};

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
                this->_pNode = this->_pNode->next();
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pNode->data();
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype (this) > ( & it );

                return this->_pNode == p->_pNode;
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
                this->_pNode = this->_pNode->next();
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pNode->data();
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype (this) > ( & it );

                return this->_pNode == p->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> SingleLinkedListDelegateConstIterator * override {
                return Memory :: instance() .create < SingleLinkedListDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < SingleLinkedListDelegateIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < SingleLinkedListDelegateIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                case DelegateIteratorRequestType :: BACKWARD_END:
                default:
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < SingleLinkedListDelegateConstIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < SingleLinkedListDelegateConstIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                case DelegateIteratorRequestType :: BACKWARD_END:
                default:
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
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            return * this->_pBack->data();
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef override {
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            return * this->_pBack->data();
        }

        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef override {
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            return * this->_pFront->data();
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef override {
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            return * this->_pFront->data();
        }

        __CDS_NoDiscard auto operator == (SingleLinkedList const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            if ( this->size() != o.size() ) return false;

            for (
                    auto
                        a = this->begin(), aEnd = this->end(),
                        b = o.begin(), bEnd = o.end();
                    a != aEnd && b != bEnd;
                    ++ a, ++ b
            )
                if ( ! Type < T > :: compare ( * a, * b ) )
                    return false;

            return true;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & o ) const noexcept -> bool final {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype (this) > (& o);
            if ( p == nullptr ) return false;

            return this->operator==(* p);
        }

        auto clear () noexcept -> void final;
        auto makeUnique () noexcept -> void override;

        auto popFront () noexcept (false) -> ElementType override {
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            -- this->_size;

            auto node = this->_pFront;
            auto value = * node->_data;

            if ( this->size() == 0 )
                this->_pFront = this->_pBack = nullptr;
            else
                this->_pFront = this->_pFront->_pNext;

            Memory::instance().destroy ( node->data() );
            Memory::instance().destroy ( node );
            return value;
        }

        auto popBack () noexcept (false) -> ElementType override {
            if ( this->empty() )
                throw OutOfBoundsException ( "List is Empty" );

            if ( this->size() == 1 ) {
                auto v = * this->_pFront->_data;

                Memory::instance().destroy ( this->_pFront->data() );
                Memory::instance().destroy ( this->_pFront );

                this->_pFront = this->_pBack = nullptr;
                this->_size = 0;

                return v;
            }

            auto p = this->_pFront;

            while ( p->_pNext->_pNext != nullptr )
                p = p->_pNext;

            auto v = * this->_pBack->_data;

            p->_pNext = nullptr;

            Memory :: instance().destroy ( this->_pBack->data() );
            Memory :: instance().destroy ( this->_pBack );
            this->_pBack = p;

            return v;
        }

    private:

        auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
        auto allocBackGetPtr () noexcept -> ElementPtrRef override;

        __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
            return this->allocBackGetPtr();
        }

        auto pAt (Index) noexcept (false) -> ElementPtr override;
        auto pAt (Index) const noexcept (false) -> ElementCPtr override;

    public:

        auto operator = ( Collection < T > const & ) noexcept -> SingleLinkedList &;

        __CDS_OptimalInline auto operator = ( SingleLinkedList const & o ) noexcept -> SingleLinkedList & {  // NOLINT(bugprone-unhandled-self-assignment)
            return this->operator= ( (Collection <T> const &)o ); // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptimalInline auto operator = ( SingleLinkedList && o ) noexcept -> SingleLinkedList & {
            if ( this == & o ) return * this;

            this->clear();
            this->_pFront = exchange( o._pFront, nullptr );
            this->_pBack = exchange( o._pBack, nullptr );
            this->_size = exchange( o._size, 0 );

            return * this;
        }

        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < SingleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < SingleLinkedList < T > >;
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < SingleLinkedList < T > const >;
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < SingleLinkedList < T > >;

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> SingleLinkedList < T > * override {
            return Memory :: instance().create < SingleLinkedList > (* this);
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Index override {
            return this->size();
        }
    };

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList ( InitializerList initializerList ) noexcept {
        for ( auto const & e : initializerList )
            this->pushBack(e);
    }

    template < typename T >
    SingleLinkedList < T > :: ~SingleLinkedList() noexcept {
        this->clear();
    }

}

#include <sstream>

namespace cds {

    template < typename T >
    auto SingleLinkedList < T > :: remove ( Index i ) noexcept -> bool {
        if ( i < 0 || i >= this->size() ) return false;
        if ( i == 0 ) { this->popFront(); return true; }

        auto current = this->_pFront;
        Index currentIndex = 1;

        while ( current->next() != nullptr && currentIndex < i ) {
            current = current->next();
            currentIndex ++;
        }

        auto toRemove = current->next();

        current->next() = current->next()->next();

        Memory :: instance().destroy ( toRemove->data() );
        Memory :: instance().destroy ( toRemove );
        return true;
    }

    template < typename T >
    auto SingleLinkedList < T > :: remove ( ElementCRef what, Size count ) noexcept -> bool {
        bool removalDone = false;

        auto current = this->_pFront;
        decltype (current) previous = nullptr;

        auto nextNode = [& current] () noexcept { current = current->next(); };

        while ( current != nullptr && count > 0 ) {
            if ( Type < T > :: compare ( * current->data(), what ) ) {
                auto after = current->next();

                if ( previous == nullptr )
                    this->_pFront = after;
                else
                    previous->next() = after;

                if ( after == nullptr )
                    this->_pBack = previous;

                auto toRemove = current;

                count --;
                this->_size --;

                nextNode();

                Memory::instance().destroy ( toRemove->data() );
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
        decltype (current) previous = Type < T > :: compare ( * current->data(), what ) ? current : nullptr;

        auto nextNode = [& current] () noexcept  { current = current->next(); };

        if ( Type < T > :: compare ( * this->_pFront->data(), what ) ) {
            auto p = this->_pFront;

            this->_pFront = this->_pFront->next();

            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );
            this->_size --;

            if ( this->size() == 0 )
                this->_pBack = nullptr;

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( Type < T > :: compare ( * current->next()->data(), what ) ) previous = current;
            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->next() == this->_pBack )
                this->_pBack = previous;

            auto p = previous->next();
            previous->next () = previous -> next () -> next ();
            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );
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

        auto nextNode = [& current] () noexcept { current = current->next(); };

        while ( current != nullptr && count > 0 ) {
            if ( from.contains( * current->data() ) ) {
                auto after = current->next();

                if ( previous == nullptr )
                    this->_pFront = after;
                else
                    previous->next() = after;

                if ( after == nullptr )
                    this->_pBack = previous;

                auto toRemove = current;

                count --;
                this->_size --;

                nextNode();

                Memory :: instance().destroy ( toRemove->data() );
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
        decltype (current) previous = from.contains(* current->data()) ? current : nullptr;

        auto nextNode = [& current] () noexcept {
            current = current->next();
        };

        if ( from.contains(* this->_pFront->data()) ) {
            auto p = this->_pFront;

            this->_pFront = this->_pFront->next();

            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );

            -- this->_size;

            if ( this->size() == 0 )
                this->_pBack = nullptr;

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( from.contains( * current->next()->data( )) )
                previous = current;
            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->next() == this->_pBack )
                this->_pBack = previous;

            auto p = previous->next();
            previous->next () = previous -> next () -> next ();
            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );
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
            current = current->next();
        };

        while ( current != nullptr && count > 0 ) {
            if ( ! from.contains( * current->data() ) ) {
                auto after = current->next();

                if ( previous == nullptr )
                    this->_pFront = after;
                else
                    previous->next() = after;

                if ( after == nullptr )
                    this->_pBack = previous;

                auto toRemove = current;

                -- count;
                -- this->_size;

                nextNode();

                Memory :: instance().destroy ( toRemove->data() );
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
        decltype (current) previous = ! from.contains(* current->data()) ? current : nullptr;

        auto nextNode = [& current] () noexcept {
            current = current->next();
        };

        if ( ! from.contains(* this->_pFront->data()) ) {
            auto p = this->_pFront;

            this->_pFront = this->_pFront->next();
            Memory::instance().destroy ( p->data() );
            Memory::instance().destroy ( p );
            --this->_size;

            if ( this->size() == 0 )
                this->_pBack = nullptr;

            return true;
        }

        while ( current->_pNext != nullptr ) {
            if ( ! from.contains( * current->next()->data( )) )
                previous = current;
            nextNode();
        }

        if ( previous != nullptr ) {
            if ( previous->next() == this->_pBack )
                this->_pBack = previous;

            auto p = previous->next();
            previous->next () = previous -> next () -> next ();
            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );
            this->_size --;

            return true;
        }

        return false;
    }

    template < typename T >
    auto SingleLinkedList < T > :: remove ( Iterator const & it ) noexcept (false) -> T {
        if ( ! it.of ( this ) )
            throw IllegalArgumentException ( "Iterator not of this Collection" );

        if ( this->empty() )
            throw IllegalArgumentException ( "List is Empty" );

        auto pDelegate = reinterpret_cast < SingleLinkedListDelegateIterator * > ( Collection < T > :: acquireDelegate( it ) );

        if ( this->_pFront == pDelegate->node() )
            return this->popFront();

        if ( this->_pBack == pDelegate->node() )
            return this->popBack();

        for ( auto node = this->_pFront; node->next() != this->_pBack; node = node->next() ) {
            if ( node->next() == pDelegate->node() ) {
                auto p = node->next();
                node->next() = node->next()->next();

                auto retVal = * p->data();
                -- this->_size;
                Memory :: instance().destroy ( p->data() );
                Memory :: instance().destroy ( p );

                return retVal;
            }
        }

        throw IllegalArgumentException("Wrong List Iterator");
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList ( SingleLinkedList const & obj ) noexcept {
        for ( auto & e : obj )
            this->pushBack(e);
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList (
            Iterator const & from,
            Iterator const & to
    ) noexcept {
        for ( auto it = from; it != to; ++ it )
            this->pushBack( * it );
    }

    template < typename T >
    SingleLinkedList < T > :: SingleLinkedList (
            ConstIterator const & from,
            ConstIterator const & to
    ) noexcept {
        for ( auto it = from; it != to; ++ it )
            this->pushBack( * it );
    }

    template < typename T >
    auto SingleLinkedList < T > :: clear () noexcept -> void {
        this->_size = 0;
        this->_pBack = nullptr;

        while ( this->_pFront != nullptr ) {
            auto p = this->_pFront;
            this->_pFront = this->_pFront->next();
            Memory :: instance().destroy ( p->data() );
            Memory :: instance().destroy ( p );
        }
    }

    template < typename T >
    auto SingleLinkedList < T > :: makeUnique() noexcept -> void {
        SingleLinkedList newList;

        for ( auto const & e : * this )
            if ( ! newList.contains(e) )
                newList.pushBack (e);

        * this = newList;
    }

    template < typename T >
    auto SingleLinkedList < T > :: operator = ( Collection < T > const & collection ) noexcept -> SingleLinkedList & {
        if ( this == & collection )
            return * this;

        this->clear();

        collection.forEach([this](T const & e){
            this->pushBack(e);
        });

        return * this;
    }

    template < typename T >
    auto SingleLinkedList < T > ::allocFrontGetPtr() noexcept -> ElementPtrRef {
        auto p = Memory :: instance ().create < Node > ();
        p->data() = nullptr;
        p->next() = this->_pFront;

        this->_pFront = p;

        ++ this->_size;
        if ( this->size() == 1 )
            this->_pBack = this->_pFront;

        return this->_pFront->data();
    }

    template < typename T >
    auto SingleLinkedList < T > ::allocBackGetPtr() noexcept -> ElementPtrRef {
        if ( this->empty() ) return this->allocFrontGetPtr();

        this->_pBack->next() = Memory :: instance().create < Node > ();
        this->_pBack->next()->data() = nullptr;
        this->_pBack->next()->next() = nullptr;

        this->_pBack = this->_pBack->_pNext;
        ++ this->_size;

        return this->_pBack->data();
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
    auto SingleLinkedList < T > :: pAt (Index index) noexcept(false) -> ElementPtr {
        if ( this->size() == 0 )
            throw OutOfBoundsException(index, 0);

        if ( index < 0 )
            index += ( (-index) / this->size() + 1 ) * this->size();
        if ( index >= static_cast<Index>(this->size()) )
            index = index % this->size();

        auto current = 0;
        for ( auto & e : (*this) ) {
            if ( current == index )
                return & e;
            current ++;
        }

        return nullptr;
    }

    template < typename T >
    auto SingleLinkedList < T > :: pAt (Index index) const noexcept(false) -> ElementCPtr {
        if ( this->size() == 0 )
            throw OutOfBoundsException(index, 0);

        if ( index < 0 )
            index += ( (-index) / this->size() + 1 ) * this->size();
        if ( index >= static_cast<Index>(this->size()) )
            index = index % this->size();

        auto current = 0;
        for ( auto & e : (*this) ) {
            if ( current == index )
                return & e;
            current ++;
        }

        return nullptr;
    }

}

__CDS_RegisterParseTypeTemplateT(SingleLinkedList)

#endif //CDS_SINGLELINKEDLIST_HPP
