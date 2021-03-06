//
// Created by loghin on 25.01.2021.
//
#ifndef CDS_HASHMAP_HPP
#define CDS_HASHMAP_HPP

#include <CDS/Map>
#include <sstream>
#include <cstring>



#if defined(__cpp_concepts) && !defined(_MSC_VER)

#endif

template <class K, class V, class H>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
    UniqueIdentifiable<K> &&
    HashCalculatorHasBoundaryFunction<H>
#endif
class HashMap final : public Map<K, V> {
public:
    H hashCalculator;

    using Key                           = typename Map<K, V>::Key;
    using Value                         = typename Map<K, V>::Value;
    using KeyReference                  = typename Map<K, V>::KeyReference;
    using ValueReference                = typename Map<K, V>::ValueReference;
    using KeyConstReference             = typename Map<K, V>::KeyConstReference;
    using ValueConstReference           = typename Map<K, V>::ValueConstReference;
    using Entry                         = typename Map<K, V>::Entry;
    using EntryReference                = typename Map<K, V>::EntryReference;
    using EntryConstReference           = typename Map<K, V>::EntryConstReference;

    using EntryReferenceList            = typename Map<K, V>::EntryReferenceList;
    using EntryConstReferenceList       = typename Map<K, V>::EntryConstReferenceList;

    using CollectionIterator            = typename Collection<Entry>::Iterator;
    using CollectionConstIterator       = typename Collection<Entry>::ConstIterator;

private:
    using HashBucket                    = LinkedList < Entry >;
    using BucketIterator                = typename HashBucket::Iterator;
    using BucketConstIterator           = typename HashBucket::ConstIterator;
    using BucketReverseIterator         = typename HashBucket::ReverseIterator;
    using BucketConstReverseIterator    = typename HashBucket::ConstReverseIterator;

    HashBucket * pBuckets;
public:
    class IteratorBase : public CollectionIterator {
    protected:
        H hashCalculator;
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        IteratorBase() noexcept = default;
        IteratorBase(IteratorBase const &) noexcept = default;
        IteratorBase(IteratorBase &&) noexcept = default;
        explicit IteratorBase( HashBucket * pB, Index i ) noexcept : pBuckets(pB), bucketIndex ( i ) { }
        virtual ~IteratorBase() noexcept = default;

        auto inline nextBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( this->pBuckets[this->bucketIndex].empty() && ! isOutOfRange() )
                this->bucketIndex++;
            return * this;
        }

        auto inline previousBucket () noexcept -> IteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( this->pBuckets[this->bucketIndex].empty() && ! isOutOfRange() )
                this->bucketIndex --;
            return * this;
        }

        [[nodiscard]] auto constexpr inline isOutOfRange () const noexcept -> bool { return bucketIndex < 0 || bucketIndex >= hashCalculator.getBoundary(); }
    };

    class ConstIteratorBase : public CollectionConstIterator {
    protected:
        H hashCalculator;
        Index bucketIndex {0};
        HashBucket * pBuckets { nullptr };

        ConstIteratorBase() noexcept = default;
        ConstIteratorBase(ConstIteratorBase const &) noexcept = default;
        ConstIteratorBase(ConstIteratorBase &&) noexcept = default;
        explicit ConstIteratorBase( HashBucket * pB, Index i ) noexcept : pBuckets(pB), bucketIndex ( i ) { }
        virtual ~ConstIteratorBase() noexcept = default;

        auto inline nextBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex ++;
            while ( this->pBuckets[this->bucketIndex].empty() && ! isOutOfRange() )
                this->bucketIndex++;
            return * this;
        }

        auto inline previousBucket () noexcept -> ConstIteratorBase & {
            if ( isOutOfRange() )
                return * this;
            this->bucketIndex --;
            while ( this->pBuckets[this->bucketIndex].empty() && ! isOutOfRange() )
                this->bucketIndex--;
            return * this;
        }

        [[nodiscard]] auto constexpr inline isOutOfRange () const noexcept -> bool { return bucketIndex < 0 || bucketIndex >= hashCalculator.getBoundary(); }
    };

    class Iterator : public IteratorBase {
    private:
        BucketIterator it;

    public:
        Iterator() noexcept = default;
        Iterator(Iterator const &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;
        explicit Iterator ( BucketIterator const & iter, HashBucket * pBucket, Index i ) noexcept : IteratorBase(pBucket, i), it(iter) {}
        ~Iterator() noexcept = default;

        auto inline next () noexcept -> Iterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].end() == it ) {
                this->nextBucket();
                if ( this->isOutOfRange() )  {
                    it = this->pBuckets[this->hashCalculator.getBoundary() - 1].end();
                    this->bucketIndex = this->hashCalculator.getBoundary() - 1;
                }
                else it = this->pBuckets[this->bucketIndex].begin();

                return * this;
            }
            return * this;
        }

        constexpr auto inline equals ( const CollectionIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < Iterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> Iterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
    };

    class ConstIterator : public ConstIteratorBase {
    private:
        BucketConstIterator it;

    public:
        ConstIterator() noexcept = default;
        ConstIterator(ConstIterator const &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;
        explicit ConstIterator ( BucketConstIterator const & iter, HashBucket * pBucket, Index i ) noexcept : ConstIteratorBase(pBucket, i), it(iter) {}
        ~ConstIterator() noexcept = default;

        auto inline next () noexcept -> ConstIterator & final {
            if ( this->isOutOfRange() ) return * this;
            this->it.next();
            if ( this->pBuckets[this->bucketIndex].cend() == it ) {
                this->nextBucket();
                if ( this->isOutOfRange() ) {
                    it = this->pBuckets[this->hashCalculator.getBoundary() - 1].cend();
                    this->bucketIndex = this->hashCalculator.getBoundary() - 1;
                }
                else it = this->pBuckets[this->bucketIndex].cbegin();

                return * this;
            }
            return * this;
        }

        constexpr auto inline equals ( const CollectionConstIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryConstReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ConstIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
    };

    class ReverseIterator : public IteratorBase {
    private:
        BucketReverseIterator it;

    public:
        ReverseIterator() noexcept = default;
        ReverseIterator(ReverseIterator const &) noexcept = default;
        ReverseIterator(ReverseIterator &&) noexcept = default;
        explicit ReverseIterator ( BucketReverseIterator const & iter, HashBucket * pBucket, Index i ) noexcept : IteratorBase(pBucket, i), it(iter) {}
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


        constexpr auto inline equals ( const CollectionIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ReverseIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
    };

    class ConstReverseIterator : public ConstIteratorBase {
    private:
        BucketConstReverseIterator it;

    public:
        ConstReverseIterator() noexcept = default;
        ConstReverseIterator(ConstReverseIterator const &) noexcept = default;
        ConstReverseIterator(ConstReverseIterator &&) noexcept = default;
        explicit ConstReverseIterator ( BucketConstReverseIterator const & iter, HashBucket * pBucket, Index i ) noexcept : ConstIteratorBase(pBucket, i), it(iter) {}
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

        constexpr auto inline equals ( const CollectionConstIterator & i ) const noexcept -> bool final {
            auto p = dynamic_cast < ConstReverseIterator const * > ( & i );
            if ( p == nullptr ) return false;
            return this->bucketIndex == p->bucketIndex && p->it == this->it;
        }

        constexpr inline auto value () const noexcept -> EntryConstReference final { return this->it.value(); }

        inline auto operator ++ () noexcept -> ConstReverseIterator & final { this->next(); return * this; }
        inline auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }
    };

    auto operator == (HashMap const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( this->size() != o.size() ) return false;

        for ( auto b = this->begin(), bOther = o.begin(); b != this->end() && bOther != o.end(); b++, bOther++ )
            if ( b.value () != bOther.value() )
                return false;

        return true;
    }

    auto equals (Object const & o) const noexcept -> bool final {
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

    template <class OH>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires HashCalculatorHasBoundaryFunction<OH>
#endif
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
        for ( auto it = from; it != to; it ++ )
            this->insert(it.value());
    }

    explicit HashMap (
        CollectionConstIterator const & from,
        CollectionConstIterator const & to
    ) noexcept : pBuckets(new HashBucket[hashCalculator.getBoundary()]) {
        for ( auto it = from; it != to; it ++ )
            this->insert(it.value());
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
            return endPtr();
        return new Iterator( this->pBuckets[i].begin(), this->pBuckets, i );
    }

    inline auto beginPtr () const noexcept -> ConstIterator * final  {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return endPtr();
        return new ConstIterator( this->pBuckets[i].cbegin(), this->pBuckets, i );
    }

    inline auto endPtr () noexcept -> Iterator * final { return new Iterator( this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1 ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator(this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1 ); }

public:
    constexpr inline auto begin () noexcept -> Iterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return end();
        return Iterator( this->pBuckets[i].begin(), this->pBuckets, i );
    }

    constexpr inline auto begin () const noexcept -> ConstIterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return end();
        return ConstIterator( this->pBuckets[i].cbegin(), this->pBuckets, i );
    }

    constexpr inline auto cbegin () const noexcept -> ConstIterator {
        Index i = 0;
        while ( i < hashCalculator.getBoundary() && this->pBuckets[i].empty() )
            i++;
        if ( i >= hashCalculator.getBoundary() )
            return cend();
        return ConstIterator (this->pBuckets[i].cbegin(), this->pBuckets, i);
    }

    constexpr inline auto rbegin () noexcept -> ReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return rend();
        return ReverseIterator(this->pBuckets[i].rbegin(), this->pBuckets, i);
    }
    constexpr inline auto rbegin () const noexcept -> ConstReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return rend();
        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i);
    }
    constexpr inline auto crbegin () const noexcept -> ConstReverseIterator {
        Index i = hashCalculator.getBoundary();
        while ( i >= 0 && this->pBuckets[i].empty() )
            i--;
        if ( i < 0 )
            return crend();
        return ConstReverseIterator (this->pBuckets[i].rbegin(), this->pBuckets, i);
    }

    constexpr inline auto end () noexcept -> Iterator { return Iterator(this->pBuckets[hashCalculator.getBoundary() - 1].end(), this->pBuckets, hashCalculator.getBoundary() - 1); }
    constexpr inline auto end () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1 ); }
    constexpr inline auto cend () const noexcept -> ConstIterator { return ConstIterator (this->pBuckets[hashCalculator.getBoundary() - 1].cend(), this->pBuckets, hashCalculator.getBoundary() - 1 ); }
    constexpr inline auto rend () noexcept -> ReverseIterator { return ReverseIterator(this->pBuckets[0].rend(), this->pBuckets, 0); }
    constexpr inline auto rend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0 ); }
    constexpr inline auto crend () const noexcept -> ConstReverseIterator { return ConstReverseIterator (this->pBuckets[0].crend(), this->pBuckets, 0 ); }

    auto keys () const noexcept -> LinkedList < Reference < const Key > > final {
        LinkedList < Reference < const Key > > keys;
        for ( auto & e : ( *this ) )
            keys.pushBack ( e.getFirst() );
        return keys;
    }

    auto values () noexcept -> LinkedList < Reference < Value > > {
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
            if ( e.getFirst() == k )
                return { e.getSecond() };
        return {};
    }

    auto find ( KeyConstReference k ) noexcept -> Optional < Reference < Value > > final {
        for ( auto & e : this->pBuckets[hashCalculator(k)] )
            if ( e.getFirst() == k )
                return { e.getSecond() };
        return {};
    }

    auto get ( KeyConstReference k ) noexcept -> ValueReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( e.getFirst() == k )
                return e.getSecond();

        b.pushBack ( { k, Value() } );
        return b.back().getSecond();
    }

    auto get ( KeyConstReference k ) const noexcept (false) -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( e.getFirst() == k )
                return e.getSecond();

        throw typename Map<K, V>::MapPairNonExistent();
    }

    auto getOr ( KeyConstReference k, ValueConstReference defVal ) const noexcept -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(k)];

        for ( auto & e : b )
            if ( e.getFirst() == k )
                return e.getSecond();

        return defVal;
    }

    auto containsKey ( KeyConstReference k ) const noexcept -> bool final {
        for ( auto & e : (*this) )
            if ( e.getFirst() == k )
                return true;
        return false;
    }

    auto containsValue ( ValueConstReference v ) const noexcept -> bool final {
        for ( auto & e : (*this) )
            if ( e.getSecond() == v )
                return true;
        return false;
    }

    auto remove ( KeyConstReference k ) noexcept -> bool final {
        auto & b = this->pBuckets[hashCalculator(k)];
        Entry e;
#if defined(__cpp_concepts) && !defined(_MSC_VER)
        b.forEach([&e, &k](auto & p){if (p.getFirst() == k) e = p;});
#else
        for ( auto & p : b )
            if ( p.getFirst() == k ) e = p;
#endif
        return b.removeFirst(e);
    }

    auto insert ( Entry const & p ) noexcept -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(p.getFirst())];
        b.pushBack(p);
        return b.back().getSecond();
    }

    auto insert ( Entry && p ) noexcept -> ValueConstReference final {
        auto & b = this->pBuckets[hashCalculator(p.getFirst())];
        b.pushBack(std::move(p));
        return b.back().getSecond();
    }

    auto emplace ( KeyConstReference k, ValueConstReference v ) noexcept -> ValueConstReference final {
        return this->insert( {k, v} );
    }

    auto clear () noexcept -> void final {
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            this->pBuckets[i].clear();
    }

    [[nodiscard]] auto size () const noexcept -> Size final {
        Size total = 0ull;
        for ( Index i = 0; i < hashCalculator.getBoundary(); i++ )
            total += this->pBuckets[i].size();
        return total;
    }

    HashMap & operator = ( HashMap const & o ) noexcept {
        if ( this == & o )
            return * this;

        this->clear();
        for ( auto & e : o )
            this->insert(e);

        return * this;
    }

    [[nodiscard]] inline auto empty() const noexcept -> bool final {
        return this->size() == 0;
    }

    [[nodiscard]] auto toString() const noexcept -> String {
        if ( this->empty() )
            return String("{ }");
        std::stringstream oss;
        oss << "{ ";
        for ( auto & e : (*this) ) {
#if !defined(CDS_GLM)
            oss << e.getFirst() << " : " << e.getSecond() << ", ";
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
        return String(s.substr(0, s.length() - 2).append(" }"));
    }

//    auto view () const noexcept -> View < HashMap < K, V, H > >;

    auto sequence () const noexcept -> Sequence < const HashMap < K, V, H > >;
    auto sequence () noexcept -> Sequence < HashMap < K, V, H > >;
};

//#include <CDS/View>
//template <class K, class V, class H>
//#if defined(__cpp_concepts) && !defined(_MSC_VER)
//    requires
//    UniqueIdentifiable<K> &&
//    HashCalculatorHasBoundaryFunction<H>
//#endif
//auto HashMap < K, V, H >::view() const noexcept -> View < HashMap < K, V, H > > {
//    return View(*this);
//}

#include <CDS/Sequence>

template <class K, class V, class H>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
UniqueIdentifiable<K> &&
HashCalculatorHasBoundaryFunction<H>
#endif
auto HashMap < K, V, H >::sequence() const noexcept -> Sequence < const HashMap < K, V, H > > {
    return Sequence(*this);
}

template <class K, class V, class H>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
UniqueIdentifiable<K> &&
HashCalculatorHasBoundaryFunction<H>
#endif
auto HashMap < K, V, H >::sequence() noexcept -> Sequence < HashMap<K, V, H>> {
    return Sequence(*this);
}

template < typename K, typename V >
HashMap ( std::initializer_list < Pair < K, V > > ) -> HashMap < K, V >;

#endif //CDS_HASHMAP_HPP
