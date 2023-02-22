/* NOLINT(llvm-header-guard)
 * Created by loghin on 2/22/2023.
 */

#ifndef __CDS_QUEUE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_QUEUE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class __CDS_InheritsEBOs Queue : public MutableCollection < __ElementType > {

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType           = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MutableCollectionBase = MutableCollection < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase  :: __GenericHandler;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase  :: __GenericConstHandler; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Queue () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Queue (
                Queue const & queue
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Queue (
                Queue && queue
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Queue () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Queue const & /* queue */
        ) noexcept -> Queue & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Queue && /* queue */
        ) noexcept -> Queue & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto remove () noexcept -> void = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto peek () noexcept (false) -> __ElementType & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto peek () const noexcept (false) -> __ElementType const & = 0;
    };

} /* namespace cds */

#include "queue/impl/Queue.hpp"

#endif /* __CDS_QUEUE_HPP__ */
