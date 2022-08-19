/*
 * Created by loghin on 7/7/2022.
 */

#ifndef __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__
#define __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @class Represents the type of iterator dispatcher that will be used if no
                 * Forward Iteration is possible -> no functions
                 */
                class __DelegateIterableServerIteratorNoService {};   /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @class Represents the type of iterator dispatcher that will be used if Forward Iteration is possible
                 * @tparam __ReceiverType is the type of the 'interface' class implementing the interface (i.e. Array)
                 * @tparam __ElementType  is the element type enclosed in the 'interface' class (i.e. int in Array \< int \>)
                 * @tparam __IteratorType is the type of the base iterator of the 'interface' class (i.e. Array :: Iterator (=shared/__Array :: __a_Iterator))
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                     /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateIterableServerIteratorService {   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef Internal Alias for the wrapper type that will be created with the received iterator from the implementation
                     * @protected
                     */
                    using __disis_Delegate = __DelegateIterator < __ElementType, __IteratorType >;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the begin function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __begin () noexcept -> __AbstractDelegateIterator < __ElementType > *;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the end function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __end () noexcept -> __AbstractDelegateIterator < __ElementType > *;       /* NOLINT(bugprone-reserved-identifier) */
                };


                /**
                 * @class Represents the type of iterator dispatcher that will be used if Forward Const Iteration is possible
                 * @tparam __ReceiverType is the type of the 'interface' class implementing the interface (i.e. Array)
                 * @tparam __ElementType  is the element type enclosed in the 'interface' class (i.e. int in Array \< int \>)
                 * @tparam __IteratorType is the type of the base iterator of the 'interface' class (i.e. Array :: Iterator (=shared/__Array :: __a_Iterator))
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                         /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateIterableServerConstIteratorService {  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef Internal Alias for the wrapper type that will be created with the received iterator from the implementation
                     * @protected
                     */
                    using __discis_Delegate = __DelegateIterator < __ElementType const, __IteratorType >;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the cbegin function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard auto __cbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the cend function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard auto __cend () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;       /* NOLINT(bugprone-reserved-identifier) */
                };


                /**
                 * @class Represents the type of iterator dispatcher that will be used if no
                 * Backward Iteration is possible -> no functions
                 */
                class __DelegateIterableServerReverseIteratorNoService {};    /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @class Represents the type of iterator dispatcher that will be used if Backward Iteration is possible
                 * @tparam __ReceiverType is the type of the 'interface' class implementing the interface (i.e. Array)
                 * @tparam __ElementType  is the element type enclosed in the 'interface' class (i.e. int in Array \< int \>)
                 * @tparam __IteratorType is the type of the base iterator of the 'interface' class (i.e. Array :: Iterator (=shared/__Array :: __a_Iterator))
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                             /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateIterableServerReverseIteratorService {    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef Internal Alias for the wrapper type that will be created with the received iterator from the implementation
                     * @protected
                     */
                    using __disris_Delegate = __DelegateIterator < __ElementType, __IteratorType >;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the rbegin function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __rbegin () noexcept -> __AbstractDelegateIterator < __ElementType > *;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the rend function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __rend () noexcept -> __AbstractDelegateIterator < __ElementType > *;       /* NOLINT(bugprone-reserved-identifier) */
                };


                /**
                 * @class Represents the type of iterator dispatcher that will be used if no
                 * Backward Const Iteration is possible -> no functions
                 */
                class __DelegateIterableServerConstReverseIteratorNoService {};   /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @class Represents the type of iterator dispatcher that will be used if Backward Const Iteration is possible
                 * @tparam __ReceiverType is the type of the 'interface' class implementing the interface (i.e. Array)
                 * @tparam __ElementType  is the element type enclosed in the 'interface' class (i.e. int in Array \< int \>)
                 * @tparam __IteratorType is the type of the base iterator of the 'interface' class (i.e. Array :: Iterator (=shared/__Array :: __a_Iterator))
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                                 /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateIterableServerConstReverseIteratorService {   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef Internal Alias for the wrapper type that will be created with the received iterator from the implementation
                     * @protected
                     */
                    using __discris_Delegate = __DelegateIterator < __ElementType const, __IteratorType >;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the crbegin function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __crbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;     /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to obtain a new delegate iterator using the crend function
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Address of the newly created iterator
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __crend () const noexcept -> __AbstractDelegateIterator < __ElementType const > *;       /* NOLINT(bugprone-reserved-identifier) */
                };


                /**
                 * @interface Server-Dispatcher-Type Class part of the Collection Communication Model, to be
                 *      extended in derived classes as a dispatcher between server iterator requests received
                 *      through Collection Communication Channels and wrapped iterators acquired from
                 *      member iterator functions. If provides the standard calls required by the server,
                 *      and enforces the function signatures via static polymorphism calls.
                 *
                 * @interface A dispatcher acts as the next layer, a connector between the derived class, that acts
                 *      as an interface to its' implementation class. This dispatcher interface contains the function
                 *      required for iterator requests
                 *
                 * @tparam __ServerType                     is the type of the server interface type (i.e. Array)
                 * @tparam __ElementType                    is the enclosed element (i.e. int in Array \< int \>)
                 * @tparam __mutable                        is a switch property. 'true' if collection is mutable ( mutable iterators can be requested - begin/end/rbegin/rend )
                 * @tparam __bidirectional                  is a switch property. 'true' if collection is bidirectionally parseable ( reverse iteration possible - rbegin/rend/crbegin/crend )
                 * @tparam __MutableForwardIteratorType     is the type returned by begin/end mutable calls. void if __mutable is 'false'
                 * @tparam __ImmutableForwardIteratorType   is the type returned by begin/end/cbegin/cend immutable calls.
                 * @tparam __MutableBackwardIteratorType    is the type returned by rbegin/rend mutable calls. void if __bidirectional is 'false' or __mutable is 'false'
                 * @tparam __ImmutableBackwardIteratorType  is the type returned by crbegin/crend immutable calls. void if __bidirectional is 'false'
                 *
                 * @extends __DelegateIterableServerIteratorService                 if __mutable is 'true'
                 * @extends __DelegateIterableServerIteratorNoService               if __mutable is 'false'
                 *
                 * @extends __DelegateIterableServerConstIteratorService
                 *
                 * @extends __DelegateIterableServerReverseIteratorService          if __mutable is 'true' and __bidirectional is 'true'
                 * @extends __DelegateIterableServerReverseIteratorNoService        if __mutable is 'false' or __bidirectional is 'false'
                 *
                 * @extends __DelegateIterableServerConstReverseIteratorService     if __bidirectional is 'true'
                 * @extends __DelegateIterableServerConstReverseIteratorNoService   if __bidirectional is 'false'
                 *
                 * @test All Tests involving Collections apply
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        bool     __mutable,                         /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __MutableForwardIteratorType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename __ImmutableForwardIteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                        typename __MutableBackwardIteratorType,     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ImmutableBackwardIteratorType    /* NOLINT(bugprone-reserved-identifier) */
                > class __DelegateIterableServer :                  /* NOLINT(bugprone-reserved-identifier) */
                        public cds :: meta :: Conditional <
                                __mutable,
                                __DelegateIterableServerIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __MutableForwardIteratorType
                                >,
                                __DelegateIterableServerIteratorNoService
                        >,
                        public __DelegateIterableServerConstIteratorService <
                                __ReceiverType,
                                __ElementType,
                                __ImmutableForwardIteratorType
                        >,
                        public cds :: meta :: Conditional <
                                __mutable && __bidirectional,
                                __DelegateIterableServerReverseIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __MutableBackwardIteratorType
                                >,
                                __DelegateIterableServerReverseIteratorNoService
                        >,
                        public cds :: meta :: Conditional <
                                __bidirectional,
                                __DelegateIterableServerConstReverseIteratorService <
                                        __ReceiverType,
                                        __ElementType,
                                        __ImmutableBackwardIteratorType
                                >,
                                __DelegateIterableServerConstReverseIteratorNoService
                        > {

                };

            }
        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_ITERABLE_SERVER_HPP__ */
