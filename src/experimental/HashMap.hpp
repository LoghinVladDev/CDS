//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_HASH_MAP_HPP__
#define __CDS_EX_HASH_MAP_HPP__

#include <CDS/experimental/Map>
#include "map/baseMap/BaseMap.hpp"
#include <CDS/HashSet>
#include <CDS/Array>

#include "map/entryArray/EntryArray.hpp"
#include "map/entryArray/Associator.hpp"
#include "hashMap/Associator.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                typename __HashCalculator = cds :: utility :: MediumCollisionDefaultHashFunction < __KeyType > // NOLINT(bugprone-reserved-identifier)
        > class HashMap : public __hidden :: __impl :: __BaseMap <
                __KeyType,
                __ValueType,
                cds :: experimental :: HashSet < __KeyType, __HashCalculator >,
                cds :: experimental :: __hidden :: __impl :: __EntryArray < __ValueType >,
                cds :: experimental :: __hidden :: __impl :: __HashEntryArrayAssociator < __KeyType, __ValueType, __HashCalculator >
        > {

        };
    }
}

#include "map/baseMap/impl/BaseMap.hpp"
#include "map/entryArray/impl/Associator.hpp"
#include "hashMap/impl/Associator.hpp"


#endif // __CDS_EX_HASH_MAP_HPP__
