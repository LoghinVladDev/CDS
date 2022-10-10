/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_COLLECTION_CONSTRUCTS_HPP__
#define __CDS_EX_COLLECTION_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_OptimalInline auto __collectionContains (  /* NOLINT(bugprone-reserved-identifier) */
                            Collection < __ElementType >    const & collection,
                            __ElementType                   const & element
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl :: __collectionContains < __ElementType > ( collection, element );
                }


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_OptimalInline auto __collectionNotContains (   /* NOLINT(bugprone-reserved-identifier) */
                            Collection < __ElementType >    const & collection,
                            __ElementType                   const & element
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl :: __collectionNotContains < __ElementType > ( collection, element );
                }


                template <
                        typename __ElementType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __function                                                  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_OptimalInline auto __initializerListContains (   /* NOLINT(bugprone-reserved-identifier) */
                            std :: initializer_list < __ElementType >   const & list,
                            __ElementType                               const & element
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl ::__initializerListContains < __ElementType, __function > ( list, element );
                }


                template <
                        typename __ElementType,                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __function                                                      /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_OptimalInline auto __initializerListNotContains (    /* NOLINT(bugprone-reserved-identifier) */
                            std :: initializer_list < __ElementType >   const & list,
                            __ElementType                               const & element
                ) noexcept -> bool {

                    return cds :: __hidden :: __impl ::__initializerListContains < __ElementType, __function > ( list, element );
                }


                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionCommunicationChannel __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionCommunicationChannel < __ElementType >;


                template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionDelegateForwardConstIterableClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionConstIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionConstIteratorRemoveClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionRandomInsertionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionContainsOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionContainsOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionFindOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionFindOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionFindByClient < __ElementType >;


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionRemoveOfCollectionClient < __ElementType >;


                template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionRemoveOfInitializerListClient < __ElementType >;


                template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionRemoveByClient < __ElementType >;


                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __CollectionGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __CollectionGenericStatementsClient < __ElementType >;

            }
        }
    }
}

#endif /* __CDS_EX_COLLECTION_CONSTRUCTS_HPP__ */
