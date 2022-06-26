//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                                                                                 // NOLINT(bugprone-reserved-identifier)
                class __BidirectionalDelegateWrapperIterator : public __AbstractDelegateWrapperIterator < __ElementType >, public meta :: BidirectionalIterator {   // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType;

                public:
                    constexpr __BidirectionalDelegateWrapperIterator () noexcept;

                public:
                    constexpr __BidirectionalDelegateWrapperIterator (
                            Object                                          const * pOwner,
                            __AbstractDelegateIterator < __ElementType >          * pDelegate
                    ) noexcept;

                public:
                    __BidirectionalDelegateWrapperIterator (
                            __BidirectionalDelegateWrapperIterator const & iterator
                    ) noexcept;

                public:
                    constexpr __BidirectionalDelegateWrapperIterator (
                            __BidirectionalDelegateWrapperIterator && iterator
                    ) noexcept;

                public:
                    ~__BidirectionalDelegateWrapperIterator () noexcept override;

                public:
                    auto operator = (
                            __BidirectionalDelegateWrapperIterator const & iterator
                    ) noexcept -> __BidirectionalDelegateWrapperIterator &;

                public:
                    auto operator = (
                            __BidirectionalDelegateWrapperIterator && iterator
                    ) noexcept -> __BidirectionalDelegateWrapperIterator &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator == (
                            __BidirectionalDelegateWrapperIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator != (
                            __BidirectionalDelegateWrapperIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> __BidirectionalDelegateWrapperIterator &;

                public:
                    __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> __BidirectionalDelegateWrapperIterator &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator -> () const noexcept -> ElementType *;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__
