/*
 * Created by stefan on 12.09.2022.
 */

#ifndef __CDS_RED_BLACK_TREE_UTILS_HPP__
#define __CDS_RED_BLACK_TREE_UTILS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __RedBlackTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */


                template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                static cds :: __hidden :: __impl :: __allocation :: __RawContainer < __RedBlackTreeNode < __ElementType > > nullNodeMemory; /* NOLINT(bugprone-reserved-identifier) */


                template < typename __ElementType >                                                                /* NOLINT(bugprone-reserved-identifier) */
                static __CDS_OptimalInline auto __endNode () noexcept -> __RedBlackTreeNode < __ElementType > * {  /* NOLINT(bugprone-reserved-identifier) */
                    return & nullNodeMemory < __ElementType > .data();
                }
            }
        }
    }
}

#endif /* __CDS_RED_BLACK_TREE_UTILS_HPP__ */
