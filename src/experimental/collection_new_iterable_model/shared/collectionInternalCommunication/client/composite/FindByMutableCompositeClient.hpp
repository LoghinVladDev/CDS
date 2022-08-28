/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../../../iterator/IteratorFindStatements.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @class Interface for calling functional find statements ( predicates as parameters, henceforth the 'find' elements 'that' are validated by a predicate )
                 * on an mutable iterable type ( has 'begin' and 'end' )
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client - 'begin' / 'end'
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __IteratorType is the type of iterator to be returned by the functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                 * as __FindByImmutableCompositeClient, which is tested
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > class __FindByMutableCompositeClient {        /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef Private definition for __IteratorType template parameter
                     * @private
                     */
                    using Iterator = __IteratorType;

                public:
                    /**
                     * @brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a given collection, until a given limit has been reached, at which point the iteration will stop.
                     * @tparam __CollectionType is the type of template iterable to store the iterators in
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findThat (
                            Size                                        count,
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a new collection, until a given limit has been reached, at which point the iteration will stop.
                     * @tparam __CollectionType is the type of template iterable to store the iterators in
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [in] count : Size = Maximum number of elements to find
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __CollectionType \< __IteratorType \> = The new collection containing the found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findThat (
                            Size count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            count,
                            cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < Iterator >;

                public:
                    /**
                     * @brief Function used to find the first element validated by a given predicate and return the iterator of the element, if applicable.
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __IteratorType = The iterator of the found element, if applicable. If none found, 'cend' is returned
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findFirstThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findFirstThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> Iterator;

                public:
                    /**
                     * @brief Function used to find the last element validated by a given predicate and return the iterator of the element, if applicable.
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __IteratorType = The iterator of the found element, if applicable. If none found, 'cend' is returned
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template < typename __Predicate > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_NoDiscard auto findLastThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findLastThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            predicate
                    ) ) ) -> Iterator;

                public:
                    /**
                     * @brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a given collection
                     * @tparam __CollectionType is the type of template iterable to store the iterators in
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [out] storeIn : __CollectionType \< __IteratorType \> cref = Constant Reference to the collection to store the iterators in
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __CollectionType \< __IteratorType \> ref = Reference to the updated object given in the 'storeIn' parameter
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > auto findAllThat (
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            storeIn,
                            predicate
                    ) ) ) -> __CollectionType < Iterator > &;

                public:
                    /**
                     * @brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a new collection
                     * @tparam __CollectionType is the type of template iterable to store the iterators in
                     * @tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool ()' member function signature.
                     * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
                     * @exceptsafe if __Predicate callable / member function is exceptsafe
                     * @return __CollectionType \< __IteratorType \> = The new collection containing the found iterators
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @test Theoretically tested, as __FindByMutableCompositeClient uses the same base implementation functions
                     * as __FindByImmutableCompositeClient, which is tested
                     *
                     * @public
                     */
                    template <
                            template < typename ... > class __CollectionType,   /* NOLINT(bugprone-reserved-identifier) */
                            typename                        __Predicate         /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto findAllThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( __findAllThat (
                            cds :: meta :: addressOf < __IterableType > ()->begin(),
                            cds :: meta :: addressOf < __IterableType > ()->end(),
                            cds :: meta :: referenceOf < __CollectionType < Iterator > > (),
                            predicate
                    ) ) ) -> __CollectionType < Iterator >;

                };


                /**
                 * @typedef Variant of the FindByMutableCompositeClient, only alias due to it being a composite client
                 * -> will use primitive local clients, making it a local client
                 * @tparam __IterableType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement a variant of DelegateForwardIterablePrimitiveClient,
                 * or provide a set of equivalent member functions provided by said client - 'begin' / 'end'
                 * @tparam __ElementType is the type of elements contained into the Object
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __IterableType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalFindByMutableCompositeClient =   /* NOLINT(bugprone-reserved-identifier) */
                        __FindByMutableCompositeClient <
                                __IterableType,
                                __ElementType,
                                __IteratorType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorFindStatements.hpp"

#endif /* __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__ */
