/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_ATOMIC_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ATOMIC_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    inline auto AtomicFlag :: clear () noexcept -> void {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        this->_atomicFlag.clear ();
#else
        this->_atomicFlag.store ( false );
#endif

    }


    inline auto AtomicFlag :: clear (
            AtomicMemoryOrder order
    ) noexcept -> void {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        this->_atomicFlag.clear ( static_cast < std :: memory_order > ( order ) );
#else
        this->_atomicFlag.store ( false, static_cast < std :: memory_order > ( order ) );
#endif

    }


    inline auto AtomicFlag :: set () noexcept -> bool {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        return this->_atomicFlag.test_and_set ();
#else
        return this->_atomicFlag.exchange ( true );
#endif

    }


    inline auto AtomicFlag :: set (
            AtomicMemoryOrder order
    ) noexcept -> bool {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        return this->_atomicFlag.test_and_set ( static_cast < std :: memory_order > ( order ) );
#else
        return this->_atomicFlag.exchange ( true, static_cast < std :: memory_order > ( order ) );
#endif

    }


    inline auto AtomicFlag :: get () const noexcept -> bool {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        return this->_atomicFlag.test ();
#else
        return this->_atomicFlag.load ( true );
#endif

    }


    inline auto AtomicFlag :: get (
            AtomicMemoryOrder order
    ) const noexcept -> bool {

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_20
        return this->_atomicFlag.test ( static_cast < std :: memory_order > ( order ) );
#else
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

} /* namespace cds */

#endif /* __CDS_ATOMIC_IMPL_HPP__ */
