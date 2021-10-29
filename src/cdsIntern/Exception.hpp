//
// Created by loghin on 24/09/2021.
//

#ifndef CDS_EXCEPTION_HPP
#define CDS_EXCEPTION_HPP

#include <CDS/String>
#include <utility>

class Exception : public Object, public std :: exception {
private:
    String _message;

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what () const noexcept -> StringLiteral override { return this->_message.cStr(); }

public:
    inline Exception () noexcept :
            Object(),
            std::exception(),
            _message("Runtime Exception") {

    }

    inline Exception ( Exception const & e ) noexcept = default;
    inline Exception ( Exception && e ) noexcept = default;

    __CDS_MaybeUnused inline Exception ( std :: exception const & e ) noexcept : // NOLINT(google-explicit-constructor)
            Object (),
            std :: exception ( e ),
            _message(e.what()) {

    }

    __CDS_MaybeUnused inline Exception ( std :: exception && e ) noexcept : // NOLINT(google-explicit-constructor)
            Object (),
            std :: exception ( e ),
            _message ( e.what() ) {

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

    __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto toString () const noexcept -> String override {
        return this->_message;
    }

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash () const noexcept -> Index override {
        return this->_message.hash();
    }

    __CDS_NoDiscard auto copy () const noexcept -> Exception * override {
        return new Exception ( * this );
    }

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->_message == p->_message;
    }

    __CDS_NoDiscard __CDS_MaybeUnused constexpr auto message () const noexcept -> StringLiteral {
        return this->_message.cStr();
    }
};

#endif //CDS_EXCEPTION_HPP
