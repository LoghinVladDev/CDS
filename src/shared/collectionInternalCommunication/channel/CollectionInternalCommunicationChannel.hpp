/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "../CollectionInternalRequestType.hpp"              /* NOLINT(llvm-include-order) */
#include "../../delegateIterator/AbstractDelegateIterator.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @class Abstract Object representing any Object type using Collection Communication Channels. made as base class for collection to represent the Server-Client model channel
             * @tparam __ReceiverType is the type of extended class, used for static polymorphism
             * @tparam __ElementType is the type of elements contained into the Object
             *
             * @extends [public]   Object - base cds Class
             *
             * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __CollectionInternalCommunicationChannel :  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */
                    public cds :: Object {

            /** Below Primitive Client friend declarations are made to access the collection channel requests. Alternative to importing the functions in all classes **/

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, bool >
                friend class __DelegateForwardIterablePrimitiveClient;                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, bool >
                friend class __DelegateBackwardIterablePrimitiveClient;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, bool >
                friend class __DelegateForwardConstIterablePrimitiveClient;             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, bool >
                friend class __DelegateBackwardConstIterablePrimitiveClient;            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename >
                friend class __AbstractIteratorRemovePrimitiveClient;                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename >
                friend class __AbstractConstIteratorRemovePrimitiveClient;              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, typename >
                friend class __RandomInsertionPrimitiveClient;                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, typename >
                friend class __BoundaryInsertionPrimitiveClient;                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename >
                friend class __AbstractIteratorRelativeInsertionPrimitiveClient;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename >
                friend class __AbstractConstIteratorRelativeInsertionPrimitiveClient;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, typename, bool >
                friend class __FindUniqueImmutablePrimitiveClient;                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Friend class pre-declaration of Primitive Client.
                 * @private
                 */
                template < typename, typename, typename, bool >
                friend class __FindUniqueMutablePrimitiveClient;                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic member function signature of the statically inherited base class ( extended class )
                 * @protected to be reused in the deriving classes to keep type consistency
                 */
                using __GenericHandler  = auto ( __ReceiverType :: * ) () -> void;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                          /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for a generic member const function signature of the statically inherited base class ( extended class )
                 * @protected to be reused in the deriving classes to keep type consistency
                 */
                using __GenericConstHandler  = auto ( __ReceiverType :: * ) () const -> void;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                                  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to request a generic member function from the derived class. Used in derived client interfaces. Not pure virtual due to cpp-14 MinGW pure virtual constexpr issue
                 * @param [in] requestType : __CollectionInternalRequestType = The Type of Handler ( member-function ) requested from the derived class
                 * @exceptsafe
                 * @return __GenericHandler = Member Function Pointer of the Requested Type
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected must be overridden in derived class to pass the request to a server or to a server dispatcher
                 */
                __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto __cicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __CollectionInternalRequestType requestType
                ) noexcept -> __GenericHandler = 0;

            protected:                                                                                          /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to request a generic member const function from the derived class. Used in derived client interfaces. Not pure virtual due to cpp-14 MinGW pure virtual constexpr issue
                 * @param [in] requestType : __CollectionInternalRequestType = The Type of Const Handler ( member-const-function ) requested from the derived class
                 * @exceptsafe
                 * @return __GenericConstHandler = Member Const Function Pointer of the Requested Type
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected must be overridden in derived class to pass the request to a server or to a server dispatcher
                 */
                __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto __cicch_obtainGenericConstHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __CollectionInternalRequestType requestType
                ) const noexcept -> __GenericConstHandler = 0;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Constructor
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected
                 */
                constexpr __CollectionInternalCommunicationChannel () noexcept = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Copy Constructor
                 * @param __CollectionInternalCommunicationChannel cref = Constant Reference to the channel to copy data from
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected
                 */
                constexpr __CollectionInternalCommunicationChannel (
                        __CollectionInternalCommunicationChannel const &
                ) noexcept = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Move Constructor
                 * @param __CollectionInternalCommunicationChannel mref = Move Reference to the channel to move data from
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected
                 */
                constexpr __CollectionInternalCommunicationChannel (
                        __CollectionInternalCommunicationChannel &&
                ) noexcept = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Copy Operator
                 * @param __CollectionInternalCommunicationChannel cref = Constant Reference to the channel to copy data from
                 * @exceptsafe
                 * @return __CollectionInternalCommunicationChannel ref = Reference to the updated object
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected
                 */
                auto operator = (
                        __CollectionInternalCommunicationChannel const &
                ) noexcept -> __CollectionInternalCommunicationChannel & = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Move Operator
                 * @param __CollectionInternalCommunicationChannel mref = Move Reference to the channel to move data from
                 * @exceptsafe
                 * @return __CollectionInternalCommunicationChannel ref = Reference to the updated object
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @protected
                 */
                auto operator = (
                        __CollectionInternalCommunicationChannel &&
                ) noexcept -> __CollectionInternalCommunicationChannel & = default;

            public:
                /**
                 * @brief Override Destructor
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @public
                 */
                __CDS_cpplang_ConstexprDestructor ~__CollectionInternalCommunicationChannel () noexcept override;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#include "../../delegateIterator/impl/AbstractDelegateIterator.hpp"

#endif /* __CDS_SHARED_COLLECTION_INTERNAL_COMMUNICATION_HPP__ */
