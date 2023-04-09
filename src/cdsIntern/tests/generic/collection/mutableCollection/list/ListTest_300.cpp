#include "ListTest_common.hpp"

namespace {
    /* ListTestGroup-BoundaryInsertion-cpp-xx : LTG-00300-BI-cpp-xx. Tests LTC-00301-BI to LTC-00322-BI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename __ItType1,
            typename __ItType2,
            typename __ItType3,
            typename ... __Values
    > auto listTestGroupBoundaryInsertion (
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            __EnclosedType const & pbFirst,
            std :: initializer_list < __EnclosedType > const & equiv1,
            __EnclosedType const & pbSecond,
            std :: initializer_list < __EnclosedType > const & equiv2,
            __EnclosedType const & pbThird,
            std :: initializer_list < __EnclosedType > const & equiv3,
            __EnclosedType pbFourth,
            std :: initializer_list < __EnclosedType > const & equiv4,
            __EnclosedType pbFifth,
            std :: initializer_list < __EnclosedType > const & equiv5,
            __EnclosedType const & pfFirst,
            std :: initializer_list < __EnclosedType > const & equiv6,
            __EnclosedType const & pfSecond,
            std :: initializer_list < __EnclosedType > const & equiv7,
            __EnclosedType const & pfThird,
            std :: initializer_list < __EnclosedType > const & equiv8,
            __EnclosedType pfFourth,
            std :: initializer_list < __EnclosedType > const & equiv9,
            __EnclosedType pfFifth,
            std :: initializer_list < __EnclosedType > const & equiv10,
            std :: initializer_list < __EnclosedType > const & pbValues,
            std :: initializer_list < __EnclosedType > const & equiv11,
            std :: initializer_list < __EnclosedType > const & equiv12,
            std :: initializer_list < __EnclosedType > const & pfValues,
            std :: initializer_list < __EnclosedType > const & equiv13,
            std :: initializer_list < __EnclosedType > const & equiv14,
            __ItType1 const & b1, __ItType1 const & e1,
            std :: initializer_list < __EnclosedType > const & equiv15,
            std :: initializer_list < __EnclosedType > const & equiv16,
            __ItType2 const & b2, __ItType2 const & e2,
            std :: initializer_list < __EnclosedType > const & equiv17,
            std :: initializer_list < __EnclosedType > const & equiv18,
            __ItType3 const & b3, __ItType3 const & e3,
            std :: initializer_list < __EnclosedType > const & equiv19,
            std :: initializer_list < __EnclosedType > const & equiv20,
            std :: initializer_list < __EnclosedType > const & equiv21,
            std :: initializer_list < __EnclosedType > const & equiv22,
            __Values const & ... values
    ) noexcept -> bool {

        __TestedType < __EnclosedType > underTest = initValues;
        List < __EnclosedType > & lref = underTest;

        /* ListTestGroup-BoundaryInsertion-pushBackCopy1-cpp-xx : LTC-00301-IT-pushBackCopy1-cpp-xx */
        lref.pushBack ( pbFirst );
        if ( ! equals ( lref, equiv1 ) ) {
            pTestLib->logError("'LTC-00301-IT-pushBackCopy1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00301-IT-pushBackCopy1-" __CDS_cpplang_core_version_name "' OK");

        /* ListTestGroup-BoundaryInsertion-pushBackCopy2-cpp-xx : LTC-00302-IT-pushBackCopy2-cpp-xx */
        lref.pushBack ( pbSecond );
        if ( ! equals ( lref, equiv2 ) ) {
            pTestLib->logError("'LTC-00302-IT-pushBackCopy2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00302-IT-pushBackCopy2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackCopy3-cpp-xx : LTC-00303-IT-pushBackCopy3-cpp-xx */
        lref.pushBack ( pbThird );
        if ( ! equals ( lref, equiv3 ) ) {
            pTestLib->logError("'LTC-00303-IT-pushBackCopy3-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00303-IT-pushBackCopy3-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackMove1-cpp-xx : LTC-00304-IT-pushBackMove1-cpp-xx */
        lref.pushBack ( std :: move ( pbFourth ) );
        if ( ! equals ( lref, equiv4 ) ) {
            pTestLib->logError("'LTC-00304-IT-pushBackMove1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00304-IT-pushBackMove1-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackMove2-cpp-xx : LTC-00305-IT-pushBackMove2-cpp-xx */
        lref.pushBack ( std :: move ( pbFifth ) );
        if ( ! equals ( lref, equiv5 ) ) {
            pTestLib->logError("'LTC-00305-IT-pushBackMove2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00305-IT-pushBackMove2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontCopy1-cpp-xx : LTC-00306-IT-pushFrontCopy1-cpp-xx */
        lref.pushFront ( pfFirst );
        if ( ! equals ( lref, equiv6 ) ) {
            pTestLib->logError("'LTC-00306-IT-pushFrontCopy1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00306-IT-pushFrontCopy1-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontCopy2-cpp-xx : LTC-00307-IT-pushFrontCopy2-cpp-xx */
        lref.pushFront ( pfSecond );
        if ( ! equals ( lref, equiv7 ) ) {
            pTestLib->logError("'LTC-00307-IT-pushFrontCopy2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00307-IT-pushFrontCopy2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontCopy3-cpp-xx : LTC-00308-IT-pushFrontCopy3-cpp-xx */
        lref.pushFront ( pfThird );
        if ( ! equals ( lref, equiv8 ) ) {
            pTestLib->logError("'LTC-00308-IT-pushFrontCopy3-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00308-IT-pushFrontCopy3-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontMove1-cpp-xx : LTC-00309-IT-pushFrontMove1-cpp-xx */
        lref.pushFront ( std :: move ( pfFourth ) );
        if ( ! equals ( lref, equiv9 ) ) {
            pTestLib->logError("'LTC-00309-IT-pushFrontMove1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00309-IT-pushFrontMove1-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontMove2-cpp-xx : LTC-00310-IT-pushFrontMove2-cpp-xx */
        lref.pushFront ( std :: move ( pfFifth ) );
        if ( ! equals ( lref, equiv10 ) ) {
            pTestLib->logError("'LTC-00310-IT-pushFrontMove2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00310-IT-pushFrontMove2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackAllOfInitList-cpp-xx : LTC-00311-IT-pushBackAllOfInitList-cpp-xx */
        lref.pushBackAllOf ( pbValues );
        if ( ! equals ( lref, equiv11 ) ) {
            pTestLib->logError("'LTC-00311-IT-pushBackAllOfInitList-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00311-IT-pushBackAllOfInitList-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackAllOfColl-cpp-xx : LTC-00312-IT-pushBackAllOfColl-cpp-xx */
        __TestedType < __EnclosedType > v12 = pbValues;
        lref.pushBackAllOf ( v12 );
        if ( ! equals ( lref, equiv12 ) ) {
            pTestLib->logError("'LTC-00312-IT-pushBackAllOfColl-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00312-IT-pushBackAllOfColl-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontAllOfInitList-cpp-xx : LTC-00313-IT-pushFrontAllOfInitList-cpp-xx */
        lref.pushFrontAllOf ( pfValues );
        if ( ! equals ( lref, equiv13 ) ) {
            pTestLib->logError("'LTC-00313-IT-pushFrontAllOfInitList-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00313-IT-pushFrontAllOfInitList-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontAllOfColl-cpp-xx : LTC-00314-IT-pushFrontAllOfColl-cpp-xx */
        __TestedType < __EnclosedType > v14 = pfValues;
        lref.pushFrontAllOf ( v14 );
        if ( ! equals ( lref, equiv14 ) ) {
            pTestLib->logError("'LTC-00314-IT-pushFrontAllOfColl-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00314-IT-pushFrontAllOfColl-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackItRange1-cpp-xx : LTC-00315-IT-pushBackItRange1-cpp-xx */
        lref.pushBackAllOf ( b1, e1 );
        if ( ! equals ( lref, equiv15 ) ) {
            pTestLib->logError("'LTC-00315-IT-pushBackItRange1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00315-IT-pushBackItRange1-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontItRange1-cpp-xx : LTC-00316-IT-pushFrontItRange1-cpp-xx */
        lref.pushFrontAllOf ( b1, e1 );
        if ( ! equals ( lref, equiv16 ) ) {
            pTestLib->logError("'LTC-00316-IT-pushFrontItRange1-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00316-IT-pushFrontItRange1-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackItRange2-cpp-xx : LTC-00317-IT-pushBackItRange2-cpp-xx */
        lref.pushBackAllOf ( b2, e2 );
        if ( ! equals ( lref, equiv17 ) ) {
            pTestLib->logError("'LTC-00317-IT-pushBackItRange2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00317-IT-pushBackItRange2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontItRange2-cpp-xx : LTC-00318-IT-pushFrontItRange2-cpp-xx */
        lref.pushFrontAllOf ( b2, e2 );
        if ( ! equals ( lref, equiv18 ) ) {
            pTestLib->logError("'LTC-00318-IT-pushFrontItRange2-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00318-IT-pushFrontItRange2-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackItRange3-cpp-xx : LTC-00319-IT-pushBackItRange3-cpp-xx */
        lref.pushBackAllOf ( b3, e3 );
        if ( ! equals ( lref, equiv19 ) ) {
            pTestLib->logError("'LTC-00319-IT-pushBackItRange3-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00319-IT-pushBackItRange3-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontItRange3-cpp-xx : LTC-00320-IT-pushFrontItRange3-cpp-xx */
        lref.pushFrontAllOf ( b3, e3 );
        if ( ! equals ( lref, equiv20 ) ) {
            pTestLib->logError("'LTC-00320-IT-pushFrontItRange3-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00320-IT-pushFrontItRange3-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushBackValues-cpp-xx : LTC-00321-IT-pushBackValues-cpp-xx */
        lref.pushBackAll ( values ... );
        if ( ! equals ( lref, equiv21 ) ) {
            pTestLib->logError("'LTC-00321-IT-pushBackValues-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00321-IT-pushBackValues-" __CDS_cpplang_core_version_name "' OK");


        /* ListTestGroup-BoundaryInsertion-pushFrontValues-cpp-xx : LTC-00322-IT-pushFrontValues-cpp-xx */
        lref.pushFrontAll ( values ... );
        if ( ! equals ( lref, equiv22 ) ) {
            pTestLib->logError("'LTC-00322-IT-pushFrontValues-" __CDS_cpplang_core_version_name "' failed");
            return false;
        }
        pTestLib->logOK("'LTC-00322-IT-pushFrontValues-" __CDS_cpplang_core_version_name "' OK");

        return true;
    }
}

auto ListTest::tests_00300_00399 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );

        /* ListTestGroup-BoundaryInsertion-emplaceFront-cpp-xx : LTC-00323-IT-emplaceFront-cpp-xx */
        Array < String > t;
        List < String > & lref = t;

        lref.emplaceFront ( 5, 'c' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc"} ) ) {
            this->logError("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' OK");

        /* ListTestGroup-BoundaryInsertion-emplaceBack-cpp-xx : LTC-00324-IT-emplaceBack-cpp-xx */

        lref.emplaceBack ( 6, 'd' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc", "dddddd"} ) ) {
            this->logError("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' OK");
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        auto range1 = Array < int > { 1, 2, 3, 4, 5 };
        auto range2 = cds :: Range (5, 10);
        auto range3 = std :: vector < int > { 20, 21, 23, 24 };

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                6, { 1, 2, 3, 4, 5, 6 },
                7, { 1, 2, 3, 4, 5, 6, 7 },
                8, { 1, 2, 3, 4, 5, 6, 7, 8 },
                9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
                { 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 }, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                { 1, 2, 3 }, { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }, { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
                range1.begin(), range1.end(),
                { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
                range2.begin(), range2.end(),
                { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
                range3.begin(), range3.end(),
                { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },

                { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
                { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
                9, 8, 7, 6, 5
        );

        /* ListTestGroup-BoundaryInsertion-emplaceFront-cpp-xx : LTC-00323-IT-emplaceFront-cpp-xx */
        LinkedList < String > t;
        List < String > & lref = t;

        lref.emplaceFront ( 5, 'c' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc"} ) ) {
            this->logError("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00323-IT-emplaceFront-" __CDS_cpplang_core_version_name "' OK");

        /* ListTestGroup-BoundaryInsertion-emplaceBack-cpp-xx : LTC-00324-IT-emplaceBack-cpp-xx */

        lref.emplaceBack ( 6, 'd' );
        if ( ! equals ( lref, std::initializer_list<String>{"ccccc", "dddddd"} ) ) {
            this->logError("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' failed");
            allOk = false;
        }
        this->logOK("'LTC-00324-IT-emplaceBack-" __CDS_cpplang_core_version_name "' OK");
    });

    return allOk;
}
