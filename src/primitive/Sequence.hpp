//
// Created by loghin on 02.06.2021.
//

#ifndef CDS_SEQUENCE_HPP
#define CDS_SEQUENCE_HPP

#include <CDS/Object>

#if defined(__cpp_concepts)
#define _REQUIRES_ITERABLE requires Iterable < Type > || ConstIterable < Type >
#define _REQUIRES_PRINTABLE requires HasToString < Type >
#define _REQUIRES_INTEGRAL_ITERABLE requires Iterable < Type > && Integral < ViewValue >
#else
#define _REQUIRES_ITERABLE
#define _REQUIRES_PRINTABLE
#define _REQUIRES_INTEGRAL_ITERABLE
#endif

#include <CDS/Boolean>
#include <CDS/Optional>
#include <CDS/Pair>
#include <CDS/Map>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/Set>

template < typename T >
class Sequence : public Object {
    using ElementType = T;

public:
    [[nodiscard]] auto toString () const noexcept -> String override;
    [[nodiscard]] auto hash () const noexcept -> Index override;
    [[nodiscard]] auto copy () const noexcept -> Sequence * override;
    [[nodiscard]] auto operator == (Object const &) const noexcept -> bool override;

    auto contains ( ElementType const & ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    auto elementAt ( Index ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    auto elementAtOr ( Index, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto indexOf ( ElementType const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    auto lastIndexOf ( ElementType const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    auto indicesOf ( ElementType const & ) const noexcept -> Array < Index > _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto find ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto first ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto firstOr ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; }, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto findLast ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto last ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto lastOr ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; }, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto single () const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    auto singleOr ( ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto single ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto singleOr ( Predicate const &, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto drop (Size) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto dropWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    auto take (Size) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto takeWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence && _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto filter ( Predicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterIndexed ( IndexedPredicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto filterTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterIndexedTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename NewType >
    auto filterIsDerivedFrom () && noexcept -> Sequence < NewType > _REQUIRES_ITERABLE;

    template < typename NewType >
    auto filterIsDerivedFromTo ( Collection < ElementType > & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto filterNot ( Predicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterNotIndexed ( Predicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto filterNotTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterNotIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto indexOfFirst ( Predicate const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto indexOfLast ( Predicate const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto indicesOfAll ( Predicate const & ) const noexcept -> Array < Index > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto any ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto all ( Predicate const & ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto count ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto none ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto one ( Predicate const & = [](ElementType const &) { return true; } ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    template < typename Transformer, typename K, typename V >
    auto associate ( Transformer const & ) && noexcept -> Sequence < Pair < K, V > > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateBy ( KeyGenerator const & ) && noexcept -> Sequence < Pair < K, ElementType > > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateBy ( KeyGenerator const &, ValueMapper const & ) && noexcept -> Sequence < Pair < K, V > > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateByTo ( Map < K, ElementType > &, KeyGenerator const & ) const noexcept -> Map < K, ElementType > & _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateByTo ( Map < K, V > &, KeyGenerator const &, ValueMapper const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename Transformer, typename K, typename V >
    auto associateTo ( Map < K, V > &, Transformer const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWith ( ValueMapper const & ) && noexcept -> Sequence < Pair < ElementType, V > > && _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWithTo ( Map < ElementType, V > &, ValueMapper const & ) const noexcept -> Map < ElementType , V > & _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto sort ( Comparator const & = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto sortedBy ( Selector const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Selector >
    auto sortedByDescending ( Selector const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Selector, typename Comparator, typename SelectorType >
    auto sortedByWith ( Selector const &, Comparator const & = []( SelectorType const & a, SelectorType const & b ) noexcept -> bool { return a < b; } ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Collection > 
    auto asCollection () const noexcept -> Collection _REQUIRES_ITERABLE;

    auto asLinkedList () const noexcept -> LinkedList < ElementType > _REQUIRES_ITERABLE;

    auto asArray () const noexcept -> Array < ElementType > _REQUIRES_ITERABLE;

    auto asOrderedSet () const noexcept -> OrderedSet < ElementType > _REQUIRES_ITERABLE;

    auto asUnorderedSet () const noexcept -> UnorderedSet < ElementType > _REQUIRES_ITERABLE;

    // auto asHashMap  look into View::toMap


    template < typename Collection >
    auto toCollection (Collection &) const noexcept -> Collection & _REQUIRES_ITERABLE;

    auto toLinkedList (LinkedList < ElementType > &) const noexcept -> LinkedList < ElementType > & _REQUIRES_ITERABLE;

    auto toArray (Array <ElementType> &) const noexcept -> Array < ElementType > & _REQUIRES_ITERABLE;

    auto toOrderedSet (OrderedSet <ElementType> &) const noexcept -> OrderedSet < ElementType > & _REQUIRES_ITERABLE;

    auto toUnorderedSet (UnorderedSet <ElementType> &) const noexcept -> UnorderedSet < ElementType > & _REQUIRES_ITERABLE;

    
    template < typename Transformer, typename TransformedType >
    auto flatMap ( Transformer const & ) && noexcept -> Sequence < TransformedType > && _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexed ( IndexedTransformer const & ) && noexcept -> Sequence < TransformedType > && _REQUIRES_ITERABLE;

    template < typename Transformer, typename TransformedType >
    auto flatMapTo ( Collection < TransformedType > &, Transformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexedTo ( Collection < TransformedType > &, IndexedTransformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K > 
    auto groupBy ( KeySelector const & ) && noexcept -> Sequence < Pair < K, LinkedList < ElementType > > > && _REQUIRES_ITERABLE; 

    template < typename KeySelector, typename ValueMapper, typename K, typename V >
    auto groupBy ( KeySelector const &, ValueMapper const & ) && noexcept -> Sequence < Pair < K, LinkedList < V > > > && _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K, typename G > 
    auto groupByTo ( Map < K, G > &, KeySelector const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE; 

    template < typename KeySelector, typename ValueMapper, typename K, typename G >
    auto groupByTo ( Map < K, G > &, KeySelector const &, ValueMapper const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE;

    
    template < typename Mapper, typename R >
    auto map ( Mapper const & ) && noexcept -> Sequence < R > && _REQUIRES_ITERABLE;

    template < typename IndexedMapper, typename R >
    auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < R > && _REQUIRES_ITERABLE;

    template < typename Mapper, typename R >
    auto mapTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE; 

    template < typename IndexedMapper, typename R > 
    auto mapIndexedTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE;


    auto indexed () && noexcept -> Sequence < Pair < Index, ElementType > > && _REQUIRES_ITERABLE;

    auto distinct () && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Folder, typename R >
    auto fold ( Folder const & ) const noexcept -> R _REQUIRES_ITERABLE;

    template < typename IndexedFolder, typename R > 
    auto foldIndexed ( IndexedFolder const & ) const noexcept -> R _REQUIRES_ITERABLE;


    template < typename Action > 
    auto forEach ( Action const & ) const noexcept -> void _REQUIRES_ITERABLE;

    template < typename IndexedAction > 
    auto forEachIndexed ( IndexedAction const & ) const noexcept -> void _REQUIRES_ITERABLE;

    template < typename Action > 
    auto onEach ( Action const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename IndexedAction >
    auto onEachIndexed ( IndexedAction const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE; 


    template < typename Comparator > 
    auto max ( Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto maxBy ( Selector const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto maxOr ( ElementType const &, Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto maxByOr ( ElementType const &, Selector const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto min ( Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto minBy ( Selector const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto minOr ( ElementType const &, Comparator const & = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto minByOr ( ElementType const &, Selector const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    template < typename Accumulator, typename AccumulatedType >
    auto reduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto reduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE; 

    template < typename Accumulator, typename AccumulatedType >
    auto runningReduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningReduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE;

    template < typename Accumulator, typename AccumulatedType >
    auto fold ( AccumulatedType const &, Accumulator const & ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto foldIndexed ( AccumulatedType const &, IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE; 

    template < typename Accumulator, typename AccumulatedType >
    auto runningFold ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningFoldIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE; 

    template < typename Accumulator, typename AccumulatedType >
    auto scan ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto scanIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < AccumulatedType > _REQUIRES_ITERABLE; 

    
    template < typename Selector, typename R >
    auto sumBy ( Selector const & ) const noexcept -> R _REQUIRES_ITERABLE;

    
    auto chunked (Size) && noexcept -> Sequence < LinkedList < ElementType > > && _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R > 
    auto chunked (Size, ListTransformer const &) && noexcept -> Sequence < R > && _REQUIRES_ITERABLE;


    auto minus ( ElementType const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto minus ( Collection < T > const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto minus ( Sequence const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    auto plus ( ElementType const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto plus ( Collection < T > const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto plus ( Sequence const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto partition ( Predicate const & ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > > _REQUIRES_ITERABLE;

    auto windowed ( Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < ElementType > > && _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R >
    auto windowed ( ListTransformer const &, Size, Size = 1, Boolean = false ) && noexcept -> Sequence < R > && _REQUIRES_ITERABLE;

    template < typename R >
    auto zip ( Sequence < R > const & ) && noexcept -> Sequence < Pair < ElementType, R > > &&;

    template < typename R, typename Transformer, typename V >
    auto zip ( Sequence < R > const &, Transformer const & ) && noexcept -> Sequence < V > &&;

    auto zipWithNext () && noexcept -> Sequence < Pair < ElementType, ElementType > > &&;

    template < typename Transformer, typename R > 
    auto zipWithNext (Transformer const &) && noexcept -> Sequence < R > &&; 
};


#endif //CDS_SEQUENCE_HPP

//    class Queryable : public Object {
//    private:
//        ElementType _value;
//
//    public:
//        Queryable() noexcept = default;
//        Queryable(Queryable const &) noexcept = default;
//        Queryable(Queryable &&) noexcept = default;
//        ~Queryable() noexcept override = default;
//
//        explicit Queryable ( ElementType const & e ) noexcept _REQUIRES_ITERABLE : value({e}) { }
//
//        template < typename Action >
//        auto ifPresent ( Action const & ) const noexcept -> void _REQUIRES_ITERABLE;
//
//        auto orElse ( ViewValue const & ) noexcept -> ViewValue const & _REQUIRES_ITERABLE;
//
//        [[nodiscard]] auto toString () const noexcept -> String override;
//        [[nodiscard]] auto hash () const noexcept -> Index override;
//        [[nodiscard]] auto copy () const noexcept -> Queryable * override;
//        [[nodiscard]] auto operator == (Object const &) const noexcept -> bool override;
//    };