//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findOf (
                        Size                                        count,
                        __CollectionType < Iterator >             & storeIn,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > & {

                    return __findOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findOf (
                        Size                                        count,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > {

                    return __findOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findFirstOf (
                        __FromIterableType                  const & from
                ) noexcept -> Iterator {

                    return __findFirstOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findLastOf (
                        __FromIterableType                  const & from
                ) noexcept -> Iterator {

                    return __findLastOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllOf (
                        __CollectionType < Iterator >             & storeIn,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > & {

                    return __findAllOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllOf (
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > {

                    return __findAllOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findNotOf (
                        Size                                        count,
                        __CollectionType < Iterator >             & storeIn,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > & {

                    return __findNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findNotOf (
                        Size                                        count,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > {

                    return __findNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            count,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findFirstNotOf (
                        __FromIterableType                  const & from
                ) noexcept -> Iterator {

                    return __findFirstNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findLastNotOf (
                        __FromIterableType                  const & from
                ) noexcept -> Iterator {

                    return __findLastNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllNotOf (
                        __CollectionType < Iterator >             & storeIn,
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > & {

                    return __findAllNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            storeIn,
                            from
                    );
                }


                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > template <
                        template < typename ... > class                             __CollectionType    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __FindOfMutableCompositeClient <
                        __IterableType,
                        __ElementType,
                        __IteratorType,
                        __FromIterableType,
                        __containsFunction
                > :: findAllNotOf (
                        __FromIterableType                  const & from
                ) noexcept -> __CollectionType < Iterator > {

                    return __findAllNotOf <
                            __ElementType,
                            Iterator,
                            __FromIterableType,
                            __CollectionType,
                            __containsFunction
                    > (
                            static_cast < __IterableType * > ( this )->begin(),
                            static_cast < __IterableType * > ( this )->end(),
                            from
                    );
                }

            }
        }
    }
}

#endif // __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
