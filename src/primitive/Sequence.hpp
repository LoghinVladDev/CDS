//
// Created by loghin on 02.06.2021.
//

#ifndef CDS_SEQUENCE_HPP
#define CDS_SEQUENCE_HPP

#include <CDS/Object>

#include <CDS/Boolean>
#include <CDS/Optional>
#include <CDS/Pair>
#include <CDS/Map>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/Set>
#include <CDS/Types>

#if defined(__linux) && GCC_VERSION >= 10200 && defined(__cpp_concepts)
//#define _REQUIRES_ITERABLE requires Iterable < C > || ConstIterable < C >
//#define _REQUIRES_PRINTABLE requires HasToString < C >
//#define _REQUIRES_INTEGRAL_ITERABLE requires Iterable < C > && Integral < C >
#else
//#define _REQUIRES_ITERABLE
//#define _REQUIRES_PRINTABLE
//#define _REQUIRES_INTEGRAL_ITERABLE
#endif

template < typename C >
class Sequence : public Object {
public:
    using CollectionType = C;

private:

    using ClassName                 = typename std::remove_reference < C >::type;
    using IterableValue             = decltype ( dataTypes::unsafeAddress < typename ClassName::Iterator > ()->value() );

public:
    using ElementType               = typename std::remove_reference < IterableValue > :: type;

private:
    using StoredPredicate           = std::function < bool (IterableValue) >;
    using StoredMapper              = std::function < std::remove_reference_t < IterableValue > (IterableValue) >;

    using StoredIndexedPredicate    = std::function < bool (Index, IterableValue) >;
    using StoredIndexedMapper       = std::function < std::remove_reference_t < IterableValue > (Index, IterableValue) >;

    friend class Iterator;
    friend class ConstIterator;

    /**
     * can be:
     *      Unique < Foreign > representing lack of ownership, a view created over a structure outside its scope
     *      Unique < Unique > representing ownership, a structure created by the view to iterate upon
     */
    UniquePointer < PointerBase < C > > pCollection { nullptr };
    uint16                              chainCount  { 0 }; // used to determine order of operations

// TODO
//    When #3 Address Move Semantics Issues in regards to Collection Move Operations - is fixed
//    LinkedList < Pair < UniquePointer < StoredPredicate >,  Index > > storedPredicates;
//    LinkedList < Pair < UniquePointer < StoredMapper >,     Index > > storedMappers;

    LinkedList < Pair < SharedPointer < StoredPredicate >,  Index > >       storedPredicates;
    LinkedList < Pair < SharedPointer < StoredMapper >,     Index > >       storedMappers;

    LinkedList < Pair < SharedPointer < StoredIndexedPredicate >, Index > > storedIndexedPredicates;
    LinkedList < Pair < SharedPointer < StoredIndexedMapper >,    Index > > storedIndexedMappers;

public:
    class Iterator : public Object {
    public:
        using CollectionIterator = typename std::conditional <
                std::is_const < CollectionType > :: type :: value,
                typename CollectionType :: ConstIterator,
                typename CollectionType :: Iterator
        > :: type;
        using CollectionElementType = typename Sequence::ElementType;

    private:
        ForeignPointer < Sequence > pSeq;
        CollectionIterator it;

        CollectionElementType precomputed;
        auto skipFiltered () noexcept -> void;

        Index index {0};

    public:
        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto hash () const noexcept -> Index override;
        [[nodiscard]] auto copy () const noexcept -> Iterator * override;
        [[nodiscard]] auto equals (Object const &) const noexcept -> bool override;

        Iterator () noexcept = delete;
        Iterator (Iterator const &) noexcept = default;
        Iterator (Iterator &&) noexcept = default;
        Iterator (Sequence *, CollectionIterator const &) noexcept;
        ~Iterator () noexcept override = default;

        auto value () const noexcept -> CollectionElementType;
        auto next () noexcept -> Iterator &;
        auto equals ( Iterator const & ) const noexcept -> Boolean;

        auto operator == ( Iterator const & ) const noexcept -> bool;
        auto operator != ( Iterator const & ) const noexcept -> bool;
        auto operator ++ () noexcept -> Iterator &;
        auto operator ++ (int) noexcept -> Iterator;
        auto operator * () const noexcept -> CollectionElementType;
    };

    class ConstIterator : public Object {
    public:
        using CollectionIterator = typename CollectionType::ConstIterator;
        using CollectionElementType = typename Sequence::ElementType;

    private:
        ForeignPointer < const Sequence > pSeq;
        CollectionIterator it;

        CollectionElementType precomputed;
        auto skipFiltered () noexcept -> void;

        Index index {0};

    public:
        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto hash () const noexcept -> Index override;
        [[nodiscard]] auto copy () const noexcept -> ConstIterator * override;
        [[nodiscard]] auto equals (Object const &) const noexcept -> bool override;

        ConstIterator () noexcept = delete;
        ConstIterator (ConstIterator const &) noexcept = default;
        ConstIterator (ConstIterator &&) noexcept = default;
        ConstIterator (Sequence const *, CollectionIterator const &) noexcept;
        ~ConstIterator () noexcept override = default;

        auto value () const noexcept -> CollectionElementType;
        auto next () noexcept -> ConstIterator &;
        auto equals ( ConstIterator const & ) const noexcept -> Boolean;

        auto operator == ( ConstIterator const & ) const noexcept -> bool;
        auto operator != ( ConstIterator const & ) const noexcept -> bool;
        auto operator ++ () noexcept -> ConstIterator &;
        auto operator ++ (int) noexcept -> ConstIterator;
        auto operator * () const noexcept -> CollectionElementType;
    };

private:
    auto clear () noexcept -> void;

public:
    [[maybe_unused]] Sequence () noexcept = delete;
    [[maybe_unused]] Sequence (Sequence const &) noexcept;
    [[maybe_unused]] Sequence (Sequence &&) noexcept;

    [[maybe_unused]] explicit Sequence ( C & ) noexcept;
    [[maybe_unused]] explicit Sequence ( C && ) noexcept;

    ~Sequence () noexcept override = default;

    auto operator = (Sequence const &) noexcept -> Sequence &;
    auto operator = (Sequence &&) noexcept -> Sequence &;

    [[maybe_unused]] auto begin () noexcept -> Iterator;
    [[maybe_unused]] auto end () noexcept -> Iterator;

    [[maybe_unused]] auto begin () const noexcept -> ConstIterator;
    [[maybe_unused]] auto end () const noexcept -> ConstIterator;
    [[maybe_unused]] auto cbegin () const noexcept -> ConstIterator;
    [[maybe_unused]] auto cend () const noexcept -> ConstIterator;

    [[nodiscard]] [[maybe_unused]] auto toString () const noexcept -> String override;
    [[nodiscard]] [[maybe_unused]] auto hash () const noexcept -> Index override;
    [[nodiscard]] [[maybe_unused]] auto copy () const noexcept -> Sequence * override;
    [[nodiscard]] [[maybe_unused]] auto equals (Object const &) const noexcept -> bool override;

    [[maybe_unused]] auto contains ( ElementType const & ) const noexcept -> Boolean
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto elementAt ( Index ) const noexcept -> Optional < ElementType >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto elementAtOr ( Index, ElementType const & ) const noexcept -> ElementType
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto indexOf ( ElementType const & ) const noexcept -> Index
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto lastIndexOf ( ElementType const & ) const noexcept -> Index
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto indicesOf ( ElementType const & ) const noexcept -> LinkedList < Index >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Action >
    [[maybe_unused]] auto apply ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    [[maybe_unused]] auto also ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    [[maybe_unused]] auto find ( Predicate const & ) const noexcept -> Optional < ElementType >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto first (
            Predicate const & = [](ElementType const &) noexcept -> bool { return true; }
    ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto firstOr (
            ElementType const &,
            Predicate   const & = [] ( ElementType const & ) noexcept -> bool { return true; }
    ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto findLast ( Predicate const & ) const noexcept -> Optional < ElementType >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto last (
            Predicate const & = [] ( ElementType const & ) noexcept -> bool { return true; }
    ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto lastOr (
            ElementType const &,
            Predicate   const & = [](ElementType const &) noexcept -> bool { return true; }
    ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto single () const noexcept -> Optional < ElementType >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto singleOr ( ElementType const & ) const noexcept -> ElementType
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto single ( Predicate const & ) const noexcept -> Optional < ElementType >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto singleOr ( ElementType const &, Predicate const & ) const noexcept -> ElementType
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto drop (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > ) {

        LinkedList < ElementType > remaining;

        Index i = 0;
        for ( auto e : * this ) {
            if ( i < count ) {
                i++;
                continue;
            }

            remaining.append(e);
        }

        return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
    }

    template < typename Predicate >
    [[maybe_unused]] auto dropWhile (
            Predicate const & p,
            Size count          = UINT64_MAX
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > ) {

        LinkedList < ElementType > remaining;

        Index i = 0;

        for ( auto e : * this ) {
            if ( i < count && p (e) ) {
                i ++;
                continue;
            }

            remaining.append(e);
        }

        return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
    }

    [[maybe_unused]] auto take (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > ) {

        LinkedList < ElementType > remaining;

        Index i = 0;

        for ( auto e : * this ) {
            if ( i < count ) {
                remaining.append(e);
                i++;
                continue;
            }
            break;
        }

        return std::move ( Sequence < LinkedList < ElementType > > (std::move(remaining)) );
    }

    template < typename Predicate >
    [[maybe_unused]] auto takeWhile (
            Predicate const &,
            Size                = UINT64_MAX
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    [[maybe_unused]] auto filter ( Predicate const & ) && noexcept -> Sequence
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    [[maybe_unused]] auto filterIndexed ( IndexedPredicate const & ) && noexcept -> Sequence
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto filterTo (
            Collection < ElementType >        &,
            Predicate                   const &
    ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    [[maybe_unused]] auto filterIndexedTo (
            Collection < ElementType >        &,
            IndexedPredicate            const &
    ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename NewType >
    [[maybe_unused]] auto filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > >
    REQUIRES(
            (Iterable < C > || ConstIterable < C >) &&
            Pointer < ElementType > &&
            Pointer < NewType >
    );

    template < typename NewType >
    [[maybe_unused]] auto filterIsDerivedTo (
            Collection < ElementType > &
    ) const noexcept -> Collection < ElementType > &
    REQUIRES(
            ( Iterable < C > || ConstIterable < C > ) &&
            Pointer < ElementType > &&
            Pointer < NewType >
    );

    template < typename Predicate >
    [[maybe_unused]] auto filterNot ( Predicate const & ) && noexcept -> Sequence
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    [[maybe_unused]] auto filterNotIndexed ( IndexedPredicate const & ) && noexcept -> Sequence
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto filterNotTo (
            Collection < ElementType >        &,
            Predicate                   const &
    ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    [[maybe_unused]] auto filterNotIndexedTo (
            Collection < ElementType >        &,
            IndexedPredicate            const &
    ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    [[maybe_unused]] auto indexOfFirst ( Predicate const & ) const noexcept -> Index
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto indexOfLast ( Predicate const & ) const noexcept -> Index
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto indicesOfAll ( Predicate const & ) const noexcept -> LinkedList < Index >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool (ElementType const &) > >
    [[maybe_unused]] auto any (
            Predicate const & = [](ElementType const & ) { return true; }
    ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    [[maybe_unused]] auto all ( Predicate const & ) const noexcept -> Boolean
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto count (
            Predicate const & = [](ElementType const &) { return true; }
    ) const noexcept -> Size REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto none (
            Predicate const & = [](ElementType const &) { return true; }
    ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    [[maybe_unused]] auto one (
            Predicate const & = [](ElementType const &) { return true; }
    ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
            typename Transformer,
            typename std::enable_if <
                    isPair < returnOf < Transformer > > :: value,
                    int
            >:: type = 0
    >
    [[maybe_unused]] auto associate (
            Transformer const &
    ) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
    REQUIRES (
            ( Iterable < C > || ConstIterable < C > ) &&
            PairType < returnOf < Transformer > >
    );

    template < typename KeyGenerator >
    [[maybe_unused]] auto associateBy (
            KeyGenerator const &
    ) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    [[maybe_unused]] auto associateBy (
            KeyGenerator    const &,
            ValueMapper     const &
    ) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, returnOf < ValueMapper > > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator >
    [[maybe_unused]] auto associateByTo (
            Map < returnOf < KeyGenerator >, ElementType >        &,
            KeyGenerator                                    const &
    ) const noexcept -> Map < returnOf < KeyGenerator >, ElementType > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    [[maybe_unused]] auto associateByTo (
            Map < returnOf < KeyGenerator >, returnOf < ValueMapper > >       &,
            KeyGenerator                                                const &,
            ValueMapper                                                 const &
    ) const noexcept -> Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename K, typename V >
    [[maybe_unused]] auto associateTo (
            Map < K, V >          &,
            Transformer     const &
    ) const noexcept -> Map < K, V > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    [[maybe_unused]] auto associateWith (
            ValueMapper const &
    ) && noexcept -> Sequence < LinkedList < Pair < ElementType, returnOf < ValueMapper > > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    [[maybe_unused]] auto associateWithTo (
            Map < ElementType, returnOf < ValueMapper > > &,
            ValueMapper const &
    ) const noexcept -> Map < ElementType , returnOf < ValueMapper > > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator = std::function < bool (ElementType const &, ElementType const &) > >
    [[maybe_unused]] auto sorted (
            Comparator const & = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
    ) && noexcept -> Sequence < Array < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto sortedBy (
            Selector const &
    ) && noexcept -> Sequence < Array < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto sortedByDescending (
            Selector const &
    ) && noexcept -> Sequence < Array < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
            typename Selector,
            typename Comparator = std::function < bool ( ElementType const &, ElementType const & ) >
    >
    [[maybe_unused]] auto sortedByWith (
            Selector const &,
            Comparator const & = []( returnOf < Selector > const & a, returnOf < Selector > const & b
            ) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < Array < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Collection >
    [[maybe_unused]] auto toCollection () const noexcept -> Collection
    REQUIRES (Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toLinkedList () const noexcept -> LinkedList < ElementType >
    REQUIRES (Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toArray () const noexcept -> Array < ElementType >
    REQUIRES (Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    [[maybe_unused]] auto toOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator >
    REQUIRES (Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toUnorderedSet () const noexcept -> UnorderedSet < ElementType >
    REQUIRES (Iterable < C > || ConstIterable < C > );

    // auto asHashMap  look into View::toMap


    template < typename Collection >
    [[maybe_unused]] auto toCollection (Collection &) const noexcept -> Collection &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toLinkedList (
            LinkedList < ElementType > &
    ) const noexcept -> LinkedList < ElementType > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toArray (
            Array <ElementType> &
    ) const noexcept -> Array < ElementType > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    [[maybe_unused]] auto toOrderedSet (
            OrderedSet <ElementType, Comparator> &
    ) const noexcept -> OrderedSet < ElementType, Comparator > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto toUnorderedSet (
            UnorderedSet <ElementType> &
    ) const noexcept -> UnorderedSet < ElementType > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Transformer >
    [[maybe_unused]] auto flatMap (
            Transformer const &
    ) && noexcept -> Sequence <
            LinkedList <
                    typename std::remove_reference <
                            decltype (
                            dataTypes::unsafeAddress <
                                    typename returnOf < Transformer > :: Iterator
                            >()->value()
                            )
                    > :: type
            >
    > REQUIRES (
            ( Iterable < C > || ConstIterable < C > ) && (
                    Iterable < returnOf < Transformer > > ||
                    ConstIterable < returnOf < Transformer > >
            )
    );

    template < typename IndexedTransformer >
    [[maybe_unused]] auto flatMapIndexed (
            IndexedTransformer const &
    ) && noexcept -> Sequence <
            LinkedList <
                    typename std::remove_reference <
                            decltype (
                            dataTypes::unsafeAddress <
                                    typename returnOf < IndexedTransformer > :: Iterator
                            > ()->value()
                            )
                    > :: type
            >
    > REQUIRES (
            ( Iterable < C > || ConstIterable < C > ) && (
                    Iterable < returnOf < IndexedTransformer > > ||
                    ConstIterable < returnOf < IndexedTransformer > >
            )
    );

    template < typename Transformer >
    [[maybe_unused]] auto flatMapTo (
            Collection <
                    typename std::remove_reference <
                            decltype (
                            dataTypes::unsafeAddress<
                                    typename returnOf < Transformer > :: Iterator
                            >()->value()
                            )
                    > :: type
            >                     &,
            Transformer     const &
    ) const noexcept -> Collection <
            typename std::remove_reference <
                    decltype (
                    dataTypes::unsafeAddress<
                            typename returnOf < Transformer > :: Iterator
                    >()->value()
                    )
            > :: type
    > & REQUIRES (
            ( Iterable < C > || ConstIterable < C > ) && (
                    Iterable <
                            typename std::remove_reference <
                                    decltype (
                                    dataTypes::unsafeAddress <
                                            typename returnOf < Transformer > :: Iterator
                                    >()->value()
                                    )
                            > :: type
                    > ||
                    ConstIterable <
                            typename std::remove_reference <
                                    decltype (
                                    dataTypes::unsafeAddress <
                                            typename returnOf < Transformer > :: Iterator
                                    >()->value()
                                    )
                            > :: type
                    >
            )
    );

    template < typename IndexedTransformer >
    [[maybe_unused]] auto flatMapIndexedTo (
            Collection <
                    typename std::remove_reference <
                            decltype (
                            dataTypes::unsafeAddress <
                                    typename returnOf < IndexedTransformer > :: Iterator
                            >()->value()
                            )
                    > :: type
            >                        &,
            IndexedTransformer const &
    ) const noexcept -> Collection <
            typename std::remove_reference <
                    decltype (
                    dataTypes::unsafeAddress <
                            typename returnOf < IndexedTransformer > :: Iterator
                    >()->value()
                    )
            > :: type
    > & REQUIRES (
            (Iterable < C > || ConstIterable < C >) && (
                    Iterable <
                            typename std::remove_reference <
                                    decltype (
                                    dataTypes::unsafeAddress <
                                            typename returnOf < IndexedTransformer > :: Iterator
                                    >()->value()
                                    )
                            > :: type
                    > ||
                    ConstIterable <
                            typename std::remove_reference <
                                    decltype (
                                    dataTypes::unsafeAddress <
                                            typename returnOf < IndexedTransformer > :: Iterator
                                    >()->value()
                                    )
                            > :: type
                    >
            )
    );

    template < typename KeySelector >
    [[maybe_unused]] auto groupBy (
            KeySelector const &
    ) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename ValueMapper >
    [[maybe_unused]] auto groupBy (
            KeySelector const &,
            ValueMapper const &
    ) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector >
    [[maybe_unused]] auto groupByTo (
            Map < returnOf < KeySelector >, LinkedList < ElementType > >          &,
            KeySelector                                                     const &
    ) const noexcept -> Map < returnOf < KeySelector >, LinkedList < ElementType > > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename ValueMapper >
    [[maybe_unused]] auto groupByTo (
            Map < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > >         &,
            KeySelector                                                                 const &,
            ValueMapper                                                                 const &
    ) const noexcept -> Map < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    /**
     * Two versions of map, one for storage of mappers when keeping same type, another for switching to another data type
     */

    template <
            typename Mapper,
            typename std::enable_if <
#if !defined(_MSC_VER)
                    ! std::is_same_v <
                            ElementType,
                            returnOf < Mapper >
                    >,
#else
                    ! std::is_same_v <
                typename std::remove_reference <
                    decltype (
                        dataTypes::unsafeAddress <
                            typename std::remove_reference<C>::type::Iterator
                        > ()->value()
                    )
                > :: type,
                returnOf < Mapper >
            >,
#endif
                    int
            >::type = 0
    >
    [[maybe_unused]] auto map (
            Mapper const &
    ) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
            typename Mapper,
            typename std::enable_if <
#if !defined(_MSC_VER)
                    std::is_same <
                            ElementType,
                            returnOf < Mapper >
                    >::type::value,
#else
                    std::is_same <
                typename std::remove_reference <
                    decltype (
                        dataTypes::unsafeAddress <
                            typename std::remove_reference<C>::type::Iterator
                        > ()->value()
                    )
                > :: type,
                returnOf < Mapper >
            >::type::value,
#endif
                    int
            >::type = 0
    >
    [[maybe_unused]] auto map (
            Mapper const &
    ) && noexcept -> Sequence < C >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
            typename IndexedMapper,
            typename std::enable_if <
#if !defined(_MSC_VER)
                    ! std::is_same_v <
                            ElementType,
                            returnOf < IndexedMapper >
                    >,
#else
                    ! std::is_same_v <
                typename std::remove_reference <
                    decltype (
                        dataTypes::unsafeAddress <
                            typename std::remove_reference<C>::type::Iterator
                        > ()->value()
                    )
                > :: type,
                returnOf < IndexedMapper >
            >,
#endif
                    int
            >::type = 0
    >
    [[maybe_unused]] auto mapIndexed (
            IndexedMapper const &
    ) && noexcept -> Sequence < LinkedList < returnOf < IndexedMapper > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
            typename IndexedMapper,
            typename std::enable_if <
#if !defined(_MSC_VER)
                    std::is_same <
                            ElementType,
                            returnOf < IndexedMapper >
                    >::type::value,
#else
                    std::is_same <
                typename std::remove_reference <
                    decltype (
                        dataTypes::unsafeAddress <
                            typename std::remove_reference<C>::type::Iterator
                        > ()->value()
                    )
                > :: type,
                returnOf < IndexedMapper >
            >::type::value,
#endif
                    int
            >::type = 0
    >
    [[maybe_unused]] auto mapIndexed (
            IndexedMapper const &
    ) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Mapper, typename R >
    [[maybe_unused]] auto mapTo (
            Collection < R >          &,
            Mapper              const &
    ) const noexcept -> Collection < R > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedMapper, typename R >
    [[maybe_unused]] auto mapIndexedTo (
            Collection < R >          &,
            IndexedMapper       const &
    ) const noexcept -> Collection < R > &
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > ) {

        LinkedList < Pair < Index, ElementType > > container;
        Index i = 0;
        for ( auto e : * this )
            container.add ( { i++, e } );

        return std::move ( Sequence < LinkedList < Pair < Index, ElementType > > > ( std::move ( container ) ) );
    }

    [[maybe_unused]] auto distinct () && noexcept -> Sequence < UnorderedSet < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    [[maybe_unused]] auto forEach ( Action const & ) const noexcept -> void
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAction >
    [[maybe_unused]] auto forEachIndexed ( IndexedAction const & ) const noexcept -> void
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    [[maybe_unused]] auto onEach ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAction >
    [[maybe_unused]] auto onEachIndexed (
            IndexedAction const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

#if defined(_MSC_VER)
    #pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#endif

    template < typename Comparator = std::function < bool (ElementType const &, ElementType const &) > >
    [[maybe_unused]] auto max (
            Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
    ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto maxBy ( Selector const & ) const noexcept -> Optional < ElementType >
    REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            TypeLessComparable < returnOf < Selector > >
    );

    template < typename Comparator = std::function < bool (ElementType const &, ElementType const &) > >
    [[maybe_unused]] auto maxOr (
            ElementType const &,
            Comparator  const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
    ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto maxByOr (
            ElementType const &,
            Selector    const &
    ) const noexcept -> ElementType REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            TypeLessComparable < returnOf < Selector > >
    );

    template < typename Comparator = std::function < bool (ElementType const &, ElementType const &) > >
    [[maybe_unused]] auto min (
            Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
    ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto minBy (
            Selector const &
    ) const noexcept -> Optional < ElementType > REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            TypeLessComparable < returnOf < Selector > >
    );

    template < typename Comparator = std::function < bool (ElementType const &, ElementType const &) > >
    [[maybe_unused]] auto minOr (
            ElementType const &,
            Comparator  const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
    ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    [[maybe_unused]] auto minByOr (
            ElementType const &,
            Selector    const &
    ) const noexcept -> ElementType REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            TypeLessComparable < returnOf < Selector > >
    );

#if defined(_MSC_VER)
    #pragma pop_macro("max")
#pragma pop_macro("min")
#endif

    template < typename Accumulator, typename AccumulatedType >
    [[maybe_unused]] auto fold (
            AccumulatedType const &,
            Accumulator     const &
    ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    [[maybe_unused]] auto foldIndexed (
            AccumulatedType     const &,
            IndexedAccumulator  const &
    ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator, typename AccumulatedType >
    [[maybe_unused]] auto runningFold (
            AccumulatedType const &,
            Accumulator     const &
    ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    [[maybe_unused]] auto runningFoldIndexed (
            AccumulatedType     const &,
            IndexedAccumulator  const &
    ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator >
    [[maybe_unused]] auto reduce (
            Accumulator const &
    ) const noexcept -> returnOf < Accumulator >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator >
    [[maybe_unused]] auto reduceIndexed (
            IndexedAccumulator const &
    ) const noexcept -> returnOf < IndexedAccumulator >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator >
    [[maybe_unused]] auto runningReduce (
            Accumulator const &
    ) && noexcept -> Sequence < LinkedList < returnOf < Accumulator > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator >
    [[maybe_unused]] auto runningReduceIndexed (
            IndexedAccumulator const &
    ) && noexcept -> Sequence < LinkedList < returnOf < IndexedAccumulator > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator, typename AccumulatedType >
    [[maybe_unused]] auto scan (
            AccumulatedType const &,
            Accumulator     const &
    ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    [[maybe_unused]] auto scanIndexed (
            AccumulatedType     const &,
            IndexedAccumulator  const &
    ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Selector >
    [[maybe_unused]] auto sumBy ( Selector const & ) const noexcept -> returnOf < Selector >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto chunked (Size) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ListTransformer >
    [[maybe_unused]] auto chunked (
            Size,
            ListTransformer const &
    ) && noexcept -> Sequence < LinkedList < returnOf < ListTransformer > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );


    [[maybe_unused]] auto minus (
            ElementType const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto minus (
            Collection < ElementType > const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

#define COMMA ,
    template < typename OC >
    [[maybe_unused]] auto minus (
            Sequence < OC > const &
    ) && noexcept -> Sequence < LinkedList < typename Sequence < C > :: ElementType > >
    REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            (Iterable < OC > || ConstIterable < OC >) &&
            EqualsComparable < ElementType COMMA typename Sequence < OC > :: ElementType >
    );
#undef COMMA

    [[maybe_unused]] auto plus (
            ElementType const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto plus (
            Collection < ElementType > const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename OC >
    [[maybe_unused]] auto plus (
            Sequence < OC > const &
    ) && noexcept -> Sequence < LinkedList < ElementType > >
    REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            (Iterable < OC > || ConstIterable < OC >)
    );


    template < typename Predicate >
    [[maybe_unused]] auto partition (
            Predicate const &
    ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    [[maybe_unused]] auto partitionIndexed (
            IndexedPredicate const &
    ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    [[maybe_unused]] auto windowed (
            Size,
            Size            = 1,
            Boolean const & = false
    ) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ListTransformer >
    [[maybe_unused]] auto windowed (
            ListTransformer const &,
            Size,
            Size                    = 1,
            Boolean         const & = false
    ) && noexcept -> Sequence < LinkedList < returnOf < ListTransformer > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename OC >
    [[maybe_unused]] auto zip (
            Sequence < OC > const &
    ) && noexcept -> Sequence < LinkedList < Pair < ElementType, typename Sequence < OC > :: ElementType > > >
    REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            (Iterable < OC > || ConstIterable < OC >)
    );

    template < typename OC, typename Transformer >
    [[maybe_unused]] auto zip (
            Sequence < OC > const &,
            Transformer     const &
    ) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
    REQUIRES (
            (Iterable < C > || ConstIterable < C >) &&
            (Iterable < OC > || ConstIterable < OC >)
    );

    [[maybe_unused]] auto zipWithNext () && noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Transformer >
    [[maybe_unused]] auto zipWithNext (
            Transformer const &
    ) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
    REQUIRES ( Iterable < C > || ConstIterable < C > );
};

/// region Ctors Dtors Copy Move Clear
template < typename C >
inline Sequence < C > ::Sequence ( Sequence const & s ) noexcept :
        pCollection ( new ForeignPointer ( s.pCollection.valueAt().get() ) ),
        chainCount ( s.chainCount ),
        storedMappers ( s.storedMappers ),
        storedPredicates ( s.storedPredicates ),
        storedIndexedMappers ( s.storedIndexedMappers ),
        storedIndexedPredicates ( s.storedIndexedPredicates ){

}

template < typename C >
inline Sequence < C > ::Sequence ( Sequence && s ) noexcept :
        chainCount ( std::exchange ( s.chainCount, 0 ) + 1 ),
        storedMappers ( std::move ( s.storedMappers ) ),
        storedPredicates ( std::move ( s.storedPredicates ) ),
        storedIndexedMappers ( std::move ( s.storedIndexedMappers ) ),
        storedIndexedPredicates ( std::move ( s.storedIndexedPredicates ) ) {
    if ( dynamic_cast < UniquePointer < C > * > ( s.pCollection.get() ) != nullptr )
        this->pCollection = new UniquePointer ( s.pCollection.valueAt().release() );
    else
        this->pCollection = new ForeignPointer ( s.pCollection.valueAt().get() );
}

template < typename C >
inline Sequence < C > ::Sequence ( C & c ) noexcept :
        pCollection ( new ForeignPointer ( & c ) ),
        chainCount ( 0u ) {

}

template < typename C >
inline Sequence < C > ::Sequence ( C && c ) noexcept :
        pCollection ( new UniquePointer ( new C (std::move(c)) ) ),
        chainCount ( 0u ) {

}

template < typename C >
inline auto Sequence < C > ::operator = ( Sequence const & s ) noexcept -> Sequence & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( new ForeignPointer ( s.pCollection.valueAt().valueAt() ) );
    this->chainCount                = s.chainCount;

    this->storedMappers             = s.storedMappers;
    this->storedPredicates          = s.storedPredicates;

    this->storedIndexedMappers      = s.storedIndexedMappers;
    this->storedIndexedPredicates   = s.storedIndexedPredicates;

    return * this;
}

template < typename C >
inline auto Sequence < C > ::operator = ( Sequence && s ) noexcept -> Sequence & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( new UniquePointer ( s.pCollection.valueAt().release() ) );
    this->chainCount                = std::exchange ( s.chainCount, 0 ) + 1;

    this->storedMappers             = std::move (s.storedMappers);
    this->storedPredicates          = std::move (s.storedPredicates);

    this->storedIndexedMappers      = std::move (s.storedIndexedMappers);
    this->storedIndexedPredicates   = std::move (s.storedIndexedPredicates);

    return * this;
}

template < typename C >
inline auto Sequence < C > ::clear() noexcept -> void {
    this->pCollection.reset();
    this->chainCount = 0;

    this->storedMappers.clear();
    this->storedPredicates.clear();

    this->storedIndexedMappers.clear();
    this->storedIndexedPredicates.clear();
}

/// endregion

/// region Iterator Support

template < typename C >
inline auto Sequence < C > ::begin() noexcept -> Iterator {
    return Sequence::Iterator ( this, this->pCollection.valueAt().valueAt().begin() );
}

template < typename C >
inline auto Sequence < C > ::end() noexcept -> Iterator {
    return Sequence::Iterator ( this, this->pCollection.valueAt().valueAt().end() );
}

template < typename C >
inline Sequence < C >::Iterator::Iterator(Sequence < C > * pSequence, CollectionIterator const & it) noexcept :
        pSeq ( pSequence ),
        it (it) {
    this->skipFiltered();
}

template < typename C >
auto Sequence < C >::Iterator::skipFiltered() noexcept -> void {
    Boolean skip = true;

    while ( skip && this->it != this->pSeq->pCollection->valueAt().end() ) {
        this->precomputed = this->it.value();
        skip = false;

        auto currentMapperIterator = this->pSeq.valueAt().storedMappers.begin();
        auto currentFilterIterator = this->pSeq.valueAt().storedPredicates.begin();

        auto currentIndexedMapperIterator = this->pSeq.valueAt().storedIndexedMappers.begin();
        auto currentIndexedFilterIterator = this->pSeq.valueAt().storedIndexedPredicates.begin();

        for ( uint32 i = 0; i < this->pSeq.valueAt().chainCount; i ++ ) {

            if (
                    currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                    currentMapperIterator.value().getSecond() == i
                    ) {
                this->precomputed = ( * currentMapperIterator.value().getFirst() ) ( this->precomputed );
                currentMapperIterator.next();

            } else if (
                    currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                    currentIndexedMapperIterator.value().getSecond() == i
                    ) {
                this->precomputed = ( * currentIndexedMapperIterator.value().getFirst() ) (
                        this->index,
                        this->precomputed
                );

                currentIndexedMapperIterator.next();

            } else if (
                    currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() &&
                    currentFilterIterator.value().getSecond() == i
                    ) {
                if ( ! (* currentFilterIterator.value().getFirst())( this->precomputed ) ) {
                    skip = true;
                    break;
                }
                currentFilterIterator.next();

            } else if (
                    currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() &&
                    currentIndexedFilterIterator.value().getSecond() == i
                    ) {
                if ( ! (* currentIndexedFilterIterator.value().getFirst()) (this->index, this->precomputed) ) {
                    skip = true;
                    break;
                }
                currentIndexedFilterIterator.next();

            } else if (
                    currentFilterIterator           == this->pSeq.valueAt().storedPredicates.end()      &&
                    currentMapperIterator           == this->pSeq.valueAt().storedMappers.end()         &&
                    currentIndexedMapperIterator    == this->pSeq.valueAt().storedIndexedMappers.end()  &&
                    currentIndexedFilterIterator    == this->pSeq.valueAt().storedIndexedPredicates.end()
                    )
                break;
        }

        if ( ! skip ) {

            for ( Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if (
                        currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                        currentMapperIterator.value().getSecond() == i
                        ) {
                    this->precomputed = (* currentMapperIterator.value().getFirst())(this->precomputed);
                    currentMapperIterator.next();
                } else if (
                        currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                        currentIndexedMapperIterator.value().getSecond() == i
                        ) {
                    this->precomputed = (* currentIndexedMapperIterator.value().getFirst())(
                            this->index,
                            this->precomputed
                    );
                    currentIndexedMapperIterator.next();
                }
            }

        }
        else {
            this->it.next();
        }

        this->index ++;
    }
}

#include <sstream>

template < typename C >
auto Sequence < C > ::Iterator::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString();

    if constexpr ( isPrintable < decltype ( this->it ) >::value ) {
        oss << ", it = " << this->it;
    } else {
        oss << ", value = " << * this->it;
    }

    oss << " }";
    return oss.str();
}

template < typename C >
inline auto Sequence < C > ::Iterator::hash() const noexcept -> Index {
    if constexpr( isObjectDerived < decltype ( this->it ) > ::value )
        return this->it.hash ();
    else if constexpr ( isObjectDerived < decltype ( * this->it ) > ::value )
        return (* this->it).hash ();
    else
        return 0;

}

template < typename C >
inline auto Sequence < C > ::Iterator::copy() const noexcept -> Iterator * {
    return new Iterator (* this);
}

template < typename C >
inline auto Sequence < C > ::Iterator::equals(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
inline auto Sequence < C > ::Iterator::value() const noexcept -> CollectionElementType {
    return this->precomputed;
}

template < typename C >
inline auto Sequence < C > ::Iterator::next() noexcept -> Iterator & {
    this->it.next();
    this->skipFiltered();
    return * this;
}

template < typename C >
inline auto Sequence < C > ::Iterator::equals(Iterator const & otherIt) const noexcept -> Boolean {
    return this->it == otherIt.it;
}

template < typename C >
inline auto Sequence < C > ::Iterator::operator==(Iterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename C >
inline auto Sequence < C > ::Iterator::operator!=(Iterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename C >
inline auto Sequence < C > ::Iterator::operator++() noexcept -> Iterator & {
    return this->next();
}

template < typename C >
inline auto Sequence < C > ::Iterator::operator++(int) noexcept -> Iterator {
    auto c = * this; this->next(); return c;
}

template < typename C >
inline auto Sequence < C > ::Iterator::operator*() const noexcept -> CollectionElementType {
    return this->value();
}

template < typename C >
inline auto Sequence < C > ::begin() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename C >
inline auto Sequence < C > ::end() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename C >
inline auto Sequence < C > ::cbegin() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename C >
inline auto Sequence < C > ::cend() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename C >
inline Sequence < C >::ConstIterator::ConstIterator(
        Sequence < C >      const * pSequence,
        CollectionIterator  const & it
) noexcept :
        pSeq ( pSequence ),
        it (it) {
    this->skipFiltered();
}

template < typename C >
auto Sequence < C >::ConstIterator::skipFiltered() noexcept -> void {
    Boolean skip = true;

    while ( skip && this->it != this->pSeq->pCollection->valueAt().cend() ) {
        this->precomputed = this->it.value();
        skip = false;

        auto currentMapperIterator = this->pSeq.valueAt().storedMappers.begin();
        auto currentFilterIterator = this->pSeq.valueAt().storedPredicates.begin();

        auto currentIndexedMapperIterator = this->pSeq.valueAt().storedIndexedMappers.begin();
        auto currentIndexedFilterIterator = this->pSeq.valueAt().storedIndexedPredicates.begin();

        for ( uint32 i = 0; i < this->pSeq.valueAt().chainCount; i ++ ) {

            if (
                    currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                    currentMapperIterator.value().getSecond() == i
                    ) {
                this->precomputed = ( * currentMapperIterator.value().getFirst() ) ( this->precomputed );
                currentMapperIterator.next();

            } else if (
                    currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                    currentIndexedMapperIterator.value().getSecond() == i
                    ) {
                this->precomputed = ( * currentIndexedMapperIterator.value().getFirst() ) (
                        this->index,
                        this->precomputed
                );

                currentIndexedMapperIterator.next();

            } else if (
                    currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() &&
                    currentFilterIterator.value().getSecond() == i
                    ) {
                if ( ! (* currentFilterIterator.value().getFirst())( this->precomputed ) ) {
                    skip = true;
                    break;
                }
                currentFilterIterator.next();

            } else if (
                    currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() &&
                    currentFilterIterator.value().getSecond() == i
                    ) {
                if ( ! (* currentIndexedFilterIterator.value().getFirst()) (this->index, this->precomputed) ) {
                    skip = true;
                    break;
                }
                currentIndexedFilterIterator.next();

            } else if (
                    currentFilterIterator           == this->pSeq.valueAt().storedPredicates.end()      &&
                    currentMapperIterator           == this->pSeq.valueAt().storedMappers.end()         &&
                    currentIndexedMapperIterator    == this->pSeq.valueAt().storedIndexedMappers.end()  &&
                    currentIndexedFilterIterator    == this->pSeq.valueAt().storedIndexedPredicates.end()
                    )
                break;
        }

        if ( ! skip ) {

            for ( Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if (
                        currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                        currentMapperIterator.value().getSecond() == i
                        ) {
                    this->precomputed = (* currentMapperIterator.value().getFirst())(this->precomputed);
                    currentMapperIterator.next();
                } else if (
                        currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                        currentIndexedMapperIterator.value().getSecond() == i
                        ) {
                    this->precomputed = (* currentIndexedMapperIterator.value().getFirst())(
                            this->index,
                            this->precomputed
                    );
                    currentIndexedMapperIterator.next();
                }
            }

        }
        else {
            this->it.next();
        }

        this->index ++;
    }
}

#include <sstream>

template < typename C >
auto Sequence < C > ::ConstIterator::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString();

    if constexpr ( isPrintable < decltype ( this->it ) >::value ) {
        oss << ", it = " << this->it;
    } else {
        oss << ", value = " << * this->it;
    }

    oss << " }";
    return oss.str();
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::hash() const noexcept -> Index {
    if constexpr( isObjectDerived < decltype ( this->it ) > ::value )
        return this->it.hash ();
    else if constexpr ( isObjectDerived < decltype ( * this->it ) > ::value )
        return (* this->it).hash ();
    else
        return 0;

}

template < typename C >
inline auto Sequence < C > ::ConstIterator::copy() const noexcept -> ConstIterator * {
    return new ConstIterator (* this);
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::equals(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::value() const noexcept -> CollectionElementType {
    return this->precomputed;
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::next() noexcept -> ConstIterator & {
    this->it.next();
    this->skipFiltered();
    return * this;
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::equals(ConstIterator const & otherIt) const noexcept -> Boolean {
    return this->it == otherIt.it;
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::operator==(ConstIterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::operator!=(ConstIterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::operator++() noexcept -> ConstIterator & {
    return this->next();
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::operator++(int) noexcept -> ConstIterator {
    auto c = * this; this->next(); return c;
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::operator*() const noexcept -> CollectionElementType {
    return this->value();
}

/// endregion

/// region Object Derived Functions

template < typename C >
auto Sequence < C > ::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "Sequence { chainCount = "
        << this->chainCount
        << ", elements = [ ";

    for ( auto e : * this )
        if constexpr ( isPrintable < ElementType >::value )
            oss << e << ", ";
        else
            oss << "Object at 0x" << std::hex << reinterpret_cast < AddressValueType > ( & e ) << ", ";

    auto s = oss.str();
    return s.replace(s.size() - 2, 2, "").append(" ]}");
}

template < typename C >
inline auto Sequence < C > ::hash() const noexcept -> Index {
    return this->pCollection.valueAt().hash();
}

template < typename C >
inline auto Sequence < C > ::copy() const noexcept -> Sequence<C> * {
    return new Sequence ( * this );
}

template < typename C >
inline auto Sequence < C > ::equals(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > (& o);
    if ( p == nullptr ) return false;

    return this->pCollection == p->pCollection;
}


/// endregion

/// region template deduction

Sequence ( String ) -> Sequence < String >;

template < typename T>
Sequence ( Array < T > & ) -> Sequence < Array < T > >;

template < typename T>
Sequence ( Array < T > const & ) -> Sequence < Array < T > const >;

template < typename T>
Sequence ( Array < T > && ) -> Sequence < Array < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > & ) -> Sequence < DoubleLinkedList < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > const & ) -> Sequence < DoubleLinkedList < T > const >;

template < typename T >
Sequence ( DoubleLinkedList < T > && ) -> Sequence < DoubleLinkedList < T > >;

template < typename T >
Sequence ( OrderedSet < T > & ) -> Sequence < OrderedSet < T > >;

template < typename T >
Sequence ( OrderedSet < T > const & ) -> Sequence < OrderedSet < T > const >;

template < typename T >
Sequence ( OrderedSet < T > && ) -> Sequence < OrderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > & ) -> Sequence < UnorderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > const & ) -> Sequence < UnorderedSet < T > const >;

template < typename T >
Sequence ( UnorderedSet < T > && ) -> Sequence < UnorderedSet < T > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > & ) -> Sequence < HashMap < K, V > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > const & ) -> Sequence < HashMap < K, V > const >;

template < typename K, typename V >
Sequence ( HashMap < K, V > && ) -> Sequence < HashMap < K, V > >;

//#include <CDS/JSON>

class JSON;
Sequence ( JSON const & ) -> Sequence < JSON const >;

#include <CDS/Generator>
template < typename T, typename ... Args >
Sequence ( Generator < T, Args ... > const & ) -> Sequence < Generator < T, Args ... > const >;

#include <CDS/Range>
Sequence ( Range && ) -> Sequence < Range >;

#include <CDS/Range>
Sequence ( Range const & ) -> Sequence < Range const >;

#include <CDS/Range>
Sequence ( Range & ) -> Sequence < Range >;

/// endregion

/// region Sequence Transformer/Ownership Pass Functions

template < typename C >
template <
        typename Mapper,
        typename std::enable_if <
                ! std::is_same_v <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename std::remove_reference<C>::type::Iterator
                                > ()->value()
                                )
                        > :: type,
                        returnOf < Mapper >
                >,
                int
        >::type
>
[[maybe_unused]] inline auto Sequence < C > :: map (
        Mapper const & mapper
) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < returnOf < Mapper > > container;
    for ( auto e : * this )
        container.append(mapper(e));

    return std::move(Sequence < LinkedList < returnOf < Mapper > > > (std::move(container)));
}

template < typename C >
template < typename Mapper,
        typename std::enable_if <
                std::is_same <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename std::remove_reference<C>::type::Iterator
                                > ()->value()
                                )
                        > :: type,
                        returnOf < Mapper >
                >::type::value,
                int
        >::type
>
[[maybe_unused]] inline auto Sequence < C > ::map(
        Mapper const & mapper
) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedMappers.append({ { new StoredMapper(mapper) }, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > ::filter(
        Predicate const & predicate
) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedPredicates.append({ { new StoredPredicate (predicate)}, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename IndexedPredicate >
[[maybe_unused]] inline auto Sequence < C > :: filterIndexed (
        IndexedPredicate const & indexedPredicate
) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedIndexedPredicates.append({ { new StoredIndexedPredicate (indexedPredicate)}, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template <
        typename IndexedMapper,
        typename std::enable_if <
                ! std::is_same_v <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename std::remove_reference<C>::type::Iterator
                                > ()->value()
                                )
                        > :: type,
                        returnOf < IndexedMapper >
                >,
                int
        >::type
>
[[maybe_unused]] inline auto Sequence < C > :: mapIndexed (
        IndexedMapper const & mapper
) && noexcept -> Sequence < LinkedList < returnOf < IndexedMapper > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < returnOf < IndexedMapper > > container;
    Index i = 0;
    for ( auto e : * this )
        container.append(mapper(i++, e));

    return std::move(Sequence < LinkedList < returnOf < IndexedMapper > > > (std::move(container)));
}

template < typename C >
template < typename IndexedMapper,
        typename std::enable_if <
                std::is_same <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename std::remove_reference<C>::type::Iterator
                                > ()->value()
                                )
                        > :: type,
                        returnOf < IndexedMapper >
                >::type::value,
                int
        >::type
>
[[maybe_unused]] inline auto Sequence < C > ::mapIndexed(
        IndexedMapper const & mapper
) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedIndexedMappers.append({ { new StoredIndexedMapper(mapper) }, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: takeWhile (
        Predicate const & predicate,
        Size count
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > remaining;

    Index i = 0;

    for ( auto e : * this ) {
        if ( i < count && predicate ( e ) ) {
            remaining.append(e);
            i++;
            continue;
        }
        break;
    }

    return std::move ( Sequence < LinkedList < ElementType > > ( std::move ( remaining ) ) );
}

template < typename C >
template < typename NewType >
[[maybe_unused]] inline auto Sequence < C > :: filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > >
REQUIRES(
        ( Iterable < C > || ConstIterable < C > ) &&
        Pointer < ElementType > &&
        Pointer < NewType >
) {

    LinkedList < NewType > container;
    for ( auto e : * this ) {
        auto p = dynamic_cast < NewType > (e);
        if ( p != nullptr )
            container.add(p);
    }

    return std::move ( Sequence < LinkedList < NewType > > ( std::move ( container ) ) );
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: filterNot (
        Predicate const & predicate
) && noexcept -> Sequence REQUIRES( Iterable < C > || ConstIterable < C > ) {
    return this->filter( [& predicate] (ElementType e) noexcept -> bool { return ! predicate(e); } );
}

template < typename C >
template < typename IndexedPredicate >
[[maybe_unused]] inline auto Sequence < C > :: filterNotIndexed(
        IndexedPredicate const & indexedPredicate
) && noexcept -> Sequence REQUIRES( Iterable < C > || ConstIterable < C > ) {
    return this->filterIndexed( [& indexedPredicate] (Index index, ElementType e) noexcept -> bool {
        return ! indexedPredicate ( index, e );
    });
}

template < typename C >
template <
        typename Transformer,
        typename std::enable_if <
                isPair < returnOf < Transformer > > :: value,
                int
        > :: type
>
[[maybe_unused]] inline auto Sequence < C > :: associate(
        Transformer const & transformer
) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) &&
        PairType < returnOf < Transformer > >
) {
    LinkedList < returnOf < Transformer > > container;
    for ( auto e : * this )
        container.add ( transformer ( e ) );

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename KeyGenerator >
[[maybe_unused]] inline auto Sequence < C > :: associateBy (
        KeyGenerator const & keyGenerator
) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > container;
    for ( auto e : * this )
        container.add ( { keyGenerator ( e ), e } );

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename KeyGenerator, typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: associateBy (
        KeyGenerator    const & keyGenerator,
        ValueMapper     const & valueMapper
) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, returnOf < ValueMapper > > > >
REQUIRES(Iterable < C > || ConstIterable < C >) {
    LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > container;
    for ( auto e : * this )
        container.add( { keyGenerator ( e ), valueMapper ( e ) } );

    return std::move ( Sequence < decltype ( container ) > (std::move( container )) );
}

template < typename C >
template < typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: associateWith (
        ValueMapper const & mapper
) && noexcept -> Sequence < LinkedList < Pair < ElementType, returnOf < ValueMapper > > > >
REQUIRES(Iterable < C > || ConstIterable < C >) {

    LinkedList < Pair < ElementType, returnOf < ValueMapper > > > container;
    for ( auto e : * this )
        container.add( { e, mapper(e) } );

    return std::move ( Sequence < decltype ( container ) > (std::move(container)) );
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: sorted (
        Comparator const & comparator
) && noexcept -> Sequence < Array < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Array < ElementType > container;
    for ( auto e: * this )
        container.add(e);

    container.shrinkToSize(container.size());
    container.sort(comparator);

    return std::move ( Sequence < Array < ElementType > > (std::move(container)) );
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: sortedBy (
        Selector const & selector
) && noexcept -> Sequence < Array < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
        return selector(a) < selector(b);
    });
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: sortedByDescending (
        Selector const & selector
) && noexcept -> Sequence < Array < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
        return selector(a) > selector(b);
    });
}

template < typename C >
template < typename Selector, typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: sortedByWith (
        Selector    const & selector,
        Comparator  const & comparator
) && noexcept -> Sequence < Array < ElementType > > REQUIRES (Iterable<C> || ConstIterable<C>) {
    return this->sorted([& selector, & comparator](ElementType const & a, ElementType const & b){
        return comparator(selector(a), selector(b));
    });
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: distinct () && noexcept -> Sequence < UnorderedSet < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    UnorderedSet < ElementType > container;
    for ( auto e : * this )
        container.add ( e );
    return std::move ( Sequence < decltype (container) > ( std::move ( container ) ) );
}

/// endregion

// region Basic Utility Functions

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::contains(
        ElementType const & e
) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto v : * this )
        if ( e == v )
            return true;
    return false;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::elementAt(
        Index i
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index at = 0;
    for ( auto v : * this )
        if ( at == i )
            return { v };
        else
            at ++;

    return { };
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::elementAtOr(
        Index i,
        ElementType const & e
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index at = 0;
    for ( auto v : * this )
        if ( at == i )
            return v;
        else
            at ++;

    return e;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::indexOf(
        ElementType const & e
) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto v : * this )
        if ( v == e )
            return i;
        else
            i++;

    return -1;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::lastIndexOf(
        ElementType const & e
) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0, last = -1;
    for ( auto v : * this ) {
        if (v == e)
            last = i;
        i++;
    }

    return last;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::indicesOf (
        ElementType const & e
) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    LinkedList < Index > result;
    Index i = 0;
    for ( auto v : * this ) {
        if (e == v)
            result.append(i);
        i++;
    }

    return result;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: find (
        Predicate const & predicate
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->first(predicate);
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: first (
        Predicate const & predicate
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return { e };
    return { };
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: firstOr (
        ElementType const & e,
        Predicate   const & predicate
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto v : * this )
        if ( predicate (v) )
            return v;
    return e;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > ::findLast (
        Predicate const & predicate
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->last(predicate);
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: last (
        Predicate const & predicate
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    ElementType v;
    Boolean found = false;
    for ( auto e : * this )
        if ( predicate(e) ) {
            found = true;
            v = e;
        }

    if ( found )
        return { v };
    return { };
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: lastOr (
        ElementType const & r,
        Predicate   const & predicate
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    ElementType v;
    Boolean found = false;
    for ( auto e : * this )
        if ( predicate(e) ) {
            found = true;
            v = e;
        }

    if ( found )
        return v;
    return r;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: single () const noexcept -> Optional < ElementType >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    if ( this->pCollection.valueAt().valueAt().size() != 1 )
        return { };
    return this->begin().value();
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: singleOr (ElementType const & v) const noexcept -> ElementType
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    if ( this->pCollection.valueAt().valueAt().size() != 1 )
        return v;
    return this->begin().value();
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: single (
        Predicate const & predicate
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    ElementType v;
    Boolean found = false;
    for ( auto e : * this )
        if ( predicate ( e ) ) {
            if (!found) {
                found = true;
                v = e;
            } else {
                return { };
            }
        }

    if ( found ) return { v };
    return { };
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: singleOr (
        ElementType const & r,
        Predicate   const & predicate
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    ElementType v;
    Boolean found = false;
    for ( auto e : * this )
        if ( predicate ( e ) ) {
            if (!found) {
                found = true;
                v = e;
            } else {
                return r;
            }
        }

    if ( found ) return v;
    return r;
}

template < typename C >
template < typename Transformer >
[[maybe_unused]] inline auto Sequence < C > :: flatMap (
        Transformer const & transformer
) && noexcept -> Sequence <
        LinkedList <
                typename std::remove_reference <
                        decltype (
                        dataTypes::unsafeAddress <
                                typename returnOf < Transformer > :: Iterator
                        >()->value()
                        )
                >::type
        >
> REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) &&
        ( Iterable < returnOf < Transformer > > || ConstIterable < returnOf < Transformer > > )
) {

    LinkedList <
            typename std::remove_reference <
                    decltype (
                    dataTypes::unsafeAddress <
                            typename returnOf < Transformer >:: Iterator
                    >()->value ()
                    )
            > :: type
    > container;

    for ( auto e : * this )
        for ( auto const & s : transformer(e) )
            container.add( s );
    return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
}

template < typename C >
template < typename IndexedTransformer >
[[maybe_unused]] inline auto Sequence < C > :: flatMapIndexed (
        IndexedTransformer const & transformer
) && noexcept -> Sequence <
        LinkedList <
                typename std::remove_reference <
                        decltype (
                        dataTypes::unsafeAddress <
                                typename returnOf < IndexedTransformer > :: Iterator
                        >()->value()
                        )
                >::type
        >
> REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) && (
                Iterable < returnOf < IndexedTransformer > > ||
                ConstIterable < returnOf < IndexedTransformer > >
        )
) {
    LinkedList <
            typename std::remove_reference <
                    decltype (
                    dataTypes::unsafeAddress <
                            typename returnOf < IndexedTransformer >:: Iterator
                    >()->value ()
                    )
            > :: type
    > container;

    Index i = 0;

    for ( auto e : * this )
        for ( auto const & s : transformer(i ++, e) )
            container.add( s );
    return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
}

template < typename C >
template < typename KeySelector >
[[maybe_unused]] inline auto Sequence < C > :: groupBy (
        KeySelector const & keySelector
) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < ElementType > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    HashMap < returnOf < KeySelector >, LinkedList < ElementType > > container;

    for ( auto e : * this ) {
        auto k = keySelector ( e );
        if ( container.containsKey(k) )
            container[k].add(e);
        else
            container[k] = { e };
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename KeySelector, typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: groupBy (
        KeySelector const & keySelector,
        ValueMapper const & valueMapper
) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    HashMap < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > container;

    for ( auto e : * this ) {
        auto k = keySelector ( e ); auto v = valueMapper ( e );
        if ( container.containsKey( k ) )
            container[k].add(v);
        else
            container[k] = {v};
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename KeySelector >
[[maybe_unused]] inline auto Sequence < C > :: groupByTo (
        Map < returnOf < KeySelector >, LinkedList < ElementType > >          & map,
        KeySelector                                                     const & keySelector
) const noexcept -> Map < returnOf < KeySelector >, LinkedList < ElementType > > &
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    for ( auto e : * this ) {
        auto k = keySelector ( e );
        if ( map.containsKey( k ) )
            map[k].add ( e );
        else
            map[k] = { e };
    }

    return map;
}

template < typename C >
template < typename KeySelector, typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: groupByTo (
        Map < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > >         & map,
        KeySelector                                                                 const & keySelector,
        ValueMapper                                                                 const & valueMapper
) const noexcept -> Map < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > &
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    for ( auto e : * this ) {
        auto k = keySelector ( e ); auto v = valueMapper ( e );
        if ( map.containsKey( k ) )
            map[k].add ( v );
        else
            map[k] = { v };
    }

    return map;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: minus (
        ElementType const & toRemove
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;
    Boolean found = false;

    for ( auto e : * this )
        if ( found || e != toRemove )
            container.add( e );
        else
            found = true;

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: minus (
        Collection < ElementType > const & toRemove
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;

    for ( auto e : * this )
        if ( ! toRemove.contains(e) )
            container.add(e);

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

#define COMMA ,
template < typename C >
template < typename OC >
[[maybe_unused]] inline auto Sequence < C > :: minus (
        Sequence < OC > const & sequence
) && noexcept -> Sequence <
        LinkedList <
                typename Sequence < C > :: ElementType
        >
> REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        (Iterable < OC > || ConstIterable < OC >) &&
        EqualsComparable < ElementType COMMA typename Sequence < OC > :: ElementType >
) {

    LinkedList < ElementType > container;

    for ( auto e : * this ) {
        Boolean found = false;
        for (auto v : sequence)
            if ( v == e ) {
                found = true;
                break;
            }

        if ( ! found )
            container.add( e );
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}
#undef COMMA

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: plus (
        ElementType const & toAdd
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;

    for ( auto e : * this )
        container.add(e);

    container.add(toAdd);

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: plus (
        Collection < ElementType > const & toAdd
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;

    for ( auto e : * this )
        container.add(e);

    toAdd.forEach([& container](auto e){container.add(e);});

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename OC >
[[maybe_unused]] inline auto Sequence < C > :: plus (
        Sequence < OC > const & toAdd
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        (Iterable < OC > || ConstIterable < OC >)
) {

    LinkedList < ElementType > container;

    for ( auto e : * this )
        container.add(e);

    for ( auto e : toAdd )
        container.add(e);

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

// endregion

// region Terminal Operations

template < typename C >
template < typename Action >
[[maybe_unused]] inline auto Sequence < C > :: forEach (
        Action const & action
) const noexcept -> void REQUIRES (Iterable<C> || ConstIterable<C>) {
    for ( auto e : * this ) action (e);
}

template < typename C >
template < typename IndexedAction >
[[maybe_unused]] inline auto Sequence < C > :: forEachIndexed (
        IndexedAction const & indexedAction
) const noexcept -> void REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this ) indexedAction (i++, e);
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: filterTo (
        Collection < ElementType >        & collection,
        Predicate                   const & predicate
) const noexcept -> Collection < ElementType >
& REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    for ( auto e : * this )
        if ( predicate(e) )
            collection.add(e);

    return collection;
}

template < typename C >
template < typename IndexedPredicate >
[[maybe_unused]] inline auto Sequence < C > :: filterIndexedTo (
        Collection < ElementType >        & collection,
        IndexedPredicate            const & predicate
) const noexcept -> Collection < ElementType > &
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    Index i = 0;
    for ( auto e : * this )
        if ( predicate(i++, e) )
            collection.add(e);

    return collection;
}

template < typename C >
template < typename Mapper, typename R >
[[maybe_unused]] inline auto Sequence < C > :: mapTo (
        Collection < R >          & collection,
        Mapper              const & mapper
) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        collection.add ( mapper(e) );
    return collection;
}

template < typename C >
template < typename IndexedMapper, typename R >
[[maybe_unused]] inline auto Sequence < C > :: mapIndexedTo (
        Collection < R >          & collection,
        IndexedMapper       const & mapper
) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this )
        collection.add ( mapper(i++, e) );
    return collection;
}

template < typename C >
template < typename NewType >
[[maybe_unused]] inline auto Sequence < C > :: filterIsDerivedTo (
        Collection < ElementType > & collection
) const noexcept -> Collection < ElementType > &
REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) &&
        Pointer < ElementType > &&
        Pointer < NewType >
) {

    for ( auto e : * this ) {
        auto p = dynamic_cast < NewType > (e);
        if ( p != nullptr )
            collection.add(p);
    }

    return collection;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: filterNotTo (
        Collection < ElementType >        & collection,
        Predicate                   const & predicate
) const noexcept -> Collection < ElementType > & REQUIRES( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( ! predicate ( e ) )
            collection.add( e );

    return collection;
}

template < typename C >
template < typename IndexedPredicate >
[[maybe_unused]] inline auto Sequence < C > :: filterNotIndexedTo (
        Collection < ElementType >        & collection,
        IndexedPredicate            const & indexedPredicate
) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this )
        if ( ! indexedPredicate ( i++, e ) )
            collection.add ( e );

    return collection;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: indexOfFirst (
        Predicate const & predicate
) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this ) {
        if ( predicate (e) )
            return i;
        i++;
    }

    return -1;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: indexOfLast (
        Predicate const & predicate
) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    Index l = -1;
    for ( auto e : * this ) {
        if ( predicate (e) )
            l = i;
        i++;
    }

    return l;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: indicesOfAll (
        Predicate const & predicate
) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    LinkedList < Index > indices;
    for ( auto e : * this ) {
        if ( predicate( e ) )
            indices.add ( i );
        i++;
    }

    return indices;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: any (
        Predicate const & predicate
) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return true;
    return false;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: all (
        Predicate const & predicate
) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( ! predicate ( e ) )
            return false;

    return true;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: count (
        Predicate const & predicate
) const noexcept -> Size REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Size count = 0;
    for ( auto e : * this )
        if ( predicate ( e ) )
            count ++;

    return count;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: none (
        Predicate const & predicate
) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return false;
    return true;
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: one (
        Predicate const & predicate
) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Boolean found = false;

    for ( auto e : * this )
        if ( predicate ( e ) ) {
            if (!found)
                found = true;
            else
                return false;
        }

    return found;
}

template < typename C >
template < typename KeyGenerator >
[[maybe_unused]] inline auto Sequence < C > :: associateByTo (
        Map < returnOf < KeyGenerator >, ElementType >        & m,
        KeyGenerator                                    const & keyGenerator
) const noexcept -> Map < returnOf < KeyGenerator >, ElementType > &
REQUIRES(Iterable < C > || ConstIterable < C >) {

    for ( auto e : * this )
        m.add ( { keyGenerator (e), e } );
    return m;
}

template < typename C >
template < typename KeyGenerator, typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: associateByTo (
        Map < returnOf < KeyGenerator >, returnOf < ValueMapper > >       & m,
        KeyGenerator                                                const & keyGenerator,
        ValueMapper                                                 const & mapper
) const noexcept -> Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > &
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    for ( auto e : * this )
        m.add ( { keyGenerator (e), mapper(e) } );
    return m;
}

template < typename C >
template < typename Transformer, typename K, typename V >
[[maybe_unused]] inline auto Sequence < C > :: associateTo (
        Map < K, V >        & m,
        Transformer   const & t
) const noexcept -> Map < K, V > & REQUIRES( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        m.add ( t(e) );
    return m;
}

template < typename C >
template < typename ValueMapper >
[[maybe_unused]] inline auto Sequence < C > :: associateWithTo (
        Map < ElementType, returnOf < ValueMapper > >         & m,
        ValueMapper                                     const & mapper
) const noexcept -> Map < ElementType, returnOf < ValueMapper > > &
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    for ( auto e : * this )
        m.add ( { e, mapper(e) } );
    return m;
}

template < typename C >
template < typename Collection >
[[maybe_unused]] inline auto Sequence < C > :: toCollection () const noexcept -> Collection
REQUIRES(Iterable<C> || ConstIterable<C>) {

    Collection c;
    for ( auto e : * this )
        c.add(e);
    return c;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: toLinkedList () const noexcept -> LinkedList < ElementType >
REQUIRES (Iterable<C> || ConstIterable <C> ) {

    return this->toCollection<LinkedList<ElementType>>();
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: toArray () const noexcept -> Array < ElementType >
REQUIRES (Iterable<C> || ConstIterable <C> ) {

    return this->toCollection<Array<ElementType>>();
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: toOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator >
REQUIRES (Iterable<C> || ConstIterable <C> ) {

    return this->toCollection<OrderedSet<ElementType, Comparator>>();
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: toUnorderedSet() const noexcept -> UnorderedSet < ElementType >
REQUIRES(Iterable < C > || ConstIterable < C > ) {

    return this->toCollection<UnorderedSet<ElementType>>();
}

template < typename C >
template < typename Collection >
[[maybe_unused]] inline auto Sequence < C > :: toCollection ( Collection & c ) const noexcept -> Collection &
REQUIRES(Iterable<C> || ConstIterable<C>) {

    for ( auto e : * this )
        c.add(e);
    return c;
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: toLinkedList (
        LinkedList < ElementType > & l
) const noexcept -> LinkedList < ElementType > & REQUIRES ( Iterable<C> || ConstIterable <C> ) {
    return this->toCollection<LinkedList<ElementType>>(l);
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: toArray (
        Array < ElementType > & a
) const noexcept -> Array < ElementType > & REQUIRES ( Iterable<C> || ConstIterable <C> ) {
    return this->toCollection<Array<ElementType>>(a);
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: toOrderedSet (
        OrderedSet < ElementType, Comparator > & s
) const noexcept -> OrderedSet < ElementType, Comparator > &
REQUIRES ( Iterable<C> || ConstIterable <C> ) {

    return this->toCollection<OrderedSet<ElementType, Comparator>>( s );
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > ::toUnorderedSet(
        UnorderedSet < ElementType > & s
) const noexcept -> UnorderedSet < ElementType > & REQUIRES( Iterable < C > || ConstIterable < C > ) {
    return this->toCollection<UnorderedSet<ElementType>>(s);
}

template < typename C >
template < typename Transformer >
[[maybe_unused]] inline auto Sequence < C > :: flatMapTo (
        Collection <
                typename std::remove_reference <
                        decltype (
                        dataTypes::unsafeAddress <
                                typename returnOf < Transformer > :: Iterator
                        >()->value()
                        )
                > :: type
        >                   & collection,
        Transformer   const & transformer
) const noexcept -> Collection <
        typename std::remove_reference <
                decltype (
                dataTypes::unsafeAddress <
                        typename returnOf < Transformer > :: Iterator
                >()->value()
                )
        > :: type
> & REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) && (
                Iterable <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename returnOf < Transformer > :: Iterator
                                >()->value()
                                )
                        > :: type
                > ||
                ConstIterable <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename returnOf < Transformer > :: Iterator
                                >()->value()
                                )
                        > :: type
                >
        )
) {

    for ( auto i : * this )
        for ( auto const & e : transformer(i) )
            collection.add(e);

    return collection;
}

template < typename C >
template < typename IndexedTransformer >
[[maybe_unused]] inline auto Sequence < C > :: flatMapIndexedTo (
        Collection <
                typename std::remove_reference <
                        decltype (
                        dataTypes::unsafeAddress <
                                typename returnOf < IndexedTransformer > :: Iterator
                        >()->value()
                        )
                > :: type
        >                        & collection,
        IndexedTransformer const & transformer
) const noexcept -> Collection <
        typename std::remove_reference <
                decltype (
                dataTypes::unsafeAddress <
                        typename returnOf < IndexedTransformer > :: Iterator
                >()->value()
                )
        > :: type
> & REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) && (
                Iterable <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename returnOf < IndexedTransformer > :: Iterator
                                >()->value()
                                )
                        > :: type
                > ||
                ConstIterable <
                        typename std::remove_reference <
                                decltype (
                                dataTypes::unsafeAddress <
                                        typename returnOf < IndexedTransformer > :: Iterator
                                >()->value()
                                )
                        > :: type
                >
        )
) {

    Index j = 0;
    for ( auto i : * this )
        for ( auto const & e : transformer(i) )
            collection.add(j++, e);

    return collection;
}


// endregion

// region Terminal Extender Operations

template < typename C >
template < typename Action >
[[maybe_unused]] inline auto Sequence < C > :: apply (
        Action const & action
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    action();

    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

template < typename C >
template < typename Action >
[[maybe_unused]] inline auto Sequence < C > :: also (
        Action const & action
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    action();

    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

template < typename C >
template < typename Action >
[[maybe_unused]] inline auto Sequence < C > :: onEach (
        Action const & action
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        action (e);
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}


template < typename C >
template < typename IndexedAction >
[[maybe_unused]] inline auto Sequence < C > :: onEachIndexed (
        IndexedAction const & indexedAction
) && noexcept -> Sequence < LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < ElementType > container;
    Index i = 0;
    for ( auto e : * this ) {
        indexedAction (i++, e);
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

// endregion

/// region Accumulator Operations

template < typename C >
template < typename Accumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: fold (
        AccumulatedType const & startingValue,
        Accumulator     const & accumulator
) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    AccumulatedType result = startingValue;

    for ( auto e : * this )
        result = accumulator ( result, e );

    return result;
}

template < typename C >
template < typename IndexedAccumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: foldIndexed (
        AccumulatedType     const & startingValue,
        IndexedAccumulator  const & indexedAccumulator
) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    AccumulatedType result = startingValue;
    Index i = 0;

    for ( auto e : * this )
        result = indexedAccumulator ( i++, result, e );

    return result;
}

template < typename C >
template < typename Accumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: runningFold (
        AccumulatedType const & initialValue,
        Accumulator     const & accumulator
) && noexcept -> Sequence < LinkedList < AccumulatedType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < AccumulatedType > results = { initialValue };

    for ( auto e : * this )
        results.add ( accumulator ( results.back(), e ) );

    return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
}

template < typename C >
template < typename IndexedAccumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: runningFoldIndexed (
        AccumulatedType     const & initialValue,
        IndexedAccumulator  const & indexedAccumulator
) && noexcept -> Sequence < LinkedList < AccumulatedType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < AccumulatedType > results = { initialValue };
    Index i = 0;

    for ( auto e : * this )
        results.add ( indexedAccumulator ( i++, results.back(), e ) );

    return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
}

template < typename C >
template < typename Accumulator >
[[maybe_unused]] inline auto Sequence < C > :: reduce (
        Accumulator const & accumulator
) const noexcept -> returnOf < Accumulator >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    auto it = this->begin();
    returnOf < Accumulator > result = it.value();

    for ( it.next(); it != this->end(); ++ it )
        result = accumulator ( result, it.value() );

    return result;
}

template < typename C >
template < typename IndexedAccumulator >
[[maybe_unused]] inline auto Sequence < C > :: reduceIndexed (
        IndexedAccumulator const & indexedAccumulator
) const noexcept -> returnOf < IndexedAccumulator >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    auto it = this->begin();
    returnOf < IndexedAccumulator > result = it.value();
    Index i = 1;

    for ( it.next(); it != this->end(); ++ it )
        result = indexedAccumulator ( i ++, result, it.value() );

    return result;
}

template < typename C >
template < typename Accumulator >
[[maybe_unused]] inline auto Sequence < C > :: runningReduce (
        Accumulator const & accumulator
) && noexcept -> Sequence < LinkedList < returnOf < Accumulator > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    auto it = this->begin();
    LinkedList < returnOf < Accumulator > > results = { it.value() };

    for ( it.next(); it != this->end(); ++ it )
        results.add ( accumulator ( results.back(), it.value() ) );

    return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
}

template < typename C >
template < typename IndexedAccumulator >
[[maybe_unused]] inline auto Sequence < C > :: runningReduceIndexed (
        IndexedAccumulator const & indexedAccumulator
) && noexcept -> Sequence < LinkedList < returnOf < IndexedAccumulator > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    auto it = this->begin();
    Index i = 1;
    LinkedList < returnOf < IndexedAccumulator > > results = { it.value() };

    for ( it.next(); it != this->end(); ++ it )
        results.add ( indexedAccumulator ( i++, results.back(), it.value() ) );

    return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
}

template < typename C >
template < typename Accumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: scan (
        AccumulatedType const & initialValue,
        Accumulator     const & accumulator
) && noexcept -> Sequence < LinkedList < AccumulatedType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    return this->runningFold( initialValue, accumulator );
}

template < typename C >
template < typename IndexedAccumulator, typename AccumulatedType >
[[maybe_unused]] inline auto Sequence < C > :: scanIndexed (
        AccumulatedType     const & initialValue,
        IndexedAccumulator  const & indexedAccumulator
) && noexcept -> Sequence < LinkedList < AccumulatedType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    return this->runningFoldIndexed ( initialValue, indexedAccumulator );
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: max (
        Comparator const & comparator
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    if ( this->pCollection.valueAt().valueAt().size() == 0 ) return {  };

    auto it = this->begin();
    ElementType max = it.value();

    for (it.next(); it != this->end(); ++it) {
        auto v = it.value();
        if ( comparator (max, v) )
            max = v;
    }

    return {max};
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: maxBy (
        Selector const & selector
) const noexcept -> Optional < ElementType > REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        TypeLessComparable < returnOf < Selector > >
) {

    if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

    auto it = this->begin();
    auto max = Pair ( selector (it.value()), it.value() );

    for ( it.next(); it != this->end(); ++ it ) {
        auto v = selector (it.value());
        if ( max.getFirst() < v )
            max = { v, it.value() };
    }

    return {max.getSecond()};
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: maxOr (
        ElementType const & e,
        Comparator  const & comparator
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    auto v = this->max ( comparator );
    return v.isPresent() ? v.value() : e;
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: maxByOr (
        ElementType const & e,
        Selector    const & selector
) const noexcept -> ElementType REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        TypeLessComparable < returnOf < Selector > >
) {

    auto v = this->maxBy ( selector );
    return v.isPresent() ? v.value() : e;
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: min (
        Comparator const & comparator
) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    if ( this->pCollection.valueAt().valueAt().size() == 0 ) return {  };

    auto it = this->begin();
    ElementType min = it.value();

    for (it.next(); it != this->end(); ++it) {
        auto v = it.value();
        if ( comparator (v, min) )
            min = v;
    }

    return {min};
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: minBy (
        Selector const & selector
) const noexcept -> Optional < ElementType > REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        TypeLessComparable < returnOf < Selector > >
) {

    if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

    auto it = this->begin();
    auto min = Pair (selector (it.value()), it.value() );

    for ( it.next(); it != this->end(); ++ it ) {
        auto v = selector (it.value());
        if ( v < min.getFirst() )
            min = {v, it.value() };
    }

    return {min.getSecond()};
}

template < typename C >
template < typename Comparator >
[[maybe_unused]] inline auto Sequence < C > :: minOr (
        ElementType const & e,
        Comparator  const & comparator
) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    auto v = this->min ( comparator );
    return v.isPresent() ? v.value() : e;
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: minByOr (
        ElementType const & e,
        Selector    const & selector
) const noexcept -> ElementType REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        TypeLessComparable < returnOf < Selector > >
) {

    auto v = this->minBy ( selector );
    return v.isPresent() ? v.value() : e;
}

template < typename C >
template < typename Selector >
[[maybe_unused]] inline auto Sequence < C > :: sumBy (
        Selector const & selector
) const noexcept -> returnOf < Selector > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    auto it = this->begin();
    auto sum = selector ( it.value() );

    for (it.next(); it != this->end(); ++ it)
        sum = sum + selector(it.value());

    return sum;
}

/// endregion

/// region Sequence Grouping Operations

template < typename C >
[[maybe_unused]] auto Sequence < C > :: chunked (
        Size chunkSize
) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < Array < ElementType > > container;
    Array < ElementType > subContainer;
    Index subContainerPos = 0;
    subContainer.resize(chunkSize);

    for ( auto e : * this ) {
        subContainer[subContainerPos++] = e;

        if ( subContainerPos >= chunkSize ){
            container.add(subContainer);
            subContainer.clear();
            subContainer.resize(chunkSize);
            subContainerPos = 0;
        }
    }

    if ( ! subContainer.empty() ) {
        subContainer.resize(subContainerPos);
        container.add(subContainer);
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename ListTransformer >
[[maybe_unused]] auto Sequence < C > :: chunked (
        Size                    chunkSize,
        ListTransformer const & listTransformer
) && noexcept -> Sequence < LinkedList < returnOf < ListTransformer > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < returnOf < ListTransformer > > container;
    Array < ElementType > subContainer;
    Index subContainerPos = 0;
    subContainer.resize(chunkSize);

    for ( auto e : * this ) {
        subContainer[subContainerPos++] = e;

        if ( subContainerPos >= chunkSize ) {
            container.add ( listTransformer ( subContainer ) );
            subContainer.clear();
            subContainer.resize(chunkSize);
            subContainerPos = 0;
        }
    }

    if ( ! subContainer.empty() ) {
        subContainer.resize(subContainerPos);
        container.add ( listTransformer ( subContainer ) );
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename Predicate >
[[maybe_unused]] inline auto Sequence < C > :: partition (
        Predicate const & predicate
) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    Pair < LinkedList < ElementType >, LinkedList < ElementType > > partitions;

    for ( auto e : * this )
        if ( predicate (e) )
            partitions.getFirst().add(e);
        else
            partitions.getSecond().add(e);

    return partitions;
}

template < typename C >
template < typename IndexedPredicate >
[[maybe_unused]] inline auto Sequence < C > :: partitionIndexed (
        IndexedPredicate const & indexedPredicate
) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    Pair < LinkedList < ElementType >, LinkedList < ElementType > > partitions;
    Index i = 0;

    for ( auto e : * this )
        if ( indexedPredicate (i++,e) )
            partitions.getFirst().add(e);
        else
            partitions.getSecond().add(e);

    return partitions;
}

template < typename C >
[[maybe_unused]] auto Sequence < C > :: windowed (
        Size            size,
        Size            step,
        Boolean const & partialWindows
) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < Array < ElementType > > container;
    Array < ElementType > window;
    auto it = this->begin();


    for ( ; it != this->end(); ) {
        Index i = 0;
        window.resize(size);

        for ( auto wIt = it; wIt != this->end() && i < size; ++wIt ) {
            window[i++] = wIt.value();
        }

        if ( i == size )
            container.add(window);
        else if ( partialWindows ) {
            window.resize(i);
            container.add(window);
        }

        window.clear();

        for ( i = 0; i < step && it != this->end(); i++ )
            ++it;
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename ListTransformer >
[[maybe_unused]] auto Sequence < C > :: windowed (
        ListTransformer const & transformer,
        Size                    size,
        Size                    step,
        Boolean         const & partialWindows
) && noexcept -> Sequence < LinkedList < returnOf < ListTransformer > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < returnOf < ListTransformer > > container;

    if constexpr (
            std::is_abstract <
                    typename std::remove_cv <
                            typename std::remove_reference <
                                    decltype (
                                    std::get < 0 > (
                                            * dataTypes::unsafeAddress <
                                                    argumentsOf <
                                                            ListTransformer
                                                    >
                                            > ()
                                    )
                                    )
                            >::type
                    > :: type
            > :: type :: value
            ) {
        LinkedList <
                typename std::remove_cv <
                        typename std::remove_reference <
                                decltype (
                                std::get < 0 > (
                                        * dataTypes::unsafeAddress <
                                                argumentsOf <
                                                        ListTransformer
                                                >
                                        > ()
                                )
                                )
                        >::type
                > :: type ::ElementType
        > window;

        auto it = this->begin();

        for (; it != this->end();) {
            Index i = 0;
            for (auto wIt = it; wIt != this->end() && i < size; ++wIt) {
                window.add(wIt.value());
            }

            if (i == size || partialWindows)
                container.add(transformer(window));

            window.clear();

            for (i = 0; i < step && it != this->end(); i++)
                ++it;
        }

        return std::move(Sequence<decltype(container)>(std::move(container)));
    } else {
        typename std::remove_cv <
                typename std::remove_reference <
                        decltype(
                        std::get<0>(
                                *dataTypes::unsafeAddress <
                                        argumentsOf <
                                                ListTransformer
                                        >
                                >()
                        )
                        )
                >::type
        > :: type window;

        auto it = this->begin();


        for (; it != this->end();) {
            Index i = 0;
            for (auto wIt = it; wIt != this->end() && i < size; ++wIt) {
                window.add(wIt.value());
            }

            if (i == size || partialWindows)
                container.add(transformer(window));

            window.clear();

            for (i = 0; i < step && it != this->end(); i++)
                ++it;
        }

        return std::move(Sequence<decltype(container)>(std::move(container)));
    }
}

template < typename C >
template < typename OC >
[[maybe_unused]] inline auto Sequence < C > :: zip (
        Sequence < OC > const & other
) && noexcept -> Sequence < LinkedList < Pair < ElementType, typename Sequence < OC > :: ElementType > > >
REQUIRES (
        ( Iterable < C > || ConstIterable < C > ) &&
        ( Iterable < OC > || ConstIterable < OC > )
) {

    auto it1 = this->begin();
    auto it2 = other.begin();

    LinkedList < Pair < decltype(it1.value()), decltype(it2.value()) > > container;

    for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
        container.add ( { it1.value(), it2.value() } );

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename OC, typename Transformer >
[[maybe_unused]] inline auto Sequence < C > :: zip (
        Sequence < OC > const & other,
        Transformer     const & transformer
) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
REQUIRES (
        (Iterable < C > || ConstIterable < C >) &&
        (Iterable < OC > || ConstIterable < OC > )
) {

    auto it1 = this->begin();
    auto it2 = other.begin();

    LinkedList < returnOf < Transformer > > container;

    for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
        container.add ( transformer( it1.value(), it2.value() ) );

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
[[maybe_unused]] inline auto Sequence < C > :: zipWithNext (

) && noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < Pair < ElementType, ElementType > > container;

    auto it = this->begin();
    auto v = it.value();

    for ( it.next(); it != this->end(); ++ it ) {
        container.add ( { v, it.value() } );
        v = it.value();
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

template < typename C >
template < typename Transformer >
[[maybe_unused]] auto Sequence < C > :: zipWithNext (
        Transformer const & transformer
) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > >
REQUIRES ( Iterable < C > || ConstIterable < C > ) {

    LinkedList < returnOf < Transformer > > container;

    auto it = this->begin();
    auto v = it.value();

    for ( it.next(); it != this->end(); ++ it ) {
        container.add ( transformer ( v, it.value() ) );
        v = it.value();
    }

    return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
}

/// endregion

#endif //CDS_SEQUENCE_HPP