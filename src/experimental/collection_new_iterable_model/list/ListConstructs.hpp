/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_EX_LIST_CONSTRUCTS_HPP__
#define __CDS_EX_LIST_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ListDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListDelegateForwardIterableClient < __ElementType >;

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ListDelegateBackwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListDelegateBackwardIterableClient < __ElementType >;

                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ListDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListDelegateForwardConstIterableClient < __ElementType >;

                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ListDelegateBackwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListDelegateBackwardConstIterableClient < __ElementType >;

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ListBoundaryInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListBoundaryInsertionClient < __ElementType >;

                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ListIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIteratorRelativeInsertionClient < __ElementType >;

                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __ListConstIteratorRelativeInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListConstIteratorRelativeInsertionClient < __ElementType >;

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ListIndexedOperationsClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIndexedOperationsClient < __ElementType >;

                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ListReplaceClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListReplaceClient < __ElementType >;

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ListReplaceOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListReplaceOfCollectionClient < __ElementType >;

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ListReplaceOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListReplaceOfInitializerListClient < __ElementType >;

                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ListReplaceByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListReplaceByClient < __ElementType >;

                template < typename __ElementType >                                                       /* NOLINT(bugprone-reserved-identifier) */
                using __ListIndicesClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIndicesClient < __ElementType >;

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __ListIndicesOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIndicesOfCollectionClient < __ElementType >;

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __ListIndicesOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIndicesOfInitializerListClient < __ElementType >;

                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __ListIndicesByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ListIndicesByClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_LIST_CONSTRUCTS_HPP__ */
