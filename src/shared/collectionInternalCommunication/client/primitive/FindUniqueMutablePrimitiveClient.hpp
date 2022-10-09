/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @interface Interface for creating Abstract Iterator find requests and creating Wrapper Iterators for received Iterators. Used when Iterable Elements are Unique
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to be derived from either the Map abstract class or
             * a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
             * function implementations provided by the __CollectionInternalCommunicationChannel class
             * Note : This Client will request the member functions identified with:
             *      __cirt_find
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __KeyType is the type given as parameter for the element identification. In Set, this is the ElementType, while in Map, it is the KeyType of a MapEntry
             * @tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                    bool     __bidirectional                /* NOLINT(bugprone-reserved-identifier) */
            > class __FindUniqueMutablePrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the Iterator type.
                 * @public
                 */
                using Iterator =
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __BidirectionalDelegateWrapperIterator < __ElementType >,
                                __ForwardDelegateWrapperIterator < __ElementType >
                        >;

            public:
                /**
                 * @brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using a __cirt_find request
                 * @param [in] key : __KeyType cref = Constant Reference to the value used to identify the searched value
                 * @exceptsafe
                 * @return Iterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType :: end ()
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard auto find (
                        __KeyType const & key
                ) noexcept -> Iterator;
            };


            /**
             * @interface Interface for creating Local Iterator find requests. Used when Iterable Elements are Unique
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to implement an appropriate dispatcher ( __MapServerDispatcher or lower in hierarchy ),
             * or provide an equivalent __findLocal member function set to the one provided
             * by the dispatcher
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __KeyType is the type given as parameter for the element identification. In Map, it is the KeyType of a MapEntry
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType                     /* NOLINT(bugprone-reserved-identifier) */
            > class __LocalFindUniqueMutablePrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @typedef alias for the __IteratorType template parameter
                 * @public
                 */
                using Iterator = __IteratorType;

            public:
                /**
                 * @brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using the __findLocal function
                 * @param [in] key : __KeyType cref = Constant Reference to the value used to identify the searched value
                 * @exceptsafe
                 * @return Iterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType :: cend ()
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard auto find (
                        __KeyType const & key
                ) noexcept -> Iterator;
            };

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ */
