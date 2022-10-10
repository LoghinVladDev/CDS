/*
 * Created by loghin on 13/08/22.
 */

#ifndef __CDS_EX_HASH_MAP_CONSTRUCTS_HPP__
#define __CDS_EX_HASH_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __KeyType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __hashMapKeyExtractor ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & element
                ) noexcept -> __KeyType const & {

                    return cds :: __hidden :: __impl :: __hashMapKeyExtractor < __KeyType, __ValueType > ( element );
                }


                template <
                        typename __KeyType,                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapCopyConstructor (    /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType       & destinationDataNode,
                        typename Map < __KeyType, __ValueType > :: EntryType const & sourceDataNode
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __hashMapCopyConstructor < __KeyType, __ValueType > ( destinationDataNode, sourceDataNode );
                }


                template <
                        typename __KeyType,                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __hashMapDestructor ( /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType & entry
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __hashMapDestructor < __KeyType, __ValueType > ( entry );
                }


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType                                                                    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __hashMapEquals (   /* NOLINT(bugprone-reserved-identifier) */
                        typename Map < __KeyType, __ValueType > :: EntryType const & leftEntry,
                        typename Map < __KeyType, __ValueType > :: EntryType const & rightEntry
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl :: __hashMapEquals < __KeyType, __ValueType > ( leftEntry, rightEntry );
                }


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapImplementation < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapDispatcher < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapServer __CDS_DeprecatedHint("No longer an experimental feature.") =            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapServer < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapRandomInsertionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapConstIteratorRemoveClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =                  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindByClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfConstCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindOfConstCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindOfConstInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindOfConstInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindByConstClient __CDS_DeprecatedHint("No longer an experimental feature.") =                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindByConstClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =                  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindUniqueClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapFindUniqueConstClient __CDS_DeprecatedHint("No longer an experimental feature.") =             /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapFindUniqueConstClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =          /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapRemoveOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapRemoveOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =                    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapRemoveByClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =           /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapGenericStatementsClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapConstGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapConstGenericStatementsClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =        /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapContainsOfCollectionClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapContainsOfInitializerListClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapDelegateForwardIterableClient < __KeyType, __ValueType, __Hasher >;


                template <
                        typename __KeyType,                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueType,                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __Hasher                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __HashMapDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashMapDelegateForwardConstIterableClient < __KeyType, __ValueType, __Hasher >;

            }
        }

    }
}

#endif /* __CDS_EX_HASH_MAP_CONSTRUCTS_HPP__ */
