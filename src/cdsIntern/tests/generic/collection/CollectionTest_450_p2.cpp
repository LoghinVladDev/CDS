#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"


auto CollectionTest::tests_00450_00599_p2 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableTreeMapRO", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        
        auto const c1 = cds::TreeMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::TreeMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c3 = cds::TreeMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        auto const c4 = cds::TreeMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c5 = cds::TreeMap <int, int> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::TreeMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::TreeMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const r1 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r2 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r3 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r4 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const r5 = cds::TreeMap <int, int> {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r6 = cds::TreeMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r7 = cds::TreeMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRO,
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );
        
        auto const r8 = cds::TreeMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r9 = cds::TreeMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r10 = cds::TreeMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r11 = cds::TreeMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r12 = cds::TreeMap <int, int> {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r13 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r14 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRNO,
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableTreeMapRA", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::TreeMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::TreeMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::TreeMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::TreeMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::TreeMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const ra1 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra2 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra3 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const ra4 = cds::TreeMap <int, int> ();
        auto const ra5 = cds::TreeMap <int, int> ();

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRAO,
                { &ra1, &ra2, &ra3, &ra4, &ra5 }
        );

        auto const ra6 = cds::TreeMap <int, int> ();
        auto const ra7 = cds::TreeMap <int, int>  {{6, 6} };
        auto const ra8 = cds::TreeMap <int, int>  {{3, 3}, {5, 5}, {7, 7} };
        auto const ra9 = cds::TreeMap <int, int>  {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra10 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRANO,
                { &ra6, &ra7, &ra8, &ra9, &ra10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableTreeMapRF", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::TreeMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::TreeMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::TreeMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::TreeMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::TreeMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const rf1 = cds::TreeMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf2 = cds::TreeMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf3 = cds::TreeMap <int, int>  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf4 = cds::TreeMap <int, int>  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf5 = cds::TreeMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFO,
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rf6 = cds::TreeMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf7 = cds::TreeMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf8 = cds::TreeMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf9 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf10 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFNO,
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableTreeMapRL", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::TreeMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::TreeMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::TreeMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::TreeMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::TreeMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const rl1 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl2 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl3 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        auto const rl4 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl5 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLO,
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const rl6 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl7 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl8 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl9 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rl10 = cds::TreeMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLNO,
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c10 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c12 = {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const r15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r17 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r18 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r19 = {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r20 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r21 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRO,
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        std::initializer_list <MapEntry <int, int>> const r22 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r23 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r24 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r25 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r26 = {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r27 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r28 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRNO,
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const ra11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra12 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra13 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra14 = {};
        std::initializer_list <MapEntry <int, int>> const ra15 = {};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRAO,
                { &ra11, &ra12, &ra13, &ra14, &ra15 }
        );

        std::initializer_list <MapEntry <int, int>> const ra16 =  {};
        std::initializer_list <MapEntry <int, int>> const ra17 =  {{6, 6} };
        std::initializer_list <MapEntry <int, int>> const ra18 =  {{3, 3}, {5, 5}, {7, 7} };
        std::initializer_list <MapEntry <int, int>> const ra19 = {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra20 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRANO,
                { &ra16, &ra17, &ra18, &ra19, &ra20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const rf11 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf12 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf13 =  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf14 =  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf15 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFO,
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <MapEntry <int, int>> const rf16 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf17 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf18 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFNO,
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListTreeMap", [this, & allOk]{

        cds :: TreeMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const rl11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl12 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl13 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl14 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLO,
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <MapEntry <int, int>> const rl16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl17 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl18 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rl20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLNO,
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableLinkedHashMapRO", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        
        auto const c1 = cds::LinkedHashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::LinkedHashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c3 = cds::LinkedHashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        auto const c4 = cds::LinkedHashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c5 = cds::LinkedHashMap <int, int> {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::LinkedHashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::LinkedHashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const r1 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r2 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r3 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r4 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const r5 = cds::LinkedHashMap <int, int> {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r6 = cds::LinkedHashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r7 = cds::LinkedHashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRO,
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );
        
        auto const r8 = cds::LinkedHashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r9 = cds::LinkedHashMap <int, int> {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r10 = cds::LinkedHashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r11 = cds::LinkedHashMap <int, int> {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r12 = cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const r13 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const r14 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRNO,
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableLinkedHashMapRA", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::LinkedHashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::LinkedHashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::LinkedHashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::LinkedHashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::LinkedHashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const ra1 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra2 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra3 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        auto const ra4 = cds::LinkedHashMap <int, int> ();
        auto const ra5 = cds::LinkedHashMap <int, int> ();

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRAO,
                { &ra1, &ra2, &ra3, &ra4, &ra5 }
        );

        auto const ra6 = cds::LinkedHashMap <int, int> ();
        auto const ra7 = cds::LinkedHashMap <int, int>  {{6, 6} };
        auto const ra8 = cds::LinkedHashMap <int, int>  {{3, 3}, {5, 5}, {7, 7} };
        auto const ra9 = cds::LinkedHashMap <int, int>  {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const ra10 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRANO,
                { &ra6, &ra7, &ra8, &ra9, &ra10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableLinkedHashMapRF", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::LinkedHashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::LinkedHashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::LinkedHashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::LinkedHashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::LinkedHashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const rf1 = cds::LinkedHashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf2 = cds::LinkedHashMap <int, int>  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf3 = cds::LinkedHashMap <int, int>  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf4 = cds::LinkedHashMap <int, int>  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rf5 = cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFO,
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rf6 = cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf7 = cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf8 = cds::LinkedHashMap <int, int> {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf9 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rf10 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFNO,
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntIterableLinkedHashMapRL", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        auto const c1 = cds::LinkedHashMap <int, int> {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        auto const c2 = cds::LinkedHashMap <int, int> {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        auto const c4 = cds::LinkedHashMap <int, int> {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        auto const c6 = cds::LinkedHashMap <int, int> {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        auto const c7 = cds::LinkedHashMap <int, int> {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        auto const rl1 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl2 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        auto const rl3 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        auto const rl4 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl5 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLO,
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const rl6 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        auto const rl7 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl8 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        auto const rl9 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        auto const rl10 = cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLNO,
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c10 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {1235, 1235}, {9534, 9534}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c12 = {{2, 2}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const r15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r17 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r18 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r19 = {{1, 1}, {4, 4}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r20 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r21 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRO,
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        std::initializer_list <MapEntry <int, int>> const r22 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r23 = {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r24 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r25 = {{3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r26 = {{2, 2}, {3, 3}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r27 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const r28 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeNotOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRNO,
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const ra11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra12 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra13 = {{1, 1}, {2, 2}, {4, 4}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra14 = {};
        std::initializer_list <MapEntry <int, int>> const ra15 = {};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRAO,
                { &ra11, &ra12, &ra13, &ra14, &ra15 }
        );

        std::initializer_list <MapEntry <int, int>> const ra16 =  {};
        std::initializer_list <MapEntry <int, int>> const ra17 =  {{6, 6} };
        std::initializer_list <MapEntry <int, int>> const ra18 =  {{3, 3}, {5, 5}, {7, 7} };
        std::initializer_list <MapEntry <int, int>> const ra19 = {{1, 1} ,{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const ra20 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeAllNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRANO,
                { &ra16, &ra17, &ra18, &ra19, &ra20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const rf11 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf12 =  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf13 =  {{1, 1}, {2, 2}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf14 =  {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rf15 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list <MapEntry <int, int>>, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFO,
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <MapEntry <int, int>> const rf16 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf17 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf18 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rf20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFNO,
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedListLinkedHashMap", [this, & allOk]{

        cds :: LinkedHashMap < int, int > const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        std::initializer_list <MapEntry <int, int>> const c8  = {{10, 10}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c9  = {{16, 16}, {6, 6}, {11, 11}, {12, 12}, {13, 13}};
        std::initializer_list <MapEntry <int, int>> const c11 = {{20, 20}, {123, 123}, {5, 5}, {1230, 1230}, {435, 435}, {3, 3}, {7, 7}, {1235, 1235}, {9534, 9534}, {1245, 1245}};
        std::initializer_list <MapEntry <int, int>> const c13 = {{9, 9}, {2, 2}, {5, 5}, {1, 1} , {4, 4}, {3, 3}, {7, 7}, {8, 8}, {6, 6} };
        std::initializer_list <MapEntry <int, int>> const c14 = {{91245, 91245}, {9, 9}, {2, 2}, {5532, 5532}, {5, 5}, {1, 1}, {4, 4}, {647, 647}, {1324, 1324}, {3, 3}, {7, 7}, {45, 45}, {234, 234}, {2365, 2365}, {2436, 2436}, {56, 56}, {8, 8}, {6, 6} };

        std::initializer_list <MapEntry <int, int>> const rl11 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl12 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl13 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {8, 8}, {9, 9} };
        std::initializer_list <MapEntry <int, int>> const rl14 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl15 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLO,
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <MapEntry <int, int>> const rl16 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8} };
        std::initializer_list <MapEntry <int, int>> const rl17 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl18 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
        std::initializer_list <MapEntry <int, int>> const rl19 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
        std::initializer_list <MapEntry <int, int>> const rl20 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < MapEntry <int, int> >, decltype (underTest), MapEntry <int, int> > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < MapEntry <int, int> > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLNO,
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );

    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayIterableRO", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <String> (10, 11, 12, 13);
        auto const c2 = make_a <String> (16, 6, 11, 12, 13);
        auto const c3 = make_a <String> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_a <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_a <String> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_a <String> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_a <String> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_a <String> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_a <String> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRO,
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        auto const r8 = make_a <String>  (4, 5, 6, 7, 8, 9 );
        auto const r9 = make_a <String>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_a <String> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_a <String> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_a <String> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRNO,
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayIterableRA", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <String> (10, 11, 12, 13);
        auto const c2 = make_a <String> (16, 6, 11, 12, 13);
        auto const c4 = make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const ra1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const ra3 = make_a <String> (1, 2, 4, 6, 8, 9 );
        auto const ra4 = make_a <String> ();
        auto const ra5 = make_a <String> ();

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRAO,
                { &ra1, &ra2, &ra3, &ra4, &ra5 }
        );

        auto const ra6 = make_a <String> ();
        auto const ra7 = make_a <String> (6 );
        auto const ra8 = make_a <String> (3, 5, 7 );
        auto const ra9 = make_a <String> (1 ,2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra10 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRANO,
                { &ra6, &ra7, &ra8, &ra9, &ra10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayIterableRF", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <String> (10, 11, 12, 13);
        auto const c2 = make_a <String> (16, 6, 11, 12, 13);
        auto const c4 = make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rf1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_a <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFO,
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rf6 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_a <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFNO,
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayIterableRL", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_a <String> (10, 11, 12, 13);
        auto const c2 = make_a <String> (16, 6, 11, 12, 13);
        auto const c4 = make_a <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_a <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_a <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rl1 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_a <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_a <String> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLO,
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const rl6 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_a <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLNO,
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayInitializerListRO", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRO,
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        std::initializer_list <String> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <String> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRNO,
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayInitializerListRA", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const ra11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const ra12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const ra13 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const ra14 = {};
        std::initializer_list <String> const ra15 = {};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRAO,
                { &ra11, &ra12, &ra13, &ra14, &ra15 }
        );

        std::initializer_list <String> const ra16 = {};
        std::initializer_list <String> const ra17 = {6 };
        std::initializer_list <String> const ra18 = {3, 5, 7 };
        std::initializer_list <String> const ra19 = {1 ,2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const ra20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRANO,
                { &ra16, &ra17, &ra18, &ra19, &ra20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayInitializerListRF", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFO,
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <String> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFNO,
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArrayInitializerListRL", [this, & allOk]{

        cds :: Array < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <String> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLO,
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <String> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLNO,
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListIterableRO", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_ll <String> (10, 11, 12, 13);
        auto const c2 = make_ll <String> (16, 6, 11, 12, 13);
        auto const c3 = make_ll <String> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_ll <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_ll <String> (1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_ll <String> (1, 2, 4, 6, 8, 9 );
        auto const r5 = make_ll <String> (1, 4, 6, 7, 8, 9 );
        auto const r6 = make_ll <String> (4, 5, 6, 7, 8, 9 );
        auto const r7 = make_ll <String> (4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRO,
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        auto const r8 = make_ll <String>  (4, 5, 6, 7, 8, 9 );
        auto const r9 = make_ll <String>  (4, 5, 6, 7, 8, 9 );
        auto const r10 = make_ll <String> (3, 5, 6, 7, 8, 9 );
        auto const r11 = make_ll <String> (3, 5, 6, 7, 8, 9 );
        auto const r12 = make_ll <String> (2, 3, 5, 7, 8, 9 );
        auto const r13 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRNO,
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListIterableRA", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_ll <String> (10, 11, 12, 13);
        auto const c2 = make_ll <String> (16, 6, 11, 12, 13);
        auto const c4 = make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const ra1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const ra3 = make_ll <String> (1, 2, 4, 6, 8, 9 );
        auto const ra4 = make_ll <String> ();
        auto const ra5 = make_ll <String> ();

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRAO,
                { &ra1, &ra2, &ra3, &ra4, &ra5 }
        );

        auto const ra6 = make_ll <String> ();
        auto const ra7 = make_ll <String> (6 );
        auto const ra8 = make_ll <String> (3, 5, 7 );
        auto const ra9 = make_ll <String> (1 ,2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra10 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRANO,
                { &ra6, &ra7, &ra8, &ra9, &ra10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListIterableRF", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_ll <String> (10, 11, 12, 13);
        auto const c2 = make_ll <String> (16, 6, 11, 12, 13);
        auto const c4 = make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rf1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_ll <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rf4 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf5 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFO,
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rf6 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf7 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf8 = make_ll <String> (2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf9 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFNO,
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListIterableRL", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_ll <String> (10, 11, 12, 13);
        auto const c2 = make_ll <String> (16, 6, 11, 12, 13);
        auto const c4 = make_ll <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_ll <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_ll <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rl1 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_ll <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_ll <String> (1, 2, 3, 4, 5, 6, 8, 9 );
        auto const rl4 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl5 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLO,
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const rl6 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8 );
        auto const rl7 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl8 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8);
        auto const rl9 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_ll <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLNO,
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListInitializerListRO", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const r15 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r16 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const r17 = {1, 2, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r18 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const r19 = {1, 4, 6, 7, 8, 9 };
        std::initializer_list <String> const r20 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r21 = {4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRO,
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        std::initializer_list <String> const r22 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r23 = {4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r24 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r25 = {3, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r26 = {2, 3, 5, 7, 8, 9 };
        std::initializer_list <String> const r27 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const r28 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRNO,
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListInitializerListRA", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const ra11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const ra12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const ra13 = {1, 2, 4, 6, 8, 9 };
        std::initializer_list <String> const ra14 = {};
        std::initializer_list <String> const ra15 = {};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRAO,
                { &ra11, &ra12, &ra13, &ra14, &ra15 }
        );

        std::initializer_list <String> const ra16 = {};
        std::initializer_list <String> const ra17 = {6 };
        std::initializer_list <String> const ra18 = {3, 5, 7 };
        std::initializer_list <String> const ra19 = {1 ,2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const ra20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRANO,
                { &ra16, &ra17, &ra18, &ra19, &ra20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListInitializerListRF", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rf11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rf13 = {1, 2, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf14 = {2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rf15 = {2, 3, 4, 5, 6, 7, 8, 9 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFO,
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <String> const rf16 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf17 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf18 = {2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rf20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFNO,
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedListInitializerListRL", [this, & allOk]{

        cds :: LinkedList < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rl11 = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::initializer_list <String> const rl12 = {1, 2, 3, 4, 5, 7, 8, 9 };
        std::initializer_list <String> const rl13 = {1, 2, 3, 4, 5, 6, 8, 9 };
        std::initializer_list <String> const rl14 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl15 = {1, 2, 3, 4, 5, 6, 7, 8 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLO,
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <String> const rl16 = {1, 2, 3, 4, 5, 6, 7, 8 };
        std::initializer_list <String> const rl17 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl18 = {1, 2, 3, 4, 5, 6, 7, 8};
        std::initializer_list <String> const rl19 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::initializer_list <String> const rl20 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLNO,
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetIterableRO", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_hs <String> (10, 11, 12, 13);
        auto const c2 = make_hs <String> (16, 6, 11, 12, 13);
        auto const c3 = make_hs <String> (20, 123, 5, 1230, 435, 3, 1235, 9534);
        auto const c4 = make_hs <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c5 = make_hs <String> (2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_hs <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_hs <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const r1 = make_hs <String> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r2 = make_hs <String> ( 1, 2, 3, 4, 5, 7, 8, 9 );
        auto const r3 = make_hs <String> ( 1, 2, 4, 6, 7, 8, 9 );
        auto const r4 = make_hs <String> ( 1, 2, 4, 6, 8, 9 );
        auto const r5 = make_hs <String> ( 1, 3, 4, 6, 8, 9 );
        auto const r6 = make_hs <String> ( 1, 2, 3, 7, 8, 9 );
        auto const r7 = make_hs <String> ( 1, 2, 3, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRO,
                { &r1, &r2, &r3, &r4, &r5, &r6, &r7 }
        );

        auto const r8 = make_hs <String> (7, 8, 9, 1, 2, 3 );
        auto const r9 = make_hs <String> (6, 8, 9, 1, 2, 3 );
        auto const r10 = make_hs <String> (5, 8, 9, 1, 2, 3 );
        auto const r11 = make_hs <String> (5, 7, 9, 1, 2, 3 );
        auto const r12 = make_hs <String> (5, 7, 9, 1, 2, 3 );
        auto const r13 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const r14 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c1, &c2, &c3, &c4, &c5, &c6, &c7 },
                statusSetRNO,
                { &r8, &r9, &r10, &r11, &r12, &r13, &r14 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetIterableRA", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_hs <String> (10, 11, 12, 13);
        auto const c2 = make_hs <String> (16, 6, 11, 12, 13);
        auto const c4 = make_hs <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_hs <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_hs <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const ra1 = make_hs <String> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra2 = make_hs <String> ( 1, 2, 3, 4, 5, 7, 8, 9 );
        auto const ra3 = make_hs <String> ( 1, 2, 4, 6, 8, 9 );
        auto const ra4 = make_hs <String> ();
        auto const ra5 = make_hs <String> ();

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRAO,
                { &ra1, &ra2, &ra3, &ra4, &ra5 }
        );

        auto const ra6 = make_hs <String> ();
        auto const ra7 = make_hs <String> ( 6 );
        auto const ra8 = make_hs <String> ( 3, 5, 7 );
        auto const ra9 = make_hs <String> ( 1 ,2, 3, 4, 5, 6, 7, 8, 9 );
        auto const ra10 = make_hs <String> ( 1, 2, 3, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveAllOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRANO,
                { &ra6, &ra7, &ra8, &ra9, &ra10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetIterableRF", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_hs <String> (10, 11, 12, 13);
        auto const c2 = make_hs <String> (16, 6, 11, 12, 13);
        auto const c4 = make_hs <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_hs <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_hs <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rf1 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rf2 = make_hs <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rf3 = make_hs <String> (1, 2, 3, 4, 6, 7, 8, 9 );
        auto const rf4 = make_hs <String> (1, 2, 3, 5, 6, 7, 8, 9 );
        auto const rf5 = make_hs <String> (1, 2, 3, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFO,
                { &rf1, &rf2, &rf3, &rf4, &rf5 }
        );

        auto const rf6 = make_hs <String> (5, 6, 7, 8, 9, 1, 2, 3);
        auto const rf7 = make_hs <String> (5, 6, 7, 8, 9, 1, 2, 3);
        auto const rf8 = make_hs <String> (5, 6, 7, 8, 9, 1, 2, 3);
        auto const rf9 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rf10 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRFNO,
                { &rf6, &rf7, &rf8, &rf9, &rf10 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetIterableRL", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        auto const c1 = make_hs <String> (10, 11, 12, 13);
        auto const c2 = make_hs <String> (16, 6, 11, 12, 13);
        auto const c4 = make_hs <String> (20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245);
        auto const c6 = make_hs <String> (9, 2, 5, 1, 4, 3, 7, 8, 6 );
        auto const c7 = make_hs <String> (91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 );

        auto const rl1 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9 );
        auto const rl2 = make_hs <String> (1, 2, 3, 4, 5, 7, 8, 9 );
        auto const rl3 = make_hs <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rl4 = make_hs <String> (1, 2, 4, 5, 6, 7, 8, 9 );
        auto const rl5 = make_hs <String> (1, 2, 4, 5, 6, 7, 8, 9 );

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLO,
                { &rl1, &rl2, &rl3, &rl4, &rl5 }
        );

        auto const rl6 = make_hs <String> (4, 5, 6, 7, 8, 9, 1, 2 );
        auto const rl7 = make_hs <String> (4, 5, 6, 7, 8, 9, 1, 2);
        auto const rl8 = make_hs <String> (4, 5, 6, 7, 8, 9, 1, 3);
        auto const rl9 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);
        auto const rl10 = make_hs <String> (1, 2, 3, 4, 5, 6, 7, 8, 9);

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < cds :: Iterable < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c1, &c2, &c4, &c6, &c7 },
                statusSetRLNO,
                { &rl6, &rl7, &rl8, &rl9, &rl10 }
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetInitializerListRO", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c10 = {20, 123, 5, 1230, 435, 3, 1235, 9534};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c12 = {2, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const r15 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r16 = {4, 5, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r17 = {4, 6, 7, 8, 9, 1, 2 };
        std::initializer_list <String> const r18 = {4, 6, 8, 9, 1, 2 };
        std::initializer_list <String> const r19 = {4, 6, 8, 9, 1, 3 };
        std::initializer_list <String> const r20 = {7, 8, 9, 1 ,2, 3 };
        std::initializer_list <String> const r21 = {7, 8, 9, 1, 2, 3 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeOf",
                        vOffsetRO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRO,
                { &r15, &r16, &r17, &r18, &r19, &r20, &r21 }
        );

        std::initializer_list <String> const r22 = {7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r23 = {6, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r24 = {5, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r25 = {5, 7, 9, 1, 2, 3 };
        std::initializer_list <String> const r26 = {5, 7, 9, 1, 2, 3 };
        std::initializer_list <String> const r27 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const r28 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };

        allOk = allOk && collectionTestGroupItemRemoveOf < std :: initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeNotOf",
                        vOffsetRNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeNotOf,
                limitR1,
                { &c8, &c9, &c10, &c11, &c12, &c13, &c14 },
                statusSetRNO,
                { &r22, &r23, &r24, &r25, &r26, &r27, &r28 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetInitializerListRA", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const ra11 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const ra12 = {4, 5, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const ra13 = {4, 6, 8, 9, 1, 2 };
        std::initializer_list <String> const ra14 = {};
        std::initializer_list <String> const ra15 = {};

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllOf",
                        vOffsetRAO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRAO,
                { &ra11, &ra12, &ra13, &ra14, &ra15 }
        );

        std::initializer_list <String> const ra16 = {};
        std::initializer_list <String> const ra17 = {6 };
        std::initializer_list <String> const ra18 = {5, 7, 3 };
        std::initializer_list <String> const ra19 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const ra20 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };

        allOk = allOk && collectionTestGroupItemRemoveAllOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeAllNotOf",
                        vOffsetRANO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeAllNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRANO,
                { &ra16, &ra17, &ra18, &ra19, &ra20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetInitializerListRF", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rf11 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rf12 = {4, 5, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rf13 = {4, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rf14 = {5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rf15 = {5, 6, 7, 8, 9, 1, 2, 3 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeFirstOf",
                        vOffsetRFO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFO,
                { &rf11, &rf12, &rf13, &rf14, &rf15 }
        );

        std::initializer_list <String> const rf16 = {5, 6, 7, 8, 9, 1, 2, 3};
        std::initializer_list <String> const rf17 = {5, 6, 7, 8, 9, 1, 2, 3};
        std::initializer_list <String> const rf18 = {5, 6, 7, 8, 9, 1, 2, 3};
        std::initializer_list <String> const rf19 = {4, 5, 6, 7, 8, 9, 1, 2, 3};
        std::initializer_list <String> const rf20 = {4, 5, 6, 7, 8, 9, 1, 2, 3};

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeFirstNotOf",
                        vOffsetRFNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeFirstNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRFNO,
                { &rf16, &rf17, &rf18, &rf19, &rf20 }
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSetInitializerListRL", [this, & allOk]{

        cds :: HashSet < String > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        std::initializer_list <String> const c8  = {10, 11, 12, 13};
        std::initializer_list <String> const c9  = {16, 6, 11, 12, 13};
        std::initializer_list <String> const c11 = {20, 123, 5, 1230, 435, 3, 7, 1235, 9534, 1245};
        std::initializer_list <String> const c13 = {9, 2, 5, 1, 4, 3, 7, 8, 6 };
        std::initializer_list <String> const c14 = {91245, 9, 2, 5532, 5, 1, 4, 647, 1324, 3, 7, 45, 234, 2365, 2436, 56, 8, 6 };

        std::initializer_list <String> const rl11 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rl12 = {4, 5, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rl13 = {4, 5, 6, 7, 8, 9, 1, 2 };
        std::initializer_list <String> const rl14 = {4, 5, 6, 7, 8, 9, 1, 2 };
        std::initializer_list <String> const rl15 = {4, 5, 6, 7, 8, 9, 1, 2 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "InitializerList",
                        "removeLastOf",
                        vOffsetRLO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLO,
                { &rl11, &rl12, &rl13, &rl14, &rl15 }
        );

        std::initializer_list <String> const rl16 = {4, 5, 6, 7, 8, 9, 1, 2 };
        std::initializer_list <String> const rl17 = {4, 5, 6, 7, 8, 9, 1, 2};
        std::initializer_list <String> const rl18 = {4, 5, 6, 7, 8, 9, 1, 3};
        std::initializer_list <String> const rl19 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };
        std::initializer_list <String> const rl20 = {4, 5, 6, 7, 8, 9, 1, 2, 3 };

        allOk = allOk && collectionTestGroupItemRemoveFirstLastOf < std::initializer_list < String >, decltype (underTest), String > (
                cds::makeTuple <Test const *, cds::String, cds::StringLiteral> (
                        this,
                        "MutableCollection",
                        "removeLastNotOf",
                        vOffsetRLNO
                ),
                underTest,
                & cds :: MutableCollection < String > :: removeLastNotOf,
                { &c8, &c9, &c11, &c13, &c14 },
                statusSetRLNO,
                { &rl16, &rl17, &rl18, &rl19, &rl20 }
        );
    });

    return allOk;
}
