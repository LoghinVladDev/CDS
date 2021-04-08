//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_BOOLEAN_HPP
#define CDS_BOOLEAN_HPP

#include <CDS/Object>
#include "../cdsIntern/PrimitiveGenerator.hpp"

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

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseBoolean = Atomic<Boolean>;
}

class Boolean::Atomic : public hidden::_AtomicBaseBoolean {
public:
    Atomic () noexcept {
        this->set(false);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseBoolean(obj) { }
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseBoolean(obj) { }
    Atomic ( Boolean const & v ) noexcept : hidden::_AtomicBaseBoolean(v) { }

    Atomic (bool v) noexcept {
        this->set(v);
    }

    Atomic & operator = (bool value) noexcept {
        this->set(Boolean(value));
        return * this;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
    Atomic & operator = (Boolean const & obj) noexcept {
        this->set(obj);
        return * this;
    }
#pragma clang diagnostic pop

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator bool () const noexcept {
        return this->get().get();
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String().append(this->get());
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)                               \
auto operator _operator (bool value) noexcept -> Atomic & {  \
    this->_access.lock();                                   \
    this->_data _operator value;                            \
    this->_access.unlock();                                 \
    return * this;                                          \
}

#undef _PREFIX_OP
};

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST
#endif //CDS_BOOLEAN_HPP
