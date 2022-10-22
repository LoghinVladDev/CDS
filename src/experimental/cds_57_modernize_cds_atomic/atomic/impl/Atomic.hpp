/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_ATOMIC_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ATOMIC_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline auto AtomicFlag :: clear () noexcept -> void {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        this->_atomicFlag.clear ();
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        this->_atomicFlag.store ( false );
#endif

    }


    inline auto AtomicFlag :: clear (
            AtomicMemoryOrder order
    ) noexcept -> void {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        this->_atomicFlag.clear ( static_cast < std :: memory_order > ( order ) );
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        this->_atomicFlag.store ( false, static_cast < std :: memory_order > ( order ) );
#endif

    }


    inline auto AtomicFlag :: set () noexcept -> bool {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        return this->_atomicFlag.test_and_set ();
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        return this->_atomicFlag.exchange ( true );
#endif

    }


    inline auto AtomicFlag :: set (
            AtomicMemoryOrder order
    ) noexcept -> bool {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        return this->_atomicFlag.test_and_set ( static_cast < std :: memory_order > ( order ) );
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        return this->_atomicFlag.exchange ( true, static_cast < std :: memory_order > ( order ) );
#endif

    }


    inline auto AtomicFlag :: get () const noexcept -> bool {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        return this->_atomicFlag.test ();
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        return this->_atomicFlag.load ();
#endif

    }


    inline auto AtomicFlag :: get (
            AtomicMemoryOrder order
    ) const noexcept -> bool {

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_flag_implementation
        return this->_atomicFlag.test ( static_cast < std :: memory_order > ( order ) );
#endif

#if __CDS_atomic_flag_implementation == __CDS_atomic_flag_stl_atomic_implementation
        return this->_atomicFlag.load ( static_cast < std :: memory_order > ( order ) );
#endif

    }


    inline AtomicFlag :: operator bool () const noexcept {

        return this->get();
    }


    inline auto AtomicFlag :: toString () const noexcept -> String {

        return this->get() ? "true" : "false";
    }


    inline auto AtomicFlag :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( & this->_atomicFlag );
    }


    inline auto AtomicFlag :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pAtomicFlag = dynamic_cast < decltype (this) > ( & object );
        if ( pAtomicFlag == nullptr ) {
            return false;
        }

        return pAtomicFlag->get() == this->get();
    }


    inline auto AtomicFlag :: toString (
            AtomicMemoryOrder order
    ) const noexcept -> String {

        return this->get ( order ) ? "true" : "false";
    }


    inline auto AtomicFlag :: equals (
            Object              const & object,
            AtomicMemoryOrder           order
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pAtomicFlag = dynamic_cast < decltype (this) > ( & object );
        if ( pAtomicFlag == nullptr ) {
            return false;
        }

        return pAtomicFlag->get ( order ) == this->get ( order );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction Atomic < __ElementType > :: Atomic (
            Atomic const & atomic
    ) noexcept {

        this->set ( atomic.get() );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction Atomic < __ElementType > :: Atomic (
            Atomic              const & atomic,
            AtomicMemoryOrder           order
    ) noexcept {

        this->set (
                atomic.get ( order ),
                order
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction Atomic < __ElementType > :: Atomic (
            Atomic              const & atomic,
            AtomicMemoryOrder           loadOrder,
            AtomicMemoryOrder           storeOrder
    ) noexcept {

        this->set (
                atomic.get ( loadOrder ),
                storeOrder
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction Atomic < __ElementType > :: Atomic (
            __ElementType value
    ) noexcept {

        this->set ( value );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction Atomic < __ElementType > :: Atomic (
            __ElementType               value,
            AtomicMemoryOrder           order
    ) noexcept {

        this->set ( value, order );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator = (
            Atomic const & atomic
    ) noexcept -> Atomic & {

        if ( this == & atomic ) {
            return * this;
        }

        this->set ( atomic.get() );
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator = (
            __ElementType value
    ) noexcept -> Atomic & {

        this->set ( value );
        return * this;
    }


    template < typename __ElementType >
    constexpr auto Atomic < __ElementType > :: get () const noexcept -> __ElementType {

        return this->_data.load();
    }


    template < typename __ElementType >
    constexpr auto Atomic < __ElementType > :: get (
            AtomicMemoryOrder order
    ) const noexcept -> __ElementType {

        return this->_data.load ( static_cast < std :: memory_order > ( order ) );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: set (
            __ElementType value
    ) noexcept -> void {

        this->_data.store ( value );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: set (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> void {

        this->_data.store ( value, static_cast < std :: memory_order > ( order ) );
    }


    template < typename __ElementType >
    constexpr Atomic < __ElementType > :: operator __ElementType () const noexcept {

        return this->get();
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: exchange (
            __ElementType value
    ) noexcept -> __ElementType {

        return this->_data.exchange ( value );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: exchange (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return this->_data.exchange ( value, static_cast < std :: memory_order > ( order ) );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeWeak (
            __ElementType & expected,
            __ElementType   desired
    ) noexcept -> bool {

        return this->_data.compare_exchange_weak ( expected, desired );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeWeak (
            __ElementType     & expected,
            __ElementType       desired,
            AtomicMemoryOrder   order
    ) noexcept -> bool {

        return this->_data.compare_exchange_weak (
                expected,
                desired,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeWeak (
            __ElementType     & expected,
            __ElementType       desired,
            AtomicMemoryOrder   success,
            AtomicMemoryOrder   failure
    ) noexcept -> bool {

        return this->_data.compare_exchange_weak (
                expected,
                desired,
                static_cast < std :: memory_order > ( success ),
                static_cast < std :: memory_order > ( failure )
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeStrong (
            __ElementType & expected,
            __ElementType   desired
    ) noexcept -> bool {

        return this->_data.compare_exchange_strong ( expected, desired );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeStrong (
            __ElementType     & expected,
            __ElementType       desired,
            AtomicMemoryOrder   order
    ) noexcept -> bool {

        return this->_data.compare_exchange_strong (
                expected,
                desired,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: compareExchangeStrong (
            __ElementType     & expected,
            __ElementType       desired,
            AtomicMemoryOrder   success,
            AtomicMemoryOrder   failure
    ) noexcept -> bool {

        return this->_data.compare_exchange_strong (
                expected,
                desired,
                static_cast < std :: memory_order > ( success ),
                static_cast < std :: memory_order > ( failure )
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenAdd (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_add ( & this->_data, value );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenAdd (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_add_explicit (
                & this->_data,
                value,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenSubtract (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_sub ( & this->_data, value );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenSubtract (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_sub_explicit (
                & this->_data,
                value,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseAnd (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_and ( & this->_data, value );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseAnd (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_and_explicit (
                & this->_data,
                value,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseOr (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_or ( & this->_data, value );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseOr (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_or_explicit (
                & this->_data,
                value,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseXor (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_xor ( & this->_data, value );
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: getThenBitwiseXor (
            __ElementType       value,
            AtomicMemoryOrder   order
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_xor_explicit (
                & this->_data,
                value,
                static_cast < std :: memory_order > ( order )
        );
    }


    template < typename __ElementType >
    template <
            meta :: EnableIf <
                    meta :: isIntegral < __ElementType > () ||
                    meta :: isBasicPointer < __ElementType > ()
            >
    > __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator ++ () noexcept -> __ElementType {

        return std :: atomic_fetch_add (
                & this->_data,
                1
        ) + 1;
    }


    template < typename __ElementType >
    template <
            meta :: EnableIf <
                    meta :: isIntegral < __ElementType > () ||
                    meta :: isBasicPointer < __ElementType > ()
            >
    > __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator ++ (int) noexcept -> __ElementType {

        return std :: atomic_fetch_add (
                & this->_data,
                1
        );
    }


    template < typename __ElementType >
    template <
            meta :: EnableIf <
                    meta :: isIntegral < __ElementType > () ||
                    meta :: isBasicPointer < __ElementType > ()
            >
    > __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator -- () noexcept -> __ElementType {

        return std :: atomic_fetch_sub (
                & this->_data,
                1
        ) + 1;
    }


    template < typename __ElementType >
    template <
            meta :: EnableIf <
                    meta :: isIntegral < __ElementType > () ||
                    meta :: isBasicPointer < __ElementType > ()
            >
    > __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator -- (int) noexcept -> __ElementType {

        return std :: atomic_fetch_sub (
                & this->_data,
                1
        );
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator += (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_add (
                & this->_data,
                value
        ) + value;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator -= (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_sub (
                & this->_data,
                value
        ) - value;
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator &= (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_and (
                & this->_data,
                value
        ) & value;
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator |= (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_or (
                & this->_data,
                value
        ) | value;
    }


    template < typename __ElementType >
    template < meta :: EnableIf < meta :: isIntegral < __ElementType > () > >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Atomic < __ElementType > :: operator ^= (
            __ElementType value
    ) noexcept -> __ElementType {

        return std :: atomic_fetch_xor (
                & this->_data,
                value
        ) ^ value;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto Atomic < __ElementType > :: hash () const noexcept -> Size {

        return this->get();
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto Atomic < __ElementType > :: hash (
            AtomicMemoryOrder order
    ) const noexcept -> Size {

        return this->get ( order );
    }


    template < typename __ElementType >
    inline auto Atomic < __ElementType > :: toString () const noexcept -> String {

        return this->get();
    }


    template < typename __ElementType >
    inline auto Atomic < __ElementType > :: toString (
            AtomicMemoryOrder order
    ) const noexcept -> String {

        return this->get ( order );
    }


    template < typename __ElementType >
    inline auto Atomic < __ElementType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pAtomic = dynamic_cast < decltype (this) > ( & object );
        if ( pAtomic == nullptr ) {
            return false;
        }

        return this->get() == pAtomic->get();
    }


    template < typename __ElementType >
    inline auto Atomic < __ElementType > :: equals (
            Object              const & object,
            AtomicMemoryOrder           order
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pAtomic = dynamic_cast < decltype (this) > ( & object );
        if ( pAtomic == nullptr ) {
            return false;
        }

        return this->get ( order ) == pAtomic->get ( order );
    }

} /* namespace cds */

#endif /* __CDS_ATOMIC_IMPL_HPP__ */
