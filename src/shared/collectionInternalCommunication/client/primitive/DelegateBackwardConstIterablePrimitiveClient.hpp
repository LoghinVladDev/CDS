/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
             * Note : This Client will request the const member functions identified with:
             *      __cirt_rbegin
             *      __cirt_rend
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
             *
             * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
             *      LTC-00202-IT-perValueImmCheck,
             *      LTC-00204-IT-perValueRevImmCheck,
             *      LTC-00206-IT-perValueBwdImmCheck,
             *      LTC-00208-IT-perValueRevBwdImmCheck
             * }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                             /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional                            /* NOLINT(bugprone-reserved-identifier) */
            > class __DelegateBackwardConstIterablePrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

            protected:
                /**
                 * @typedef internal alias representing the __ElementType template parameter
                 * @protected
                 */
                using __dbcic_ElementType   = /* NOLINT(bugprone-reserved-identifier) */
                        __ElementType const;

            public:
                /**
                 * @typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the ConstReverseIterator type.
                 * @public
                 */
                using ConstReverseIterator  = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __BidirectionalDelegateWrapperIterator < __dbcic_ElementType >,
                                __ForwardDelegateWrapperIterator < __dbcic_ElementType >
                        >;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rbegin request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, immutable, begin iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00202-IT-perValueImmCheck,
                 *      LTC-00204-IT-perValueRevImmCheck,
                 *      LTC-00206-IT-perValueBwdImmCheck,
                 *      LTC-00208-IT-perValueRevBwdImmCheck
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto rbegin () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rend request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, immutable, end iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00202-IT-perValueImmCheck,
                 *      LTC-00204-IT-perValueRevImmCheck,
                 *      LTC-00206-IT-perValueBwdImmCheck,
                 *      LTC-00208-IT-perValueRevBwdImmCheck
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto rend () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rbegin request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, immutable, begin iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00202-IT-perValueImmCheck,
                 *      LTC-00204-IT-perValueRevImmCheck,
                 *      LTC-00206-IT-perValueBwdImmCheck,
                 *      LTC-00208-IT-perValueRevBwdImmCheck
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto crbegin () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_rend request
                 * @exceptsafe
                 * @return ConstReverseIterator = Wrapper for the received backward, immutable, end iterator
                 *
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00202-IT-perValueImmCheck,
                 *      LTC-00204-IT-perValueRevImmCheck,
                 *      LTC-00206-IT-perValueBwdImmCheck,
                 *      LTC-00208-IT-perValueRevBwdImmCheck
                 * }
                 *
                 * @public
                 */
                __CDS_NoDiscard auto crend () const noexcept -> ConstReverseIterator;
            };


            /**
             * @class Interface for creating Local Backward Const Iterator requests.
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to implement an appropriate dispatcher ( __ListServerDispatcher or lower in hierarchy ),
             * or provide an equivalent __crbeginLocal and __crendLocal member function set to the one provided
             * by the dispatcher
             * @tparam __ConstReverseIteratorType is the type of the iterator returned by the rbegin / rend / crbegin / crend functions
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType                     /* NOLINT(bugprone-reserved-identifier) */
            > class __LocalDelegateBackwardConstIterablePrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @typedef alias for chosen const reverse iterator.
                 * @public
                 */
                using ConstReverseIterator = __ConstReverseIteratorType;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __crbeginLocal function
                 * @exceptsafe
                 * @return ConstReverseIterator = begin const iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard constexpr auto rbegin () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __crendLocal function
                 * @exceptsafe
                 * @return ConstReverseIterator = end const iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard constexpr auto rend () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __crbeginLocal function
                 * @exceptsafe
                 * @return ConstReverseIterator = begin const iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard constexpr auto crbegin () const noexcept -> ConstReverseIterator;

            public:
                /**
                 * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __crendLocal function
                 * @exceptsafe
                 * @return ConstReverseIterator = end const iterator
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard constexpr auto crend () const noexcept -> ConstReverseIterator;
            };

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ */