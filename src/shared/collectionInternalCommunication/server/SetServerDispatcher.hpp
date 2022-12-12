/*
 * Created by loghin on 24/07/22.
 */

#ifndef __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "CollectionServerDispatcher.hpp"

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
             *      required only for the Set used handlers.
             *
             * @tparam __ServerType                 is the type of the server interface type (i.e. Array)
             * @tparam __ServiceType                is the type of the implementation service (i.e. shared/__Array)
             * @tparam __ElementType                is the enclosed element (i.e. int in Array \< int \>)
             * @tparam __AbstractConstIteratorType  is the abstract const iterator type used by the remove const function. Can be same as const iterator type, if accepting only const iterator
             * @tparam __ConstIteratorType          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
             * @tparam __cbeginFunction             is the function of the implementation used to obtain a begin const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __cendFunction               is the function of the implementation used to obtain an end const iterator (i.e. shared/__Array :: __a_cbegin)
             * @tparam __newAddressFunction         is the function of the implementation used to obtain a new element address (i.e. shared/__Array :: __a_newAddress)
             * @tparam __removeConstFunction        is the function of the implementation used to remove a const iterator (i.e. shared/__Array :: __a_removeConstIterator)
             * @tparam __removeConstArrayFunction   is the function of the implementation used to remove multiple const iterators (i.e. shared/__Array :: __a_removeConstIteratorArray)
             * @tparam __findConstFunction          is the function of the implementation used to find an element and return a ConstIterator (i.e. shared/__HashTable :: __ht_findConst)
             *
             * @extends __CollectionServerDispatcher
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             * @test Suite: STS-00001, Group: STS-00050-FU, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
             template <
                    typename                                                                                                        __ServerType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ServiceType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ElementType,                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __AbstractConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                                                        __ConstIteratorType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cbeginFunction,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >                                __cendFunction,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, __ElementType *, __ElementType const *, bool * >            __newAddressFunction,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, bool, __AbstractConstIteratorType const & >                 __removeConstFunction,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperConstMemberFunction < __ServiceType, __ConstIteratorType, __ElementType const & >           __findConstFunction             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __SetServerDispatcher :                                                                                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to construct a new delegate iterator using the received iterator
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: STS-00001, Group: STS-00050-FU, Test Cases: All
                 * @protected
                 */
                static auto __findConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType    const * pServer,
                        __ElementType   const & element
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __findConstFunction, and is used by the server to return the received iterator. Used by local clients
                 * @param [in] element : __ElementType cref = Constant Reference to an element to look for
                 * @exceptsafe
                 * @return __ConstIteratorType = An iterator indicating to the element given as a parameter
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_cpplang_NonConstConstexprMemberFunction static auto __findConstLocal ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType    const * pServer,
                        __ElementType   const & element
                ) noexcept -> __ConstIteratorType;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__ */

