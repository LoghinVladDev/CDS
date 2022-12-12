/*
 * Created by loghin on 7/3/22.
 */

#ifndef __CDS_SHARED_SET_SERVER_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_SET_SERVER_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @interface Server-Type Class part of Collection Communication Model, to be extended in derived classes that act
             *      as a router for requests made through Collection Communication Channels. Provides the
             *      request table that is standard for Set-Type Collections. Also enforces existence
             *      of these functions in the derived class. It does NOT enforce the type of these
             *      functions, and this must be either done manually, or a Dispatcher has to be used
             *
             * @interface A dispatcher acts as the next layer, a connector between the derived class, that acts
             *      as an interface to its' implementation class ( i.e. HashSet = interface, shared/__HashTable =
             *          implementation, and shared/__HashTable :: __SetDispatcher = dispatcher. The Array class
             *          must derive the implementation, the dispatcher and the SetServer, as the
             *          Server will receive requests, it will handle them to the dispatcher, which will
             *          handle them to the implementation, statically, without branching
             *      )
             *
             * @tparam __ReceiverType is the type of the interface ( HashSet / LinkedHashSet / TreeSet / ... )
             * @tparam __ElementType is the type enclosed in the interface collection ( int from HashSet \< int \> )
             *
             * @test All Tests involving Collections apply
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             * @test Suite: STS-00001, Group: All, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __SetServer {               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic function of the target Collection.
                 * @private
                 */
                using __GenericHandler      = functional :: ConsumerFunction < Collection < __ElementType > * >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic const function of the target Collection.
                 * @private
                 */
                using __GenericConstHandler = functional :: ConsumerFunction < Collection < __ElementType > const * >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief routing table of the generic functions. One for each request type.
                 * @static
                 * @private
                 */
                static __GenericHandler const __routingTable [   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ];

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief routing table of the generic const functions. One for each request type.
                 * @static
                 * @private
                 */
                static __GenericConstHandler const __constRoutingTable [   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        static_cast < uint32 > ( __CollectionInternalRequestType :: __cirt_requestCountDoNotUse )
                ];

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the Set Server Generic Handlers, to be used in
                 *      __cicch_obtainGenericHandler in the 'interface' class ( i.e. HashSet / LinkedHashSet / TreeSet / ... )
                 * @exceptsafe
                 * @return __GenericHandler cptr = Address to the array of Immutable Generic Handlers
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ss_handlers () const noexcept -> __GenericHandler const *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the Set Server Generic Const Handlers, to be used in
                 *      __cicch_obtainGenericConstHandler in the 'interface' class ( i.e. HashSet / LinkedHashSet / TreeSet / ... )
                 * @exceptsafe
                 * @return __GenericConstHandler cptr = Address to the array of Immutable Generic Const Handlers
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ss_constHandlers () const noexcept -> __GenericConstHandler const *;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_SET_SERVER_HPP__ */
