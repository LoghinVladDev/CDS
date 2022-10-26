//
// Created by loghin on 13/09/22.
//

#include "SetTest.h"

#include <CDS/HashSet>
#include <CDS/experimental/TreeSet>
#include <CDS/LinkedHashSet>

#include <CDS/Range>
#include <vector>
#include <array>

template < typename __ElementType >
inline auto equiv (
        cds :: Set < __ElementType >    const & s,
        std :: initializer_list < __ElementType >       const & l
) noexcept -> bool {

    if ( s.size() != l.size() ) {
        return false;
    }

    auto itS = s.begin();
    auto itL = l.begin();
    auto endS = s.end();
    auto endL = l.end();
    while ( itS != endS && itL != endL ) {
        if ( * itS != * itL ) {
            return false;
        }

        ++ itS; ++ itL;
    }

    if ( itS != endS || itL != endL ) {
        return false;
    }

    return true;
}

/* SetTestGroup-MemberFunctions-CPP14 : STS-00100-MF-CPP14. Tests STC-00101 to STC-001xx */
template <
        typename __MemberType /* NOLINT(bugprone-reserved-identifier) */
> auto setTestGroupMemberFunctions (
        cds :: Set < __MemberType >       & collection,
        Test                                              * pTestLib,
        String                                      const & expectedToString,
        __MemberType                                const & remove1,
        bool                                                remove1Success,
        std :: initializer_list < __MemberType >    const & remove1Equiv,
        __MemberType                                const & remove2,
        bool                                                remove2Success,
        std :: initializer_list < __MemberType >    const & remove2Equiv,
        __MemberType                                const & remove3,
        bool                                                remove3Success,
        std :: initializer_list < __MemberType >    const & remove3Equiv,
        __MemberType                                const & remove4,
        bool                                                remove4Success,
        std :: initializer_list < __MemberType >    const & remove4Equiv,
        __MemberType                                const & remove5,
        bool                                                remove5Success,
        std :: initializer_list < __MemberType >    const & remove5Equiv
) -> bool {

    pTestLib->log ( "Object Under Test : %s", collection.toString().cStr() );


    /* SetTestGroup-MemberFunctions-toString-CPP14 : STC-00101-MF-toString-CPP14 */
    auto asString = collection.toString();
    pTestLib->log ( "object 'toString' : '%s'. expected 'toString' : '%s'", asString.cStr(), expectedToString.cStr() );
    if ( asString != expectedToString ) {
        pTestLib->logError ( "'STC-00101-MF-toString-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00101-MF-toString-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-removeScen1-CPP14 : STC-00103-MF-removeScen1-CPP14 */
    bool resultRemove1 = collection.remove ( remove1 );
    if ( resultRemove1 != remove1Success || ! equiv ( collection, remove1Equiv ) ) {
        pTestLib->logError ( "'STC-00103-MF-removeScen1-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00103-MF-removeScen1-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-removeScen2-CPP14 : STC-00104-MF-removeScen2-CPP14 */
    bool resultRemove2 = collection.remove ( remove2 );
    if ( resultRemove2 != remove2Success || ! equiv ( collection, remove2Equiv ) ) {
        pTestLib->logError ( "'STC-00104-MF-removeScen2-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00104-MF-removeScen2-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-removeScen3-CPP14 : STC-00105-MF-removeScen3-CPP14 */
    bool resultRemove3 = collection.remove ( remove3 );
    if ( resultRemove3 != remove3Success || ! equiv ( collection, remove3Equiv ) ) {
        pTestLib->logError ( "'STC-00105-MF-removeScen3-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00105-MF-removeScen3-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-removeScen4-CPP14 : STC-00106-MF-removeScen4-CPP14 */
    bool resultRemove4 = collection.remove ( remove4 );
    if ( resultRemove4 != remove4Success || ! equiv ( collection, remove4Equiv ) ) {
        pTestLib->logError ( "'STC-00106-MF-removeScen4-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00106-MF-removeScen4-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-removeScen5-CPP14 : STC-00107-MF-removeScen5-CPP14 */
    bool resultRemove5 = collection.remove ( remove5 );
    if ( resultRemove5 != remove5Success || ! equiv ( collection, remove5Equiv ) ) {
        pTestLib->logError ( "'STC-00107-MF-removeScen5-CPP14' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00107-MF-removeScen5-CPP14' OK" );
    }

    /* SetTestGroup-MemberFunctions-clear-CPP14 : STC-00102-MF-clear-CPP14 */
    collection.clear();

    asString                    = collection.toString();

    pTestLib->log ( "Object Cleared using 'clear'. Re-execution after clear : " );
    pTestLib->log ( "object 'toString' : '%s'. potential expected 'toString' : '%s'", asString.cStr(), "[]" );

    if ( asString.length() > 2ULL ) {
        pTestLib->logError( "'STC-00102-MF-clear-CPP14 - toString' failed" );
        return false;
    } else {
        pTestLib->logOK ( "'STC-00102-MF-clear-CPP14' OK" );
    }


    return true;
}

/* SetTestSuite-CPP14 : STS-00001-CPP14 */
auto SetTest :: execute () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : IntHashSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: HashSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](int e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : IntTreeSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: experimental :: TreeSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](int e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : IntLinkedHashSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: LinkedHashSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](int e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : StringHashSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: HashSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](String const & e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : StringTreeSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: experimental :: TreeSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](String const & e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberUniqueness-CPP14 : STG-00002-MU-CPP14 : StringLinkedHashSet", [& allOk, this] {

        /* SetTestCase-MemberUniqueness-SetDuplicateProperty-CPP14 : STC-00003-MU-SetDuplicateProperty-CPP14 */
        cds :: LinkedHashSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 1, 2, 2, 2, 2, 3, 2,2, 3, 3,3, 5,5 , 5, 4, 5, 1, 1, 2, 4, 5, 3, 1, 2 };
        bool status = true;

        for ( auto const & e : underTest ) {
            if ( underTest.count([& e](String const & e2) { return e2 == e; }) != 1 ) {
                status = false;
            }
        }

        if ( allOk && ! status ) {
            this->logError ( "'STC-00003-MU-SetDuplicateProperty-CPP14' failed" );
            allOk = false;
        }

        if ( allOk ) {
            this->logOK( "'STC-00003-MU-SetDuplicateProperty-CPP14' OK" );
        }
    });

    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : IntHashSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: HashSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast < bool > (it) || it == underTest.end() || ( * it != e ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : IntTreeSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: experimental :: TreeSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast < bool > (it) || it == underTest.end() || ( * it != e ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : IntLinkedHashSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: LinkedHashSet < int > intSetUnderTest;
        cds :: Set < int > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast < bool > (it) || it == underTest.end() || ( * it != e ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : StringHashSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: HashSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast < bool > (it) || it == underTest.end() || ( * it != String(e) ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : StringTreeSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: experimental :: TreeSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast <bool> (it) || it == underTest.end() || ( * it != String(e) ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });
    this->executeSubtest ( "SetTestGroup-FindUnique-CPP14 : STG-00050-FU-CPP14 : StringLinkedHashSet", [& allOk, this] {

        /* SetTestCase-FindUnique-FindUniqueNotIn-CPP14 : STC-00051-MU-FindUniqueNotIn-CPP14 */
        cds :: LinkedHashSet < String > intSetUnderTest;
        cds :: Set < String > & underTest = intSetUnderTest;
        intSetUnderTest = { 1, 2, 3, 4, 5 };

        for ( auto e : { -5, -4, -3, -2, -1, 0, 6, 7, 8, 9 } ) {
            auto it = underTest.find ( e );
            if ( it != underTest.end() ) {
                this->logError ( "'STC-00051-FU-FindUniqueNotIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00051-FU-FindUniqueNotIn-CPP14' OK" );
        }

        /* SetTestCase-FindUnique-FindUniqueIn-CPP14 : STC-00052-MU-FindUniqueIn-CPP14 */

        for ( auto e : { 1, 2, 3, 4, 5 } ) {
            auto it = underTest.find ( e );
            if ( ! static_cast <bool> (it) || it == underTest.end() || ( * it != String(e) ) ) {
                this->logError ( "'STC-00052-FU-FindUniqueIn-CPP14' failed" );
                allOk = false;
                break;
            }
        }

        if ( allOk ) {
            this->logOK( "'STC-00052-FU-FindUniqueIn-CPP14' OK" );
        }
    });

    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : IntHashSet", [& allOk, this] {

        cds :: HashSet < int > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";

        auto status = setTestGroupMemberFunctions (
                intSet,
                this,
                expectedToString,
                6, false,
                { 1, 2, 3, 4, 5 },
                -1, false,
                { 1, 2, 3, 4, 5 },
                5, true,
                { 1, 2, 3, 4 },
                1, true,
                { 2, 3, 4 },
                3, true,
                { 2, 4 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : IntTreeSet", [& allOk, this] {

        cds :: experimental :: TreeSet < int > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";

        auto status = setTestGroupMemberFunctions (
                intSet,
                this,
                expectedToString,
                6, false,
                { 1, 2, 3, 4, 5 },
                -1, false,
                { 1, 2, 3, 4, 5 },
                5, true,
                { 1, 2, 3, 4 },
                1, true,
                { 2, 3, 4 },
                3, true,
                { 2, 4 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : IntLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < int > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";

        auto status = setTestGroupMemberFunctions (
                intSet,
                this,
                expectedToString,
                6, false,
                { 1, 2, 3, 4, 5 },
                -1, false,
                { 1, 2, 3, 4, 5 },
                5, true,
                { 1, 2, 3, 4 },
                1, true,
                { 2, 3, 4 },
                3, true,
                { 2, 4 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : StringHashSet", [& allOk, this] {

        cds :: HashSet < String > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 4, 5, 1, 2, 3 }";

        auto status = setTestGroupMemberFunctions < String > (
                intSet,
                this,
                expectedToString,
                6, false,
                { 4, 5, 1, 2, 3 },
                -1, false,
                { 4, 5, 1, 2, 3 },
                5, true,
                { 4, 1, 2, 3 },
                1, true,
                { 4, 2, 3 },
                3, true,
                { 4, 2 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : StringTreeSet", [& allOk, this] {

        cds :: experimental :: TreeSet < String > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";

        auto status = setTestGroupMemberFunctions < String > (
                intSet,
                this,
                expectedToString,
                6, false,
                { 1, 2, 3, 4, 5 },
                -1, false,
                { 1, 2, 3, 4, 5 },
                5, true,
                { 1, 2, 3, 4 },
                1, true,
                { 2, 3, 4 },
                3, true,
                { 2, 4 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });
    this->executeSubtest ( "SetTestGroup-MemberFunctions-CPP14 : STG-00100-MF-CPP14 : StringLinkedHashSet", [& allOk, this] {

        cds :: LinkedHashSet < String > intSet;
        intSet = { 1, 2, 3, 4, 5 };

        auto expectedToString       = "{ 1, 2, 3, 4, 5 }";

        auto status = setTestGroupMemberFunctions < String > (
                intSet,
                this,
                expectedToString,
                6, false,
                { 1, 2, 3, 4, 5 },
                -1, false,
                { 1, 2, 3, 4, 5 },
                5, true,
                { 1, 2, 3, 4 },
                1, true,
                { 2, 3, 4 },
                3, true,
                { 2, 4 }
        );

        if ( allOk && ! status ) {
            allOk = false;
        }
    });

    return allOk;
}
