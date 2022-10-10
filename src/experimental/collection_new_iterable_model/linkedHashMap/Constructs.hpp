/*
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__
#define __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __CDS_DeprecatedHint("No longer an experimental feature.") __linkedHashMapKeyExtractor (   /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & element
                ) noexcept -> __KeyType const & {

                    return cds :: __hidden :: __impl :: __linkedHashMapKeyExtractor < __KeyType, __ValueType > ( element );
                }


                template <
                        typename __KeyType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapCopyConstructor (  /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                        typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __linkedHashMapCopyConstructor < __KeyType, __ValueType > ( destinationDataNode, sourceDataNode );
                }


                template <
                        typename __KeyType,                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashMapDestructor (   /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & entry
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __linkedHashMapDestructor < __KeyType, __ValueType > ( entry );
                }


                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __linkedHashMapEquals ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry,
                        typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl :: __linkedHashMapEquals < __KeyType, __ValueType > ( leftEntry, rightEntry );
                }


                template <
                        typename __DecoratedIteratorType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __linkedHashMapIteratorDecoratorValueAt (   /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return cds :: __hidden :: __impl :: __linkedHashMapIteratorDecoratorValueAt < __DecoratedIteratorType, __ValueAtType >;
                }


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapHashTableImplementation __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapHashTableImplementation < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapLinkedListImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapLinkedListImplementation < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapIterator __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapIterator < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstIterator __CDS_DeprecatedHint("No longer an experimental feature.") =               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapConstIterator < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapServer __CDS_DeprecatedHint("No longer an experimental feature.") =                      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapServer < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindByClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfConstCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindOfConstInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindByConstClient __CDS_DeprecatedHint("No longer an experimental feature.") =                   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindByConstClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapFindUniqueConstClient __CDS_DeprecatedHint("No longer an experimental feature.") =               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =                      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapRemoveByClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =             /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapConstGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =          /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LinkedHashMapDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher >;

            }
        }

    }
}

#endif /* __CDS_EX_LINKED_HASH_MAP_CONSTRUCTS_HPP__ */
