#include "CollectionTest.h"
#include "CollectionTest_common.hpp"


namespace {

    /* CollectionTestGroup-RandomInsertion-cpp-xx : CTG-00800-RI-cpp-xx. CTC-00801-RI to CTC-008xx-RI */
    template <
            typename __DerivedType,
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
            typename __FwdElementType1,
            typename __FwdElementType2,
            typename __FwdElementType3,
            typename __ItType1,
            typename __ItType2,
            typename __ItType3,
            typename ... __Pack
    > auto collectionTestGroupRandomInsertion (
            Test * pTestLib,
            __ElementType const & insertByCopy,
            __ElementType && insertByMove,
            __FwdElementType1 && insertByEmplace1,
            __FwdElementType2 && insertByEmplace2,
            __FwdElementType3 && insertByEmplace3,
            cds :: Collection < __ElementType > const & toInsertAll,
            std :: initializer_list < __ElementType > const & toInsertAllList,
            __ItType1 const & r1Begin, __ItType1 const & r1End,
            __ItType2 const & r2Begin, __ItType2 const & r2End,
            __ItType3 const & r3Begin, __ItType3 const & r3End,
            cds :: Collection < __ElementType > const & expectedInsertByCopy,
            cds :: Collection < __ElementType > const & expectedInsertByMove,
            cds :: Collection < __ElementType > const & expectedAfterAllInsertByEmplace,
            cds :: Collection < __ElementType > const & expectedAfterPackInsertion,
            cds :: Collection < __ElementType > const & expectedAfterInsertAll,
            cds :: Collection < __ElementType > const & expectedAfterInsertAllList,
            cds :: Collection < __ElementType > const & expectedAfterR1Insert,
            cds :: Collection < __ElementType > const & expectedAfterR2Insert,
            cds :: Collection < __ElementType > const & expectedAfterR3Insert,

            __Pack && ... insertedPack
    ) -> bool {

        /* CollectionTestCase-RandomInsertion-insertByCopy-cpp-xx : CTC-00801-RI-insertByCopy-cpp-xx */
        __DerivedType RI00801;
        cds :: Collection < __ElementType > & baseRI00801 = RI00801;

        baseRI00801.insert ( insertByCopy );
        if ( ! RI00801.equals ( expectedInsertByCopy ) ) {
            pTestLib->logError( "'CTC-00801-RI-insertByCopy-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00801-RI-insertByCopy-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByMove-cpp-xx : CTC-00802-RI-insertByMove-cpp-xx */
        __DerivedType RI00802;
        cds :: Collection < __ElementType > & baseRI00802 = RI00802;

        baseRI00802.insert ( std :: forward <__ElementType> ( insertByMove ) );
        if ( ! RI00802.equals ( expectedInsertByMove ) ) {
            pTestLib->logError( "'CTC-00802-RI-insertByMove-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00802-RI-insertByMove-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByEmplace-cpp-xx : CTC-00803-RI-insertByEmplace-cpp-xx */
        __DerivedType RI00803;
        cds :: Collection < __ElementType > & baseRI00803 = RI00803;

        baseRI00803.emplace ( std :: forward < __FwdElementType1 > ( insertByEmplace1 ) );
        baseRI00803.emplace ( std :: forward < __FwdElementType2 > ( insertByEmplace2 ) );
        baseRI00803.emplace ( std :: forward < __FwdElementType3 > ( insertByEmplace3 ) );
        if ( ! RI00803.equals ( expectedAfterAllInsertByEmplace ) ) {
            pTestLib->logError( "'CTC-00803-RI-insertByEmplace-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00803-RI-insertByEmplace-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByPack-cpp-xx : CTC-00804-RI-insertByPack-cpp-xx */
        __DerivedType RI00804;
        cds :: Collection < __ElementType > & baseRI00804 = RI00804;

        baseRI00804.insertAll ( std :: forward < __Pack > ( insertedPack ) ... );
        if ( ! RI00804.equals ( expectedAfterPackInsertion ) ) {
            pTestLib->logError( "'CTC-00804-RI-insertByPack-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00804-RI-insertByPack-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByInsertAllIterable-cpp-xx : CTC-00805-RI-insertByInsertAllIterable-cpp-xx */
        __DerivedType RI00805;
        cds :: Collection < __ElementType > & baseRI00805 = RI00805;

        baseRI00805.insertAllOf ( toInsertAll );
        if ( ! RI00805.equals ( expectedAfterInsertAll ) ) {
            pTestLib->logError( "'CTC-00805-RI-insertByInsertAllIterable-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00805-RI-insertByInsertAllIterable-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByInsertAllList-cpp-xx : CTC-00806-RI-insertByInsertAllList-cpp-xx */
        __DerivedType RI00806;
        cds :: Collection < __ElementType > & baseRI00806 = RI00806;

        baseRI00806.insertAllOf ( toInsertAllList );
        if ( ! RI00806.equals ( expectedAfterInsertAllList ) ) {
            pTestLib->logError( "'CTC-00806-RI-insertByInsertAllList-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00806-RI-insertByInsertAllList-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByRange1-cpp-xx : CTC-00807-RI-insertByRange1-cpp-xx */
        __DerivedType RI00807;
        cds :: Collection < __ElementType > & baseRI00807 = RI00807;

        baseRI00807.insertAllOf ( r1Begin, r1End );
        if ( ! RI00807.equals ( expectedAfterR1Insert ) ) {
            pTestLib->logError( "'CTC-00807-RI-insertByRange1-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00807-RI-insertByRange1-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByRange2-cpp-xx : CTC-00808-RI-insertByRange2-cpp-xx */
        __DerivedType RI00808;
        cds :: Collection < __ElementType > & baseRI00808 = RI00808;

        baseRI00808.insertAllOf ( r2Begin, r2End );
        if ( ! RI00808.equals ( expectedAfterR2Insert ) ) {
            pTestLib->logError( "'CTC-00808-RI-insertByRange2-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00808-RI-insertByRange2-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* CollectionTestCase-RandomInsertion-insertByRange3-cpp-xx : CTC-00809-RI-insertByRange3-cpp-xx */
        __DerivedType RI00809;
        cds :: Collection < __ElementType > & baseRI00809 = RI00809;

        baseRI00809.insertAllOf ( r3Begin, r3End );
        if ( ! RI00809.equals ( expectedAfterR3Insert ) ) {
            pTestLib->logError( "'CTC-00809-RI-insertByRange3-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'CTC-00809-RI-insertByRange3-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }

}

auto CollectionTest::tests_00800_00899 () noexcept -> bool {

    bool allOk = true;
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: Array < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a <int> (1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_a <int> (5),
                make_a <int> (8),
                make_a <int> (2, 3, 4),
                make_a <int> (100, 200, 300, 400),
                make_a <int> (1, 2, 3, 4, 5),
                make_a <int> (5, 6, 7, 8, 9),
                make_a <int> (10, 20, 30, 40),
                make_a <int> (10, 11, 12, 13, 14),
                make_a <int> (20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: LinkedList < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a <int> (1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_ll <int> (5),
                make_ll <int> (8),
                make_ll <int> (2, 3, 4),
                make_ll <int> (100, 200, 300, 400),
                make_ll <int> (1, 2, 3, 4, 5),
                make_ll <int> (5, 6, 7, 8, 9),
                make_ll <int> (10, 20, 30, 40),
                make_ll <int> (10, 11, 12, 13, 14),
                make_ll <int> (20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: HashSet < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a <int> (1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_hs <int> (5),
                make_hs <int> (8),
                make_hs <int> (2, 3, 4),
                make_hs <int> (100, 200, 300, 400),
                make_hs <int> (1, 2, 3, 4, 5),
                make_hs <int> (5, 6, 7, 8, 9),
                make_hs <int> (10, 20, 30, 40),
                make_hs <int> (10, 11, 12, 13, 14),
                make_hs <int> (20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: TreeSet < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a  <int> (1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_ts <int> (5),
                make_ts <int> (8),
                make_ts <int> (2, 3, 4),
                make_ts <int> (100, 200, 300, 400),
                make_ts <int> (1, 2, 3, 4, 5),
                make_ts <int> (5, 6, 7, 8, 9),
                make_ts <int> (10, 20, 30, 40),
                make_ts <int> (10, 11, 12, 13, 14),
                make_ts <int> (20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk] {

        int byCopy = 5;
        int byMove = 8;

        cds :: Array < int > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < int > range3Definer { 20, 21, 22, 23, 24, 25 };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: LinkedHashSet < int >,
                int
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, 3, 4,
                make_a <int> (1, 2, 3, 4, 5),
                { 5, 6, 7, 8, 9 },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_lhs <int> (5),
                make_lhs <int> (8),
                make_lhs <int> (2, 3, 4),
                make_lhs <int> (100, 200, 300, 400),
                make_lhs <int> (1, 2, 3, 4, 5),
                make_lhs <int> (5, 6, 7, 8, 9),
                make_lhs <int> (10, 20, 30, 40),
                make_lhs <int> (10, 11, 12, 13, 14),
                make_lhs <int> (20, 21, 22, 23, 24, 25),
                100, 200, 300, 400
        );
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        MapEntry < int, int > byCopy = {5, 87};
        MapEntry < int, int > byMove = {8, 16};

        cds :: Array < MapEntry < int, int > > range1Definer = { {10, 20}, {20, 40}, {30, 60}, {40, 80} };
        std :: array < MapEntry < int, int >, 3 > range2Definer { MapEntry < int, int > ( 5, 1 ), MapEntry < int, int > (6, 2), MapEntry < int, int > (7, 2) };
        std :: vector < MapEntry < int, int > > range3Definer { {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25} };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: HashMap < int, int >,
                MapEntry < int, int >
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                MapEntry < int, int > {2, 3}, MapEntry < int, int > {3, 2}, MapEntry < int, int > {4, 6},
                cds :: Array < MapEntry < int, int > > ( { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} } ),
                { {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18} },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                cds::HashMap <int, int> {{5, 87}},
                cds::HashMap <int, int> {{8, 16}},
                cds::HashMap <int, int> {{2, 3}, {3, 2}, {4, 6}},
                cds::HashMap <int, int> {{100, 10}, {200, 20}, {300, 30}, {400, 40}},
                cds::HashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
                cds::HashMap <int, int> {{5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18}},
                cds::HashMap <int, int> {{10, 20}, {20, 40}, {30, 60}, {40, 80}},
                cds::HashMap <int, int> {{5, 1}, {6,2 }, {7, 2}},
                cds::HashMap <int, int> {{20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}},
                MapEntry < int, int > {100, 10}, MapEntry < int, int > {200, 20}, MapEntry < int, int > {300, 30}, MapEntry < int, int > {400, 40}
        );

        /* CollectionTestCase-RandomInsertion-specialEmplace-cpp-xx : CTC-00810-RI-specialEmplace-cpp-xx */
        cds :: HashMap < int, int > hm00810;
        cds :: Collection < MapEntry < int, int > > & RI00810 = hm00810;

        RI00810.emplace ( 3, 5 );
        RI00810.emplace ( 4, 5 );

        if ( ! RI00810.equals ( cds :: HashMap < int, int > { { 3, 5 }, { 4, 5 } } ) ) {
            this->logError( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk] {

        MapEntry < int, int > byCopy = {5, 87};
        MapEntry < int, int > byMove = {8, 16};

        cds :: Array < MapEntry < int, int > > range1Definer = { {10, 20}, {20, 40}, {30, 60}, {40, 80} };
        std :: array < MapEntry < int, int >, 3 > range2Definer { MapEntry < int, int > ( 5, 1 ), MapEntry < int, int > (6, 2), MapEntry < int, int > (7, 2) };
        std :: vector < MapEntry < int, int > > range3Definer { {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25} };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: LinkedHashMap < int, int >,
                MapEntry < int, int >
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                MapEntry < int, int > {2, 3}, MapEntry < int, int > {3, 2}, MapEntry < int, int > {4, 6},
                cds :: Array < MapEntry < int, int > > ( { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} } ),
                { {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18} },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                cds::LinkedHashMap <int, int> {{5, 87}},
                cds::LinkedHashMap <int, int> {{8, 16}},
                cds::LinkedHashMap <int, int> {{2, 3}, {3, 2}, {4, 6}},
                cds::LinkedHashMap <int, int> {{100, 10}, {200, 20}, {300, 30}, {400, 40}},
                cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
                cds::LinkedHashMap <int, int> {{5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18}},
                cds::LinkedHashMap <int, int> {{10, 20}, {20, 40}, {30, 60}, {40, 80}},
                cds::LinkedHashMap <int, int> {{5, 1}, {6,2 }, {7, 2}},
                cds::LinkedHashMap <int, int> {{20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}},
                MapEntry < int, int > {100, 10}, MapEntry < int, int > {200, 20}, MapEntry < int, int > {300, 30}, MapEntry < int, int > {400, 40}
        );

        /* CollectionTestCase-RandomInsertion-specialEmplace-cpp-xx : CTC-00810-RI-specialEmplace-cpp-xx */
        cds :: LinkedHashMap < int, int > hm00810;
        cds :: Collection < MapEntry < int, int > > & RI00810 = hm00810;

        RI00810.emplace ( 3, 5 );
        RI00810.emplace ( 4, 5 );

        if ( ! RI00810.equals ( cds :: LinkedHashMap < int, int > { { 3, 5 }, { 4, 5 } } ) ) {
            this->logError( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk] {

        MapEntry < int, int > byCopy = {5, 87};
        MapEntry < int, int > byMove = {8, 16};

        cds :: Array < MapEntry < int, int > > range1Definer = { {10, 20}, {20, 40}, {30, 60}, {40, 80} };
        std :: array < MapEntry < int, int >, 3 > range2Definer { MapEntry < int, int > ( 5, 1 ), MapEntry < int, int > (6, 2), MapEntry < int, int > (7, 2) };
        std :: vector < MapEntry < int, int > > range3Definer { {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25} };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: TreeMap < int, int >,
                MapEntry < int, int >
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                MapEntry < int, int > {2, 3}, MapEntry < int, int > {3, 2}, MapEntry < int, int > {4, 6},
                cds :: Array < MapEntry < int, int > > ( { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} } ),
                { {5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18} },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                cds::LinkedHashMap <int, int> {{5, 87}},
                cds::LinkedHashMap <int, int> {{8, 16}},
                cds::LinkedHashMap <int, int> {{2, 3}, {3, 2}, {4, 6}},
                cds::LinkedHashMap <int, int> {{100, 10}, {200, 20}, {300, 30}, {400, 40}},
                cds::LinkedHashMap <int, int> {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
                cds::LinkedHashMap <int, int> {{5, 10}, {6, 12}, {7, 14}, {8, 16}, {9, 18}},
                cds::LinkedHashMap <int, int> {{10, 20}, {20, 40}, {30, 60}, {40, 80}},
                cds::LinkedHashMap <int, int> {{5, 1}, {6,2 }, {7, 2}},
                cds::LinkedHashMap <int, int> {{20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25}},
                MapEntry < int, int > {100, 10}, MapEntry < int, int > {200, 20}, MapEntry < int, int > {300, 30}, MapEntry < int, int > {400, 40}
        );

        /* CollectionTestCase-RandomInsertion-specialEmplace-cpp-xx : CTC-00810-RI-specialEmplace-cpp-xx */
        cds :: TreeMap < int, int > hm00810;
        cds :: Collection < MapEntry < int, int > > & RI00810 = hm00810;

        RI00810.emplace ( 3, 5 );
        RI00810.emplace ( 4, 5 );

        if ( ! RI00810.equals ( cds :: TreeMap < int, int > { { 3, 5 }, { 4, 5 } } ) ) {
            this->logError( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' failed" );
            allOk = false;
        } else {
            this->logOK ( "'CTC-00810-RI-specialEmplace-" __CDS_cpplang_core_version_name "' OK" );
        }
    });
    this->executeSubtest ( "CollectionTestGroup-RandomInsertion-" __CDS_cpplang_core_version_name " : CTG-00800-RI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        String byCopy = 5;
        String byMove = "Ana are mere";

        cds :: Array < String > range1Definer = { 10, 20, 30, 40 };
        cds :: Range range2Definer ( 10, 15 );
        std :: vector < std :: string > range3Definer { "w1", "s2", "s3", "w4", "s25", "t35" };

        allOk = allOk && collectionTestGroupRandomInsertion <
                cds :: Array < String >,
                String
        > (
                this,
                byCopy,
                std :: move ( byMove ),
                2, "Whoa", cds :: StringView ( "Test case" ),
                make_a <String> (1, 2, 3, 4, 5),
                { "w1", 6, "w2", 8, "W3" },
                range1Definer.begin(), range1Definer.end(),
                range2Definer.begin(), range2Definer.end(),
                range3Definer.begin(), range3Definer.end(),
                make_a <String> (5),
                make_a <String> ("Ana are mere"),
                make_a <String> ("2", "Whoa", "Test case"),
                make_a <String> ("100", "-300", "word", "word2"),
                make_a <String> (1, 2, 3, 4, 5),
                make_a <String> ("w1", 6, "w2", 8, "W3"),
                make_a <String> (10, 20, 30, 40),
                make_a <String> (10, 11, 12, 13, 14),
                make_a <String> ("w1", "s2", "s3", "w4", "s25", "t35"),
                100, -300, "word", "word2"
        );
    });

    return allOk;
}
