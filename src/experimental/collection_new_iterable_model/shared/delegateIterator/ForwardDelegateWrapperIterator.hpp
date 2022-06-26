//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                                                                     // NOLINT(bugprone-reserved-identifier)
                class __ForwardDelegateWrapperIterator : public __AbstractDelegateWrapperIterator < __ElementType >, public meta :: ForwardIterator {   // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType;

                public:
                    constexpr __ForwardDelegateWrapperIterator () noexcept;

                public:
                    constexpr __ForwardDelegateWrapperIterator (
                            Object                                          const * pOwner,
                            __AbstractDelegateIterator < __ElementType >          * pDelegate
                    ) noexcept;

                public:
                    __ForwardDelegateWrapperIterator (
                            __ForwardDelegateWrapperIterator const & iterator
                    ) noexcept;

                public:
                    constexpr __ForwardDelegateWrapperIterator (
                            __ForwardDelegateWrapperIterator && iterator
                    ) noexcept;

                public:
                    ~__ForwardDelegateWrapperIterator () noexcept override;

                public:
                    auto operator = (
                            __ForwardDelegateWrapperIterator const & iterator
                    ) noexcept -> __ForwardDelegateWrapperIterator &;

                public:
                    auto operator = (
                            __ForwardDelegateWrapperIterator && iterator
                    ) noexcept -> __ForwardDelegateWrapperIterator &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator == (
                            __ForwardDelegateWrapperIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator != (
                            __ForwardDelegateWrapperIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> __ForwardDelegateWrapperIterator &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;

                public:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator -> () const noexcept -> ElementType *;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__
