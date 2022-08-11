//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_SHARED_NODE_HPP__
#define __CDS_SHARED_NODE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces,bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            /**
             * @note Mandatory - Element is the first value of the type !!!
             */
            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            struct __UnidirectionalNode { // NOLINT(bugprone-reserved-identifier)
                __ElementType          _data;
                __UnidirectionalNode * _pNext;
            };


            /**
             * @note Mandatory - Element is the first value of the type !!!
             */
            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            struct __BidirectionalNode { // NOLINT(bugprone-reserved-identifier)
                __ElementType           _data;
                __BidirectionalNode   * _pNext;
                __BidirectionalNode   * _pPrevious;
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            struct __RBTreeNode {       // NOLINT(bugprone-reserved-identifier)
                enum __Colour { BLACK, RED };   // NOLINT(bugprone-reserved-identifier)
                __ElementType           _data;
                __Colour                _colour;
                __RBTreeNode          * _pLeft;
                __RBTreeNode          * _pRight;
                __RBTreeNode          * _pParent;
            };
        }
    }

}

#endif // __CDS_SHARED_NODE_HPP__
