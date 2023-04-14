/*
 * Created by loghin on 30.11.2021.
 */

#ifndef CDS_COLLECTIONTEST_H
#define CDS_COLLECTIONTEST_H

#define CDS_TEST_EXPERIMENTAL

#include "../Test.h"

namespace glob {
    class CollectionTest : public Test {
    public:
        bool execute () noexcept override;
    private:
        bool tests_00000_00099 () noexcept;
        bool tests_00100_00299_p1 () noexcept;
        bool tests_00100_00299_p2 () noexcept;
        bool tests_00300_00399 () noexcept;
        bool tests_00400_00449 () noexcept;
        bool tests_00450_00599_p1 () noexcept;
        bool tests_00450_00599_p2 () noexcept;
        bool tests_00450_00599_p3 () noexcept;
        bool tests_00600_00699 () noexcept;
        bool tests_00700_00799_p1 () noexcept;
        bool tests_00700_00799_p2 () noexcept;
        bool tests_00800_00899 () noexcept;
    };
}


#endif /* CDS_COLLECTIONTEST_H */
