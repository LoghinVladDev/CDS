//
// Created by stefan on 10.10.2022.
//

#ifndef __CDS_TREE_MAP_CONSTRUCTS_HPP__
#define __CDS_TREE_MAP_CONSTRUCTS_HPP__     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > class TreeSet;

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __treeMapKeyExtractor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & value
                ) noexcept -> __KeyType const & {

                    return value.key();
                }


                template <
                        typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
                > auto __treeMapDestructor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & element
                ) noexcept -> void {

                    using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;
                    element.~EntryType();
                }


                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapImplementation =   /* NOLINT(bugprone-reserved-identifier) */
                            __RedBlackTree <
                                    typename Map < __KeyType, __ValueType > :: EntryType,
                                    __KeyType,
                                    & __treeMapKeyExtractor < __KeyType, __ValueType >,
                                    & cds :: predicates :: lessThan < __KeyType >,
                                    & cds :: meta :: equals < __KeyType >,
                                    & __treeMapDestructor < __KeyType, __ValueType >
                            >;

                template <
                        typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapServer =           /* NOLINT(bugprone-reserved-identifier) */
                        __MapServer <
                                __TreeMapImplementation <
                                        __KeyType,
                                        __ValueType
                                >,
                                typename Map < __KeyType, __ValueType > :: EntryType
                        >;
            }
        }
    }
}

#endif //__CDS_TREE_MAP_CONSTRUCTS_HPP__
