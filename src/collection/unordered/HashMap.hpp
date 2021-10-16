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
) class HashMap final : public Map<K, V> {
public:
    H hashCalculator;

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

    using CollectionIterator                        = typename Collection<Entry>::Iterator;
    using CollectionConstIterator                   = typename Collection<Entry>::ConstIterator;

private:
    using HashBucket                                = LinkedList < Entry >;
    using BucketIterator                            = typename HashBucket::Iterator;
    using BucketConstIterator                       = typename HashBucket::ConstIterator;
    using BucketReverseIterator                     = typename HashBucket::ReverseIterator;
    using BucketConstReverseIterator                = typename HashBucket::ConstReverseIterator;

    HashBucket * pBuckets;
public:
    class IteratorBase : public CollectionIterator {
    protected:
        HashMap < K, V, H > * pMap {nullptr};
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        IteratorBase() noexcept = default;
        IteratorBase(IteratorBase const &) noexcept = default;
        IteratorBase(IteratorBase &&) noexcept = default;
        explicit IteratorBase( HashBucket * pB, Index i, HashMap < K, V, H > * pMap ) noexcept : CollectionIterator (pMap), pBuckets(pB), bucketIndex ( i ), pMap(pMap) { }
        virtual ~IteratorBase() noexcept = default;

        auto inline nextBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( ! isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex++;
            return * this;
        }

        auto inline previousBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( ! isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex --;
            return * this;
        }

        __CDS_NoDiscard auto constexpr inline isOutOfRange () const noexcept -> bool { return bucketIndex < 0 || bucketIndex >= pMap->getHashCalculator().getBoundary(); }

        __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;
    };

    class ConstIteratorBase : public CollectionConstIterator {
    protected:
        HashMap < K, V, H > const * pMap {nullptr};
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        ConstIteratorBase() noexcept = default;
        ConstIteratorBase(ConstIteratorBase const &) noexcept = default;
        ConstIteratorBase(ConstIteratorBase &&) noexcept = default;
        explicit ConstIteratorBase( HashBucket * pB, Index i, HashMap < K, V, H > const * pMap ) noexcept : CollectionConstIterator(pMap), pBuckets(pB), bucketIndex ( i ), pMap(pMap) { }
        virtual ~ConstIteratorBase() noexcept = default;

        auto inline nextBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( ! this->isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex++;
            return * this;
        }

        auto inline previousBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( ! this->isOutOfRange() && this->pBuckets[this->bucketIndex].empty() )
                this->bucketIndex--;
            return * this;
        }

        __CDS_NoDiscard auto constexpr inline isOutOfRange () const noexcept -> bool { return bucketIndex < 0 || bucketIndex >= pMap->getHashCalculator().getBoundary(); }

        __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;
    };

    class Iterator : public IteratorBase {
    private:
        BucketIterator it;

    public:
        Iterator() noexcept = default;
        Iterator(Iterator const &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;
        explicit Iterator ( BucketIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > * pMap ) noexcept : IteratorBase(pBucket, i, pMap), it(iter) {}
        ~Iterator() noexcept = default;

        auto inline next () noexcept -> Iterator & final {
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

        __CDS_cpplang_ConstexprConditioned auto  equals ( const CollectionIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < Iterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> Iterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> Iterator * override {
            return new Iterator ( * this );
        }
    };

    class ConstIterator : public ConstIteratorBase {
    private:
        BucketConstIterator it;

    public:
        ConstIterator() noexcept = default;
        ConstIterator(ConstIterator const &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;
        explicit ConstIterator ( BucketConstIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > const * pMap ) noexcept : ConstIteratorBase(pBucket, i, pMap), it(iter) {}
        ~ConstIterator() noexcept = default;

        auto inline next () noexcept -> ConstIterator & final {
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

        __CDS_cpplang_ConstexprConditioned auto equals ( const CollectionConstIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> EntryConstReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ConstIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> ConstIterator * override {
            return new ConstIterator ( * this );
        }
    };

    class ReverseIterator : public IteratorBase {
    private:
        BucketReverseIterator it;

    public:
        ReverseIterator() noexcept = default;
        ReverseIterator(ReverseIterator const &) noexcept = default;
        ReverseIterator(ReverseIterator &&) noexcept = default;
        explicit ReverseIterator ( BucketReverseIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > * pMap ) noexcept : IteratorBase(pBucket, i, pMap), it(iter) {}
        ~ReverseIterator() noexcept = default;

        auto inline next () noexcept -> ReverseIterator & final {
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


        __CDS_cpplang_ConstexprConditioned auto equals ( const CollectionIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ReverseIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> ReverseIterator * override {
            return new ReverseIterator ( * this );
        }
    };

    class ConstReverseIterator : public ConstIteratorBase {
    private:
        BucketConstReverseIterator it;

    public:
        ConstReverseIterator() noexcept = default;
        ConstReverseIterator(ConstReverseIterator const &) noexcept = default;
        ConstReverseIterator(ConstReverseIterator &&) noexcept = default;
        explicit ConstReverseIterator ( BucketConstReverseIterator const & iter, HashBucket * pBucket, Index i, HashMap < K, V, H > const * pMap ) noexcept : ConstIteratorBase(pBucket, i, pMap), it(iter) {}
        ~ConstReverseIterator() noexcept = default;

        auto inline next () noexcept -> ReverseIterator & final {
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

        __CDS_cpplang_ConstexprConditioned auto equals ( const CollectionConstIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryConstReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ConstReverseIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> ConstReverseIterator * override {
            return new ConstReverseIterator ( * this );
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

    inline auto getHashCalculator () const noexcept -> H const & { return hashCalculator; }

    HashMap () noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) { }
    HashMap (HashMap const & hm) noexcept {
        this->pBuckets = new HashBucket [hm.getHashCalculator().getBoundary()];
        for ( Index i = 0; i < hm.getHashCalculator().getBoundary(); i++ ) {
            this->pBuckets[i] = hm.pBuckets[i];
        }
    }

    inline HashMap ( HashMap && hashMap ) noexcept :
            hashCalculator ( std :: move ( hashMap.hashCalculator ) ),
            pBuckets ( Utility :: exchange ( hashMap.pBuckets, nullptr ) ) {

    }

    template <class OH> __CDS_Requires ( HashCalculatorHasBoundaryFunction<OH> )
    explicit HashMap (HashMap<K, V, OH> const & hm) noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) {
        for ( auto & e : hm.entries() )
            this->insert ( e );
    }

    HashMap ( std::initializer_list<Entry> const & list ) noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) {
        for ( auto & e : list )
            this->insert( e );
    }

    explicit HashMap (
        CollectionIterator const & from,
        CollectionIterator const & to
    ) noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) {
        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy () ); ! it->equals ( from ); it->next() )
            this->insert(it->value());
    }

    explicit HashMap (
        CollectionConstIterator const & from,
        CollectionConstIterator const & to
    ) noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) {
        for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy () ); ! it->equals ( from ); it->next() )
            this->insert(it->value());
    }

    ~HashMap () noexcept final {
        delete [] this->pBuckets;
    }

private:
    inline auto beginPtr () noexcept -> Iterator * final {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->endPtr();
        return new Iterator( this->pBuckets[i].begin(), this->pBuckets, i, this );
    }

    inline auto beginPtr () const noexcept -> ConstIterator * final  {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return this->endPtr();
        return new ConstIterator( this->pBuckets[i].cbegin(), this->pBuckets, i, this );
    }

    inline auto endPtr () noexcept -> Iterator * final { return new Iterator( this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator(this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }

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
    constexpr inline auto end () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    constexpr inline auto cend () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1, this ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto rend () noexcept -> ReverseIterator { return ReverseIterator(this->pBuckets[0].rend(), this->pBuckets, 0, this); }
    constexpr inline auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }
    constexpr inline auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0, this ); }

    auto keys () const noexcept -> LinkedList < Reference < const Key > > final {
        LinkedList < Reference < const Key > > keys;
        for ( auto & e : ( *this ) )
            keys.pushBack ( Reference < const Key > ( e.getFirst() ) );
        return keys;
    }

    auto values () noexcept -> LinkedList < Reference < Value > > override {
        LinkedList < Reference < Value > > values;
        for ( auto & e : (*this) )
            values.pushBack ( e.getSecond() );

        return values;
    }

    auto values () const noexcept -> LinkedList < Reference < const Value > > final {
        LinkedList < Reference < const Value > > values;
        for ( auto & e : (*this) )
            values.pushBack ( e.getSecond() );

        return values;
    }

    auto entries () noexcept -> LinkedList < Pair < Reference < const Key >, Reference < Value > > > final {
        LinkedList < Pair < Reference < const Key >, Reference < Value > > > entries;
        for ( auto & e : (*this) )
            entries.pushBack({ {e.getFirst()}, {e.getSecond()} });

        return entries;
    }

    auto entries () const noexcept -> LinkedList < Pair < Reference < const Key >, Reference < const Value > > > final {
        LinkedList < Pair < Reference < const Key >, Reference < const Value > > > entries;
        for ( auto & e : (*this) )
            entries.pushBack({ {e.getFirst()}, {e.getSecond()} });

        return entries;
    }

    auto find ( KeyConstReference k ) const noexcept -> Optional < Reference < const Value > > final {
        for ( auto & e : this->pBuckets[hashCalculator(k)] )
            if ( Type < K > :: compare ( e.getFirst(), k ) )
                return { e.getSecond() };
        return {};
    }

    auto find ( KeyConstReference k ) noexcept -> Optional < Reference < Value > > final {
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

        throw typename Map<K, V>::MapPairNonExistent();
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
        auto & b = this->pBuckets[hashCalculator(k)];
        Entry e;
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        b.forEach([&e, &k](auto & p){if (Type < K > :: compare ( p.getFirst(), k )) e = p;});
#else
        for ( auto & p : b )
            if ( Type < Key > :: compare ( p.getFirst(), k ) ) e = p;
#endif
        return b.removeFirst(e);
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

    auto clear () noexcept -> void final {
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            this->pBuckets[i].clear();
    }

    __CDS_NoDiscard auto size () const noexcept -> Size final {
        Size total = 0ull;
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            total += this->pBuckets[i].size();
        return total;
    }

    inline auto operator = ( HashMap const & o ) noexcept -> HashMap & {
        if ( this == & o )
            return * this;

        this->clear();
        for ( auto & e : o )
            this->insert(e);

        return * this;
    }

    inline auto operator = ( HashMap && hashMap ) noexcept -> HashMap & {
        if ( this == & hashMap ) return * this;

        delete [] this->pBuckets;

        this->pBuckets = Utility::exchange ( hashMap.pBuckets, nullptr );
        this->hashCalculator = std :: move ( hashMap.hashCalculator );

        return * this;
    }

    __CDS_NoDiscard inline auto empty() const noexcept -> bool final {
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

    auto sequence () const noexcept -> Sequence < const HashMap < K, V, H > >;
    auto sequence () noexcept -> Sequence < HashMap < K, V, H > >;
};

#include <CDS/Sequence>

template <class K, class V, class H>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
UniqueIdentifiable<K> &&
HashCalculatorHasBoundaryFunction<H>
#endif
auto HashMap < K, V, H >::sequence() const noexcept -> Sequence < const HashMap < K, V, H > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template <class K, class V, class H>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
UniqueIdentifiable<K> &&
HashCalculatorHasBoundaryFunction<H>
#endif
auto HashMap < K, V, H >::sequence() noexcept -> Sequence < HashMap<K, V, H>> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
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
