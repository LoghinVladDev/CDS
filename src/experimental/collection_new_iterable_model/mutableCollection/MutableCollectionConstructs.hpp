/*
 * Created by loghin on 08/07/22.
 */

#ifndef __CDS_EX_MUTABLE_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionDelegateForwardIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionDelegateForwardIterableClient < __ElementType >;


                template < typename __ElementType >                                                                        /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionRandomInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                          /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionFindOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                               /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionFindOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionFindByClient < __ElementType >;


                template < typename __ElementType >                                                                           /* NOLINT(bugprone-reserved-identifier) */
                using __MutableCollectionGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __MutableCollectionGenericStatementsClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ */
