//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_SET_HPP__
#define __CDS_EX_SET_HPP__

#include <CDS/experimental/Collection>

#include <CDS/experimental/Collection>

#include "set/Constructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf < cds :: experimental :: meta :: isValidSetElement < __ElementType > () > = 0
        > class Set : public Collection < __ElementType > {

        };

    }
}

#endif // __CDS_EX_SET_HPP__
