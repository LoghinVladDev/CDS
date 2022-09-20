/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_SHARED_NODE_HPP__
#define __CDS_SHARED_NODE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces,bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @note Mandatory - Element is the first value of the type !!!
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            struct __UnidirectionalNode {       /* NOLINT(bugprone-reserved-identifier) */
                __ElementType          _data;
                __UnidirectionalNode * _pNext;
            };


            /**
             * @note Mandatory - Element is the first value of the type !!!
             */
            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            struct __BidirectionalNode {        /* NOLINT(bugprone-reserved-identifier) */
                __ElementType           _data;
                __BidirectionalNode   * _pNext;
                __BidirectionalNode   * _pPrevious;
            };


            enum class __RedBlackTreeNodeColour {   /* NOLINT(bugprone-reserved-identifier) */
                __rbtnc_Black,                      /* NOLINT(bugprone-reserved-identifier) */
                __rbtnc_Red                         /* NOLINT(bugprone-reserved-identifier) */
            };


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            struct __RedBlackTreeNode {         /* NOLINT(bugprone-reserved-identifier) */
                __ElementType               _data;
                __RedBlackTreeNodeColour    _colour;
                __RedBlackTreeNode        * _pLeft;
                __RedBlackTreeNode        * _pRight;
                __RedBlackTreeNode        * _pParent;
            };
        }
    }

}

#endif /* __CDS_SHARED_NODE_HPP__ */
