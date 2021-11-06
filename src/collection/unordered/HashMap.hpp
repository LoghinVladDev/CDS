//
// Created by loghin on 25.01.2021.
//
#ifndef CDS_HASHMAP_HPP
#define CDS_HASHMAP_HPP

#include <CDS/Map>
#include <sstream>
#include <cstring>

template <class K, class V, class H> __CDS_Requires (
        UniqueIdentifiable< K > &&
        HashCalculatorHasBoundaryFunction< H >
) class HashMap : public Map<K, V> {
public:
    __CDS_NoUniqueAddress H hashCalculator;

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
    using HashBucket                                = LinkedList < Entry >;


    HashBucket * pBuckets {nullptr};

    class HashMapDelegateForwardIterator : public DelegateIterator {
    private:
        ForeignPointer < HashMap >      _pMap;
        Index                           _bucketIndex;
        typename HashBucket :: Iterator _bucketIterator;

        auto skipEmptyBuckets () noexcept -> void {
            while (
                    this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() &&
                    this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
            )
                ++ this->_bucketIndex;

            if ( this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() )
                this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].begin();
            else
                this->_bucketIterator = this->_pMap->pBuckets[ this->_pMap->hashCalculator.getBoundary() - 1 ].end();
        }

    public:
        explicit HashMapDelegateForwardIterator ( HashMap * pMap, bool begin ) noexcept :
                DelegateIterator (),
                _pMap ( pMap ),
                _bucketIndex (begin ? 0 : this->_pMap->hashCalculator.getBoundary()) {

            this->skipEmptyBuckets();
        }

        HashMapDelegateForwardIterator ( HashMapDelegateForwardIterator const & ) noexcept = default;
        HashMapDelegateForwardIterator ( HashMapDelegateForwardIterator && ) noexcept = default;

        ~HashMapDelegateForwardIterator () noexcept override = default;

        auto next () noexcept -> HashMapDelegateForwardIterator & override {
            if ( this->_bucketIndex >= this->_pMap->hashCalculator.getBoundary() )
                return * this;

            ++ this->_bucketIterator;

            if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].end() ) {
                ++ this->_bucketIndex;
                this->skipEmptyBuckets();
            }

            return * this;
        }

        auto value () const noexcept -> EntryReference override {
            return * this->_bucketIterator;
        }

        auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = reinterpret_cast < decltype ( this ) > ( & it );

            return
                    this->_pMap == p->_pMap &&
                    this->_bucketIndex == p->_bucketIndex &&
                    this->_bucketIterator == p->_bucketIterator;
        }

        auto copy () const noexcept -> HashMapDelegateForwardIterator * override {
            return Memory :: instance ().create < HashMapDelegateForwardIterator > ( * this );
        }
    };

    class HashMapDelegateForwardConstIterator : public DelegateConstIterator {
    private:
        ForeignPointer < HashMap const >        _pMap;
        Index                                   _bucketIndex;
        typename HashBucket :: ConstIterator    _bucketIterator;

        auto skipEmptyBuckets () noexcept -> void {
            while (
                    this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() &&
                    this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
            )
                ++ this->_bucketIndex;

            if ( this->_bucketIndex < this->_pMap->hashCalculator.getBoundary() )
                this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].cbegin();
            else
                this->_bucketIterator = this->_pMap->pBuckets[ this->_pMap->hashCalculator.getBoundary() - 1 ].cend();
        }

    public:
        explicit HashMapDelegateForwardConstIterator ( HashMap const * pMap, bool begin ) noexcept :
                DelegateConstIterator (),
                _pMap ( pMap ),
                _bucketIndex (begin ? 0 : this->_pMap->hashCalculator.getBoundary()) {

            this->skipEmptyBuckets();
        }

        HashMapDelegateForwardConstIterator ( HashMapDelegateForwardConstIterator const & ) noexcept = default;
        HashMapDelegateForwardConstIterator ( HashMapDelegateForwardConstIterator && ) noexcept = default;

        ~HashMapDelegateForwardConstIterator () noexcept override = default;

        auto next () noexcept -> HashMapDelegateForwardConstIterator & override {
            if ( this->_bucketIndex >= this->_pMap->hashCalculator.getBoundary() )
                return * this;

            ++ this->_bucketIterator;

            if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].cend() ) {
                ++ this->_bucketIndex;
                this->skipEmptyBuckets();
            }

            return * this;
        }

        auto value () const noexcept -> EntryConstReference override {
            return * this->_bucketIterator;
        }

        auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = reinterpret_cast < decltype ( this ) > ( & it );

            return
                    this->_pMap == p->_pMap &&
                    this->_bucketIndex == p->_bucketIndex &&
                    this->_bucketIterator == p->_bucketIterator;
        }

        auto copy () const noexcept -> HashMapDelegateForwardConstIterator * override {
            return Memory :: instance ().create < HashMapDelegateForwardConstIterator > ( * this );
        }
    };

    class HashMapDelegateBackwardIterator : public DelegateIterator {
    private:
        ForeignPointer < HashMap >              _pMap;
        Index                                   _bucketIndex;
        typename HashBucket :: ReverseIterator  _bucketIterator;

        auto skipEmptyBuckets () noexcept -> void {
            while (
                    this->_bucketIndex > -1 &&
                    this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
            )
                -- this->_bucketIndex;

            if ( this->_bucketIndex > - 1 )
                this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].rbegin();
            else
                this->_bucketIterator = this->_pMap->pBuckets[ 0 ].rend();
        }

    public:
        explicit HashMapDelegateBackwardIterator ( HashMap * pMap, bool begin ) noexcept :
                DelegateIterator (),
                _pMap ( pMap ),
                _bucketIndex ( begin ? this->_pMap->hashCalculator.getBoundary() - 1 : -1 ) {

            this->skipEmptyBuckets();
        }

        HashMapDelegateBackwardIterator ( HashMapDelegateBackwardIterator const & ) noexcept = default;
        HashMapDelegateBackwardIterator ( HashMapDelegateBackwardIterator && ) noexcept = default;

        ~HashMapDelegateBackwardIterator () noexcept override = default;

        auto next () noexcept -> HashMapDelegateBackwardIterator & override {
            if ( this->_bucketIndex < 0 )
                return * this;

            ++ this->_bucketIterator;

            if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].rend() ) {
                -- this->_bucketIndex;
                this->skipEmptyBuckets();
            }

            return * this;
        }

        auto value () const noexcept -> EntryReference override {
            return * this->_bucketIterator;
        }

        auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = reinterpret_cast < decltype ( this ) > ( & it );

            return
                    this->_pMap == p->_pMap &&
                    this->_bucketIndex == p->_bucketIndex &&
                    this->_bucketIterator == p->_bucketIterator;
        }

        auto copy () const noexcept -> HashMapDelegateBackwardIterator * override {
            return Memory :: instance ().create < HashMapDelegateBackwardIterator > ( * this );
        }
    };

    class HashMapDelegateBackwardConstIterator : public DelegateConstIterator {
    private:
        ForeignPointer < HashMap const >            _pMap;
        Index                                       _bucketIndex;
        typename HashBucket :: ConstReverseIterator _bucketIterator;

        auto skipEmptyBuckets () noexcept -> void {
            while (
                    this->_bucketIndex > -1 &&
                    this->_pMap->pBuckets[ this->_bucketIndex ].empty ()
            )
                -- this->_bucketIndex;

            if ( this->_bucketIndex > - 1 )
                this->_bucketIterator = this->_pMap->pBuckets[ this->_bucketIndex ].crbegin();
            else
                this->_bucketIterator = this->_pMap->pBuckets[ 0 ].crend();
        }

    public:
        explicit HashMapDelegateBackwardConstIterator ( HashMap const * pMap, bool begin ) noexcept :
                DelegateConstIterator (),
                _pMap ( pMap ),
                _bucketIndex ( begin ? this->_pMap->hashCalculator.getBoundary() - 1 : -1 ) {

            this->skipEmptyBuckets();
        }

        HashMapDelegateBackwardConstIterator ( HashMapDelegateBackwardConstIterator const & ) noexcept = default;
        HashMapDelegateBackwardConstIterator ( HashMapDelegateBackwardConstIterator && ) noexcept = default;

        ~HashMapDelegateBackwardConstIterator () noexcept override = default;

        auto next () noexcept -> HashMapDelegateBackwardConstIterator & override {
            if ( this->_bucketIndex < 0 )
                return * this;

            ++ this->_bucketIterator;

            if ( this->_bucketIterator == this->_pMap->pBuckets[ this->_bucketIndex ].crend() ) {
                -- this->_bucketIndex;
                this->skipEmptyBuckets();
            }

            return * this;
        }

        auto value () const noexcept -> EntryConstReference override {
            return * this->_bucketIterator;
        }

        auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = reinterpret_cast < decltype ( this ) > ( & it );

            return
                    this->_pMap == p->_pMap &&
                    this->_bucketIndex == p->_bucketIndex &&
                    this->_bucketIterator == p->_bucketIterator;
        }

        auto copy () const noexcept -> HashMapDelegateBackwardConstIterator * override {
            return Memory :: instance ().create < HashMapDelegateBackwardConstIterator > ( * this );
        }
    };

    using DelegateIteratorRequestType = typename Collection < Entry > :: DelegateIteratorRequestType;

    auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
        switch ( requestType ) {
            case DelegateIteratorRequestType :: FORWARD_BEGIN:
                return Memory :: instance () . create < HashMapDelegateForwardIterator > ( this, true );
            case DelegateIteratorRequestType :: FORWARD_END:
                return Memory :: instance () . create < HashMapDelegateForwardIterator > ( this, false );
            case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                return Memory :: instance () . create < HashMapDelegateBackwardIterator > ( this, true );
            case DelegateIteratorRequestType :: BACKWARD_END:
                return Memory :: instance () . create < HashMapDelegateBackwardIterator > ( this, false );
        }
    }

    auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
        switch ( requestType ) {
            case DelegateIteratorRequestType :: FORWARD_BEGIN:
                return Memory :: instance () . create < HashMapDelegateForwardConstIterator > ( this, true );
            case DelegateIteratorRequestType :: FORWARD_END:
                return Memory :: instance () . create < HashMapDelegateForwardConstIterator > ( this, false );
            case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                return Memory :: instance () . create < HashMapDelegateBackwardConstIterator > ( this, true );
            case DelegateIteratorRequestType :: BACKWARD_END:
                return Memory :: instance () . create < HashMapDelegateBackwardConstIterator > ( this, false );
        }
    }

public:
    auto operator == (HashMap const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( this->size() != o.size() ) return false;

        for ( auto b = this->begin(), bOther = o.begin(); b != this->end() && bOther != o.end(); b++, bOther++ )
            if ( * b != * bOther )
                return false;

        return true;
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < HashMap const * > ( & o );
        if ( p == nullptr ) return false;

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
            pBuckets ( Utility :: exchange ( hashMap.pBuckets, Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary()) ) ) {

    }

    template < class OH > __CDS_Requires ( HashCalculatorHasBoundaryFunction <OH> )
    explicit HashMap (HashMap<K, V, OH> const & hm) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        this->hashCalculator = hm.hashCalculator;
        for ( auto & e : hm.entries() )
            this->insert ( e );
    }

    __CDS_OptionalInline HashMap ( InitializerList list ) noexcept : // NOLINT(google-explicit-constructor)
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto & e : list )
            this->insert( e );
    }

    explicit HashMap (
            Iterator from,
            Iterator to
    ) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto it = from; it != to; ++ it )
            this->insert( * it );
    }

    explicit HashMap (
            ConstIterator from,
            ConstIterator to
    ) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto it = from; it != to; ++ it )
            this->insert( * it );
    }

    ~HashMap () noexcept override {
        Memory :: instance().destroyArray ( this->pBuckets );
    }

private:
//    __CDS_OptionalInline auto beginPtr () noexcept -> Iterator * final {
//        Index i = 0;
//        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
//            i++;
//        if ( i >= hashCalculator.getBoundary() )
//            return this->endPtr();
//        return Memory::instance().create < Iterator > ( this->pBuckets[i].begin(), this->pBuckets, i, this );
//    }
//
//    __CDS_OptionalInline auto beginPtr () const noexcept -> ConstIterator * final  {
//        Index i = 0;
//        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
//            i++;
//        if ( i >= hashCalculator.getBoundary() )
//            return this->endPtr();
//        return Memory::instance().create < ConstIterator > ( this->pBuckets[i].cbegin(), this->pBuckets, i, this );
//    }
//
//    __CDS_OptimalInline auto endPtr () noexcept -> Iterator * final { return Memory :: instance().create < Iterator > ( this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
//    __CDS_OptimalInline auto endPtr () const noexcept -> ConstIterator * final { return Memory :: instance().create < ConstIterator > (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }

public:
//    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator {
//        Index i = 0;
//        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
//            i++;
//        if ( i >= hashCalculator.getBoundary() )
//            return this->end();
//        return Iterator( this->pBuckets[i].begin(), this->pBuckets, i, this );
//    }
//
//    __CDS_cpplang_ConstexprConditioned auto begin () const noexcept -> ConstIterator {
//        Index i = 0;
//        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
//            i++;
//        if ( i >= hashCalculator.getBoundary() )
//            return this->end();
//        return ConstIterator( this->pBuckets[i].cbegin(), this->pBuckets, i, this );
//    }
//
//    __CDS_cpplang_ConstexprConditioned auto cbegin () const noexcept -> ConstIterator {
//        Index i = 0;
//        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
//            i++;
//        if ( i >= hashCalculator.getBoundary() )
//            return this->cend();
//        return ConstIterator (this->pBuckets[i].cbegin(), this->pBuckets, i, this);
//    }
//
//    __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator {
//        Index i = hashCalculator.getBoundary();
//        while ( i >= 0 && this->pBuckets[i].empty() )
//            i--;
//        if ( i < 0 )
//            return this->rend();
//        return ReverseIterator(this->pBuckets[i].rbegin(), this->pBuckets, i, this);
//    }
//
//    __CDS_cpplang_ConstexprConditioned auto rbegin () const noexcept -> ConstReverseIterator {
//        Index i = hashCalculator.getBoundary();
//        while ( i >= 0 && this->pBuckets[i].empty() )
//            i--;
//        if ( i < 0 )
//            return this->rend();
//        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i, this);
//    }
//
//    __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto crbegin () const noexcept -> ConstReverseIterator {
//        Index i = hashCalculator.getBoundary();
//        while ( i >= 0 && this->pBuckets[i].empty() )
//            i--;
//        if ( i < 0 )
//            return this->crend();
//        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i, this);
//    }
//
//    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator(this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1, this); }
//    __CDS_OptimalInline auto end () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
//    __CDS_OptimalInline auto cend () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
//    __CDS_cpplang_NonConstConstexprMemberFunction auto rend () noexcept -> ReverseIterator { return ReverseIterator(this->pBuckets[0].rend(), this->pBuckets, 0, this); }
//    __CDS_OptimalInline auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }
//    __CDS_OptimalInline auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }

    __CDS_OptionalInline auto keys () const noexcept -> LinkedList < Reference < Key const > > final {
        LinkedList < Reference < Key const > > keys;
        for ( auto & e : ( *this ) )
            keys.pushBack ( Reference < Key const > ( e.getFirst() ) );
        return keys;
    }

    __CDS_OptionalInline auto values () noexcept -> LinkedList < Reference < Value > > override {
        LinkedList < Reference < Value > > values;
        for ( auto & e : (*this) )
            values.pushBack ( e.getSecond() );

        return values;
    }

    __CDS_OptionalInline auto values () const noexcept -> LinkedList < Reference < Value const > > final {
        LinkedList < Reference < Value const > > values;
        for ( auto & e : (*this) )
            values.pushBack ( e.getSecond() );

        return values;
    }

    __CDS_OptionalInline auto entries () noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value > > > final {
        LinkedList < Pair < Reference < Key const >, Reference < Value > > > entries;
        for ( auto & e : (*this) )
            entries.pushBack({ {e.getFirst()}, {e.getSecond()} });

        return entries;
    }

    __CDS_OptionalInline auto entries () const noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value const > > > final {
        LinkedList < Pair < Reference < Key const >, Reference < Value const > > > entries;
        for ( auto & e : (*this) )
            entries.pushBack({ {e.getFirst()}, {e.getSecond()} });

        return entries;
    }

    __CDS_OptionalInline auto find ( KeyConstReference k ) const noexcept -> Optional < Reference < Value const > > final {
        for ( auto & e : this->pBuckets[hashCalculator(k)] )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return { e.getSecond() };
        return {};
    }

    __CDS_OptionalInline auto find ( KeyConstReference k ) noexcept -> Optional < Reference < Value > > final {
        for ( auto & e : this->pBuckets[hashCalculator(k)] )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return { e.getSecond() };
        return {};
    }

    auto get ( KeyConstReference k ) noexcept -> ValueReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return e.getSecond();

        b.pushBack ( Pair<Key, Value>{ k, Value() } );
        return b.back().getSecond();
    }

    auto get ( KeyConstReference k ) const noexcept (false) -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return e.getSecond();

        throw KeyException( k );
    }

    auto getOr ( KeyConstReference k, ValueConstReference defVal ) const noexcept -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return e.getSecond();

        return defVal;
    }

    auto containsKey ( KeyConstReference k ) const noexcept -> bool final {
        for ( EntryConstReference e : this->pBuckets[hashCalculator(k)] )
            if ( Type < K > :: compare ( e.first(), k ) )
                return true;
        return false;
    }

    auto containsValue ( ValueConstReference v ) const noexcept -> bool final {
        for ( EntryConstReference e : (*this) )
            if ( Type < V > :: compare ( e.getSecond(), v ) )
                return true;
        return false;
    }

    auto contains ( EntryConstReference entry ) const noexcept -> bool final {
        for ( EntryConstReference e : this->pBuckets[hashCalculator(entry.first())] )
            if (
                    Type < K > :: compare ( e.first(), entry.first() ) &&
                    Type < V > :: compare ( e.second(), entry.second() )
                    )
                return true;
        return false;
    }

    auto remove ( KeyConstReference k ) noexcept -> bool final {
        auto & b = this->pBuckets [ this->hashCalculator(k) ];

        for ( auto & e : b )
            if ( Type < Key > :: compare ( e.first(), k ) )
                return b.removeFirst ( e );

        return false;
    }

    auto allocInsertGetPtr (EntryConstReference entry) noexcept -> EntryPointerReference override {
        auto pFront = this->pBuckets[hashCalculator(entry.first())]._pFront;
        while ( pFront != nullptr ) {
            if ( Type < K > :: compare ( pFront->data->first(), entry.first() ) )
                return pFront->data;

            pFront = pFront->pNext;
        }

        return this->pBuckets[hashCalculator(entry.first())].allocBackGetPtr();
    }

    __CDS_OptionalInline auto clear () noexcept -> void final {
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            this->pBuckets[i].clear();
    }

    __CDS_NoDiscard __CDS_OptionalInline auto size () const noexcept -> Size final {
        Size total = 0ull;
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            total += this->pBuckets[i].size();
        return total;
    }

    __CDS_OptionalInline auto operator = ( HashMap const & o ) noexcept -> HashMap & {
        if ( this == & o )
            return * this;

        this->clear();
        for ( auto & e : o )
            this->insert(e);

        return * this;
    }

    __CDS_OptimalInline auto operator = ( HashMap && hashMap ) noexcept -> HashMap & {
        if ( this == & hashMap ) return * this;

        Memory :: instance().destroyArray ( this->pBuckets );

        this->hashCalculator = std :: move ( hashMap.hashCalculator );
        this->pBuckets = Utility::exchange ( hashMap.pBuckets, Memory :: instance().createArray < HashBucket > ( hashMap.hashCalculator.getBoundary() ) );

        return * this;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto empty() const noexcept -> bool final {
        return this->size() == 0;
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        if ( this->empty() )
            return {"{ }"};
        std::stringstream oss;
        oss << "{ ";
        for ( auto & e : (*this) ) {
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
        return {s.substr(0, s.length() - 2).append(" }")};
    }

    auto sequence () const & noexcept -> Sequence < const HashMap < K, V, H > >;
    auto sequence () & noexcept -> Sequence < HashMap < K, V, H > >;
    auto sequence () const && noexcept -> Sequence < const HashMap < K, V, H > >;
    auto sequence () && noexcept -> Sequence < HashMap < K, V, H > >;
};

#include <CDS/Sequence>

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

#if __CDS_cpplang_CTAD_available == true

template < typename K, typename V >
HashMap ( std::initializer_list < Pair < K, V > > ) -> HashMap < K, V >;

#endif

template < typename K, typename V, typename H >
__CDS_Requires (UniqueIdentifiable < K > && HashCalculatorHasBoundaryFunction < H >)
class __CDS_MaybeUnused MultiHashMap final : public Map < K, V > {

};

namespace Utility {
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

#endif //CDS_HASHMAP_HPP
