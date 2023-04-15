#include "MutableCollectionTest_450_common.hpp"
#include <CDS/TreeMap>
#include <CDS/LinkedHashMap>

#include "../CollectionTest_450_data.hpp"

auto MutableCollectionTest::tests_00450_00499_s () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringArray", [this, &allOk]{

        using E = String;
        using C = cds::Array <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, &allOk]{

        using E = String;
        using C = cds::LinkedList <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::sData,
                data::sDataGroups,
                data::sResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::HashMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ssResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringTreeMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::TreeMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ossResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : StringToStringLinkedHashMap", [this, &allOk]{

        using E = cds::MapEntry <String, String>;
        using C = cds::LinkedHashMap <String, String>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::ssData,
                data::ssDataGroups,
                data::ossResultGroups
        );
    });

    return allOk;
}
