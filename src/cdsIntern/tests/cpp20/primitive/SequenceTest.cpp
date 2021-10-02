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

        allTest();
        anyTest();
    });

    this->executeSubtest("Mapping Functionalities", [&]{
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

        associateTest();
        associateByTest();
        associateByToTest();
    });

    return ok;
}