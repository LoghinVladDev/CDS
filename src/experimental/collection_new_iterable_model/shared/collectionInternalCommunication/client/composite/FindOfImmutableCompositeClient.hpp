/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorFind.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @interface Interface for calling findOf statements - of / firstOf / lastOf / allOf / notOf / firstNotOf / lastNotOf / allNotOf
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient, or provide
                 * a set of equivalent member functions provided by said client - 'cbegin' / 'cend'
                 * @tparam __ElementType is the type of elements contained in the object
                 * @tparam __IteratorType is the type of iterator to be returned by the functions
                 * @tparam __FromIterableType is the type of iterator expected as the main look-into parameter to the functions
                 * @tparam __containsFunction is the function used to check if a given element is contained by the main look-into parameter to the functions
                 * @tparam __notContainsFunction is the function used to check if a given element is not contained by the main look-into parameter to the functions
                 *
                 * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: All
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
                > class __FindOfImmutableCompositeClient {                                                  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef Private definition for __IteratorType template parameter
                     * @private
                     */
                    using ConstIterator = __IteratorType;

                public:
                    /**
                     * @brief Function used to find the elements that are also found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a given collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [out] storeIn : __CollectionType \< ConstIterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00701-FO-findOfStoreInMatchingNone,
                     *      CTC-00702-FO-findOfStoreInMatchingOne,
                     *      CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit,
                     *      CTC-00704-FO-findOfStoreInMatchingMore,
                     *      CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit,
                     *      CTC-00706-FO-findOfStoreInMatchingAll,
                     *      CTC-00707-FO-findOfStoreInMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findOf (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                public:
                    /**
                     * @brief Function used to find the elements that are also found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a newly created collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> = The new collection containing found iterators
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00708-FO-findOfReturnedMatchingNone,
                     *      CTC-00709-FO-findOfReturnedMatchingOne,
                     *      CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit,
                     *      CTC-00711-FO-findOfReturnedMatchingMore,
                     *      CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit,
                     *      CTC-00713-FO-findOfReturnedMatchingAll,
                     *      CTC-00714-FO-findOfReturnedMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                public:
                    /**
                     * @brief Function used to find the first element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as 'cend()'.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return ConstIterator = The Iterator pointing to said element, if found. 'cend()' otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00715-FO-findFirstOfMatchingNone,
                     *      CTC-00716-FO-findFirstOfMatchingOne,
                     *      CTC-00717-FO-findFirstOfMatchingMore,
                     *      CTC-00718-FO-findFirstOfMatchingAll,
                     *      CTC-00719-FO-findFirstOfMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findFirstOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to find the last element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'cend()' value.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return ConstIterator = The Iterator pointing to said element, if found. 'cend()' otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00720-FO-findLastOfMatchingNone,
                     *      CTC-00721-FO-findLastOfMatchingOne,
                     *      CTC-00722-FO-findLastOfMatchingMore,
                     *      CTC-00723-FO-findLastOfMatchingAll,
                     *      CTC-00724-FO-findLastOfMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findLastOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to find all the elements that are also found in the given parameter iterable. Returns elements locations via iterators in a given collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [out] storeIn : __CollectionType \< ConstIterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00725-FO-findAllOfStoreInMatchingNone,
                     *      CTC-00726-FO-findAllOfStoreInMatchingOne,
                     *      CTC-00727-FO-findAllOfStoreInMatchingMore,
                     *      CTC-00728-FO-findAllOfStoreInMatchingAll,
                     *      CTC-00729-FO-findAllOfStoreInMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findAllOf (
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                public:
                    /**
                     * @brief Function used to find all the elements that are also found in the given parameter iterable. Returns elements locations via iterators in a newly created collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> = The new collection containing found iterators
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00730-FO-findAllOfReturnedMatchingNone,
                     *      CTC-00731-FO-findAllOfReturnedMatchingOne,
                     *      CTC-00732-FO-findAllOfReturnedMatchingMore,
                     *      CTC-00733-FO-findAllOfReturnedMatchingAll,
                     *      CTC-00734-FO-findAllOfReturnedMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findAllOf (
                            __FromIterableType const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                public:
                    /**
                     * @brief Function used to find the elements that are not found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a given collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [out] storeIn : __CollectionType \< ConstIterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00735-FO-findNotOfStoreInMatchingNone,
                     *      CTC-00736-FO-findNotOfStoreInMatchingOne,
                     *      CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit,
                     *      CTC-00738-FO-findNotOfStoreInMatchingMore,
                     *      CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit,
                     *      CTC-00740-FO-findNotOfStoreInMatchingAll,
                     *      CTC-00741-FO-findNotOfStoreInMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findNotOf (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                public:
                    /**
                     * @brief Function used to find the elements that are not found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a newly created collection.
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> = The new collection containing found iterators
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00742-FO-findNotOfReturnedMatchingNone,
                     *      CTC-00743-FO-findNotOfReturnedMatchingOne,
                     *      CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit,
                     *      CTC-00745-FO-findNotOfReturnedMatchingMore,
                     *      CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit,
                     *      CTC-00747-FO-findNotOfReturnedMatchingAll,
                     *      CTC-00748-FO-findNotOfReturnedMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findNotOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                public:
                    /**
                     * @brief Function used to find the first element that is not found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as 'cend()'.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return ConstIterator = The Iterator pointing to said element, if found. 'cend()' otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00749-FO-findFirstNotOfMatchingNone,
                     *      CTC-00750-FO-findFirstNotOfMatchingOne,
                     *      CTC-00751-FO-findFirstNotOfMatchingMore,
                     *      CTC-00752-FO-findFirstNotOfMatchingAll,
                     *      CTC-00753-FO-findFirstNotOfMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findFirstNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to find the last element that is not found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'cend()' value.
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return ConstIterator = The Iterator pointing to said element, if found. 'cend()' otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00754-FO-findLastNotOfMatchingNone,
                     *      CTC-00755-FO-findLastNotOfMatchingOne,
                     *      CTC-00756-FO-findLastNotOfMatchingMore,
                     *      CTC-00757-FO-findLastNotOfMatchingAll,
                     *      CTC-00758-FO-findLastNotOfMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    __CDS_NoDiscard auto findLastNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to find all the elements that are not found in the given parameter iterable. Returns elements locations via iterators in a given collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [out] storeIn : __CollectionType \< ConstIterator \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00759-FO-findAllNotOfStoreInMatchingNone,
                     *      CTC-00760-FO-findAllNotOfStoreInMatchingOne,
                     *      CTC-00761-FO-findAllNotOfStoreInMatchingMore,
                     *      CTC-00762-FO-findAllNotOfStoreInMatchingAll,
                     *      CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    auto findAllNotOf (
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                public:
                    /**
                     * @brief Function used to find all the elements that are not found in the given parameter iterable. Returns elements locations via iterators in a newly created collection
                     * @tparam __CollectionType is the type of collection to return the found iterators in
                     * @param [in] from : __FromIterableType cref = Constant Reference to locate the elements into
                     * @exceptsafe
                     * @return __CollectionType \< ConstIterator \> = The new collection containing found iterators
                     *
                     * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                     *      CTC-00764-FO-findAllNotOfReturnedMatchingNone,
                     *      CTC-00765-FO-findAllNotOfReturnedMatchingOne,
                     *      CTC-00766-FO-findAllNotOfReturnedMatchingMore,
                     *      CTC-00767-FO-findAllNotOfReturnedMatchingAll,
                     *      CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore
                     * }
                     *
                     * @public
                     */
                    template < template < typename ... > class __CollectionType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findAllNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;
                };


                /**
                 * @typedef Variant of the FindOfImmutableCompositeClient, only alias due to it being a composite client
                 * -> will use primitive local clients, making it a local client
                 * Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient, or provide
                 * a set of equivalent member functions provided by said client - 'cbegin' / 'cend'
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
                > using __LocalFindOfImmutableCompositeClient =                                             /* NOLINT(bugprone-reserved-identifier) */
                        __FindOfImmutableCompositeClient <
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

#endif /* __CDS_SHARED_FIND_OF_IMMUTABLE_COMPOSITE_CLIENT_HPP__ */
