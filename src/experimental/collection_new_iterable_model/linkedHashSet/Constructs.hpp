/*
 * Created by loghin on 02/10/22.
 */

#ifndef __CDS_EX_LINKED_HASH_SET_CONSTRUCTS_HPP__
#define __CDS_EX_LINKED_HASH_SET_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __linkedHashSetKeyExtractor ( /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return cds :: __hidden :: __impl :: __linkedHashSetKeyExtractor < __ElementType > ( element );
                }


                template < typename __ElementType >                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetCopyConstructor (    /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __linkedHashSetCopyConstructor < __ElementType > ( destination, source );
                }


                template < typename __ElementType >                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                __CDS_DeprecatedHint("No longer an experimental feature.") __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetDestructor ( /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType & element
                ) noexcept -> void {

                    cds :: __hidden :: __impl :: __linkedHashSetDestructor < __ElementType > ( element );
                }


                template <
                        typename __DecoratedIteratorType,                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __ValueAtType                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") constexpr auto __linkedHashSetIteratorDecoratorValueAt (   /* NOLINT(bugprone-reserved-identifier) */
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return cds :: __hidden :: __impl :: __linkedHashSetIteratorDecoratorValueAt < __DecoratedIteratorType, __ValueAtType > ( iterator );
                }


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetHashTableImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetHashTableImplementation < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetLinkedListImplementation __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetIterator __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetIterator < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetServer __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetServer < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetRandomInsertionClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetRandomInsertionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetIteratorRemoveClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetIteratorRemoveClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetFindOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetFindOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                          /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetFindOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetFindOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                          /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetFindByClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetFindByClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetRemoveOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetRemoveOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                          /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetRemoveOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetRemoveByClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetRemoveByClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                      /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetGenericStatementsClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetGenericStatementsClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                              /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetFindUniqueClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetFindUniqueClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                          /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetContainsOfCollectionClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetContainsOfCollectionClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                              /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetContainsOfInitializerListClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetContainsOfInitializerListClient < __ElementType, __Hasher >;


                template < typename __ElementType, typename __Hasher >                                                                  /* NOLINT(bugprone-reserved-identifier) */
                using __LinkedHashSetDelegateForwardConstIterableClient __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LinkedHashSetDelegateForwardConstIterableClient < __ElementType, __Hasher >;

            }
        }

    }
}

#endif /* __CDS_EX_LINKED_HASH_SET_CONSTRUCTS_HPP__ */
