/* NOLINT(llvm-header-guard)
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @interface Server-Dispatcher-Type Class part of the Iterable Communication Model, to be
             *      extended in derived classes as a dispatcher between server requests received
             *      through Iterable Communication Channels and base implementation. If provides
             *      the standard calls required by the server, and enforces the function signatures
             *      via template parameters.
             *
             * @interface A dispatcher acts as the next layer, a connector between the derived class, that acts
             *      as an interface to its' implementation class. This dispatcher interface contains the function
             *      required only for the Iterable used handlers.
             *
             * @tparam __ServerType                 is the type of the server interface type (i.e. Array)
             * @tparam __ServiceType                is the type of the implementation service (i.e. shared/__Array)
             * @tparam __ElementType                is the enclosed element (i.e. int in Array \< int \>)
             * @tparam __ConstIteratorType          is the const iterator type returned by begin & end (i.e. __a_ConstIterator for shared/__Array)
             * @tparam __cbeginFunction             is the function of the implementation used to obtain a constant begin iterator (i.e. shared/__ArrayBase :: __ab_cbegin)
             * @tparam __cendFunction               is the function of the implementation used to obtain an constant end iterator (i.e. shared/__ArrayBase :: __ab_cbegin)
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             * @test Suite: MCTS-00001, Group: All, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename                                                                            __ServerType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ServiceType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __ConstIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cbeginFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    functional :: SupplierConstMemberFunction < __ServiceType, __ConstIteratorType >    __cendFunction          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
            > class __IterableServerDispatcher {                                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cbeginFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard static auto __cbegin (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cendFunction to construct a new delegate iterator using the received iterator
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to newly created delegate iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard static auto __cend (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType const * pServer
                ) noexcept -> __AbstractDelegateIterator < __ElementType const > *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cbeginFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __cbeginLocal (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType const * pServer
                ) noexcept -> __ConstIteratorType;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function provided by the dispatcher interface calling the received __cendFunction to return the received iterator. Used by local clients
                 * @exceptsafe
                 * @return __ConstIteratorType = the const iterator returned by the function
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr static auto __cendLocal ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ServerType const * pServer
                ) noexcept -> __ConstIteratorType;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERABLE_SERVER_DISPATCHER_HPP__ */
