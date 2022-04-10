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
    ) class HashMap : public Map<K, V> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
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

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return
                        this->_pMap == pIterator->_pMap &&
                        this->_bucketIndex == pIterator->_bucketIndex &&
                        this->_bucketIterator == pIterator->_bucketIterator;
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

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return
                        this->_pMap == pIterator->_pMap &&
                        this->_bucketIndex == pIterator->_bucketIndex &&
                        this->_bucketIterator == pIterator->_bucketIterator;
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

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return
                        this->_pMap == pIterator->_pMap &&
                        this->_bucketIndex == pIterator->_bucketIndex &&
                        this->_bucketIterator == pIterator->_bucketIterator;
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

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pIterator = reinterpret_cast < decltype ( this ) > ( & iterator );

                return
                        this->_pMap == pIterator->_pMap &&
                        this->_bucketIndex == pIterator->_bucketIndex &&
                        this->_bucketIterator == pIterator->_bucketIterator;
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
        auto operator == (HashMap const & map) const noexcept -> bool {
            if ( this == & map ) {
                return true;
            }

            if (this->size() != map.size() ) {
                return false;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                        aIt = this->begin(), aEnd = this->end(),
                        bIt = map.begin(), bEnd = map.end();
                    aIt != aEnd && bIt != bEnd;
                    ++ aIt, ++ bIt // NOLINT(clion-misra-cpp2008-5-18-1)
            ) {
                if ( ! Type < Entry > :: compare (* aIt, * bIt ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_NoDiscard auto equals (Object const & object) const noexcept -> bool final {
            if (& object == this ) {
                return true;
            }

            auto pMap = dynamic_cast < HashMap const * > ( & object );
            if (pMap == nullptr ) {
                return false;
            }

            return this->operator==(*pMap);
        }

    public:
        __CDS_NoDiscard auto copy () const noexcept -> HashMap < K, V, H > * override {
            return Memory :: instance () .create < HashMap < K, V, H > > ( * this );
        }

        __CDS_OptimalInline auto getHashCalculator () const noexcept -> H const & {
            return this->hashCalculator;
        }

        HashMap () noexcept :
                pBuckets(Memory::instance().createArray < HashBucket > (hashCalculator.getBoundary()) ) {

        }

        HashMap (HashMap const & map) noexcept :
                pBuckets(Memory::instance().createArray < HashBucket > (map.getHashCalculator().getBoundary()) ){

            this->hashCalculator = map.hashCalculator;
            for (Index i = 0; i < map.getHashCalculator().getBoundary(); i++ ) {
                this->pBuckets[i] = map.pBuckets[i];
            }
        }

        __CDS_OptimalInline HashMap ( HashMap && hashMap ) noexcept :
                hashCalculator ( std :: move ( hashMap.hashCalculator ) ),
                pBuckets ( exchange ( hashMap.pBuckets, Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary()) ) ) {

        }

        template < class OH > __CDS_Requires ( HashCalculatorHasBoundaryFunction <OH> )
        explicit HashMap (HashMap<K, V, OH> const & map __CDS_MaybeUnused ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            this->hashCalculator = map.hashCalculator;
            for ( auto & element __CDS_MaybeUnused : map.entries() ) {
                (void) this->insert (element );
            }
        }

        __CDS_OptionalInline HashMap ( InitializerList list __CDS_MaybeUnused ) noexcept : // NOLINT(google-explicit-constructor)
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for ( auto & element __CDS_MaybeUnused : list ) {
                (void) this->insert(element );
            }
        }

        explicit HashMap (
                Iterator from,
                Iterator until
        ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for (auto it = from; it != until; ++ it ) {
                (void) this->insert( * it );
            }
        }

        explicit HashMap (
                ConstIterator from,
                ConstIterator until
        ) noexcept :
                pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

            for (auto it = from; it != until; ++ it ) {
                (void) this->insert( * it );
            }
        }

        ~HashMap () noexcept override {
            Memory :: instance().destroyArray ( this->pBuckets );
        }

        __CDS_OptionalInline auto keys () const noexcept -> DoubleLinkedList < Reference < Key const > > final {
            DoubleLinkedList < Reference < Key const > > keys;
            for ( auto & element __CDS_MaybeUnused : ( *this ) ) {
                (void) keys.pushBack ( Reference < Key const > (element.getFirst() ) );
            }

            return keys;
        }

        __CDS_OptionalInline auto values () noexcept -> DoubleLinkedList < Reference < Value > > override {
            DoubleLinkedList < Reference < Value > > values;
            for ( auto & element __CDS_MaybeUnused : (*this) ) {
                values.pushBack (element.getSecond() );
            }

            return values;
        }

        __CDS_OptionalInline auto values () const noexcept -> DoubleLinkedList < Reference < Value const > > final {
            DoubleLinkedList < Reference < Value const > > values;
            for ( auto & element __CDS_MaybeUnused : (*this) ) {
                values.pushBack (element.getSecond() );
            }

            return values;
        }

        __CDS_OptionalInline auto entries () noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value > > > final {
            DoubleLinkedList < Pair < Reference < Key const >, Reference < Value > > > entries;
            for ( auto & element __CDS_MaybeUnused : (*this) ) {
                entries.pushBack({{element.getFirst()}, {element.getSecond()} });
            }

            return entries;
        }

        __CDS_OptionalInline auto entries () const noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value const > > > final {
            DoubleLinkedList < Pair < Reference < Key const >, Reference < Value const > > > entries;
            for ( auto & element __CDS_MaybeUnused : (*this) ) {
                entries.pushBack({{element.getFirst()}, {element.getSecond()} });
            }

            return entries;
        }

        __CDS_OptionalInline auto find ( KeyConstReference key __CDS_MaybeUnused ) const noexcept -> Optional < Reference < Value const > > final {
            for ( auto & element __CDS_MaybeUnused : this->pBuckets[hashCalculator(key)] ) {
                if ( Type < K > :: compare (element.getFirst(), key ) ) {
                    return {element.getSecond() };
                }
            }

            return {};
        }

        __CDS_OptionalInline auto find ( KeyConstReference key __CDS_MaybeUnused ) noexcept -> Optional < Reference < Value > > final {
            for ( auto & element __CDS_MaybeUnused : this->pBuckets[hashCalculator(key)] ) {
                if ( Type < K > :: compare (element.getFirst(), key ) ) {
                    return {element.getSecond() };
                }
            }

            return {};
        }

        auto get ( KeyConstReference key __CDS_MaybeUnused ) noexcept -> ValueReference final {
            auto & bucket __CDS_MaybeUnused = this->pBuckets[hashCalculator(key)];

            for ( auto & element __CDS_MaybeUnused : bucket ) {
                if ( Type < K > :: compare (element.getFirst(), key ) ) {
                    return element.getSecond();
                }
            }

            bucket.pushBack (Pair<Key, Value>{key, Value() } );
            return bucket.back().getSecond();
        }

        auto get ( KeyConstReference key __CDS_MaybeUnused ) const noexcept (false) -> ValueConstReference final {
            auto & bucket __CDS_MaybeUnused = this->pBuckets[hashCalculator(key)];

            for ( auto & element __CDS_MaybeUnused : bucket ) {
                if ( Type < K > :: compare (element.getFirst(), key ) ) {
                    return element.getSecond();
                }
            }

            throw KeyException(key );
        }

        auto getOr (KeyConstReference key __CDS_MaybeUnused, ValueConstReference defVal __CDS_MaybeUnused ) const noexcept -> ValueConstReference final {
            auto & bucket __CDS_MaybeUnused = this->pBuckets[hashCalculator(key)];

            for ( auto & element __CDS_MaybeUnused : bucket ) {
                if ( Type < K > :: compare (element.getFirst(), key ) ) {
                    return element.getSecond();
                }
            }

            return defVal;
        }

        auto containsKey ( KeyConstReference key __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference element __CDS_MaybeUnused : this->pBuckets[hashCalculator(key)] ) {
                if ( Type < K > :: compare (element.first(), key ) ) {
                    return true;
                }
            }

            return false;
        }

        auto containsValue ( ValueConstReference value __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference element __CDS_MaybeUnused : (*this) ) {
                if ( Type < V > :: compare (element.getSecond(), value ) ) {
                    return true;
                }
            }

            return false;
        }

        auto contains ( EntryConstReference entry __CDS_MaybeUnused ) const noexcept -> bool final {
            for ( EntryConstReference element __CDS_MaybeUnused : this->pBuckets[hashCalculator(entry.first())] ) {
                if (
                        Type < K > :: compare (element.first(), entry.first() ) &&
                        Type < V > :: compare (element.second(), entry.second() )
                ) {
                    return true;
                }
            }

            return false;
        }

        auto remove ( KeyConstReference key __CDS_MaybeUnused ) noexcept -> bool final {
            auto & bucket __CDS_MaybeUnused = this->pBuckets [ this->hashCalculator(key) ];

            for ( auto & element __CDS_MaybeUnused : bucket ) {
                if ( Type < Key > :: compare (element.first(), key ) ) {
                    return bucket.removeFirst (element );
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

        __CDS_OptionalInline auto operator = ( HashMap const & map __CDS_MaybeUnused ) noexcept -> HashMap & {
            if ( this == & map ) {
                return * this;
            }

            this->clear();
            for ( auto & element __CDS_MaybeUnused : map ) {
                (void) this->insert(element);
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
            for ( auto & element __CDS_MaybeUnused : (*this) ) {
    #if !defined(CDS_GLM)
                Type < V > :: streamPrint (Type < K > :: streamPrint (oss, element.getFirst() ) << " : ", element.getSecond() ) << ", ";
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
            auto asString = oss.str();
            return {asString.substr(0u, asString.length() - 2u).append(" }")};
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
