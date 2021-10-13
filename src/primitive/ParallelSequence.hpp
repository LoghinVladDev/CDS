//
// Created by loghin on 30.08.2021.
//

#ifndef CDS_PARALLELSEQUENCE_HPP
#define CDS_PARALLELSEQUENCE_HPP

#include <CDS/Object>

#include <CDS/Boolean>
#include <CDS/Optional>
#include <CDS/Pair>
#include <CDS/Map>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/Set>
#include <CDS/Types>

#include <CDS/Thread>

template < typename C >
class ParallelSequence : public Object {
public:
    using CollectionType                = C;

private:
    using ClassName                     = typename std::remove_reference < C > :: type;
    using IterableValue                 = decltype ( dataTypes::unsafeAddress < typename ClassName::Iterator > () -> value () );

public:
    using ElementType                   = typename std::remove_reference < IterableValue > :: type;

debug_private:
    using StoredPredicate               = std::function < bool (IterableValue) >;
    using StoredMapper                  = std::function < std::remove_reference_t < IterableValue > ( IterableValue ) >;

    using StoredIndexedPredicate        = std::function < bool (Index, IterableValue) >;
    using StoredIndexedMapper           = std::function < std::remove_reference_t < IterableValue > ( Index, IterableValue ) >;

    using StoredPredicateList           = LinkedList < Pair < SharedPointer < StoredPredicate >, Index > >;
    using StoredMapperList              = LinkedList < Pair < SharedPointer < StoredMapper >, Index > >;
    using StoredIndexedPredicateList    = LinkedList < Pair < SharedPointer < StoredIndexedPredicate >, Index > >;
    using StoredIndexedMapperList       = LinkedList < Pair < SharedPointer < StoredIndexedMapper >, Index > >;

    friend class Iterator;
    friend class ConstIterator;

    /**
     * can be:
     *      Unique < Foreign > representing lack of ownership, a view created over a structure outside its scope
     *      Unique < Unique > representing ownership, a structure created by the view to iterate upon
     */
    UniquePointer < PointerBase < C > >                                     pCollection { nullptr };
    uint16                                                                  chainCount  { 0 }; // used to determine order of operations

    // TODO
    //    When #3 Address Move Semantics Issues in regards to Collection Move Operations - is fixed
    //    LinkedList < Pair < UniquePointer < StoredPredicate >,  Index > > storedPredicates;
    //    LinkedList < Pair < UniquePointer < StoredMapper >,     Index > > storedMappers;

    StoredPredicateList storedPredicates;
    StoredMapperList storedMappers;

    StoredIndexedPredicateList storedIndexedPredicates;
    StoredIndexedMapperList storedIndexedMappers;

private:
    auto clear () noexcept -> void;

public:

    ParallelSequence () noexcept = delete;
    ParallelSequence ( ParallelSequence const & ) noexcept;
    ParallelSequence ( ParallelSequence && ) noexcept;

    explicit ParallelSequence ( CollectionType const & ) noexcept;
    explicit ParallelSequence ( CollectionType && ) noexcept;

    ~ParallelSequence () noexcept override = default;

    auto operator = ( ParallelSequence const & ) noexcept -> ParallelSequence &;
    auto operator = ( ParallelSequence && ) noexcept -> ParallelSequence &;


//     TODO :
//
//     auto begin () noexcept -> ;
//     auto end () noexcept -> ;
//
//     auto begin () const noexcept -> ;
//     auto end () const noexcept -> ;
//     auto cbegin () const noexcept -> ;
//     auto cend () const noexcept -> ;

    __CDS_NoDiscard __CDS_MaybeUnused auto toString () const noexcept -> String override;
    __CDS_NoDiscard __CDS_MaybeUnused auto hash () const noexcept -> Index override;
    __CDS_NoDiscard __CDS_MaybeUnused auto copy () const noexcept -> ParallelSequence * override;
    __CDS_NoDiscard __CDS_MaybeUnused auto equals (Object const &) const noexcept -> bool override;

    __CDS_NoDiscard __CDS_MaybeUnused auto contains ( ElementType const & ) const noexcept -> Boolean __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto elementAt ( Index ) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto elementAtOr ( Index, ElementType const & ) const noexcept -> ElementType __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto indexOf ( ElementType const & ) const noexcept -> Index __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto lastIndexOf ( ElementType const & ) const noexcept -> Index __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto indicesOf ( ElementType const & ) const noexcept -> LinkedList < Index > __CDS_Requires ( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    __CDS_MaybeUnused auto apply ( Action const & ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    __CDS_MaybeUnused auto also ( Action const & ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );


    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto find ( Predicate const & ) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto first ( Predicate const & = [](ElementType const &) noexcept -> bool {return true;} ) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto firstOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool {return true;} ) const noexcept -> ElementType __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto findLast ( Predicate const & ) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto last ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; }) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto lastOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> ElementType __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto single ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Optional < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto singleOr ( ElementType const &, Predicate const & = [](ElementType const &) noexcept -> bool { return true; }) const noexcept -> ElementType __CDS_Requires( Iterable < C > || ConstIterable < C > );


    __CDS_MaybeUnused auto drop ( Size ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_MaybeUnused auto dropWhile ( Predicate const & p, Size = UINT64_MAX ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    __CDS_MaybeUnused auto take ( Size ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires ( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_MaybeUnused auto takeWhile ( Predicate const &, Size = UINT64_MAX ) && noexcept -> ParallelSequence < LinkedList < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_MaybeUnused auto filter ( Predicate const & ) && noexcept -> ParallelSequence __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    __CDS_MaybeUnused auto filterIndexed ( IndexedPredicate const & ) && noexcept -> ParallelSequence __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_MaybeUnused auto filterTo ( Collection < ElementType > const &, Predicate const & ) const noexcept -> Collection < ElementType > & __CDS_Requires ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    __CDS_MaybeUnused auto filterIndexedTo ( Collection < ElementType > const &, IndexedPredicate const & ) const noexcept -> Collection < ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename NewType >
    __CDS_MaybeUnused auto filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > > __CDS_Requires( ( Iterable < C > || ConstIterable < C > ) && Pointer < ElementType > && Pointer < NewType > );

    template < typename NewType >
    __CDS_MaybeUnused auto filterIsDerivedTo ( Collection < ElementType > & ) const noexcept -> Collection < ElementType > & __CDS_Requires( ( Iterable < C > || ConstIterable < C > ) && Pointer < ElementType > && Pointer < NewType > );

    template < typename Predicate >
    __CDS_MaybeUnused auto filterNot ( Predicate const & ) && noexcept -> ParallelSequence __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    __CDS_MaybeUnused auto filterNotIndexed ( IndexedPredicate const & ) && noexcept -> ParallelSequence __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_MaybeUnused auto filterNotTo ( Collection < ElementType > &, Predicate const & ) const noexcept -> Collection < ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename IndexedPredicate >
    __CDS_MaybeUnused auto filterNotIndexedTo ( Collection < ElementType > &, IndexedPredicate const & ) const noexcept -> Collection < ElementType  > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto indexOfFirst ( Predicate const & ) const noexcept -> Index __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto indexOfLast ( Predicate const & ) const noexcept -> Index __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto indicesOfAll ( Predicate const & ) const noexcept -> LinkedList < Index > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto any ( Predicate const & = [](ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Boolean __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate >
    __CDS_NoDiscard __CDS_MaybeUnused auto all ( Predicate const & ) const noexcept -> Boolean __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto count ( Predicate const & = [] (ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Size __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto none ( Predicate const & = [] (ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Boolean __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Predicate = std :: function < bool ( ElementType const & ) > >
    __CDS_NoDiscard __CDS_MaybeUnused auto one ( Predicate const & = [] (ElementType const &) noexcept -> bool { return true; } ) const noexcept -> Boolean __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename std :: enable_if < isPair < returnOf < Transformer > > :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto associate ( Transformer const & ) && noexcept -> ParallelSequence < LinkedList < returnOf < Transformer > > > __CDS_Requires( ( Iterable < C > || ConstIterable < C > ) && PairType < returnOf < Transformer > > );

    template < typename KeyGenerator >
    __CDS_MaybeUnused auto associateBy ( KeyGenerator const & ) && noexcept -> ParallelSequence < LinkedList < Pair < returnOf < KeyGenerator >, ElementType > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    __CDS_MaybeUnused auto associateBy ( KeyGenerator const &, ValueMapper const & ) && noexcept -> ParallelSequence < LinkedList < Pair < returnOf < KeyGenerator >, returnOf < ValueMapper > > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator >
    __CDS_MaybeUnused auto associateByTo ( Map < returnOf < KeyGenerator >, ElementType > &, KeyGenerator const & ) const noexcept -> Map < returnOf < KeyGenerator >, ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeyGenerator, typename ValueMapper >
    __CDS_MaybeUnused auto associateByTo ( Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > &, KeyGenerator const &, ValueMapper const & ) const noexcept -> Map < returnOf < KeyGenerator >, returnOf < ValueMapper > > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Transformer, typename K, typename V >
    __CDS_MaybeUnused auto associateTo ( Map < K, V > &, Transformer const & ) const noexcept -> Map < K, V > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    __CDS_MaybeUnused auto associateWith ( ValueMapper const & ) && noexcept -> ParallelSequence < LinkedList < Pair < ElementType, returnOf < ValueMapper > > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename ValueMapper >
    __CDS_MaybeUnused auto associateWithTo ( Map < ElementType, returnOf < ValueMapper > > &, ValueMapper const & ) const noexcept -> Map < ElementType, returnOf < ValueMapper > > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Comparator = std :: function < bool ( ElementType const &, ElementType const & ) > >
    __CDS_MaybeUnused auto sorted ( Comparator const & = [] ( ElementType const & a, ElementType const & b ) noexcept -> bool { return a < b; } ) && noexcept -> ParallelSequence < Array < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Selector, typename Comparator = std :: function < bool ( returnOf < Selector > const &, returnOf < Selector > const & ) > >
    __CDS_MaybeUnused auto sortedBy ( Selector const &, Comparator const & = [] ( returnOf < Selector > const & a, returnOf < Selector > const & b ) noexcept -> bool { return a < b; } ) && noexcept -> ParallelSequence < Array < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Collection >
    __CDS_NoDiscard __CDS_MaybeUnused auto toCollection () const noexcept -> Collection __CDS_Requires( Iterable < C > || ConstIterable < C > );

    __CDS_NoDiscard __CDS_MaybeUnused auto toLinkedList () const noexcept -> LinkedList < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto toArray () const noexcept -> Array < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_NoDiscard __CDS_MaybeUnused auto toUnorderedSet () const noexcept -> UnorderedSet < ElementType > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    __CDS_NoDiscard __CDS_MaybeUnused auto toOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Collection >
    __CDS_MaybeUnused auto toCollection ( Collection & ) const noexcept -> Collection & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    __CDS_MaybeUnused auto toLinkedList ( LinkedList < ElementType > & ) const noexcept -> LinkedList < ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_MaybeUnused auto toArray ( Array < ElementType > & ) const noexcept -> Array < ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );
    __CDS_MaybeUnused auto toUnorderedSet ( UnorderedSet < ElementType > & ) const noexcept -> UnorderedSet < ElementType > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Comparator >
    __CDS_MaybeUnused auto toOrderedSet ( OrderedSet < ElementType, Comparator > & ) const noexcept -> OrderedSet < ElementType, Comparator > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Transformer >
    __CDS_MaybeUnused auto flatMap ( Transformer const & ) && noexcept -> ParallelSequence < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename returnOf < Transformer > :: Iterator >() -> value () ) > :: type > __CDS_Requires( ( Iterable < C > || ConstIterable < C > ) && ( Iterable < returnOf < Transformer > > || ConstIterable < returnOf < Transformer > > ) );

    template < typename IndexedTransformer >
    __CDS_MaybeUnused auto flatMapIndexed ( IndexedTransformer const & ) && noexcept -> ParallelSequence < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename returnOf < IndexedTransformer > :: Iterator > () -> value () ) > :: type > __CDS_Requires( ( Iterable < C > || ConstIterable < C > ) && ( Iterable < returnOf < IndexedTransformer > > || ConstIterable < returnOf < IndexedTransformer > > ) );

    template < typename Transformer >
    __CDS_MaybeUnused auto flatMapTo ( Collection < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename returnOf < Transformer > :: Iterator > () -> value () ) > :: type > &, Transformer const & ) const noexcept -> Collection < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename returnOf < Transformer > :: Iterator > () -> value () ) > :: type > & __CDS_Requires ( ( Iterable < C > || ConstIterable < C > && ( Iterable < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename returnOf < Transformer > :: Iterator > () -> value () ) > :: type > || ConstIterable < typename std :: remove_reference < decltype ( dataTypes ::unsafeAddress < typename returnOf < Transformer > :: Iterator > () -> value () ) > :: type > ) ) );

    template < typename IndexedTransformer >
    __CDS_MaybeUnused auto flatMapIndexedTo ( Collection < typename std::remove_reference < decltype ( dataTypes::unsafeAddress < typename returnOf < IndexedTransformer > :: Iterator >()->value() ) > :: type > &, IndexedTransformer const & ) const noexcept -> Collection < typename std::remove_reference < decltype ( dataTypes::unsafeAddress < typename returnOf < IndexedTransformer > :: Iterator > ()->value() ) > :: type > & __CDS_Requires( ( Iterable < C > || ConstIterable < C >) && ( Iterable < typename std::remove_reference < decltype ( dataTypes::unsafeAddress < typename returnOf < IndexedTransformer > :: Iterator >()->value() ) > :: type > || ConstIterable < typename std::remove_reference < decltype ( dataTypes::unsafeAddress < typename returnOf < IndexedTransformer > :: Iterator >()->value() ) > :: type > ) );

    template < typename KeySelector >
    __CDS_MaybeUnused auto groupBy ( KeySelector const & ) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < ElementType > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename ValueMapper >
    __CDS_MaybeUnused auto groupBy ( KeySelector const &, ValueMapper const & ) && noexcept -> Sequence < HashMap < returnOf < KeySelector >, LinkedList < returnOf < ValueMapper > > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector >
    __CDS_MaybeUnused auto groupByTo ( Map < returnOf < KeySelector >, LinkedList < ElementType > > &, KeySelector const & ) const noexcept -> Map < returnOf < KeySelector >, LinkedList < ElementType > > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename KeySelector, typename ValueMapper >
    __CDS_MaybeUnused auto groupByTo ( Map < returnOf < KeySelector >, returnOf < ValueMapper > > &, KeySelector const &, ValueMapper const & ) const noexcept -> Map < returnOf < KeySelector >, returnOf < ElementType > > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Mapper, typename std :: enable_if < ! std :: is_same < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename std :: remove_reference < C > :: type :: Iterator > () -> value () ) > :: type, returnOf < Mapper > > :: type :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto map ( Mapper const & ) && noexcept -> Sequence < LinkedList < returnOf < Mapper > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Mapper, typename std :: enable_if < std :: is_same < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename std :: remove_reference < C > :: type :: Iterator > () -> value () ) > :: type, returnOf < Mapper > > :: type :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto map ( Mapper const & ) && noexcept -> Sequence < C > __CDS_Requires ( Iterable < C > || ConstIterable < C > );

    template < typename IndexedMapper, typename std :: enable_if < ! std :: is_same < typename std :: remove_reference < decltype ( dataTypes ::unsafeAddress < typename std :: remove_reference < C > :: type :: Iterator > () -> value () ) > :: type, returnOf < IndexedMapper > > :: type :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < LinkedList < returnOf < IndexedMapper > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename IndexedMapper, typename std :: enable_if < std :: is_same < typename std :: remove_reference < decltype ( dataTypes :: unsafeAddress < typename std :: remove_reference < C > :: type :: Iterator > () -> value () ) > :: type, returnOf < IndexedMapper > > :: type :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto mapIndexed ( IndexedMapper const & ) && noexcept -> Sequence < C > __CDS_Requires ( Iterable < C > || ConstIterable < C > );

    template < typename Mapper, typename R >
    __CDS_MaybeUnused auto mapTo ( Collection < R > &, Mapper const & ) const noexcept -> Collection < R > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename IndexedMapper, typename R >
    __CDS_MaybeUnused auto mapIndexedTo ( Collection < R > &, IndexedMapper const & ) const noexcept -> Collection < R > & __CDS_Requires( Iterable < C > || ConstIterable < C > );

    __CDS_MaybeUnused auto indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    __CDS_MaybeUnused auto distinct () && noexcept -> Sequence < UnorderedSet < ElementType > > __CDS_Requires( Iterable < C > || ConstIterable < C > );

    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) const noexcept -> void __CDS_Requires( Iterable < C > || ConstIterable < C > );



    class Worker : public Thread {
    public:
        enum State {
            STANDBY,
            READY,
            RUNNING,
            FINISHED,
        };

        struct WorkerDataContainer {
            StoredPredicateList * pPredicateList = nullptr;
            StoredMapperList * pMapperList = nullptr;
            StoredIndexedPredicateList * pIndexedPredicateList = nullptr;
            StoredIndexedMapperList * pIndexedMapperList = nullptr;

            uint32 chainCount = 0u;
            uint32 threadIndex = 0u;
        };

        WorkerDataContainer const * _pContainer = nullptr;
        ElementType * _pOrig = nullptr;
        ElementType * _pEnd = nullptr;

        [[nodiscard]] constexpr auto container () const noexcept -> WorkerDataContainer const * {
            return this->_pContainer;
        }

        [[nodiscard]] auto getResult () noexcept -> Index {
            if ( this->state() != FINISHED ) return -1;
            if ( this->_pEnd != nullptr ) return -1;
            auto i = this->_pContainer->threadIndex;

            this->state().set( STANDBY );
            return i;
        }

        Atomic < State > _state;

        Worker () noexcept {
            this->state().set ( STANDBY );
        }

        Worker ( WorkerDataContainer const * pDataContainer, ElementType * pOrig, ElementType * pEnd ) noexcept {
            this->prepare( pDataContainer, pOrig, pEnd );
        }

        auto prepare ( WorkerDataContainer const * pDataContainer, ElementType * pOrig, ElementType * pEnd ) noexcept -> Worker & {
            if ( this->state() != STANDBY )
                return * this;

            this->_pContainer = pDataContainer;
            this->_pOrig = pOrig;
            this->_pEnd = pEnd;

            this->state().set ( READY );

            return * this;
        }

        constexpr auto state () const noexcept -> Atomic < State > const & { return this->_state; }
        constexpr auto state () noexcept -> Atomic < State > & { return this->_state; }

        auto run () noexcept (false) -> void override {
            if ( this->_pContainer == nullptr || this->_pOrig == nullptr || this->_pEnd == nullptr ) {
                this->_pEnd = nullptr;
                this->state().set ( STANDBY );
                return;
            }

            this->state().set ( RUNNING );

            * this->_pEnd = * this->_pOrig;

            auto mapperIt = this->_pContainer->pMapperList->begin();
            auto filterIt = this->_pContainer->pPredicateList->begin();

            auto indexedMapperIt = this->_pContainer->pIndexedMapperList->begin();
            auto indexedFilterIt = this->_pContainer->pIndexedPredicateList->begin();

            for ( uint32 i = 0; i < this->_pContainer->chainCount; i ++ ) {

                if (
                    filterIt != this->_pContainer->pPredicateList->end() &&
                    filterIt.value().second() == i
                ) {
                    if ( ! ( * filterIt.value().first() ) ( * this->_pEnd ) ) {
                        this->_pEnd = nullptr;
                        break;
                    }

                    filterIt.next();
                } else if (
                    indexedFilterIt != this->_pContainer->pIndexedPredicateList->end() &&
                    indexedFilterIt.value().second() == i
                ) {
                    if ( ! ( * indexedFilterIt.value().first() ) ( this->_pContainer->threadIndex, * this->_pEnd ) ) {
                        this->_pEnd = nullptr;
                        break;
                    }

                    indexedFilterIt.next();
                } else if (
                    mapperIt != this->_pContainer->pMapperList->end() &&
                    mapperIt.value().second() == i
                ) {
                    * this->_pEnd = ( * mapperIt.value().first() ) ( *this->_pEnd );
                    mapperIt.next();
                } else if (
                    indexedMapperIt != this->_pContainer->pIndexedMapperList->end() &&
                    indexedMapperIt.value().second() == i
                ) {
                    * this->_pEnd = ( * indexedMapperIt.value().first() ) ( this->_pContainer->threadIndex, * this->_pEnd );
                    indexedMapperIt.next();
                } else if (
                    mapperIt        == this->_pContainer->pMapperList->end() &&
                    filterIt        == this->_pContainer->pPredicateList->end() &&
                    indexedMapperIt == this->_pContainer->pIndexedMapperList->end() &&
                    indexedFilterIt == this->_pContainer->pIndexedPredicateList->end()
                )
                    break;
            }

            this->state().set ( FINISHED );
        }
    };

    struct ParallelFilterContainer {
        StoredPredicateList         * pPredicateList        = nullptr;
        StoredMapperList            * pMapperList           = nullptr;
        StoredIndexedPredicateList  * pIndexedPredicateList = nullptr;
        StoredIndexedMapperList     * pIndexedMapperList    = nullptr;

        LinkedList < ElementType >  * pOriginalList         = nullptr;
        LinkedList < ElementType >  * pNewList              = nullptr;

        uint32                        chainCount            = 0u;
    };

    static auto filterContainer ( ParallelFilterContainer & ) noexcept -> void;
};

#include <CDS/HashMap>
template < typename C >
auto ParallelSequence < C > ::filterContainer ( ParallelFilterContainer & container ) noexcept -> void {
    if (
        container.pPredicateList == nullptr ||
        container.pMapperList == nullptr ||
        container.pIndexedPredicateList == nullptr ||
        container.pIndexedMapperList == nullptr ||

        container.pOriginalList == nullptr ||
        container.pNewList == nullptr
    )
        return;

    HashMap < Index, Boolean > toRemove;

    Array < Worker > workers;
    Array < typename Worker :: WorkerDataContainer > containers;

    LinkedList < ElementType > finals;

    workers.resize( Thread::hardwareConcurrency() );
    containers.resize ( workers.size() );

    Index i = 0;

    for ( auto & e : * container.pOriginalList ) {

        toRemove.insert( { i, false } );

        finals.pushBack( e );
        auto & newE = finals.back();

        bool threadFound = false;
        while (! threadFound) { // find from available threads

            for ( Index threadIndex = 0; threadIndex < workers.size(); threadIndex ++ ) {
                auto & t = workers[threadIndex];

                __CDS_WarningSuppression_UseScopedEnum_SuppressEnable

                if ( t.state() == Worker :: State :: FINISHED ) {

                __CDS_WarningSuppression_UseScopedEnum_SuppressDisable

                    auto iToRemove = t.getResult();
                    if ( iToRemove != -1 )
                    toRemove[ iToRemove ] = true;
                }

                __CDS_WarningSuppression_UseScopedEnum_SuppressEnable

                if ( t.state() == Worker :: State :: STANDBY ) {

                __CDS_WarningSuppression_UseScopedEnum_SuppressDisable

                    containers[threadIndex] = {
                        .pPredicateList = container.pPredicateList,
                        .pMapperList = container.pMapperList,
                        .pIndexedPredicateList = container.pIndexedPredicateList,
                        .pIndexedMapperList = container.pIndexedMapperList,

                        .chainCount = container.chainCount,
                        .threadIndex = (uint32) i ++
                    };

                    t.prepare ( & containers[threadIndex] , & e, & newE ).start();
                    threadFound = true;
                    break;
                }

            }

        }

    }

    for ( auto & t : workers ) {
        t.join();

        auto iToRemove = t.getResult();
        if ( iToRemove != -1 )
        toRemove[ iToRemove ] = true;
    }

    container.pNewList->clear();

    i = 0;
    for ( auto & e : finals ) {
        if ( ! toRemove[i++] )
            container.pNewList->pushBack( e );
    }

}

__CDS_RegisterParseTypeTemplateT(ParallelSequence)

#endif //CDS_PARALLELSEQUENCE_HPP
