/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_EX_TREE_SET_HPP__
#define __CDS_EX_TREE_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/TreeSet>

#include <CDS/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>
#include <CDS/Function>

#include "../../shared/Node.hpp"
#include "../../shared/impl/generalPredicates.hpp"

#include "shared/iterator/RedBlackTreeIterator.hpp"

#include "shared/collectionInternalCommunication/server/TreeSetServerDispatcher.hpp"

#include "shared/redBlackTree/RedBlackTree.hpp"

#include "../../shared/collectionInternalCommunication/client/primitive/DelegateBackwardConstIterablePrimitiveClient.hpp"

#include "../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../shared/collectionInternalCommunication/server/SetServer.hpp"

#include "treeSet/Constructs.hpp"

namespace cds {                             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using TreeSet __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: TreeSet < __ElementType >;

    }
}



#endif /* __CDS_EX_TREE_SET_HPP__ */
