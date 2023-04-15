#include "CollectionTest.h"
#include "CollectionTest_450_common.hpp"
#include "CollectionTest_450_data.hpp"


auto CollectionTest::tests_00450_00599_p1 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntArray", [this, &allOk]{

        using E = int;
        using C = cds::Array <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, &allOk]{

        using E = int;
        using C = cds::LinkedList <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntHashSet", [this, &allOk]{

        using E = int;
        using C = cds::HashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntTreeSet", [this, &allOk]{

        using E = int;
        using C = cds::TreeSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntLinkedHashSet", [this, &allOk]{

        using E = int;
        using C = cds::LinkedHashSet <E>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iData,
                data::iDataGroups,
                data::iResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::HashMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntTreeMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::TreeMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    this->executeSubtest ( "CollectionTestGroup-RemoveOf-" __CDS_cpplang_core_version_name " : CTC-00450-RO-" __CDS_cpplang_core_version_name " : IntToIntLinkedHashMap", [this, &allOk]{

        using E = cds::MapEntry <int, int>;
        using C = cds::LinkedHashMap <int, int>;

        allOk = allOk && collectionTest_450_All <E, C> (
                this,
                data::iiData,
                data::iiDataGroups,
                data::iiResultGroups
        );
    });

    return allOk;
}
