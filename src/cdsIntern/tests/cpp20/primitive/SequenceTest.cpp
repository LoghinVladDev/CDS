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
            log("chars.dropLastWhile(it < 'x') : %s", chars.dropWhile([](char c){return c < 'x';}).toArray().toString().cStr() );
        };

        chunkedTest();
        dropTest();
    });

    return ok;
}