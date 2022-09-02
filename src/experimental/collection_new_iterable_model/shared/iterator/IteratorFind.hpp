/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_ITERATOR_FIND_HPP__
#define __CDS_SHARED_ITERATOR_FIND_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @brief Function used to find the elements that are also found in the given parameter iterable, until it has found a certain number of elements, specified in the 'count' parameter. Returns elements locations via iterators in a given collection.
                 * @tparam __ElementType is the type enclosed in the range
                 * @tparam __IteratorType is the type of iterator expected to indicate to located elements
                 * @tparam __IterableType is the type of iterable given as parameter, containing elements to be found of
                 * @tparam __CollectionType is the type of collection to return the found iterators in
                 * @tparam __containsFunction is the function used to check whether the given iterable contains a certain element of the range
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] count : Size = Maximum number of elements to find
                 * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                 * @param [in] from : __IterableType cref = Constant Reference to locate the elements into
                 * @exceptsafe
                 * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                 *
                 * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                 *      CTC-00701-FO-findOfStoreInMatchingNone,
                 *      CTC-00702-FO-findOfStoreInMatchingOne,
                 *      CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit,
                 *      CTC-00704-FO-findOfStoreInMatchingMore,
                 *      CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit,
                 *      CTC-00706-FO-findOfStoreInMatchingAll,
                 *      CTC-00707-FO-findOfStoreInMatchingAllAndMore,
                 *      CTC-00708-FO-findOfReturnedMatchingNone,
                 *      CTC-00709-FO-findOfReturnedMatchingOne,
                 *      CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit,
                 *      CTC-00711-FO-findOfReturnedMatchingMore,
                 *      CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit,
                 *      CTC-00713-FO-findOfReturnedMatchingAll,
                 *      CTC-00714-FO-findOfReturnedMatchingAllAndMore,
                 *      CTC-00735-FO-findNotOfStoreInMatchingNone,
                 *      CTC-00736-FO-findNotOfStoreInMatchingOne,
                 *      CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit,
                 *      CTC-00738-FO-findNotOfStoreInMatchingMore,
                 *      CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit,
                 *      CTC-00740-FO-findNotOfStoreInMatchingAll,
                 *      CTC-00741-FO-findNotOfStoreInMatchingAllAndMore,
                 *      CTC-00742-FO-findNotOfReturnedMatchingNone,
                 *      CTC-00743-FO-findNotOfReturnedMatchingOne,
                 *      CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit,
                 *      CTC-00745-FO-findNotOfReturnedMatchingMore,
                 *      CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit,
                 *      CTC-00747-FO-findNotOfReturnedMatchingAll,
                 *      CTC-00748-FO-findNotOfReturnedMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                         __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findOf (                                /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

                /**
                 * @brief Function used to find the first element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'end' value.
                 * @tparam __ElementType is the type enclosed in the range
                 * @tparam __IteratorType is the type of iterator expected to indicate to located elements
                 * @tparam __IterableType is the type of iterable given as parameter, containing elements to be found of
                 * @tparam __containsFunction is the function used to check whether the given iterable contains a certain element of the range
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] from : __IterableType cref = Constant Reference to locate the elements into
                 * @exceptsafe
                 * @return __IteratorType = The Iterator pointing to said element, if found. 'end' otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                 *      CTC-00715-FO-findFirstOfMatchingNone,
                 *      CTC-00716-FO-findFirstOfMatchingOne,
                 *      CTC-00717-FO-findFirstOfMatchingMore,
                 *      CTC-00718-FO-findFirstOfMatchingAll,
                 *      CTC-00719-FO-findFirstOfMatchingAllAndMore,
                 *      CTC-00749-FO-findFirstNotOfMatchingNone,
                 *      CTC-00750-FO-findFirstNotOfMatchingOne,
                 *      CTC-00751-FO-findFirstNotOfMatchingMore,
                 *      CTC-00752-FO-findFirstNotOfMatchingAll,
                 *      CTC-00753-FO-findFirstNotOfMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findFirstOf (           /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;


                /**
                 * @brief Function used to find the last element that is found in the given parameter iterable. Returns element location via iterator, if found. Otherwise, returns same as given 'end' value.
                 * @tparam __ElementType is the type enclosed in the range
                 * @tparam __IteratorType is the type of iterator expected to indicate to located elements
                 * @tparam __IterableType is the type of iterable given as parameter, containing elements to be found of
                 * @tparam __containsFunction is the function used to check whether the given iterable contains a certain element of the range
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] from : __IterableType cref = Constant Reference to locate the elements into
                 * @exceptsafe
                 * @return __IteratorType = The Iterator pointing to said element, if found. 'end' otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                 *      CTC-00720-FO-findLastOfMatchingNone,
                 *      CTC-00721-FO-findLastOfMatchingOne,
                 *      CTC-00722-FO-findLastOfMatchingMore,
                 *      CTC-00723-FO-findLastOfMatchingAll,
                 *      CTC-00724-FO-findLastOfMatchingAllAndMore,
                 *      CTC-00754-FO-findLastNotOfMatchingNone,
                 *      CTC-00755-FO-findLastNotOfMatchingOne,
                 *      CTC-00756-FO-findLastNotOfMatchingMore,
                 *      CTC-00757-FO-findLastNotOfMatchingAll,
                 *      CTC-00758-FO-findLastNotOfMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findLastOf (            /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __IterableType                      const & from
                ) noexcept -> __IteratorType;

                /**
                 * @brief Function used to find all the elements that are also found in the given parameter iterable. Returns elements locations via iterators in a given collection
                 * @tparam __ElementType is the type enclosed in the range
                 * @tparam __IteratorType is the type of iterator expected to indicate to located elements
                 * @tparam __IterableType is the type of iterable given as parameter, containing elements to be found of
                 * @tparam __CollectionType is the type of collection to return the found iterators in
                 * @tparam __containsFunction is the function used to check whether the given iterable contains a certain element of the range
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                 * @param [in] from : __IterableType cref = Constant Reference to locate the elements into
                 * @exceptsafe
                 * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                 *
                 * @test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
                 *      CTC-00725-FO-findAllOfStoreInMatchingNone,
                 *      CTC-00726-FO-findAllOfStoreInMatchingOne,
                 *      CTC-00727-FO-findAllOfStoreInMatchingMore,
                 *      CTC-00728-FO-findAllOfStoreInMatchingAll,
                 *      CTC-00729-FO-findAllOfStoreInMatchingAllAndMore,
                 *      CTC-00730-FO-findAllOfReturnedMatchingNone,
                 *      CTC-00731-FO-findAllOfReturnedMatchingOne,
                 *      CTC-00732-FO-findAllOfReturnedMatchingMore,
                 *      CTC-00733-FO-findAllOfReturnedMatchingAll,
                 *      CTC-00734-FO-findAllOfReturnedMatchingAllAndMore,
                 *      CTC-00759-FO-findAllNotOfStoreInMatchingNone,
                 *      CTC-00760-FO-findAllNotOfStoreInMatchingOne,
                 *      CTC-00761-FO-findAllNotOfStoreInMatchingMore,
                 *      CTC-00762-FO-findAllNotOfStoreInMatchingAll,
                 *      CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore,
                 *      CTC-00764-FO-findAllNotOfReturnedMatchingNone,
                 *      CTC-00765-FO-findAllNotOfReturnedMatchingOne,
                 *      CTC-00766-FO-findAllNotOfReturnedMatchingMore,
                 *      CTC-00767-FO-findAllNotOfReturnedMatchingAll,
                 *      CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                __IterableType,     /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class                         __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        __ContainsFunction < __IterableType, __ElementType >    __containsFunction  /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_cpplang_ConstexprConditioned auto __findAllOf (                             /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __IterableType                      const & from
                ) noexcept -> __CollectionType < __IteratorType > &;

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_FIND_HPP__ */
