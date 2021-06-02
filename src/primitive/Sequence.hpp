//
// Created by loghin on 02.06.2021.
//

#ifndef CDS_SEQUENCE_HPP
#define CDS_SEQUENCE_HPP

#include <CDS/Object>

#if defined(__cpp_concepts)
#define _REQUIRES_ITERABLE requires Iterable < ElementType > || ConstIterable < ElementType >
#define _REQUIRES_PRINTABLE requires HasToString < ElementType >
#define _REQUIRES_INTEGRAL_ITERABLE requires Iterable < ElementType > && Integral < ElementType >
#define _REQUIRES_ITERABLE_DEF requires Iterable < typename Sequence < T, C > ::ElementType > || ConstIterable < typename Sequence < T, C > ::ElementType >
#define _REQUIRES_PRINTABLE_DEF requires HasToString < typename Sequence < T, C > ::ElementType >
#define _REQUIRES_INTEGRAL_ITERABLE_DEF requires Iterable < typename Sequence < T, C > ::ElementType > && Integral < typename Sequence < T, C > ::ElementType >
#else
#define _REQUIRES_ITERABLE
#define _REQUIRES_PRINTABLE
#define _REQUIRES_INTEGRAL_ITERABLE
#define _REQUIRES_ITERABLE_DEF
#define _REQUIRES_PRINTABLE_DEF
#define _REQUIRES_INTEGRAL_ITERABLE_DEF
#endif

#include <CDS/Boolean>
#include <CDS/Optional>
#include <CDS/Pair>
#include <CDS/Map>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/Set>

template < typename T, typename C >
class Sequence : public Object {
public:
    using ElementType = T;
    using CollectionType = C;

private:
    /**
     * can be:
     *      Unique < Foreign > representing lack of ownership, a view created over a structure outside its scope
     *      Unique < Unique > representing ownership, a structure created by the view to iterate upon
     */
    UniquePointer < PointerBase < C > > pCollection { nullptr };

public:
    class Iterator : public Object {
    public:
        using CollectionIterator = typename CollectionType::Iterator;
        using CollectionElementType = decltype ( reinterpret_cast < CollectionIterator * >(0x10)->value() );

    private:
        ForeignPointer < Sequence > pSeq;
        CollectionIterator it;

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
        using CollectionElementType = decltype ( reinterpret_cast < CollectionIterator * >(0x10)->value() );

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
    auto filterIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & _REQUIRES_ITERABLE;

    template < typename NewType >
    auto filterIsDerivedFrom () && noexcept -> Sequence < NewType, C > _REQUIRES_ITERABLE;

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
    auto associate ( Transformer const & ) && noexcept -> Sequence < Pair < K, V >, C > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateBy ( KeyGenerator const & ) && noexcept -> Sequence < Pair < K, ElementType >, C > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateBy ( KeyGenerator const &, ValueMapper const & ) && noexcept -> Sequence < Pair < K, V >, C > && _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename K >
    auto associateByTo ( Map < K, ElementType > &, KeyGenerator const & ) const noexcept -> Map < K, ElementType > & _REQUIRES_ITERABLE;

    template < typename KeyGenerator, typename ValueMapper, typename K, typename V >
    auto associateByTo ( Map < K, V > &, KeyGenerator const &, ValueMapper const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename Transformer, typename K, typename V >
    auto associateTo ( Map < K, V > &, Transformer const & ) const noexcept -> Map < K, V > & _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWith ( ValueMapper const & ) && noexcept -> Sequence < Pair < ElementType, V >, C > && _REQUIRES_ITERABLE;

    template < typename ValueMapper, typename V >
    auto associateWithTo ( Map < ElementType, V > &, ValueMapper const & ) const noexcept -> Map < ElementType , V > & _REQUIRES_ITERABLE;

    template < typename Comparator > 
    auto sort ( Comparator const & = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < ElementType, LinkedList < ElementType > > && _REQUIRES_ITERABLE;

    template < typename Selector > 
    auto sortedBy ( Selector const & ) && noexcept -> Sequence < ElementType, LinkedList < ElementType > > && _REQUIRES_ITERABLE;

    template < typename Selector >
    auto sortedByDescending ( Selector const & ) && noexcept -> Sequence < ElementType, LinkedList < ElementType > > && _REQUIRES_ITERABLE;

    template < typename Selector, typename Comparator, typename SelectorType >
    auto sortedByWith ( Selector const &, Comparator const & = []( SelectorType const & a, SelectorType const & b ) noexcept -> bool { return a < b; } ) && noexcept -> Sequence < ElementType, LinkedList < ElementType > > && _REQUIRES_ITERABLE;

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
    auto flatMap ( Transformer const & ) && noexcept -> Sequence < TransformedType, C > && _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexed ( IndexedTransformer const & ) && noexcept -> Sequence < TransformedType, C > && _REQUIRES_ITERABLE;

    template < typename Transformer, typename TransformedType >
    auto flatMapTo ( Collection < TransformedType > &, Transformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename IndexedTransformer, typename TransformedType >
    auto flatMapIndexedTo ( Collection < TransformedType > &, IndexedTransformer const & ) const noexcept -> Collection < TransformedType > & _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K > 
    auto groupBy ( KeySelector const & ) && noexcept -> Sequence < Pair < K, LinkedList < ElementType > >, C > && _REQUIRES_ITERABLE;

    template < typename KeySelector, typename ValueMapper, typename K, typename V >
    auto groupBy ( KeySelector const &, ValueMapper const & ) && noexcept -> Sequence < Pair < K, LinkedList < V > >, C > && _REQUIRES_ITERABLE;

    template < typename KeySelector, typename K, typename G > 
    auto groupByTo ( Map < K, G > &, KeySelector const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE; 

    template < typename KeySelector, typename ValueMapper, typename K, typename G >
    auto groupByTo ( Map < K, G > &, KeySelector const &, ValueMapper const & ) const noexcept -> Map < K, G > & _REQUIRES_ITERABLE;

    
    template < typename Mapper, typename R >
    auto map ( Mapper const & ) && noexcept -> Sequence < R, C > && _REQUIRES_ITERABLE;

    template < typename IndexedMapper, typename R >
    auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < R, C > && _REQUIRES_ITERABLE;

    template < typename Mapper, typename R >
    auto mapTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE; 

    template < typename IndexedMapper, typename R > 
    auto mapIndexedTo ( Collection < R > &, IndexedMapper const & ) const noexcept -> Collection < R > & _REQUIRES_ITERABLE;


    auto indexed () && noexcept -> Sequence < Pair < Index, ElementType >, C > && _REQUIRES_ITERABLE;

    auto distinct () && noexcept -> Sequence < ElementType, UnorderedSet < ElementType > > && _REQUIRES_ITERABLE;

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
    auto runningReduce ( Accumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningReduceIndexed ( IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    template < typename Accumulator, typename AccumulatedType >
    auto fold ( AccumulatedType const &, Accumulator const & ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto foldIndexed ( AccumulatedType const &, IndexedAccumulator const &, AccumulatedType const & = AccumulatedType() ) const noexcept -> AccumulatedType _REQUIRES_ITERABLE; 

    template < typename Accumulator, typename AccumulatedType >
    auto runningFold ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto runningFoldIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    template < typename Accumulator, typename AccumulatedType >
    auto scan ( AccumulatedType const &, Accumulator const & ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    template < typename IndexedAccumulator, typename AccumulatedType >
    auto scanIndexed ( AccumulatedType const &, IndexedAccumulator const & ) && noexcept -> Sequence < AccumulatedType, C > _REQUIRES_ITERABLE;

    
    template < typename Selector, typename R >
    auto sumBy ( Selector const & ) const noexcept -> R _REQUIRES_ITERABLE;

    
    auto chunked (Size) && noexcept -> Sequence < LinkedList < ElementType >, C > && _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R > 
    auto chunked (Size, ListTransformer const &) && noexcept -> Sequence < R, C > && _REQUIRES_ITERABLE;


    auto minus ( ElementType const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto minus ( Collection < T > const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto minus ( Sequence const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;

    auto plus ( ElementType const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto plus ( Collection < T > const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;
    auto plus ( Sequence const & ) && noexcept -> Sequence && _REQUIRES_ITERABLE;


    template < typename Predicate >
    auto partition ( Predicate const & ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > > _REQUIRES_ITERABLE;

    auto windowed ( Size, Size = 1, Boolean = false ) && noexcept -> Sequence < LinkedList < ElementType >, C > && _REQUIRES_ITERABLE;

    template < typename ListTransformer, typename R >
    auto windowed ( ListTransformer const &, Size, Size = 1, Boolean = false ) && noexcept -> Sequence < R, C > && _REQUIRES_ITERABLE;

    template < typename R >
    auto zip ( Sequence < R, C > const & ) && noexcept -> Sequence < Pair < ElementType, R >, C > && _REQUIRES_ITERABLE;

    template < typename R, typename Transformer, typename V >
    auto zip ( Sequence < R, C > const &, Transformer const & ) && noexcept -> Sequence < V, C > && _REQUIRES_ITERABLE;

    auto zipWithNext () && noexcept -> Sequence < Pair < ElementType, ElementType >, C > && _REQUIRES_ITERABLE;

    template < typename Transformer, typename R > 
    auto zipWithNext (Transformer const &) && noexcept -> Sequence < R, C > && _REQUIRES_ITERABLE;
};

/// region Ctors Dtors Copy Move Clear
template < typename T, typename C >
inline Sequence < T, C > ::Sequence ( Sequence const & s ) noexcept :
        pCollection ( new ForeignPointer ( s.pCollection.valueAt().get() ) ) {

}

template < typename T, typename C >
inline Sequence < T, C > ::Sequence ( Sequence && s ) noexcept :
        pCollection ( s.pCollection.valueAt().release() ) {

}

template < typename T, typename C >
inline Sequence < T, C > ::Sequence ( C const & c ) noexcept :
        pCollection ( new ForeignPointer ( & c ) ) {

}

template < typename T, typename C >
inline Sequence < T, C > ::Sequence ( C && c ) noexcept :
        pCollection ( new UniquePointer ( new C (std::move(c)) ) ) {

}

template < typename T, typename C >
inline auto Sequence < T, C > ::operator = ( Sequence const & s ) noexcept -> Sequence & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( new ForeignPointer ( s.pCollection.valueAt().valueAt() ) );

    return * this;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::operator = ( Sequence && s ) noexcept -> Sequence & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( new UniquePointer ( s.pCollection.valueAt().release() ) );

    return * this;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::clear() noexcept -> void {
    this->pCollection.reset();
}

/// endregion

/// region Iterator Support

template < typename T, typename C >
inline auto Sequence < T, C > ::begin() noexcept -> Iterator {
    return Sequence::Iterator ( this, this->pCollection.valueAt().valueAt().begin() );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::end() noexcept -> Iterator {
    return Sequence::Iterator ( this, this->pCollection.valueAt().valueAt().end() );
}

template < typename T, typename C >
inline Sequence < T, C >::Iterator::Iterator(Sequence < T, C > * pSequence, CollectionIterator const & it) noexcept :
        pSeq ( pSequence ),
        it (it) {

}

#include <sstream>

template < typename T, typename C >
auto Sequence < T, C > ::Iterator::toString() const noexcept -> String {
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

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::hash() const noexcept -> Index {
    if constexpr( isObjectDerived < decltype ( this->it ) > ::value )
        return this->it.hash ();
    else if constexpr ( isObjectDerived < decltype ( * this->it ) > ::value )
        return (* this->it).hash ();
    else
        return 0;

}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::copy() const noexcept -> Iterator * {
    return new Iterator (* this);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::value() const noexcept -> CollectionElementType {
    return this->it.value();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::next() noexcept -> Iterator & {
    this->it.next();
    return * this;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::equals(Iterator const & otherIt) const noexcept -> Boolean {
    return this->it == otherIt.it;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator==(Iterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator!=(Iterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator++() noexcept -> Iterator & {
    return this->next();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator++(int) noexcept -> Iterator {
    auto c = * this; this->next(); return c;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::Iterator::operator*() const noexcept -> CollectionElementType {
    return this->value();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::begin() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::end() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::cbegin() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::cend() const noexcept -> ConstIterator {
    return Sequence::ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename T, typename C >
inline Sequence < T, C >::ConstIterator::ConstIterator(Sequence < T, C > const * pSequence, CollectionIterator const & it) noexcept :
        pSeq ( pSequence ),
        it (it) {

}

#include <sstream>

template < typename T, typename C >
auto Sequence < T, C > ::ConstIterator::toString() const noexcept -> String {
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

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::hash() const noexcept -> Index {
    if constexpr( isObjectDerived < decltype ( this->it ) > ::value )
        return this->it.hash ();
    else if constexpr ( isObjectDerived < decltype ( * this->it ) > ::value )
        return (* this->it).hash ();
    else
        return 0;

}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::copy() const noexcept -> ConstIterator * {
    return new ConstIterator (* this);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::value() const noexcept -> CollectionElementType {
    return this->it.value();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::next() noexcept -> ConstIterator & {
    this->it.next();
    return * this;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::equals(ConstIterator const & otherIt) const noexcept -> Boolean {
    return this->it == otherIt.it;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator==(ConstIterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator!=(ConstIterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator++() noexcept -> ConstIterator & {
    return this->next();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator++(int) noexcept -> ConstIterator {
    auto c = * this; this->next(); return c;
}

template < typename T, typename C >
inline auto Sequence < T, C > ::ConstIterator::operator*() const noexcept -> CollectionElementType {
    return this->value();
}

/// endregion

/// region Object Derived Functions

template < typename T, typename C >
auto Sequence < T, C > ::toString() const noexcept -> String {
    std::stringstream oss;

    oss << "Sequence { elements = [ ";

    for ( auto e : * this )
        if constexpr ( isPrintable < ElementType >::value )
            oss << e << ", ";
        else
            oss << "Object at 0x" << std::hex << reinterpret_cast < AddressValueType > ( & e ) << ", ";

    auto s = oss.str();
    return s.substr(s.size() - 2).append(" ]}");
}

template < typename T, typename C >
inline auto Sequence < T, C > ::hash() const noexcept -> Index {
    return this->pCollection.valueAt().hash();
}

template < typename T, typename C >
inline auto Sequence < T, C > ::copy() const noexcept -> Sequence<T, C> * {
    return new Sequence ( * this );
}

template < typename T, typename C >
inline auto Sequence < T, C > ::operator==(Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > (& o);
    if ( p == nullptr ) return false;

    return this->pCollection == p->pCollection;
}


/// endregion

/// region template deduction

Sequence ( String ) -> Sequence < char, String >;

template < typename T >
Sequence ( Array < T > ) -> Sequence < T, Array < T > >;

//template < typename T >
//Sequence ( DoubleLinkedList < T > ) -> Sequence < T, DoubleLinkedList < T > >;

template < typename T >
Sequence ( DoubleLinkedList < T > ) -> Sequence < decltype ( reinterpret_cast < typename DoubleLinkedList <T> ::Iterator * > (0x10)->value() ), DoubleLinkedList < T > >;

template < typename T >
Sequence ( OrderedSet < T > ) -> Sequence < T, OrderedSet < T > >;

template < typename T >
Sequence ( UnorderedSet < T > ) -> Sequence < T, UnorderedSet < T > >;

template < typename K, typename V >
Sequence ( HashMap < K, V > ) -> Sequence < Pair < K, V >, HashMap < K, V > >;

#include <CDS/JSON>
Sequence ( JSON ) -> Sequence < std::remove_reference < decltype ( reinterpret_cast < JSON * > ( 0x10 )->begin().value() ) > ::type , JSON >;

#include <CDS/Generator>
template < typename T, typename ... Args >
Sequence ( Generator < T, Args ... > ) -> Sequence < decltype ( reinterpret_cast < typename Generator < T, Args ... > ::IterableObject * > ( 0x00 )->begin().operator*() ), Generator < T, Args ... > >;

#include <CDS/Range>
Sequence ( Range ) -> Sequence < decltype ( reinterpret_cast < Range::Iterator * > (0x10)->value() ), Range >;

/// endregion

#endif //CDS_SEQUENCE_HPP
