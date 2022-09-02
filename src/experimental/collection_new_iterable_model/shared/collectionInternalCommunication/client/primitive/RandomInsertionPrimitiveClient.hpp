/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                namespace meta {

                    /**
                     * @struct Meta-Type used to determine if a given type has the 'size' function available. By default false
                     * @tparam __IterableType is the type to be checked
                     * @test Not Applicable
                     * @namespace cds :: experimental :: __hidden :: __impl :: meta
                     * @internal library-private
                     */
                    template < typename __IterableType, typename = void >           /* NOLINT(bugprone-reserved-identifier) */
                    struct __IterableSizeAvailable : cds :: meta :: FalseType {};   /* NOLINT(bugprone-reserved-identifier) */

                    /**
                     * @struct Meta-Type used to determine if a given type has the 'size' function available. True when type can call size()
                     * @tparam __IterableType is the type to be checked
                     * @test Not Applicable
                     * @namespace cds :: experimental :: __hidden :: __impl :: meta
                     * @internal library-private
                     */
                    template < typename __IterableType >                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    struct __IterableSizeAvailable < __IterableType, cds :: meta :: Void < decltype ( cds :: meta :: addressOf < __IterableType > ()->size() ) > > : cds :: meta :: TrueType {};    /* NOLINT(bugprone-reserved-identifier) */

                }

                /**
                 * @struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __ElementType
                 * @tparam __ElementType is the type of element constructed to check for construction noexcept specification
                 * @tparam __FirstConstructedArgument is the type of parameter given to constructor
                 * @test Not Applicable
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __FirstConstructedArgument /* NOLINT(bugprone-reserved-identifier) */
                > struct __ConstructExceptSpecOne {         /* NOLINT(bugprone-reserved-identifier) */

                    /* the value is the noexcept value of the constructor call */
                    constexpr static bool value = noexcept ( __ElementType ( cds :: meta :: valueOf < __FirstConstructedArgument > () ) );
                };


                /**
                 * @struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __ElementType
                 * @tparam __ElementType is the type of element constructed to check for construction noexcept specification
                 * @tparam __FirstConstructedArgument is the type of the first parameter given to construction
                 * @tparam __RemainingConstructedArguments is the parameter type pack of the remaining parameters given to construction
                 * @test Not Applicable
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __FirstConstructedArgument,            /* NOLINT(bugprone-reserved-identifier) */
                        typename ... __RemainingConstructedArguments    /* NOLINT(bugprone-reserved-identifier) */
                > struct __ConstructExceptSpecMultiple;                 /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __ElementType
                 * @tparam __ElementType is the type of element constructed to check for construction noexcept specification
                 * @tparam __FirstConstructedArgument is the type of the first parameter given to construction
                 * @test Not Applicable
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ElementType,                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __FirstConstructedArgument                                             /* NOLINT(bugprone-reserved-identifier) */
                > struct __ConstructExceptSpecMultiple < __ElementType, __FirstConstructedArgument > {  /* NOLINT(bugprone-reserved-identifier) */

                    /* when only one type remaining, call noexcept spec of One value constructed */
                    constexpr static bool value =
                            __ConstructExceptSpecOne < __ElementType, __FirstConstructedArgument > :: value;
                };


                /**
                 * @struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __ElementType
                 * @tparam __ElementType is the type of element constructed to check for construction noexcept specification
                 * @tparam __FirstConstructedArgument is the type of the first parameter given to construction
                 * @tparam __RemainingConstructedArguments is the parameter type pack of the remaining parameters given to construction
                 * @test Not Applicable
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __FirstConstructedArgument,            /* NOLINT(bugprone-reserved-identifier) */
                        typename ... __RemainingConstructedArguments    /* NOLINT(bugprone-reserved-identifier) */
                > struct __ConstructExceptSpecMultiple {                /* NOLINT(bugprone-reserved-identifier) */

                    /* when more than or two values are to be constructed, acquire the noexcept spec of the current one, use and on the
                     * noexcept spec of the remaining types */
                    constexpr static bool value =
                            __ConstructExceptSpecOne < __ElementType, __FirstConstructedArgument > :: value &&
                            __ConstructExceptSpecMultiple < __ElementType, __RemainingConstructedArguments ... > :: value;
                };


                /**
                 * @interface Interface for creating Random Insertion requests, inserting / emplacing elements without a specified location.
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either be derived from the Collection abstract class or a class
                 * extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
                 * function implementations provided by the __collectionInternalCommunicationChannel class
                 * Note : This Client will request the member functions identified with:
                 *      __cirt_newAddress
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: All
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType               /* NOLINT(bugprone-reserved-identifier) */
                > class __RandomInsertionPrimitiveClient {  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef alias for __ElementType template parameter
                     * @private
                     */
                    using ElementType       = __ElementType;

                private:
                    /**
                     * @typedef alias for __ReturnType template parameter reference
                     * @private
                     */
                    using ElementReference  = __ReturnType &;

                private:
                    /**
                     * @brief Function used to insert multiple elements of a parameter pack into a given accumulator value
                     * @tparam __AccumulatorType is the type of value to insert the elements into
                     * @tparam __LastType is the type last inserted into the accumulator
                     * @param pAccumulator
                     * @param lastValue
                     */
                    template <
                            typename __AccumulatorType, /* NOLINT(bugprone-reserved-identifier) */
                            typename __LastType         /* NOLINT(bugprone-reserved-identifier) */
                    > friend auto __expansiveInsert (   /* NOLINT(bugprone-reserved-identifier) */
                            __AccumulatorType   * pAccumulator,
                            __LastType         && lastValue
                    ) noexcept ( false ) -> void;

                private:
                    template <
                            typename     __AccumulatorType, /* NOLINT(bugprone-reserved-identifier) */
                            typename     __FirstType,       /* NOLINT(bugprone-reserved-identifier) */
                            typename ... __RemainingTypes   /* NOLINT(bugprone-reserved-identifier) */
                    > friend auto __expansiveInsert (       /* NOLINT(bugprone-reserved-identifier) */
                            __AccumulatorType      *     pAccumulator,
                            __FirstType           &&     firstValue,
                            __RemainingTypes      && ... remainingValues
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType const & element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType && element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType const & element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType && element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplace (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( false ) -> void;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAll' has been deprecated. Use 'Collection :: insertAll' instead") auto addAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOf (
                            __IterableType const & iterable
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( false ) -> void;


                public:
                    template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IterableType const & iterable
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( false ) -> void;
                };


                /**
                 * @interface Interface for creating Local Random Insertion requests, inserting / emplacing elements without a specified location.
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either implement an appropriate dispatcher ( __CollectionServerDispatcher or lower
                 * in hierarchy ) or provide an equivalent __newAddress member function to the one provided by the dispatcher
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                   /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalRandomInsertionPrimitiveClient { /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                private:
                    template <
                            typename __AccumulatorType, /* NOLINT(bugprone-reserved-identifier) */
                            typename __LastType         /* NOLINT(bugprone-reserved-identifier) */
                    > friend auto __expansiveInsert (   /* NOLINT(bugprone-reserved-identifier) */
                            __AccumulatorType   * pAccumulator,
                            __LastType         && lastValue
                    ) noexcept ( false ) -> void;

                private:
                    template <
                            typename     __AccumulatorType, /* NOLINT(bugprone-reserved-identifier) */
                            typename     __FirstType,       /* NOLINT(bugprone-reserved-identifier) */
                            typename ... __RemainingTypes   /* NOLINT(bugprone-reserved-identifier) */
                    > friend auto __expansiveInsert (       /* NOLINT(bugprone-reserved-identifier) */
                            __AccumulatorType      *     pAccumulator,
                            __FirstType           &&     firstValue,
                            __RemainingTypes      && ... remainingValues
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType const & element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType && element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType const & element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType && element
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplace (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( false ) -> ElementReference;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( false ) -> void;

                public:
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAll' has been deprecated. Use 'Collection :: insertAll' instead") auto addAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOf (
                            __IterableType const & iterable
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( false ) -> void;


                public:
                    template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IterableType const & iterable
                    ) noexcept ( false ) -> void;

                public:
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( false ) -> void;

                public:
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept ( false ) -> void;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ */
