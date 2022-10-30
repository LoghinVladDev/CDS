/*
 * Created by loghin on 30/10/22.
 */

#ifndef __CDS_SHARED_ITERABLE_SERVER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERABLE_SERVER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __IterableServer {          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic function of the target Collection.
                 * @private
                 */
                using __GenericHandler      = functional :: ConsumerMemberFunction < Iterable < __ElementType > >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic const function of the target Collection.
                 * @private
                 */
                using __GenericConstHandler = functional :: ConsumerConstMemberFunction < Iterable < __ElementType > >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief routing table of the generic functions. One for each request type.
                 * @static
                 * @private
                 */
                static __GenericHandler const __routingTable [   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
                ];

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief routing table of the generic const functions. One for each request type.
                 * @static
                 * @private
                 */
                static __GenericConstHandler const __constRoutingTable [   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        static_cast < uint32 > ( __IterableInternalRequestType :: __iirt_requestCountDoNotUse )
                ];

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the List Server Generic Handlers, to be used in
                 *      __cicch_obtainGenericHandler in the 'interface' class ( i.e. Array / LinkedList / ... )
                 * @exceptsafe
                 * @return __GenericHandler cptr = Address to the array of Immutable Generic Handlers
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __is_handlers () const noexcept -> __GenericHandler const *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the List Server Generic Const Handlers, to be used in
                 *      __cicch_obtainGenericConstHandler in the 'interface' class ( i.e. Array / LinkedList / ... )
                 * @exceptsafe
                 * @return __GenericConstHandler cptr = Address to the array of Immutable Generic Const Handlers
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __is_constHandlers () const noexcept -> __GenericConstHandler const *;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERABLE_SERVER_HPP__ */
