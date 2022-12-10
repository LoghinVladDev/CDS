/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

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
             * @tparam __AbstractIteratorType           is the abstract iterator type used by the remove, insert before/after functions. Can be same as iterator type, if accepting only iterator
             * @tparam __AbstractConstIteratorType      is the abstract const iterator type used by the remove const, insert before/after const functions. Can be same as const iterator type, if accepting only const iterator
             * @tparam __IteratorType                   is the iterator type returned by begin & end (i.e. __a_Iterator for shared/__Array)
             * @tparam __ConstIteratorType              is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
             * @tparam __ReverseIteratorType            is the reverse iterator type returned by rbegin & rend (i.e. __a_ReverseIterator for shared/__Array)
             * @tparam __ConstReverseIteratorType       is the const reverse iterator type returned by rbegin & rend (i.e. __a_ConstReverseIterator for shared/__Array)
             * @tparam __beginFunction                  is the function of the implementation used to obtain a begin iterator (i.e. shared/__Array :: __a_begin)
             * @tparam __beginFunction                  is the function of the implementation used to obtain an end iterator (i.e. shared/__Array :: __a_end)
             * @tparam __cbeginFunction                 is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __cendFunction                   is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __rbeginFunction                 is the function of the implementation used to obtain a reverse begin iterator (i.e. shared/__Array :: __a_rbegin)
             * @tparam __rendFunction                   is the function of the implementation used to obtain an reverse end iterator (i.e. shared/__Array :: __a_rend)
             * @tparam __crbeginFunction                is the function of the implementation used to obtain a reverse begin const iterator (i.e. shared/__Array :: __a_crbegin)
             * @tparam __crendFunction                  is the function of the implementation used to obtain an reverse end const iterator (i.e. shared/__Array :: __a_crbegin)
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
             * @tparam __removeArrayFunction            is the function of the implementation used to remove multiple iterators (i.e. shared/__Array :: __a_removeIteratorArray)
             * @tparam __removeConstArrayFunction       is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array :: __a_removeConstIteratorArray)
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
                    typename                                                                                                                __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __AbstractIteratorType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __IteratorType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __ReverseIteratorType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                                __ConstReverseIteratorType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                                  __beginFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __IteratorType >                                                  __endFunction,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                        __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                        __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __ReverseIteratorType >                                           __rbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __ReverseIteratorType >                                           __rendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstReverseIteratorType >                                 __crbeginFunction,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstReverseIteratorType >                                 __crendFunction,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >                    __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __ElementType * >                                                 __newFrontFunction,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierMemberFunction < __ServiceType, __ElementType * >                                                 __newBackFunction,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerMemberFunction < __ServiceType, Size, __ElementType ** >                                          __newFrontArrayFunction,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerMemberFunction < __ServiceType, Size, __ElementType ** >                                          __newBackArrayFunction,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __AbstractIteratorType const & >                   __newBeforeFunction,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __AbstractConstIteratorType const & >              __newBeforeConstFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __AbstractIteratorType const & >                   __newAfterFunction,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __AbstractConstIteratorType const & >              __newAfterConstFunction,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractIteratorType const &, Size, __ElementType ** >      __newBeforeArrayFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractConstIteratorType const &, Size, __ElementType ** > __newBeforeArrayConstFunction,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractIteratorType const &, Size, __ElementType ** >      __newAfterArrayFunction,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractConstIteratorType const &, Size, __ElementType ** > __newAfterArrayConstFunction,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractIteratorType const & >                              __removeFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractConstIteratorType const & >                         __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractIteratorType const * const *, Size >                __removeArrayFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >           __removeConstArrayFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __ListServerDispatcher :                                                                                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
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

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __rbeginFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard static auto __rbegin (
                        __ServerType * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __rendFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard static auto __rend (
                        __ServerType * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __crbeginFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard static auto __crbegin (
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __crendFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard static auto __crend (
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __rbeginFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal (
                        __ServerType * pServer
                ) noexcept -> __ReverseIteratorType;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __rendFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal (
                        __ServerType * pServer
                ) noexcept -> __ReverseIteratorType;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __crbeginFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __crbeginLocal (
                        __ServerType const * pServer
                ) const noexcept -> __ConstReverseIteratorType;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __crendFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __crendLocal (
                        __ServerType const * pServer
                ) noexcept -> __ConstReverseIteratorType;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newFrontFunction, and is used by the server
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newFront (
                        __ServerType * pServer
                ) noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBackFunction, and is used by the server
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBack (
                        __ServerType * pServer
                ) noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newFrontArrayFunction, and is used by the server
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newFrontArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType   * pServer,
                        Size             count,
                        __ElementType ** ppElements
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBackArrayFunction, and is used by the server
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBackArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType   * pServer,
                        Size             count,
                        __ElementType ** ppElements
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBeforeFunction, and is used by the server
                 * @param [in] pIterator : __IteratorType cptr = Address to an Immutable iterator
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBefore ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                 * pServer,
                        __AbstractIteratorType const * pIterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBeforeConstFunction, and is used by the server
                 * @param [in] pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBeforeConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                      * pServer,
                        __AbstractConstIteratorType const * pIterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newAfterFunction, and is used by the server
                 * @param [in] pIterator : __IteratorType cptr = Address to an Immutable iterator
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newAfter ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                 * pServer,
                        __AbstractIteratorType const * pIterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newAfterConstFunction, and is used by the server
                 * @param [in] pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newAfterConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                      * pServer,
                        __AbstractConstIteratorType const * pIterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBeforeArrayFunction, and is used by the server
                 * @param [in] pIterator : __IteratorType cptr = Address to an Immutable iterator
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in, out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBeforeArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                  * pServer,
                        __AbstractIteratorType  const * pIterator,
                        Size                            count,
                        __ElementType                ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newBeforeArrayConstFunction, and is used by the server
                 * @param [in] pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in, out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newBeforeArrayConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                      * pServer,
                        __AbstractConstIteratorType const * pIterator,
                        Size                                count,
                        __ElementType                    ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newAfterArrayFunction, and is used by the server
                 * @param [in] pIterator : __IteratorType cptr = Address to an Immutable iterator
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in, out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newAfterArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                  * pServer,
                        __AbstractIteratorType  const * pIterator,
                        Size                            count,
                        __ElementType                ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newAfterArrayConstFunction, and is used by the server
                 * @param [in] pIterator : __ConstIteratorType cptr = Address to an Immutable const iterator
                 * @param [in] count : Size = number of elements to allocate
                 * @param [in, out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                static auto __newAfterArrayConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                      * pServer,
                        __AbstractConstIteratorType const * pIterator,
                        Size                                count,
                        __ElementType                    ** ppElements
                ) noexcept -> bool;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__ */
