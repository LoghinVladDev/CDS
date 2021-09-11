//
// Created by loghin on 04.06.2021.
//

#include "SequenceTest.h"

#include <CDS/Range>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/HashMap>
#include <CDS/JSON>
"JSON.hpp"
#include <CDS/OrderedSet>
#include <CDS/UnorderedSet>

#include <Sequence.hpp>

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

    return ok;
}