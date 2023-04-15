#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"


auto CollectionTest::tests_00450_00599_p2 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [this, &allOk]{

        using E = String;
        using C = cds::Array <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, &allOk]{

        using E = String;
        using C = cds::LinkedList <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringHashSet", [this, &allOk]{

        using E = String;
        using C = cds::HashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::usResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringTreeSet", [this, &allOk]{

        using E = String;
        using C = cds::TreeSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedHashSet", [this, &allOk]{

        using E = String;
        using C = cds::LinkedHashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::HashMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ssResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::TreeMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ossResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::LinkedHashMap <String, String>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ossResultGroups
        );
    });

    return allOk;
}
