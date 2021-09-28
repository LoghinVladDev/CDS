//
// Created by loghin on 22/09/2021.
//

#ifndef CDS_UTILITY_HPP
#define CDS_UTILITY_HPP

#include <type_traits>
#include <prepro.h>
#include <CDS/Conversion>
#include <CDS/Exception>
#include <CDS/Limits>

class ArithmeticException : public Exception {
public:
    ArithmeticException () noexcept : Exception ("Arithmetic Exception") { }
    ArithmeticException ( ArithmeticException const & ) noexcept = default;
    ArithmeticException ( ArithmeticException && ) noexcept = default;
    explicit ArithmeticException ( String const & message ) noexcept : Exception ( String("Arithmetic Exception : ") + message ) { }
};

class DivideByZeroException : public ArithmeticException {
public:
    DivideByZeroException () noexcept : ArithmeticException ("Divide By Zero Exception") { }
    DivideByZeroException ( DivideByZeroException const & ) noexcept = default;
    DivideByZeroException ( DivideByZeroException && ) noexcept = default;
    __CDS_MaybeUnused explicit DivideByZeroException ( String const & message ) noexcept : ArithmeticException ( String("Divide By Zero Exception : ") + message ) { }
};

class IllegalArgumentException : public Exception {
public:
    IllegalArgumentException () noexcept : Exception ("Illegal Argument") { }
    IllegalArgumentException ( IllegalArgumentException const & ) noexcept = default;
    IllegalArgumentException ( IllegalArgumentException && ) noexcept = default;
    __CDS_MaybeUnused explicit IllegalArgumentException ( String const & message ) noexcept : Exception ( String("Illegal Argument Exception : ") + message ) { }
};

class NullPointerException : public Exception {
public:
    NullPointerException () noexcept : Exception ("Tried De-Referencing a null valued Pointer") { }
    NullPointerException ( NullPointerException const & ) noexcept = default;
    NullPointerException ( NullPointerException && ) noexcept = default;
};

class OutOfBoundsException : public Exception {
public:
    OutOfBoundsException () noexcept : Exception ("Out of Bounds Access for Object") { }
    OutOfBoundsException ( OutOfBoundsException const & ) noexcept = default;
    OutOfBoundsException ( OutOfBoundsException && ) noexcept = default;
    __CDS_MaybeUnused explicit OutOfBoundsException ( String const & message ) noexcept : Exception ( String("Out of Bounds Exception : ") + message ) { }
    __CDS_MaybeUnused explicit OutOfBoundsException ( Index requested, Index capacity ) noexcept : Exception ( String::format("Out of Bounds Exception : Requested : %lld, Capacity : %lld", requested, capacity) ) { }
};

#endif //CDS_UTILITY_HPP
