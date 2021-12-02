//
// Created by loghin on 25.01.2021.
//
#ifndef CDS_HASHMAP_HPP
#define CDS_HASHMAP_HPP

#include <CDS/Map>
#include <sstream>
#include <cstring>

namespace cds {

    template <class K, class V, class H> __CDS_Requires (
            UniqueIdentifiable< K > &&
            HashCalculatorHasBoundaryFunction< H >
    ) class HashMap : public Map<K, V> {
    private:
        __CDS_NoUniqueAddress H hashCalculator;

    public:
        using Key                                       = typename Map<K, V>::Key;
        using KeyReference            __CDS_MaybeUnused = typename Map<K, V>::KeyReference;
        using KeyConstReference                         = typename Map<K, V>::KeyConstReference;
        using KeyMoveReference        __CDS_MaybeUnused = typename Map<K, V>::KeyMoveReference;

        using Value                                     = typename Map<K, V>::Value;
        using ValueReference                            = typename Map<K, V>::ValueReference;
        using ValueConstReference                       = typename Map<K, V>::ValueConstReference;
        using ValueMoveReference      __CDS_MaybeUnused = typename Map<K, V>::ValueMoveReference;

        using Entry                                     = typename Map<K, V>::Entry;
        using EntryReference                            = typename Map<K, V>::EntryReference;
        using EntryConstReference                       = typename Map<K, V>::EntryConstReference;
        using EntryMoveReference      __CDS_MaybeUnused = typename Map<K, V>::EntryMoveReference;
        using EntryPointer            __CDS_MaybeUnused = typename Map<K, V>::EntryPointer;
        using EntryPointerReference                     = typename Map<K, V>::EntryPointerReference ;

        using EntryReferenceList      __CDS_MaybeUnused = typename Map<K, V>::EntryReferenceList;
        using EntryConstReferenceList __CDS_MaybeUnused = typename Map<K, V>::EntryConstReferenceList;

        using InitializerList                           = typename Map<K, V>::InitializerList;

        using Iterator                                  = typename Map<K, V>::Iterator;
        using ConstIterator                             = typename Map<K, V>::ConstIterator;
        using ReverseIterator                           = typename Map<K, V>::ReverseIterator;
        using ConstReverseIterator                      = typename Map<K, V>::ConstReverseIterator;

        using DelegateIterator                          = typename Map<K, V>::DelegateIterator;
        using DelegateConstIterator                     = typename Map<K, V>::DelegateConstIterator;

    private:
        using HashBucket                                = DoubleLinkedList < Entry >;


        HashBucket * pBuckets {nullptr};

        class HashMapDelegateForwardIterator : public DelegateIterator {
        private:
            ForeignPointer < HashMap >      _pMap;
            Index                           _bucketIndex;
            typename HashBucket :: Iterator _bucketIterator;

            __CDS_OptionalInline auto skipEmptyBuckets () noexcept -> void {
                while (
                        this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() &&
                        this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
                ) {
                    ++ this->_bucketIndex;
                }

                if ( this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() ) {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].begin();
                } else {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_pMap->hashCalculator.getBoundary() - 1 ].end();
                }
            }

        public:
            __CDS_OptionalInline explicit HashMapDelegateForwardIterator ( HashMap * pMap, bool begin ) noexcept :
                    DelegateIterator (),
                    _pMap ( pMap ),
                    _bucketIndex (begin ? 0 : this->_pMap->hashCalculator.getBoundary()) {

                this->skipEmptyBuckets();
            }

            constexpr HashMapDelegateForwardIterator ( HashMapDelegateForwardIterator const & ) noexcept = default;
            constexpr HashMapDelegateForwardIterator ( HashMapDelegateForwardIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateForwardIterator () noexcept override = default;

            __CDS_OptionalInline auto next () noexcept -> HashMapDelegateForwardIterator & override {
                if ( this->_bucketIndex >= this->_pMap->hashCalculator.getBoundary() ) {
                    return * this;
                }

                ++ this->_bucketIterator;

                if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].end() ) {
                    ++ this->_bucketIndex;
                    this->skipEmptyBuckets();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryReference override {
                return * this->_bucketIterator;
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) {
                    return true;
                }

                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return
                        this->_pMap == p->_pMap &&
                        this->_bucketIndex == p->_bucketIndex &&
                        this->_bucketIterator == p->_bucketIterator;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashMapDelegateForwardIterator * override {
                return Memory :: instance ().create < HashMapDelegateForwardIterator > ( * this );
            }
        };

        class HashMapDelegateForwardConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < HashMap const >        _pMap;
            Index                                   _bucketIndex;
            typename HashBucket :: ConstIterator    _bucketIterator;

            __CDS_OptionalInline auto skipEmptyBuckets () noexcept -> void {
                while (
                        this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() &&
                        this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
                ) {
                    ++ this->_bucketIndex;
                }

                if ( this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() ) {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].cbegin();
                } else {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_pMap->hashCalculator.getBoundary() - 1 ].cend();
                }
            }

        public:
            __CDS_OptionalInline explicit HashMapDelegateForwardConstIterator ( HashMap const * pMap, bool begin ) noexcept :
                    DelegateConstIterator (),
                    _pMap ( pMap ),
                    _bucketIndex (begin ? 0 : this->_pMap->hashCalculator.getBoundary()) {

                this->skipEmptyBuckets();
            }

            constexpr HashMapDelegateForwardConstIterator ( HashMapDelegateForwardConstIterator const & ) noexcept = default;
            constexpr HashMapDelegateForwardConstIterator ( HashMapDelegateForwardConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateForwardConstIterator () noexcept override = default;

            __CDS_OptionalInline auto next () noexcept -> HashMapDelegateForwardConstIterator & override {
                if ( this->_bucketIndex >= this->_pMap->hashCalculator.getBoundary() ) {
                    return * this;
                }

                ++ this->_bucketIterator;

                if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].cend() ) {
                    ++ this->_bucketIndex;
                    this->skipEmptyBuckets();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryConstReference override {
                return * this->_bucketIterator;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) {
                    return true;
                }

                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return
                        this->_pMap == p->_pMap &&
                        this->_bucketIndex == p->_bucketIndex &&
                        this->_bucketIterator == p->_bucketIterator;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashMapDelegateForwardConstIterator * override {
                return Memory :: instance ().create < HashMapDelegateForwardConstIterator > ( * this );
            }
        };

        class HashMapDelegateBackwardIterator : public DelegateIterator {
        private:
            ForeignPointer < HashMap >              _pMap;
            Index                                   _bucketIndex;
            typename HashBucket :: ReverseIterator  _bucketIterator;

            __CDS_OptionalInline auto skipEmptyBuckets () noexcept -> void {
                while (
                        this->_bucketIndex > -1 &&
                        this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
                ) {
                    -- this->_bucketIndex;
                }

                if ( this->_bucketIndex > - 1 ) {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].rbegin();
                } else {
                    this->_bucketIterator = this->_pMap->pBuckets[ 0 ].rend();
                }
            }

        public:
            __CDS_OptimalInline explicit HashMapDelegateBackwardIterator ( HashMap * pMap, bool begin ) noexcept :
                    DelegateIterator (),
                    _pMap ( pMap ),
                    _bucketIndex ( begin ? this->_pMap->hashCalculator.getBoundary() - 1 : -1 ) {

                this->skipEmptyBuckets();
            }

            constexpr HashMapDelegateBackwardIterator ( HashMapDelegateBackwardIterator const & ) noexcept = default;
            constexpr HashMapDelegateBackwardIterator ( HashMapDelegateBackwardIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateBackwardIterator () noexcept override = default;

            __CDS_OptionalInline auto next () noexcept -> HashMapDelegateBackwardIterator & override {
                if ( this->_bucketIndex < 0 ) {
                    return * this;
                }

                ++ this->_bucketIterator;

                if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].rend() ) {
                    -- this->_bucketIndex;
                    this->skipEmptyBuckets();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryReference override {
                return * this->_bucketIterator;
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) {
                    return true;
                }

                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return
                        this->_pMap == p->_pMap &&
                        this->_bucketIndex == p->_bucketIndex &&
                        this->_bucketIterator == p->_bucketIterator;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashMapDelegateBackwardIterator * override {
                return Memory :: instance ().create < HashMapDelegateBackwardIterator > ( * this );
            }
        };

        class HashMapDelegateBackwardConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < HashMap const >            _pMap;
            Index                                       _bucketIndex;
            typename HashBucket :: ConstReverseIterator _bucketIterator;

            __CDS_OptionalInline auto skipEmptyBuckets () noexcept -> void {
                while (
                        this->_bucketIndex > -1 &&
                        this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
                ) {
                    -- this->_bucketIndex;
                }

                if ( this->_bucketIndex > - 1 ) {
                    this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].crbegin();
                } else {
                    this->_bucketIterator = this->_pMap->pBuckets[ 0 ].crend();
                }
            }

        public:
            __CDS_OptionalInline explicit HashMapDelegateBackwardConstIterator ( HashMap const * pMap, bool begin ) noexcept :
                    DelegateConstIterator (),
                    _pMap ( pMap ),
                    _bucketIndex ( begin ? this->_pMap->hashCalculator.getBoundary() - 1 : -1 ) {

                this->skipEmptyBuckets();
            }

            constexpr HashMapDelegateBackwardConstIterator ( HashMapDelegateBackwardConstIterator const & ) noexcept = default;
            constexpr HashMapDelegateBackwardConstIterator ( HashMapDelegateBackwardConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateBackwardConstIterator () noexcept override = default;

            __CDS_OptionalInline auto next () noexcept -> HashMapDelegateBackwardConstIterator & override {
                if ( this->_bucketIndex < 0 ) {
                    return * this;
                }

                ++ this->_bucketIterator;

                if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].crend() ) {
                    -- this->_bucketIndex;
                    this->skipEmptyBuckets();
                }

                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryConstReference override {
                return * this->_bucketIterator;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) {
                    return true;
                }

                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return
                        this->_pMap == p->_pMap &&
                        this->_bucketIndex == p->_bucketIndex &&
                        this->_bucketIterator == p->_bucketIterator;
            }

            __CDS_OptimalInline auto copy () const noexcept -> HashMapDelegateBackwardConstIterator * override {
                return Memory :: instance ().create < HashMapDelegateBackwardConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < Entry > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateForwardIterator > ( this, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateForwardIterator > ( this, false );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateBackwardIterator > ( this, true );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateBackwardIterator > ( this, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateForwardConstIterator > ( this, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateForwardConstIterator > ( this, false );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateBackwardConstIterator > ( this, true );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < HashMapDelegateBackwardConstIterator > ( this, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

    public:
        auto operator == (HashMap const & o) const noexcept -> bool {
            if ( this == & o ) {
                return true;
            }

            if ( this->size() != o.size() ) {
                return false;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                        a = this->begin(), aEnd = this->end(),
                        b = o.begin(), bEnd = o.end();
                    a != aEnd && b != bEnd;
                    ++ a, ++ b // NOLINT(clion-misra-cpp2008-5-18-1)
            ) {
                if ( ! Type < Entry > :: compare ( * a, * b ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
            if ( & o == this ) {
                return true;
            }

            auto p = dynamic_cast < HashMap const * > ( & o );
            if ( p == nullptr ) {
                return false;
            }

            return this->operator==(*p);
        }

        __CDS_OptimalInline auto getHashCalculator () const noexcept -> H const & {
            return this->hashCalculator;
        }

        HashMap () noexcept :
                pBuckets(Memory::instance().createArray < HashBucket > (hashCalculator.getBoundary()) ) {

        }

        HashMap (HashMap const & hm) noexcept :
                pBuckets(Memory::instance().createArray < HashBucket > (hm.getHashCalculator().getBoundary()) ){

            this->hashCalculator = hm.hashCalculator;
            for ( Index i = 0; i < hm.getHashCalculator().getBoundary(); i++ ) {
                this->pBuckets[i] = hm.pBuckets[i];
            }
        }

        __CDS_OptimalInline HashMap ( HashMap && hashMap ) noexcept :
                hashCalculator ( std :: move ( hashMap.hashCalculator ) ),
                pBuckets ( exchange ( hashMap.pBuckets, Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary()) ) ) {

        }

        template < class OH > __CDS_Requires ( HashCalculatorHasBoundaryFunction <OH> )
        explicit HashMap (HashMap<K, V, OH> const & hm __CDS_MaybeUnused ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            this->hashCalculator = hm.hashCalculator;
            for ( auto & e __CDS_MaybeUnused : hm.entries() ) {
                (void) this->insert ( e );
            }
        }

        __CDS_OptionalInline HashMap ( InitializerList list __CDS_MaybeUnused ) noexcept : // NOLINT(google-explicit-constructor)
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for ( auto & e __CDS_MaybeUnused : list ) {
                (void) this->insert( e );
            }
        }

        explicit HashMap (
                Iterator from,
                Iterator to
        ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for ( auto it = from; it != to; ++ it ) {
                (void) this->insert( * it );
            }
        }

        explicit HashMap (
                ConstIterator from,
                ConstIterator to
        ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for ( auto it = from; it != to; ++ it ) {
                (void) this->insert( * it );
            }
        }

        ~HashMap () noexcept override {
            Memory :: instance().destroyArray ( this->pBuckets );
        }

        __CDS_OptionalInline auto keys () const noexcept -> DoubleLinkedList < Reference < Key const > > final {
            DoubleLinkedList < Reference < Key const > > keys;
            for ( auto & e __CDS_MaybeUnused : ( *this ) ) {
                (void) keys.pushBack ( Reference < Key const > ( e.getFirst() ) );
            }

            return keys;
        }

        __CDS_OptionalInline auto values () noexcept -> DoubleLinkedList < Reference < Value > > override {
            DoubleLinkedList < Reference < Value > > values;
            for ( auto & e __CDS_MaybeUnused : (*this) ) {
                values.pushBack ( e.getSecond() );
            }

            return values;
        }

        __CDS_OptionalInline auto values () const noexcept -> DoubleLinkedList < Reference < Value const > > final {
            DoubleLinkedList < Reference < Value const > > values;
            for ( auto & e __CDS_MaybeUnused : (*this) ) {
                values.pushBack ( e.getSecond() );
            }

            return values;
        }

        __CDS_OptionalInline auto entries () noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value > > > final {
            DoubleLinkedList < Pair < Reference < Key const >, Reference < Value > > > entries;
            for ( auto & e __CDS_MaybeUnused : (*this) ) {
                entries.pushBack({ {e.getFirst()}, {e.getSecond()} });
            }

            return entries;
        }

        __CDS_OptionalInline auto entries () const noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value const > > > final {
            DoubleLinkedList < Pair < Reference < Key const >, Reference < Value const > > > entries;
            for ( auto & e __CDS_MaybeUnused : (*this) ) {
                entries.pushBack({ {e.getFirst()}, {e.getSecond()} });
            }

            return entries;
        }

        __CDS_OptionalInline auto find ( KeyConstReference k __CDS_MaybeUnused ) const noexcept -> Optional < Reference < Value const > > final {
            for ( auto & e __CDS_MaybeUnused : this->pBuckets[hashCalculator(k)] ) {
                if ( Type < K > :: compare ( e.getFirst(), k ) ) {
                    return { e.getSecond() };
                }
            }

            return {};
        }

        __CDS_OptionalInline auto find ( KeyConstReference k __CDS_MaybeUnused ) noexcept -> Optional < Reference < Value > > final {
            for ( auto & e __CDS_MaybeUnused : this->pBuckets[hashCalculator(k)] ) {
                if ( Type < K > :: compare ( e.getFirst(), k ) ) {
                    return { e.getSecond() };
                }
            }

            return {};
        }

        auto get ( KeyConstReference k __CDS_MaybeUnused ) noexcept -> ValueReference final {
            auto & b __CDS_MaybeUnused = this->pBuckets[hashCalculator(k)];

            for ( auto & e __CDS_MaybeUnused : b ) {
                if ( Type < K > :: compare ( e.getFirst(), k ) ) {
                    return e.getSecond();
                }
            }

            b.pushBack ( Pair<Key, Value>{ k, Value() } );
            return b.back().getSecond();
        }

        auto get ( KeyConstReference k __CDS_MaybeUnused ) const noexcept (false) -> ValueConstReference final {
            auto & b __CDS_MaybeUnused = this->pBuckets[hashCalculator(k)];

            for ( auto & e __CDS_MaybeUnused : b ) {
                if ( Type < K > :: compare ( e.getFirst(), k ) ) {
                    return e.getSecond();
                }
            }

            throw KeyException( k );
        }

        auto getOr ( KeyConstReference k __CDS_MaybeUnused, ValueConstReference defVal __CDS_MaybeUnused ) const noexcept -> ValueConstReference final {
            auto & b __CDS_MaybeUnused = this->pBuckets[hashCalculator(k)];

            for ( auto & e __CDS_MaybeUnused : b ) {
                if ( Type < K > :: compare ( e.getFirst(), k ) ) {
                    return e.getSecond();
                }
            }

            return defVal;
        }

        auto containsKey ( KeyConstReference k __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference e __CDS_MaybeUnused : this->pBuckets[hashCalculator(k)] ) {
                if ( Type < K > :: compare ( e.first(), k ) ) {
                    return true;
                }
            }

            return false;
        }

        auto containsValue ( ValueConstReference v __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference e __CDS_MaybeUnused : (*this) ) {
                if ( Type < V > :: compare ( e.getSecond(), v ) ) {
                    return true;
                }
            }

            return false;
        }

        auto contains ( EntryConstReference entry __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference e __CDS_MaybeUnused : this->pBuckets[hashCalculator(entry.first())] ) {
                if (
                        Type < K > :: compare ( e.first(), entry.first() ) &&
                        Type < V > :: compare ( e.second(), entry.second() )
                ) {
                    return true;
                }
            }

            return false;
        }

        auto remove ( KeyConstReference k __CDS_MaybeUnused ) noexcept -> bool final {
            auto & b __CDS_MaybeUnused = this->pBuckets [ this->hashCalculator(k) ];

            for ( auto & e __CDS_MaybeUnused : b ) {
                if ( Type < Key > :: compare ( e.first(), k ) ) {
                    return b.removeFirst ( e );
                }
            }

            return false;
        }

        auto allocInsertGetPtr (EntryConstReference entry) noexcept -> EntryPointerReference override {
            auto pFront = this->pBuckets[hashCalculator(entry.first())]._pFront;
            while ( pFront != nullptr ) {
                if ( Type < K > :: compare ( pFront->data->first(), entry.first() ) ) {
                    return pFront->data;
                }

                pFront = pFront->pNext;
            }

            return this->pBuckets[hashCalculator(entry.first())].allocBackGetPtr();
        }

        __CDS_OptionalInline auto clear () noexcept -> void final {
            for ( Index i = 0; i < hashCalculator.getBoundary(); i++ ) {
                this->pBuckets[i].clear();
            }
        }

        __CDS_NoDiscard __CDS_OptionalInline auto size () const noexcept -> Size final {
            Size total = 0ull;
            for ( Index i = 0; i < hashCalculator.getBoundary(); i++ ) {
                total += this->pBuckets[i].size();
            }

            return total;
        }

        __CDS_OptionalInline auto operator = ( HashMap const & o __CDS_MaybeUnused ) noexcept -> HashMap & {
            if ( this == & o ) {
                return * this;
            }

            this->clear();
            for ( auto & e __CDS_MaybeUnused : o ) {
                (void) this->insert(e);
            }

            return * this;
        }

        __CDS_OptimalInline auto operator = ( HashMap && hashMap ) noexcept -> HashMap & {
            if ( this == & hashMap ) {
                return * this;
            }

            Memory :: instance().destroyArray ( this->pBuckets );

            this->hashCalculator = std :: move ( hashMap.hashCalculator );
            this->pBuckets = exchange ( hashMap.pBuckets, Memory :: instance().createArray < HashBucket > ( hashMap.hashCalculator.getBoundary() ) );

            return * this;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto empty() const noexcept -> bool final {
            return this->size() == 0;
        }

        __CDS_NoDiscard auto toString() const noexcept -> String override {
            if ( this->empty() ) {
                return {"{ }"};
            }

            std::stringstream oss;
            oss << "{ ";
            for ( auto & e __CDS_MaybeUnused : (*this) ) {
    #if !defined(CDS_GLM)
                Type < V > :: streamPrint ( Type < K > :: streamPrint ( oss, e.getFirst() ) << " : ", e.getSecond() ) << ", ";
    #else
                if constexpr (
                        std::is_same < glm::vec1, Value >::type::value ||
                        std::is_same < glm::vec2, Value >::type::value ||
                        std::is_same < glm::vec3, Value >::type::value ||
                        std::is_same < glm::vec4, Value >::type::value
                )
                    oss << e.getFirst () << " : " << String(e.getSecond ()) << ", ";
                else
                    oss << e.getFirst () << " : " << e.getSecond () << ", ";
    #endif
            }
            auto s = oss.str();
            return {s.substr(0u, s.length() - 2u).append(" }")};
        }

        auto sequence () const & noexcept -> Sequence < const HashMap < K, V, H > >;
        auto sequence () & noexcept -> Sequence < HashMap < K, V, H > >;
        auto sequence () const && noexcept -> Sequence < const HashMap < K, V, H > >;
        auto sequence () && noexcept -> Sequence < HashMap < K, V, H > >;
    };

}

#include <CDS/Sequence>

namespace cds {

    template <class K, class V, class H> __CDS_Requires (UniqueIdentifiable<K> && HashCalculatorHasBoundaryFunction<H> )
    auto HashMap < K, V, H >::sequence() const & noexcept -> Sequence < const HashMap < K, V, H > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class K, class V, class H> __CDS_Requires (UniqueIdentifiable<K> && HashCalculatorHasBoundaryFunction<H> )
    auto HashMap < K, V, H >::sequence() & noexcept -> Sequence < HashMap<K, V, H>> {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class K, class V, class H> __CDS_Requires (UniqueIdentifiable<K> && HashCalculatorHasBoundaryFunction<H> )
    auto HashMap < K, V, H >::sequence() const && noexcept -> Sequence < const HashMap < K, V, H > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template <class K, class V, class H> __CDS_Requires (UniqueIdentifiable<K> && HashCalculatorHasBoundaryFunction<H> )
    auto HashMap < K, V, H >::sequence() && noexcept -> Sequence < HashMap<K, V, H>> {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template < typename K, typename V >
    HashMap ( std::initializer_list < Pair < K, V > > ) -> HashMap < K, V >;

}

#endif

namespace cds {

    template < typename K, typename V, typename H >
    __CDS_Requires (UniqueIdentifiable < K > && HashCalculatorHasBoundaryFunction < H >)
    class __CDS_MaybeUnused MultiHashMap final : public Map < K, V > {

    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class K, class V, class H> __CDS_Requires (
                UniqueIdentifiable< K > &&
                HashCalculatorHasBoundaryFunction< H >
        ) struct TypeParseTraits<HashMap < K, V, H >> {
            constexpr static StringLiteral name = "HashMap";
        };

        template <class K, class V, class H> __CDS_Requires (
                UniqueIdentifiable< K > &&
                HashCalculatorHasBoundaryFunction< H >
        ) struct TypeParseTraits<MultiHashMap < K, V, H >> {
            constexpr static StringLiteral name = "MultiHashMap";
        };

    }
}

#endif //CDS_HASHMAP_HPP
