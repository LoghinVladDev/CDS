/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "CollectionServerDispatcher.hpp"

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
             *      required only for the MutableCollection used handlers.
             *
             * @tparam __ServerType                 is the type of the server interface type (i.e. Array)
             * @tparam __ServiceType                is the type of the implementation service (i.e. shared/__Array)
             * @tparam __ElementType                is the enclosed element (i.e. int in Array \< int \>)
             * @tparam __IteratorType               is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
             * @tparam __ConstIteratorType          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
             * @tparam __beginFunction              is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array :: __a_begin)
             * @tparam __endFunction                is the function of the implementation used to obtain an end iterator (i.e. shared/__Array :: __a_begin)
             * @tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array :: __a_newAddress)
             * @tparam __removeFunction             is the function of the implementation used to remove an iterator (i.e. shared/__Array :: __a_removeIterator)
             * @tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array :: __a_removeConstIterator)
             * @tparam __removeArrayFunction        is the function of the implementation used to remove multiple iterators (i.e. shared/__Array :: __a_removeIteratorArray)
             * @tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array :: __a_removeConstIteratorArray)
             *
             * @extends __CollectionServerDispatcher
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             * @test Suite: MCTS-00001, Group: All, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ServerType,                                                                                                                          /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                        /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )         ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )           ()                                                                  -> __IteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )        ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )          ()                                                          const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )                                   -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )        ( __AbstractIteratorType const & )                                  -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )                             -> bool,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )   ( __AbstractIteratorType const * const *, Size )                    -> Size,                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )  ( __AbstractConstIteratorType const * const *, Size )           -> Size                 /* NOLINT(bugprone-reserved-identifier) */
            > class __MutableCollectionServerDispatcher :                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                    public __CollectionServerDispatcher <
                            __ServerType,
                            __ServiceType,
                            __ElementType,
                            __AbstractConstIteratorType,
                            __ConstIteratorType,
                            __cbeginFunction,
                            __cendFunction,
                            __newAddressFunction,
                            __removeConstFunction,
                            __removeConstArrayFunction
                    > {

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __beginFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard auto __begin () noexcept -> __AbstractDelegateIterator < __ElementType > *;  /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __endFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard auto __end () noexcept -> __AbstractDelegateIterator < __ElementType > *;    /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __beginFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __beginLocal () noexcept -> __IteratorType;  /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __endFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __endLocal () noexcept -> __IteratorType;    /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __removeFunction, and is used by the server
                 * @param [in] pIterator : __IteratorType cptr = Address to an Immutable Iterator to be removed
                 * @exceptsafe
                 * @return bool = true if iterator was removed, false otherwise
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00350-RAIT, Test Cases: All
                 * @test Suite: MCTS-00001, Group: MCTG-00400-RB, Test Cases: All
                 * @test Suite: MCTS-00001, Group: MCTG-00450-RO, Test Cases: All
                 * @protected
                 */
                auto __remove ( /* NOLINT(bugprone-reserved-identifier) */
                        __AbstractIteratorType const * pIterator
                ) noexcept -> bool;

            protected:
                /**
                 * @brief Function provided by the dispatcher interface calling the received __removeArrayFunction, and is used by the server
                 * @param [in] ppIterators : __AbstractIteratorType cptr cptr = Address to an Immutable Array of Immutable Addresses to Iterators to be removed
                 * @param [in] iteratorArrayCount : Size = number of iterator addresses contained in the array
                 * @exceptsafe
                 * @return Size = number of iterators to be removed
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00400-RB, Test Cases: All
                 * @test Suite: MCTS-00001, Group: MCTG-00450-RO, Test Cases: All
                 * @protected
                 */
                auto __removeArray ( /* NOLINT(bugprone-reserved-identifier) */
                        __AbstractIteratorType  const * const * ppIterators,
                        Size                                    iteratorArrayCount
                ) noexcept -> Size;
            };

        }
    }
}

#endif /* __CDS_SHARED_MUTABLE_COLLECTION_SERVER_DISPATCHER_HPP__ */
