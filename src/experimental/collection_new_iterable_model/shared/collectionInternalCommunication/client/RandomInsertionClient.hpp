//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_RANDOM_INSERTION_CLIENT_HPP__
#define __CDS_SHARED_RANDOM_INSERTION_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ReturnType       // NOLINT(bugprone-reserved-identifier)
                > class __RandomInsertionClient {   // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType       = __ElementType;

                private:
                    using ElementReference  = __ReturnType &;

                private:
                    template <
                            typename __AccumulatorType, // NOLINT(bugprone-reserved-identifier)
                            typename __LastType         // NOLINT(bugprone-reserved-identifier)
                    > friend auto __expansiveInsert (   // NOLINT(bugprone-reserved-identifier)
                            __AccumulatorType   * pAccumulator,
                            __LastType         && lastValue
                    ) noexcept (false) -> void;

                private:
                    template <
                            typename     __AccumulatorType, // NOLINT(bugprone-reserved-identifier)
                            typename     __FirstType,       // NOLINT(bugprone-reserved-identifier)
                            typename ... __RemainingTypes   // NOLINT(bugprone-reserved-identifier)
                    > friend auto __expansiveInsert (       // NOLINT(bugprone-reserved-identifier)
                            __AccumulatorType      *     pAccumulator,
                            __FirstType           &&     firstValue,
                            __RemainingTypes      && ... remainingValues
                    ) noexcept (false) -> void;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insert (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType const & element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template <
                            typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'Collection :: add' has been deprecated. Use 'Collection :: insert' instead") auto add (
                            ElementType && element
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __EmplaceArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto emplace (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept (false) -> ElementReference;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    auto insertAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
                    __CDS_DeprecatedHint ("'Collection :: addAll' has been deprecated. Use 'Collection :: insertAll' instead") auto addAll (
                            __ArgumentTypes && ... values
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOf (
                            __IterableType const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    auto insertAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IterableType const & iterableType
                    ) noexcept (false) -> void;

                protected:
                    template < typename __IteratorType > // NOLINT(bugprone-reserved-identifier)
                    __CDS_DeprecatedHint ("'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead") auto addAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end
                    ) noexcept (false) -> void;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_RANDOM_INSERTION_CLIENT_HPP__
