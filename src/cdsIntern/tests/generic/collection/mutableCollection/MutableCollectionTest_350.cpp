#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"

namespace {
    /* MutableCollectionTestGroup-RemoveAbsIt-cpp-xx : MCTG-00350-RAIT-cpp-xx. MCTC-00351-RAIT to MCTC-00356-RAIT */
    template <
            typename __MemberType  /* NOLINT(bugprone-reserved-identifier) */
    > auto mutableCollectionTestGroupRemoveAbstractIterator (
            cds :: MutableCollection < __MemberType >       & collection,
            Test                                                     * pTestLib,
            cds :: MutableCollection < __MemberType > const & equivAfter1,
            cds :: MutableCollection < __MemberType >  & equivAfter2,
            cds :: MutableCollection < __MemberType > const & equivAfter3,
            cds :: MutableCollection < __MemberType > const & equivAfter5,
            cds :: MutableCollection < __MemberType > const & equivAfter6
    ) -> bool {

        pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );

        /* MutableCollectionTestGroup-RemoveAbsIt-removeAtFront-cpp-xx : MCTC-00351-RAIT-removeAtFront-cpp-xx */
        typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAtFront = collection.begin();
        auto const resultToRemoveAtFront = collection.remove( toRemoveAtFront );
        auto const expectedResultToRemoveAtFront = true;
        pTestLib->log ( "object after 'removeAtFront' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter1.toString().cStr() );
        if ( resultToRemoveAtFront != expectedResultToRemoveAtFront || ! collection.equals ( equivAfter1 ) ) {
            pTestLib->logError( "'MCTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00351-RAIT-removeAtFront-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-RemoveAbsIt-removeInBounds-cpp-xx : MCTC-00352-RAIT-removeInBounds-cpp-xx */
        typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveInBounds = collection.begin();
        for ( uint32 i = 0; i * 2 < collection.size(); ++ i ) {
            ++ toRemoveInBounds;
        }

        auto const resultToRemoveAtInBounds = collection.remove( toRemoveInBounds );
        auto const expectedResultToRemoveAtInBounds = true;
        pTestLib->log ( "object after 'removeInBounds' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter2.toString().cStr() );
        if ( resultToRemoveAtInBounds != expectedResultToRemoveAtInBounds || ! collection.equals ( equivAfter2 ) ) {
            pTestLib->logError( "'MCTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00352-RAIT-removeInBounds-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-RemoveAbsIt-removeAtEnd-cpp-xx : MCTC-00353-RAIT-removeAtEnd-cpp-xx */
        typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAtEnd = collection.begin();
        for ( uint32 i = 0; i + 1 < collection.size(); ++ i ) {
            ++ toRemoveAtEnd;
        }

        auto const resultToRemoveAtEnd = collection.remove( toRemoveAtEnd );
        auto const expectedResultToRemoveAtEnd = true;
        pTestLib->log ( "object after 'removeAtEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter3.toString().cStr() );
        if ( resultToRemoveAtEnd != expectedResultToRemoveAtEnd || ! collection.equals ( equivAfter3 ) ) {
            pTestLib->logError( "'MCTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00353-RAIT-removeAtEnd-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-RemoveAbsIt-removeBeforeFront-" __CDS_cpplang_core_version_name " : MCTC-00354-RAIT-removeBeforeFront-cpp-xx : N/A */

        /* MutableCollectionTestGroup-RemoveAbsIt-removeAfterEnd-cpp-xx : MCTC-00355-RAIT-removeAfterEnd-cpp-xx */
        typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveAfterBack = collection.end();
        auto const resultToRemoveAfterEnd = collection.remove( toRemoveAfterBack );
        auto const expectedResultToRemoveAfterEnd = false;
        pTestLib->log ( "object after 'removeAfterEnd' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
        if ( resultToRemoveAfterEnd != expectedResultToRemoveAfterEnd || ! collection.equals ( equivAfter5 ) ) {
            pTestLib->logError( "'MCTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00355-RAIT-removeAfterEnd-" __CDS_cpplang_core_version_name "' OK" );
        }

        /* MutableCollectionTestGroup-RemoveAbsIt-removeFromOther-cpp-xx : MCTC-00355-RAIT-removeFromOther-cpp-xx */
        typename cds :: MutableCollection < __MemberType > :: Iterator toRemoveFromSimilar = equivAfter2.begin();
        auto const resultToRemoveFromSimilar = collection.remove( toRemoveFromSimilar );
        auto const expectedResultToRemoveFromSimilar = false;
        pTestLib->log ( "object after 'removeFromOther' : '%s'. expected : '%s'", collection.toString().cStr(), equivAfter5.toString().cStr() );
        if ( resultToRemoveFromSimilar != expectedResultToRemoveFromSimilar || ! collection.equals ( equivAfter6 ) ) {
            pTestLib->logError( "'MCTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' failed" );
            return false;
        } else {
            pTestLib->logOK ( "'MCTC-00356-RAIT-removeFromOther-" __CDS_cpplang_core_version_name "' OK" );
        }

        return true;
    }
}

auto MutableCollectionTest::tests_00350_00399 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk]{

        cds :: Array < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < int > & underTestColl = underTest;

        cds :: Array < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk]{

        cds :: LinkedList < int > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < int > & underTestColl = underTest;

        cds :: LinkedList < int > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < int > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < int > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < int > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : IntToIntHashMap", [this, & allOk]{

        cds :: HashMap < int, int > underTest = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: MutableCollection < MapEntry < int, int > > & underTestColl = underTest;

        cds :: HashMap < int, int > afterFrontRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterMidRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8}, {9, 9} };
        cds :: HashMap < int, int > afterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterAfterBackRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };
        cds :: HashMap < int, int > afterOtherRemove = { {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {8, 8} };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk]{

        cds :: Array < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < String > & underTestColl = underTest;

        cds :: Array < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: Array < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: Array < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: Array < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk]{

        cds :: LinkedList < String > underTest = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: MutableCollection < String > & underTestColl = underTest;

        cds :: LinkedList < String > afterFrontRemove = { 2, 3, 4, 5, 6, 7, 8, 9 };
        cds :: LinkedList < String > afterMidRemove = { 2, 3, 4, 5, 7, 8, 9 };
        cds :: LinkedList < String > afterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterAfterBackRemove = { 2, 3, 4, 5, 7, 8 };
        cds :: LinkedList < String > afterOtherRemove = { 2, 3, 4, 5, 7, 8 };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    this->executeSubtest ( "MutableCollectionTestGroup-RemoveAbsIt-" __CDS_cpplang_core_version_name " : MCTG-00350-RAIT-" __CDS_cpplang_core_version_name " : StringToStringHashMap", [this, & allOk]{

        cds :: HashMap < String, String > underTest = { {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3} };
        cds :: MutableCollection < MapEntry < String, String > > & underTestColl = underTest;

        cds :: HashMap < String, String > afterFrontRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {1, 1}, {2, 2}, {3, 3},  };
        cds :: HashMap < String, String > afterMidRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2}, {3, 3} };
        cds :: HashMap < String, String > afterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterAfterBackRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };
        cds :: HashMap < String, String > afterOtherRemove = { {5, 5}, {6, 6}, {7, 7}, {8, 8}, {1, 1}, {2, 2} };

        allOk = allOk && mutableCollectionTestGroupRemoveAbstractIterator (
                underTest,
                this,
                afterFrontRemove,
                afterMidRemove,
                afterBackRemove,
                afterAfterBackRemove,
                afterOtherRemove
        );
    });
    
    return allOk;
}
