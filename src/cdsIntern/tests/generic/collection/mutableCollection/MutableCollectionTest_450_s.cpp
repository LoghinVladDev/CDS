#include "MutableCollectionTest_450_common.hpp"
#include <CDS/TreeMap>
#include <CDS/LinkedHashMap>

#include "../CollectionTest_450_data.hpp"

auto MutableCollectionTest::tests_00450_00499_s () noexcept -> bool {

    bool allOk = true;

    using namespace data;

    auto const sData = composeTestObject <String> ();
    auto const sDataGroups = composeTestDataGroups <String> ();
    auto const sResultGroups = composeTestResultGroups <String> ();

    auto const ssData = composeMapTestObject <String> ();
    auto const ssDataGroups = composeMapTestDataGroups <String> ();
    auto const ossResultGroups = composeMapTestResultGroups <String> ();
    auto const ssResultGroups = hashMapComposeTestResultGroups <String> ();

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [&]{

        using E = String;
        using C = cds::Array <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [&]{

        using E = String;
        using C = cds::LinkedList <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::HashMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ssResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::TreeMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ossResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::LinkedHashMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ossResultGroups
        );
    });

    return allOk;
}
