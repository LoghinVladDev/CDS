//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_ITERATOR_HPP__
#define __CDS_SHARED_DELEGATE_ITERATOR_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                namespace meta {
                    template <
                            typename,
                            typename = void
                    > struct __WrappedIteratorBidirectional : cds :: meta :: FalseType {}; // NOLINT(bugprone-reserved-identifier)

                    template <
                            typename __TWrappedIteratorType // NOLINT(bugprone-reserved-identifier)
                    > struct __WrappedIteratorBidirectional < __TWrappedIteratorType, cds :: meta :: Void < decltype ( -- cds :: meta :: referenceOf < __TWrappedIteratorType > () ) > > : cds :: meta :: TrueType {}; // NOLINT(bugprone-reserved-identifier)
                }

                template <
                        typename __ElementType,                                                     // NOLINT(bugprone-reserved-identifier)
                        typename __WrappedIteratorType                                              // NOLINT(bugprone-reserved-identifier)
                > class __DelegateIterator : public __AbstractDelegateIterator < __ElementType > {  // NOLINT(bugprone-reserved-identifier)

                public:
                    using ElementType   = __ElementType;

                public:
                    using IteratorType  = __WrappedIteratorType;

                private:
                    IteratorType _wrappedIterator;

                public:
                    constexpr __DelegateIterator () noexcept;

                public:
                    __CDS_Explicit constexpr __DelegateIterator (
                            IteratorType const & iterator
                    ) noexcept;

                public:
                    __CDS_Explicit constexpr __DelegateIterator (
                            IteratorType && iterator
                    ) noexcept;

                public:
                    constexpr __DelegateIterator (
                            __DelegateIterator const & iterator
                    ) noexcept;

                public:
                    constexpr __DelegateIterator (
                            __DelegateIterator && iterator
                    ) noexcept;

                public:
                    __CDS_cpplang_ConstexprDestructor ~__DelegateIterator () noexcept override;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto iterator () const noexcept -> __GenericIterator override;

                private:
                    template <
                            typename __TWrappedIteratorType = __WrappedIteratorType,  // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf < meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value > = 0
                    > constexpr auto __advanceBackwards () noexcept -> void; // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            typename __TWrappedIteratorType = __WrappedIteratorType,  // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf < ! meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value > = 0
                    > constexpr auto __advanceBackwards () noexcept -> void; // NOLINT(bugprone-reserved-identifier)

                public:
                    __CDS_cpplang_ConstexprPureAbstract auto advance (
                            __IteratorAdvanceDirection direction
                    ) noexcept -> void override;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals (
                            __AbstractDelegateIterator < __ElementType > const & iterator
                    ) const noexcept -> bool override;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override;

                public:
                    __CDS_NoDiscard auto copy () const noexcept -> __AbstractDelegateIterator < __ElementType > * override;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto value () const noexcept -> ElementType & override;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_DELEGATE_ITERATOR_HPP__
