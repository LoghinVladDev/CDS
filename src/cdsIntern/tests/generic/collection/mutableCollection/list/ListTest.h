/*
 * Created by loghin on 18/09/22.
 */

#ifndef __CDS_LIST_TEST_H__
#define __CDS_LIST_TEST_H__

#include "../../../Test.h"

namespace glob {
    class ListTest : public Test {
    public:
        auto execute () noexcept -> bool override;
    private:
        bool tests_00100_00199 () noexcept;
        bool tests_00200_00299 () noexcept;
        bool tests_00300_00399 () noexcept;
        bool tests_00400_00599 () noexcept;
    };
}

#endif
