/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
                 * @interface Interface for creating Abstract Iterator remove requests.
                 *
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to be derived from either the Collection abstract class or
                 * a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
                 * function implementations provided by the __CollectionInternalCommunicationChannel class
                 * Note : This Client will request the member functions identified with:
                 *      __cirt_remove
                 *      __cirt_removeArray
                 *
                 * @tparam __ElementType is the type of elements enclosed in the object
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                      /* NOLINT(bugprone-reserved-identifier) */
                > class __AbstractIteratorRemovePrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef internal alias representing the __ElementType parameter
                     * @protected
                     */
                    using __acirc_ElementType       = /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType;

                protected:
                    /**
                     * @typedef internal alias representing the iterator parameter type
                     * @protected
                     */
                    using AbstractIterator          = /* NOLINT(bugprone-reserved-identifier) */
                            __AbstractDelegateWrapperIterator < __acirc_ElementType >;

                public:
                    /**
                     * @brief Function used to create a request to remove an element indicated to by the given iterator
                     * @param iterator : AbstractIterator cref = Constant Reference to the iterator to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    auto remove (
                            AbstractIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to create a request to remove several elements indicated to by the given iterators in the array
                     * @param pIterators : AbstractIterator cptr = Address to an array of constant Abstract Iterator values
                     * @param iteratorCount : Size = number of values enclosed in the array given at pIterators
                     * @exceptsafe
                     * @return Size = number of elements that were removed successfully
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @protected Unused by implementor class, used by other clients. Do not inherit public
                     */
                    auto removeAll (
                            AbstractIterator const * pIterators,
                            Size                     iteratorCount
                    ) noexcept -> Size;
                };


                /**
                 * @interface Interface for creating Local Iterator remove requests. ( not through channel, through function )
                 *
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is also required to implement an appropriate dispatcher ( __CollectionServerDispatcher or lower in hierarchy ),
                 * or provide an equivalent __remove and __removeArray member function set to the one provided
                 * by the dispatcher
                 * @tparam __ElementType is the type of elements enclosed in the object
                 * @tparam __IteratorType is the iterator type to be expected as parameter to the functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                  /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalIteratorRemovePrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef internal alias representing the __ElementType const parameter
                     * @protected
                     */
                    using __acirc_ElementType   = /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType;

                protected:
                    /**
                     * @typedef internal alias representing the iterator parameter type
                     * @protected
                     */
                    using Iterator              = /* NOLINT(bugprone-reserved-identifier) */
                            __IteratorType;

                public:
                    /**
                     * @brief Function used to create a request to remove an element indicated to by the given iterator
                     * @param iterator : Iterator cref = Constant Reference to the iterator to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    auto remove (
                            Iterator const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to create a request to remove several elements indicated to by the given iterators in the array
                     * @param pIterators : Iterator cptr = Address to an array of constant Const Iterator values
                     * @param iteratorCount : Size = number of values enclosed in the array given at pIterators
                     * @exceptsafe
                     * @return Size = number of elements that were removed successfully
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @protected Unused by implementor class, used by other clients. Do not inherit public
                     */
                    auto removeAll (
                            Iterator const * pIterators,
                            Size             iteratorCount
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ */
