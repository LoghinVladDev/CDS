//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_BOOLEAN_HPP
#define CDS_BOOLEAN_HPP

#include <CDS/Object>
#include "./PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __boolean_constexpr constexpr
#else
#define __boolean_constexpr
#endif

class Boolean : public Object {
private:
    bool v { false };
public:
    constexpr Boolean () noexcept = default;
    constexpr Boolean ( Boolean const & ) noexcept = default;
    constexpr Boolean ( Boolean && ) noexcept = default;
    __boolean_constexpr ~Boolean() noexcept override = default;

    constexpr Boolean ( bool v ) noexcept : v(v) { }

    constexpr Boolean & operator = ( Boolean const & o ) noexcept {
        if ( this == & o ) return * this;
        this->v = o.v;
        return * this;
    }

    constexpr Boolean & operator = ( bool value ) noexcept {
        this->v = value;
        return * this;
    }

    __boolean_constexpr auto operator &&(Boolean const & o) const noexcept -> Boolean {
        return this->v && o.v;
    }

    __boolean_constexpr auto operator && ( bool value ) const noexcept -> Boolean {
        return this->v && value;
    }

    __boolean_constexpr auto operator ||(Boolean const & o) const noexcept -> Boolean {
        return this->v || o.v;
    }

    __boolean_constexpr auto operator || ( bool value ) const noexcept -> Boolean {
        return this->v || value;
    }

//    constexpr auto operator &&(Boolean const &o) const noexcept -> Boolean { return this->v && o.v; }
//    constexpr auto operator &&(bool value) const noexcept -> Boolean { return this->v && value; }

//    _G_OP_OBJ_CONST(Boolean, ==, bool, v, bool)
//    _G_OP_OBJ_CONST(Boolean, !=, bool, v, bool)

    __boolean_constexpr auto operator ! () const noexcept -> Boolean {
        return !this->v;
    }

    constexpr operator bool () const noexcept {
        return this->v;
    }

    [[nodiscard]] constexpr inline auto get () const noexcept -> bool {
        return this->v;
    }

    [[nodiscard]] auto hash () const noexcept -> Index override {
        return static_cast < Index > (this->v);
    }

    [[nodiscard]] auto toString () const noexcept -> String override {
        return String().append(this->v ? "true" : "false");
    }

    inline static auto parse(String const & string) noexcept -> Boolean {
        if ( string.empty() ) return false;

        return string == "true";
    }

    [[nodiscard]] auto copy () const noexcept -> Boolean * override {
        return new Boolean( * this );
    }
};

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST

#endif //CDS_BOOLEAN_HPP
