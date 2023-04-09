/*
 * Created by loghin on 04/09/22.
 */

#ifndef __CDS_MUTABLE_COLLECTION_TEST_H__
#define __CDS_MUTABLE_COLLECTION_TEST_H__

#include "../../Test.h"

namespace glob {
    class MutableCollectionTest : public Test {
    public:
        auto execute () noexcept -> bool override;
    private:
        bool tests_00000_00099 () noexcept; 
        bool tests_00100_00199 () noexcept; 
        bool tests_00200_00349 () noexcept; 
        bool tests_00350_00399 () noexcept; 
        bool tests_00400_00449 () noexcept; 
        bool tests_00450_00499 () noexcept; 
        bool tests_00600_00699 () noexcept; 
        bool tests_00700_00799 () noexcept; 
        bool tests_00800_00899 () noexcept; 
    };
}

#endif
