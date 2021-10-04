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

        elementAtTest();
        elementAtOrElseTest();
        elementAtOrNullTest ();

    });

    this->executeSubtest("Basic Functional Properties", [& ok, this]{
        auto allTest = [&] {

            auto zeroToTen = Range(0, 10).sequence();

            this->log("Zero To Ten.all(isEven) : %s", zeroToTen.all(Integer::isEven) ? "true" : "false");

            if (zeroToTen.all(Integer::isEven)) {
                ok = false;
                this->logWarning(".all Error");
            }

            auto evens = zeroToTen.map([](Index const &v) -> Index { return v * 2; });
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

        allTest();
        anyTest();
        containsTest();
        countTest();
        distinctTest();
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
                Person(String firstName, String lastName) : firstName(std::move(firstName)), lastName(std::move(lastName)) { }

                __CDS_NoDiscard auto toString () const noexcept -> String override {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array < Person > {
                Person("Grace", "Hopper"),
                Person("Jacob", "Bernoulli"),
                Person("Johann", "Bernoulli")
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

                __CDS_NoDiscard auto toString () const noexcept -> String override {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
                    if ( this == & o ) return true;
                    auto p = dynamic_cast < decltype ( this ) > ( & o );
                    if ( p == nullptr ) return false;

                    return this->firstName == p->firstName && this->lastName == p->lastName;
                }
            };

            auto scientists = Array {
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

                __CDS_NoDiscard auto toString () const noexcept -> String override {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
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

                __CDS_NoDiscard auto toString () const noexcept -> String override {
                    return this->firstName + " " + this->lastName;
                }

                __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool override {
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

        associateTest();
        associateByTest();
        associateByToTest();
        associateToTest();
        associateWithTest();
        associateWithToTest();
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
            auto notMultipleOf3 = numbers.filterNot ( [](Int const & v){ return v % 3 == 0; } );

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
    });

    return ok;
}