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
                 * @class Interface for calling functional statements ( actions & predicates as parameters ) on an mutable iterable type ( has 'begin' and 'end' )
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client
                 * @tparam __ElementType is the type of elements contained into the Object
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                 * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __GenericMutableStatementsCompositeClient uses the same base implementation functions
                     * as __GenericImmutableStatementsCompositeClient, which is tested
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
