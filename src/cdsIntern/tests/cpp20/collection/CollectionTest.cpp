//
// Created by loghin on 30.11.2021.
//

#include "CollectionTest.h"

#if !defined(CDS_TEST_EXPERIMENTAL)
#include <CDS/Array>

using namespace cds;

auto CollectionTest :: execute() noexcept -> bool {
    bool allOk = true;

    Array < int > arrayTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    this->executeSubtest( "Contains/Additions", [&]{

        auto arrayIntContains = []( Collection < int > & array, int value ) {
            return array.contains( value );
        };
        auto constArrayIntContains = []( Collection < int > const & array, int value ) {
            return array.contains( value );
        };

        if (
                ! arrayIntContains ( arrayTestObject, 3 ) ||
                ! constArrayIntContains ( arrayTestObject, 3 )
        ) {
            this->logWarning("Array Contains Error");
            allOk = false;
        }

        if (
                arrayIntContains ( arrayTestObject, 200 ) ||
                constArrayIntContains ( arrayTestObject, 200 )
        ) {
            this->logWarning("Array Contains Error");
            allOk = false;
        }

    });

    this->executeSubtest( "Iterative Functionals", [&]{

        auto arrayIntSum = []( cds :: Collection < int > const & array ) -> int {
            int sum = 0;
            for ( auto const & v : array )
                sum += v;
            return sum;
        };

        auto arrayIntSumForEach_paramCopy = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto v){sum += v;});
            return sum;
        };

        auto arrayIntSumForEach_paramRef = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto & v){sum += v;});
            return sum;
        };

        auto arrayIntSumForEach_paramCRef = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto const & v){sum += v;});
            return sum;
        };

        auto compareResults = [&]{

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCopy (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramRef (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCRef (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

        };

        compareResults();

        auto intArrayModify = [] ( Collection < int > & collection ) {
            collection.forEach([](auto & e){e = e * 2;});
        };

        intArrayModify ( arrayTestObject );

        compareResults();

    });

    return allOk;
}

#endif

#if defined(CDS_TEST_EXPERIMENTAL)
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>

using namespace cds;

template < template < typename ... > typename CollectionType >
auto constructionTest () noexcept -> bool {
    class DefaultCopyMove : public cds :: Object {
    public:
        DefaultCopyMove () noexcept = default;
        DefaultCopyMove ( DefaultCopyMove const & ) noexcept = default;
        DefaultCopyMove ( DefaultCopyMove && ) noexcept = default;

        auto toString () const noexcept -> String override {
            return "Default, Copy, Move";
        }
    };

    class DefaultCopy : public cds :: Object {
    public:
        DefaultCopy () noexcept = default;
        DefaultCopy ( DefaultCopy const & ) noexcept = default;
        DefaultCopy ( DefaultCopy && ) noexcept = delete;

        auto toString () const noexcept -> String override {
            return "DefaultCopy";
        }
    };

    class DefaultMove : public cds :: Object {
    public:
        DefaultMove () noexcept = default;
        DefaultMove ( DefaultMove const & ) noexcept = delete;
        DefaultMove ( DefaultMove && ) noexcept = default;

        auto toString () const noexcept -> String override {
            return "DefaultMove";
        }
    };

    class CopyMove : public cds :: Object {
    public:
        CopyMove () noexcept = delete;
        CopyMove ( CopyMove const & ) noexcept = default;
        CopyMove ( CopyMove && ) noexcept = default;

        auto toString () const noexcept -> String override {
            return "CopyMove";
        }
    };

    class Move : public cds :: Object {
    public:
        Move () noexcept = delete;
        Move ( Move const & ) noexcept = delete;
        Move ( Move && ) noexcept = default;

        auto toString () const noexcept -> String override {
            return "Move";
        }
    };

    class Copy : public cds :: Object {
    public:
        Copy () noexcept = delete;
        Copy ( Copy const & ) noexcept = default;
        Copy ( Copy && ) noexcept = delete;

        auto toString () const noexcept -> String override {
            return "Copy";
        }
    };

    class Default : public cds :: Object {
    public:
        Default () noexcept = default;
        Default ( Default const & ) noexcept = delete;
        Default ( Default && ) noexcept = delete;

        auto toString () const noexcept -> String override {
            return "Default";
        }
    };

    class None : public cds :: Object {
    public:
        None () noexcept = delete;
        None ( None const & ) noexcept = delete;
        None ( None && ) noexcept = delete;

        auto toString () const noexcept -> String override {
            return "None";
        }
    };

    CollectionType < DefaultCopyMove > a;
    CollectionType < DefaultCopy > b;
    CollectionType < DefaultMove > c;
    CollectionType < CopyMove > d;
    CollectionType < Move > e;
    CollectionType < Copy > f;
    CollectionType < Default > g;
    CollectionType < None > h;

    CollectionType < DefaultCopyMove > const ac;
    CollectionType < DefaultCopy > const bc;
    CollectionType < DefaultMove > const cc;
    CollectionType < CopyMove > const dc;
    CollectionType < Move > const ec;
    CollectionType < Copy > const fc;
    CollectionType < Default > const gc;
    CollectionType < None > const hc;

    return true;
}

auto CollectionTest :: execute() noexcept -> bool {
    bool allOk = true;

    experimental :: Array < int > emptyArrayTestObject;
    experimental :: Array < int > arrayTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    experimental :: Array < String > arrayTestObjectStr = { "Ana", "are", "mere" };
    experimental :: Array < String > emptyArrayTestObjectStr;

//    experimental :: LinkedList < int > listTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    experimental :: LinkedList < String > listTestObjectStr = { "Ana", "are", "mere" };

    auto primitiveTest = [this, & allOk]( experimental :: Collection < int > & collection, experimental :: Collection < int > & emptyCollection ) {

        this->log ( "Object in test : %s", collection.toString().cStr() );
        this->log ( "Empty object in test : %s", emptyCollection.toString().cStr() );

        this->executeSubtest ("cds :: Object functions", [&]{

            std :: stringstream out1, out2;
            out1 << collection;
            this->log ( "operator << : %s", out1.str().c_str() );

            out2 << emptyCollection;
            this->log ( "operator on empty << : %s", out2.str().c_str() );

            int expectedHash = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9;
            if ( expectedHash != collection.hash() ) {
                this->logError ( "hash() error. Expected : %d, got : %d", expectedHash, (int)collection.hash() );
                allOk = false;
            }

            if ( 0 != emptyCollection.hash() ) {
                this->logError ( "hash() error. Expected : %d, got : %d", expectedHash, (int)emptyCollection.hash() );
                allOk = false;
            }

            if ( ! collection.equals(collection) ) {
                this->logError ( "equals() error." );
                allOk = false;
            }

            if ( ! emptyCollection.equals(emptyCollection) ) {
                this->logError ( "equals() error." );
                allOk = false;
            }

            if ( emptyCollection.equals(collection) ) {
                this->logError ( "equals() error." );
                allOk = false;
            }

            if ( collection.equals(emptyCollection) ) {
                this->logError ( "equals() error." );
                allOk = false;
            }

            this->log("Testing iterators");

            int expectedElementCount = 9;
            int expectedElementSum = expectedHash;

            int elementCount = 0;
            int elementSum = 0;
            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {

                if ( elementSum == 0 && * it != 1 ) {
                    this->logError ( "ConstIterator error. Expected value : %d. Value : %d", 1, * it );
                    allOk = false;
                }

                elementSum += * it;
                elementCount ++;
            }

            if ( elementCount != expectedElementCount ) {
                this->logError ( "ConstIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
                allOk = false;
            }

            if ( elementSum != expectedElementSum ) {
                this->logError ( "ConstIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
                allOk = false;
            }

            elementCount = 0;
            elementSum = 0;
            for ( auto it = collection.cbegin(); it != collection.cend(); ++ it ) {

                if ( elementSum == 0 && * it != 1 ) {
                    this->logError ( "ConstIterator error. Expected value : %d. Value : %d", 1, * it );
                    allOk = false;
                }

                elementSum += * it;
                elementCount ++;
            }

            if ( elementCount != expectedElementCount ) {
                this->logError ( "ConstIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
                allOk = false;
            }

            if ( elementSum != expectedElementSum ) {
                this->logError ( "ConstIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
                allOk = false;
            }

            elementCount = 0;
            elementSum = 0;
            for ( auto it = collection.rbegin(); it != collection.rend(); ++ it ) {

                if ( elementSum == 0 && * it != 9 ) {
                    this->logError ( "ConstReverseIterator error. Expected value : %d. Value : %d", 9, * it );
                    allOk = false;
                }

                elementSum += * it;
                elementCount ++;
            }

            if ( elementCount != expectedElementCount ) {
                this->logError ( "ConstReverseIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
                allOk = false;
            }

            if ( elementSum != expectedElementSum ) {
                this->logError ( "ConstReverseIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
                allOk = false;
            }

            elementCount = 0;
            elementSum = 0;
            for ( auto it = collection.crbegin(); it != collection.crend(); ++ it ) {

                if ( elementSum == 0 && * it != 9 ) {
                    this->logError ( "ConstReverseIterator error. Expected value : %d. Value : %d", 9, * it );
                    allOk = false;
                }

                elementSum += * it;
                elementCount ++;
            }

            if ( elementCount != expectedElementCount ) {
                this->logError ( "ConstReverseIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
                allOk = false;
            }

            if ( elementSum != expectedElementSum ) {
                this->logError ( "ConstReverseIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
                allOk = false;
            }

            for ( auto it = emptyCollection.begin(); it != emptyCollection.end(); ++ it ) {
                this->logError ( "ConstIterator Error. Empty collection should not be iterable" );
                allOk = false;
            }

            for ( auto it = emptyCollection.cbegin(); it != emptyCollection.cend(); ++ it ) {
                this->logError ( "ConstIterator Error. Empty collection should not be iterable" );
                allOk = false;
            }

            for ( auto it = emptyCollection.rbegin(); it != emptyCollection.rend(); ++ it ) {
                this->logError ( "ConstReverseIterator Error. Empty collection should not be iterable" );
                allOk = false;
            }

            for ( auto it = emptyCollection.crbegin(); it != emptyCollection.crend(); ++ it ) {
                this->logError ( "ConstReverseIterator Error. Empty collection should not be iterable" );
                allOk = false;
            }

            int removeAt = 3;
            int valueExpectedAt = 4;
            int at = 0;

            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
                if ( at != removeAt ) {
                    ++ at;
                    continue;
                }

                if ( ! collection.remove ( it ) ) {
                    this->logError ( "remove (ConstIterator) error Failed to remove valid iterator" );
                    allOk = false;
                }

                break;
            }

            if ( collection.contains (valueExpectedAt) ) {
                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
                allOk = false;
            }

            Array < int > expectedRemaining = { 1, 2, 3, 5, 6, 7, 8, 9 };
            for ( auto e : expectedRemaining ) {
                if ( ! collection.contains(e) ) {
                    this->logError ( "remove error, removed more than expected" );
                    allOk = false;
                }
            }

            if ( collection.remove ( collection.end() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 1 ) {
                this->logError ( "Removal changed the size when it should not have had" );
                allOk = false;
            }

            if ( ! collection.remove ( collection.begin() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 2 ) {
                this->logError ( "Removal did not change the size" );
                allOk = false;
            }

            if ( collection.contains(1) ) {
                this->logError ( "Removal did not work" );
                allOk = false;
            }

            removeAt = 3;
            valueExpectedAt = 6;
            at = 0;
            experimental :: meta :: RemoveReference < decltype (collection) > :: ConstIterator iter;

            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
                if ( at != removeAt ) {
                    ++ at;
                    continue;
                }

                iter = it;

                break;
            }

            if ( ! collection.remove (iter) ) {
                this->logError ( "remove did not work" );
                allOk = false;
            }

            if ( collection.contains (valueExpectedAt) ) {
                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
                allOk = false;
            }

            expectedRemaining = { 2, 3, 5, 7, 8, 9 };
            for ( auto e : expectedRemaining ) {
                if ( ! collection.contains(e) ) {
                    this->logError ( "remove error, removed more than expected" );
                    allOk = false;
                }
            }

            if ( collection.remove ( collection.end() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 3 ) {
                this->logError ( "Removal changed the size when it should not have had" );
                allOk = false;
            }

            if ( ! collection.remove ( collection.begin() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 4 ) {
                this->logError ( "Removal did not change the size" );
                allOk = false;
            }

            if ( collection.contains(2) ) {
                this->logError ( "Removal did not work" );
                allOk = false;
            }

            removeAt = 3;
            valueExpectedAt = 5;
            at = 0;

            for ( auto it = collection.rbegin(); it != collection.rend(); ++ it ) {
                if ( at != removeAt ) {
                    ++ at;
                    continue;
                }

                if ( ! collection.remove ( it ) ) {
                    this->logError ( "remove (ConstIterator) error Failed to remove valid iterator" );
                    allOk = false;
                }

                break;
            }

            if ( collection.contains (valueExpectedAt) ) {
                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
                allOk = false;
            }

            expectedRemaining = { 3, 7, 8, 9 };
            for ( auto e : expectedRemaining ) {
                if ( ! collection.contains(e) ) {
                    this->logError ( "remove error, removed more than expected" );
                    allOk = false;
                }
            }

            if ( collection.remove ( collection.end() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 5 ) {
                this->logError ( "Removal changed the size when it should not have had" );
                allOk = false;
            }

            if ( ! collection.remove ( collection.begin() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 6 ) {
                this->logError ( "Removal did not change the size" );
                allOk = false;
            }

            if ( collection.contains(3) ) {
                this->logError ( "Removal did not work" );
                allOk = false;
            }

            removeAt = 1;
            valueExpectedAt = 8;
            at = 0;
            experimental :: meta :: RemoveReference < decltype (collection) > :: ConstReverseIterator iter2;

            for ( auto it = collection.rbegin(); it != collection.rend(); ++ it ) {
                if ( at != removeAt ) {
                    ++ at;
                    continue;
                }

                iter2 = it;

                break;
            }

            if ( ! collection.remove (iter2) ) {
                this->logError ( "remove did not work" );
                allOk = false;
            }

            if ( collection.contains (valueExpectedAt) ) {
                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
                allOk = false;
            }

            expectedRemaining = { 7, 9 };
            for ( auto e : expectedRemaining ) {
                if ( ! collection.contains(e) ) {
                    this->logError ( "remove error, removed more than expected" );
                    allOk = false;
                }
            }

            if ( collection.remove ( collection.end() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 7 ) {
                this->logError ( "Removal changed the size when it should not have had" );
                allOk = false;
            }

            if ( ! collection.remove ( collection.begin() ) ) {
                this->logError ( "Removal should not have happened" );
                allOk = false;
            }

            if ( collection.size() != expectedElementCount - 8 ) {
                this->logError ( "Removal did not change the size" );
                allOk = false;
            }

            if ( collection.contains(7) ) {
                this->logError ( "Removal did not work" );
                allOk = false;
            }

            if ( collection.empty() ) {
                this->logError ( "Empty error" );
                allOk = false;
            }

            collection.clear();

            if ( ! collection.empty() ) {
                this->logError ( "Clear/Empty error" );
                allOk = false;
            }

            if ( collection.remove ( collection.begin() ) ) {
                this->logError ( "Remove error" );
                allOk = false;
            }

            if ( collection.remove ( collection.end() ) ) {
                this->logError ( "Remove error" );
                allOk = false;
            }

            if ( ! emptyCollection.empty() ) {
                this->logError ( "Clear/Empty error" );
                allOk = false;
            }

            if ( emptyCollection.remove ( emptyCollection.begin() ) ) {
                this->logError ( "Remove error" );
                allOk = false;
            }

            if ( emptyCollection.remove ( emptyCollection.end() ) ) {
                this->logError ( "Remove error" );
                allOk = false;
            }

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );
            collection.add ( 7 );
            collection.add ( 8 );
            collection.add ( 9 );

            collection.remove ( 9, [](int v){ return v >= 6; } );
            if ( collection.any ( [](int v){ return v >= 6; } ) ) {
                this->logError("remove Predicate error");
                allOk = false;
            }

            collection.removeFirst ( []( int v ) { return v == 3; } );
            if ( collection.contains (3) ) {
                this->logError ("removeFirst Predicate error");
                allOk = false;
            }

            collection.add ( 3 );
            collection.add ( 3 );

            collection.removeFirst ( []( int v ) { return v == 3; } );
            if ( ! collection.contains (3) ) {
                this->logError ("removeFirst Predicate error");
                allOk = false;
            }

            collection.removeLast ( []( int v ) { return v == 3; } );
            if ( collection.contains (3) ) {
                this->logError ("removeLast Predicate error");
                allOk = false;
            }

            collection.add ( 3 );
            collection.add ( 3 );

            collection.removeLast ( []( int v ) { return v == 3; } );
            if ( ! collection.contains (3) ) {
                this->logError ("removeLast Predicate error");
                allOk = false;
            }

            collection.add ( 3 );
            collection.add ( 3 );
            collection.add ( 3 );
            collection.add ( 3 );

            collection.removeAll ( []( int v ) { return v == 3; } );
            if ( collection.contains (3) ) {
                this->logError ("removeAll Predicate error");
                allOk = false;
            }

            collection.add ( 3 );
            collection.add ( 3 );
            collection.add ( 3 );

            collection.remove ( 2, 3 );
            if ( ! collection.contains ( 3 ) ) {
                this->logError ( "remove ElementType, Size error" );
                allOk = false;
            }

            collection.remove ( 2, 3 );
            if ( collection.contains ( 3 ) ) {
                this->logError ( "remove ElementType, Size error" );
                allOk = false;
            }

            collection.add (3);
            collection.add (3);

            collection.removeFirst ( 3 );
            if ( ! collection.contains ( 3 ) ) {
                this->logError ( "removeFirst ElementType error" );
                allOk = false;
            }

            collection.removeFirst ( 3 );
            if ( collection.contains ( 3 ) ) {
                this->logError ( "removeFirst ElementType error" );
                allOk = false;
            }

            collection.add (3);
            collection.add (3);

            collection.removeLast ( 3 );
            if ( ! collection.contains ( 3 ) ) {
                this->logError ( "removeFirst ElementType error" );
                allOk = false;
            }

            collection.removeLast ( 3 );
            if ( collection.contains ( 3 ) ) {
                this->logError ( "removeFirst ElementType error" );
                allOk = false;
            }

            collection.add (3);
            collection.add (3);

            collection.removeAll ( 3 );
            if ( collection.contains ( 3 ) ) {
                this->logError ( "removeAll ElementType error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeOf ( 2, experimental :: Array < int > { 2, 3, 4 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || ! collection.contains (4) ) {
                this->logError ( "removeOf Collection cref, Size error" );
                allOk = false;
            }

            collection.removeOf ( 2, experimental :: Array < int > { 2, 3, 4 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || collection.contains (4) ) {
                this->logError ( "removeOf Collection cref, Size error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeFirstOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.contains ( 2 ) || ! collection.contains ( 3 ) ) {
                this->logError ( "removeFirstOf Collection cref error" );
                allOk = false;
            }

            collection.removeFirstOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeFirstOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeLastOf ( experimental :: Array < int > { 3, 2 } );

            if ( ! collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeLastOf Collection cref error" );
                allOk = false;
            }

            collection.removeLastOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeLastOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeAllOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeAllOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeNotOf ( 2, experimental :: Array < int > { 2, 3, 4 } );

            if ( collection.containsAnyOf ( { 1, 5 } ) || ! collection.containsAllOf ( { 2, 3, 4, 6 } ) ) {
                this->logError ( "removeNotOf Collection cref, Size error" );
                allOk = false;
            }

            collection.removeNotOf ( 2, experimental :: Array < int > { 2, 3, 4 } );

            if ( collection.containsAnyOf ( { 1, 5, 6 } ) || ! collection.containsAllOf ( { 2, 3, 4 } ) ) {
                this->logError ( "removeNotOf Collection cref, Size error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeFirstNotOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3, 4, 5, 6 } ) ) {
                this->logError ( "removeFirstNotOf Collection cref error" );
                allOk = false;
            }

            collection.removeFirstNotOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3, 5, 6 } ) ) {
                this->logError ( "removeFirstNotOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeLastNotOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 1, 2, 3, 4, 5 } ) ) {
                this->logError ( "removeLastNotOf Collection cref error" );
                allOk = false;
            }

            collection.removeLastNotOf ( experimental :: Array < int > { 4, 5 } );

            if ( collection.containsAnyNotOf ( { 1, 2, 4, 5 } ) ) {
                this->logError ( "removeLastNotOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeAllNotOf ( experimental :: Array < int > { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3 } ) ) {
                this->logError ( "removeAllOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeOf ( 2, { 2, 3, 4 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || ! collection.contains (4) ) {
                this->logError ( "removeOf Collection cref, Size error" );
                allOk = false;
            }

            collection.removeOf ( 2, { 2, 3, 4 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || collection.contains (4) ) {
                this->logError ( "removeOf Collection cref, Size error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeFirstOf ( { 3, 2 } );

            if ( collection.contains ( 2 ) || ! collection.contains ( 3 ) ) {
                this->logError ( "removeFirstOf Collection cref error" );
                allOk = false;
            }

            collection.removeFirstOf ( { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeFirstOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeLastOf ( { 3, 2 } );

            if ( ! collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeLastOf Collection cref error" );
                allOk = false;
            }

            collection.removeLastOf ( { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeLastOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeAllOf ( { 3, 2 } );

            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
                this->logError ( "removeAllOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeNotOf ( 2, { 2, 3, 4 } );

            if ( collection.containsAnyOf ( { 1, 5 } ) || ! collection.containsAllOf ( { 2, 3, 4, 6 } ) ) {
                this->logError ( "removeNotOf Collection cref, Size error" );
                allOk = false;
            }

            collection.removeNotOf ( 2, { 2, 3, 4 } );

            if ( collection.containsAnyOf ( { 1, 5, 6 } ) || ! collection.containsAllOf ( { 2, 3, 4 } ) ) {
                this->logError ( "removeNotOf Collection cref, Size error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeFirstNotOf ( { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3, 4, 5, 6 } ) ) {
                this->logError ( "removeFirstNotOf Collection cref error" );
                allOk = false;
            }

            collection.removeFirstNotOf ( { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3, 5, 6 } ) ) {
                this->logError ( "removeFirstNotOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeLastNotOf ( { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 1, 2, 3, 4, 5 } ) ) {
                this->logError ( "removeLastNotOf Collection cref error" );
                allOk = false;
            }

            collection.removeLastNotOf ( { 4, 5 } );

            if ( collection.containsAnyNotOf ( { 1, 2, 4, 5 } ) ) {
                this->logError ( "removeLastNotOf Collection cref error" );
                allOk = false;
            }

            collection.clear ();

            collection.add ( 1 );
            collection.add ( 2 );
            collection.add ( 3 );
            collection.add ( 4 );
            collection.add ( 5 );
            collection.add ( 6 );

            collection.removeAllNotOf ( { 3, 2 } );

            if ( collection.containsAnyNotOf ( { 2, 3 } ) ) {
                this->logError ( "removeAllOf Collection cref error" );
                allOk = false;
            }

            collection.clear();

            collection.addAll ( 3, 4, 5 );

            this->log("Add all : %s", collection.toString().cStr());
            if ( collection.size() != 3 ) {
                this->logError ( "add all error" );
                allOk = false;
            }

            int expectedSum = 3 + 4 + 5;
            int actualSum = 0;

            collection.forEach ( [& actualSum] ( int v ) { actualSum += v; } );

            if ( actualSum != expectedSum ) {
                this->logError ( "forEach error" );
                allOk = false;
            }

            if ( ! collection.some ( 1, [](int v){ return v == 3; } ) ) {
                this->logError ( "some error" );
                allOk = false;
            }

            if ( ! collection.atLeast ( 2, [](int v){ return v > 3; } ) ) {
                this->logError ( "atLeast error" );
                allOk = false;
            }

            if ( ! collection.atMost ( 2, [](int v){ return v < 5; } ) ) {
                this->logError ( "atMost error" );
                allOk = false;
            }

            if ( ! collection.moreThan ( 1, [](int v){ return v > 3; } ) ) {
                this->logError ( "moreThan error" );
                allOk = false;
            }

            if ( collection.moreThan ( 2, [](int v){ return v > 3; } ) ) {
                this->logError ( "moreThan error" );
                allOk = false;
            }

            if ( ! collection.lessThan ( 3, [](int v){ return v < 5; } ) ) {
                this->logError ( "lessThan error" );
                allOk = false;
            }

            if ( collection.lessThan ( 2, [](int v){ return v < 5; } ) ) {
                this->logError ( "lessThan error" );
                allOk = false;
            }

            if ( collection.count () != 3 ) {
                this->logError ( "count error" );
                allOk = false;
            }

            if ( collection.count ( [](int v) { return v >= 3 && v <= 4; } ) != 2 ) {
                this->logError ( "count error" );
                allOk = false;
            }

            if ( collection.any ( [](int v) { return v > 5; } ) ) {
                this->logError ( "any error" );
                allOk = false;
            }

            if ( ! collection.any ( [](int v) { return v < 4; } ) ) {
                this->logError ( "any error" );
                allOk = false;
            }

            if ( ! collection.all ( [](int v) { return v >= 3 && v <= 5; } ) ) {
                this->logError ( "all error" );
                allOk = false;
            }

            if ( collection.all ( [](int v) { return v > 4; } ) ) {
                this->logError ( "all error" );
                allOk = false;
            }

            try {
                collection.any ( [](int v) { throw NullPointerException(); return false; } );
                this->logError ( "Exception not triggered, error" );
                allOk = false;
            } catch ( Exception const & ) {
                this->log("Exception caught ok from functional request");
            }

            collection.clear ();

            collection.addAll ( 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 );

            Array < experimental :: meta :: RemoveReference < decltype ( collection ) > :: ConstIterator > iterators;
            collection.find ( 2, 5, iterators );

            if ( iterators.size () != 2 ) {
                this->logError ( "wrong element count found" );
                allOk = false;
            }

            if ( * iterators[0] != 5 || * iterators[1] != 5 ) {
                this->logError ( "Iterators not ok from value pov" );
                allOk = false;
            }

            if ( * ( ++ iterators[0] ) != 6 || * ( ++ iterators[1] ) != 4 ) {
                this->logError ( "Iterators not positioned in correct places" );
                allOk = false;
            }

            auto iteratorsReturned = collection.find < Array > ( 2, 5 );

            if ( iteratorsReturned.size () != 2 ) {
                this->logError ( "wrong element count found" );
                allOk = false;
            }

            if ( * iteratorsReturned[0] != 5 || * iteratorsReturned[1] != 5 ) {
                this->logError ( "Iterators not ok from value pov" );
                allOk = false;
            }

            if ( * ( ++ iteratorsReturned[0] ) != 6 || * ( ++ iteratorsReturned[1] ) != 4 ) {
                this->logError ( "Iterators not positioned in correct places" );
                allOk = false;
            }

            iter = collection.findFirst ( 5 );

//            if ( * iter != 5 ) {
//                this->logError()
//            }
        });
    };

    auto objectTest = [this, & allOk]( experimental :: Collection < String > & collection, experimental :: Collection < String > & emptyCollection ) {

        this->log ( "Object in test : %s", collection.toString().cStr() );
        this->log ( "Empty object in test : %s", emptyCollection.toString().cStr() );

        this->executeSubtest ("cds :: Object functions", [&]{

            std :: stringstream out1, out2;
            out1 << collection;
            this->log ( "operator << : %s", out1.str().c_str() );

            out2 << emptyCollection;
            this->log ( "operator on empty << : %s", out2.str().c_str() );
        });
    };

    constructionTest < experimental :: Array > ();
    constructionTest < experimental :: LinkedList > ();

    this->executeSubtest ( "Array Primitive Test", [&]{ primitiveTest ( arrayTestObject, emptyArrayTestObject ); } );
    this->executeSubtest ( "Array Object Test", [&]{ objectTest ( arrayTestObjectStr, emptyArrayTestObjectStr ); } );

//    this->executeSubtest ( "LinkedList Primitive Test", [&]{ primitiveTest ( listTestObject ); } );
//    this->executeSubtest ( "LinkedList Object Test", [&]{ objectTest ( listTestObjectStr ); } );

    return allOk;
}

#endif