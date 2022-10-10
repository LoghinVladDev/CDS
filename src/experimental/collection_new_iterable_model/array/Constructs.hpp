/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_EX_ARRAY_CONSTRUCTS_HPP__
#define __CDS_EX_ARRAY_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayImplementation __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayImplementation < __ElementType >;


                template < typename __ElementType >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayDispatcher < __ElementType >;


                template < typename __ElementType >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayServer __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayServer < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayRandomInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayBoundaryInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayBoundaryInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIteratorRelativeInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayConstIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayConstIteratorRelativeInsertionClient < __ElementType >;


                template < typename __ElementType >                                                               /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindConstOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindConstOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindConstOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindConstOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindByClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayFindConstByClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayFindConstByClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayConstIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayRemoveOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayRemoveOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayRemoveByClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayGenericStatementsClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayGenericConstStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayGenericConstStatementsClient < __ElementType >;


                template < typename __ElementType >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayReplaceClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayReplaceClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayReplaceOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayReplaceOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayReplaceOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayReplaceOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayReplaceByClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayReplaceByClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIndexedOperationsClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIndexedOperationsClient < __ElementType >;


                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIndicesClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIndicesClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIndicesOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIndicesOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIndicesOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIndicesOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayIndicesByClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayIndicesByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayContainsOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayContainsOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayDelegateForwardIterableClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayDelegateForwardConstIterableClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayDelegateBackwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayDelegateBackwardIterableClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ArrayDelegateBackwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ArrayDelegateBackwardConstIterableClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_ARRAY_CONSTRUCTS_HPP__ */
