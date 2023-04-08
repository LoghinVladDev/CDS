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
    };
}

#endif
