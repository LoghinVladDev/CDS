/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_EX_LINKED_LIST_HPP__
#define __CDS_EX_LINKED_LIST_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/LinkedList>

#include <CDS/experimental/List>

#include "../../shared/Node.hpp"

#include "shared/iterator/NodeIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServerDispatcher.hpp"
#include "shared/collectionInternalCommunication/server/ListServer.hpp"

#include "shared/linkedList/DoubleLinkedList.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "linkedList/Constructs.hpp"


namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using LinkedList __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: LinkedList < __ElementType >;

    }
}

#endif /* __CDS_EX_LINKED_LIST_HPP__ */
