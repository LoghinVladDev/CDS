/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_LINKED_HASH_MAP_HPP__
#define __CDS_EX_LINKED_HASH_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/LinkedHashMap>

#include <CDS/experimental/Map>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../shared/Node.hpp"
#include "../../shared/rehashPolicy/rehashPolicy.hpp"

#include "shared/iterator/HashTableIterator.hpp"
#include "shared/iterator/NodeIterator.hpp"
#include "shared/iterator/IteratorGenericDecorator.hpp"

#include "shared/collectionInternalCommunication/server/MapServerDispatcher.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "shared/hashTable/HashTable.hpp"
#include "shared/linkedList/SingleLinkedList.hpp"

#include "shared/collectionInternalCommunication/server/SetServer.hpp"
#include "shared/collectionInternalCommunication/server/MapServer.hpp"

#include "linkedHashMap/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
        using LinkedHashMap __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: LinkedHashMap < __KeyType, __ValueType, __Hasher >;

    }
}

#endif /* __CDS_EX_LINKED_HASH_MAP_HPP__ */
