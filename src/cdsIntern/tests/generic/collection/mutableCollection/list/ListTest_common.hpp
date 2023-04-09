/*
 * Created by loghin on 18/09/22.
 */

#ifndef CDS_LIST_TEST_COMMON_H
#define CDS_LIST_TEST_COMMON_H

#include <CDS/Array>
#include <CDS/LinkedList>

#include <initializer_list>
#include <vector>
#include <array>
#include <CDS/Range>

#include "ListTest.h"

namespace {
    using glob::Test;
    using glob::ListTest;


    using cds::Index;
    using cds::Size;

    using cds::String;

    using cds::List;
    using cds::Array;
    using cds::LinkedList;


    template <
            typename T,
            typename V
    > auto equals (T const & t, V const & v) -> bool {

        auto lIt = t.begin();
        auto le = t.end();
        auto rIt = v.begin();
        auto re = v.end();
        for (
                ;   lIt != le && rIt != re; ++ lIt, ++ rIt
                )
            if ( ! cds :: meta :: equals ( * lIt, * rIt ) )
                return false;

        return true;
    }
}

#endif
