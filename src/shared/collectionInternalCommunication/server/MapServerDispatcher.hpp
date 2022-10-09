/*
 * Created by loghin on 24/07/22.
 */

#ifndef __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @interface Server-Dispatcher-Type Class part of the Collection Communication Model, to be
             *      extended in derived classes as a dispatcher between server requests received
             *      through Collection Communication Channels and base implementation. If provides
             *      the standard calls required by the server, and enforces the function signatures
             *      via template parameters.
             *
             * @interface A dispatcher acts as the next layer, a connector between the derived class, that acts
             *      as an interface to its' implementation class. This dispatcher interface contains the function
             *      required only for the Map used handlers.
             *
             * @tparam __ServerType                 is the type of the server interface type (i.e. Array)
             * @tparam __ServiceType                is the type of the implementation service (i.e. shared/__Array)
             * @tparam __ElementType                is the enclosed element (i.e. int in Array \< int \>)
             * @tparam __AbstractIteratorType       is the abstract iterator type used by the remove function. Can be same as iterator type, if accepting only iterator
             * @tparam __AbstractConstIteratorType  is the abstract const iterator type used by the remove const function. Can be same as const iterator type, if accepting only const iterator
             * @tparam __IteratorType               is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
             * @tparam __ConstIteratorType          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
             * @tparam __beginFunction              is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array :: __a_begin)
             * @tparam __beginFunction              is the function of the implementation used to obtain an end iterator (i.e. shared/__Array :: __a_end)
             * @tparam __cbeginFunction             is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __cendFunction               is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array :: __a_newAddress)
             * @tparam __removeFunction             is the function of the implementation used to remove an iterator (i.e. shared/__Array :: __a_removeIterator)
             * @tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array :: __a_removeConstIterator)
             * @tparam __removeArrayFunction        is the function of the implementation used to remove multiple iterators (i.e. shared/__Array :: __a_removeIteratorArray)
             * @tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array :: __a_removeConstIteratorArray)
             * @tparam __findFunction               is the function of the implementation used to find an element and return an iterator (i.e. shared/__HashTable :: __ht_find)
             * @tparam __findConstFunction          is the function of the implementation used to find an element and return a const iterator (i.e. shared/__HashTable :: __ht_findConst)
             *
             * @extends __MutableCollectionServerDispatcher
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )             ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )               ()                                                              -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )            ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )              ()                                                      const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )        ( __ElementType const *, bool * )                               -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )            ( __AbstractIteratorType const & )                              -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )       ( __AbstractConstIteratorType const & )                         -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )       ( __AbstractIteratorType const * const *, Size )                -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findFunction )              ( __KeyType const & )                                           -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __findConstFunction )         ( __KeyType const & )                                   const   -> __ConstIteratorType  /* NOLINT(bugprone-reserved-identifier) */
            > class __MapServerDispatcher :                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    public __MutableCollectionServerDispatcher <
                            __ServerType,
                            __ServiceType,
                            __ElementType,
                            __AbstractIteratorType,
                            __AbstractConstIteratorType,
                            __IteratorType,
                            __ConstIteratorType,
                            __beginFunction,
                            __endFunction,
                            __cbeginFunction,
                            __cendFunction,
                            __newAddressFunction,
                            __removeFunction,
                            __removeConstFunction,
                            __removeArrayFunction,
                            __removeConstArrayFunction
                    > {

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to construct a new delegate iterator using the received iterator
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __find ( /* NOLINT(bugprone-reserved-identifier) */
                        __KeyType const & key
                ) noexcept -> __AbstractDelegateIterator < __ElementType > *;

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to construct a new delegate iterator using the received iterator
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __findConst ( /* NOLINT(bugprone-reserved-identifier) */
                        __KeyType const & key
                ) const noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to return the received iterator. Used by local clients
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __IteratorType = An iterator indicating to the element given as a parameter
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __findLocal ( /* NOLINT(bugprone-reserved-identifier) */
                        __KeyType const & key
                ) noexcept -> __IteratorType;

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to return the received iterator. Used by local clients
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __ConstIteratorType = An iterator indicating to the element given as a parameter
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __findConstLocal ( /* NOLINT(bugprone-reserved-identifier) */
                        __KeyType const & key
                ) const noexcept -> __ConstIteratorType;
            };

        }
    }
}

#endif /* __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__ */

