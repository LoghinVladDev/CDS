/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
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
                 * @tparam __ServerType                     is the type of the server interface type (i.e. Array)
                 * @tparam __ServiceType                    is the type of the implementation service (i.e. shared/__Array)
                 * @tparam __ElementType                    is the enclosed element (i.e. int in Array \< int \>)
                 * @tparam __IteratorType                   is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
                 * @tparam __ConstIteratorType              is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
                 * @tparam __newAddressFunction             is the function of the implementation used to obtain a new element address (i.e. shared/__Array :: __a_newAddress)
                 * @tparam __newFrontFunction               is the function of the implementation used to obtain a new element address at the front of the list (i.e. shared/__Array :: __a_newFront)
                 * @tparam __newBackFunction                is the function of the implementation used to obtain a new element address at the end of the list (i.e. shared/__Array :: __a_newBack)
                 * @tparam __newFrontArrayFunction          is the function of the implementation used to populate an array with new addresses at the front of the list (i.e. shared/__Array :: __a_newFrontArray)
                 * @tparam __newBackArrayFunction           is the function of the implementation used to populate an array with new addresses at the back of the list (i.e. shared/__Array :: __a_newBackArray)
                 * @tparam __newBeforeFunction              is the function of the implementation used to obtain a new element address before an iterator (i.e. shared/__Array :: __a_newBefore)
                 * @tparam __newBeforeConstFunction         is the function of the implementation used to obtain a new element address before a const iterator (i.e. shared/__Array :: __a_newBeforeConst)
                 * @tparam __newAfterFunction               is the function of the implementation used to obtain a new element address after an iterator (i.e. shared/__Array :: __a_newAfter)
                 * @tparam __newAfterConstFunction          is the function of the implementation used to obtain a new element address after a const iterator (i.e. shared/__Array :: __a_newAfterConst)
                 * @tparam __newBeforeArrayFunction         is the function of the implementation used to populate an array with new addresses before an iterator (i.e. shared/__Array :: __a_newBeforeArray)
                 * @tparam __newBeforeArrayConstFunction    is the function of the implementation used to populate an array with new addresses before a const iterator (i.e. shared/__Array :: __a_newBeforeArrayConst)
                 * @tparam __newAfterArrayFunction          is the function of the implementation used to populate an array with new addresses after an iterator (i.e. shared/__Array :: __a_newAfterArray)
                 * @tparam __newAfterArrayConstFunction     is the function of the implementation used to populate an array with new addresses after a const iterator (i.e. shared/__Array :: __a_newAfterArrayConst)
                 * @tparam __removeFunction                 is the function of the implementation used to remove an iterator (i.e. shared/__Array :: __a_removeIterator)
                 * @tparam __removeConstFunction            is the function of the implementation used to remove a const iterator (i.e. shared/__Array :: __a_removeConstIterator)
                 *
                 * @extends __MutableCollectionServerDispatcher
                 *
                 * @test All Tests involving Collections apply
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool                         /* NOLINT(bugprone-reserved-identifier) */
                > class __ListServerDispatcher :                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
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
                                __removeConstFunction
                        > {

                protected:
                    __CDS_NoDiscard auto __rbegin () noexcept -> __AbstractDelegateIterator < __ElementType > *;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rend () noexcept -> __AbstractDelegateIterator < __ElementType > *;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __crbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __crend () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __rbeginLocal () noexcept -> __ReverseIteratorType;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __rendLocal () noexcept -> __ReverseIteratorType;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __crbeginLocal () const noexcept -> __ConstReverseIteratorType;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __crendLocal () const noexcept -> __ConstReverseIteratorType;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newFrontFunction, and is used by the server
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newFront () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBackFunction, and is used by the server
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBack () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newFrontArrayFunction, and is used by the server
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newFrontArray ( /* NOLINT(bugprone-reserved-identifier) */
                            Size             count,
                            __ElementType ** ppElements
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBackArrayFunction, and is used by the server
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBackArray ( /* NOLINT(bugprone-reserved-identifier) */
                            Size             count,
                            __ElementType ** ppElements
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBeforeFunction, and is used by the server
                     * @param pIterator : __IteratorType cptr = Address to an Immutable iterator
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBefore ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBeforeConstFunction, and is used by the server
                     * @param pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBeforeConst ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractConstIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newAfterFunction, and is used by the server
                     * @param pIterator : __IteratorType cptr = Address to an Immutable iterator
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newAfter ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newAfterConstFunction, and is used by the server
                     * @param pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newAfterConst ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractConstIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBeforeArrayFunction, and is used by the server
                     * @param pIterator : __IteratorType cptr = Address to an Immutable iterator
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBeforeArray ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractIteratorType  const * pIterator,
                            Size                            count,
                            __ElementType                ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newBeforeArrayConstFunction, and is used by the server
                     * @param pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newBeforeArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractConstIteratorType const * pIterator,
                            Size                                count,
                            __ElementType                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newAfterArrayFunction, and is used by the server
                     * @param pIterator : __IteratorType cptr = Address to an Immutable iterator
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newAfterArray ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractIteratorType  const * pIterator,
                            Size                            count,
                            __ElementType                ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function provided by the dispatcher interface calling the received __newAfterArrayConstFunction, and is used by the server
                     * @param pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                     * @param count : Size = number of elements to allocate
                     * @param ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __newAfterArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractConstIteratorType const * pIterator,
                            Size                                count,
                            __ElementType                    ** ppElements
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ */
