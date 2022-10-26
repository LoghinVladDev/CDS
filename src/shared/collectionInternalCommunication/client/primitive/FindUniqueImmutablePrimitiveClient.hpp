/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @interface Interface for creating Abstract Const Iterator find requests and creating Wrapper Iterators for received Iterators. Used when Iterable Elements are Unique
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to be derived from either the Set / Map abstract class or
             * a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
             * function implementations provided by the __CollectionInternalCommunicationChannel class
             * Note : This Client will request the const member functions identified with:
             *      __cirt_findConst
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __KeyType is the type given as parameter for the element identification. In Set, this is the ElementType, while in Map, it is the KeyType of a MapEntry
             * @tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
             *
             * @test Suite: STS-00001, Group: STG-00050-FU, Test Cases: All
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool     __bidirectional                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __FindUniqueImmutablePrimitiveClient {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the ConstIterator type.
                 * @public
                 */
                using ConstIterator =
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __BidirectionalDelegateWrapperIterator < __ElementType const >,
                                __ForwardDelegateWrapperIterator < __ElementType const >
                >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using a __cirt_findConst request
                 * @param [in] key : __KeyType cref = Constant Reference to the value used to identify the searched value
                 * @exceptsafe
                 * @return ConstIterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType :: cend ()
                 * @test Suite: STS-00001, Group: STG-00050-FU, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard auto find (
                        __KeyType const & key
                ) const noexcept -> ConstIterator;
            };


            /**
             * @interface Interface for creating Local Const Iterator find requests. Used when Iterable Elements are Unique
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is also required to implement an appropriate dispatcher ( __SetServerDispatcher or lower in hierarchy ),
             * or provide an equivalent __findConstLocal member function set to the one provided
             * by the dispatcher
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __KeyType is the type given as parameter for the element identification. In Set, this is the ElementType, while in Map, it is the KeyType of a MapEntry
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __LocalFindUniqueImmutablePrimitiveClient { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for the __IteratorType template parameter
                 * @public
                 */
                using ConstIterator = __IteratorType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using the __findConstLocal function
                 * @param [in] key : __KeyType cref = Constant Reference to the value used to identify the searched value
                 * @exceptsafe
                 * @return ConstIterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType :: cend ()
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard auto find (
                        __KeyType const & key
                ) const noexcept -> ConstIterator;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_HPP__ */
