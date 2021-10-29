//
// Created by loghin on 04.06.2021.
//
#include "SequenceTest.h"

#include <CDS/Range>
#include <CDS/HashMap>
#include <CDS/OrderedSet>
#include <CDS/UnorderedSet>

#include <CDS/Sequence>
#include <CDS/Integer>
#include <CDS/Long>
#include <CDS/Float>
#include <CDS/Double>
#include <utility>

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif

bool SequenceTest::execute() noexcept {
    bool ok = true;
    this->log("Start of test Sequence ... ");

    Range r(20);
    Array < float > fArray = {0.5f, 0.3f, 1.7f, 3.0f, 2.2f, 1.4f, 2.2f, 4.0f, 3.0f, 0.3f, 0.5f, 0.5f, 4.3f, 2.1f, 2.2f};
    LinkedList < String > sList = String("Ana are mere, dar merele o au pe Ana?. Ce este cert, Ana are pere si mere").split(" ,?.");
    HashMap < String, int > siHMap;
    OrderedSet < int > intSet = {4, 2 ,1 ,0 , 1, 2, 7 , 8, 9 ,14, 11, 2, 5};
    UnorderedSet < uint32 > uintUSet = { 3, 1, 2 ,11, 14, 7 };

    sList.forEach([& siHMap](auto & s){
        if ( siHMap.containsKey(s) ) siHMap[s] ++;
        else siHMap[s] = 1;
    });

    this->executeSubtest("Datatypes involved initialisations", [=, this] {
        this->log("Original Types : ");
        this->log("\tRange : '%s'", r.toString().cStr());
        this->log("\tArray<float> : '%s'", fArray.toString().cStr());
        this->log("\tList<String> : '%s'", sList.toString().cStr());
        this->log("\tMap<String, int> : '%s'", siHMap.toString().cStr());
        this->log("\tOSet<int> : '%s'", intSet.toString().cStr());
        this->log("\tUSet<uint> : '%s'", uintUSet.toString().cStr());
    });

    this->executeSubtest("Constructors/Destructors, Copy, Move, Clear tests", [&] {
        Range r3 = r;
        Range const & r2 = r;

        this->log("<Range> Ctor Resolution Test : '%s'", Sequence(r3).toString().cStr());
        this->log("<Range &> Ctor Resolution Test : '%s'", Sequence(r2).toString().cStr());
        this->log("<Range const &> Ctor Resolution Test : '%s'", Sequence(r).toString().cStr());
        this->log("<Range &&> Ctor Resolution Test : '%s'", Sequence(Range(r)).toString().cStr());

        Array a1 = fArray;
        Array<float> & a2 = fArray;
        Array<float> const & a3 = fArray;

        this->log("<Array> Ctor Resolution Test : '%s'", Sequence(a1).toString().cStr());
        this->log("<Array &> Ctor Resolution Test : '%s'", Sequence(a2).toString().cStr());
        this->log("<Array const &> Ctor Resolution Test : '%s'", Sequence(a3).toString().cStr());
        this->log("<Array &&> Ctor Resolution Test : '%s'", Sequence(Array(fArray)).toString().cStr());

        LinkedList<String> l1 = sList;
        LinkedList<String> & l2 = sList;
        LinkedList<String> const & l3 = sList;

        this->log("<List> Ctor Resolution Test : '%s'", Sequence(l1).toString().cStr());
        this->log("<List &> Ctor Resolution Test : '%s'", Sequence(l2).toString().cStr());
        this->log("<List const &> Ctor Resolution Test : '%s'", Sequence(l3).toString().cStr());
        this->log("<List &&> Ctor Resolution Test : '%s'", Sequence(DoubleLinkedList(sList)).toString().cStr());

        HashMap<String, int > m1 = siHMap;
        HashMap<String, int > & m2 = siHMap;
        HashMap<String, int > const & m3 = siHMap;

        this->log("<Map> Ctor Resolution Test : '%s'", Sequence(m1).toString().cStr());
        this->log("<Map &> Ctor Resolution Test : '%s'", Sequence(m2).toString().cStr());
        this->log("<Map const &> Ctor Resolution Test : '%s'", Sequence(m3).toString().cStr());
        this->log("<Map &&> Ctor Resolution Test : '%s'", Sequence(HashMap(siHMap)).toString().cStr());

        OrderedSet< int > o1 = intSet;
        OrderedSet< int > & o2 = intSet;
        OrderedSet< int > const & o3 = intSet;

        this->log("<OrderedSet> Ctor Resolution Test : '%s'", Sequence(o1).toString().cStr());
        this->log("<OrderedSet &> Ctor Resolution Test : '%s'", Sequence(o2).toString().cStr());
        this->log("<OrderedSet const &> Ctor Resolution Test : '%s'", Sequence(o3).toString().cStr());
        this->log("<OrderedSet &&> Ctor Resolution Test : '%s'", Sequence(OrderedSet(intSet)).toString().cStr());

        UnorderedSet< uint32 > u1 = uintUSet;
        UnorderedSet< uint32 > & u2 = uintUSet;
        UnorderedSet< uint32 > const & u3 = uintUSet;

        this->log("<UnorderedSet> Ctor Resolution Test : '%s'", Sequence(u1).toString().cStr());
        this->log("<UnorderedSet &> Ctor Resolution Test : '%s'", Sequence(u2).toString().cStr());
        this->log("<UnorderedSet const &> Ctor Resolution Test : '%s'", Sequence(u3).toString().cStr());
        this->log("<UnorderedSet &&> Ctor Resolution Test : '%s'", Sequence(UnorderedSet(uintUSet)).toString().cStr());
    });

    this->executeSubtest("Iterative Properties", [& ok, this]{
        auto elementAtTest = [&] {
            bool e1Thrown = false, e2Thrown = false;

            auto list = Array<int>{1, 2, 3}.sequence();

            log("list : %s", list.toArray().toString().cStr());
            log("elementAt(0) : %d", list.elementAt(0).value());
            log("elementAt(2) : %d", list.elementAt(2).value());

            try {
                log("elementAt(3) : %d", list.elementAt(3).value());
            } catch (Exception const &) {
                log("elementAt(3) returned empty Optional<int>");
                e1Thrown = true;
            }

            auto emptyList = Array<int>().sequence();

            log("emptyList : %s", emptyList.toArray().toString().cStr());

            try {
                log("elementAt(0) : %d", emptyList.elementAt(0).value());
            } catch (Exception const &) {
                log("elementAt(0) returned empty Optional <int>");
                e2Thrown = true;
            }

            if (
                    list.elementAt(0).value() != 1 ||
                    list.elementAt(2).value() != 3 ||
                    ! e1Thrown ||
                    ! e2Thrown
            ) {
                ok = false;
                log("elementAt error");
            }
        };

        auto elementAtOrElseTest = [&] {
            auto list = Array < int > {1, 2, 3}.sequence();

            log("list : %s", list.toArray().toString().cStr());
            log("elementAtOr(0, 42) : %d", list.elementAtOr(0, 42));
            log("elementAtOr(2, 42) : %d", list.elementAtOr(2, 42));
            log("elementAtOr(3, 42) : %d", list.elementAtOr(3, 42));

            auto emptyList = Array<int>().sequence();

            log("emptyList : %s", emptyList.toArray().toString().cStr());
            log("elementAtOr(0, 84) : %d", emptyList.elementAtOr(0, 82));

            if (
                    list.elementAtOr(0, 42) != 1 ||
                    list.elementAtOr(2, 42) != 3 ||
                    list.elementAtOr(3, 42) != 42 ||
                    emptyList.elementAtOr(0, 84) != 84
            ) {
                ok = false;
                log("elementAtOr error");
            }
        };

        auto elementAtOrNullTest = [&] {
            auto list = Array < int * > { new int(1), new int(2), new int(3) }.sequence();

            log("list : %s", list.toArray().toString().cStr());
            log("list.elementAtOrNull(0) : %d", * list.elementAtOrNull(0));
            log("list.elementAtOrNull(2) : %d", * list.elementAtOrNull(2));

            auto p = list.elementAtOrNull(3);
            if ( p == nullptr )
                log("list.elementAtOrNull(3) : nullptr");

            auto emptyList = Array<int *>().sequence();

            log("emptyList : %s", emptyList.toArray().toString().cStr());
            p = emptyList.elementAtOrNull(0);

            log("emptyList : %s", emptyList.toArray().toString().cStr());
            if ( p == nullptr )
                log("emptyList.elementAtOrNull(0) : nullptr");

            list.forEach([](int * e){delete e;});
        };

        auto findTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5, 6, 7 }.sequence();
            auto firstOdd = numbers.find( Int::isOdd );
            auto lastEven = numbers.findLast( Int::isEven );
            auto firstNegative = numbers.find( [](Int const & a) { return a < 0; } );

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "firstOdd : %s", firstOdd.toString().cStr() );
            log( "lastEven : %s", lastEven.toString().cStr() );
            log( "firstNegative : %s", firstNegative.toString().cStr() );

            if ( firstOdd.value() != 1 || lastEven.value() != 6 || firstNegative.hasValue() ) {
                ok = false;
                logWarning("find error");
            }
        };

        auto firstTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5 }.sequence();
            auto first = numbers.first();
            auto firstEven = numbers.first(Int::isEven);
            auto firstNegative = numbers.first([](Int const & n){ return n < 0; });

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "first : %s", first.toString().cStr() );
            log( "firstEven : %s", firstEven.toString().cStr() );
            log( "firstNegative : %s", firstNegative.toString().cStr() );

            if ( first.value () != 1 || firstEven.value() != 2 || firstNegative.hasValue() ) {
                ok = false;
                logWarning("first error");
            }
        };

        auto firstOrTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5 }.sequence();
            auto first = numbers.firstOr(15);
            auto firstEven = numbers.firstOr(15,Int::isEven);
            auto firstNegative = numbers.firstOr(15,[](Int const & n){ return n < 0; });

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "first : %s", first.toString().cStr() );
            log( "firstEven : %s", firstEven.toString().cStr() );
            log( "firstNegative : %s", firstNegative.toString().cStr() );

            if ( first != 1 || firstEven != 2 || firstNegative != 15 ) {
                ok = false;
                logWarning("first error");
            }
        };

        auto lastTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5 }.sequence();
            auto last = numbers.last();
            auto lastEven = numbers.last(Int::isEven);
            auto lastNegative = numbers.last([](Int const & n){ return n < 0; });

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "last : %s", last.toString().cStr() );
            log( "lastEven : %s", lastEven.toString().cStr() );
            log( "lastNegative : %s", lastNegative.toString().cStr() );

            if ( last.value () != 5 || lastEven.value() != 4 || lastNegative.hasValue() ) {
                ok = false;
                logWarning("last error");
            }
        };

        auto lastOrTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5 }.sequence();
            auto last = numbers.lastOr(15);
            auto lastEven = numbers.lastOr(15,Int::isEven);
            auto lastNegative = numbers.lastOr(15,[](Int const & n){ return n < 0; });

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "last : %s", last.toString().cStr() );
            log( "lastEven : %s", lastEven.toString().cStr() );
            log( "lastNegative : %s", lastNegative.toString().cStr() );

            if ( last != 5 || lastEven != 4 || lastNegative != 15 ) {
                ok = false;
                logWarning("last error");
            }
        };

        auto maxTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 4,  3, 2, 1 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers.max : %d", numbers.max().value());
            log("emptyList.max : %s", Array<int>{}.sequence().max().toString().cStr());

            if ( numbers.max().value() != 5 || Array<int>{}.sequence().max().hasValue() ) {
                logWarning("max error");
                ok = false;
            }

            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %s", strings.max().value().cStr());

            if ( strings.max().value() != "pe" ) {
                logWarning("max error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %s", pairs.max([](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).value().toString().cStr());

            if (
                    pairs.max([](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).value()
                    !=
                    Pair < int, int > { 1, 6 }
            ) {
                logWarning("max error");
                ok = false;
            }
        };

        auto maxByTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %s", strings.maxBy([](String const & s){return s.length();}).value().cStr());
            log("emptyList.max : %s", Array<String>{}.sequence().maxBy([](String const & s){return s.length();}).toString().cStr());

            if (
                    strings.maxBy([](String const & s){return s.length();}).value() != "merele" ||
                    Array<String>{}.sequence().maxBy([](String const & s){return s.length();}).hasValue()
            ) {
                logWarning("maxby error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %s", pairs.maxBy([](Pair<int, int> const & a){ return a.first() + a.second(); }).value().toString().cStr());

            if (
                    pairs.maxBy([](Pair<int, int> const & a){ return a.first() + a.second(); }).value()
                    !=
                    Pair < int, int > { 1, 6 }
                    ) {
                logWarning("maxby error");
                ok = false;
            }
        };

        auto maxOfTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %d", strings.maxOf([](String const & s){return s.length();}).value());
            log("emptyList.max : %d", Array<String>{}.sequence().maxOf([](String const & s){return s.length();}).toString().cStr());

            if (
                    strings.maxOf([](String const & s){return s.length();}).value() != 6 ||
                    Array<String>{}.sequence().maxOf([](String const & s){return s.length();}).hasValue()
            ) {
                logWarning("maxof error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %d", pairs.maxOf([](Pair<int, int> const & a){ return a.first() + a.second(); }).value());

            if (
                    pairs.maxOf([](Pair<int, int> const & a){ return a.first() + a.second(); }).value()
                    !=
                    7
            ) {
                logWarning("maxof error");
                ok = false;
            }
        };

        auto maxOrTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 4,  3, 2, 1 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers.max : %d", numbers.maxOr(15));
            log("emptyList.max : %d", Array<int>{}.sequence().maxOr(15));

            if ( numbers.maxOr(15) != 5 || Array<int>{}.sequence().maxOr(15) != 15 ) {
                logWarning("maxOr error");
                ok = false;
            }

            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %s", strings.maxOr("no-max").cStr());

            if ( strings.maxOr("no-max") != "pe" ) {
                logWarning("maxOr error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %s", pairs.maxOr(Pair<int,int>{9, 9}, [](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).toString().cStr());

            if (
                    pairs.maxOr(Pair<int,int>{9,9},[](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); })
                    !=
                    Pair < int, int > { 1, 6 }
            ) {
                logWarning("maxOr error");
                ok = false;
            }
        };

        auto maxByOrTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %s", strings.maxByOr("no-max", [](String const & s){return s.length();}).cStr());
            log("emptyList.max : %s", Array<String>{}.sequence().maxByOr("no-max", [](String const & s){return s.length();}).cStr());

            if (
                    strings.maxByOr("no-max",[](String const & s){return s.length();}) != "merele" ||
                    Array<String>{}.sequence().maxByOr("no-max", [](String const & s){return s.length();}) != "no-max"
            ) {
                logWarning("maxbyor error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %s", pairs.maxByOr(Pair<int,int>{0,0},[](Pair<int, int> const & a){ return a.first() + a.second(); }).toString().cStr());

            if (
                    pairs.maxByOr(Pair<int,int>{0,0},[](Pair<int, int> const & a){ return a.first() + a.second(); })
                    !=
                    Pair < int, int > { 1, 6 }
            ) {
                logWarning("maxbyor error");
                ok = false;
            }
        };

        auto maxOfOrTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.max : %d", strings.maxOfOr(0,[](String const & s){return s.length();}));
            log("emptyList.max : %d", Array<String>{}.sequence().maxOfOr(0, [](String const & s){return s.length();}));

            if (
                    strings.maxOfOr(0, [](String const & s){return s.length();}) != 6 ||
                    Array<String>{}.sequence().maxOfOr(0, [](String const & s){return s.length();}) != 0
            ) {
                logWarning("maxofor error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.max : %d", pairs.maxOfOr(0,[](Pair<int, int> const & a){ return a.first() + a.second(); }));

            if (
                    pairs.maxOfOr(0,[](Pair<int, int> const & a){ return a.first() + a.second(); })
                    !=
                    7
            ) {
                logWarning("maxofor error");
                ok = false;
            }
        };

        auto minTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 4,  3, 2, 1 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers.min : %d", numbers.min().value());
            log("emptyList.min : %s", Array<int>{}.sequence().min().toString().cStr());

            if ( numbers.min().value() != 1 || Array<int>{}.sequence().min().hasValue() ) {
                logWarning("max error");
                ok = false;
            }

            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %s", strings.min().value().cStr());

            if ( strings.min().value() != "Ana" ) {
                logWarning("min error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %s", pairs.min([](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).value().toString().cStr());

            if (
                    pairs.min([](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).value()
                    !=
                    Pair < int, int > { 2, 3 }
            ) {
                logWarning("min error");
                ok = false;
            }
        };

        auto minByTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %s", strings.minBy([](String const & s){return s.length();}).value().cStr());
            log("emptyList.min : %s", Array<String>{}.sequence().minBy([](String const & s){
                return s.length();
            }).toString().cStr());

            if (
                    strings.minBy([](String const & s){return s.length();}).value() != "o" ||
                    Array<String>{}.sequence().minBy([](String const & s){return s.length();}).hasValue()
            ) {
                logWarning("minby error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %s", pairs.minBy([](Pair<int, int> const & a){ return a.first() + a.second(); }).value().toString().cStr());

            if (
                    pairs.minBy([](Pair<int, int> const & a){ return a.first() + a.second(); }).value()
                    !=
                    Pair < int, int > { 2, 3 }
            ) {
                logWarning("minby error");
                ok = false;
            }
        };

        auto minOfTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %d", strings.minOf([](String const & s){return s.length();}).value());
            log("emptyList.min : %s", Array<String>{}.sequence().minOf([](String const & s){return s.length();}).toString().cStr());

            if (
                    strings.minOf([](String const & s){return s.length();}).value() != 1 ||
                    Array<String>{}.sequence().minOf([](String const & s){return s.length();}).hasValue()
            ) {
                logWarning("minof error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %d", pairs.minOf([](Pair<int, int> const & a){ return a.first() + a.second(); }).value());

            if (
                    pairs.minOf([](Pair<int, int> const & a){ return a.first() + a.second(); }).value()
                    !=
                    5
            ) {
                logWarning("minof error");
                ok = false;
            }
        };

        auto minOrTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 4,  3, 2, 1 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers.min : %d", numbers.minOr(15));
            log("emptyList.min : %d", Array<int>{}.sequence().minOr(15));

            if ( numbers.minOr(15) != 1 || Array<int>{}.sequence().minOr(15) != 15 ) {
                logWarning("minOr error");
                ok = false;
            }

            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %s", strings.minOr("no-min").cStr());

            if ( strings.minOr("no-min") != "Ana" ) {
                logWarning("minOr error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %s", pairs.minOr(Pair<int,int>{9, 9}, [](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); }).toString().cStr());

            if (
                    pairs.minOr(Pair<int,int>{9,9},[](Pair<int, int> const & a, Pair<int, int> const &b){ return a.first() + a.second() < b.first() + b.second(); })
                    !=
                    Pair < int, int > { 2, 3 }
            ) {
                logWarning("minOr error");
                ok = false;
            }
        };

        auto minByOrTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %s", strings.minByOr("no-min", [](String const & s){return s.length();}).cStr());
            log("emptyList.min : %s", Array<String>{}.sequence().minByOr("no-min", [](String const & s){return s.length();}).cStr());

            if (
                    strings.minByOr("no-min",[](String const & s){return s.length();}) != "o" ||
                    Array<String>{}.sequence().minByOr("no-min", [](String const & s){return s.length();}) != "no-min"
            ) {
                logWarning("minbyor error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %s", pairs.minByOr(Pair<int,int>{0,0},[](Pair<int, int> const & a){ return a.first() + a.second(); }).toString().cStr());

            if (
                    pairs.minByOr(Pair<int,int>{0,0},[](Pair<int, int> const & a){ return a.first() + a.second(); })
                    !=
                    Pair < int, int > { 2, 3 }
            ) {
                logWarning("minbyor error");
                ok = false;
            }
        };

        auto minOfOrTest = [&]{
            auto strings = "Ana are mere, dar merele o au pe Ana?"_s.split(", ?").sequence();

            log("strings : %s", strings.toArray().toString().cStr());
            log("strings.min : %d", strings.minOfOr(0,[](String const & s){return s.length();}));
            log("emptyList.min : %d", Array<String>{}.sequence().minOfOr(0, [](String const & s){return s.length();}));

            if (
                    strings.minOfOr(0, [](String const & s){return s.length();}) != 1 ||
                    Array<String>{}.sequence().minOfOr(0, [](String const & s){return s.length();}) != 0
            ) {
                logWarning("minofor error");
                ok = false;
            }

            auto pairs = Array < Pair < int, int > > {
                    {2, 3},
                    {1, 6},
                    {4, 2}
            }.sequence();

            log("pairs : %s", pairs.toArray().toString().cStr());
            log("pairs.min : %d", pairs.minOfOr(0,[](Pair<int, int> const & a){ return a.first() + a.second(); }));

            if (
                    pairs.minOfOr(0,[](Pair<int, int> const & a){ return a.first() + a.second(); })
                    !=
                    5
            ) {
                logWarning("minofor error");
                ok = false;
            }
        };

        auto minusTest = [&]{
            auto numbers = Array < int > {1, 2, 3, 4, 5, 6, 7 ,8, 9}.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers minus 7 : %s", numbers.minus(7).toArray().toString().cStr());
            log("numbers minus {2, 4} : %s", numbers.minus(Array<int>{2, 4}).toArray().toString().cStr());
            log("numbers minus numbers.even : %s", numbers.minus(numbers.filter(Int::isEven)).toArray().toString().cStr());

            if (
                    numbers.minus(7).toArray() != Array <int> { 1, 2, 3, 4, 5, 6, 8, 9} ||
                    numbers.minus(Array<int>{2, 4}).toArray() != Array < int > {1, 3, 5, 6, 7, 8, 9} ||
                    numbers.minus(numbers.filter(Int::isEven)).toArray() != Array < int > {1, 3, 5, 7, 9}
            ) {
                logWarning("minus error");
                ok = false;
            }
        };

        auto plusTest = [&]{
            auto numbers = Array <int> {1, 2, 3, 4, 5}.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers plus 7 : %s", numbers.plus(7).toArray().toString().cStr());
            log("numbers plus {2, 4, 8} : %s", numbers.plus(Array<int>{2, 4, 8}).toString().cStr());
            log("numbers plus 15..20 : %s", numbers.plus(Range(15, 20).sequence()).toArray().toString().cStr());

            if (
                    numbers.plus(7).toArray() != Array <int> { 1, 2,  3, 4, 5, 7 } ||
                    numbers.plus(Array<int>{2, 4, 8}).toArray() != Array<int>{1, 2, 3, 4, 5, 2, 4, 8} ||
                    numbers.plus(Range(15, 20).sequence()).toArray() !=  Array <int> {1, 2, 3, 4, 5, 15, 16, 17, 18, 19}
            ) {
                logWarning("plus error");
                ok = false;
            }
        };

        auto noneTest = [&]{
            auto emptyList = Array<int>{}.sequence();
            auto nonEmptyList = Array<int>{1, 2, 3}.sequence();

            log("emptyList : %s", emptyList.toArray().toString().cStr());
            log("nonEmptyList : %s", nonEmptyList.toArray().toString().cStr());
            log("emptyList.none : %s", emptyList.none().toString().cStr());
            log("nonEmptyList.none : %s", nonEmptyList.none().toString().cStr());

            if ( ! emptyList.none() || nonEmptyList.none() ) {
                logWarning("none error");
                ok = false;
            }

            auto zeroToTen = Range(0, 10).sequence();
            log( "zeroToTen.none isEven : %s", zeroToTen.none(Int::isEven).toString().cStr() );
            log( "zeroToTen.map to uneven . none isEven : %s", zeroToTen.map([](int v){return v * 2 + 1;}).none(Int::isEven).toString().cStr() );
            log( "emptyList.none isEven : %s", Array<int>{}.sequence().none(Int::isEven).toString().cStr() );

            if (
                    zeroToTen.none(Int::isEven) ||
                    ! zeroToTen.map([](int v){return v * 2 + 1;}).none(Int::isEven) ||
                    ! Array<int>{}.sequence().none(Int::isEven)
            ) {
                logWarning("none error");
                ok = false;
            }
        };

        auto singleTest = [&] {
            log("{1}.single() : %s", Array<int>{1}.sequence().single().toString().cStr());
            log("{}.single() : %s", Array<int>{}.sequence().single().toString().cStr());
            log("{1, 2}.single() : %s", Array<int>{1, 2}.sequence().single().toString().cStr());
            log("{1, 2, 3}.single(isEven) : %s", Array<int>{1, 2, 3}.sequence().single(Int::isEven).toString().cStr());
            log("{}.single(isEven) : %s", Array<int>{}.sequence().single(Int::isEven).toString().cStr());
            log("{1, 2, 3, 4, 5}.single(isEven) : %s", Array<int>{1, 2, 3, 4, 5}.sequence().single(Int::isEven).toString().cStr());

            if (
                    ! Array<int>{1}.sequence().single().hasValue() ||
                    Array<int>{}.sequence().single().hasValue() ||
                    Array<int>{1, 2}.sequence().single().hasValue() ||
                    ! Array<int>{1, 2, 3}.sequence().single(Int::isEven).hasValue() ||
                    Array<int>{}.sequence().single(Int::isEven).hasValue() ||
                    Array<int>{1, 2, 3, 4, 5}.sequence().single(Int::isEven).hasValue()
            ) {
                logWarning("Single error");
                ok = false;
            }
        };

        auto singleOrTest = [&] {
            log("{1}.singleOr() : %d", Array<int>{1}.sequence().singleOr(15));
            log("{}.singleOr() : %d", Array<int>{}.sequence().singleOr(15));
            log("{1, 2}.singleOr() : %d", Array<int>{1, 2}.sequence().singleOr(15));
            log("{1, 2, 3}.singleOr(isEven) : %d", Array<int>{1, 2, 3}.sequence().singleOr(15,Int::isEven));
            log("{}.singleOr(isEven) : %d", Array<int>{}.sequence().singleOr(15, Int::isEven));
            log("{1, 2, 3, 4, 5}.singleOr(isEven) : %d", Array<int>{1, 2, 3, 4, 5}.sequence().singleOr(15, Int::isEven));

            if (
                    Array<int>{1}.sequence().singleOr(15) == 15 ||
                    Array<int>{}.sequence().singleOr(15) != 15 ||
                    Array<int>{1, 2}.sequence().singleOr(15) != 15 ||
                    Array<int>{1, 2, 3}.sequence().singleOr(15, Int::isEven) == 15 ||
                    Array<int>{}.sequence().singleOr(15, Int::isEven) != 15 ||
                    Array<int>{1, 2, 3, 4, 5}.sequence().singleOr(15, Int::isEven) != 15
            ) {
                logWarning("SingleOr error");
                ok = false;
            }
        };

        auto sumTest = [&] {
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();
            auto sum = numbers.sum();

            log( "numbers : %s", numbers.toArray().toString().cStr() );
            log( "sum : %d", sum );

            if ( sum != 15 ) {
                logWarning("sum error");
                ok = false;
            }
        };

        auto sumByTest = [&] {
            auto strings = Array < String > { "aaaa", "bb", "ccc", "d" }.sequence();
            auto sum = strings.sumBy([](String const & s){return s.length();});

            log ( "strings : %s", strings.toArray().toString().cStr() );
            log ( "sum : %d", sum );

            if ( sum != 10 ) {
                logWarning("sumBy error");
                ok = false;
            }
        };

        elementAtTest();
        elementAtOrElseTest();
        elementAtOrNullTest ();
        findTest();
        firstTest();
        firstOrTest();
        lastTest();
        lastOrTest();

        maxTest();
        maxByTest();
        maxOfTest();
        maxOrTest();
        maxByOrTest();
        maxOfOrTest();

        minTest();
        minByTest();
        minOfTest();
        minOrTest();
        minByOrTest();
        minOfOrTest();

        minusTest();
        plusTest();

        noneTest();

        singleTest();
        singleOrTest();

        sumTest();
        sumByTest();
    });

    this->executeSubtest("Basic Functional Properties", [& ok, this]{
        auto allTest = [&] {

            auto zeroToTen = Range(0, 10).sequence();

            this->log("Zero To Ten.all(isEven) : %s", zeroToTen.all(Integer::isEven) ? "true" : "false");

            if (zeroToTen.all(Integer::isEven)) {
                ok = false;
                this->logWarning(".all Error");
            }

            auto evens = zeroToTen.map([](Index v) -> Index {
                return v * 2;
            });
            this->log("Evens.all(isEven) : %s", evens.all(Integer::isEven) ? "true" : "false");

            if (!evens.all(Integer::isEven)) {
                ok = false;
                this->logWarning(".all Error");
            }

            auto empty = LinkedList<Int>().sequence();
            this->log("EmptyList.all(isEven) : %s", empty.all(Integer::isEven) ? "true" : "false");

            if (!empty.all(Integer::isEven)) {
                ok = false;
                this->logWarning(".all error");
            }

            log("zeroToTen : %s", zeroToTen.toArray().toString().cStr() );
            log("evens : %s", evens.toArray().toString().cStr() );
            log("empty : %s", empty.toArray().toString().cStr() );
        };

        auto anyTest = [&]{
            auto zeroToTen = Range(0, 10).sequence();

            log("zeroToTen.any(isEven) : %s", zeroToTen.any(Int::isEven).toString().cStr());

            if ( ! zeroToTen.any(Int::isEven) ) {
                ok = false;
                logWarning(".any error");
            }

            auto odds = zeroToTen.map([](int v){return v * 2 + 1;});

            log("odds.any(isEven) : %s", odds.any(Int::isEven).toString().cStr());

            if ( odds.any(Int::isEven) ) {
                ok = false;
                logWarning(".any error");
            }

            auto emptyList = LinkedList<Int>().sequence();

            log("emptyList.any(isEven) : %s", emptyList.any(Int::isEven).toString().cStr());

            if ( emptyList.any(Int::isEven) ) {
                ok = false;
                logWarning(".any error");
            }

            log("zeroToTen : %s", zeroToTen.toArray().toString().cStr());
            log("odds : %s", odds.toArray().toString().cStr());
            log("empty : %s", emptyList.toArray().toString().cStr());
        };

        auto containsTest = [&]{
            log("contents : %s", Array<int>{1, 2, 3, 4, 5}.sequence().toArray().toString().cStr());
            log("contains 3 : %s", Array<int>{1, 2, 3, 4, 5}.sequence().contains(3).toString().cStr());
            log("contains 6 : %s", Array<int>{1, 2, 3, 4, 5}.sequence().contains(6).toString().cStr());

            if ( ! Array<int>{1, 2, 3, 4, 5}.sequence().contains(3) ) {
                ok = false;
                logWarning("contains error");
            }

            auto oneToFive = Range(1, 6).sequence();

            if ( oneToFive.contains(6) ) {
                ok = false;
                logWarning("contains error");
            }
        };

        auto countTest = [&] {
            auto zeroToTen = Range(0, 10).sequence();

            log("zeroToTen : %s", zeroToTen.toArray().toString().cStr());
            log("zeroToTen count : %d", zeroToTen.count().get());
            log("zeroToTen isEven count : %d", zeroToTen.count(Int::isEven).get());
            log("zeroToTen isOdd count : %d", zeroToTen.count(Int::isOdd).get());

            if (
                    zeroToTen.count() != 10 ||
                    zeroToTen.count(Int::isEven) != 5 ||
                    zeroToTen.count(Int::isOdd) != 5
            ) {
                ok = false;
                logWarning("count error");
            }
        };

        auto distinctTest = [&] {
            auto list = Array < char > {'a', 'A', 'b', 'B', 'A', 'a'}.sequence();

            log("list : %s", list.toArray().toString().cStr());
            log("list.distinct(): %s", list.distinct().toArray().toString().cStr());
            log("list.distinctBy(String::upperChar): %s", list.distinctBy(String::upperChar).toArray().toString().cStr());

            if ( list.distinct().toArray() != Array < char > { 'B', 'b', 'A', 'a' } ) {
                ok = false;
                logWarning("distinct error");
            }

            if ( list.distinctBy(String::upperChar).toArray() != Array < char > { 'b', 'a' } ) {
                ok = false;
                logWarning("distinct error");
            }

        };

        auto foldTest = [&]{
            auto numbers = Array < int > {1, 2, 3, 4, 5, 6}.sequence();
            auto strings = Array < String > {"a", "b", "c", "d" }.sequence();

            log ("numbers : %s", numbers.toArray().toString().cStr() );
            log ("strings : %s", strings.toArray().toString().cStr() );

            log ("numbers.fold : %d", numbers.fold(0, [](int s, int n){return s + n;}));
            log ("numbers.fold(start 5) : %d", numbers.fold(5, [](int s, int n){ return s + n; }));

            log ("strings.fold : %s", strings.fold(""_s, [](String const & s, String const & t){ return s + t; }).cStr());
            log ("strings.fold(start 'xyz' : %s", strings.fold("xyz"_s, [](String const & s, String const & t){ return s + t; }).cStr());

            if (
                    numbers.fold(0, [](int s, int n){return s + n;}) != 21 ||
                    numbers.fold(5, [](int s, int n){ return s + n; }) != 26 ||
                    strings.fold(""_s, [](String const & s, String const & t){ return s + t; }) != "abcd" ||
                    strings.fold("xyz"_s, [](String const & s, String const & t){ return s + t; }) != "xyzabcd"
            ) {
                logWarning("fold error");
                ok = false;
            }

        };

        auto foldIndexedTest = [&]{
            auto numbers = Array < int > {1, 2, 3, 4, 5, 6}.sequence();
            auto strings = Array < String > {"a", "b", "c", "d" }.sequence();

            log ("numbers : %s", numbers.toArray().toString().cStr() );
            log ("strings : %s", strings.toArray().toString().cStr() );

            log ("numbers.fold : %d", numbers.foldIndexed(0, [](Index i, int s, int n){if ( i % 2 == 0 ) return s + n; return s;}));
            log ("numbers.fold(start 5) : %d", numbers.foldIndexed(5, [](Index i, int s, int n){if ( i % 2 == 0 ) return s + n; return s;}));

            log ("strings.fold : %s", strings.foldIndexed(""_s, [](Index i, String const & s, String const & t){ if ( i % 2 == 1 ) return s + t; return s; }).cStr());
            log ("strings.fold(start 'xyz' : %s", strings.foldIndexed("xyz"_s, [](Index i, String const & s, String const & t){ if ( i % 2 == 1 ) return s + t; return s; }).cStr());

            if (
                    numbers.foldIndexed(0, [](Index i, int s, int n){if ( i % 2 == 0 ) return s + n; return s;}) != 9 ||
                    numbers.foldIndexed(5, [](Index i, int s, int n){if ( i % 2 == 0 ) return s + n; return s;}) != 14 ||
                    strings.foldIndexed(""_s, [](Index i, String const & s, String const & t){ if ( i % 2 == 1 ) return s + t; return s; }) != "bd" ||
                    strings.foldIndexed("xyz"_s, [](Index i, String const & s, String const & t){ if ( i % 2 == 1 ) return s + t; return s; }) != "xyzbd"
            ) {
                logWarning("fold error");
                ok = false;
            }

        };

        auto forEachTest = [&]{
            auto sum = 0;
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "sum : %d", sum );

            numbers.forEach([&](int number){ sum += number; });

            log ( "sum : %d", sum );

            if ( sum != 15 ) {
                logWarning("For Each error");
                ok = false;
            }
        };

        auto forEachIndexedTest = [&]{
            auto sum = 0;
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "sum : %d", sum );

            numbers.forEachIndexed([&](Index i, int number){ if ( i % 2 == 0 ) sum += number; });

            log ( "sum : %d", sum );

            if ( sum != 9 ) {
                logWarning("For Each error");
                ok = false;
            }
        };

        auto indexOfTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4 ,5 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("index of 4 : %d", numbers.indexOf(4));
            log("index of 6 : %d", numbers.indexOf(6));

            if ( numbers.indexOf(4) != 3 || numbers.indexOf(6) != -1 ) {
                logWarning("indexOf error");
                ok = false;
            }
        };

        auto indexOfFirstTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4 ,5 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("index of first even : %d", numbers.indexOfFirst(Int::isEven));
            log("index of first > 10 : %d", numbers.indexOfFirst([](int v){return v > 10;}));

            if ( numbers.indexOfFirst(Int::isEven) != 1 || numbers.indexOfFirst([](int v){return v> 10;}) != -1 ) {
                logWarning("indexOfFirst error");
                ok = false;
            }
        };

        auto indexOfLastTest = [&] {
            auto numbers = Array < int > { 1, 2, 3, 4 ,5 }.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("index of last even : %d", numbers.indexOfLast(Int::isEven));
            log("index of last > 10 : %d", numbers.indexOfLast([](int v){return v > 10;}));

            if ( numbers.indexOfLast(Int::isEven) != 3 || numbers.indexOfLast([](int v){return v> 10;}) != -1 ) {
                logWarning("indexOfLast error");
                ok = false;
            }
        };

        auto onEachTest = [&]{
            auto sum = 0;
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "sum : %d", sum );

            numbers.onEach([&](int number){ sum += number; }).also([]{});

            log ( "sum : %d", sum );

            if ( sum != 15 ) {
                logWarning("For Each error");
                ok = false;
            }
        };

        auto onEachIndexedTest = [&]{
            auto sum = 0;
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "sum : %d", sum );

            numbers.onEachIndexed([&](Index i, int number){ if ( i % 2 == 0 ) sum += number; }).also([]{});

            log ( "sum : %d", sum );

            if ( sum != 9 ) {
                logWarning("For Each error");
                ok = false;
            }
        };

        auto reduceTest = [&]{
            auto strings = Array<String>{"a", "b", "c", "d"}.sequence();

            log ( "strings : %s", strings.toArray().toString().cStr() );
            log ( "strings.reduce : %s", strings.reduce([](String const & s, String const & t){ return s + t; }).cStr());
            log ( "strings.reduceIndexed : %s", strings.reduceIndexed([](Index i, String const & s, String const & t){ return s + t + i; }).cStr());

            if (
                    strings.reduce([](String const & s, String const & t){ return s + t; }) != "abcd" ||
                    strings.reduceIndexed([](Index i, String const & s, String const & t){ return s + t + i; }) != "ab1c2d3"
            ) {
                logWarning("reduce error");
                ok = false;
            }

            ok = false;
            try {
                log("empty.reduce : %d", Array<int>{}.sequence().reduce([](int _, int _1) { return 0; }));
            } catch ( OutOfBoundsException const & e ) {
                log("Exception expected : %s", e.toString().cStr());
                ok = true;
            }

            ok = false;
            try {
                log("empty.reduce : %d", Array<int>{}.sequence().reduceIndexed([](Index i, int _, int _1) { return 0; }));
            } catch ( OutOfBoundsException const & e ) {
                log("Exception expected : %s", e.toString().cStr());
                ok = true;
            }
        };

        auto runningFoldTest = [&] {
            auto strings = Array < String > {"a", "b", "c", "d"}.sequence();

            log ("strings : %s", strings.toArray().toString().cStr());
            log ("strings.runningFold : %s", strings.runningFold("s"_s, [](String const & s, String const & t){ return s + t; }).toArray().toString().cStr());
            log ("strings.runningFoldIndexed : %s", strings.runningFoldIndexed("s"_s, [](Index i, String const & s, String const & t){ return s + t + i; }).toArray().toString().cStr());

            if (
                    strings.runningFold("s"_s, [](String const & s, String const & t){ return s + t; }).toArray() != Array < String > { "s", "sa", "sab", "sabc", "sabcd" } ||
                    strings.runningFoldIndexed("s"_s, [](Index i, String const & s, String const & t){ return s + t + i; }).toArray() != Array < String > { "s", "sa0", "sa0b1", "sa0b1c2", "sa0b1c2d3" } ||
                    Array < String > {}.sequence().runningFold("s"_s, [](String const &, String const &){ return "x"; }).toArray () != Array < String > { "s" }
            ) {
                logWarning("runningFold error");
                ok = false;
            }
        };

        auto runningReduceTest = [&] {
            auto strings = Array < String >{"a", "b", "c", "d"}.sequence();

            log ("strings : %s", strings.toArray().toString().cStr());
            log ("strings.runningReduce : %s", strings.runningReduce([](String const & s, String const & t){return s + t;}).toArray().toString().cStr());
            log ("strings.runningReduceIndexed : %s", strings.runningReduceIndexed([](Index i, String const & s, String const & t){ return s + t + i; }).toArray().toString().cStr());
            log ("emptyList.runningReduce : %s", Array <String> {}.sequence().runningReduce([](String const &, String const &){return "X"_s;}).toArray().toString().cStr());

            if (
                    strings.runningReduce([](String const & s, String const & t){return s + t;}).toArray() != Array < String > { "a", "ab", "abc", "abcd" } ||
                    strings.runningReduceIndexed([](Index i, String const & s, String const & t){ return s + t + i; }).toArray() != Array < String > { "a", "ab1", "ab1c2", "ab1c2d3" } ||
                    ! Array <String> {}.sequence().runningReduce([](String const &, String const &){return "X"_s;}).toArray().empty()
            ) {
                logWarning("runningReduce error");
                ok = false;
            }
        };

        auto shuffledTest = [&]{
            auto numbers = Array < int > {1, 2, 3, 4, 5}.sequence();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbers.shuffled : %s", numbers.shuffled().toArray().toString().cStr());
            log("numbers.shuffled : %s", numbers.shuffled().toArray().toString().cStr());
            log("numbers.shuffled : %s", numbers.shuffled().toArray().toString().cStr());
            log("numbers.shuffled : %s", numbers.shuffled().toArray().toString().cStr());
        };

        auto sortedTest = [&] {
            auto numbers = Array < int > { 2, 1, 5, 4, 3 }.sequence();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "numbers.sorted : %s", numbers.sorted().toArray().toString().cStr() );

            if ( numbers.sorted().zipWithNext().any([](Pair<int,int>const &p){return p.first() > p.second();}) ){
                logWarning("sorted error");
                ok = false;
            }
        };

        auto sortedByTest = [&] {
            auto list = Array < String > { "aaa", "cc", "bbbb" }.sequence();
            auto sorted = list.sortedBy ([](String const & s){return s.length();});

            log ( "list : %s", list.toArray().toString().cStr() );
            log ( "sorted : %s", sorted.toArray().toString().cStr() );

            if ( sorted.zipWithNext().any([](Pair <String,String> const & p){ return p.first().length() > p.second().length(); }) ) {
                logWarning("sortedBy error");
                ok = false;
            }
        };

        auto sortedByDescendingTest = [&] {
            auto list = Array < String > { "aaa", "cc", "bbbb" }.sequence();
            auto sorted = list.sortedByDescending ([](String const & s){return s.length();});

            log ( "list : %s", list.toArray().toString().cStr() );
            log ( "sorted : %s", sorted.toArray().toString().cStr() );

            if ( sorted.zipWithNext().any([](Pair <String,String> const & p){ return p.first().length() < p.second().length(); }) ) {
                logWarning("sortedByDescending error");
                ok = false;
            }
        };

        auto sortedDescendingTest = [&] {
            auto list = Array < int > { 5, 1, 2, 4, 3 }.sequence ();
            auto sorted = list.sorted([](int a, int b){return a > b;});

            log ( "list : %s", list.toArray().toString().cStr() );
            log ( "sortedDesc : %s", sorted.toArray().toString().cStr() );

            if ( sorted.zipWithNext().any([](Pair<int,int>const &p){return p.first() < p.second();}) ){
                logWarning("sortedDescending error");
                ok = false;
            }
        };


        allTest();
        anyTest();
        containsTest();
        countTest();
        distinctTest();
        foldTest ();
        foldIndexedTest ();
        forEachTest();
        forEachIndexedTest();
        indexOfTest();
        indexOfFirstTest();
        indexOfLastTest();

        onEachTest();
        onEachIndexedTest();

        reduceTest ();
        runningFoldTest();
        runningReduceTest();

        shuffledTest();

        sortedTest();
        sortedByTest();
        sortedByDescendingTest();
        sortedDescendingTest();
    });

    this->executeSubtest("Mapping Association Functionalities", [&]{
        auto associateTest = [&] {
            auto names = LinkedList<String>{"Grace Hopper", "Jacob Bernoulli", "Johann Bernoulli"}.sequence();
            log("byLastName : %s", names.associate([](String const &fullName) {
                return Pair{fullName.split(" ")[1], fullName.split(" ")[0]};
            }).toHashMap().toString().cStr());

            if (
                    names.associate([](String const &fullName) {
                        return Pair{fullName.split(" ")[1], fullName.split(" ")[0]};
                    }).toHashMap() !=
                    HashMap<String, String>{
                            {"Hopper",    "Grace"},
                            {"Bernoulli", "Johann"}
                    }
            ) {
                ok = false;
                logWarning(".associate error");
            }
        };

        auto associateByTest = [&] {
            class Person : public Object {
            public:
                String firstName;
                String lastName;

                Person() noexcept = default;
                __CDS_MaybeUnused Person(Person const &) noexcept = default;
                Person(String firstName, String lastName) noexcept : firstName(std::move(firstName)), lastName(std::move(lastName)) { }

                __CDS_NoDiscard auto toString () const noexcept -> String __CDS_cpplang_NestedInheritedOverride {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool __CDS_cpplang_NestedInheritedOverride {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array < Person > {
                Person(String("Grace"), String("Hopper")),
                Person(String("Jacob"), String("Bernoulli")),
                Person(String("Johann"), String("Bernoulli"))
            }.sequence();

            log("scientists : %s", scientists.toArray().toString().cStr());

            auto byLastName = scientists.associateBy ([](Person const & p){ return p.lastName; });

            log("byLastName : %s", byLastName.toHashMap().toString().cStr());

            if (
                    byLastName.toHashMap() !=
                    HashMap < String, Person > {
                            { "Hopper", Person("Grace", "Hopper") },
                            { "Bernoulli", Person("Johann", "Bernoulli") }
                    }
            ) {
                ok = false;
                logWarning(".associateBy error");
            }

            auto byLastNameWithFirst = scientists.associateBy (
                    [](Person const & p){ return p.lastName; },
                    [](Person const & p){ return p.firstName; }
            );

            log("byLastNameWithFirst : %s", byLastNameWithFirst.toHashMap().toString().cStr());

            if (
                    byLastNameWithFirst.toHashMap() !=
                    HashMap < String, String > {
                            { "Hopper", "Grace" }, {"Bernoulli", "Johann"}
                    }
            ) {
                ok = false;
                logWarning(".associateBy error");
            }
        };

        auto associateByToTest = [&]{
            class Person : public Object {
            public:
                String firstName;
                String lastName;

                Person() noexcept = default;
                __CDS_MaybeUnused Person(Person const &) noexcept = default;
                Person(String firstName, String lastName) : firstName(std::move(firstName)), lastName(std::move(lastName)) { }

                __CDS_NoDiscard auto toString () const noexcept -> String __CDS_cpplang_NestedInheritedOverride {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool __CDS_cpplang_NestedInheritedOverride {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array < Person > {
                Person ("Grace", "Hopper"),
                Person ( "Jacob", "Bernoulli" ),
                Person ( "Johann", "Bernoulli" )
            }.sequence();

            log("scientists : %s", scientists.toArray().toString().cStr());

            auto byLastName = HashMap < String, Person > ();
            log("byLastName.empty() : %s", byLastName.empty() ? "true" : "false");

            if ( ! byLastName.empty() ) {
                ok = false;
                logWarning("in associateByTo, map error");
            }

            scientists.associateByTo ( byLastName, []( Person const & p ){ return p.lastName; } );

            log("byLastName.empty() : %s, byLastName : %s", byLastName.empty() ? "true" : "false", byLastName.toString().cStr());

            if ( byLastName.empty() ||
                byLastName != HashMap < String, Person >{
                        {"Hopper", Person("Grace", "Hopper")},
                        {"Bernoulli", Person("Johann", "Bernoulli")}
                }
            ) {
                ok = false;
                logWarning("associateByTo error");
            }

            auto byLastNameWithFirst = HashMap < String, String >();

            log("byLastNameWithFirst.empty() : %s", byLastNameWithFirst.empty() ? "true" : "false");

            if ( ! byLastNameWithFirst.empty() ) {
                ok = false;
                logWarning("map error, associateByTo");
            }

            scientists.associateByTo (
                    byLastNameWithFirst,
                    [](Person const & p){ return p.lastName; },
                    [](Person const & p){ return p.firstName; }
            );

            log("byLastNameWithFirst.empty() : %s, contents : %s", byLastNameWithFirst.empty() ? "true" : "false", byLastNameWithFirst.toString().cStr());

            if ( byLastNameWithFirst.empty() ||
                byLastNameWithFirst !=
                HashMap < String, String > {
                        {"Hopper", "Grace"},
                        {"Bernoulli", "Johann"}
                }
            ) {
                ok = false;
                logWarning("associateByTo error");
            }
        };

        auto associateToTest = [&] {
            class Person : public Object {
            public:
                String firstName;
                String lastName;

                Person() noexcept = default;
                __CDS_MaybeUnused Person(Person const &) noexcept = default;
                Person(String firstName, String lastName) : firstName(std::move(firstName)), lastName(std::move(lastName)) { }

                __CDS_NoDiscard auto toString () const noexcept -> String __CDS_cpplang_NestedInheritedOverride {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool __CDS_cpplang_NestedInheritedOverride {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array < Person > { Person("Grace", "Hopper"), Person("Jacob", "Bernoulli"), Person("Johann", "Bernoulli")}
                    .sequence();

            log("scientists : %s", scientists.toArray().toString().cStr());

            auto byLastName = HashMap < String, String > ();
            log("byLastName.empty() : %s", byLastName.empty() ? "true" : "false");
            if ( ! byLastName.empty() ) {
                ok = false;
                logWarning("map error, from associateTo");
            }

            scientists.associateTo(byLastName, [](Person const & p){ return Pair { p.lastName, p.firstName }; });

            log("byLastName.empty() : %s, contents : %s", byLastName.empty() ? "true" : "false", byLastName.toString().cStr() );

            if ( byLastName.empty() ||
                byLastName != HashMap < String, String > {
                        {"Hopper", "Grace"},
                        {"Bernoulli", "Johann"}
                }
            ) {
                ok = false;
                logWarning("associateTo error");
            }
        };

        auto associateWithTest = [&]{
            auto words = Array<String> { "a", "abc", "ab", "def", "abcd" }.sequence();
            log("words : %s", words.toArray().toString().cStr());

            auto withLength = words.associateWith([](String const & s){return s.length();});
            log("withLength(seq) : %s", withLength.toString().cStr());
            log("withLength : %s", withLength.toHashMap().toString().cStr());
            log("withLength : %s", withLength.toHashMap().keys().toString().cStr());
            log("withLength : %s", withLength.toHashMap().values().toString().cStr());

            if ( withLength.toHashMap() != HashMap < String, Size > {
                    { "a", 1 },
                    {"ab", 2},
                    {"abc", 3},
                    {"def", 3},
                    {"abcd", 4}
            } ) {
                ok = false;
                logWarning("associateWith error");
            }
        };

        auto associateWithToTest = [&] {
            class Person : public Object {
            public:
                String firstName;
                String lastName;

                Person() noexcept = default;
                __CDS_MaybeUnused Person(Person const &) noexcept = default;
                Person(String firstName, String lastName) : firstName(std::move(firstName)), lastName(std::move(lastName)) { }

                __CDS_NoDiscard auto toString () const noexcept -> String __CDS_cpplang_NestedInheritedOverride {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool __CDS_cpplang_NestedInheritedOverride {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array < Person > {
                Person("Grace", "Hopper"), Person("Jacob", "Bernoulli"), Person("Jacob", "Bernoulli")
            }.sequence();

            auto withLengthOfNames = HashMap < Person, Size >();

            log("scientists : %s", scientists.toArray().toString().cStr());
            log("withLengthOfNames.empty() : %s", withLengthOfNames.empty() ? "true" : "false");

            if ( ! withLengthOfNames.empty() ) {
                ok = false;
                logWarning("map empty error, associateWithTo");
            }

            scientists.associateWithTo ( withLengthOfNames, [](Person const & p){return p.firstName.length() + p.lastName.length();} );

            log("withLengthOfNames.empty() : %s, contents : %s", withLengthOfNames.empty() ? "true" : "false", withLengthOfNames.toString().cStr());
            if ( withLengthOfNames.empty() ||
                withLengthOfNames != HashMap < Person, Size > {
                        { Person("Grace", "Hopper"), 11 },
                        { Person("Jacob", "Bernoulli"), 14 }
                }
            ) {
                ok = false;
                logWarning("associateWithTo error");
            }
        };

        auto groupByTest = [&] {
            auto words = Array < String > { "a", "abc", "ab", "def", "abcd" }.sequence();
            auto byLength = words.groupBy ( [](String const & s) { return s.length(); } );

            log ( "words : %s", words.toArray().toString().cStr() );
            log ( "byLength.keys() : %s", byLength.toHashMap().keys().toString().cStr() );
            log ( "byLength.values() : %s", byLength.toHashMap().values().toString().cStr() );

            auto nameToTeam = Array < Pair < String, String > > {
                { "Alice", "Marketing" },
                { "Bob", "Sales" },
                { "Carol", "Marketing" }
            }.sequence();

            auto namesByTeam = nameToTeam.groupBy (
                    [](Pair<String, String> const & p){ return p.second(); },
                    [](Pair<String, String> const & p){ return p.first(); }
            );

            log ( "nameToTeam : %s", nameToTeam.toArray().toString().cStr() );
            log ( "namesByTeam : %s", namesByTeam.toHashMap().toString().cStr() );
        };

        auto groupByToTest = [&]{
            auto words = Array < String > { "a", "abc", "ab", "def", "abcd" }.sequence();
            auto byLength = HashMap < Size, LinkedList < String > >();

            log ( "words : %s", words.toArray().toString().cStr() );
            log ( "byLength.keys() : %s", byLength.keys().toString().cStr() );
            log ( "byLength.values() : %s", byLength.values().toString().cStr() );

            words.groupByTo ( byLength, [](String const & s){ return s.length(); } );

            log ( "byLength.keys() : %s", byLength.keys().toString().cStr() );
            log ( "byLength.values() : %s", byLength.values().toString().cStr() );


            auto nameToTeam = Array < Pair < String, String > > {
                    { "Alice", "Marketing" },
                    { "Bob", "Sales" },
                    { "Carol", "Marketing" }
            }.sequence();

            auto namesByTeam = HashMap < String, LinkedList < String > >();

            log ( "nameToTeam : %s", nameToTeam.toArray().toString().cStr() );
            log ( "namesByTeam : %s", namesByTeam.toString().cStr() );

            nameToTeam.groupByTo (
                    namesByTeam,
                    [](Pair<String, String> const & p){ return p.second(); },
                    [](Pair<String, String> const & p){ return p.first(); }
            );

            log ( "namesByTeam : %s", namesByTeam.toString().cStr() );
        };

        associateTest();
        associateByTest();
        associateByToTest();
        associateToTest();
        associateWithTest();
        associateWithToTest();

        groupByTest();
        groupByToTest();
    });

    this->executeSubtest("Mathematical Utilities", [&]{
        auto averageTest = [&] {

            Array<Int> intObjArray = {1, 2, 3, 4, 5, 6};
            Array<int> intArray = {1, 2, 3, 4, 5, 6};

            Array<Long> longObjArray = {1, 2, 3, 4, 5, 6};
            Array<long long> longArray = {1, 2, 3, 4, 5, 6};

            Array<Float> floatObjArray = {1.0f, 2.1f, 3.2f, 4.3f, 5.4f};
            Array<float> floatArray = {1.0f, 2.1f, 3.2f, 4.3f, 5.4f};

            Array<Double> doubleObjArray = {1.0, 2.1, 3.2, 4.3, 5.4};
            Array<double> doubleArray = {1.0, 2.1, 3.2, 4.3, 5.4};

            log("intObjArray : %s", intObjArray.toString().cStr());
            log("intArray : %s", intArray.toString().cStr());
            log("longObjArray : %s", longObjArray.toString().cStr());
            log("longArray : %s", longArray.toString().cStr());
            log("floatObjArray : %s", floatObjArray.toString().cStr());
            log("floatArray : %s", floatArray.toString().cStr());
            log("doubleObjArray : %s", doubleObjArray.toString().cStr());
            log("doubleArray : %s", doubleArray.toString().cStr());

            double classicAvg;

            classicAvg = 0.0;
            for (auto e: intObjArray)
                classicAvg += e;
            classicAvg = classicAvg / intObjArray.size();

            log("intObjArray average : %lf", classicAvg);
            log("intObjArray.average() : %lf", intObjArray.sequence().average().get());

            if (classicAvg != intObjArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: intArray)
                classicAvg += e;
            classicAvg = classicAvg / intArray.size();

            log("intArray average : %lf", classicAvg);
            log("intArray.average() : %lf", intArray.sequence().average().get());

            if (classicAvg != intArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: longObjArray)
                classicAvg += e;
            classicAvg = classicAvg / longObjArray.size();

            log("longObjArray average : %lf", classicAvg);
            log("longObjArray.average() : %lf", longObjArray.sequence().average().get());

            if (classicAvg != longObjArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: longArray)
                classicAvg += e;
            classicAvg = classicAvg / longArray.size();

            log("longArray average : %lf", classicAvg);
            log("longArray.average() : %lf", longArray.sequence().average().get());

            if (classicAvg != longArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: floatObjArray)
                classicAvg += e.get();
            classicAvg = classicAvg / floatObjArray.size();

            log("floatObjArray average : %lf", classicAvg);
            log("floatObjArray.average() : %lf", floatObjArray.sequence().average().get());

            if (classicAvg != floatObjArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: floatArray)
                classicAvg += e;
            classicAvg = classicAvg / floatArray.size();

            log("floatArray average : %lf", classicAvg);
            log("floatArray.average() : %lf", floatArray.sequence().average().get());

            if (classicAvg != floatArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: doubleObjArray)
                classicAvg += e.get();
            classicAvg = classicAvg / doubleObjArray.size();

            log("doubleObjArray average : %lf", classicAvg);
            log("doubleObjArray.average() : %lf", doubleObjArray.sequence().average().get());

            if (classicAvg != doubleObjArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

            classicAvg = 0.0;
            for (auto e: doubleArray)
                classicAvg += e;
            classicAvg = classicAvg / doubleArray.size();

            log("doubleArray average : %lf", classicAvg);
            log("doubleArray.average() : %lf", doubleArray.sequence().average().get());

            if (classicAvg != doubleArray.sequence().average()) {
                ok = false;
                logError("Average Error");
            }

        };

        averageTest();
    });

    this->executeSubtest("Transformational Utilities", [&]{
        auto chunkedTest = [&] {
            auto words = "one two three four five six seven eight nine ten"_s.split(' ').sequence();
            log("words : %s", words.toArray().toString().cStr());

            auto chunks = words.chunked(3);
            log("chunks : %s", chunks.toArray().toString().cStr());

            if (chunks.toLinkedList() != LinkedList<Array<String> >{
                    {"one",   "two",   "three"},
                    {"four",  "five",  "six"},
                    {"seven", "eight", "nine"},
                    {"ten"}
            }) {
                ok = false;
                logWarning("chunked error");
            }

            auto codonTable = HashMap < String, String> {
                { "ATT", "Isoleucine" },
                { "CAA", "Glutamine" },
                { "CGC", "Arginine" },
                { "GGC", "Glycine" }
            };

            auto dnaFragment = "ATTCGCGGCCGCCAA"_s.sequence();
            auto proteins = dnaFragment.chunked(3, [&](Array<char> const &charList) {
                String s;
                for (auto e: charList) s += e;

                if (codonTable.containsKey(s))
                    return codonTable[s];
                return "Unknown Codon"_s;
            });

            log("proteins : %s", proteins.toArray().toString().cStr());
        };

        auto dropTest = [&]{
            auto chars = Range('a', 'z' + 1).sequence().map([](Index i)->char{return i;}).toArray().sequence();
            log("chars : %s", chars.toArray().toString().cStr());
            log("chars.drop(23) : %s", chars.drop(23).toArray().toString().cStr() );
            log("chars.dropLast(23) : %s", chars.dropLast(23).toArray().toString().cStr() );
            log("chars.dropWhile(it < 'x') : %s", chars.dropWhile([](char c){return c < 'x';}).toArray().toString().cStr() );
            log("chars.dropWhile(it > 'c') : %s", chars.dropLastWhile([](char c){return c > 'c';}).toArray().toString().cStr() );

            if (
                    chars.toArray() != Array < char > {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'} ||
                    chars.drop(23).toArray() != Array < char > { 'x', 'y', 'z' } ||
                    chars.dropLast(23).toArray() != Array < char > { 'a', 'b', 'c' } ||
                    chars.dropWhile([](char c){return c < 'x';}).toArray() != Array < char > { 'x', 'y', 'z' } ||
                    chars.dropLastWhile([](char c){return c > 'c';}).toArray() != Array < char > { 'a', 'b', 'c' }
            ) {
                ok = false;
                logWarning("drop error");
            }
        };

        auto filterTest = [&] {
            auto numbers = Array < Int > { 1, 2 ,3 ,4 , 5, 6, 7 }.sequence();
            auto evenNumbers = numbers.filter(Int::isEven);
            auto notMultipleOf3 = numbers.filterNot ( [](Int const & v){
                return v % 3 == 0;
            } );

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "evenNumbers : %s", evenNumbers.toArray().toString().cStr() );
            log ( "notMultipleOfThree : %s", notMultipleOf3.toArray().toString().cStr() );

            if (
                    numbers.toArray() != Array < Int > { 1, 2, 3, 4, 5, 6, 7 } ||
                    evenNumbers.toArray() != Array < Int > { 2, 4, 6 } ||
                    notMultipleOf3.toArray() != Array < Int > { 1, 2, 4, 5, 7 }
            ) {
                ok = false;
                logWarning("filter, filterNot error");
            }
        };

        auto filterIndexedTest = [&] {
            auto numbers = Array < Int > { 0, 1, 2, 5, 4, 8, 6 }.sequence();
            auto numbersOnSameIndexAsValue = numbers.filterIndexed ([](Index i, Int const & number){ return number == (int)i; });

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "numbersOnSameIndexAsValue : %s", numbersOnSameIndexAsValue.toArray().toString().cStr() );

            if (
                    numbers.toArray() != Array < Int > { 0, 1, 2, 5, 4, 8, 6 } ||
                    numbersOnSameIndexAsValue.toArray() != Array < Int > {0, 1, 2, 4, 6}
            ) {
                ok = false;
                logWarning("filterIndexed error");
            }
        };

        auto filterIndexedToTest = [&] {
            auto numbers = Array < Int > { 0, 1, 2, 3, 4 ,8, 6 }.sequence();
            auto numbersOnSameIndexAsValue = Array < Int > ();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("numbersOnSameIndexAsValue : %s", numbersOnSameIndexAsValue.toString().cStr());

            if ( ! numbersOnSameIndexAsValue.empty() ) {
                ok = false;
                logWarning("array error, from filterIndexedTo error");
            }

            numbers.filterIndexedTo (numbersOnSameIndexAsValue, [](Index i, Int const & e){ return (int)i == e; });

            log("numbersOnSameIndexAsValue : %s", numbersOnSameIndexAsValue.toString().cStr());

            if (
                    numbersOnSameIndexAsValue != Array < Int > { 0, 1, 2, 3, 4, 6 }
            ) {
                ok = false;
                logWarning("filterIndexedTo error");
            }
        };

        auto filterIsInstanceTest = [&]{
            class Animal : public Object {
            public:
                String name;

                Animal () noexcept = default;
                Animal (Animal const &) noexcept = default;
                Animal (String name) noexcept : name(std::move(name)) { }

                String toString () const noexcept override { return name; }
                bool equals(Object const & o) const noexcept override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return name == p->name;
                }
            };

            class Dog : public Animal {
            public:
                Dog() noexcept = default;
                Dog(Dog const &) noexcept = default;
                Dog(String name) noexcept : Animal(std::move(name)) { }
            };

            class Cat : public Animal {
            public:
                Cat() noexcept = default;
                Cat(Cat const &) noexcept = default;
                Cat(String name) noexcept : Animal(std::move(name)) { }
            };

            auto animals = Array < Animal * > { new Cat("Scratchy"), new Dog("Poochie") }.sequence();
            auto cats = animals.filterIsDerived < Cat * >();

            log("animals : %s", animals.toArray().toString().cStr());
            log("cats (animals.filter<Cat *>) : %s", cats.toArray().toString().cStr());

            if ( cats.toArray() != 1 || cats.toArray()[0]->name != "Scratchy" ) {
                ok = false;
                logWarning("filterIsDerived error");
            }

            animals.forEach([](auto * p){ delete p; });

            auto animalsSP = Array < SharedPointer < Animal > > { new Cat("Scratchy"), new Dog("Poochie") }.sequence();
            auto catsSP = animalsSP.filterIsDerived < Cat * > ();

            log ( "animals : %s", animalsSP.toArray().toString().cStr() );
            log ( "cats (animals.filter<Cat *>) : %s", catsSP.toArray().toString().cStr() );

            if ( cats.toArray() != Array < SharedPointer < Animal > > { new Cat("Scratchy") } ) {
                ok = false;
                logWarning("filterIsDerived error");
            }
        };

        auto filterIsInstanceToTest = [&] {
            class Animal : public Object {
            public:
                String name;

                Animal () noexcept = default;
                Animal (Animal const &) noexcept = default;
                Animal (String name) noexcept : name(std::move(name)) { }

                String toString () const noexcept override { return name; }
                bool equals(Object const & o) const noexcept override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return name == p->name;
                }
            };

            class Dog : public Animal {
            public:
                Dog() noexcept = default;
                Dog(Dog const &) noexcept = default;
                Dog(String name) noexcept : Animal(std::move(name)) { }
            };

            class Cat : public Animal {
            public:
                Cat() noexcept = default;
                Cat(Cat const &) noexcept = default;
                Cat(String name) noexcept : Animal(std::move(name)) { }
            };

            auto animals = Array < Animal * > { new Cat("Scratchy"), new Dog("Poochie") }.sequence();
            auto cats = Array < Cat * > ();

            log("animals : %s", animals.toArray().toString().cStr());
            log("cats : %s", cats.toString().cStr());

            if ( ! cats.empty() ) {
                ok = false;
                logWarning("array error, filterIsDerivedTo");
            }

            animals.filterIsDerivedTo < Cat * > ( cats );

            log ("cats : %s", cats.toString().cStr());

            if ( cats.empty() || cats[0]->name != "Scratchy" ) {
                ok = false;
                logWarning("filterIsDerivedTo Error");
            }

            animals.forEach([](auto * p){ delete p; });


            auto animalsSP = Array < SharedPointer < Animal > > { new Cat("Scratchy"), new Dog("Poochie") }.sequence();
            auto catsSP = Array < ForeignPointer < Cat > > ();

            log("animals : %s", animalsSP.toArray().toString().cStr());
            log("cats : %s", catsSP.toString().cStr());

            if ( ! catsSP.empty() ) {
                ok = false;
                logWarning("array error, filterIsDerivedTo");
            }

            animalsSP.filterIsDerivedTo < Cat * > ( catsSP );

            log ("cats : %s", catsSP.toString().cStr());

            if ( catsSP != Array < SharedPointer < Cat > > { new Cat("Scratchy") } ) {
                ok = false;
                logWarning("filterIsDerivedTo error");
            }
        };

        auto filterNotNullTest = [&] {
            auto numbers = Array < Int * > { new Int(1), new Int(2), nullptr, new Int(4) }.sequence();
            auto notNullNumbers = numbers.filterNotNull();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("notNullNumbers : %s", notNullNumbers.toArray().toString().cStr());

            if (
                    notNullNumbers.toArray().size() != 3
            ) {
                ok = false;
                logWarning("filterNotNull error");
            }

            numbers.forEach([](auto * p){ delete p; });

            auto numbersSP = Array < SharedPointer < Int > > { new Int(1), new Int(2), nullptr, new Int(4) }.sequence();
            auto notNullNumbersSP = numbers.filterNotNull();

            log("numbers : %s", numbersSP.toArray().toString().cStr());
            log("notNullNumbers : %s", notNullNumbersSP.toArray().toString().cStr());

            if (
                    notNullNumbersSP.toArray() != Array < SharedPointer < Int > > { new Int(1), new Int(2), new Int(4) }
            ) {
                ok = false;
                logWarning("filterNotNull error");
            }
        };

        auto filterNotNullToTest = [&] {
            auto numbers = Array < Int * > { new Int (1), new Int(2), nullptr, new Int(4) }.sequence();
            auto nonNullNumbers = Array < Int * >();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("nonNullNumbers : %s", nonNullNumbers.toString().cStr());

            if ( ! nonNullNumbers.empty() ) {
                ok = false;
                logWarning("array error, filterNotNullTo");
            }

            numbers.filterNotNullTo(nonNullNumbers);

            log("nonNullNumbers : %s", nonNullNumbers.toString().cStr());

            if ( nonNullNumbers.size() != 3 ) {
                ok = false;
                logWarning("filterNotNullTo error");
            }

            numbers.forEach([](auto * p){ delete p; });


            auto numbersSP = Array < SharedPointer < Int > > { new Int (1), new Int(2), nullptr, new Int(4) }.sequence();
            auto nonNullNumbersSP = Array < ForeignPointer < Int > >();

            log("numbers : %s", numbersSP.toArray().toString().cStr());
            log("nonNullNumbers : %s", nonNullNumbersSP.toString().cStr());

            if ( ! nonNullNumbersSP.empty() ) {
                ok = false;
                logWarning("array error, filterNotNullTo");
            }

            numbersSP.filterNotNullTo(nonNullNumbersSP);

            log("nonNullNumbers : %s", nonNullNumbersSP.toString().cStr());

            if ( nonNullNumbersSP != Array < SharedPointer < Int > > { new Int(1), new Int(2), new Int(4) } ) {
                ok = false;
                logWarning("filterNotNullTo error");
            }
        };

        auto filterNotToTest = [&] {
            auto numbers = Array < Int > { 1, 2, 3, 4, 5, 6 , 7 }.sequence();
            auto evenNumbers = Array < Int >();
            auto notMultipleOf3 = Array < Int >();

            log ( "numbers : %s", numbers.toArray().toString().cStr() );
            log ( "evenNumbers : %s", evenNumbers.toString().cStr() );
            log ( "notMultipleOf3 : %s", notMultipleOf3.toString().cStr() );

            if ( ! evenNumbers.empty () || ! notMultipleOf3.empty() ) {
                ok = false;
                logWarning("array error, filterNotTo Test");
            }

            numbers.filterTo ( evenNumbers, Int::isEven );
            numbers.filterNotTo ( notMultipleOf3, [](Int const & i){ return i % 3 == 0; } );

            log ( "evenNumbers : %s", evenNumbers.toString().cStr() );
            log ( "notMultipleOf3 : %s", notMultipleOf3.toString().cStr() );

            if (
                    evenNumbers != Array < Int > { 2, 4 ,6 } ||
                    notMultipleOf3 != Array < Int > { 1, 2, 4, 5, 7 }
            ) {
                ok = false;
                logWarning("filterTo, filterNotTo error");
            }
        };

        auto flatMapTest = [&] {
            auto numberStrings = Array < String > { "123", "45", "172", "14156" }.sequence();

            auto digits = numberStrings.flatMap ( [] ( String const & s ) { return s.sequence().toArray(); } );

            log("numberStrings : %s", numberStrings.toArray().toString().cStr());
            log("digits : %s", digits.toArray().toString().cStr());

            if ( digits.toArray() != String("1234517214156").sequence().toArray() ) {
                ok = false;
                logWarning("flatMap error");
            }
        };

        auto flatMapToTest = [&] {
            auto numberStrings = Array < String > { "123", "45", "172", "14156" }.sequence();

            auto digits = Array < char > ();

            numberStrings.flatMapTo ( digits, [] ( String const & s ) { return s.sequence().toArray(); } );

            log("numberStrings : %s", numberStrings.toArray().toString().cStr());
            log("digits : %s", digits.toString().cStr());

            if ( digits != String("1234517214156").sequence().toArray() ) {
                ok = false;
                logWarning("flatMap error");
            }
        };

        auto flatMapIndexedTest = [&] {
            auto data = Array < String > { "Abcd", "efgh", "Klmn" }.sequence();
            auto selected = data.map( [](String const & s){ return s.any(String::isUpperChar); } ).toArray();
            auto result = data.flatMapIndexed( [&](Index index, String const & s) {
                if ( selected[index] )
                    return s.sequence().toArray();
                return Array < char > ();
            } );

            log ( "data : %s", data.toArray().toString().cStr() );
            log ( "selected : %s", selected.toString().cStr() );
            log ( "result : %s", result.toArray().toString().cStr() );

            if ( result.toArray () != "AbcdKlmn"_s.sequence().toArray() ) {
                ok = false;
                logWarning("flatMapIndexed error");
            }
        };

        auto flatMapIndexedToTest = [&] {
            auto data = Array < String > { "Abcd", "efgh", "Klmn" }.sequence();
            auto selected = data.map( [](String const & s){ return s.any(String::isUpperChar); } ).toArray();
            auto result = Array < char > ();

            data.flatMapIndexedTo( result, [&](Index index, String const & s) {
                if ( selected[index] )
                    return s.sequence().toArray();
                return Array < char > ();
            } );

            log ( "data : %s", data.toArray().toString().cStr() );
            log ( "selected : %s", selected.toString().cStr() );
            log ( "result : %s", result.toString().cStr() );

            if ( result != "AbcdKlmn"_s.sequence().toArray() ) {
                ok = false;
                logWarning("flatMapIndexed error");
            }
        };

        auto flattenTest = [&]{
//            Array < Array < int > > {
//                    { 1, 2, 3 },
//                    { 4, 5, 6 },
//                    { 7, 8, 9 }
//            }.sequence().map( []( Array < int > const & a ){ return a.sequence(); } )

//            delayed for later release
        };

        auto mapTest = [&]{
            auto numbers = Array < int > { 1, 2, 3 }.sequence();
            auto squares = numbers.map([](int v){

                return v * v;
            });

//            std :: cout << (*squares.storedMappers.front().first())(1) << '\n';

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("squares : %s", squares.toArray().toString().cStr());

            if ( squares.toArray() != Array <int> {1, 4, 9} ) {
                logWarning("map error");
                ok = false;
            }
        };

        auto mapIndexedTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();
            auto squares = numbers.mapIndexed([](Index i, int v){if ( i % 2 == 0 ) return v * v; return v/2;});

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("squares : %s", squares.toArray().toString().cStr());

            if ( squares.toArray() != Array <int> {1, 1, 9, 2, 25} ) {
                logWarning("mapIndexed error");
                ok = false;
            }
        };

        auto mapToTest = [&]{
            auto numbers = Array < int > { 1, 2, 3 }.sequence();
            auto squares = Array < int > ();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("squares : %s", squares.toString().cStr());

            numbers.mapTo ( squares, [](int v){ return v * v; } );

            log("squares : %s", squares.toString().cStr());

            if ( squares != Array <int> {1, 4, 9} ) {
                logWarning("map error");
                ok = false;
            }
        };

        auto mapIndexedToTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5 }.sequence();
            auto squares = Array < int > ();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("squares : %s", squares.toString().cStr());

            numbers.mapIndexedTo(squares, [](Index i, int v){if ( i % 2 == 0 ) return v * v; return v/2;});

            log("squares : %s", squares.toString().cStr());

            if ( squares != Array <int> {1, 1, 9, 2, 25} ) {
                logWarning("mapIndexed error");
                ok = false;
            }
        };

        auto partitionTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }.sequence();
            auto partitions = numbers.partition([](int v){return v % 2 == 0;});

            log ("numbers : %s", numbers.toArray().toString().cStr());
            log ("even : %s", partitions.first().toString().cStr());
            log ("odd : %s", partitions.second().toString().cStr());

            if (
                    partitions.first().any(Int::isOdd) ||
                    partitions.second().any(Int::isEven)
            ) {
                logWarning("Partition error");
                ok = false;
            }
        };

        auto partitionIndexedTest = [&]{
            auto numbers = Array < int > { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }.sequence();
            auto partitions = numbers.partitionIndexed([](Index i, int v){return (i + v) % 2 == 0;});

            log ("numbers : %s", numbers.toArray().toString().cStr());
            log ("even : %s", partitions.first().toString().cStr());
            log ("odd : %s", partitions.second().toString().cStr());

            if (
                    ! partitions.first().empty() ||
                    partitions.second().empty()
            ) {
                logWarning("PartitionIndexed error");
                ok = false;
            }
        };

        auto takeTest = [&] {
            auto chars = Range('a', 'z' + 1).sequence().map([](Index i){return (char)i;});

            log ( "chars : %s", chars.toArray().toString().cStr() );
            log ( "chars.take(3) : %s", chars.take(3).toArray().toString().cStr() );
            log ( "chars.takeWhile(e<'f') : %s", chars.takeWhile([](char c){return c < 'f';}).toArray().toString().cStr() );
            log ( "chars.takeLast(2) : %s", chars.takeLast(2).toArray().toString().cStr() );
            log ( "chars.takeLastWhile(it > 'w') : %s", chars.takeLastWhile([](char c){return c > 'w';}).toArray().toString().cStr() );

            if (
                    chars.take(3).toArray() != Array <char> { 'a', 'b', 'c' } ||
                    chars.takeWhile([](char c){return c < 'f';}).toArray() != Array <char> {'a','b','c','d','e'} ||
                    chars.takeLast(2).toArray() != Array < char > {'y', 'z'} ||
                    chars.takeLastWhile([](char c){return c > 'w';}).toArray() != Array < char > {'x', 'y', 'z'}
            ) {
                logWarning("take error");
                ok = false;
            }
        };

        auto unzipTest = [&] {
            auto result = Range(0, 10).sequence().map([](Index i){return Pair<int, int>{(int)i, (int)i * 2};});
            auto unzipped = result.unzip();

            log("original : %s", result.toArray().toString().cStr());
            log("unzipped : %s", unzipped.toString().cStr());

            if (
                    unzipped.first() != LinkedList < int > { 0, 1, 2, 3, 4, 5 ,6 ,7 ,8, 9 } ||
                    unzipped.second() != LinkedList < int > { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 }
            ) {
                logWarning("unzip error");
                ok = false;
            }
        };

        auto windowedTest = [&] {
            auto numbers = Range(0, 15).sequence();

            auto windows = numbers.windowed(5, 1);
            auto moreSparseWindows = numbers.windowed(5, 3);
            auto fullWindows = numbers.take(10).windowed(5, 3);
            auto partialWindows = numbers.take(10).windowed(5, 3, true);

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("windows : %s", windows.toArray().toString().cStr());
            log("moreSparseWindows : %s", moreSparseWindows.toArray().toString().cStr());
            log("fullWindows : %s", fullWindows.toArray().toString().cStr());
            log("partialWindows : %s", partialWindows.toArray().toString().cStr());

            if (
                    windows.toArray() != Array < Array < int > > { { 0, 1, 2, 3, 4 }, { 1, 2, 3, 4, 5 }, { 2, 3, 4, 5, 6 }, { 3, 4, 5, 6, 7 }, { 4, 5, 6, 7, 8 }, { 5, 6, 7, 8, 9 }, { 6, 7, 8, 9, 10 }, { 7, 8, 9, 10, 11 }, { 8, 9, 10, 11, 12 }, { 9, 10, 11, 12, 13 }, { 10, 11, 12, 13, 14 } } ||
                    moreSparseWindows.toArray() != Array < Array < int > > { {0, 1, 2, 3, 4}, { 3, 4, 5, 6 ,7 }, { 6, 7, 8, 9, 10 }, {9, 10, 11, 12, 13} } ||
                    fullWindows.toArray() != Array < Array < int > > { {0, 1, 2, 3, 4}, {3, 4, 5, 6, 7} } ||
                    partialWindows.toArray() != Array < Array < int > > { { 0, 1, 2, 3, 4 }, {3, 4, 5, 6, 7}, {6, 7, 8, 9}, {9} }
            ) {
                logWarning("windowed error");
                ok = false;
            }

            auto dataPoints = Array < int > { 10, 15, 18, 25, 19, 21, 14, 8, 5 }.sequence();

            auto averaged = dataPoints.windowed( [](List < int > const & window){
                double sum = 0;
                window.forEach([&](int e){sum += e;});
                return sum / window.size();
            }, 4, 1, true );

            auto averagedNoPartials = dataPoints.windowed( [](List < int > const & window){
                double sum = 0;
                window.forEach([&](int e){sum += e;});
                return sum / window.size();
            }, 4, 1 );

            log("dataPoints : %s", dataPoints.toArray().toString().cStr());
            log("averaged : %s", averaged.toArray().toString().cStr());
            log("averagedNoPartials : %s", averagedNoPartials.toArray().toString().cStr());

            ///todo : check windowed!
        };

        auto withIndexTest = [&] {
            auto numbers = Array<int> {2, 4, 6, 8}.sequence();
            auto withIndices = numbers.indexed();

            log("numbers : %s", numbers.toArray().toString().cStr());
            log("indexed : %s", withIndices.toArray().toString().cStr());

            if ( withIndices.toArray() != Array<Pair<Index, int>> { {0, 2}, {1, 4}, {2, 6}, {3, 8} } ) {
                logWarning("indexed error");
                ok = false;
            }
        };

        auto zipTest = [&] {
            auto sequenceA = Range('a', 'z' + 1).sequence().map([](Index v){return (char)v;});
            auto sequenceB = Range(4).sequence().map([](Index v){ return (int)(v * 2 + 1); });

            auto zipped = sequenceA.zip(sequenceB);

            log("sequenceA : %s", sequenceA.toArray().toString().cStr());
            log("sequenceB : %s", sequenceB.toArray().toString().cStr());
            log("zipped : %s", zipped.toArray().toString().cStr());

            if ( zipped.toArray() != Array < Pair < char,int> > {{'a', 1}, {'b', 3}, {'c', 5}, {'d', 7}} ) {
                logWarning("zipped error");
                ok = false;
            }

            auto result = sequenceA.zip(sequenceB, [](char a, int b){ return String::f("%c/%d", a, b); });

            log("result : %s", result.toArray().toString().cStr());

            if ( result.toArray() != Array < String > { "a/1", "b/3", "c/5", "d/7" } ) {
                logWarning("zipped error");
                ok = false;
            }
        };

        auto zipWithNextTest = [&] {
            auto letters = Range('a', 'f' + 1).sequence().map([](Index v){return (char)v;});
            auto pairs = letters.zipWithNext();

            auto values = Array < int > { 1, 4, 9, 16, 25, 36 }.sequence();
            auto deltas = values.zipWithNext([](int a, int b){ return b - a; });

            log("letters : %s", letters.toArray().toString().cStr());
            log("pairs : %s", pairs.toArray().toString().cStr());
            log("values : %s", values.toArray().toString().cStr());
            log("deltas : %s", deltas.toArray().toString().cStr());

            if (
                    pairs.toArray() != Array<Pair<char, char>>{{'a', 'b'}, {'b','c'}, {'c','d'}, {'d','e'}, {'e','f'}} ||
                    deltas.toArray() != Array<int > { 3, 5, 7, 9, 11 }
            ) {
                logWarning("zipWithNext error");
                ok = false;
            }
        };


        chunkedTest();
        dropTest();
        filterTest();
        filterIndexedTest();
        filterIndexedToTest();
        filterIsInstanceTest();
        filterIsInstanceToTest();
        filterNotNullTest();
        filterNotNullToTest();
        filterNotToTest();
        flatMapTest();
        flatMapToTest();
        flatMapIndexedTest();
        flatMapIndexedToTest();
        flattenTest ();

        mapTest ();
        mapIndexedTest();
        mapToTest();
        mapIndexedToTest();

        partitionTest();
        partitionIndexedTest();

        takeTest();

        unzipTest();
        windowedTest();
        withIndexTest();
        zipTest();
        zipWithNextTest();
    });

    return ok;
}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif