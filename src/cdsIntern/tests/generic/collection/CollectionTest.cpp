/*
 * Created by loghin on 30.11.2021.
 */

#include "CollectionTest.h"
#include "CollectionTest_common.hpp"

/* CollectionTestSuite-cpp-xx : CTS-00001-cpp-xx */
auto CollectionTest :: execute () noexcept -> bool {

    return 
            this->tests_00000_00099 () &&
            this->tests_00100_00299_p1 () &&
            this->tests_00100_00299_p2 () &&
            this->tests_00300_00399 () &&
            this->tests_00400_00449 () &&
            this->tests_00450_00599_p1 () &&
            this->tests_00450_00599_p2 () &&
            this->tests_00450_00599_p3 () &&
            this->tests_00600_00699 () &&
            this->tests_00700_00799_p1 () &&
            this->tests_00700_00799_p2 () &&
            this->tests_00800_00899 ();
}
