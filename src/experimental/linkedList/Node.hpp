//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_NODE_HPP__
#define __CDS_LINKED_LIST_NODE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        struct LinkedList < T > :: Node {
            ElementType * _pData;
            Node        * _pNext;
            Node        * _pPrevious;
        };

    }
}

#endif // __CDS_LINKED_LIST_NODE_HPP__
