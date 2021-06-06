//
// Created by loghin on 02.06.2021.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
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
#define _REQUIRES_ITERABLE requires Iterable < C > || ConstIterable < C >
#define _REQUIRES_PRINTABLE requires HasToString < C >
#define _REQUIRES_INTEGRAL_ITERABLE requires Iterable < C > && Integral < C >
#else
#define REQUIRES ( Iterable < C > || ConstIterable < C > )
#define _REQUIRES_PRINTABLE
#define _REQUIRES_INTEGRAL_ITERABLE
#endif

template < typename C >
class Sequence : public Object {
public:
    using CollectionType = C;

private:

    using ClassName                 = typename std::remove_reference < C >::type;
    using IterableValue             = decltype ( dataTypes::unsafeAddress < typename ClassName::Iterator > ()->value() );
    using ElementType               = typename std::remove_reference < IterableValue > :: type;

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
        using CollectionIterator = typename CollectionType::Iterator;
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
    Sequence () noexcept = delete;
    Sequence (Sequence const &) noexcept;
    Sequence (Sequence &&) noexcept;

    explicit Sequence ( C & ) noexcept;
//    explicit Sequence ( C const & ) noexcept;
    explicit Sequence ( C && ) noexcept;

    ~Sequence () noexcept override = default;

    auto operator = (Sequence const &) noexcept -> Sequence &;
    auto operator = (Sequence &&) noexcept -> Sequence &;

    auto begin () noexcept -> Iterator;
    auto end () noexcept -> Iterator;

    auto begin () const noexcept -> ConstIterator;
    auto end () const noexcept -> ConstIterator;
    auto cbegin () const noexcept -> ConstIterator;
    auto cend () const noexcept -> ConstIterator;

    [[nodiscard]] auto toString () const noexcept -> String override;
    [[nodiscard]] auto hash () const noexcept -> Index override;
    [[nodiscard]] auto copy () const noexcept -> Sequence * override;
    [[nodiscard]] auto equals (Object const &) const noexcept -> bool override;

    auto contains ( ElementType const & ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto elementAt ( Index ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto elementAtOr ( Index, ElementType const & ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );


    auto indexOf ( ElementType const & ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto lastIndexOf ( ElementType const & ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto indicesOf ( ElementType const & ) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Action >
    auto apply ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    auto also ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    auto find ( Predicate const & ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto first ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto firstOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto findLast ( Predicate const & ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto last ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto lastOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );


    auto single () const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto singleOr ( ElementType const & ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto single ( Predicate const & ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto singleOr ( ElementType const &, Predicate const & ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );


    auto drop (Size) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto dropWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto take (Size) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto takeWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    auto filter ( Predicate const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    auto filterIndexed ( IndexedPredicate const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto filterTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    auto filterIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename NewType >
    auto filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > > REQUIRES((Iterable < C > || ConstIterable < C >) && Pointer < ElementType > && Pointer < NewType >);

    template < typename NewType >
    auto filterIsDerivedTo ( Collection < ElementType > & ) const noexcept -> Collection < ElementType > & REQUIRES( ( Iterable < C > || ConstIterable < C > ) && Pointer < ElementType > && Pointer < NewType > );

    template < typename Predicate >
    auto filterNot ( Predicate const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    auto filterNotIndexed ( IndexedPredicate const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto filterNotTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    auto filterNotIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    auto indexOfFirst ( Predicate const & ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto indexOfLast ( Predicate const & ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto indicesOfAll ( Predicate const & ) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto any ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto all ( Predicate const & ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto count ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Size REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto none ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    auto one ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
        typename Transformer,
        typename std::enable_if <
            isPair < returnOf < Transformer > > :: value,
            int
        >:: type = 0
    >
    auto associate ( Transformer const & ) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > > REQUIRES ( ( Iterable < C > || ConstIterable < C > ) && PairType < returnOf < Transformer > > );

    template < typename KeyGenerator >
    auto associateBy ( KeyGenerator const & ) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    auto associateBy ( KeyGenerator const &, ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, returnOf < ValueMapper > > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator >
    auto associateByTo ( Map < returnOf < KeyGenerator >, ElementType > &, KeyGenerator const & ) const noexcept -> Map < returnOf < KeyGenerator >, ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    auto associateByTo ( Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > &, KeyGenerator const &, ValueMapper const & ) const noexcept -> Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename K, typename V >
    auto associateTo ( Map < K, V > &, Transformer const & ) const noexcept -> Map < K, V > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    auto associateWith ( ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < ElementType, returnOf < ValueMapper > > > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    auto associateWithTo ( Map < ElementType, returnOf < ValueMapper > > &, ValueMapper const & ) const noexcept -> Map < ElementType , returnOf < ValueMapper > > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator > 
    auto sort ( Comparator const & = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < LinkedList < ElementType > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector > 
    auto sortedBy ( Selector const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector >
    auto sortedByDescending ( Selector const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector, typename Comparator, typename SelectorType >
    auto sortedByWith ( Selector const &, Comparator const & = []( SelectorType const & a, SelectorType const & b ) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < LinkedList < ElementType > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Collection > 
    auto asCollection () const noexcept -> Collection REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto asLinkedList () const noexcept -> LinkedList < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto asArray () const noexcept -> Array < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    auto asOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto asUnorderedSet () const noexcept -> UnorderedSet < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    // auto asHashMap  look into View::toMap


    template < typename Collection >
    auto toCollection (Collection &) const noexcept -> Collection & REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto toLinkedList (LinkedList < ElementType > &) const noexcept -> LinkedList < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto toArray (Array <ElementType> &) const noexcept -> Array < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    auto toOrderedSet (OrderedSet <ElementType, Comparator> &) const noexcept -> OrderedSet < ElementType, Comparator > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto toUnorderedSet (UnorderedSet <ElementType> &) const noexcept -> UnorderedSet < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    
    template < typename Transformer, typename TransformedType >
    auto flatMap ( Transformer const & ) && noexcept -> Sequence < LinkedList < TransformedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexed ( IndexedTransformer const & ) && noexcept -> Sequence < LinkedList < TransformedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename TransformedType >
    auto flatMapTo ( Collection < TransformedType > &, Transformer const & ) const noexcept -> Collection < TransformedType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexedTo ( Collection < TransformedType > &, IndexedTransformer const & ) const noexcept -> Collection < TransformedType > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename K > 
    auto groupBy ( KeySelector const & ) && noexcept -> Sequence < LinkedList < Pair < K, LinkedList < ElementType > > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename ValueMapper, typename K, typename V >
    auto groupBy ( KeySelector const &, ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < K, LinkedList < V > > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename K, typename G > 
    auto groupByTo ( Map < K, G > &, KeySelector const & ) const noexcept -> Map < K, G > & REQUIRES ( Iterable < C > || ConstIterable < C > ); 

    template < typename KeySelector, typename ValueMapper, typename K, typename G >
    auto groupByTo ( Map < K, G > &, KeySelector const &, ValueMapper const & ) const noexcept -> Map < K, G > & REQUIRES ( Iterable < C > || ConstIterable < C > );

    /**
     * Two versions of map, one for storage of mappers when keeping same type, another for switching to another data type
     */

    template <
        typename Mapper,
        typename std::enable_if <
            ! std::is_same_v <
                ElementType,
                returnOf < Mapper >
            >,
            int
        >::type = 0
    >
    auto map ( Mapper const & ) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
        typename Mapper,
        typename std::enable_if <
            std::is_same <
                ElementType,
                returnOf < Mapper >
            >::type::value,
            int
        >::type = 0
    >
    auto map ( Mapper const & ) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
        typename IndexedMapper,
        typename std::enable_if <
            ! std::is_same_v <
                ElementType,
                returnOf < IndexedMapper >
            >,
            int
        >::type = 0
    >
    auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < LinkedList < returnOf < IndexedMapper > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template <
        typename IndexedMapper,
        typename std::enable_if <
            std::is_same <
                ElementType,
                returnOf < IndexedMapper >
            >::type::value,
            int
        >::type = 0
    >
    auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Mapper, typename R >
    auto mapTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > ); 

    template < typename IndexedMapper, typename R > 
    auto mapIndexedTo ( Collection < R > &, IndexedMapper const & ) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > );


    auto indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto distinct () && noexcept -> Sequence < UnorderedSet < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Folder, typename R >
    auto fold ( Folder const & ) const noexcept -> R REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedFolder, typename R > 
    auto foldIndexed ( IndexedFolder const & ) const noexcept -> R REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Action > 
    auto forEach ( Action const & ) const noexcept -> void REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAction > 
    auto forEachIndexed ( IndexedAction const & ) const noexcept -> void REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Action > 
    auto onEach ( Action const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAction >
    auto onEachIndexed ( IndexedAction const & ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Comparator > 
    auto max ( Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector > 
    auto maxBy ( Selector const & ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator > 
    auto maxOr ( ElementType const &, Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector > 
    auto maxByOr ( ElementType const &, Selector const & ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator > 
    auto min ( Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector > 
    auto minBy ( Selector const & ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Comparator > 
    auto minOr ( ElementType const &, Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Selector > 
    auto minByOr ( ElementType const &, Selector const & ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Accumulator, typename AccumulatedType >
    auto reduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto reduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > ); 

    template < typename Accumulator, typename AccumulatedType >
    auto runningReduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningReduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator, typename AccumulatedType >
    auto fold ( AccumulatedType const &, Accumulator const & ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto foldIndexed ( AccumulatedType const &, IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType REQUIRES ( Iterable < C > || ConstIterable < C > ); 

    template < typename Accumulator, typename AccumulatedType >
    auto runningFold ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningFoldIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Accumulator, typename AccumulatedType >
    auto scan ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto scanIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    
    template < typename Selector, typename R >
    auto sumBy ( Selector const & ) const noexcept -> R REQUIRES ( Iterable < C > || ConstIterable < C > );

    
    auto chunked (Size) && noexcept -> Sequence < LinkedList < LinkedList < ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ListTransformer, typename R > 
    auto chunked (Size, ListTransformer const &) && noexcept -> Sequence < LinkedList < R > > REQUIRES ( Iterable < C > || ConstIterable < C > );


    auto minus ( ElementType const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );
    auto minus ( Collection < ElementType > const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );
    auto minus ( Sequence const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto plus ( ElementType const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );
    auto plus ( Collection < ElementType > const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );
    auto plus ( Sequence const & ) && noexcept -> Sequence REQUIRES ( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    auto partition ( Predicate const & ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto windowed ( Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < LinkedList < ElementType > > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename ListTransformer, typename R >
    auto windowed ( ListTransformer const &, Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < R > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename S >
    auto zip ( Sequence < S > const & ) && noexcept -> Sequence < LinkedList < Pair < ElementType, typename S::ElementType > > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename S, typename Transformer, typename V >
    auto zip ( Sequence < S > const &, Transformer const & ) && noexcept -> Sequence < LinkedList < V > >  REQUIRES ( Iterable < C > || ConstIterable < C > );

    auto zipWithNext () && noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename R > 
    auto zipWithNext (Transformer const &) && noexcept -> Sequence < LinkedList < R > > REQUIRES ( Iterable < C > || ConstIterable < C > );
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
        pCollection ( new UniquePointer ( s.pCollection.valueAt().release() ) ),
        chainCount ( std::exchange ( s.chainCount, 0 ) + 1 ),
        storedMappers ( std::move ( s.storedMappers ) ),
        storedPredicates ( std::move ( s.storedPredicates ) ),
        storedIndexedMappers ( std::move ( s.storedIndexedMappers ) ),
        storedIndexedPredicates ( std::move ( s.storedIndexedPredicates ) ){

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

            if ( currentMapperIterator != this->pSeq.valueAt().storedMappers.end() && currentMapperIterator.value().getSecond() == i ) {
                this->precomputed = ( * currentMapperIterator.value().getFirst() ) ( this->precomputed );
                currentMapperIterator.next();

            } else if ( currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() && currentIndexedMapperIterator.value().getSecond() == i ) {
                this->precomputed = ( * currentIndexedMapperIterator.value().getFirst() ) ( this->index, this->precomputed );
                currentIndexedMapperIterator.next();

            } else if ( currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() && currentFilterIterator.value().getSecond() == i ) {
                if ( ! (* currentFilterIterator.value().getFirst())( this->precomputed ) ) {
                    skip = true;
                    break;
                }
                currentFilterIterator.next();

            } else if ( currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() && currentIndexedFilterIterator.value().getSecond() == i ) {
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
//            while (currentMapperIterator != this->pSeq.valueAt().storedMappers.end()) {
//                this->precomputed = (*currentMapperIterator.value().getFirst())(this->precomputed);
//                currentMapperIterator++;
//            }

            for ( Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if ( currentMapperIterator != this->pSeq.valueAt().storedMappers.end() && currentMapperIterator.value().getSecond() == i ) {
                    this->precomputed = (* currentMapperIterator.value().getFirst())(this->precomputed);
                    currentMapperIterator.next();
                } else if ( currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() && currentIndexedMapperIterator.value().getSecond() == i ) {
                    this->precomputed = (* currentIndexedMapperIterator.value().getFirst())(this->index, this->precomputed);
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
inline Sequence < C >::ConstIterator::ConstIterator(Sequence < C > const * pSequence, CollectionIterator const & it) noexcept :
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

            if ( currentMapperIterator != this->pSeq.valueAt().storedMappers.end() && currentMapperIterator.value().getSecond() == i ) {
                this->precomputed = ( * currentMapperIterator.value().getFirst() ) ( this->precomputed );
                currentMapperIterator.next();

            } else if ( currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() && currentIndexedMapperIterator.value().getSecond() == i ) {
                this->precomputed = ( * currentIndexedMapperIterator.value().getFirst() ) ( this->index, this->precomputed );
                currentIndexedMapperIterator.next();

            } else if ( currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() && currentFilterIterator.value().getSecond() == i ) {
                if ( ! (* currentFilterIterator.value().getFirst())( this->precomputed ) ) {
                    skip = true;
                    break;
                }
                currentFilterIterator.next();

            } else if ( currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() && currentFilterIterator.value().getSecond() == i ) {
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
//            while (currentMapperIterator != this->pSeq.valueAt().storedMappers.end()) {
//                this->precomputed = (*currentMapperIterator.value().getFirst())(this->precomputed);
//                currentMapperIterator++;
//            }

            for ( Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if ( currentMapperIterator != this->pSeq.valueAt().storedMappers.end() && currentMapperIterator.value().getSecond() == i ) {
                    this->precomputed = (* currentMapperIterator.value().getFirst())(this->precomputed);
                    currentMapperIterator.next();
                } else if ( currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() && currentIndexedMapperIterator.value().getSecond() == i ) {
                    this->precomputed = (* currentIndexedMapperIterator.value().getFirst())(this->index, this->precomputed);
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

//template < typename T >
//Sequence ( Array < T > ) -> Sequence < Array < T > >;

template < typename T>
Sequence ( Array < T > & ) -> Sequence < Array < T > >;

template < typename T>
Sequence ( Array < T > const & ) -> Sequence < Array < T > const >;

template < typename T>
Sequence ( Array < T > && ) -> Sequence < Array < T > >;

//template < typename T >
//Sequence ( DoubleLinkedList < T > ) -> Sequence < DoubleLinkedList < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > & ) -> Sequence < DoubleLinkedList < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > const & ) -> Sequence < DoubleLinkedList < T > const >;

template < typename T >
Sequence ( DoubleLinkedList < T > && ) -> Sequence < DoubleLinkedList < T > >;

//template < typename T >
//Sequence ( OrderedSet < T > ) -> Sequence < OrderedSet < T > >;
//
template < typename T >
Sequence ( OrderedSet < T > & ) -> Sequence < OrderedSet < T > >;

template < typename T >
Sequence ( OrderedSet < T > const & ) -> Sequence < OrderedSet < T > const >;

template < typename T >
Sequence ( OrderedSet < T > && ) -> Sequence < OrderedSet < T > >;


//template < typename T >
//Sequence ( UnorderedSet < T > ) -> Sequence < UnorderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > & ) -> Sequence < UnorderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > const & ) -> Sequence < UnorderedSet < T > const >;

template < typename T >
Sequence ( UnorderedSet < T > && ) -> Sequence < UnorderedSet < T > >;

//template < typename K, typename V >
//Sequence ( HashMap < K, V > ) -> Sequence < HashMap < K, V > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > & ) -> Sequence < HashMap < K, V > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > const & ) -> Sequence < HashMap < K, V > const >;

template < typename K, typename V >
Sequence ( HashMap < K, V > && ) -> Sequence < HashMap < K, V > >;

#include <CDS/JSON>
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
                decltype ( dataTypes::unsafeAddress < typename std::remove_reference<C>::type::Iterator > ()->value() )
            > :: type,
            returnOf < Mapper >
        >,
        int
    >::type
>
auto Sequence < C > :: map ( Mapper const & mapper ) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
                decltype ( dataTypes::unsafeAddress < typename std::remove_reference<C>::type::Iterator > ()->value() )
            > :: type,
            returnOf < Mapper >
        >::type::value,
        int
    >::type
>
auto Sequence < C > ::map(Mapper const & mapper) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedMappers.append({ { new StoredMapper(mapper) }, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename Predicate >
auto Sequence < C > ::filter(Predicate const & predicate) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedPredicates.append({ { new StoredPredicate (predicate)}, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename IndexedPredicate >
auto Sequence < C > :: filterIndexed ( IndexedPredicate const & indexedPredicate ) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedIndexedPredicates.append({ { new StoredIndexedPredicate (indexedPredicate)}, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template <
    typename IndexedMapper,
    typename std::enable_if <
        ! std::is_same_v <
            typename std::remove_reference <
                decltype ( dataTypes::unsafeAddress < typename std::remove_reference<C>::type::Iterator > ()->value() )
            > :: type,
            returnOf < IndexedMapper >
        >,
        int
    >::type
>
auto Sequence < C > :: mapIndexed ( IndexedMapper const & mapper ) && noexcept -> Sequence < LinkedList < returnOf < IndexedMapper > > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
                decltype ( dataTypes::unsafeAddress < typename std::remove_reference<C>::type::Iterator > ()->value() )
            > :: type,
            returnOf < IndexedMapper >
        >::type::value,
        int
    >::type
>
auto Sequence < C > ::mapIndexed(IndexedMapper const & mapper) && noexcept -> Sequence < C > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    this->storedIndexedMappers.append({ { new StoredIndexedMapper(mapper) }, this->chainCount });
    return std::move ( * this );
}

template < typename C >
auto Sequence < C > :: drop ( Size count ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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

template < typename C >
template < typename Predicate >
auto Sequence < C > :: dropWhile ( Predicate const & p, Size count ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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

template < typename C >
auto Sequence < C > :: take ( Size count ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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

template < typename C >
template < typename Predicate >
auto Sequence < C > :: takeWhile ( Predicate const & predicate, Size count ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    LinkedList < Pair < Index, ElementType > > container;
    Index i = 0;
    for ( auto e : * this )
        container.add ( { i++, e } );

    return std::move ( Sequence < LinkedList < Pair < Index, ElementType > > > ( std::move ( container ) ) );
}

template < typename C >
template < typename NewType >
inline auto Sequence < C > :: filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > > REQUIRES(( Iterable < C > || ConstIterable < C > ) && Pointer < ElementType > && Pointer < NewType > ) {
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
inline auto Sequence < C > :: filterNot ( Predicate const & predicate ) && noexcept -> Sequence REQUIRES( Iterable < C > || ConstIterable < C > ) {
    return this->filter( [& predicate] (ElementType e) noexcept -> bool { return ! predicate(e); } );
}

template < typename C >
template < typename IndexedPredicate >
inline auto Sequence < C > :: filterNotIndexed(IndexedPredicate const & indexedPredicate) && noexcept -> Sequence REQUIRES( Iterable < C > || ConstIterable < C > ) {
    return this->filterIndexed( [& indexedPredicate] (Index index, ElementType e) noexcept -> bool { return ! indexedPredicate ( index, e ); } );
}

template < typename C >
template <
    typename Transformer,
    typename std::enable_if <
        isPair < returnOf < Transformer > > :: value,
        int
    > :: type
>
inline auto Sequence < C > :: associate( Transformer const & transformer ) && noexcept -> Sequence < LinkedList < returnOf < Transformer > > > REQUIRES ( ( Iterable < C > || ConstIterable < C > ) && PairType < returnOf < Transformer > > ) {
    LinkedList < returnOf < Transformer > > container;
    for ( auto e : * this )
        container.add ( transformer ( e ) );

    return std::move ( Sequence < LinkedList < returnOf < Transformer > > > ( std::move ( container ) ) );
}

template < typename C >
template < typename KeyGenerator >
inline auto Sequence < C > :: associateBy ( KeyGenerator const & keyGenerator ) && noexcept -> Sequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > container;
    for ( auto e : * this )
        container.add ( { keyGenerator ( e ), e } );

    return std::move ( Sequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > > ( std::move ( container ) ) );
}


/// endregion

// region Basic Utility Functions

template < typename C >
inline auto Sequence < C > ::contains(ElementType const & e) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto v : * this )
        if ( e == v )
            return true;
    return false;
}

template < typename C >
inline auto Sequence < C > ::elementAt(Index i) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index at = 0;
    for ( auto v : * this )
        if ( at == i )
            return { v };
        else
            at ++;

    return { };
}

template < typename C >
inline auto Sequence < C > ::elementAtOr(Index i, ElementType const & e) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index at = 0;
    for ( auto v : * this )
        if ( at == i )
            return v;
        else
            at ++;

    return e;
}

template < typename C >
inline auto Sequence < C > ::indexOf(ElementType const & e) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto v : * this )
        if ( v == e )
            return i;
        else
            i++;

    return -1;
}

template < typename C >
inline auto Sequence < C > ::lastIndexOf(ElementType const & e) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0, last = -1;
    for ( auto v : * this ) {
        if (v == e)
            last = i;
        i++;
    }

    return last;
}

template < typename C >
inline auto Sequence < C > ::indicesOf (ElementType const & e) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: find ( Predicate const & predicate ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->first(predicate);
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: first ( Predicate const & predicate ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return { e };
    return { };
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: firstOr ( ElementType const & e, Predicate const & predicate ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto v : * this )
        if ( predicate (v) )
            return v;
    return e;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > ::findLast ( Predicate const & predicate ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    return this->last(predicate);
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: last ( Predicate const & predicate ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: lastOr ( ElementType const & r, Predicate const & predicate ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: single () const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    if ( this->pCollection.valueAt().valueAt().size() != 1 )
        return { };
    return this->begin().value();
}

template < typename C >
inline auto Sequence < C > :: singleOr (ElementType const & v) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    if ( this->pCollection.valueAt().valueAt().size() != 1 )
        return v;
    return this->begin().value();
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: single ( Predicate const & predicate ) const noexcept -> Optional < ElementType > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: singleOr ( ElementType const & r, Predicate const & predicate ) const noexcept -> ElementType REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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

// endregion

// region Terminal Operations

template < typename C >
template < typename Action >
inline auto Sequence < C > :: forEach ( Action const & action ) const noexcept -> void REQUIRES(Iterable<C> || ConstIterable<C>) {
    for ( auto e : * this ) action (e);
}

template < typename C >
template < typename IndexedAction >
inline auto Sequence < C > :: forEachIndexed ( IndexedAction const & indexedAction ) const noexcept -> void REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this ) indexedAction (i++, e);
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: filterTo ( Collection < ElementType > & collection, Predicate const & predicate ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate(e) )
            collection.add(e);

    return collection;
}

template < typename C >
template < typename IndexedPredicate >
inline auto Sequence < C > :: filterIndexedTo ( Collection < ElementType > & collection, IndexedPredicate const & predicate ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this )
        if ( predicate(i++, e) )
            collection.add(e);

    return collection;
}

template < typename C >
template < typename Mapper, typename R >
inline auto Sequence < C > :: mapTo ( Collection < R > & collection, Mapper const & mapper ) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        collection.add ( mapper(e) );
    return collection;
}

template < typename C >
template < typename IndexedMapper, typename R >
inline auto Sequence < C > :: mapIndexedTo ( Collection < R > & collection, IndexedMapper const & mapper ) const noexcept -> Collection < R > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this )
        collection.add ( mapper(i++, e) );
    return collection;
}

template < typename C >
template < typename NewType >
inline auto Sequence < C > :: filterIsDerivedTo ( Collection < ElementType > & collection ) const noexcept -> Collection < ElementType > & REQUIRES ( ( Iterable < C > || ConstIterable < C > ) && Pointer < ElementType > && Pointer < NewType > ) {
    for ( auto e : * this ) {
        auto p = dynamic_cast < NewType > (e);
        if ( p != nullptr )
            collection.add(p);
    }

    return collection;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: filterNotTo ( Collection < ElementType > & collection, Predicate const & predicate ) const noexcept -> Collection < ElementType > & REQUIRES( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( ! predicate ( e ) )
            collection.add( e );

    return collection;
}

template < typename C >
template < typename IndexedPredicate >
inline auto Sequence < C > :: filterNotIndexedTo ( Collection < ElementType > & collection, IndexedPredicate const & indexedPredicate ) const noexcept -> Collection < ElementType > & REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Index i = 0;
    for ( auto e : * this )
        if ( ! indexedPredicate ( i++, e ) )
            collection.add ( e );

    return collection;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: indexOfFirst ( Predicate const & predicate ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: indexOfLast ( Predicate const & predicate ) const noexcept -> Index REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: indicesOfAll ( Predicate const & predicate ) const noexcept -> LinkedList < Index > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
inline auto Sequence < C > :: any ( Predicate const & predicate ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return true;
    return false;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: all ( Predicate const & predicate ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( ! predicate ( e ) )
            return false;

    return true;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: count ( Predicate const & predicate ) const noexcept -> Size REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    Size count = 0;
    for ( auto e : * this )
        if ( predicate ( e ) )
            count ++;

    return count;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: none ( Predicate const & predicate ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    for ( auto e : * this )
        if ( predicate ( e ) )
            return false;
    return true;
}

template < typename C >
template < typename Predicate >
inline auto Sequence < C > :: one ( Predicate const & predicate ) const noexcept -> Boolean REQUIRES ( Iterable < C > || ConstIterable < C > ) {
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
// endregion

// region Terminal Extender Operations

template < typename C >
template < typename Action >
inline auto Sequence < C > :: apply ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    action();

    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

template < typename C >
template < typename Action >
inline auto Sequence < C > :: also ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    action();

    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

template < typename C >
template < typename Action >
inline auto Sequence < C > :: onEach ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    LinkedList < ElementType > container;
    for ( auto e : * this ) {
        action (e);
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}


template < typename C >
template < typename IndexedAction >
inline auto Sequence < C > :: onEachIndexed (IndexedAction const & indexedAction ) && noexcept -> Sequence < LinkedList < ElementType > > REQUIRES ( Iterable < C > || ConstIterable < C > ) {
    LinkedList < ElementType > container;
    Index i = 0;
    for ( auto e : * this ) {
        indexedAction (i++, e);
        container.append(e);
    }

    return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
}

// endregion

#endif //CDS_SEQUENCE_HPP

#pragma clang diagnostic pop