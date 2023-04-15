#include "MutableCollectionTest_450_common.hpp"
#include <initializer_list>

#include <CDS/TreeMap>
#include <CDS/LinkedHashMap>

#include "../CollectionTest_450_data.hpp"

auto MutableCollectionTest::tests_00450_00499_i () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [this, &allOk]{

        using E = int;
        using C = cds::Array <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, &allOk]{

        using E = int;
        using C = cds::LinkedList <E>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::HashMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::TreeMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : MCTG-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::LinkedHashMap <int, int>;

        allOk = allOk && mutableCollectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    return allOk;
}
