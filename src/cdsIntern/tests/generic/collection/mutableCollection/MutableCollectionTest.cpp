/*
 * Created by loghin on 04/09/22.
 */

#include "MutableCollectionTest.h"
#include "MutableCollectionTest_common.hpp"


/* MutableCollectionTestSuite-cpp-xx : MCTS-00001-cpp-xx */
auto MutableCollectionTest :: execute () noexcept -> bool {

    return 
            this->tests_00000_00099 () &&
            this->tests_00100_00199 () &&
            this->tests_00200_00349 () &&
            this->tests_00350_00399 () &&
            this->tests_00400_00449 () &&
            this->tests_00450_00499_i () &&
            this->tests_00450_00499_s () &&
            this->tests_00600_00699 () &&
            this->tests_00700_00799 () &&
            this->tests_00800_00899 ();
}
