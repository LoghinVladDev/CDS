//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <Object.hpp>
#include <PrimitiveGenerator.hpp>

class Integer : public Object {
    _G_OBJ(Integer, int, v, 0)

//private:
//    int v { 0 };
//
//public:
//    constexpr Integer () noexcept = default;
//    constexpr Integer ( Integer const & ) noexcept = default;
//    constexpr Integer ( Integer && ) noexcept = default;
//    constexpr ~Integer() noexcept = default;
//
//    constexpr Integer ( int value ) noexcept : v(value) { } // NOLINT(google-explicit-constructor)
//
//    constexpr Integer & operator = ( Integer const & o ) noexcept {
//        if ( this == & o ) return * this;
//
//        this->v = o.v;
//        return * this;
//    }
//
//    constexpr Integer & operator = ( int value ) noexcept { this->v = value; return * this; }
//
//#define _G_OP_OBJ_CONST(_opVal, _rDatType) \
//    constexpr auto operator _opVal ( Integer const & o ) const noexcept -> _rDatType { return this->v _opVal o.v; } \
//    constexpr auto operator _opVal ( int value ) const noexcept -> _rDatType { return this->v _opVal value; }
//
//#define _G_OP_OBJ(_opVal) \
//    constexpr auto operator _opVal ( Integer const & o ) noexcept -> Integer & { this->v _opVal o.v; return * this; } \
//    constexpr auto operator _opVal ( int value ) noexcept -> Integer & { this->v _opVal value; return * this; }
//
//    _G_OP_OBJ_CONST(+, Integer)
//    _G_OP_OBJ_CONST(-, Integer)
//    _G_OP_OBJ_CONST(*, Integer)
//    _G_OP_OBJ_CONST(/, Integer)
//    _G_OP_OBJ_CONST(%, Integer)
//
//    _G_OP_OBJ(+=)
//    _G_OP_OBJ(-=)
//    _G_OP_OBJ(*=)
//    _G_OP_OBJ(/=)
//    _G_OP_OBJ(%=)
//
//    _G_OP_OBJ_CONST(==, bool)
//    _G_OP_OBJ_CONST(!=, bool)
//    _G_OP_OBJ_CONST(>, bool)
//    _G_OP_OBJ_CONST(<, bool)
//    _G_OP_OBJ_CONST(>=, bool)
//    _G_OP_OBJ_CONST(<=, bool)
//
//    _G_OP_OBJ_CONST(&, Integer)
//    _G_OP_OBJ_CONST(|, Integer)
//    _G_OP_OBJ_CONST(^, Integer)
//
//    _G_OP_OBJ(&)
//    _G_OP_OBJ(|)
//    _G_OP_OBJ(^)
//
//    constexpr operator int () const noexcept { // NOLINT(google-explicit-constructor)
//        return this->v;
//    }
//
//    [[nodiscard]] constexpr inline auto get () const noexcept -> int { return this->v; }
public:
    [[nodiscard]] auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v);
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Integer {
        if ( string.empty() ) return 0;

        auto it = string.begin();
        constexpr static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        constexpr static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > ( c ) - 48; };

        while( ! isNumericChar ( it.value() ) && it != string.end() )
            it.next();

        int numericValue = 0;

        while ( isNumericChar ( it.value() ) && it != string.end() ) {
            numericValue = numericValue * 10 + numericCharToInt ( it.value() );
            it.next();
        }

        return numericValue;
    }
};


#endif //CDS_INTEGER_HPP
