/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_EX_HASH_SET_CONSTRUCTS_HPP__
#define __CDS_EX_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __hashSetKeyExtractor (   /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return cds :: __hidden :: __impl :: __hashSetKeyExtractor < __ElementType > ( element );
                }


                template < typename __ElementType >                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetCopyConstructor (  /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __hashSetCopyConstructor < __ElementType > ( destination, source );
                }


                template < typename __ElementType >                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetDestructor (   /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType & element
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __hashSetDestructor < __ElementType > ( element );
                }


                template < typename __ElementType, typename __Hasher >                                      /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                  /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetDispatcher __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                              /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetServer __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetFindOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                      /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetRemoveOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                      /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                          /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetFindUniqueClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetContainsOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetContainsOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                          /* NOLINT(bugprone-reserved-identifier) */
                using __HashSetDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __HashSetDelegateForwardConstIterableClient < __ElementType, __Hasher >;

            }
        }
    }
}

#endif /* __CDS_EX_HASH_SET_CONSTRUCTS_HPP__ */
