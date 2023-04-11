/*
 * Created by loghin on 18/09/22.
 */

#include "ListTest.h"
#include "ListTest_common.hpp"

/* ListTestSuite-cpp-xx : LTS-00001-cpp-xx */
auto ListTest :: execute () noexcept -> bool {

    return 
            this->tests_00100_00199() &&
            this->tests_00200_00299() &&
            this->tests_00300_00399() &&
            this->tests_00400_00599();
}
