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
    ArithmeticException ( String const & message ) noexcept : Exception ( String("Arithmetic Exception : ") + message ) { }  // NOLINT(google-explicit-constructor)
};

class DivideByZeroException : public ArithmeticException {
public:
    DivideByZeroException () noexcept : ArithmeticException ("Divide By Zero Exception") { }
    DivideByZeroException ( DivideByZeroException const & ) noexcept = default;
    DivideByZeroException ( DivideByZeroException && ) noexcept = default;
    __CDS_MaybeUnused DivideByZeroException ( String const & message ) noexcept : ArithmeticException ( String("Divide By Zero Exception : ") + message ) { }  // NOLINT(google-explicit-constructor)
};

#endif //CDS_UTILITY_HPP
