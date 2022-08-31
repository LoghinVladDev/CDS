/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorStatements.hpp"
#include "../../../iterator/IteratorMemberStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @class Interface for calling functional statements ( actions & predicates as parameters ) on an immutable iterable type ( has 'cbegin' and 'cend' )
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client
                 * @tparam __ElementType is the type of elements contained into the Object
                 *
                 * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: All
                 * 
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IterableType,                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                          /* NOLINT(bugprone-reserved-identifier) */
                > class __GenericImmutableStatementsCompositeClient {   /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef Private definition for __ElementType template parameter  
                     * @private
                     */
                    using ElementType = __ElementType;

                public:
                    /**
                     * @brief Function used to apply an action over each element of the iterable
                     * @tparam __Action the type of the action given as a parameter, the type must be callable and compatible with the 'Any ( Decay < ElementType > )' function signature, where Any is any type or a member function compatible with the signature 'Any () const'
                     * @param [in] action : __Action cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Action callable / member function is exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00139-FS-forEachCount }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00201-FSMF-forEach }
                     *
                     * @public
                     */
                    template < typename __Action > /* NOLINT(bugprone-reserved-identifier) */
                    auto forEach (
                            __Action const & action
                    ) const noexcept ( noexcept ( __forEach (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            action
                    ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to check if the iterable contains exactly 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be a callable compatible with the 'bool ( Decay < ElementType > )' function signature or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable / member function object, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value.
                     *      If no predicate is given, 'some' must yield the same value as 'caller.size() == count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated == count, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00136-FS-someExact, CTC-00137-FS-someLessFalse, CTC-00138-someMoreFalse }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00202-FSMF-someEqual, CTC-00203-FSMF-someLess, CTC-00204-someMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto some (
                            Size                count,
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __some (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains at least 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = minimum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'atLeast' must yield the same value as 'caller.size() >= count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated >= count, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00132-FS-atLeastTrue, CTC-00133-FS-atLeastCloseTrue, CTC-00134-atLeastCloseFalse, CTC-00135-atLeastFalse }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00205-FSMF-atLeast, CTC-00206-FSMF-atLeastLess, CTC-00207-atLeastMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto atLeast (
                            Size                count,
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __atLeast (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains at most 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = maximum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'atMost' must yield the same value as 'caller.size() <= count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated <= count, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00128-FS-atMostTrue, CTC-00129-FS-atMostCloseTrue, CTC-00130-atMostCloseFalse, CTC-00131-atMostFalse }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00208-FSMF-atMost, CTC-00209-FSMF-atMostLess, CTC-00210-atMostMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto atMost (
                            Size                count,
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __atMost (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains more than 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = minimum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'moreThan' must yield the same value as 'caller.size() > count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated > count, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00123-FS-moreThanTrue, CTC-00124-FS-moreThanCloseTrue, CTC-00125-moreThanCloseFalse, CTC-00126-moreThanFalse, CTC-00127-moreThanCompletelyFalse }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00211-FSMF-moreThan, CTC-00212-FSMF-moreThanLess, CTC-00213-moreThanMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto moreThan (
                            Size                count,
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __moreThan (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if the iterable contains less than 'count' elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] count : Size = maximum number of elements required to match
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'fewerThan' must yield the same value as 'caller.size() < count'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if number of elements validated < count, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00118-FS-fewerThanTrue, CTC-00119-FS-fewerThanCloseTrue, CTC-00120-fewerThanCloseFalse, CTC-00121-fewerThanFalse, CTC-00122-fewerThanCompletelyFalse }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00214-FSMF-fewerThan, CTC-00215-FSMF-fewerThanLess, CTC-00216-fewerThanMore }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto fewerThan (
                            Size                count,
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __fewerThan (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            count,
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to acquire the number of elements that are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'count' must yield the same value as 'caller.size()'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return Size = number of elements that are validated by the given predicate
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00113-FS-countProp1, CTC-00114-FS-countProp2, CTC-00115-countProp3, CTC-00116-countProp4, CTC-00117-countPropLbd }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00217-FSMF-countExact }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto count (
                            __Predicate const & predicate = & predicates :: alwaysTrue < __ElementType >
                    ) const noexcept ( noexcept ( __count (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> Size;

                public:
                    /**
                     * @brief Function used to check if any of the iterable's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'any' must yield the same value as 'caller.size() > 0'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if at least one element is validated by the given predicate, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00101-FS-anyNone, CTC-00102-FS-anyOne, CTC-00103-anyMore, CTC-00104-anyAll }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00218-FSMF-anyNone, CTC-00219-FSMF-anyOne, CTC-00220-anyMore, CTC-00221-anyAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto any (
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __any (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if all of the iterable's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'all' must return 'true'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if all of the iterable's elements are validated by the given predicate, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00105-FS-allNone, CTC-00106-FS-allOne, CTC-00107-allMore, CTC-00108-allAll }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00222-FSMF-allNone, CTC-00223-FSMF-allOne, CTC-00224-allMore, CTC-00225-allAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto all (
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __all (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to check if none of the iterable's elements are validated by a given predicate
                     * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the iterable as a parameter. If no predicate is given, it will default to a predicate that will validate every value
                     *      If no predicate is given, 'none' must yield the same value as 'caller.empty()'
                     * @exceptsafe if Predicate is exceptsafe
                     * @return bool = true if none of the iterable's elements are validated by the given predicate, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00109-FS-noneNone, CTC-00110-FS-noneOne, CTC-00111-noneMore, CTC-00112-noneAll }
                     * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00226-FSMF-noneNone, CTC-00227-FSMF-noneOne, CTC-00228-noneMore, CTC-00229-noneAll }
                     *
                     * @public
                     */
                    template <
                            typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto none (
                            __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
                    ) const noexcept ( noexcept ( __none (
                            cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
                            cds :: meta :: addressOf < __IterableType const > ()->cend(),
                            predicate
                    ) ) ) -> bool;
                };


                /**
                 * @typedef Variant of the GenericImmutableStatementsCompositeClient, only alias due to it being a composite client
                 * -> will use primitive local clients, making it a local client
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient,
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
                > using __LocalGenericImmutableStatementsCompositeClient =  /* NOLINT(bugprone-reserved-identifier) */
                        __GenericImmutableStatementsCompositeClient <
                                __IterableType,
                                __ElementType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorStatements.hpp"
#include "../../../iterator/impl/IteratorMemberStatements.hpp"

#endif /* __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_HPP__ */
