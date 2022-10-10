/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_HASH_SET_HPP__
#define __CDS_EX_HASH_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/HashSet>

#include <CDS/experimental/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../shared/Node.hpp"
#include "../../shared/rehashPolicy/rehashPolicy.hpp"

#include "shared/iterator/HashTableIterator.hpp"

#include "shared/collectionInternalCommunication/server/SetServerDispatcher.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "shared/hashTable/HashTable.hpp"

#include "shared/collectionInternalCommunication/server/SetServer.hpp"

#include "hashSet/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType, typename __Hasher = cds :: WrapperHasher < __ElementType, Hash < __ElementType > > > /* NOLINT(bugprone-reserved-identifier) */
        using HashSet __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: HashSet < __ElementType, __Hasher >;

    }
}

#endif /* __CDS_EX_HASH_SET_HPP__ */
