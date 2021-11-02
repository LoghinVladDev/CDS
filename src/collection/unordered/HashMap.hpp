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

    using CollectionIterator                        = typename Map<K, V>::CollectionIterator;
    using ConstCollectionIterator                   = typename Map<K, V>::ConstCollectionIterator;
    using InitializerList                           = typename Map<K, V>::InitializerList;

private:
    using HashBucket                                = LinkedList < Entry >;
    using BucketIterator                            = typename HashBucket::Iterator;
    using BucketConstIterator                       = typename HashBucket::ConstIterator;
    using BucketReverseIterator                     = typename HashBucket::ReverseIterator;
    using BucketConstReverseIterator                = typename HashBucket::ConstReverseIterator;

    HashBucket * pBuckets {nullptr};
public:
    class IteratorBase : public CollectionIterator {
    protected:
        HashMap < K, V, H > * pMap {nullptr};
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        constexpr IteratorBase() noexcept = default;
        constexpr IteratorBase(IteratorBase const &) noexcept = default;
        constexpr IteratorBase(IteratorBase &&) noexcept = default;

        constexpr explicit IteratorBase( HashBucket * pB, Index i, HashMap < K, V, H > * pMap ) noexcept :
                CollectionIterator (pMap),
                pBuckets(pB),
                bucketIndex ( i ),
                pMap(pMap) {

        }

        __CDS_cpplang_ConstexprDestructor ~IteratorBase() noexcept override = default;

        __CDS_OptionalInline auto nextBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( ! isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex++;
            return * this;
        }

        __CDS_OptionalInline auto previousBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( ! isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex --;
            return * this;
        }

        __CDS_NoDiscard auto constexpr isOutOfRange () const noexcept -> bool {
            return bucketIndex < 0 || bucketIndex >= pMap->getHashCalculator().getBoundary();
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto copy () const noexcept -> IteratorBase * override = 0;
    };

    class ConstIteratorBase : public ConstCollectionIterator {
    protected:
        HashMap < K, V, H > const * pMap {nullptr};
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        constexpr ConstIteratorBase() noexcept = default;
        constexpr ConstIteratorBase(ConstIteratorBase const &) noexcept = default;
        constexpr ConstIteratorBase(ConstIteratorBase &&) noexcept = default;

        constexpr explicit ConstIteratorBase( HashBucket * pB, Index i, HashMap < K, V, H > const * pMap ) noexcept :
                ConstCollectionIterator(pMap),
                pBuckets(pB),
                bucketIndex ( i ),
                pMap(pMap) {

        }

        __CDS_cpplang_ConstexprDestructor ~ConstIteratorBase() noexcept override = default;

        __CDS_OptionalInline auto nextBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( ! this->isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex++;
            return * this;
        }

        __CDS_OptionalInline auto previousBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( ! this->isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex--;
            return * this;
        }

        __CDS_NoDiscard auto constexpr isOutOfRange () const noexcept -> bool {
            return bucketIndex < 0 || bucketIndex >= pMap->getHashCalculator().getBoundary();
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto copy () const noexcept -> ConstIteratorBase * override = 0;
    };

    class Iterator : public IteratorBase {
    private:
        BucketIterator it;

    public:
        constexpr Iterator() noexcept = delete;
        constexpr Iterator(Iterator const &) noexcept = default;
        constexpr Iterator(Iterator &&) noexcept = default;

        constexpr explicit Iterator ( BucketIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > * pMap ) noexcept :
                IteratorBase(pBucket, i, pMap),
                it(iter) {

        }

        __CDS_cpplang_ConstexprDestructor ~Iterator() noexcept = default;

        __CDS_OptionalInline auto next () noexcept -> Iterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].end() == it ) {
                this->nextBucket();
                if ( this->isOutOfRange() )  {
                    it = this->pBuckets[this->pMap->getHashCalculator().getBoundary() - 1].end();
                    this->bucketIndex = this->pMap->getHashCalculator().getBoundary() - 1;
                }
                else it = this->pBuckets[this->bucketIndex].begin();

                return * this;
            }
            return * this;
        }

        __CDS_cpplang_DynamicCastConstexpr auto equals ( CollectionIterator const & i ) const noexcept -> bool final {
            auto p = dynamic_cast < Iterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryReference final {
            return this->it.value();
        }

        __CDS_OptimalInline auto operator ++ () noexcept -> Iterator & final {
            return this->next();
        }

        __CDS_OptimalInline auto operator ++ (int) noexcept -> Iterator {
            auto copy = * this;
            this->next();
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Iterator * override {
            return Memory :: instance().create < Iterator > ( * this );
        }
    };

    class ConstIterator : public ConstIteratorBase {
    private:
        BucketConstIterator it;

    public:
        constexpr ConstIterator() noexcept = delete;
        constexpr ConstIterator(ConstIterator const &) noexcept = default;
        constexpr ConstIterator(ConstIterator &&) noexcept = default;

        constexpr explicit ConstIterator ( BucketConstIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > const * pMap ) noexcept :
                ConstIteratorBase(pBucket, i, pMap),
                it(iter) {

        }

        __CDS_cpplang_ConstexprDestructor ~ConstIterator() noexcept = default;

        __CDS_OptionalInline auto next () noexcept -> ConstIterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].cend() == it ) {
                this->nextBucket();
                if ( this->isOutOfRange() ) {
                    it = this->pBuckets[this->pMap->getHashCalculator().getBoundary() - 1].cend();
                    this->bucketIndex = this->pMap->getHashCalculator().getBoundary() - 1;
                }
                else it = this->pBuckets[this->bucketIndex].cbegin();

                return * this;
            }
            return * this;
        }

        __CDS_cpplang_DynamicCastConstexpr auto equals ( ConstCollectionIterator const & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryConstReference final {
            return this->it.value();
        }

        __CDS_OptimalInline auto operator ++ () noexcept -> ConstIterator & final {
            return this->next();
        }

        __CDS_OptimalInline auto operator ++ (int) noexcept -> ConstIterator {
            auto copy = * this;
            this->next();
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstIterator * override {
            return Memory :: instance().create < ConstIterator > ( * this );
        }
    };

    class ReverseIterator : public IteratorBase {
    private:
        BucketReverseIterator it;

    public:
        constexpr ReverseIterator() noexcept = default;
        constexpr ReverseIterator(ReverseIterator const &) noexcept = default;
        constexpr ReverseIterator(ReverseIterator &&) noexcept = default;

        constexpr explicit ReverseIterator ( BucketReverseIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > * pMap ) noexcept :
                IteratorBase(pBucket, i, pMap),
                it(iter) {

        }

        __CDS_cpplang_ConstexprDestructor ~ReverseIterator() noexcept = default;

        __CDS_OptionalInline auto next () noexcept -> ReverseIterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].rend() == it ) {
                this->previousBucket();
                if ( this->isOutOfRange() ) {
                    it = this->pBuckets[0].rend();
                    this->bucketIndex = 0;
                }
                else it = this->pBuckets[this->bucketIndex].rbegin();

                return * this;
            }
            return * this;
        }


        __CDS_cpplang_DynamicCastConstexpr auto equals ( CollectionIterator const & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryReference final {
            return this->it.value();
        }

        __CDS_OptimalInline auto operator ++ () noexcept -> ReverseIterator & final {
            return this->next();
        }

        __CDS_OptimalInline auto operator ++ (int) noexcept -> ReverseIterator {
            auto copy = * this;
            this->next();
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ReverseIterator * override {
            return Memory :: instance().create < ReverseIterator > ( * this );
        }
    };

    class ConstReverseIterator : public ConstIteratorBase {
    private:
        BucketConstReverseIterator it;

    public:
        constexpr ConstReverseIterator() noexcept = default;
        constexpr ConstReverseIterator(ConstReverseIterator const &) noexcept = default;
        constexpr ConstReverseIterator(ConstReverseIterator &&) noexcept = default;

        constexpr explicit ConstReverseIterator ( BucketConstReverseIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > const * pMap ) noexcept :
                ConstIteratorBase(pBucket, i, pMap),
                it(iter) {

        }

        __CDS_cpplang_ConstexprDestructor ~ConstReverseIterator() noexcept = default;

        __CDS_OptionalInline auto next () noexcept -> ReverseIterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].crend() == it ) {
                this->previousBucket();
                if ( this->isOutOfRange() ) {
                    it = this->pBuckets[0].crend();
                    this->bucketIndex = 0;
                }
                else it = this->pBuckets[this->bucketIndex].crbegin();

                return * this;
            }
            return * this;
        }

        __CDS_cpplang_DynamicCastConstexpr auto equals ( ConstCollectionIterator const & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryConstReference final {
            return this->it.value();
        }

        __CDS_OptimalInline auto operator ++ () noexcept -> ConstReverseIterator & final {
            return this->next();
        }
        __CDS_OptimalInline auto operator ++ (int) noexcept -> ConstReverseIterator {
            auto copy = * this;
            this->next();
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstReverseIterator * override {
            return Memory :: instance().create < ConstReverseIterator > ( * this );
        }
    };

    auto operator == (HashMap const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( this->size() != o.size() ) return false;

        for ( auto b = this->begin(), bOther = o.begin(); b != this->end() && bOther != o.end(); b++, bOther++ )
            if ( b.value () != bOther.value() )
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

    __CDS_OptionalInline HashMap ( InitializerList list ) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto & e : list )
            this->insert( e );
    }

    explicit HashMap (
            CollectionIterator const & from,
            CollectionIterator const & to
    ) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy () ); ! it->equals ( from ); it->next() )
            this->insert(it->value());
    }

    explicit HashMap (
            ConstCollectionIterator const & from,
            ConstCollectionIterator const & to
    ) noexcept :
            pBuckets(Memory :: instance().createArray < HashBucket > (hashCalculator.getBoundary())) {

        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy () ); ! it->equals ( from ); it->next() )
            this->insert(it->value());
    }

    ~HashMap () noexcept override {
        Memory :: instance().destroyArray ( this->pBuckets );
    }

private:
    __CDS_OptionalInline auto beginPtr () noexcept -> Iterator * final {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->endPtr();
        return Memory::instance().create < Iterator > ( this->pBuckets[i].begin(), this->pBuckets, i, this );
    }

    __CDS_OptionalInline auto beginPtr () const noexcept -> ConstIterator * final  {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->endPtr();
        return Memory::instance().create < ConstIterator > ( this->pBuckets[i].cbegin(), this->pBuckets, i, this );
    }

    __CDS_OptimalInline auto endPtr () noexcept -> Iterator * final { return Memory :: instance().create < Iterator > ( this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    __CDS_OptimalInline auto endPtr () const noexcept -> ConstIterator * final { return Memory :: instance().create < ConstIterator > (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }

public:
    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->end();
        return Iterator( this->pBuckets[i].begin(), this->pBuckets, i, this );
    }

    __CDS_cpplang_ConstexprConditioned auto begin () const noexcept -> ConstIterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->end();
        return ConstIterator( this->pBuckets[i].cbegin(), this->pBuckets, i, this );
    }

    __CDS_cpplang_ConstexprConditioned auto cbegin () const noexcept -> ConstIterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->cend();
        return ConstIterator (this->pBuckets[i].cbegin(), this->pBuckets, i, this);
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return this->rend();
        return ReverseIterator(this->pBuckets[i].rbegin(), this->pBuckets, i, this);
    }

    __CDS_cpplang_ConstexprConditioned auto rbegin () const noexcept -> ConstReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return this->rend();
        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i, this);
    }

    __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto crbegin () const noexcept -> ConstReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return this->crend();
        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i, this);
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator(this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1, this); }
    __CDS_OptimalInline auto end () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    __CDS_OptimalInline auto cend () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto rend () noexcept -> ReverseIterator { return ReverseIterator(this->pBuckets[0].rend(), this->pBuckets, 0, this); }
    __CDS_OptimalInline auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }
    __CDS_OptimalInline auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }

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
