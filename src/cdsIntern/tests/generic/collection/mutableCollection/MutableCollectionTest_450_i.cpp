#include "MutableCollectionTest_450_common.hpp"
#include <initializer_list>

#include <CDS/TreeMap>
#include <CDS/LinkedHashMap>

#include "../CollectionTest_450_data.hpp"

auto MutableCollectionTest::tests_00450_00499_i () noexcept -> bool {

    bool allOk = true;

    using namespace data;

    auto const iData = composeTestObject <int> ();
    auto const iDataGroups = composeTestDataGroups <int> ();
    auto const iResultGroups = composeTestResultGroups <int> ();

    auto const iiData = composeMapTestObject <int> ();
    auto const iiDataGroups = composeMapTestDataGroups <int> ();
    auto const iiResultGroups = composeMapTestResultGroups <int> ();

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [&]{

        using E = int;
        using C = cds::Array <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [&]{

        using E = int;
        using C = cds::LinkedList <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                iData,
                iDataGroups,
                iResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::HashMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::TreeMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [&]{

        using E = cds::MapEntry <int, int>;
        using C = cds::LinkedHashMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                iiData,
                iiDataGroups,
                iiResultGroups
        );
    });

    return allOk;
}
