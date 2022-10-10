/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_EX_LINKED_LIST_CONSTRUCTS_HPP__
#define __CDS_EX_LINKED_LIST_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListImplementation < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListDispatcher < __ElementType >;


                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListServer __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListServer < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListRandomInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListBoundaryInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListBoundaryInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIteratorRelativeInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListConstIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListConstIteratorRelativeInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindConstOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindConstOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindConstOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindConstOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindByClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListFindConstByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListFindConstByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListConstIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListRemoveOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListRemoveOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListRemoveByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListGenericStatementsClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListGenericConstStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListGenericConstStatementsClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListReplaceClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListReplaceClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListReplaceOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListReplaceOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListReplaceOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListReplaceOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListReplaceByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListReplaceByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIndexedOperationsClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIndexedOperationsClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIndicesClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIndicesClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIndicesOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIndicesOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIndicesOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIndicesOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListIndicesByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListIndicesByClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListContainsOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListContainsOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListDelegateForwardIterableClient < __ElementType >;


                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListDelegateForwardConstIterableClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListDelegateBackwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListDelegateBackwardIterableClient < __ElementType >;


                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedListDelegateBackwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedListDelegateBackwardConstIterableClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_LINKED_LIST_CONSTRUCTS_HPP__ */
