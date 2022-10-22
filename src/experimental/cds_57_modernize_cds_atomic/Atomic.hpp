/*
 * Created by loghin on 30.03.2021.
 */

#ifndef __CDS_ATOMIC_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ATOMIC_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>
#include <CDS/meta/TypeTraits>
#include <atomic>

namespace cds {

    enum class AtomicMemoryOrder {
        relaxed                 = static_cast < int > ( std :: memory_order :: relaxed ),
        consume                 = static_cast < int > ( std :: memory_order :: consume ),
        acquire                 = static_cast < int > ( std :: memory_order :: acquire ),
        release                 = static_cast < int > ( std :: memory_order :: release ),
        acquireRelease          = static_cast < int > ( std :: memory_order :: acq_rel ),
        sequentiallyConsistent  = static_cast < int > ( std :: memory_order :: seq_cst )
    };

    class AtomicFlag : public Object {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20

    private:
        using BaseType = std :: atomic_flag;

#else

        private:
        using BaseType = std :: atomic < bool >;

#endif

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        BaseType _atomicFlag;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicFlag () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AtomicFlag (
                AtomicFlag const &
        ) = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AtomicFlag (
                AtomicFlag &&
        ) = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AtomicFlag() noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AtomicFlag const &
        ) = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AtomicFlag &&
        ) = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto clear () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto clear (
                AtomicMemoryOrder order
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set () noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                AtomicMemoryOrder order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get () const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get (
                AtomicMemoryOrder order
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr operator bool () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString (
                AtomicMemoryOrder order
        ) const noexcept -> String;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash (
                AtomicMemoryOrder order
        ) const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object              const & object,
                AtomicMemoryOrder           order
        ) const noexcept -> bool;
    };


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Atomic : public Object {

        static_assert (
                cds :: meta :: isTriviallyCopyable < __ElementType > () &&
                cds :: meta :: isCopyConstructible < __ElementType > () &&
                cds :: meta :: isCopyAssignable < __ElementType > () &&
                cds :: meta :: isMoveConstructible < __ElementType > () &&
                cds :: meta :: isMoveAssignable < __ElementType > (),

                "Incompatible atomic type"
        );

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        std :: atomic < __ElementType > _data;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Atomic () noexcept ( noexcept ( __ElementType () ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic (
                Atomic const & atomic
        ) noexcept ( noexcept ( __ElementType ( cds :: meta :: referenceOf < __ElementType const > () ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic (
                Atomic && atomic
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic (
                Atomic              const & atomic,
                AtomicMemoryOrder           order
        ) noexcept ( noexcept ( __ElementType ( cds :: meta :: referenceOf < __ElementType const > () ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic (
                Atomic              const & atomic,
                AtomicMemoryOrder           loadOrder,
                AtomicMemoryOrder           storeOrder
        ) noexcept ( noexcept ( __ElementType ( cds :: meta :: referenceOf < __ElementType const > () ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Atomic (
                Atomic              && atomic,
                AtomicMemoryOrder      exchangeOrder
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Atomic() noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Atomic const & atomic
        ) noexcept -> Atomic &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Atomic && atomic
        ) noexcept -> Atomic &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get () const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get (
                AtomicMemoryOrder order
        ) const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_Implicit constexpr operator __ElementType () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator += (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator &= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator |= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ^= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash (
                AtomicMemoryOrder order
        ) const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString (
                AtomicMemoryOrder order
        ) const noexcept -> String;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object              const & object,
                AtomicMemoryOrder           order
        ) const noexcept -> bool;
    };


#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class AtomicReference : public Object {

        static_assert (
                cds :: meta :: isTriviallyCopyable < __ElementType > () &&
                cds :: meta :: isCopyConstructible < __ElementType > () &&
                cds :: meta :: isCopyAssignable < __ElementType > () &&
                cds :: meta :: isMoveConstructible < __ElementType > () &&
                cds :: meta :: isMoveAssignable < __ElementType > (),

                "Incompatible atomic type"
        );

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        std :: atomic_ref < __ElementType > _data;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicReference () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicReference (
                __ElementType & value
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicReference (
                AtomicReference const & atomic
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicReference (
                AtomicReference && atomic
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AtomicReference() noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType & value
        ) noexcept -> AtomicReference &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr auto operator = (
                AtomicReference const & atomic
        ) noexcept -> AtomicReference & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr auto operator = (
                AtomicReference && atomic
        ) noexcept -> AtomicReference & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get () const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get (
                AtomicMemoryOrder order
        ) const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_Implicit constexpr operator __ElementType () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator += (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator &= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator |= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ^= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash (
                AtomicMemoryOrder order
        ) const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString (
                AtomicMemoryOrder order
        ) const noexcept -> String;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object              const & object,
                AtomicMemoryOrder           order
        ) const noexcept -> bool;
    };

#endif

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class AtomicWeakReference : public Object {

        static_assert (
                cds :: meta :: isTriviallyCopyable < __ElementType > () &&
                cds :: meta :: isCopyConstructible < __ElementType > () &&
                cds :: meta :: isCopyAssignable < __ElementType > () &&
                cds :: meta :: isMoveConstructible < __ElementType > () &&
                cds :: meta :: isMoveAssignable < __ElementType > (),

                "Incompatible atomic type"
        );

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        std :: atomic < __ElementType * > _data;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicWeakReference () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicWeakReference (
                __ElementType & value
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicWeakReference (
                AtomicWeakReference const & atomic
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AtomicWeakReference (
                AtomicWeakReference && atomic
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AtomicWeakReference() noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType & value
        ) noexcept -> AtomicWeakReference &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr auto operator = (
                AtomicWeakReference const & atomic
        ) noexcept -> AtomicWeakReference & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr auto operator = (
                AtomicWeakReference && atomic
        ) noexcept -> AtomicWeakReference & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get () const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get (
                AtomicMemoryOrder order
        ) const noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto set (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_Implicit constexpr operator __ElementType () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto exchange (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeWeak (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType & expected,
                __ElementType   desired
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   order
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto compareExchangeStrong (
                __ElementType     & expected,
                __ElementType       desired,
                AtomicMemoryOrder   success,
                AtomicMemoryOrder   failure
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenAdd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenSubtract (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseAnd (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseOr (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getThenBitwiseXor (
                __ElementType       value,
                AtomicMemoryOrder   order
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                meta :: EnableIf <
                        meta :: isIntegral < __ElementType > () ||
                        meta :: isBasicPointer < __ElementType > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator += (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator &= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator |= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ^= (
                __ElementType       value
        ) noexcept -> __ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash (
                AtomicMemoryOrder order
        ) const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString (
                AtomicMemoryOrder order
        ) const noexcept -> String;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object              const & object,
                AtomicMemoryOrder           order
        ) const noexcept -> bool;
    };

} /* namespace cds */

#endif /* __CDS_ATOMIC_HPP__ */
