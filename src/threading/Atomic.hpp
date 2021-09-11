//
// Created by loghin on 30.03.2021.
//

#ifndef CDS_ATOMIC_HPP
#define CDS_ATOMIC_HPP

#include <CDS/Object>
#include <CDS/Mutex>

#include <sstream>

template < typename T >
class Atomic : public Object {
protected:
    using DataType = T;

    Mutex    mutable _access;
    DataType         _data;
public:

    Atomic () noexcept = default;

    Atomic (Atomic const & obj) noexcept { this->set(obj.get()); }

    Atomic (Atomic && obj) noexcept {
        if ( obj._access.tryLock() ) {
            this->set(obj._data);
            obj._access.unlock();
        } else {
            this->_data = obj._data;
            this->_access.lock();
        }
    }

    Atomic (DataType const & v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    inline auto get () const noexcept -> T {
        this->_access.lock();
        auto v = this->_data;
        this->_access.unlock();

        return v;
    }

    inline auto set ( DataType const & v ) noexcept -> void {
        this->_access.lock();
        this->_data = v;
        this->_access.unlock();
    }

    inline Atomic & operator = ( Atomic const & obj ) noexcept {
        if ( this == & obj ) return * this;

        this->set( obj.get() );

        return * this;
    }

    Atomic & operator = ( Atomic && obj ) noexcept {
        if ( this == & obj ) return * this;

        if ( obj._access.tryLock() ) {
            this->set(obj._data);
            obj._access.unlock();
        } else {
            this->_data = obj._data;
            this->_access.lock();
        }

        return * this;
    }

    inline virtual Atomic & operator = ( DataType const & v ) noexcept {
        this->set( v );

        return * this;
    }

    inline Atomic & operator = ( DataType && v ) noexcept {
        this->set ( std::move ( v ) );

        return * this;
    }

    inline auto operator == ( Atomic const & v ) const noexcept -> bool {
        return this->get() == v.get();
    }

    inline auto operator == ( DataType const & v ) const noexcept -> bool {
        return this->get() == v;
    }

    inline auto operator != ( Atomic const & v ) const noexcept -> bool {
        return this->get() != v.get();
    }

    inline auto operator != ( DataType const & v ) const noexcept -> bool {
        return this->get() != v;
    }

    inline operator DataType () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get();
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override {
        std::stringstream ss;

        ss
            << "Atomic{"
            << "data=" << this->_data
            << ", accessLock" << this->_access.toString().cStr()
            << "}";

        return ss.str();
    }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & o );
        if ( p == nullptr ) return false;

        return p->get() == this->get();
    }
};

#endif //CDS_ATOMIC_HPP
