#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"


auto CollectionTest::tests_00450_00599_p2 () noexcept -> bool {

    bool allOk = true;

    using namespace data;

    auto const sData = composeTestObject <String> ();
    auto const sDataGroups = composeTestDataGroups <String> ();
    auto const sResultGroups = composeTestResultGroups <String> ();
    auto const usResultGroups = hashComposeTestResultGroups <String> ();

    auto const ssData = composeMapTestObject <String> ();
    auto const ssDataGroups = composeMapTestDataGroups <String> ();
    auto const ossResultGroups = composeMapTestResultGroups <String> ();
    auto const ssResultGroups = hashMapComposeTestResultGroups <String> ();

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [&]{

        using E = String;
        using C = cds::Array <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [&]{

        using E = String;
        using C = cds::LinkedList <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSet", [&]{

        using E = String;
        using C = cds::HashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                usResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringTreeSet", [&]{

        using E = String;
        using C = cds::TreeSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [&]{

        using E = String;
        using C = cds::LinkedHashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                sData,
                sDataGroups,
                sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::HashMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ssResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::TreeMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ossResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [&]{

        using E = cds::MapEntry <String, String>;
        using C = cds::LinkedHashMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                ssData,
                ssDataGroups,
                ossResultGroups
        );
    });

    return allOk;
}
