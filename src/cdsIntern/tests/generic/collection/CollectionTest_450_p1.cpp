#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"


auto CollectionTest::tests_00450_00599_p1 () noexcept -> bool {

    bool allOk = true;

    std::initializer_list<int> const iData = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::initializer_list<std::initializer_list<int>> const iDataGroups = {       
            {10, 11, 12, 13},
            {16, 6, 11, 12, 13},
            {20, 123, 5, 1230, 435, 3, 1235, 9534},
            {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
            {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245},
            {9, 2, 5, 1, 4, 3, 7, 8, 6 },
            {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 }
    };
    std::initializer_list<std::initializer_list<int>> const iResultGroups = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9 },
            {1, 2, 3, 4, 5, 7, 8, 9 },
            {1, 2, 4, 6, 7, 8, 9 },
            {1, 2, 4, 6, 8, 9 },
            {1, 4, 6, 7, 8, 9 },
            {4, 5, 6, 7, 8, 9 },
            {4, 5, 6, 7, 8, 9 },
            {4, 5, 6, 7, 8, 9 },
            {4, 5, 6, 7, 8, 9 },
            {3, 5, 6, 7, 8, 9 },
            {3, 5, 6, 7, 8, 9 },
            {2, 3, 5, 7, 8, 9 },
            {1, 2, 3, 4, 5, 6, 7, 8, 9 },
            {1, 2, 3, 4, 5, 6, 7, 8, 9 },

            {1, 2, 3, 4, 5, 6, 7, 8, 9 },
            {1, 2, 3, 4, 5, 7, 8, 9 },
            {1, 2, 4, 6, 8, 9 },
            {},
            {},
            {},
            { 6 },
            { 3, 5, 7 },
            { 1 ,2, 3, 4, 5, 6, 7, 8, 9 },
            { 1, 2, 3, 4, 5, 6, 7, 8, 9},

            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 7, 8, 9},
            {1, 2, 4, 5, 6, 7, 8, 9},
            {2, 3, 4, 5, 6, 7, 8, 9},
            {2, 3, 4, 5, 6, 7, 8, 9},
            {2, 3, 4, 5, 6, 7, 8, 9},
            {2, 3, 4, 5, 6, 7, 8, 9},
            {2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},

            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 2, 3, 4, 5, 6, 7, 8},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    std::initializer_list<cds::MapEntry <int, int>> const iiData = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
    std::initializer_list<std::initializer_list<cds::MapEntry <int, int>>> const iiDataGroups = {       
            {{10, 10}, {11, 11}, {12, 12}, {13, 13}},
            {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}},
            {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}},
            {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
            {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}},
            {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} },
            {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} }
    };
    std::initializer_list<std::initializer_list<cds::MapEntry <int, int>>> const iiResultGroups = {
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
            {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },

            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} },
            {},
            {},
            {},
            {{6, 6} },
            {{3, 3}, {5, 5}, {7, 7} },
            {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },

            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
            {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
            {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},

            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} },
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}},
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}},
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}
    };

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [&]{

        using E = int;
        using C = cds::Array <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [&]{

        using E = int;
        using C = cds::LinkedList <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntHashSet", [&]{

        using E = int;
        using C = cds::HashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntTreeSet", [&]{

        using E = int;
        using C = cds::TreeSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [&]{

        using E = int;
        using C = cds::LinkedHashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::HashMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::TreeMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::LinkedHashMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    return allOk;
}
