//
// Created by loghin on 08.11.2021.
//

#ifndef CDS_HASHSET_HPP
#define CDS_HASHSET_HPP

#include <CDS/Set>
#include <CDS/Memory>

namespace cds {

    template < typename C >
    class Sequence;

    template < typename T, typename H = utility :: LowCollisionDefaultHashFunction < T > > __CDS_Requires(
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) class HashSet : public Set < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)

    public:
        using ElementType                     = typename Collection < T > :: ElementType;

    private:
        using ElementRef                      = typename Collection < T > :: ElementRef;
        using ElementCRef                     = typename Collection < T > :: ElementCRef;
        using ElementMRef   __CDS_MaybeUnused = typename Collection < T > :: ElementMRef;
        using ElementPtr    __CDS_MaybeUnused = typename Collection < T > :: ElementPtr;
        using ElementPtrRef                   = typename Collection < T > :: ElementPtrRef;
        using ElementCPtr   __CDS_MaybeUnused = typename Collection < T > :: ElementCPtr;
        using InitializerList                 = typename Collection < T > :: InitializerList;

    public:
        using Iterator                        = typename Collection < T > :: Iterator;
        using ConstIterator                   = typename Collection < T > :: ConstIterator;

        using ReverseIterator                 = typename Collection < T > :: ReverseIterator;
        using ConstReverseIterator            = typename Collection < T > :: ConstReverseIterator;

    private:
        using DelegateIterator                = typename Collection < T > :: DelegateIterator;
        using DelegateConstIterator           = typename Collection < T > :: DelegateConstIterator;

    private:

        struct Node {
            T       * pData;
            Node    * pNext;
        };

        Node ** _listArray { nullptr };
        Size    _size {0u};
        H       _hasher;

    public:
        __CDS_NoDiscard constexpr auto size () const noexcept -> Size final {
            return this->_size;
        }

        __CDS_OptimalInline HashSet () noexcept {
            this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)
        }

        __CDS_OptimalInline HashSet ( HashSet && set ) noexcept:
                _listArray ( exchange ( set._listArray, nullptr ) ),
                _size ( exchange ( set._size, 0 ) ),
                _hasher ( set._hasher ) {

        }

#if __JETBRAINS_IDE__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#endif

        auto clear () noexcept -> void final {
            for ( Index i = 0; i < this->_hasher.getBoundary(); ++ i ) {
                while ( this->_listArray[i] != nullptr ) {
                    auto * pHead = this->_listArray[i];
                    this->_listArray[i] = this->_listArray[i]->pNext;
                    Memory :: instance().destroy (pHead );
                }
            }

            this->_size = 0;
        }

#if __JETBRAINS_IDE__
#pragma clang diagnostic pop
#endif

        __CDS_OptimalInline ~HashSet () noexcept override {
            if ( this->_listArray != nullptr ) {
                this-> HashSet :: clear();
                Memory :: instance().destroyArray ( this->_listArray );
            }
        }

        auto allocInsertGetPtr ( ElementCRef element ) noexcept -> ElementPtrRef final {
            auto hash = this->_hasher(element);

            for (auto pHead = this->_listArray[hash]; pHead != nullptr; pHead = pHead->pNext ) { // NOLINT(clion-misra-cpp2008-6-5-2,clion-misra-cpp2008-6-5-4)
                if ( Type < ElementType > :: compare (* pHead->pData, element ) ) {
                    return pHead->pData;
                }
            }

            auto pNode = Memory :: instance().create < Node > ();
            pNode->pData = nullptr; pNode->pNext = this->_listArray[hash];
            this->_listArray[hash] = pNode;

            ++ this->_size;

            return this->_listArray[hash]->pData;
        }

        auto contains ( ElementCRef element ) const noexcept -> bool final {
            for (auto pHead = this->_listArray[this->_hasher(element)]; pHead != nullptr; pHead = pHead->pNext ) { // NOLINT(clion-misra-cpp2008-6-5-2,clion-misra-cpp2008-6-5-4)
                if ( Type < ElementType > :: compare (* pHead->pData, element ) ) {
                    return true;
                }
            }

            return false;
        }

        auto remove ( ElementCRef element ) noexcept -> bool final {
            auto hash = this->_hasher(element);

            if ( this->_listArray[hash] == nullptr ) {
                return false;
            }

            if ( Type < ElementType > :: compare (element, * this->_listArray[hash]->pData ) ) {
                auto pNode = this->_listArray[hash];
                this->_listArray[hash] = this->_listArray[hash]->pNext;

                -- this->_size;
                Memory :: instance().destroy (pNode->pData );
                Memory :: instance().destroy (pNode );
                return true;
            }

            if ( this->_listArray[hash]->pNext == nullptr ) {
                return false;
            }

            Node * previous = this->_listArray[hash];
            Node * current = previous->pNext;

            while ( current != nullptr ) {
                if ( Type < ElementType > :: compare (element, * current->pData ) ) {
                    previous->pNext = current->pNext;

                    Memory :: instance().destroy ( current->pData );
                    Memory :: instance().destroy ( current );
                    -- this->_size;

                    return true;
                }

                previous = current;
                current = current->pNext;
            }

            return false;
        }

        auto operator == ( HashSet const & set ) const noexcept -> bool {
            if ( this == & set ) {
                return true;
            }

            for (auto aIt = this->begin(), bIt = set.begin(), aEnd = this->end(), bEnd = set.end(); aIt != aEnd && bIt != bEnd; ++ aIt, ++ bIt ) { // NOLINT(clion-misra-cpp2008-6-5-1,clion-misra-cpp2008-8-0-1,clion-misra-cpp2008-5-18-1)
                if ( ! Type < ElementType > :: compare (* aIt, * bIt ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_OptimalInline auto operator != ( HashSet const & set ) const noexcept -> bool {
            return ! this->operator == ( set ); // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & object ) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < HashSet < T, H > const * > ( & object );
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator == ( * pObject );
        }

    private:
        class HashSetDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < Node > _pNode {nullptr};
            Node ** _listArray {nullptr};
            Index _currentList {0};
            H _hasher;

            auto skipEmpty () noexcept -> void {
                do {
                    ++ this->_currentList;
                } while (
                        this->_currentList < this->_hasher.getBoundary() &&
                        this->_listArray[this->_currentList] == nullptr
                        );

                if ( this->_currentList < this->_hasher.getBoundary() ) {
                    this->_pNode = this->_listArray[this->_currentList];
                } else {
                    this->_pNode = nullptr;
                }
            }

        public:
            constexpr explicit HashSetDelegateIterator ( Node ** listArray ) noexcept :
                    DelegateIterator (),
                    _listArray ( listArray ) {

                if ( this->_listArray != nullptr ) {
                    this->skipEmpty();
                }
            }

            constexpr HashSetDelegateIterator ( HashSetDelegateIterator const & ) noexcept = default;
            constexpr HashSetDelegateIterator ( HashSetDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashSetDelegateIterator () noexcept override = default;

            auto next () noexcept -> HashSetDelegateIterator & override {
                if ( this->_currentList >= this->_hasher.getBoundary() ) {
                    return * this;
                }

                this->_pNode = this->_pNode->pNext;
                if ( this->_pNode == nullptr ) {
                    this->skipEmpty();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pNode->pData;
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pIterator->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashSetDelegateIterator * override {
                return Memory :: instance().create < HashSetDelegateIterator > ( * this );
            }
        };

        class HashSetDelegateConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < Node const > _pNode {nullptr};
            Node ** _listArray {nullptr};
            Index _currentList {0};
            H _hasher;

            auto skipEmpty () noexcept -> void {
                do {
                    ++ this->_currentList;
                } while (
                        this->_currentList < this->_hasher.getBoundary() &&
                        this->_listArray[this->_currentList] == nullptr
                );

                if ( this->_currentList < this->_hasher.getBoundary() ) {
                    this->_pNode = this->_listArray[this->_currentList];
                } else {
                    this->_pNode = nullptr;
                }
            }

        public:
            constexpr explicit HashSetDelegateConstIterator ( Node ** listArray ) noexcept :
                    DelegateConstIterator (),
                    _listArray ( listArray ) {

                if ( this->_listArray != nullptr ) {
                    this->skipEmpty();
                }
            }

            constexpr HashSetDelegateConstIterator ( HashSetDelegateConstIterator const & ) noexcept = default;
            constexpr HashSetDelegateConstIterator ( HashSetDelegateConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashSetDelegateConstIterator () noexcept override = default;

            auto next () noexcept -> HashSetDelegateConstIterator & override {
                if ( this->_currentList >= this->_hasher.getBoundary() ) {
                    return * this;
                }

                this->_pNode = this->_pNode->pNext;
                if ( this->_pNode == nullptr ) {
                    this->skipEmpty();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pNode->pData;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pIterator->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashSetDelegateConstIterator * override {
                return Memory :: instance().create < HashSetDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateIterator > ( this->_listArray );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateIterator > ( this->_listArray );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateIterator > ( nullptr );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateConstIterator > ( this->_listArray );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateConstIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateConstIterator > ( this->_listArray );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashSetDelegateConstIterator > ( nullptr );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

    public:
        auto operator = ( HashSet const & set __CDS_MaybeUnused ) noexcept -> HashSet & {
            if ( this == & set ) {
                return * this;
            }

            this->clear();
            for ( auto const & element __CDS_MaybeUnused : set ) {
                this->insert(element);
            }

            return * this;
        }

        auto operator = ( HashSet && set ) noexcept -> HashSet & {
            if ( this == & set ) {
                return * this;
            }

            this->clear();

            this->_listArray = exchange ( set._listArray, nullptr );
            this->_size = exchange ( set._size, 0 );

            return * this;
        }

        auto operator = ( Collection < T > const & obj __CDS_MaybeUnused ) noexcept -> HashSet & {
            if ( this == & obj ) {
                return *this;
            }

            this->clear();
            for ( auto const & element __CDS_MaybeUnused : obj ) {
                this->insert(element);
            }

            return * this;
        }

        auto sequence () const && noexcept -> Sequence < HashSet const >;
        auto sequence () && noexcept -> Sequence < HashSet >;
        auto sequence () const & noexcept -> Sequence < HashSet const >;
        auto sequence () & noexcept -> Sequence < HashSet >;

        __CDS_OptimalInline HashSet ( HashSet const & set __CDS_MaybeUnused ) noexcept {
            this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)

            for ( auto const & element __CDS_MaybeUnused : set ) {
                this->insert(element);
            }
        }

        __CDS_OptimalInline HashSet ( InitializerList initializerList __CDS_MaybeUnused ) noexcept { // NOLINT(google-explicit-constructor)
             this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)

            for ( auto const & element __CDS_MaybeUnused : initializerList ) {
                this->insert(element);
            }
        }

        __CDS_OptionalInline explicit HashSet (
                Iterator from,
                Iterator until
        ) noexcept :
                Set <T> () {
            this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)

            for (auto it = from; it != until; ++ it ) {
                this->insert ( * it );
            }
        }

        __CDS_OptionalInline explicit HashSet (
                ConstIterator from,
                ConstIterator until
        ) noexcept :
                Set <T> () {
            this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)

            for (auto it = from; it != until; ++ it ) {
                this->insert ( * it );
            }
        }

        __CDS_OptionalInline explicit HashSet (
                Collection < T > const & collection
        ) noexcept :
                Set <T> () {
            this->_listArray = Memory :: instance().createArray < Node * > ( this->_hasher.getBoundary() );
            (void) std::memset ( this->_listArray, 0, this->_hasher.getBoundary() * sizeof ( Node * ) ); // NOLINT(bugprone-sizeof-expression)

            for (auto it = collection.begin(); it != collection.end(); ++ it ) {
                this->insert ( * it );
            }
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> HashSet < T, H > * override {
            return Memory :: instance () .create < HashSet < T, H > > ();
        }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<typename T, typename H> __CDS_Requires(
                UniqueIdentifiable < T > &&
                HashCalculatorHasBoundaryFunction < H >
        ) struct TypeParseTraits<HashSet<T, H>> {
            constexpr static StringLiteral name = "HashSet";
        };

    }
}

#if defined(CDS_SEQUENCE_HPP) && !defined(CDS_HASHSET_SEQUENCE)
#define CDS_HASHSET_SEQUENCE

namespace cds {

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () const & noexcept -> Sequence < HashSet const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () & noexcept -> Sequence < HashSet > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () const && noexcept -> Sequence < HashSet const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () && noexcept -> Sequence < HashSet > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

}

#endif

#endif //CDS_HASHSET_HPP
