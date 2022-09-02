/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__
#define __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a given collection, until a given limit has been reached, at which point the iteration will stop. This is the predicate = callable variant
                 * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
                 * @tparam __CollectionType is the type of template iterable to store the iterators in
                 * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] count : Size = Maximum number of elements to find
                 * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                 * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                 * @exceptsafe if __Predicate callable / member function is exceptsafe
                 * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                 *
                 * @test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
                 *      CTC-00601-FT-findThatStoreInMatchingNone,
                 *      CTC-00602-FT-findThatStoreInMatchingOne,
                 *      CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit,
                 *      CTC-00604-FT-findThatStoreInMatchingMore,
                 *      CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit,
                 *      CTC-00606-FT-findThatStoreInMatchingAll,
                 *      CTC-00607-FT-findThatStoreInMatchingAllAndMore,
                 *      CTC-00608-FT-findThatReturnedMatchingNone,
                 *      CTC-00609-FT-findThatReturnedMatchingOne,
                 *      CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit,
                 *      CTC-00611-FT-findThatReturnedMatchingMore,
                 *      CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit,
                 *      CTC-00613-FT-findThatReturnedMatchingAll,
                 *      CTC-00614-FT-findThatReturnedMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer < 
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_cpplang_ConstexprConditioned auto __findThat (      /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        Size                                        count,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > &;

                /**
                 * @brief Function used to find the first element validated by a given predicate and return the iterator of the element, if found. This is the predicate = callable variant
                 * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
                 * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                 * @exceptsafe if __Predicate callable / member function is exceptsafe
                 * @return __IteratorType = The found iterator, if applicable. Returns 'end' otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
                 *      CTC-00615-FT-findFirstThatMatchingNone,
                 *      CTC-00616-FT-findFirstThatMatchingOne,
                 *      CTC-00617-FT-findFirstThatMatchingMore,
                 *      CTC-00618-FT-findFirstThatMatchingAll,
                 *      CTC-00619-FT-findFirstThatMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType;

                /**
                 * @brief Function used to find the last element validated by a given predicate and return the iterator of the element, if found. This is the predicate = callable variant
                 * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
                 * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                 * @exceptsafe if __Predicate callable / member function is exceptsafe
                 * @return __IteratorType = The found iterator, if applicable. Returns 'end' otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
                 *      CTC-00620-FT-findLastThatMatchingNone,
                 *      CTC-00621-FT-findLastThatMatchingOne,
                 *      CTC-00622-FT-findLastThatMatchingMore,
                 *      CTC-00623-FT-findLastThatMatchingAll,
                 *      CTC-00624-FT-findLastThatMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IteratorType,                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findLastThat (  /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __IteratorType;

                /**
                 * @brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a given collection. This is the predicate = callable variant
                 * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
                 * @tparam __CollectionType is the type of template iterable to store the iterators in
                 * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                 * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                 * @exceptsafe if __Predicate callable / member function is exceptsafe
                 * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                 *
                 * @test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
                 *      CTC-00625-FT-findAllThatStoreInMatchingNone,
                 *      CTC-00626-FT-findAllThatStoreInMatchingOne,
                 *      CTC-00627-FT-findAllThatStoreInMatchingMore,
                 *      CTC-00628-FT-findAllThatStoreInMatchingAll,
                 *      CTC-00629-FT-findAllThatStoreInMatchingAllAndMore,
                 *      CTC-00630-FT-findAllThatReturnedMatchingNone,
                 *      CTC-00631-FT-findAllThatReturnedMatchingOne,
                 *      CTC-00632-FT-findAllThatReturnedMatchingMore,
                 *      CTC-00633-FT-findAllThatReturnedMatchingAll,
                 *      CTC-00634-FT-findAllThatReturnedMatchingAllAndMore
                 * }
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IteratorType,                            /* NOLINT(bugprone-reserved-identifier) */
                        template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __Predicate,                               /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isMemberFunctionPointer <
                                        __Predicate,
                                        cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                                > ()
                        > = 0
                > __CDS_cpplang_ConstexprConditioned auto __findAllThat (   /* NOLINT(bugprone-reserved-identifier) */
                        __IteratorType                      const & begin,
                        __IteratorType                      const & end,
                        __CollectionType < __IteratorType >       & storeIn,
                        __Predicate                         const & predicate
                ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> __CollectionType < __IteratorType > &;

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_FIND_STATEMENTS_HPP__ */
