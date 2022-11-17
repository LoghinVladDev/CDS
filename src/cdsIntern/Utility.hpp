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
#include <CDS/meta/TypeTraits>

namespace cds {

    class RuntimeException : public Exception {
    public:
        RuntimeException () noexcept : Exception ("Runtime Exception") { }
        RuntimeException ( RuntimeException const & ) noexcept = default;
        RuntimeException ( RuntimeException && ) noexcept = default;
        __CDS_MaybeUnused explicit RuntimeException ( StringView message ) noexcept : Exception ( message ) { }

        ~RuntimeException() noexcept override = default;
    };

    class ArithmeticException : public RuntimeException {
    public:
        ArithmeticException () noexcept : RuntimeException ("Arithmetic Exception") { }
        ArithmeticException ( ArithmeticException const & ) noexcept = default;
        ArithmeticException ( ArithmeticException && ) noexcept = default;
        explicit ArithmeticException ( StringView message ) noexcept : RuntimeException ( message ) { }

        ~ArithmeticException() noexcept override = default;
    };

    class DivideByZeroException : public ArithmeticException {
    public:
        DivideByZeroException () noexcept : ArithmeticException ("Divide By Zero Exception") { }
        DivideByZeroException ( DivideByZeroException const & ) noexcept = default;
        DivideByZeroException ( DivideByZeroException && ) noexcept = default;
        __CDS_MaybeUnused explicit DivideByZeroException ( StringView message ) noexcept : ArithmeticException ( message ) { }

        ~DivideByZeroException() noexcept override = default;
    };


    class IllegalArgumentException : public RuntimeException {
    public:
        IllegalArgumentException () noexcept : RuntimeException ("Illegal Argument") { }
        IllegalArgumentException ( IllegalArgumentException const & ) noexcept = default;
        IllegalArgumentException ( IllegalArgumentException && ) noexcept = default;
        __CDS_MaybeUnused explicit IllegalArgumentException ( StringView message ) noexcept : RuntimeException ( message ) { }

        ~IllegalArgumentException() noexcept override = default;
    };


    class UnsupportedOperationException : public Exception {
    public:
        UnsupportedOperationException () noexcept : Exception ("Unsupported Operation") { }
        UnsupportedOperationException ( UnsupportedOperationException const & ) noexcept = default;
        UnsupportedOperationException ( UnsupportedOperationException && ) noexcept = default;
        __CDS_MaybeUnused explicit UnsupportedOperationException ( StringView message ) noexcept : Exception ( message ) { }

        ~UnsupportedOperationException() noexcept override = default;
    };


    class NullPointerException : public RuntimeException {
    public:
        NullPointerException () noexcept : RuntimeException ("Tried De-Referencing a null valued Pointer") { }
        NullPointerException ( NullPointerException const & ) noexcept = default;
        NullPointerException ( NullPointerException && ) noexcept = default;
        __CDS_OptimalInline explicit NullPointerException ( StringView message ) noexcept : RuntimeException ( message ) {}

        ~NullPointerException() noexcept override = default;
    };


    class OutOfBoundsException : public RuntimeException {
    public:
        OutOfBoundsException () noexcept : RuntimeException ("Out of Bounds Access for Object") { }
        OutOfBoundsException ( OutOfBoundsException const & ) noexcept = default;
        OutOfBoundsException ( OutOfBoundsException && ) noexcept = default;
        __CDS_MaybeUnused explicit OutOfBoundsException ( StringView message ) noexcept : RuntimeException ( message ) { }
        __CDS_MaybeUnused explicit OutOfBoundsException ( Index requested, Index capacity ) noexcept : RuntimeException ( String::format("Out of Bounds Exception : Requested : %lld, Capacity : %lld", requested, capacity) ) { }

        ~OutOfBoundsException() noexcept override = default;
    };


    class TypeException : public RuntimeException {
    public:
        TypeException () noexcept : RuntimeException ( "Type Cast Exception" ) { }

        template < typename T, typename V >
        TypeException () noexcept : Exception ( String::f("Type Cast Exception. Cannot convert '%s' to '%s'", meta :: Type < T > :: name(), meta :: Type < V > :: name()) ) { }
        template < typename T >
        explicit TypeException ( T const & unused __CDS_MaybeUnused ) noexcept : RuntimeException ( String::f("Type Cast Exception. Conversion to '%s' not possible", meta :: Type < T > :: name()) ) { }
        explicit TypeException ( StringView message ) noexcept : RuntimeException ( message ) { }

        ~TypeException() noexcept override = default;
    };

    class KeyException : public RuntimeException {
    public:
        KeyException () noexcept : RuntimeException ( "Key Exception" ) { }

        template < typename K >
        __CDS_MaybeUnused explicit KeyException ( K const & key ) noexcept : RuntimeException ( String :: f ( "Key Exception : Key '%s' is invalid for Object", String(key).cStr() ) ) { }

        ~KeyException() noexcept override = default;
    };

    class NotImplementedException : public Exception {
    public:
        NotImplementedException () noexcept : Exception ( "Not Implemented" ) { }
        explicit NotImplementedException ( StringView message ) noexcept : Exception ( message ) { }

        ~NotImplementedException() noexcept override = default;
    };

    class FormatException : public IllegalArgumentException {
    public:
        FormatException () noexcept : IllegalArgumentException ( "Argument Format Error" ) { }
        explicit FormatException ( StringView message ) noexcept : IllegalArgumentException ( message ) { }

        ~FormatException() noexcept override = default;
    };

    template < typename T, typename SmartPointerType >
    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto copy ( T const & object ) noexcept -> SmartPointerType {
        return SmartPointerType ( copy ( object ) );
    }

    template < typename T > 
    __CDS_NoDiscard __CDS_MaybeUnused constexpr auto compare ( T const & left, T const & right ) noexcept -> bool {
        return meta :: equals ( left, right );
    } 

    template < typename T > 
    __CDS_MaybeUnused constexpr auto streamPrint ( std :: ostream & out, T const & object ) noexcept -> std :: ostream & {
        return meta :: print ( out, object );
    }

    template < typename T, typename = meta :: EnableIf < meta :: isCopyConstructible < T > () > >
    __CDS_NoDiscard __CDS_OptimalInline auto copy ( T const & obj ) noexcept -> T * {
        return Memory :: instance().create < T > ( obj );
    }

    template < typename T, meta :: EnableIf < meta :: isPrintable < T > () > = 0 >
    __CDS_OptimalInline auto println ( T const & obj ) noexcept -> std :: ostream & {
        return std :: cout << obj << '\n';
    }

}

#include "../shared/impl/arithmetic.hpp"
#include "../shared/impl/generalPredicates.hpp"

__CDS_Meta_RegisterParseType(ArithmeticException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(DivideByZeroException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(IllegalArgumentException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(NullPointerException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(OutOfBoundsException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(TypeException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(KeyException) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_Meta_RegisterParseType(NotImplementedException) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_UTILITY_HPP
