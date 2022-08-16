//
// Created by loghin on 30.11.2021.
//

#include "CollectionTest.h"

//#if !defined(CDS_TEST_EXPERIMENTAL)
//#include <CDS/Array>
//
//using namespace cds;
//
//auto CollectionTest :: execute() noexcept -> bool {
//    bool allOk = true;
//
//    Array < int > arrayTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//
//    this->executeSubtest( "Contains/Additions", [&]{
//
//        auto arrayIntContains = []( Collection < int > & array, int value ) {
//            return array.contains( value );
//        };
//        auto constArrayIntContains = []( Collection < int > const & array, int value ) {
//            return array.contains( value );
//        };
//
//        if (
//                ! arrayIntContains ( arrayTestObject, 3 ) ||
//                ! constArrayIntContains ( arrayTestObject, 3 )
//        ) {
//            this->logWarning("Array Contains Error");
//            allOk = false;
//        }
//
//        if (
//                arrayIntContains ( arrayTestObject, 200 ) ||
//                constArrayIntContains ( arrayTestObject, 200 )
//        ) {
//            this->logWarning("Array Contains Error");
//            allOk = false;
//        }
//
//    });
//
//    this->executeSubtest( "Iterative Functionals", [&]{
//
//        auto arrayIntSum = []( cds :: Collection < int > const & array ) -> int {
//            int sum = 0;
//            for ( auto const & v : array )
//                sum += v;
//            return sum;
//        };
//
//        auto arrayIntSumForEach_paramCopy = [] ( cds :: Collection < int > & array ) -> int {
//            int sum = 0;
//            array.forEach([&sum](auto v){sum += v;});
//            return sum;
//        };
//
//        auto arrayIntSumForEach_paramRef = [] ( cds :: Collection < int > & array ) -> int {
//            int sum = 0;
//            array.forEach([&sum](auto & v){sum += v;});
//            return sum;
//        };
//
//        auto arrayIntSumForEach_paramCRef = [] ( cds :: Collection < int > & array ) -> int {
//            int sum = 0;
//            array.forEach([&sum](auto const & v){sum += v;});
//            return sum;
//        };
//
//        auto compareResults = [&]{
//
//            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCopy (arrayTestObject)) {
//                this->logWarning("Array forEach error");
//                allOk = false;
//            }
//
//            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramRef (arrayTestObject)) {
//                this->logWarning("Array forEach error");
//                allOk = false;
//            }
//
//            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCRef (arrayTestObject)) {
//                this->logWarning("Array forEach error");
//                allOk = false;
//            }
//
//        };
//
//        compareResults();
//
//        auto intArrayModify = [] ( Collection < int > & collection ) {
//            collection.forEach([](auto & e){e = e * 2;});
//        };
//
//        intArrayModify ( arrayTestObject );
//
//        compareResults();
//
//    });
//
//    return allOk;
//}
//
//#endif
//
//#if defined(CDS_TEST_EXPERIMENTAL)
//#include <CDS/smartPointers/UniquePointer>
//#include <CDS/experimental/Array>
////#include <CDS/experimental/LinkedList>
//
//using namespace cds;
//
//template < template < typename ... > typename CollectionType >
//auto constructionTest () noexcept -> bool {
//    class DefaultCopyMove : public cds :: Object {
//    public:
//        DefaultCopyMove () noexcept = default;
//        DefaultCopyMove ( DefaultCopyMove const & ) noexcept = default;
//        DefaultCopyMove ( DefaultCopyMove && ) noexcept = default;
//
//        auto toString () const noexcept -> String override {
//            return "Default, Copy, Move";
//        }
//    };
//
//    class DefaultCopy : public cds :: Object {
//    public:
//        DefaultCopy () noexcept = default;
//        DefaultCopy ( DefaultCopy const & ) noexcept = default;
//        DefaultCopy ( DefaultCopy && ) noexcept = delete;
//
//        auto toString () const noexcept -> String override {
//            return "DefaultCopy";
//        }
//    };
//
//    class DefaultMove : public cds :: Object {
//    public:
//        DefaultMove () noexcept = default;
//        DefaultMove ( DefaultMove const & ) noexcept = delete;
//        DefaultMove ( DefaultMove && ) noexcept = default;
//
//        auto toString () const noexcept -> String override {
//            return "DefaultMove";
//        }
//    };
//
//    class CopyMove : public cds :: Object {
//    public:
//        CopyMove () noexcept = delete;
//        CopyMove ( CopyMove const & ) noexcept = default;
//        CopyMove ( CopyMove && ) noexcept = default;
//
//        auto toString () const noexcept -> String override {
//            return "CopyMove";
//        }
//    };
//
//    class Move : public cds :: Object {
//    public:
//        Move () noexcept = delete;
//        Move ( Move const & ) noexcept = delete;
//        Move ( Move && ) noexcept = default;
//
//        auto toString () const noexcept -> String override {
//            return "Move";
//        }
//    };
//
//    class Copy : public cds :: Object {
//    public:
//        Copy () noexcept = delete;
//        Copy ( Copy const & ) noexcept = default;
//        Copy ( Copy && ) noexcept = delete;
//
//        auto toString () const noexcept -> String override {
//            return "Copy";
//        }
//    };
//
//    class Default : public cds :: Object {
//    public:
//        Default () noexcept = default;
//        Default ( Default const & ) noexcept = delete;
//        Default ( Default && ) noexcept = delete;
//
//        auto toString () const noexcept -> String override {
//            return "Default";
//        }
//    };
//
//    class None : public cds :: Object {
//    public:
//        None () noexcept = delete;
//        None ( None const & ) noexcept = delete;
//        None ( None && ) noexcept = delete;
//
//        auto toString () const noexcept -> String override {
//            return "None";
//        }
//    };
//
//    CollectionType < DefaultCopyMove > a;
//    CollectionType < DefaultCopy > b;
//    CollectionType < DefaultMove > c;
//    CollectionType < CopyMove > d;
//    CollectionType < Move > e;
//    CollectionType < Copy > f;
//    CollectionType < Default > g;
//    CollectionType < None > h;
//
//    CollectionType < DefaultCopyMove > const ac;
//    CollectionType < DefaultCopy > const bc;
//    CollectionType < DefaultMove > const cc;
//    CollectionType < CopyMove > const dc;
//    CollectionType < Move > const ec;
//    CollectionType < Copy > const fc;
//    CollectionType < Default > const gc;
//    CollectionType < None > const hc;
//
//    return true;
//}
//
//using namespace cds :: experimental;
//
//auto CollectionTest :: execute() noexcept -> bool {
//    bool allOk = true;
//
//    experimental :: Array < int > emptyArrayTestObject;
//    experimental :: Array < int > arrayTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    experimental :: Array < String > arrayTestObjectStr = { "Ana", "are", "mere" };
//    experimental :: Array < String > emptyArrayTestObjectStr;
//
////    experimental :: LinkedList < int > listTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};
////    experimental :: LinkedList < String > listTestObjectStr = { "Ana", "are", "mere" };
//
//    auto primitiveTest = [this, & allOk]( experimental :: Collection < int > & collection, experimental :: Collection < int > & emptyCollection ) {
//
//        this->log ( "Object in test : %s", collection.toString().cStr() );
//        this->log ( "Empty object in test : %s", emptyCollection.toString().cStr() );
//
//        this->executeSubtest ("cds :: Object functions", [&]{
//
//            std :: stringstream out1, out2;
//            out1 << collection;
//            this->log ( "operator << : %s", out1.str().c_str() );
//
//            out2 << emptyCollection;
//            this->log ( "operator on empty << : %s", out2.str().c_str() );
//
//            int expectedHash = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9;
//            if ( expectedHash != collection.hash() ) {
//                this->logError ( "hash() error. Expected : %d, got : %d", expectedHash, (int)collection.hash() );
//                allOk = false;
//            }
//
//            if ( 0 != emptyCollection.hash() ) {
//                this->logError ( "hash() error. Expected : %d, got : %d", expectedHash, (int)emptyCollection.hash() );
//                allOk = false;
//            }
//
//            if ( ! collection.equals(collection) ) {
//                this->logError ( "equals() error." );
//                allOk = false;
//            }
//
//            if ( ! emptyCollection.equals(emptyCollection) ) {
//                this->logError ( "equals() error." );
//                allOk = false;
//            }
//
//            if ( emptyCollection.equals(collection) ) {
//                this->logError ( "equals() error." );
//                allOk = false;
//            }
//
//            if ( collection.equals(emptyCollection) ) {
//                this->logError ( "equals() error." );
//                allOk = false;
//            }
//
//            this->log("Testing iterators");
//
//            int expectedElementCount = 9;
//            int expectedElementSum = expectedHash;
//
//            int elementCount = 0;
//            int elementSum = 0;
//            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//
//                if ( elementSum == 0 && * it != 1 ) {
//                    this->logError ( "ConstIterator error. Expected value : %d. Value : %d", 1, * it );
//                    allOk = false;
//                }
//
//                elementSum += * it;
//                elementCount ++;
//            }
//
//            if ( elementCount != expectedElementCount ) {
//                this->logError ( "ConstIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
//                allOk = false;
//            }
//
//            if ( elementSum != expectedElementSum ) {
//                this->logError ( "ConstIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
//                allOk = false;
//            }
//
//            elementCount = 0;
//            elementSum = 0;
//            for ( auto it = collection.cbegin(); it != collection.cend(); ++ it ) {
//
//                if ( elementSum == 0 && * it != 1 ) {
//                    this->logError ( "ConstIterator error. Expected value : %d. Value : %d", 1, * it );
//                    allOk = false;
//                }
//
//                elementSum += * it;
//                elementCount ++;
//            }
//
//            if ( elementCount != expectedElementCount ) {
//                this->logError ( "ConstIterator iteration count different than expected. expected %d, occurred %d", expectedElementCount, elementCount );
//                allOk = false;
//            }
//
//            if ( elementSum != expectedElementSum ) {
//                this->logError ( "ConstIterator yielded elements different than expected. expected sum %d, occurred sum %d", expectedElementSum, elementSum );
//                allOk = false;
//            }
//
//            for ( auto it = emptyCollection.begin(); it != emptyCollection.end(); ++ it ) {
//                this->logError ( "ConstIterator Error. Empty collection should not be iterable" );
//                allOk = false;
//            }
//
//            for ( auto it = emptyCollection.cbegin(); it != emptyCollection.cend(); ++ it ) {
//                this->logError ( "ConstIterator Error. Empty collection should not be iterable" );
//                allOk = false;
//            }
//
//            int removeAt = 3;
//            int valueExpectedAt = 4;
//            int at = 0;
//
//            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//                if ( at != removeAt ) {
//                    ++ at;
//                    continue;
//                }
//
//                if ( ! collection.remove ( it ) ) {
//                    this->logError ( "remove (ConstIterator) error Failed to remove valid iterator" );
//                    allOk = false;
//                }
//
//                break;
//            }
//
//            if ( collection.contains (valueExpectedAt) ) {
//                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
//                allOk = false;
//            }
//
//            Array < int > expectedRemaining = { 1, 2, 3, 5, 6, 7, 8, 9 };
//            for ( auto e : expectedRemaining ) {
//                if ( ! collection.contains(e) ) {
//                    this->logError ( "remove error, removed more than expected" );
//                    allOk = false;
//                }
//            }
//
//            if ( collection.remove ( collection.end() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 1 ) {
//                this->logError ( "Removal changed the size when it should not have had" );
//                allOk = false;
//            }
//
//            if ( ! collection.remove ( collection.begin() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 2 ) {
//                this->logError ( "Removal did not change the size" );
//                allOk = false;
//            }
//
//            if ( collection.contains(1) ) {
//                this->logError ( "Removal did not work" );
//                allOk = false;
//            }
//
//            removeAt = 3;
//            valueExpectedAt = 6;
//            at = 0;
//            cds :: meta :: RemoveReference < decltype (collection) > :: ConstIterator iter;
//
//            for ( auto it = collection.begin(); it != collection.end(); ++ it ) {
//                if ( at != removeAt ) {
//                    ++ at;
//                    continue;
//                }
//
//                iter = it;
//
//                break;
//            }
//
//            if ( ! collection.remove (iter) ) {
//                this->logError ( "remove did not work" );
//                allOk = false;
//            }
//
//            if ( collection.contains (valueExpectedAt) ) {
//                this->logError ( "remove not working as expected. did not remove. Collection : %s", collection.toString().cStr() );
//                allOk = false;
//            }
//
//            expectedRemaining = { 2, 3, 5, 7, 8, 9 };
//            for ( auto e : expectedRemaining ) {
//                if ( ! collection.contains(e) ) {
//                    this->logError ( "remove error, removed more than expected" );
//                    allOk = false;
//                }
//            }
//
//            if ( collection.remove ( collection.end() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 3 ) {
//                this->logError ( "Removal changed the size when it should not have had" );
//                allOk = false;
//            }
//
//            if ( ! collection.remove ( collection.begin() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 4 ) {
//                this->logError ( "Removal did not change the size" );
//                allOk = false;
//            }
//
//            if ( collection.contains(2) ) {
//                this->logError ( "Removal did not work" );
//                allOk = false;
//            }
//
//            removeAt = 3;
//            valueExpectedAt = 5;
//            at = 0;
//
//            expectedRemaining = { 3, 7, 8, 9 };
//            for ( auto e : expectedRemaining ) {
//                if ( ! collection.contains(e) ) {
//                    this->logError ( "remove error, removed more than expected" );
//                    allOk = false;
//                }
//            }
//
//            if ( collection.remove ( collection.end() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 5 ) {
//                this->logError ( "Removal changed the size when it should not have had" );
//                allOk = false;
//            }
//
//            if ( ! collection.remove ( collection.begin() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 6 ) {
//                this->logError ( "Removal did not change the size" );
//                allOk = false;
//            }
//
//            if ( collection.contains(3) ) {
//                this->logError ( "Removal did not work" );
//                allOk = false;
//            }
//
//            if ( collection.remove ( collection.end() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 7 ) {
//                this->logError ( "Removal changed the size when it should not have had" );
//                allOk = false;
//            }
//
//            if ( ! collection.remove ( collection.begin() ) ) {
//                this->logError ( "Removal should not have happened" );
//                allOk = false;
//            }
//
//            if ( collection.size() != expectedElementCount - 8 ) {
//                this->logError ( "Removal did not change the size" );
//                allOk = false;
//            }
//
//            if ( collection.contains(7) ) {
//                this->logError ( "Removal did not work" );
//                allOk = false;
//            }
//
//            if ( collection.empty() ) {
//                this->logError ( "Empty error" );
//                allOk = false;
//            }
//
//            collection.clear();
//
//            if ( ! collection.empty() ) {
//                this->logError ( "Clear/Empty error" );
//                allOk = false;
//            }
//
//            if ( collection.remove ( collection.begin() ) ) {
//                this->logError ( "Remove error" );
//                allOk = false;
//            }
//
//            if ( collection.remove ( collection.end() ) ) {
//                this->logError ( "Remove error" );
//                allOk = false;
//            }
//
//            if ( ! emptyCollection.empty() ) {
//                this->logError ( "Clear/Empty error" );
//                allOk = false;
//            }
//
//            if ( emptyCollection.remove ( emptyCollection.begin() ) ) {
//                this->logError ( "Remove error" );
//                allOk = false;
//            }
//
//            if ( emptyCollection.remove ( emptyCollection.end() ) ) {
//                this->logError ( "Remove error" );
//                allOk = false;
//            }
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//            collection.add ( 7 );
//            collection.add ( 8 );
//            collection.add ( 9 );
//
//            collection.removeIf ( 9, [](int v){ return v >= 6; } );
//            if ( collection.any ( [](int v){ return v >= 6; } ) ) {
//                this->logError("remove Predicate error");
//                allOk = false;
//            }
//
//            collection.removeFirstIf ( []( int v ) { return v == 3; } );
//            if ( collection.contains (3) ) {
//                this->logError ("removeFirst Predicate error");
//                allOk = false;
//            }
//
//            collection.add ( 3 );
//            collection.add ( 3 );
//
//            collection.removeFirstIf ( []( int v ) { return v == 3; } );
//            if ( ! collection.contains (3) ) {
//                this->logError ("removeFirst Predicate error");
//                allOk = false;
//            }
//
//            collection.removeLastIf ( []( int v ) { return v == 3; } );
//            if ( collection.contains (3) ) {
//                this->logError ("removeLast Predicate error");
//                allOk = false;
//            }
//
//            collection.add ( 3 );
//            collection.add ( 3 );
//
//            collection.removeLastIf ( []( int v ) { return v == 3; } );
//            if ( ! collection.contains (3) ) {
//                this->logError ("removeLast Predicate error");
//                allOk = false;
//            }
//
//            collection.add ( 3 );
//            collection.add ( 3 );
//            collection.add ( 3 );
//            collection.add ( 3 );
//
//            collection.removeAllIf ( []( int v ) { return v == 3; } );
//            if ( collection.contains (3) ) {
//                this->logError ("removeAll Predicate error");
//                allOk = false;
//            }
//
//            collection.add ( 3 );
//            collection.add ( 3 );
//            collection.add ( 3 );
//
//            collection.remove ( 3 );
//            if ( ! collection.contains ( 3 ) ) {
//                this->logError ( "remove ElementType, Size error" );
//                allOk = false;
//            }
//
//            collection.remove ( 3 );
//            if ( collection.contains ( 3 ) ) {
//                this->logError ( "remove ElementType, Size error" );
//                allOk = false;
//            }
//
//            collection.add (3);
//            collection.add (3);
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeOf ( 2, experimental :: Array < int > { 2, 3, 4 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || ! collection.contains (4) ) {
//                this->logError ( "removeOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.removeOf ( 2, experimental :: Array < int > { 2, 3, 4 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || collection.contains (4) ) {
//                this->logError ( "removeOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeFirstOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || ! collection.contains ( 3 ) ) {
//                this->logError ( "removeFirstOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeFirstOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeFirstOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeLastOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( ! collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeLastOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeLastOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeLastOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeAllOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeAllOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeNotOf ( 2, experimental :: Array < int > { 2, 3, 4 } );
//
//            if ( collection.containsAnyOf ( { 1, 5 } ) || ! collection.containsAllOf ( { 2, 3, 4, 6 } ) ) {
//                this->logError ( "removeNotOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.removeNotOf ( 2, experimental :: Array < int > { 2, 3, 4 } );
//
//            if ( collection.containsAnyOf ( { 1, 5, 6 } ) || ! collection.containsAllOf ( { 2, 3, 4 } ) ) {
//                this->logError ( "removeNotOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeFirstNotOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3, 4, 5, 6 } ) ) {
//                this->logError ( "removeFirstNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeFirstNotOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3, 5, 6 } ) ) {
//                this->logError ( "removeFirstNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeLastNotOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 1, 2, 3, 4, 5 } ) ) {
//                this->logError ( "removeLastNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeLastNotOf ( experimental :: Array < int > { 4, 5 } );
//
//            if ( collection.containsAnyNotOf ( { 1, 2, 4, 5 } ) ) {
//                this->logError ( "removeLastNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeAllNotOf ( experimental :: Array < int > { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3 } ) ) {
//                this->logError ( "removeAllOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeOf ( 2, { 2, 3, 4 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || ! collection.contains (4) ) {
//                this->logError ( "removeOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.removeOf ( 2, { 2, 3, 4 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) || collection.contains (4) ) {
//                this->logError ( "removeOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeFirstOf ( { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || ! collection.contains ( 3 ) ) {
//                this->logError ( "removeFirstOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeFirstOf ( { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeFirstOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeLastOf ( { 3, 2 } );
//
//            if ( ! collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeLastOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeLastOf ( { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeLastOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeAllOf ( { 3, 2 } );
//
//            if ( collection.contains ( 2 ) || collection.contains ( 3 ) ) {
//                this->logError ( "removeAllOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeNotOf ( 2, { 2, 3, 4 } );
//
//            if ( collection.containsAnyOf ( { 1, 5 } ) || ! collection.containsAllOf ( { 2, 3, 4, 6 } ) ) {
//                this->logError ( "removeNotOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.removeNotOf ( 2, { 2, 3, 4 } );
//
//            if ( collection.containsAnyOf ( { 1, 5, 6 } ) || ! collection.containsAllOf ( { 2, 3, 4 } ) ) {
//                this->logError ( "removeNotOf Collection cref, Size error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeFirstNotOf ( { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3, 4, 5, 6 } ) ) {
//                this->logError ( "removeFirstNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeFirstNotOf ( { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3, 5, 6 } ) ) {
//                this->logError ( "removeFirstNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeLastNotOf ( { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 1, 2, 3, 4, 5 } ) ) {
//                this->logError ( "removeLastNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.removeLastNotOf ( { 4, 5 } );
//
//            if ( collection.containsAnyNotOf ( { 1, 2, 4, 5 } ) ) {
//                this->logError ( "removeLastNotOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear ();
//
//            collection.add ( 1 );
//            collection.add ( 2 );
//            collection.add ( 3 );
//            collection.add ( 4 );
//            collection.add ( 5 );
//            collection.add ( 6 );
//
//            collection.removeAllNotOf ( { 3, 2 } );
//
//            if ( collection.containsAnyNotOf ( { 2, 3 } ) ) {
//                this->logError ( "removeAllOf Collection cref error" );
//                allOk = false;
//            }
//
//            collection.clear();
//
//            collection.addAll ( 3, 4, 5 );
//
//            this->log("Add all : %s", collection.toString().cStr());
//            if ( collection.size() != 3 ) {
//                this->logError ( "add all error" );
//                allOk = false;
//            }
//
//            int expectedSum = 3 + 4 + 5;
//            int actualSum = 0;
//
//            collection.forEach ( [& actualSum] ( int v ) { actualSum += v; } );
//
//            if ( actualSum != expectedSum ) {
//                this->logError ( "forEach error" );
//                allOk = false;
//            }
//
//            if ( ! collection.some ( 1, [](int v){ return v == 3; } ) ) {
//                this->logError ( "some error" );
//                allOk = false;
//            }
//
//            if ( ! collection.atLeast ( 2, [](int v){ return v > 3; } ) ) {
//                this->logError ( "atLeast error" );
//                allOk = false;
//            }
//
//            if ( ! collection.atMost ( 2, [](int v){ return v < 5; } ) ) {
//                this->logError ( "atMost error" );
//                allOk = false;
//            }
//
//            if ( ! collection.moreThan ( 1, [](int v){ return v > 3; } ) ) {
//                this->logError ( "moreThan error" );
//                allOk = false;
//            }
//
//            if ( collection.moreThan ( 2, [](int v){ return v > 3; } ) ) {
//                this->logError ( "moreThan error" );
//                allOk = false;
//            }
//
//            if ( ! collection.fewerThan ( 3, [](int v){ return v < 5; } ) ) {
//                this->logError ( "lessThan error" );
//                allOk = false;
//            }
//
//            if ( collection.fewerThan ( 2, [](int v){ return v < 5; } ) ) {
//                this->logError ( "lessThan error" );
//                allOk = false;
//            }
//
//            if ( collection.count () != 3 ) {
//                this->logError ( "count error" );
//                allOk = false;
//            }
//
//            if ( collection.count ( [](int v) { return v >= 3 && v <= 4; } ) != 2 ) {
//                this->logError ( "count error" );
//                allOk = false;
//            }
//
//            if ( collection.any ( [](int v) { return v > 5; } ) ) {
//                this->logError ( "any error" );
//                allOk = false;
//            }
//
//            if ( ! collection.any ( [](int v) { return v < 4; } ) ) {
//                this->logError ( "any error" );
//                allOk = false;
//            }
//
//            if ( ! collection.all ( [](int v) { return v >= 3 && v <= 5; } ) ) {
//                this->logError ( "all error" );
//                allOk = false;
//            }
//
//            if ( collection.all ( [](int v) { return v > 4; } ) ) {
//                this->logError ( "all error" );
//                allOk = false;
//            }
//
//            try {
//                collection.any ( [](int v) { throw NullPointerException(); return false; } );
//                this->logError ( "Exception not triggered, error" );
//                allOk = false;
//            } catch ( Exception const & ) {
//                this->log("Exception caught ok from functional request");
//            }
//
//            collection.clear ();
//
//            collection.addAll ( 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 );
//
//            Array < cds :: meta :: RemoveReference < decltype ( collection ) > :: ConstIterator > iterators;
//            collection.find ( 2, 5, iterators );
//
//            if ( iterators.size () != 2 ) {
//                this->logError ( "wrong element count found" );
//                allOk = false;
//            }
//
//            if ( * iterators[0] != 5 || * iterators[1] != 5 ) {
//                this->logError ( "Iterators not ok from value pov" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iterators[0] ) != 6 || * ( ++ iterators[1] ) != 4 ) {
//                this->logError ( "Iterators not positioned in correct places" );
//                allOk = false;
//            }
//
//            iterators.clear();
//            collection.find ( 1, 5, iterators );
//            if ( iterators.size() != 1 ) {
//                this->logError ( "wrong iterator count returned by limited find" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iterators[0] ) != 6 ) {
//                this->logError ( "Iterator not positioned in correct place" );
//                allOk = false;
//            }
//
//            auto iteratorsReturned = collection.find < Array > ( 2, 5 );
//
//            if ( iteratorsReturned.size () != 2 ) {
//                this->logError ( "wrong element count found" );
//                allOk = false;
//            }
//
//            if ( * iteratorsReturned[0] != 5 || * iteratorsReturned[1] != 5 ) {
//                this->logError ( "Iterators not ok from value pov" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iteratorsReturned[0] ) != 6 || * ( ++ iteratorsReturned[1] ) != 4 ) {
//                this->logError ( "Iterators not positioned in correct places" );
//                allOk = false;
//            }
//
//            iter = collection.findFirst ( 5 );
//
//            if ( * iter != 5 ) {
//                this->logError ( "Iterator not ok from value PoV" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iter ) != 6 ) {
//                this->logError ( "Iterator not ok from position PoV" );
//                allOk = false;
//            }
//
//            iter = collection.findLast ( 5 );
//
//            if ( * iter != 5 ) {
//                this->logError ( "Iterator not ok from value PoV" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iter ) != 4 ) {
//                this->logError ( "Iterator not ok from position PoV" );
//                allOk = false;
//            }
//
//            iterators.clear();
//
//            collection.findAll ( 5, iterators );
//
//            if ( iterators.size () != 2 ) {
//                this->logError ( "wrong element count found" );
//                allOk = false;
//            }
//
//            if ( * iterators[0] != 5 || * iterators[1] != 5 ) {
//                this->logError ( "Iterators not ok from value pov" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iterators[0] ) != 6 || * ( ++ iterators[1] ) != 4 ) {
//                this->logError ( "Iterators not positioned in correct places" );
//                allOk = false;
//            }
//
//            iteratorsReturned = collection.findAll < Array > ( 5 );
//
//            if ( iteratorsReturned.size () != 2 ) {
//                this->logError ( "wrong element count found" );
//                allOk = false;
//            }
//
//            if ( * iteratorsReturned[0] != 5 || * iteratorsReturned[1] != 5 ) {
//                this->logError ( "Iterators not ok from value pov" );
//                allOk = false;
//            }
//
//            if ( * ( ++ iteratorsReturned[0] ) != 6 || * ( ++ iteratorsReturned[1] ) != 4 ) {
//                this->logError ( "Iterators not positioned in correct places" );
//                allOk = false;
//            }
//        });
//    };
//
//    auto objectTest = [this, & allOk]( experimental :: Collection < String > & collection, experimental :: Collection < String > & emptyCollection ) {
//
//        this->log ( "Object in test : %s", collection.toString().cStr() );
//        this->log ( "Empty object in test : %s", emptyCollection.toString().cStr() );
//
//        this->executeSubtest ("cds :: Object functions", [&]{
//
//            std :: stringstream out1, out2;
//            out1 << collection;
//            this->log ( "operator << : %s", out1.str().c_str() );
//
//            out2 << emptyCollection;
//            this->log ( "operator on empty << : %s", out2.str().c_str() );
//        });
//    };
//
//    constructionTest < experimental :: Array > ();
//    constructionTest < experimental :: LinkedList > ();
//
//    this->executeSubtest ( "Array Primitive Test", [&]{ primitiveTest ( arrayTestObject, emptyArrayTestObject ); } );
//    this->executeSubtest ( "Array Object Test", [&]{ objectTest ( arrayTestObjectStr, emptyArrayTestObjectStr ); } );
//
////    this->executeSubtest ( "LinkedList Primitive Test", [&]{ primitiveTest ( listTestObject ); } );
////    this->executeSubtest ( "LinkedList Object Test", [&]{ objectTest ( listTestObjectStr ); } );
//
//    return allOk;
//}
//
//#endif

#include <CDS/experimental/Array>
#include <CDS/experimental/LinkedList>
#include <CDS/experimental/HashSet>
#include <CDS/experimental/HashMap>

/* CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20. Tests CT-00003 to CT-00016 */
template <
        typename __MemberType // NOLINT(bugprone-reserved-identifier)
> auto collectionTestGroupMemberFunctions (
        cds :: experimental :: Collection < __MemberType >        & collection,
        Test                                                      * pTestLib,
        String                                              const & expectedToString,
        Size                                                        expectedSize,
        __MemberType                                        const & toBeFound,
        __MemberType                                        const & toNotBeFound,
        Size                                                        expectedHash,
        cds :: Object                                       const & equalSameType,
        cds :: Object                                       const & equalDifferentType,
        cds :: Object                                       const & notEqualSameType,
        cds :: Object                                       const & notEqualDifferentType,
        cds :: Object                                       const & notEqualNonCollection
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


    /* CollectionTest-MemberFunctions-toString-CPP20 : CT-00003-MF-toString-CPP20 */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'CT-00003-MF-toString-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00003-MF-toString-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-size-CPP20 : CT-00004-MF-size-CPP20 */
    auto size = collection.size();
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, expectedSize );
    if ( size != expectedSize ) {
        pTestLib->logError( "'CT-00004-MF-size-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00004-MF-size-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-empty-CPP20 : CT-00005-MF-empty-CPP20 */
    auto empty = collection.empty();
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( empty != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CT-00005-MF-empty-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00005-MF-empty-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-boolCast-CPP20 : CT-00006-MF-boolCast-CPP20 */
    auto boolCast = static_cast < bool > ( collection.empty() );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", expectedSize == 0ULL ? "true" : "false" );
    if ( boolCast != ( expectedSize == 0ULL ) ) {
        pTestLib->logError( "'CT-00006-MF-boolCast-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00006-MF-boolCast-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-containsTrue-CPP20 : CT-00007-MF-containsTrue-CPP20 */
    auto containsTrue = collection.contains ( toBeFound );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "true" );
    if ( ! containsTrue ) {
        pTestLib->logError( "'CT-00007-MF-containsTrue-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00007-MF-containsTrue-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-containsFalse-CPP20 : CT-00008-MF-containsFalse-CPP20 */
    auto containsFalse = collection.contains ( toNotBeFound );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    if ( containsFalse ) {
        pTestLib->logError( "'CT-00008-MF-containsFalse-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00008-MF-containsFalse-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00009-MF-hash-CPP20 */
    auto hash = collection.hash();
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, expectedHash );
    if ( hash != expectedHash ) {
        pTestLib->logError( "'CT-00009-MF-hash-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00009-MF-hash-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00011-MF-equalsSelf-CPP20 */
    auto equalsToSelf = collection.equals ( collection );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    if ( ! equalsToSelf ) {
        pTestLib->logError( "'CT-00011-MF-equalsSelf-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00011-MF-equalsSelf-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00012-MF-equalsTrueSameType-CPP20 */
    auto equalsToEqualSameType = collection.equals ( equalSameType );
    pTestLib->log ( "object 'equals to equal, same type' : '%s', expected 'equals to equal, same type' : '%s'", equalsToEqualSameType ? "true" : "false", "true" );
    if ( ! equalsToEqualSameType ) {
        pTestLib->logError( "'CT-00012-MF-equalsTrueSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00012-MF-equalsTrueSameType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00013-MF-equalsTrueDifferentType-CPP20 */
    auto equalsToEqualDiffType = collection.equals ( equalDifferentType );
    pTestLib->log ( "object 'equals to equal, different type' : '%s', expected 'equals to equal, different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "true" );
    if ( ! equalsToEqualDiffType ) {
        pTestLib->logError( "'CT-00013-MF-equalsTrueDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00013-MF-equalsTrueDifferentType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00014-MF-equalsFalseSameType-CPP20 */
    auto notEqualsToSameType = collection.equals ( notEqualSameType );
    pTestLib->log ( "object 'equals to not equal, same type' : '%s', expected 'equals to not equal, same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    if ( notEqualsToSameType ) {
        pTestLib->logError( "'CT-00014-MF-equalsFalseSameType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00014-MF-equalsFalseSameType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00015-MF-equalsFalseDifferentType-CPP20 */
    auto notEqualsToDifferentType = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, different type' : '%s', expected 'equals to not equal, different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CT-00015-MF-equalsFalseDifferentType-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00015-MF-equalsFalseDifferentType-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-hash-CPP20 : CT-00016-MF-equalsFalseNotCollection-CPP20 */
    auto notEqualsToOtherObject = collection.equals ( notEqualDifferentType );
    pTestLib->log ( "object 'equals to not equal, not collection' : '%s', expected 'equals to not equal, not collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );
    if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CT-00016-MF-equalsFalseNotCollection-CPP20' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00016-MF-equalsFalseNotCollection-CPP20' OK" );
    }

    /* CollectionTest-MemberFunctions-clear-CPP20 : CT-00010-MF-clear-CPP20 */
    collection.clear();

    empty                       = collection.empty();
    boolCast                    = static_cast < bool > ( collection.empty() );
    size                        = collection.size();
    hash                        = collection.hash();
    containsTrue                = collection.contains( toBeFound );
    containsFalse               = collection.contains( toNotBeFound );
    asString                    = collection.toString();
    equalsToSelf                = collection.equals ( collection );
    equalsToEqualSameType       = collection.equals ( equalSameType );
    equalsToEqualDiffType       = collection.equals ( equalDifferentType );
    notEqualsToSameType         = collection.equals ( notEqualSameType );
    notEqualsToDifferentType    = collection.equals ( notEqualDifferentType );
    notEqualsToOtherObject      = collection.equals ( notEqualNonCollection );

    pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
    pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );
    pTestLib->log ( "object 'size' : '%llu'. expected 'size' : '%llu'", size, 0ULL );
    pTestLib->log ( "object 'empty' : '%s'. expected 'empty' : '%s'", empty ? "true" : "false", "true" );
    pTestLib->log ( "object 'bool cast' : '%s'. expected 'bool cast' : '%s'", boolCast ? "true" : "false", "true" );
    pTestLib->log ( "object 'containsTrue' : '%s'. expected 'containsTrue' : '%s'", containsTrue ? "true" : "false", "false" );
    pTestLib->log ( "object 'containsFalse' : '%s'. expected 'containsFalse' : '%s'", containsFalse ? "true" : "false", "false" );
    pTestLib->log ( "object 'hash' : '%llu', expected 'hash' : '%llu'", hash, 0ULL );
    pTestLib->log ( "object 'equals to self' : '%s', expected 'equals to self' : '%s'", equalsToSelf ? "true" : "false", "true" );
    pTestLib->log ( "object 'equals to equal same type' : '%s', expected 'equals to equal same type' : '%s'", equalsToEqualSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to equal different type' : '%s', expected 'equals to equal different type' : '%s'", equalsToEqualDiffType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal same type' : '%s', expected 'equals to not equal same type' : '%s'", notEqualsToSameType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to not equal different type' : '%s', expected 'equals to not equal different type' : '%s'", notEqualsToDifferentType ? "true" : "false", "false" );
    pTestLib->log ( "object 'equals to non-collection' : '%s', expected 'equals to non-collection' : '%s'", notEqualsToOtherObject ? "true" : "false", "false" );

    if ( asString.length() > 2ULL ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - toString' failed" );
        return false;
    } else if ( size != 0ULL ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - size' failed" );
        return false;
    } else if ( ! empty ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - empty' failed" );
        return false;
    } else if ( ! boolCast ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - bool cast' failed" );
        return false;
    } else if ( containsTrue || containsFalse ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - contains' failed" );
        return false;
    } else if ( hash != 0ULL ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - hash' failed" );
        return false;
    } else if ( ! equalsToSelf ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToSelf' failed" );
        return false;
    } else if ( equalsToEqualSameType ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( equalsToEqualDiffType ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToSameType ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToNotEqualSameTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToDifferentType ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToNotEqualDiffTypePrevToClear' failed" );
        return false;
    } else if ( notEqualsToOtherObject ) {
        pTestLib->logError( "'CT-00010-MF-clear-CPP20 - equalsToNotEqualOtherObj' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'CT-00010-MF-clear-CPP20' OK" );
    }


    return true;
}

/* CollectionTestSuiteCPP20 : CTS-00001-CPP20 */
auto CollectionTest :: execute () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntArray", [& allOk, this] {

        cds :: experimental :: Array < int > intArrayObjectUnderTest;
        intArrayObjectUnderTest     = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
        ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < int > intLinkedListObjectUnderTest;
        intLinkedListObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "[ 1, 2, 3, 4, 5 ]";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: LinkedList < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: Array < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: LinkedList < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: Array < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < int > intHashSetObjectUnderTest;
        intHashSetObjectUnderTest = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = 2;
        auto expectedToBeNotFound   = 7;
        auto expectedHash           = ((((
                                                 cds :: hash ( 1 ) * 31 + cds :: hash ( 2 )
                                         ) * 31 + cds :: hash ( 3 )) * 31 + cds :: hash ( 4 ) ) * 31 + cds :: hash ( 5 ));

        auto equalSameType          = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto equalDifferentType     = cds :: experimental :: HashSet < int > { 1, 2, 3, 4, 5 };
        auto notEqualSameType       = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < int > { 1, 2, 3, 5 };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions (
                intHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : IntToIntHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < int, int > intIntHashMapObjectUnderTest;
        intIntHashMapObjectUnderTest = { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };

        auto expectedToString       = "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }";
        auto expectedSize           = 5;
        auto expectedToBeFound      = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 2, 7 );
        auto expectedToBeNotFound   = decltype ( intIntHashMapObjectUnderTest ) :: EntryType ( 6, 20 );
        auto expectedHash           = ((((
                                                 ( cds :: hash (1) ^ cds :: hash (6) ) * 31 + ( cds :: hash ( 2 ) ^ cds :: hash (7))
                                         ) * 31 + ( cds :: hash ( 3 )) ^ cds :: hash (8)) * 31 + ( cds :: hash ( 4 ) ^ cds :: hash (9)) ) * 31 + ( cds :: hash ( 5 )) ^ cds :: hash (10));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto equalDifferentType     = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {4, 9}, {5, 10} };
        auto notEqualSameType       = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < int, int > { {1, 6}, {2, 7}, {3, 8}, {5, 10} };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions (
                intIntHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringArray", [& allOk, this] {

        cds :: experimental :: Array < cds :: String > stringArrayObjectUnderTest;
        stringArrayObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
        ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringArrayObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringLinkedList", [& allOk, this] {

        cds :: experimental :: LinkedList < cds :: String > stringLinkedListObjectUnderTest;
        stringLinkedListObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "[ Ana, are, mere ]";
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "Ana" ) * 31 + cds :: hash ( "are" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: Array < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: LinkedList < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: Array < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringLinkedListObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringHashSet", [& allOk, this] {

        cds :: experimental :: HashSet < cds :: String > stringHashSetObjectUnderTest;
        stringHashSetObjectUnderTest     = { "Ana", "are", "mere" };

        auto expectedToString       = "{ are, Ana, mere }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = "Ana";
        auto expectedToBeNotFound   = "ana";
        auto expectedHash           = (
                                              cds :: hash ( "are" ) * 31 + cds :: hash ( "Ana" )
                                      ) * 31 + cds :: hash ( "mere" );

        auto equalSameType          = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto equalDifferentType     = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "mere" };
        auto notEqualSameType       = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualDifferentType  = cds :: experimental :: HashSet < cds :: String > { "Ana", "are", "pere" };
        auto notEqualNonCollection  = cds :: String { "[ 1, 2, 3, 4, 5 ]" };

        auto status = collectionTestGroupMemberFunctions < cds :: String > (
                stringHashSetObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    this->executeSubtest ( "CollectionTestGroup-MemberFunctions-CPP20 : CTG-00002-MF-CPP20 : StringToStringHashMap", [& allOk, this] {

        cds :: experimental :: HashMap < cds :: String, cds :: String > stringStringHashMapObjectUnderTest;
        stringStringHashMapObjectUnderTest = { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };

        auto expectedToString       = "{ are: verb, Ana: name, mere: noun }"; /// due to hash table
        auto expectedSize           = 3;
        auto expectedToBeFound      = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "are", "verb" );
        auto expectedToBeNotFound   = decltype ( stringStringHashMapObjectUnderTest ) :: EntryType ( "pere", "noun" );
        auto expectedHash           = (
                                               (( cds :: hash ("are") ^ cds :: hash ("verb") ) * 31 + ( cds :: hash ( "Ana" ) ^ cds :: hash ("name")))
                                          * 31 + ( cds :: hash ( "mere" ) ^ cds :: hash ("noun")));

        /* error reported by IDE makes no sense? */
        auto equalSameType          = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto equalDifferentType     = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "noun" } };
        auto notEqualSameType       = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "pere", "noun" } };
        auto notEqualDifferentType  = cds :: experimental :: HashMap < cds :: String, cds :: String > { { "Ana", "name" }, { "are", "verb" }, { "mere", "other" } };
        auto notEqualNonCollection  = cds :: String { "{ 1: 6, 2: 7, 3: 8, 4: 9, 5: 10 }" };

        auto status = collectionTestGroupMemberFunctions < cds :: MapEntry < cds :: String, cds :: String > > (
                stringStringHashMapObjectUnderTest,
                this,
                expectedToString,
                expectedSize,
                expectedToBeFound,
                expectedToBeNotFound,
                expectedHash,
                equalSameType,
                equalDifferentType,
                notEqualSameType,
                notEqualDifferentType,
                notEqualNonCollection
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    return allOk;
}
