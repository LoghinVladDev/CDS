//
// Created by loghin on 24/09/2021.
//

#ifndef CDS_EXCEPTION_HPP
#define CDS_EXCEPTION_HPP

#include <CDS/String>
#include <CDS/Memory>
#include <utility>

namespace cds {

    class Exception : public Object, public std :: exception {
    private:
        String _message;

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what () const noexcept -> StringLiteral override { return this->_message.cStr(); }

    public:
        inline Exception () noexcept :
                Object(),
                std :: exception(),
                _message("Runtime Exception") {

        }

        inline Exception ( Exception const & exception ) noexcept = default;
        inline Exception ( Exception && exception ) noexcept = default;

        __CDS_MaybeUnused inline Exception ( std :: exception const & exception ) noexcept : // NOLINT(google-explicit-constructor)
                Object (),
                std :: exception (exception ),
                _message(exception.what()) {

        }

        __CDS_MaybeUnused inline Exception ( std :: exception && exception ) noexcept : // NOLINT(google-explicit-constructor)
                Object (),
                std :: exception (exception ),
                _message (exception.what() ) {

        }

        inline ~Exception () override = default;

        __CDS_MaybeUnused inline explicit Exception ( String message ) noexcept :
                Object (),
                std :: exception (),
                _message ( std :: move ( message ) ) {

        }

        __CDS_MaybeUnused inline explicit Exception ( std :: string const & message ) noexcept :
                Object (),
                std :: exception (),
                _message ( message ) {

        }

        __CDS_MaybeUnused inline explicit Exception ( std :: string && message ) noexcept :
                Object (),
                std :: exception (),
                _message ( message ) {

        }

        inline explicit Exception ( StringLiteral message ) noexcept :
                Object (),
                std :: exception (),
                _message ( message ) {

        }

        __CDS_MaybeUnused inline explicit Exception ( CString message ) noexcept :
                Object (),
                std :: exception (),
                _message ( message ) {

        }

        __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override {
            return this->_message;
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash () const noexcept -> Index override {
            return this->_message.hash();
        }

        __CDS_NoDiscard auto copy () const noexcept -> Exception * override {
            return Memory::instance().create < Exception > ( * this );
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < decltype (this) > ( & object );

            if (pObject == nullptr ) {
                return false;
            }

            return this->_message == pObject->_message;
        }

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto message () const noexcept -> StringLiteral {
            return this->_message.cStr();
        }
    };

}

#endif //CDS_EXCEPTION_HPP
