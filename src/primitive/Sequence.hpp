//
// Created by loghin on 02.06.2021.
//

#ifndef CDS_SEQUENCE_HPP
#define CDS_SEQUENCE_HPP

#include <CDS/Object>

#if defined(__cpp_concepts)
#define _REQUIRES_ITERABLE requires Iterable < C > || ConstIterable < C >
#define _REQUIRES_PRINTABLE requires HasToString < C >
#define _REQUIRES_INTEGRAL_ITERABLE requires Iterable < C > && Integral < C >
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
#include <CDS/Types>

template < typename C >
class Sequence : public Object {
public:
    using CollectionType = C;

private:

    using IterableValue     = decltype ( dataTypes::unsafeAddress < typename C::Iterator > ()->value() );
    using ElementType       = typename std::remove_reference < IterableValue > :: type;
    using StoredPredicate   = std::function < bool (IterableValue) >;
    using StoredMapper      = std::function < std::remove_reference_t < IterableValue > (IterableValue) >;

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

    LinkedList < Pair < SharedPointer < StoredPredicate >,  Index > > storedPredicates;
    LinkedList < Pair < SharedPointer < StoredMapper >,     Index > > storedMappers;

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

    public:
        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto hash () const noexcept -> Index override;
        [[nodiscard]] auto copy () const noexcept -> Iterator * override;
        [[nodiscard]] auto operator == (Object const &) const noexcept -> bool override;

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

    public:
        [[nodiscard]] auto toString () const noexcept -> String override;
        [[nodiscard]] auto hash () const noexcept -> Index override;
        [[nodiscard]] auto copy () const noexcept -> ConstIterator * override;
        [[nodiscard]] auto operator == (Object const &) const noexcept -> bool override;

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

    explicit Sequence ( C const & ) noexcept;
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
    [[nodiscard]] auto operator == (Object const &) const noexcept -> bool override;

    auto contains ( ElementType const & ) const noexcept -> Boolean _REQUIRES_ITERABLE;

    auto elementAt ( Index ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    auto elementAtOr ( Index, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto indexOf ( ElementType const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    auto lastIndexOf ( ElementType const & ) const noexcept -> Index _REQUIRES_ITERABLE;

    auto indicesOf ( ElementType const & ) const noexcept -> Array < Index > _REQUIRES_ITERABLE;


    template < typename Action >
    auto apply ( Action const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;

    template < typename Action >
    auto also ( Action const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto find ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto first ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto firstOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto findLast ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto last ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto lastOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto single () const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    auto singleOr ( ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto single ( Predicate const & ) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto singleOr ( Predicate const &, ElementType const & ) const noexcept -> ElementType _REQUIRES_ITERABLE;


    auto drop (Size) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto dropWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence _REQUIRES_ITERABLE;

    auto take (Size) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto takeWhile (Predicate const &, Size = UINT64_MAX) && noexcept -> Sequence _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto filter ( Predicate const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterIndexed ( IndexedPredicate const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto filterTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename NewType >
    auto filterIsDerivedFrom () && noexcept -> Sequence < C > _REQUIRES_ITERABLE;

    template < typename NewType >
    auto filterIsDerivedFromTo ( Collection < ElementType > & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename Predicate >
    auto filterNot ( Predicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    template < typename IndexedPredicate >
    auto filterNotIndexed ( IndexedPredicate const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

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
    auto associate ( Transformer const & ) && noexcept -> Sequence < LinkedList < Pair < K, V > > > _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateBy ( KeyGenerator const & ) && noexcept -> Sequence < LinkedList < Pair < K, ElementType > > >  _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateBy ( KeyGenerator const &, ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < K, V > > > _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateByTo ( Map < K, ElementType > &, KeyGenerator const & ) const noexcept -> Map < K, ElementType > & _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateByTo ( Map < K, V > &, KeyGenerator const &, ValueMapper const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename Transformer, typename K, typename V >
    auto associateTo ( Map < K, V > &, Transformer const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWith ( ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < ElementType, V > > >  _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWithTo ( Map < ElementType, V > &, ValueMapper const & ) const noexcept -> Map < ElementType , V > & _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto sort ( Comparator const & = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < LinkedList < ElementType > >  _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto sortedBy ( Selector const & ) && noexcept -> Sequence < LinkedList < ElementType > > _REQUIRES_ITERABLE;

    template < typename Selector >
    auto sortedByDescending ( Selector const & ) && noexcept -> Sequence < LinkedList < ElementType > > _REQUIRES_ITERABLE;

    template < typename Selector, typename Comparator, typename SelectorType >
    auto sortedByWith ( Selector const &, Comparator const & = []( SelectorType const & a, SelectorType const & b ) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < LinkedList < ElementType > >  _REQUIRES_ITERABLE;

    template < typename Collection > 
    auto asCollection () const noexcept -> Collection _REQUIRES_ITERABLE;

    auto asLinkedList () const noexcept -> LinkedList < ElementType > _REQUIRES_ITERABLE;

    auto asArray () const noexcept -> Array < ElementType > _REQUIRES_ITERABLE;

    template < typename Comparator >
    auto asOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator > _REQUIRES_ITERABLE;

    auto asUnorderedSet () const noexcept -> UnorderedSet < ElementType > _REQUIRES_ITERABLE;

    // auto asHashMap  look into View::toMap


    template < typename Collection >
    auto toCollection (Collection &) const noexcept -> Collection & _REQUIRES_ITERABLE;

    auto toLinkedList (LinkedList < ElementType > &) const noexcept -> LinkedList < ElementType > & _REQUIRES_ITERABLE;

    auto toArray (Array <ElementType> &) const noexcept -> Array < ElementType > & _REQUIRES_ITERABLE;

    template < typename Comparator >
    auto toOrderedSet (OrderedSet <ElementType, Comparator> &) const noexcept -> OrderedSet < ElementType, Comparator > & _REQUIRES_ITERABLE;

    auto toUnorderedSet (UnorderedSet <ElementType> &) const noexcept -> UnorderedSet < ElementType > & _REQUIRES_ITERABLE;

    
    template < typename Transformer, typename TransformedType >
    auto flatMap ( Transformer const & ) && noexcept -> Sequence < LinkedList < TransformedType > > _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexed ( IndexedTransformer const & ) && noexcept -> Sequence < LinkedList < TransformedType > > _REQUIRES_ITERABLE;

    template < typename Transformer, typename TransformedType >
    auto flatMapTo ( Collection < TransformedType > &, Transformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexedTo ( Collection < TransformedType > &, IndexedTransformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K > 
    auto groupBy ( KeySelector const & ) && noexcept -> Sequence < LinkedList < Pair < K, LinkedList < ElementType > > > > _REQUIRES_ITERABLE;

    template < typename KeySelector, typename ValueMapper, typename K, typename V >
    auto groupBy ( KeySelector const &, ValueMapper const & ) && noexcept -> Sequence < LinkedList < Pair < K, LinkedList < V > > > > _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K, typename G > 
    auto groupByTo ( Map < K, G > &, KeySelector const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE; 

    template < typename KeySelector, typename ValueMapper, typename K, typename G >
    auto groupByTo ( Map < K, G > &, KeySelector const &, ValueMapper const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE;

    /**
     * Two versions of map, one for storage of mappers when keeping same type, another for switching to another data type
     */

    template < typename Mapper, typename std::enable_if <
                    ! std::is_same_v <
                            ElementType,
                            returnOf < Mapper >
                    >,
                    int
            >::type = 0
    >
    auto map ( Mapper const & m ) && noexcept ->
    Sequence < LinkedList < returnOf < Mapper > > > _REQUIRES_ITERABLE;

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
    auto map ( Mapper const & m ) && noexcept -> Sequence < C > _REQUIRES_ITERABLE;

    template < typename IndexedMapper, typename R >
    auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < C > && _REQUIRES_ITERABLE;

    template < typename Mapper, typename R >
    auto mapTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE; 

    template < typename IndexedMapper, typename R > 
    auto mapIndexedTo ( Collection < R > &, IndexedMapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE;


    auto indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > > _REQUIRES_ITERABLE;

    auto distinct () && noexcept -> Sequence < UnorderedSet < ElementType > > _REQUIRES_ITERABLE;

    template < typename Folder, typename R >
    auto fold ( Folder const & ) const noexcept -> R _REQUIRES_ITERABLE;

    template < typename IndexedFolder, typename R > 
    auto foldIndexed ( IndexedFolder const & ) const noexcept -> R _REQUIRES_ITERABLE;


    template < typename Action > 
    auto forEach ( Action const & ) const noexcept -> void _REQUIRES_ITERABLE;

    template < typename IndexedAction > 
    auto forEachIndexed ( IndexedAction const & ) const noexcept -> void _REQUIRES_ITERABLE;

    template < typename Action > 
    auto onEach ( Action const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;

    template < typename IndexedAction >
    auto onEachIndexed ( IndexedAction const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;


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
    auto runningReduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningReduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    template < typename Accumulator, typename AccumulatedType >
    auto fold ( AccumulatedType const &, Accumulator const & ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto foldIndexed ( AccumulatedType const &, IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE; 

    template < typename Accumulator, typename AccumulatedType >
    auto runningFold ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningFoldIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    template < typename Accumulator, typename AccumulatedType >
    auto scan ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto scanIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < LinkedList < AccumulatedType > > _REQUIRES_ITERABLE;

    
    template < typename Selector, typename R >
    auto sumBy ( Selector const & ) const noexcept -> R _REQUIRES_ITERABLE;

    
    auto chunked (Size) && noexcept -> Sequence < LinkedList < LinkedList < ElementType > > > _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R > 
    auto chunked (Size, ListTransformer const &) && noexcept -> Sequence < LinkedList < R > > _REQUIRES_ITERABLE;


    auto minus ( ElementType const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;
    auto minus ( Collection < ElementType > const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;
    auto minus ( Sequence const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;

    auto plus ( ElementType const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;
    auto plus ( Collection < ElementType > const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;
    auto plus ( Sequence const & ) && noexcept -> Sequence _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto partition ( Predicate const & ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > > _REQUIRES_ITERABLE;

    auto windowed ( Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < LinkedList < ElementType > > >  _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R >
    auto windowed ( ListTransformer const &, Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < R > >  _REQUIRES_ITERABLE;

    template < typename S >
    auto zip ( Sequence < S > const & ) && noexcept -> Sequence < LinkedList < Pair < ElementType, typename S::ElementType > > >  _REQUIRES_ITERABLE;

    template < typename S, typename Transformer, typename V >
    auto zip ( Sequence < S > const &, Transformer const & ) && noexcept -> Sequence < LinkedList < V > >  _REQUIRES_ITERABLE;

    auto zipWithNext () && noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > > _REQUIRES_ITERABLE;

    template < typename Transformer, typename R > 
    auto zipWithNext (Transformer const &) && noexcept -> Sequence < LinkedList < R > > _REQUIRES_ITERABLE;
};

/// region Ctors Dtors Copy Move Clear
template < typename C >
inline Sequence < C > ::Sequence ( Sequence const & s ) noexcept :
        pCollection ( new ForeignPointer ( s.pCollection.valueAt().get() ) ),
        chainCount ( s.chainCount ),
        storedMappers ( s.storedMappers ),
        storedPredicates ( s.storedPredicates ){

}

template < typename C >
inline Sequence < C > ::Sequence ( Sequence && s ) noexcept :
        pCollection ( new UniquePointer ( s.pCollection.valueAt().release() ) ),
        chainCount ( std::exchange ( s.chainCount, 0 ) + 1 ),
        storedMappers ( std::move ( s.storedMappers ) ),
        storedPredicates ( std::move ( s.storedPredicates ) ){

}

template < typename C >
inline Sequence < C > ::Sequence ( C const & c ) noexcept :
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
    this->chainCount = s.chainCount;
    this->storedMappers = s.storedMappers;
    this->storedPredicates = s.storedPredicates;

    return * this;
}

template < typename C >
inline auto Sequence < C > ::operator = ( Sequence && s ) noexcept -> Sequence & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( new UniquePointer ( s.pCollection.valueAt().release() ) );
    this->chainCount = std::exchange ( s.chainCount, 0 ) + 1;
    this->storedMappers = std::move (s.storedMappers);
    this->storedPredicates = std::move (s.storedPredicates);

    return * this;
}

template < typename C >
inline auto Sequence < C > ::clear() noexcept -> void {
    this->pCollection.reset();
    this->chainCount = 0;
    this->storedMappers.clear();
    this->storedPredicates.clear();
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

        for ( uint32 i = 0; i < this->pSeq.valueAt().chainCount; i ++ ) {
            if ( currentMapperIterator != this->pSeq.valueAt().storedMappers.end() && currentMapperIterator.value().getSecond() == i ) {
                this->precomputed = ( * currentMapperIterator.value().getFirst() ) ( this->precomputed );
                currentMapperIterator.next();
            } else if ( currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() && currentFilterIterator.value().getSecond() == i ) {
                if ( ! (* currentFilterIterator.value().getFirst())( this->precomputed ) ) {
                    skip = true;
                    break;
                }
                currentFilterIterator.next();
            } else if ( currentFilterIterator == this->pSeq.valueAt().storedPredicates.end() && currentMapperIterator == this->pSeq.valueAt().storedMappers.end() )
                break;
        }

        if ( ! skip ) {
            while (currentMapperIterator != this->pSeq.valueAt().storedMappers.end()) {
                this->precomputed = (*currentMapperIterator.value().getFirst())(this->precomputed);
                currentMapperIterator++;
            }
        }
        else
            this->it.next();
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
inline auto Sequence < C > ::Iterator::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
inline auto Sequence < C > ::Iterator::value() const noexcept -> CollectionElementType {
//    ElementType v = this->it.value();
//    this->pSeq->storedMappers.forEach([&v](auto p){v = (*p.getFirst())(v);});
//    return v;
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
inline auto Sequence < C > ::ConstIterator::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::value() const noexcept -> CollectionElementType {
    ElementType v = this->it.value();
    this->pSeq->storedMappers.forEach([&v](auto p){v = (*p.getFirst())(v);});
    return v;
}

template < typename C >
inline auto Sequence < C > ::ConstIterator::next() noexcept -> ConstIterator & {
    this->it.next();
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
    return s.substr(s.size() - 2).append(" ]}");
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
inline auto Sequence < C > ::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > (& o);
    if ( p == nullptr ) return false;

    return this->pCollection == p->pCollection;
}


/// endregion

/// region template deduction

Sequence ( String ) -> Sequence < String >;

template < typename T >
Sequence ( Array < T > ) -> Sequence < Array < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > ) -> Sequence < DoubleLinkedList < T > >;

template < typename T >
Sequence ( OrderedSet < T > ) -> Sequence < OrderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > ) -> Sequence < UnorderedSet < T > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > ) -> Sequence < HashMap < K, V > >;

#include <CDS/JSON>
Sequence ( JSON ) -> Sequence < JSON >;

#include <CDS/Generator>
template < typename T, typename ... Args >
Sequence ( Generator < T, Args ... > ) -> Sequence < Generator < T, Args ... > >;

#include <CDS/Range>
Sequence ( Range ) -> Sequence < Range >;

/// endregion

// region basic ownership pass functions

template < typename C >
template <
    typename Mapper,
    typename std::enable_if <
        ! std::is_same_v <
            typename std::remove_reference <
                decltype ( dataTypes::unsafeAddress < typename C::Iterator > ()->value() )
            > :: type,
            returnOf < Mapper >
        >,
        int
    >::type
>
auto Sequence < C > :: map ( Mapper const & mapper ) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > > _REQUIRES_ITERABLE {
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
                decltype ( dataTypes::unsafeAddress < typename C::Iterator > ()->value() )
            > :: type,
            returnOf < Mapper >
        >::type::value,
        int
    >::type
>
auto Sequence < C > ::map(Mapper const & mapper) && noexcept -> Sequence < C >  _REQUIRES_ITERABLE {
    this->storedMappers.append({ { new StoredMapper(mapper) }, this->chainCount });
    return std::move ( * this );
}

template < typename C >
template < typename Predicate >
auto Sequence < C > ::filter(Predicate const & predicate) && noexcept -> Sequence < C > _REQUIRES_ITERABLE {
    this->storedPredicates.append({ { new StoredPredicate (predicate)}, this->chainCount });
    return std::move ( * this );
}

// endregion

// region Basic Utility Functions

template < typename C >
inline auto Sequence < C > ::contains(ElementType const & e) const noexcept -> Boolean _REQUIRES_ITERABLE {
    for ( auto v : * this )
        if ( e == v )
            return true;
    return false;
}

template < typename C >
inline auto Sequence < C > ::elementAt(Index i) const noexcept -> Optional < ElementType > _REQUIRES_ITERABLE {
    Index at = 0;
    for ( auto v : * this )
        if ( at == i )
            return { v };
        else
            at ++;

    return { };
}

// endregion

// region Terminal Operations

template < typename C >
template < typename Action >
inline auto Sequence < C > :: forEach ( Action const & action ) const noexcept -> void _REQUIRES_ITERABLE {
    for ( auto e : * this ) action (e);
}

// endregion

// region Terminal Extender Operations

template < typename C >
template < typename Action >
inline auto Sequence < C > :: apply ( Action const & action ) && noexcept -> Sequence < C > _REQUIRES_ITERABLE {
    action();
    return std::move(* this);
}

template < typename C >
template < typename Action >
inline auto Sequence < C > :: also ( Action const & action ) && noexcept -> Sequence < C > _REQUIRES_ITERABLE {
    action();
    return std::move(* this);
}

template < typename C >
template < typename Action >
inline auto Sequence < C > :: onEach ( Action const & action ) && noexcept -> Sequence _REQUIRES_ITERABLE {
    for ( auto e : * this ) action (e);
    return std::move(*this);
}

// endregion

#endif //CDS_SEQUENCE_HPP
