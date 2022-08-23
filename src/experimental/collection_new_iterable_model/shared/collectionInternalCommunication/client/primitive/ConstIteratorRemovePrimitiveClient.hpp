/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @class pre-declaration of Abstract Delegate Wrapper Iterator, to be used by Remove Client as Abstract Iterator
                 */
                template < typename >
                class __AbstractDelegateWrapperIterator;    /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @interface Interface for creating Abstract Const Iterator remove requests.
                 *
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism
                 * @tparam __ElementType is the type of elements enclosed in the object
                 *
                 * @test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: All
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                          /* NOLINT(bugprone-reserved-identifier) */
                > class __AbstractConstIteratorRemovePrimitiveClient {  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @brief friend declaration, functions from primitive client used by RemoveBy Composite Client
                     * @private
                     */
                    template < typename, typename >
                    friend class __RemoveByCompositeClient; /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @brief friend declaration, functions from primitive client used by RemoveOf Composite Client
                     * @private
                     */
                    template <
                            typename,
                            typename __FElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            typename __FIterableType,   /* NOLINT(bugprone-reserved-identifier) */
                            __ContainsFunction < __FIterableType, __FElementType >
                    > friend class __RemoveOfCompositeClient;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef internal alias representing the __ElementType const parameter
                     * @protected
                     */
                    using __acirc_ElementType       = /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const;

                protected:
                    /**
                     * @typedef internal alias representing the iterator parameter type
                     * @protected
                     */
                    using AbstractConstIterator     = /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractDelegateWrapperIterator < __acirc_ElementType >;

                public:
                    /**
                     * @brief Function used to create a request to remove an element indicated to by the given iterator
                     * @param iterator : AbstractConstIterator cref = Constant Reference to the iterator to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: {
                     *      CTC-00351-RAIT-removeAtFront,
                     *      CTC-00352-RAIT-removeInBounds,
                     *      CTC-00353-RAIT-removeAtEnd,
                     *      CTC-00355-RAIT-removeBeforeFront,
                     *      CTC-00356-RAIT-removeFromOther
                     * }
                     *
                     * @public
                     */
                    auto remove (
                            AbstractConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to create a request to remove several elements indicated to by the given iterators in the array
                     * @param pIterators : AbstractConstIterator cptr = Address to an array of constant Abstract Const Iterator values
                     * @param iteratorCount : Size = number of values enclosed in the array given at pIterators
                     * @exceptsafe
                     * @return Size = number of elements that were removed successfully
                     *
                     * @test Suite: CTS-00001, Group: TBA, Test Cases: TBA
                     *
                     * @protected Unused by implementor class, used by other clients. Do not inherit public
                     */
                    auto removeAll (
                            AbstractConstIterator const * pIterators,
                            Size                          iteratorCount
                    ) noexcept -> Size;
                };


                /**
                 * @interface Interface for creating Local Const Iterator remove requests. ( not through channel, through function )
                 *
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism
                 * @tparam __ElementType is the type of elements enclosed in the object
                 * @tparam __IteratorType is the iterator type to be expected as parameter to the functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                     /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalConstIteratorRemovePrimitiveClient { /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef internal alias representing the __ElementType const parameter
                     * @protected
                     */
                    using __acirc_ElementType       = /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const;

                protected:
                    /**
                     * @typedef internal alias representing the iterator parameter type
                     * @protected
                     */
                    using ConstIterator             = __IteratorType;

                public:
                    /**
                     * @brief Function used to create a request to remove an element indicated to by the given iterator
                     * @param iterator : ConstIterator cref = Constant Reference to the iterator to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    auto remove (
                            ConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to create a request to remove several elements indicated to by the given iterators in the array
                     * @param pIterators : ConstIterator cptr = Address to an array of constant Const Iterator values
                     * @param iteratorCount : Size = number of values enclosed in the array given at pIterators
                     * @exceptsafe
                     * @return Size = number of elements that were removed successfully
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @protected Unused by implementor class, used by other clients. Do not inherit public
                     */
                    auto removeAll (
                            ConstIterator const * pIterators,
                            Size                  iteratorCount
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ */
