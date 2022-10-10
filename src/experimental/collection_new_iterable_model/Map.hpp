/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_MAP_HPP__
#define __CDS_EX_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/Map>

#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>

#include "shared/collectionInternalCommunication/client/primitive/FindUniqueMutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/server/MutableCollectionServer.hpp"

#include "../../collection/mutableCollection/map/map/entry/Entry.hpp"

#include "map/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
        using Map __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: Map < __KeyType, __ValueType >;

    }
}

#endif /* __CDS_EX_MAP_HPP__ */
