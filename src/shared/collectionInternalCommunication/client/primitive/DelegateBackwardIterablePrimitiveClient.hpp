/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @class pre-declaration of Bi-Directional Abstract Iterator Wrapper, to be used in Conditional
             */
            template < typename >
            class __BidirectionalDelegateWrapperIterator;   /* NOLINT(bugprone-reserved-identifier) */


            /**
             * @class pre-declaration of Uni-Directional Abstract Iterator Wrapper, to be used in Conditional
             */
            template < typename >
            class __ForwardDelegateWrapperIterator; /* NOLINT(bugprone-reserved-identifier) */


            /**
             * @interface Interface for creating Abstract Iterator requests and creating Wrapper Iterators for received Iterators
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to be derived from either the Collection abstract class or
             * a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
             * function implementations provided by the __CollectionInternalCommunicationChannel class
             * Note : This Client will request the member functions identified with:
             *      __cirt_rbegin
             *      __cirt_rend
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
             *
             * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
             *      LTC-00201-IT-perValueCheck,
             *      LTC-00203-IT-perValueRevCheck,
             *      LTC-00205-IT-perValueBwdCheck,
             *      LTC-00207-IT-perValueRevBwdCheck,
             *      LTC-00209-IT-itMutabilityRange,
             *      LTC-00210-IT-itMutabilityStd,
             *      LTC-00211-IT-itMutabilityStdRev
             * }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional                    /* NOLINT(bugprone-reserved-identifier) */
            > class __DelegateBackwardIterablePrimitiveClient { /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @typedef internal alias representing the __ElementType template parameter
                 * @protected
                 */
                using __dbic_ElementType   = /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType;

            public:
                /**
                 * @typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the ReverseIterator type.
                 * @public
                 */
                using ReverseIterator      = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __BidirectionalDelegateWrapperIterator < __dbic_ElementType >,
                                __ForwardDelegateWrapperIterator < __dbic_ElementType >
                        >;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rbegin request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, mutable, begin iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00201-IT-perValueCheck,
                 *      LTC-00203-IT-perValueRevCheck,
                 *      LTC-00205-IT-perValueBwdCheck,
                 *      LTC-00207-IT-perValueRevBwdCheck,
                 *      LTC-00209-IT-itMutabilityRange,
                 *      LTC-00210-IT-itMutabilityStd,
                 *      LTC-00211-IT-itMutabilityStdRev
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto rbegin () noexcept -> ReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rend request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, mutable, end iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00201-IT-perValueCheck,
                 *      LTC-00203-IT-perValueRevCheck,
                 *      LTC-00205-IT-perValueBwdCheck,
                 *      LTC-00207-IT-perValueRevBwdCheck,
                 *      LTC-00209-IT-itMutabilityRange,
                 *      LTC-00210-IT-itMutabilityStd,
                 *      LTC-00211-IT-itMutabilityStdRev
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto rend () noexcept -> ReverseIterator;
            };


            /**
             * @class Interface for creating Local Backward Iterator requests.
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to implement an appropriate dispatcher ( __ListServerDispatcher or lower in hierarchy ),
             * or provide an equivalent __rbeginLocal and __rendLocal member function set to the one provided
             * by the dispatcher
             * @tparam __ReverseIteratorType is the type of the iterator returned by the rbegin / rend functions
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType                      /* NOLINT(bugprone-reserved-identifier) */
            > class __LocalDelegateBackwardIterablePrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @typedef alias for chosen reverse iterator.
                 * @public
                 */
                using ReverseIterator = __ReverseIteratorType;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __rbeginLocal function
                 * @exceptsafe
                 * @return ReverseIterator = begin iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __rendLocal function
                 * @exceptsafe
                 * @return ReverseIterator = end iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rend () noexcept -> ReverseIterator;
            };

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ */
