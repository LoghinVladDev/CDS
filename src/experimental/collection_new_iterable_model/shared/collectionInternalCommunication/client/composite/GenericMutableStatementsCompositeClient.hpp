/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorStatements.hpp"
#include "../../../iterator/IteratorMemberStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @interface Interface for calling functional statements ( actions & predicates as parameters ) on an mutable iterable type ( has 'begin' and 'end' )
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client
                 * @tparam __ElementType is the type of elements contained into the Object
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: All
                 * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: All
                 * 
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IterableType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                      /* NOLINT(bugprone-reserved-identifier) */
                > class __GenericMutableStatementsCompositeClient { /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef Private definition for __ElementType template parameter  
                     * @private
                     * */
                    using ElementType = __ElementType;

                public:
                    /**
                     * @brief Function used to apply an action over each element of the iterable
                     * @tparam __Action the type of the action given as a parameter, the type must be callable and compatible with the 'Any ( Decay < ElementType > )' function signature, where Any is any type or a member function compatible with the signature 'Any () const'
                     * @param [in] action : __Action cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Action callable / member function is exceptsafe
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00139-FS-forEachCount }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00201-FSMF-forEach }
                     *
                     * @public
                     */
                    template < typename __Action > /* NOLINT(bugprone-reserved-identifier) */
                    auto forEach (
                            __Action const & action
                    ) noexcept ( noexcept ( __forEach (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            action
                    ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to check if the iterable contains exactly 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be a callable compatible with the 'bool ( Decay < ElementType > )' function signature or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable / member function object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value.
                     *      If no predicate is given, 'some' must yield the same value as 'caller.size() == count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated == count, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00136-FS-someExact, MCTC-00137-FS-someLessFalse, MCTC-00138-someMoreFalse }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00202-FSMF-someEqual, MCTC-00203-FSMF-someLess, MCTC-00204-someMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto some (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __some (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains at least 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = minimum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'atLeast' must yield the same value as 'caller.size() >= count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated >= count, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00132-FS-atLeastTrue, MCTC-00133-FS-atLeastCloseTrue, MCTC-00134-atLeastCloseFalse, MCTC-00135-atLeastFalse }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00205-FSMF-atLeast, MCTC-00206-FSMF-atLeastLess, MCTC-00207-atLeastMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto atLeast (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __atLeast (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains at most 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = maximum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'atMost' must yield the same value as 'caller.size() <= count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated <= count, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00128-FS-atMostTrue, MCTC-00129-FS-atMostCloseTrue, MCTC-00130-atMostCloseFalse, MCTC-00131-atMostFalse }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00208-FSMF-atMost, MCTC-00209-FSMF-atMostLess, MCTC-00210-atMostMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto atMost (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __atMost (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains more than 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = minimum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'moreThan' must yield the same value as 'caller.size() > count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated > count, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00123-FS-moreThanTrue, MCTC-00124-FS-moreThanCloseTrue, MCTC-00125-moreThanCloseFalse, MCTC-00126-moreThanFalse, MCTC-00127-moreThanCompletelyFalse }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00211-FSMF-moreThan, MCTC-00212-FSMF-moreThanLess, MCTC-00213-moreThanMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto moreThan (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __moreThan (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the collection contains less than 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = maximum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'fewerThan' must yield the same value as 'caller.size() < count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated < count, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00118-FS-fewerThanTrue, MCTC-00119-FS-fewerThanCloseTrue, MCTC-00120-fewerThanCloseFalse, MCTC-00121-fewerThanFalse, MCTC-00122-fewerThanCompletelyFalse }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00214-FSMF-fewerThan, MCTC-00215-FSMF-fewerThanLess, MCTC-00216-fewerThanMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto fewerThan (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __fewerThan (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to acquire the number of elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'count' must yield the same value as 'caller.size()'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return Size = number of elements that are validated by the given predicate
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00113-FS-countProp1, MCTC-00114-FS-countProp2, MCTC-00115-countProp3, MCTC-00116-countProp4, MCTC-00117-countPropLbd }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00217-FSMF-countExact }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto count (
                            __Predicate const & predicate = & predicates :: alwaysTrue < __ElementType >
                    ) noexcept ( noexcept ( __count (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> Size;

                public:
                    /**
                     * @brief Function used to check if any of the collection's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'any' must yield the same value as 'caller.size() > 0'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if at least one element is validated by the given predicate, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00101-FS-anyNone, MCTC-00102-FS-anyOne, MCTC-00103-anyMore, MCTC-00104-anyAll }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00218-FSMF-anyNone, MCTC-00219-FSMF-anyOne, MCTC-00220-anyMore, MCTC-00221-anyAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto any (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __any (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if all of the collection's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'all' must return 'true'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if all of the collection's elements are validated by the given predicate, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00105-FS-allNone, MCTC-00106-FS-allOne, MCTC-00107-allMore, MCTC-00108-allAll }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00222-FSMF-allNone, MCTC-00223-FSMF-allOne, MCTC-00224-allMore, MCTC-00225-allAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto all (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __all (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if none of the collection's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'none' must yield the same value as 'caller.empty()'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if none of the collection's elements are validated by the given predicate, false otherwise
                     *
                     * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00109-FS-noneNone, MCTC-00110-FS-noneOne, MCTC-00111-noneMore, MCTC-00112-noneAll }
                     * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00226-FSMF-noneNone, MCTC-00227-FSMF-noneOne, MCTC-00228-noneMore, MCTC-00229-noneAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto none (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __none (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> bool;
                };


                /**
                 * @typedef Variant of the GenericMutableStatementsCompositeClient, only alias due to it being a composite client
                 * -> will use primitive local clients, making it a local client
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client
                 * @tparam __ElementType is the type of elements contained into the Object
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IterableType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                              /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalGenericMutableStatementsCompositeClient =    /* NOLINT(bugprone-reserved-identifier) */
                        __GenericMutableStatementsCompositeClient <
                                __IterableType,
                                __ElementType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorStatements.hpp"
#include "../../../iterator/impl/IteratorMemberStatements.hpp"

#endif /* __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ */
