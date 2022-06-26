//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                class __AbstractDelegateWrapperIterator {   // NOLINT(bugprone-reserved-identifier)

                private:
                    Object                                          const * _pOwner     { nullptr };

                private:
                    __AbstractDelegateIterator < __ElementType >          * _pDelegate  { nullptr };

                protected:
                    constexpr __AbstractDelegateWrapperIterator() noexcept;

                protected:
                    constexpr __AbstractDelegateWrapperIterator(
                            Object                                          const * pOwner,
                            __AbstractDelegateIterator < __ElementType >          * pDelegate
                    ) noexcept;

                protected:
                    __AbstractDelegateWrapperIterator (
                            __AbstractDelegateWrapperIterator const & iterator
                    ) noexcept;

                protected:
                    constexpr __AbstractDelegateWrapperIterator (
                            __AbstractDelegateWrapperIterator && iterator
                    ) noexcept;

                public:
                    virtual ~__AbstractDelegateWrapperIterator() noexcept;

                public:
                    __CDS_NoDiscard constexpr auto of (
                            Object const * pObject
                    ) const noexcept -> bool;

                protected:
                    __CDS_cpplang_ConstexprPureAbstract auto advance (
                            __IteratorAdvanceDirection direction
                    ) noexcept -> __AbstractDelegateWrapperIterator &;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto equals (
                            __AbstractDelegateWrapperIterator const & iterator
                    ) const noexcept -> bool;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool;

                protected:
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType &;

                protected:
                    auto copy (
                            __AbstractDelegateWrapperIterator const & iterator
                    ) noexcept -> __AbstractDelegateWrapperIterator &;

                protected:
                    auto move (
                            __AbstractDelegateWrapperIterator && iterator
                    ) noexcept -> __AbstractDelegateWrapperIterator &;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__
