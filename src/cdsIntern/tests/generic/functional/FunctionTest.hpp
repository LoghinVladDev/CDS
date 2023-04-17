//
// Created by vlad.loghin on 17.04.23.
//

#ifndef CDS_FUNCTIONTEST_HPP
#define CDS_FUNCTIONTEST_HPP

#define CDS_TEST_EXPERIMENTAL

#include "../Test.h"

namespace glob {
    class FunctionTest : public Test {
    public:
        bool execute () noexcept override;
    };
}


#endif /* CDS_FUNCTIONTEST_HPP */
