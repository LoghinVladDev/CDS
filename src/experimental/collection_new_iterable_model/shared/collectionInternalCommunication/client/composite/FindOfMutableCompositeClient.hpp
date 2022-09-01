/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorFind.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @interface Interface for calling findOf statements - of / firstOf / lastOf / allOf / notOf / firstNotOf / lastNotOf / allNotOf
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient, or provide
                 * a set of equivalent member functions provided by said client - 'begin' / 'end'
                 * @tparam __ElementType is the type of elements contained in the object
                 * @tparam __IteratorType is the type of iterator to be returned by the functions
                 * @tparam __FromIterableType is the type of iterator expected as the main look-into parameter to the functions
                 * @tparam __containsFunction is the function used to check if a given element is contained by the main look-into parameter to the functions
                 * @tparam __notContainsFunction is the function used to check if a given element is not contained by the main look-into parameter to the functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                 * as __FindOfImmutableCompositeClient, which is tested
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
                > class __FindOfMutableCompositeClient {                                                    /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef Private definition for __IteratorType template parameter
                     * @private
                     */
                    using Iterator = __IteratorType;

                public:
                    /**
                     * @brief Function used to find the elements that are also found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a given collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [out] storeIn : __CollectionType \< Iterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findOf (
                            Size                                        count,
                            __CollectionType < Iterator >             & storeIn,
                            __FromIterableType                  const & from
                    ) noexcept -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find the elements that are also found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a newly created collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> = The new collection containing found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> __CollectionType < Iterator >;

                public:
                    /**
                     * @brief Function used to find the first element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as 'end()'.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return Iterator = The Iterator pointing to said element, if found. 'end()' otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findFirstOf (
                            __FromIterableType const & from
                    ) noexcept -> Iterator;

                public:
                    /**
                     * @brief Function used to find the last element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'end()' value.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return Iterator = The Iterator pointing to said element, if found. 'end()' otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findLastOf (
                            __FromIterableType const & from
                    ) noexcept -> Iterator;

                public:
                    /**
                     * @brief Function used to find all the elements that are also found in the given parameter iterable. Returns elements locations via iterators in a given collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [out] storeIn : __CollectionType \< Iterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findAllOf (
                            __CollectionType < Iterator >             & storeIn,
                            __FromIterableType                  const & from
                    ) noexcept -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find all the elements that are also found in the given parameter iterable. Returns elements locations via iterators in a newly created collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> = The new collection containing found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findAllOf (
                            __FromIterableType const & from
                    ) noexcept -> __CollectionType < Iterator >;

                public:
                    /**
                     * @brief Function used to find the elements that are not found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a given collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [out] storeIn : __CollectionType \< Iterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findNotOf (
                            Size                                        count,
                            __CollectionType < Iterator >             & storeIn,
                            __FromIterableType                  const & from
                    ) noexcept -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find the elements that are not found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a newly created collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> = The new collection containing found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findNotOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) noexcept -> __CollectionType < Iterator >;

                public:
                    /**
                     * @brief Function used to find the first element that is not found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as 'end()'.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return Iterator = The Iterator pointing to said element, if found. 'end()' otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findFirstNotOf (
                            __FromIterableType const & from
                    ) noexcept -> Iterator;

                public:
                    /**
                     * @brief Function used to find the last element that is not found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'end()' value.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return Iterator = The Iterator pointing to said element, if found. 'end()' otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findLastNotOf (
                            __FromIterableType const & from
                    ) noexcept -> Iterator;

                public:
                    /**
                     * @brief Function used to find all the elements that are not found in the given parameter iterable. Returns elements locations via iterators in a given collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [out] storeIn : __CollectionType \< Iterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findAllNotOf (
                            __CollectionType < Iterator >             & storeIn,
                            __FromIterableType                  const & from
                    ) noexcept -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find all the elements that are not found in the given parameter iterable. Returns elements locations via iterators in a newly created collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< Iterator \> = The new collection containing found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindOfMutableCompositeClient uses the same base implementation functions
                     * as __FindOfImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findAllNotOf (
                            __FromIterableType const & from
                    ) noexcept -> __CollectionType < Iterator >;
                };


                /**
                 * @typedef Variant of the FindOfMutableCompositeClient, only alias due to it being a composite client
                 * -> will use primitive local clients, making it a local client
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient, or provide
                 * a set of equivalent member functions provided by said client - 'begin' / 'end'
                 * @tparam __ElementType is the type of elements contained in the object
                 * @tparam __IteratorType is the type of iterator to be returned by the functions
                 * @tparam __FromIterableType is the type of iterator expected as the main look-into parameter to the functions
                 * @tparam __containsFunction is the function used to check if a given element is contained by the main look-into parameter to the functions
                 * @tparam __notContainsFunction is the function used to check if a given element is not contained by the main look-into parameter to the functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                    __IterableType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __IteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                    __FromIterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __FromIterableType, __ElementType >    __notContainsFunction   /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindOfMutableCompositeClient =                                               /* NOLINT(bugprone-reserved-identifier) */
                        __FindOfMutableCompositeClient <
                                __IterableType,
                                __ElementType,
                                __IteratorType,
                                __FromIterableType,
                                __containsFunction,
                                __notContainsFunction
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorFind.hpp"

#endif /* __CDS_SHARED_FIND_OF_MUTABLE_COMPOSITE_CLIENT_HPP__ */
