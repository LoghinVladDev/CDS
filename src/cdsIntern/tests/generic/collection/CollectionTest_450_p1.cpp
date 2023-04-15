#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"


auto CollectionTest::tests_00450_00599_p1 () noexcept -> bool {

    bool allOk = true;

    using namespace data;

    auto const iData = composeTestObject <int> ();
    auto const iDataGroups = composeTestDataGroups <int> ();
    auto const iResultGroups = composeTestResultGroups <int> ();

    auto const iiData = composeMapTestObject <int> ();
    auto const iiDataGroups = composeMapTestDataGroups <int> ();
    auto const iiResultGroups = composeMapTestResultGroups <int> ();

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
