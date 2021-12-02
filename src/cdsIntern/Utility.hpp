//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_UTILITY_HPP
#define CDS_UTILITY_HPP

#include <type_traits>
#include "../prepro.h"
#include <CDS/Conversion>
#include <CDS/Exception>
#include <CDS/Limits>

namespace cds {

    class ArithmeticException : public Exception {
    public:
        ArithmeticException () noexcept : Exception ("Arithmetic Exception") { }
        ArithmeticException ( ArithmeticException const & ) noexcept = default;
        ArithmeticException ( ArithmeticException && ) noexcept = default;
        explicit ArithmeticException ( String const & message ) noexcept : Exception ( String("Arithmetic Exception : ") + message ) { }

        ~ArithmeticException() noexcept override = default;
    };

    class DivideByZeroException : public ArithmeticException {
    public:
        DivideByZeroException () noexcept : ArithmeticException ("Divide By Zero Exception") { }
        DivideByZeroException ( DivideByZeroException const & ) noexcept = default;
        DivideByZeroException ( DivideByZeroException && ) noexcept = default;
        __CDS_MaybeUnused explicit DivideByZeroException ( String const & message ) noexcept : ArithmeticException ( String("Divide By Zero Exception : ") + message ) { }

        ~DivideByZeroException() noexcept override = default;
    };


    class IllegalArgumentException : public Exception {
    public:
        IllegalArgumentException () noexcept : Exception ("Illegal Argument") { }
        IllegalArgumentException ( IllegalArgumentException const & ) noexcept = default;
        IllegalArgumentException ( IllegalArgumentException && ) noexcept = default;
        __CDS_MaybeUnused explicit IllegalArgumentException ( String const & message ) noexcept : Exception ( String("Illegal Argument Exception : ") + message ) { }

        ~IllegalArgumentException() noexcept override = default;
    };


    class NullPointerException : public Exception {
    public:
        NullPointerException () noexcept : Exception ("Tried De-Referencing a null valued Pointer") { }
        NullPointerException ( NullPointerException const & ) noexcept = default;
        NullPointerException ( NullPointerException && ) noexcept = default;
        __CDS_OptimalInline explicit NullPointerException ( String const & message ) noexcept : Exception ( "Tried De-Referencing a null valued Pointer : "_s + message ) {}
        __CDS_OptimalInline explicit NullPointerException ( StringLiteral message ) noexcept : NullPointerException ( String(message) ) {}

        ~NullPointerException() noexcept override = default;
    };


    class OutOfBoundsException : public Exception {
    public:
        OutOfBoundsException () noexcept : Exception ("Out of Bounds Access for Object") { }
        OutOfBoundsException ( OutOfBoundsException const & ) noexcept = default;
        OutOfBoundsException ( OutOfBoundsException && ) noexcept = default;
        __CDS_MaybeUnused explicit OutOfBoundsException ( String const & message ) noexcept : Exception ( String("Out of Bounds Exception : ") + message ) { }
        __CDS_MaybeUnused explicit OutOfBoundsException ( Index requested, Index capacity ) noexcept : Exception ( String::format("Out of Bounds Exception : Requested : %lld, Capacity : %lld", requested, capacity) ) { }

        ~OutOfBoundsException() noexcept override = default;
    };


    class TypeException : public Exception {
    public:
        TypeException () noexcept : Exception ( "Type Cast Exception" ) { }

        template < typename T, typename V >
        TypeException () noexcept : Exception ( String::f("Type Cast Exception. Cannot convert '%s' to '%s'", Type < T > :: name(), Type < V > :: name()) ) { }
        template < typename T >
        explicit TypeException ( T const & _ __CDS_MaybeUnused ) noexcept : Exception ( String::f("Type Cast Exception. Conversion to '%s' not possible", Type < T > :: name()) ) { }
        explicit TypeException (String const & message) noexcept : Exception ("Type Cast Exception : "_s + message) { }

        ~TypeException() noexcept override = default;
    };

    class KeyException : public Exception {
    public:
        KeyException () noexcept : Exception ( "Key Exception" ) { }

        template < typename K >
        __CDS_MaybeUnused explicit KeyException ( K const & key ) noexcept : Exception ( String :: f ( "Key Exception : Key '%s' is invalid for Object", String(key).cStr() ) ) { }

        ~KeyException() noexcept override = default;
    };

    class NotImplementedException : public Exception {
    public:
        NotImplementedException () noexcept : Exception ( "Not Implemented" ) { }
        explicit NotImplementedException ( String const & message ) noexcept : Exception ( "Not Implemented : "_s + message ) { }

        ~NotImplementedException() noexcept override = default;
    };

}

__CDS_RegisterParseType(ArithmeticException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(DivideByZeroException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(IllegalArgumentException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(NullPointerException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(OutOfBoundsException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(TypeException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(KeyException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(NotImplementedException) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_UTILITY_HPP
