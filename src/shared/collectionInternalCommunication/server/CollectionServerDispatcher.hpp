/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

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
             *      required only for the Collection used handlers.
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
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
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
                    functional :: MapperMemberFunction < __ServiceType, Size, __AbstractConstIteratorType const * const *, Size >   __removeConstArrayFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __CollectionServerDispatcher {                                                                                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cbeginFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard static auto __cbegin (
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cendFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard static auto __cend (
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cbeginFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __cbeginLocal (
                        __ServerType const * pServer
                ) noexcept -> __ConstIteratorType;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cendFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __cendLocal (
                        __ServerType const * pServer
                ) noexcept -> __ConstIteratorType;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __newAddressFunction, and is used by the server
                 * @param [in] pReferenceElement : __ElementType cptr = Address to an Immutable element to be used as a reference for insertion ( i.e. Set duplicate avoidance )
                 * @param [in, out] pNewElementCreated : bool ptr = Address to a boolean variable to be set to 'true' if a new address was returned, 'false' otherwise
                 * @exceptsafe
                 * @return __ElementType ptr = An address to an element, to a new one or to an existing one
                 *
                 * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: All
                 * @protected
                 */
                static auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType        * pServer,
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __removeConstFunction, and is used by the server
                 * @param [in] pIterator : __AbstractConstIteratorType cptr = Address to an Immutable Constant Iterator to be removed
                 * @exceptsafe
                 * @return bool = true if iterator was removed, false otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
                 * @protected
                 */
                static auto __removeConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                      * pServer,
                        __AbstractConstIteratorType const * pIterator
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __removeConstArrayFunction, and is used by the server
                 * @param [in] ppIterators : __AbstractConstIteratorType cptr cptr = Address to an Immutable Array of Immutable Addresses to Constant Iterators to be removed
                 * @param [in] iteratorArrayCount : Size = number of iterator addresses contained in the array
                 * @exceptsafe
                 * @return Size = number of iterators to be removed
                 *
                 * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
                 * @protected
                 */
                static auto __removeConstArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType                              * pServer,
                        __AbstractConstIteratorType const * const * ppIterators,
                        Size                                        iteratorArrayCount
                ) noexcept -> Size;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_HPP__ */
