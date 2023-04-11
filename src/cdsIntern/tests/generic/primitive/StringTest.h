/*
 * Created by loghin on 05.04.2021.
 */

#ifndef CDS_STRINGTEST_H
#define CDS_STRINGTEST_H

#define CDS_TEST_EXPERIMENTAL

#include "../Test.h"

namespace glob {
    class StringTest : public Test {
    public:
        bool execute() noexcept override;
    };
}


#endif /* CDS_STRINGTEST_H */
