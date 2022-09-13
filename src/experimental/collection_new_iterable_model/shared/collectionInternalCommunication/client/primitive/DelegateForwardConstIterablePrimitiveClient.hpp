/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
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
                 *      __cirt_begin
                 *      __cirt_end
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional                        /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateForwardConstIterablePrimitiveClient { /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef internal alias representing the __ElementType template parameter
                     * @protected
                     */
                    using __dfcic_ElementType   = /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const;

                public:
                    /**
                     * @typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the ConstIterator type.
                     * @public
                     */
                    using ConstIterator         = /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: Conditional <
                                    __bidirectional,
                                    __BidirectionalDelegateWrapperIterator < __dfcic_ElementType >,
                                    __ForwardDelegateWrapperIterator < __dfcic_ElementType >
                            >;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_begin request
                     * @exceptsafe
                     * @return ConstIterator = Wrapper for the received forward, immutable, begin iterator
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
                     *      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
                     * @public
                     */
                    __CDS_NoDiscard auto begin () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_end request
                     * @exceptsafe
                     * @return ConstIterator = Wrapper for the received forward, immutable, end iterator
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
                     *      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
                     * @public
                     */
                    __CDS_NoDiscard auto end () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_begin request
                     * @exceptsafe
                     * @return ConstIterator = Wrapper for the received forward, immutable, begin iterator
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
                     *      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                     * @public
                     */
                    __CDS_NoDiscard auto cbegin () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_end request
                     * @exceptsafe
                     * @return ConstIterator = Wrapper for the received forward, immutable, end iterator
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
                     *      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                     * @public
                     */
                    __CDS_NoDiscard auto cend () const noexcept -> ConstIterator;
                };


                /**
                 * @class Interface for creating Local Forward Const Iterator requests.
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement an appropriate dispatcher ( __CollectionServerDispatcher or lower in hierarchy ),
                 * or provide an equivalent __cbeginLocal and __cendLocal member function set to the one provided
                 * by the dispatcher
                 * @tparam __ConstIteratorType is the type of the iterator returned by the begin / end / cbegin / cend functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType                            /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalDelegateForwardConstIterablePrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @typedef alias for chosen const iterator.
                     * @public
                     */
                    using ConstIterator = __ConstIteratorType;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __cbeginLocal function
                     * @exceptsafe
                     * @return ConstIterator = begin const iterator
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __cendLocal function
                     * @exceptsafe
                     * @return ConstIterator = end const iterator
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __cbeginLocal function
                     * @exceptsafe
                     * @return ConstIterator = begin const iterator
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

                public:
                    /**
                     * @brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __cendLocal function
                     * @exceptsafe
                     * @return ConstIterator = end const iterator
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ */
