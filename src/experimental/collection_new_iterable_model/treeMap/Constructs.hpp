/*
 * Created by stefan on 10.10.2022.
 */

#ifndef __CDS_EX_TREE_MAP_CONSTRUCTS_HPP__
#define __CDS_EX_TREE_MAP_CONSTRUCTS_HPP__     /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __treeMapKeyExtractor ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & value
                ) noexcept -> __KeyType const & {

                    return cds :: __hidden :: __impl :: __treeMapKeyExtractor ( value );
                }


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") auto __treeMapCopyConstructor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & destination,
                        typename Map < __KeyType, __ValueType > :: EntryType const & source
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __treeMapCopyConstructor ( destination, source );
                }


                template <
                        typename __KeyType,                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                            /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") auto __treeMapDestructor ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & element
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __treeMapDestructor ( element );
                }


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapImplementation < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapDispatcher < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapServer __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapServer < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapDelegateForwardIterableClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapDelegateBackwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapDelegateBackwardIterableClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapDelegateForwardConstIterableClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapDelegateBackwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapDelegateBackwardConstIterableClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapIteratorRemoveClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapConstIteratorRemoveClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindUniqueClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindUniqueConstClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindUniqueConstClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapRandomInsertionClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapContainsOfCollectionClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapContainsOfInitializerListClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindByClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindByConstClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindByConstClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindOfCollectionClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindOfInitializerListClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindOfConstCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindOfConstCollectionClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapFindOfConstInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapFindOfConstInitializerListClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapGenericStatementsClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapConstGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapConstGenericStatementsClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapRemoveByClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapRemoveOfCollectionClient < __KeyType, __ValueType >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > using __TreeMapRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeMapRemoveOfInitializerListClient < __KeyType, __ValueType >;

            }
        }
    }
}

#endif /* __CDS_EX_TREE_MAP_CONSTRUCTS_HPP__ */
