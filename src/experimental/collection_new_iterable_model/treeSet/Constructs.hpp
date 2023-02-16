/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_EX_TREE_SET_CONSTRUCTS_HPP__
#define __CDS_EX_TREE_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") auto __treeSetKeyExtractor ( /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return cds :: __hidden :: __impl :: __treeSetKeyExtractor ( element );
                }


                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") auto __treeSetDestructor (   /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType & element
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __treeSetDestructor ( element );
                }


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") auto __treeSetCopyConstructor (  /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __treeSetCopyConstructor ( destination, source );
                }


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetImplementation < __ElementType >;


                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetDispatcher < __ElementType >;


                template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetServer __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetServer < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetDelegateForwardConstIterableClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetDelegateBackwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetDelegateBackwardConstIterableClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetConstIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetRandomInsertionClient < __ElementType >;

                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetFindUniqueClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetContainsOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetContainsOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetFindOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetFindOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetFindByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetRemoveOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetRemoveOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetRemoveByClient < __ElementType >;


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __TreeSetGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __TreeSetGenericStatementsClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_TREE_SET_CONSTRUCTS_HPP__ */
