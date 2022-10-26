//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_  /* NOLINT(bugprone-reserved-identifier) */
namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */


                template <
                        typename __ServerType,              /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapValueProxyServer =         /* NOLINT(bugprone-reserved-identifier) */
                        __MutableCollectionServer <
                                __ServerType,
                                __ValueType
                        >;


                template <
                        typename __DecoratedIteratorType,                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                                                      /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt (     /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return ( * iterator ).value ();
                }


                template <
                        typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapValueProxyForwardIterator =        /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_Iterator,
                                __ValueType,
                                & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_Iterator,
                                        __ValueType
                                >
                        >;


                template <
                        typename __KeyType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapValueProxyForwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ConstIterator,
                                __ValueType const,
                                & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ConstIterator,
                                        __ValueType const
                                >
                        >;


                template <
                        typename __KeyType,                          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                         /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapValueProxyBackwardIterator =        /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseIterator,
                                __ValueType,
                                & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseIterator,
                                        __ValueType
                                >
                        >;


                template <
                        typename __KeyType,                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                             /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapValueProxyBackwardConstIterator =       /* NOLINT(bugprone-reserved-identifier) */
                        BidirectionalIteratorGenericDecorator <
                                typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseConstIterator,
                                __ValueType const,
                                & __treeMapValueMutableCollectionProxyIteratorDecoratorValueAt <
                                        typename __TreeMapImplementation < __KeyType, __ValueType > :: __rbt_ReverseConstIterator,
                                        __ValueType const
                                >
                        >;
             }
        }

            template <
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
            > class TreeMap <
                    __KeyType,
                    __ValueType
            > :: ValueMutableCollectionProxy :
                    private AbstractValueMutableCollectionProxy,
                    private __hidden :: __impl :: __TreeMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType > {

            };
    }
}
#endif //__CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP_
