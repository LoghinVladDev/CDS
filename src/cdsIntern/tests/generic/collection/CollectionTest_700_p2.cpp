#include "CollectionTest.h"
#include "CollectionTest_700_common.hpp"

namespace {
    using cds::makeTuple;

    std::initializer_list <String> const sv1 = {-1, -4, -7, 20};
    std::initializer_list <String> const sv2 = {-9, -8, -7, -6, -5, 4, -3, -2, -1};
    std::initializer_list <String> const sv3 = {-9, -8, -7, -6, 5, 4, 3, -2, -1};
    std::initializer_list <String> const sv4 = {-9, -8, -7, 6, 5, 4, 3, 2, -1};
    std::initializer_list <String> const sv5 = {-9, 8, 7, 6, 5, -4, 3, 2, 1};
    std::initializer_list <String> const sv6 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::initializer_list <String> const sv7 = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20};

    std::initializer_list <std::initializer_list <String> const *> const svList = {& sv1, & sv2, & sv3, & sv4, & sv5, & sv6, & sv7};

    std::initializer_list <MapEntry <String, String>> const ssv1 = {{-1, -1}, {-4, -4}, {-7, -7}, {20, 20}};
    std::initializer_list <MapEntry <String, String>> const ssv2 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1}};
    std::initializer_list <MapEntry <String, String>> const ssv3 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1}};
    std::initializer_list <MapEntry <String, String>> const ssv4 = {{-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1}};
    std::initializer_list <MapEntry <String, String>> const ssv5 = {{-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1}};
    std::initializer_list <MapEntry <String, String>> const ssv6 = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    std::initializer_list <MapEntry <String, String>> const ssv7 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
            {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}};

    std::initializer_list <std::initializer_list <MapEntry <String, String>> const *> const ssvList = {& ssv1, & ssv2, & ssv3, & ssv4, & ssv5, & ssv6, & ssv7};

    Size const iLimit = 5U;

    auto const sfo = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (3U, {3, 4, 5}),
            makeTuple <Size, Array <String>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <String>> (5U, {1, 2, 3, 5, 6}),
            makeTuple <Size, Array <String>> (5U, {1, 2, 3, 4, 5}),
            makeTuple <Size, Array <String>> (5U, {1, 2, 3, 4, 5})
    );

    auto const sffo = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 2),
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (true, 1)
    );

    auto const sflo = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 6),
            makeTuple <bool, String> (true, 9),
            makeTuple <bool, String> (true, 9)
    );

    auto const sfao = makeTuple (
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <String>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <String>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9})
    );

    auto const sfno = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (5U, {1, 2, 3, 4, 5}),
            makeTuple <Size, Array <String>> (5U, {1, 2, 3, 5, 6}),
            makeTuple <Size, Array <String>> (5U, {1, 2, 6, 7, 8}),
            makeTuple <Size, Array <String>> (4U, {1, 7, 8, 9}),
            makeTuple <Size, Array <String>> (2U, {4, 9}),
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (0U, {})
    );

    auto const sffno = makeTuple (
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (false, -1)
    );

    auto const sflno = makeTuple (
            makeTuple <bool, String> (true, 9),
            makeTuple <bool, String> (true, 9),
            makeTuple <bool, String> (true, 9),
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (false, -1)
    );

    auto const sfano = makeTuple (
            makeTuple <Size, Array <String>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <String>> (8U, {1, 2, 3, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <String>> (4U, {1, 7, 8, 9}),
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (0U, {})
    );

    auto const sData = makeTuple (
            sfo, sffo, sflo, sfao,
            sfno, sffno, sflno, sfano
    );

    auto const osfo = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (3U, {4, 5, 3}),
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 2, 3}),
            makeTuple <Size, Array <String>> (5U, {5, 6, 7, 8, 1}),
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 7, 8}),
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 7, 8})
    );

    auto const osffo = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 4)
    );

    auto const osflo = makeTuple (
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 3)
    );

    auto const osfao = makeTuple (
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (1U, {4}),
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 2, 3}),
            makeTuple <Size, Array <String>> (9U, {4, 5, 6, 7, 8, 9, 1, 2, 3}),
            makeTuple <Size, Array <String>> (9U, {4, 5, 6, 7, 8, 9, 1, 2, 3})
    );

    auto const osfno = makeTuple (
            iLimit,
            makeTuple <Size, Array <String>> (5U, {4, 5, 6, 7, 8}),
            makeTuple <Size, Array <String>> (5U, {5, 6, 7, 8, 9}),
            makeTuple <Size, Array <String>> (5U, {6, 7, 8, 9, 1}),
            makeTuple <Size, Array <String>> (4U, {7, 8, 9, 1}),
            makeTuple <Size, Array <String>> (2U, {4, 9}),
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (0U, {})
    );

    auto const osffno = makeTuple (
            makeTuple <bool, String> (true, 4),
            makeTuple <bool, String> (true, 5),
            makeTuple <bool, String> (true, 7),
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (false, -1)
    );

    auto const osflno = makeTuple (
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 3),
            makeTuple <bool, String> (true, 1),
            makeTuple <bool, String> (false, -1),
            makeTuple <bool, String> (false, -1)
    );

    auto const osfano = makeTuple (
            makeTuple <Size, Array <String>> (9U, {4, 5, 6, 7, 8, 9, 1, 2, 3}),
            makeTuple <Size, Array <String>> (8U, {5, 6, 7, 8, 9, 1, 2, 3}),
            makeTuple <Size, Array <String>> (4U, {7, 8, 9, 1}),
            makeTuple <Size, Array <String>> (0U, {}),
            makeTuple <Size, Array <String>> (0U, {})
    );

    auto const osData = makeTuple (
            osfo, osffo, osflo, osfao,
            osfno, osffno, osflno, osfano
    );

    auto const ssfo = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (3U, {{3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}})
    );

    auto const ssffo = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {2, 2}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1})
    );

    auto const ssflo = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {6, 6}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9})
    );

    auto const ssfao = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}})
    );

    auto const ssfno = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{1, 1}, {2, 2}, {6, 6}, {7, 7}, {8, 8}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (4U, {{1, 1}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (2U, {{4, 4}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {})
    );

    auto const ssffno = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1})
    );

    auto const ssflno = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9}),
            makeTuple <bool, MapEntry <String, String>> (true, {9, 9}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1})
    );

    auto const ssfano = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (8U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (4U, {{1, 1}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {})
    );

    auto const ssData = makeTuple (
            ssfo, ssffo, ssflo, ssfao,
            ssfno, ssffno, ssflno, ssfano
    );

    auto const ossfo = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (3U, {{4, 4}, {5, 5}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}})
    );

    auto const ossffo = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, 1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4})
    );

    auto const ossflo = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3})
    );

    auto const ossfao = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}})
    );

    auto const ossfno = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (5U, {{6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (4U, {{7, 7}, {8, 8}, {9, 9}, {1, 1}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (2U, {{4, 4}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {})
    );

    auto const ossffno = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (true, {4, 4}),
            makeTuple <bool, MapEntry <String, String>> (true, {5, 5}),
            makeTuple <bool, MapEntry <String, String>> (true, {7, 7}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1})
    );

    auto const ossflno = makeTuple (
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {3, 3}),
            makeTuple <bool, MapEntry <String, String>> (true, {1, 1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <String, String>> (false, {-1, -1})
    );

    auto const ossfano = makeTuple (
            makeTuple <Size, Array <MapEntry <String, String>>> (9U, {{4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (8U, {{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (4U, {{7, 7}, {8, 8}, {9, 9}, {1, 1}}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <String, String>>> (0U, {})
    );

    auto const ossData = makeTuple (
            ossfo, ossffo, ossflo, ossfao,
            ossfno, ossffno, ossflno, ossfano
    );
}


auto CollectionTest::tests_00700_00799_p2 () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        cds::Array <String> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::Array <String> const v1 = sv1;
        cds::Array <String> const v2 = sv2;
        cds::Array <String> const v3 = sv3;
        cds::Array <String> const v4 = sv4;
        cds::Array <String> const v5 = sv5;
        cds::Array <String> const v6 = sv6;
        cds::Array <String> const v7 = sv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < String > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                sData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String > > (
                this, "Collection", underTest,
                svList,
                sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        cds::LinkedList <String> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::LinkedList <String> const v1 = sv1;
        cds::LinkedList <String> const v2 = sv2;
        cds::LinkedList <String> const v3 = sv3;
        cds::LinkedList <String> const v4 = sv4;
        cds::LinkedList <String> const v5 = sv5;
        cds::LinkedList <String> const v6 = sv6;
        cds::LinkedList <String> const v7 = sv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < String > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                sData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String > > (
                this, "Collection", underTest,
                svList,
                sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringHashSet", [this, & allOk] {

        cds::HashSet <String> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::HashSet <String> const v1 = sv1;
        cds::HashSet <String> const v2 = sv2;
        cds::HashSet <String> const v3 = sv3;
        cds::HashSet <String> const v4 = sv4;
        cds::HashSet <String> const v5 = sv5;
        cds::HashSet <String> const v6 = sv6;
        cds::HashSet <String> const v7 = sv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < String > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                osData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String > > (
                this, "Collection", underTest,
                svList,
                osData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, & allOk] {

        cds::TreeSet <String> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::TreeSet <String> const v1 = sv1;
        cds::TreeSet <String> const v2 = sv2;
        cds::TreeSet <String> const v3 = sv3;
        cds::TreeSet <String> const v4 = sv4;
        cds::TreeSet <String> const v5 = sv5;
        cds::TreeSet <String> const v6 = sv6;
        cds::TreeSet <String> const v7 = sv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < String > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                sData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String > > (
                this, "Collection", underTest,
                svList,
                sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, & allOk] {

        cds::LinkedHashSet <String> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::LinkedHashSet <String> const v1 = sv1;
        cds::LinkedHashSet <String> const v2 = sv2;
        cds::LinkedHashSet <String> const v3 = sv3;
        cds::LinkedHashSet <String> const v4 = sv4;
        cds::LinkedHashSet <String> const v5 = sv5;
        cds::LinkedHashSet <String> const v6 = sv6;
        cds::LinkedHashSet <String> const v7 = sv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < String > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                sData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < String > > (
                this, "Collection", underTest,
                svList,
                sData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk] {

        cds::HashMap <String, String> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        cds::HashMap <String, String> const v1 = ssv1;
        cds::HashMap <String, String> const v2 = ssv2;
        cds::HashMap <String, String> const v3 = ssv3;
        cds::HashMap <String, String> const v4 = ssv4;
        cds::HashMap <String, String> const v5 = ssv5;
        cds::HashMap <String, String> const v6 = ssv6;
        cds::HashMap <String, String> const v7 = ssv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <String, String> > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                ossData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <String, String> > > (
                this, "Collection", underTest,
                ssvList,
                ossData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, & allOk] {

        cds::TreeMap <String, String> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        cds::TreeMap <String, String> const v1 = ssv1;
        cds::TreeMap <String, String> const v2 = ssv2;
        cds::TreeMap <String, String> const v3 = ssv3;
        cds::TreeMap <String, String> const v4 = ssv4;
        cds::TreeMap <String, String> const v5 = ssv5;
        cds::TreeMap <String, String> const v6 = ssv6;
        cds::TreeMap <String, String> const v7 = ssv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <String, String> > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                ssData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <String, String> > > (
                this, "Collection", underTest,
                ssvList,
                ssData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, & allOk] {

        cds::LinkedHashMap <String, String> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };

        cds::LinkedHashMap <String, String> const v1 = ssv1;
        cds::LinkedHashMap <String, String> const v2 = ssv2;
        cds::LinkedHashMap <String, String> const v3 = ssv3;
        cds::LinkedHashMap <String, String> const v4 = ssv4;
        cds::LinkedHashMap <String, String> const v5 = ssv5;
        cds::LinkedHashMap <String, String> const v6 = ssv6;
        cds::LinkedHashMap <String, String> const v7 = ssv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <String, String> > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                ssData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <String, String> > > (
                this, "Collection", underTest,
                ssvList,
                ssData
        );
    });

    return allOk;
}
