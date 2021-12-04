//
// Created by loghin on 30.03.2021.
//

#ifndef CDS_ATOMIC_HPP
#define CDS_ATOMIC_HPP

#include <CDS/Object>
#include <CDS/Mutex>

#include <sstream>

namespace cds {

    template < typename T >
    class Atomic : public Object {
    protected:
        using DataType = T;

        Mutex    mutable _access; // NOLINT(clion-misra-cpp2008-11-0-1)
        DataType         _data; // NOLINT(clion-misra-cpp2008-11-0-1)
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

        Atomic (DataType const & value) noexcept { // NOLINT(google-explicit-constructor)
            this->set(value);
        }

        __CDS_OptimalInline auto get () const noexcept -> T {
            this->_access.lock();
            auto value = this->_data;
            this->_access.unlock();

            return value;
        }

        __CDS_OptimalInline auto set ( DataType const & value ) noexcept -> void {
            this->_access.lock();
            this->_data = value;
            this->_access.unlock();
        }

        __CDS_OptimalInline Atomic & operator = ( Atomic const & obj ) noexcept {
            if ( this == & obj ) {
                return * this;
            }

            this->set( obj.get() );

            return * this;
        }

        Atomic & operator = ( Atomic && obj ) noexcept {
            if ( this == & obj ) {
                return * this;
            }

            if ( obj._access.tryLock() ) {
                this->set(obj._data);
                obj._access.unlock();
            } else {
                this->_data = obj._data;
                this->_access.lock();
            }

            return * this;
        }

        __CDS_OptimalInline virtual Atomic & operator = ( DataType const & value ) noexcept {
            this->set(value );

            return * this;
        }

        __CDS_OptimalInline Atomic & operator = ( DataType && value ) noexcept {
            this->set ( std::move (value ) );

            return * this;
        }

        __CDS_OptimalInline auto operator == ( Atomic const & value ) const noexcept -> bool {
            return this->get() == value.get();
        }

        __CDS_OptimalInline auto operator == ( DataType const & value ) const noexcept -> bool {
            return this->get() == value;
        }

        __CDS_OptimalInline auto operator != ( Atomic const & value ) const noexcept -> bool {
            return this->get() != value.get();
        }

        __CDS_OptimalInline auto operator != ( DataType const & value ) const noexcept -> bool {
            return this->get() != value;
        }

        __CDS_OptimalInline operator DataType () const noexcept { // NOLINT(google-explicit-constructor)
            return this->get();
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            std::stringstream stringStream;

            stringStream
                << "Atomic{"
                << "data=" << this->_data
                << ", accessLock" << this->_access.toString().cStr()
                << "}";

            return stringStream.str();
        }

        __CDS_NoDiscard auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pAtomic = dynamic_cast < Atomic < T > const * > ( & object );
            if (pAtomic == nullptr ) {
                return false;
            }

            return pAtomic->get() == this->get();
        }
    };

}

__CDS_RegisterParseTypeTemplateT(Atomic) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_ATOMIC_HPP
