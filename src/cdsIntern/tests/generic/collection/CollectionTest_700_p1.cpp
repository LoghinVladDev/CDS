#include "CollectionTest.h"
#include "CollectionTest_700_common.hpp"
#include <initializer_list>

namespace {
    using cds::makeTuple;

    std::initializer_list <int> const iv1 = {-1, -4, -7, 20};
    std::initializer_list <int> const iv2 = {-9, -8, -7, -6, -5, 4, -3, -2, -1};
    std::initializer_list <int> const iv3 = {-9, -8, -7, -6, 5, 4, 3, -2, -1};
    std::initializer_list <int> const iv4 = {-9, -8, -7, 6, 5, 4, 3, 2, -1};
    std::initializer_list <int> const iv5 = {-9, 8, 7, 6, 5, -4, 3, 2, 1};
    std::initializer_list <int> const iv6 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::initializer_list <int> const iv7 = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ,15 , 16, 17, 18, 19, 20};

    std::initializer_list <std::initializer_list <int> const *> const ivList = {& iv1, & iv2, & iv3, & iv4, & iv5, & iv6, & iv7};

    std::initializer_list <MapEntry <int, int>> const iiv1 = {{-1, -1}, {-4, -4}, {-7, -7}, {20, 20}};
    std::initializer_list <MapEntry <int, int>> const iiv2 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {4, 4}, {-3, -3}, {-2, -2}, {-1, -1}};
    std::initializer_list <MapEntry <int, int>> const iiv3 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {5, 5}, {4, 4}, {3, 3}, {-2, -2}, {-1, -1}};
    std::initializer_list <MapEntry <int, int>> const iiv4 = {{-9, -9}, {-8, -8}, {-7, -7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {-1, -1}};
    std::initializer_list <MapEntry <int, int>> const iiv5 = {{-9, -9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {-4, -4}, {3, 3}, {2, 2}, {1, 1}};
    std::initializer_list <MapEntry <int, int>> const iiv6 = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    std::initializer_list <MapEntry <int, int>> const iiv7 = {{-9, -9}, {-8, -8}, {-7, -7}, {-6, -6}, {-5, -5}, {-4, -4}, {-3, -3}, {-2, -2}, {-1, -1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
            {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18}, {19, 19}, {20, 20}};

    std::initializer_list <std::initializer_list <MapEntry <int, int>> const *> const iivList = {& iiv1, & iiv2, & iiv3, & iiv4, & iiv5, & iiv6, & iiv7};

    Size const iLimit = 5U;

    auto const ifo = makeTuple (
            iLimit,
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (1U, {4}),
            makeTuple <Size, Array <int>> (3U, {3, 4, 5}),
            makeTuple <Size, Array <int>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <int>> (5U, {1, 2, 3, 5, 6}),
            makeTuple <Size, Array <int>> (5U, {1, 2, 3, 4, 5}),
            makeTuple <Size, Array <int>> (5U, {1, 2, 3, 4, 5})
    );

    auto const iffo = makeTuple (
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (true, 4),
            makeTuple <bool, int> (true, 2),
            makeTuple <bool, int> (true, 1),
            makeTuple <bool, int> (true, 1)
    );

    auto const iflo = makeTuple (
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (true, 4),
            makeTuple <bool, int> (true, 6),
            makeTuple <bool, int> (true, 9),
            makeTuple <bool, int> (true, 9)
    );

    auto const ifao = makeTuple (
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (1U, {4}),
            makeTuple <Size, Array <int>> (5U, {2, 3, 4, 5, 6}),
            makeTuple <Size, Array <int>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <int>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9})
    );

    auto const ifno = makeTuple (
            iLimit,
            makeTuple <Size, Array <int>> (5U, {1, 2, 3, 4, 5}),
            makeTuple <Size, Array <int>> (5U, {1, 2, 3, 5, 6}),
            makeTuple <Size, Array <int>> (5U, {1, 2, 6, 7, 8}),
            makeTuple <Size, Array <int>> (4U, {1, 7, 8, 9}),
            makeTuple <Size, Array <int>> (2U, {4, 9}),
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (0U, {})
    );

    auto const iffno = makeTuple (
            makeTuple <bool, int> (true, 1),
            makeTuple <bool, int> (true, 1),
            makeTuple <bool, int> (true, 1),
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (false, -1)
    );

    auto const iflno = makeTuple (
            makeTuple <bool, int> (true, 9),
            makeTuple <bool, int> (true, 9),
            makeTuple <bool, int> (true, 9),
            makeTuple <bool, int> (false, -1),
            makeTuple <bool, int> (false, -1)
    );

    auto const ifano = makeTuple (
            makeTuple <Size, Array <int>> (9U, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <int>> (8U, {1, 2, 3, 5, 6, 7, 8, 9}),
            makeTuple <Size, Array <int>> (4U, {1, 7, 8, 9}),
            makeTuple <Size, Array <int>> (0U, {}),
            makeTuple <Size, Array <int>> (0U, {})
    );

    auto const iData = makeTuple (
            ifo, iffo, iflo, ifao,
            ifno, iffno, iflno, ifano
    );

    auto const iifo = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (3U, {{3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}})
    );

    auto const iiffo = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (false, {-1, 1}),
            makeTuple <bool, MapEntry <int, int>> (true, {4, 4}),
            makeTuple <bool, MapEntry <int, int>> (true, {2, 2}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1})
    );

    auto const iiflo = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <int, int>> (true, {4, 4}),
            makeTuple <bool, MapEntry <int, int>> (true, {6, 6}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9})
    );

    auto const iifao = makeTuple (
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (1U, {{4, 4}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}})
    );

    auto const iifno = makeTuple (
            iLimit,
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (5U, {{1, 1}, {2, 2}, {6, 6}, {7, 7}, {8, 8}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (4U, {{1, 1}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (2U, {{4, 4}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {})
    );

    auto const iiffno = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1}),
            makeTuple <bool, MapEntry <int, int>> (true, {1, 1}),
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1})
    );

    auto const iiflno = makeTuple (
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9}),
            makeTuple <bool, MapEntry <int, int>> (true, {9, 9}),
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1}),
            makeTuple <bool, MapEntry <int, int>> (false, {-1, -1})
    );

    auto const iifano = makeTuple (
            makeTuple <Size, Array <MapEntry <int, int>>> (9U, {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (8U, {{1, 1}, {2, 2}, {3, 3}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (4U, {{1, 1}, {7, 7}, {8, 8}, {9, 9}}),
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {}),
            makeTuple <Size, Array <MapEntry <int, int>>> (0U, {})
    );

    auto const iiData = makeTuple (
            iifo, iiffo, iiflo, iifao,
            iifno, iiffno, iiflno, iifano
    );
}


auto CollectionTest::tests_00700_00799_p1 () noexcept -> bool {
    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        cds :: Array < int > const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        cds::Array <int> const v1 = iv1;
        cds::Array <int> const v2 = iv2;
        cds::Array <int> const v3 = iv3;
        cds::Array <int> const v4 = iv4;
        cds::Array <int> const v5 = iv5;
        cds::Array <int> const v6 = iv6;
        cds::Array <int> const v7 = iv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < int > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                this, "Collection", underTest,
                ivList,
                iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        cds::LinkedList <int> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds::LinkedList <int> const v1 = iv1;
        cds::LinkedList <int> const v2 = iv2;
        cds::LinkedList <int> const v3 = iv3;
        cds::LinkedList <int> const v4 = iv4;
        cds::LinkedList <int> const v5 = iv5;
        cds::LinkedList <int> const v6 = iv6;
        cds::LinkedList <int> const v7 = iv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < int > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                this, "Collection", underTest,
                ivList,
                iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntHashSet", [this, & allOk] {

        cds::HashSet <int> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds::HashSet <int> const v1 = iv1;
        cds::HashSet <int> const v2 = iv2;
        cds::HashSet <int> const v3 = iv3;
        cds::HashSet <int> const v4 = iv4;
        cds::HashSet <int> const v5 = iv5;
        cds::HashSet <int> const v6 = iv6;
        cds::HashSet <int> const v7 = iv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < int > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                this, "Collection", underTest,
                ivList,
                iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, & allOk] {

        cds::TreeSet <int> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds::TreeSet <int> const v1 = iv1;
        cds::TreeSet <int> const v2 = iv2;
        cds::TreeSet <int> const v3 = iv3;
        cds::TreeSet <int> const v4 = iv4;
        cds::TreeSet <int> const v5 = iv5;
        cds::TreeSet <int> const v6 = iv6;
        cds::TreeSet <int> const v7 = iv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < int > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                this, "Collection", underTest,
                ivList,
                iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, & allOk] {

        cds::LinkedHashSet <int> const underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds::LinkedHashSet <int> const v1 = iv1;
        cds::LinkedHashSet <int> const v2 = iv2;
        cds::LinkedHashSet <int> const v3 = iv3;
        cds::LinkedHashSet <int> const v4 = iv4;
        cds::LinkedHashSet <int> const v5 = iv5;
        cds::LinkedHashSet <int> const v6 = iv6;
        cds::LinkedHashSet <int> const v7 = iv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < int > > (
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < int > > (
                this, "Collection", underTest,
                ivList,
                iData
        );
    });

    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk] {

        cds::HashMap <int, int> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds::HashMap <int, int> const v1 = iiv1;
        cds::HashMap <int, int> const v2 = iiv2;
        cds::HashMap <int, int> const v3 = iiv3;
        cds::HashMap <int, int> const v4 = iiv4;
        cds::HashMap <int, int> const v5 = iiv5;
        cds::HashMap <int, int> const v6 = iiv6;
        cds::HashMap <int, int> const v7 = iiv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <int, int> > >(
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iiData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <int, int> > >(
                this, "Collection", underTest,
                iivList,
                iiData
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, & allOk] {

        cds::LinkedHashMap <int, int> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds::LinkedHashMap <int, int> const v1 = iiv1;
        cds::LinkedHashMap <int, int> const v2 = iiv2;
        cds::LinkedHashMap <int, int> const v3 = iiv3;
        cds::LinkedHashMap <int, int> const v4 = iiv4;
        cds::LinkedHashMap <int, int> const v5 = iiv5;
        cds::LinkedHashMap <int, int> const v6 = iiv6;
        cds::LinkedHashMap <int, int> const v7 = iiv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <int, int> > >(
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iiData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <int, int> > >(
                this, "Collection", underTest,
                iivList,
                iiData
        );
    });
    this->executeSubtest ( "CollectionTestGroup-FindOf-" __CDS_cpplang_core_version_name " : CTG-00700-FO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, & allOk] {

        cds::TreeMap <int, int> const underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds::TreeMap <int, int> const v1 = iiv1;
        cds::TreeMap <int, int> const v2 = iiv2;
        cds::TreeMap <int, int> const v3 = iiv3;
        cds::TreeMap <int, int> const v4 = iiv4;
        cds::TreeMap <int, int> const v5 = iiv5;
        cds::TreeMap <int, int> const v6 = iiv6;
        cds::TreeMap <int, int> const v7 = iiv7;

        allOk = allOk && collectionTestGroupFindOf < cds :: Collection < MapEntry <int, int> > >(
                this, "Collection", underTest,
                { & v1, & v2, & v3, & v4, & v5, & v6, & v7 },
                iiData
        );

        allOk = allOk && collectionTestGroupFindOf < std :: initializer_list < MapEntry <int, int> > >(
                this, "Collection", underTest,
                iivList,
                iiData
        );
    });

    return allOk;
}
