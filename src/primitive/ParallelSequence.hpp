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

public:
    class Iterator;
    class ConstIterator;

    [[nodiscard]] auto toString () const noexcept -> String override { return ""; }

    ParallelSequence () noexcept = delete;
    ParallelSequence ( ParallelSequence const & ) noexcept {}
    ParallelSequence ( ParallelSequence && ) noexcept {}

    explicit ParallelSequence ( CollectionType const & ) noexcept {}
    explicit ParallelSequence ( CollectionType && ) noexcept {}

    ~ParallelSequence () noexcept override = default;

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
            uint32 threadIndex;
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

                if ( t.state() == Worker :: State :: FINISHED ) {
                    auto iToRemove = t.getResult();
                    if ( iToRemove != -1 )
                    toRemove[ iToRemove ] = true;
                }

                if ( t.state() == Worker :: State :: STANDBY ) {
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

#endif //CDS_PARALLELSEQUENCE_HPP
