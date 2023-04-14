#include "CollectionTest.h"
#include "CollectionTest_100_common.hpp"
#include <initializer_list>

auto CollectionTest::tests_00100_00299_p1 () noexcept -> bool {
    
    bool allOk = true;

#ifdef _MSC_VER
#pragma message("You are testing this on MSVC. Some Functions will not be tested. While compatbility should be OK, I am not bothering to actually do these tests until microsoft gets their member function pointer acquisiton code to standard.")
#else
    
    Size const exOne = 1;
    Size const exTwo = 2;
    Size const exThree = 3;
    Size const exFour = 4;

    auto const tId1 = 101;
    auto const tId2 = 105;
    auto const tId3 = 109;
    auto const tId4 = 113;
    auto const tId5 = 118;
    auto const tId6 = 123;
    auto const tId7 = 128;
    auto const tId8 = 132;
    auto const tId9 = 136;

    std::initializer_list<int> const td1 = {1, 3, 5, 7, 9};
    std::initializer_list<int> const td2 = {1, 4, 5, 7, 9};
    std::initializer_list<int> const td3 = {1, 4, 5, 6, 8};
    std::initializer_list<int> const td4 = {2, 4, 6, 8, 10};
    std::initializer_list<int> const td5 = {1, 2, 3, 4, 5};

    std::initializer_list<MapEntry<int, int>> const td6 = {{1, 1}, {3, 3}, {5, 5}, {7, 7}, {9, 9}};
    std::initializer_list<MapEntry<int, int>> const td7 = {{1, 1}, {4, 4}, {5, 5}, {7, 7}, {9, 9}};
    std::initializer_list<MapEntry<int, int>> const td8 = {{1, 1}, {4, 4}, {5, 5}, {6, 6}, {8, 8}};
    std::initializer_list<MapEntry<int, int>> const td9 = {{2, 2}, {4, 4}, {6, 6}, {8, 8}, {10, 10}};
    std::initializer_list<MapEntry<int, int>> const td10 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    int const comparedToLbdCap = 3;

    auto const p1 = [](int const e) {return (e % 2) == 0;};
    auto const p2 = [](int const e) {return (e % 2) == 1;};
    auto const p3 = [](int const e) {return e < 3;};
    auto const p4 = [](int const e) {return e >= 2;};
    auto const p5 = [comparedToLbdCap] (int const e) {return e > comparedToLbdCap; };

    auto const p6 = [](MapEntry <int, int> const & e) {return (e.key () % 2) == 0;};
    auto const p7 = [](MapEntry <int, int> const & e) {return (e.key () % 2) == 1;};
    auto const p8 = [](MapEntry <int, int> const & e) {return e.key() < 3;};
    auto const p9 = [](MapEntry <int, int> const & e) {return e.key() >= 2;};
    auto const p10 = [comparedToLbdCap] (MapEntry <int, int> const & e) {return e.key() > comparedToLbdCap; };

    /* CollectionTestGroup-FunctionalStatements-cpp-xx : CTG-00100-FS-cpp-xx - Tests CTC-00101-FS to CTC-10139-FS - located directly below due to varability of these tests */
    /* IntArray */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntArray", [&] {
        allOk = allOk && allTest_100 <int, cds::Array <int>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* IntLinkedList */                 
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedList", [&] {
        allOk = allOk && allTest_100 <int, cds::LinkedList <int>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });
    
    /* IntHashSet */                    
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntHashSet", [&] {
        allOk = allOk && allTest_100 <int, cds::HashSet <int>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* IntTreeSet */                    
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntTreeSet", [&] {
        allOk = allOk && allTest_100 <int, cds::TreeSet <int>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* IntLinkedHashSet */
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [&] {
        allOk = allOk && allTest_100 <int, cds::LinkedHashSet <int>> (
                this,
                {td1, td2, td3, td4, td5},
                {p1, p2, p3, p4, p5},
                comparedToLbdCap
        );
    });

    /* IntToIntHashMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <int, int>, cds::HashMap <int, int>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

    /* IntToIntTreeMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <int, int>, cds::TreeMap <int, int>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

    /* IntToIntLinkedHashMap */               
    this->executeSubtest ( "CollectionTestGroup-FunctionalStatements-" __CDS_cpplang_core_version_name " : CTG-00100-FS-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [&] {
        allOk = allOk && allTest_100 <MapEntry <int, int>, cds::LinkedHashMap <int, int>> (
                this,
                {td6, td7, td8, td9, td10},
                {p6, p7, p8, p9, p10},
                comparedToLbdCap
        );
    });

#endif

    return allOk;
}
