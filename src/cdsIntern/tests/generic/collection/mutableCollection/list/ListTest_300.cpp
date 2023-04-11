#include "ListTest_common.hpp"

#include <CDS/Tuple>

namespace {

    using cds::Size;
    using cds::Array;
    using cds::Tuple;
    using cds::makeTuple;

    template <typename E>
    using STC = Tuple <E, Array <E>>;

    template <typename E>
    using MTC = Tuple <std::initializer_list <E> const *, Array <E>, Array <E>>;

    template <typename I, typename E>
    using ITC = Tuple <I, I, Array <E>, Array <E>>;

    template <typename E>
    using PTC = Tuple <Array <E>, Array <E>>;

    template <typename E, typename I1, typename I2, typename I3>
    using TData = Tuple <
            STC <E>, STC <E>, STC <E>, STC <E>, STC <E>, /* pb */
            STC <E>, STC <E>, STC <E>, STC <E>, STC <E>, /* pf */
            MTC <E>, MTC <E>,
            ITC <I1, E>,
            ITC <I2, E>,
            ITC <I3, E>,
            PTC <E>
    >;

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
            TData <__EnclosedType, __ItType1, __ItType2, __ItType3> const & tData,
            __Values const & ... values
    ) noexcept -> bool {

        auto const & pbFirst = tData.template get <0> ().template get <0> ();
        auto const & equiv1 = tData.template get <0> ().template get <1> ();
        auto const & pbSecond = tData.template get <1> ().template get <0> ();
        auto const & equiv2 = tData.template get <1> ().template get <1> ();
        auto const & pbThird = tData.template get <2> ().template get <0> ();
        auto const & equiv3 = tData.template get <2> ().template get <1> ();

        auto pbFourth = tData.template get <3> ().template get <0> ();
        auto const & equiv4 = tData.template get <3> ().template get <1> ();
        auto pbFifth = tData.template get <4> ().template get <0> ();
        auto const & equiv5 = tData.template get <4> ().template get <1> ();

        auto const & pfFirst = tData.template get <5> ().template get <0> ();
        auto const & equiv6 = tData.template get <5> ().template get <1> ();
        auto const & pfSecond = tData.template get <6> ().template get <0> ();
        auto const & equiv7 = tData.template get <6> ().template get <1> ();
        auto const & pfThird = tData.template get <7> ().template get <0> ();
        auto const & equiv8 = tData.template get <7> ().template get <1> ();

        auto pfFourth = tData.template get <8> ().template get <0> ();
        auto const & equiv9 = tData.template get <8> ().template get <1> ();
        auto pfFifth = tData.template get <9> ().template get <0> ();
        auto const & equiv10 = tData.template get <9> ().template get <1> ();


        auto const & pbValues = * tData.template get <10> ().template get <0> ();
        auto const & equiv11 = tData.template get <10> ().template get <1> ();
        auto const & equiv12 = tData.template get <10> ().template get <2> ();

        auto const & pfValues = * tData.template get <11> ().template get <0> ();
        auto const & equiv13 = tData.template get <11> ().template get <1> ();
        auto const & equiv14 = tData.template get <11> ().template get <2> ();

        auto const & b1 = tData.template get <12> ().template get <0> ();
        auto const & e1 = tData.template get <12> ().template get <1> ();
        auto const & equiv15 = tData.template get <12> ().template get <2> ();
        auto const & equiv16 = tData.template get <12> ().template get <3> ();

        auto const & b2 = tData.template get <13> ().template get <0> ();
        auto const & e2 = tData.template get <13> ().template get <1> ();
        auto const & equiv17 = tData.template get <13> ().template get <2> ();
        auto const & equiv18 = tData.template get <13> ().template get <3> ();

        auto const & b3 = tData.template get <14> ().template get <0> ();
        auto const & e3 = tData.template get <14> ().template get <1> ();
        auto const & equiv19 = tData.template get <14> ().template get <2> ();
        auto const & equiv20 = tData.template get <14> ().template get <3> ();

        auto const & equiv21 = tData.template get <15> ().template get<0> ();
        auto const & equiv22 = tData.template get <15> ().template get<1> ();


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

    auto const irange1 = Array < int > { 1, 2, 3, 4, 5 };
    auto const irange2 = cds :: Range (5, 10);
    auto const irange3 = std :: vector < int > { 20, 21, 23, 24 };

    auto const istc1 = makeTuple <int, Array <int>> (6, { 1, 2, 3, 4, 5, 6 });
    auto const istc2 = makeTuple <int, Array <int>> (7, { 1, 2, 3, 4, 5, 6, 7 });
    auto const istc3 = makeTuple <int, Array <int>> (8, { 1, 2, 3, 4, 5, 6, 7, 8 });
    auto const istc4 = makeTuple <int, Array <int>> (9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto const istc5 = makeTuple <int, Array <int>> (10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const istc6 = makeTuple <int, Array <int>> (0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const istc7 = makeTuple <int, Array <int>> (1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const istc8 = makeTuple <int, Array <int>> (2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const istc9 = makeTuple <int, Array <int>> (3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const istc10 = makeTuple <int, Array <int>> (4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

    std::initializer_list <int> const imtc1Val = { 1, 2, 3 };
    auto const imtc1 = makeTuple <std::initializer_list <int> const *, Array <int>, Array <int>> (
            & imtc1Val,
            { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 },
            { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }
    );

    std::initializer_list <int> const imtc2Val = { 1, 2, 3 };
    auto const imtc2 = makeTuple <std::initializer_list <int> const *, Array <int>, Array <int>> (
            & imtc2Val,
            { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
            { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }
    );

    auto const iitc1 = makeTuple <decltype (irange1.begin()), decltype (irange1.end()), Array <int>, Array <int>> (
            irange1.begin(), irange1.end(),
            { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
            { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 }
    );

    auto const iitc2 = makeTuple <decltype (irange2.begin()), decltype (irange2.end()), Array <int>, Array <int>> (
            irange2.begin(), irange2.end(),
            { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
            { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 }
    );

    auto const iitc3 = makeTuple <decltype (irange3.begin()), decltype (irange3.end()), Array <int>, Array <int>> (
            irange3.begin(), irange3.end(),
            { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
            { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 }
    );

    auto const iptc = makeTuple <Array <int>, Array <int>> (
            { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
            { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 }
    );

    auto const itd = makeTuple (
            istc1, istc2, istc3, istc4, istc5,
            istc6, istc7, istc8, istc9, istc10,
            imtc1, imtc2,
            iitc1, iitc2, iitc3,
            iptc
    );

    auto const srange1 = Array < String > { 1, 2, 3, 4, 5 };
    auto const srange2 = cds :: Range (5, 10);
    auto const srange3 = std :: vector < String > { 20, 21, 23, 24 };

    auto const sstc1 = makeTuple <String, Array <String>> (6, { 1, 2, 3, 4, 5, 6 });
    auto const sstc2 = makeTuple <String, Array <String>> (7, { 1, 2, 3, 4, 5, 6, 7 });
    auto const sstc3 = makeTuple <String, Array <String>> (8, { 1, 2, 3, 4, 5, 6, 7, 8 });
    auto const sstc4 = makeTuple <String, Array <String>> (9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto const sstc5 = makeTuple <String, Array <String>> (10, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const sstc6 = makeTuple <String, Array <String>> (0, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const sstc7 = makeTuple <String, Array <String>> (1, { 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const sstc8 = makeTuple <String, Array <String>> (2, { 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const sstc9 = makeTuple <String, Array <String>> (3, { 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    auto const sstc10 = makeTuple <String, Array <String>> (4, { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

    std::initializer_list <String> const smtc1Val = { 1, 2, 3 };
    auto const smtc1 = makeTuple <std::initializer_list <String> const *, Array <String>, Array <String>> (
            & smtc1Val,
            { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 },
            { 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }
    );

    std::initializer_list <String> const smtc2Val = { 1, 2, 3 };
    auto const smtc2 = makeTuple <std::initializer_list <String> const *, Array <String>, Array <String>> (
            & smtc2Val,
            { 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 },
            { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3 }
    );

    auto const sitc1 = makeTuple <decltype (srange1.begin()), decltype (srange1.end()), Array <String>, Array <String>> (
            srange1.begin(), srange1.end(),
            { 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 },
            { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5 }
    );

    auto const sitc2 = makeTuple <decltype (srange2.begin()), decltype (srange2.end()), Array <String>, Array <String>> (
            srange2.begin(), srange2.end(),
            { 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 },
            { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9 }
    );

    auto const sitc3 = makeTuple <decltype (srange3.begin()), decltype (srange3.end()), Array <String>, Array <String>> (
            srange3.begin(), srange3.end(),
            { 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 },
            { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 }
    );

    auto const sptc = makeTuple <Array <String>, Array <String>> (
            { 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24, 9, 8, 7, 6, 5 },
            { 9, 8, 7, 6, 5, 20, 21, 23, 24, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 1, 2, 3, 1, 2, 3, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 20, 21, 23, 24 }
    );

    auto const _std = makeTuple (
            sstc1, sstc2, sstc3, sstc4, sstc5,
            sstc6, sstc7, sstc8, sstc9, sstc10,
            smtc1, smtc2,
            sitc1, sitc2, sitc3,
            sptc
    );
}


auto ListTest::tests_00300_00399 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        std::initializer_list <int> const initValues = {1, 2, 3, 4, 5};

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                int
        > (
                this,
                initValues,
                itd,
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        std::initializer_list <int> const initValues = {1, 2, 3, 4, 5};

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                int
        > (
                this,
                initValues,
                itd,
                9, 8, 7, 6, 5
        );
    });
    this->executeSubtest ( "ListTestGroup-BoundaryInsertion-" __CDS_cpplang_core_version_name " : LTG-00300-BI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        std::initializer_list <String> const initValues = {1, 2, 3, 4, 5};

        allOk = allOk && listTestGroupBoundaryInsertion <
                Array,
                String
        > (
                this,
                initValues,
                _std,
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

        std::initializer_list <String> const initValues = {1, 2, 3, 4, 5};

        allOk = allOk && listTestGroupBoundaryInsertion <
                LinkedList,
                String
        > (
                this,
                initValues,
                _std,
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
