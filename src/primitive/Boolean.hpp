//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_BOOLEAN_HPP
#define CDS_BOOLEAN_HPP

#include <CDS/Object>

class Boolean : public Object {
private:
    bool v { false };
public:
    constexpr Boolean () noexcept = default;
    constexpr Boolean ( Boolean const & ) noexcept = default;
    constexpr Boolean ( Boolean && ) noexcept = default;
    __CDS_cpplang_ConstexprDestructor ~Boolean() noexcept override { } /* NOLINT(modernize-use-equals-default) */ /* causes destructor to be created after the True/False constexpr variables (cpp20) */

    constexpr Boolean ( bool v ) noexcept : v(v) { } // NOLINT(google-explicit-constructor)

    __CDS_cpplang_NonConstConstexprMemberFunction Boolean & operator = ( Boolean const & o ) noexcept {
        if ( this == & o ) return * this;
        this->v = o.v;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction Boolean & operator = ( bool value ) noexcept {
        this->v = value;
        return * this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator &&(Boolean const & o) const noexcept -> Boolean {
        return this->v && o.v;
    }

    __CDS_cpplang_ConstexprDestructor auto operator && ( bool value ) const noexcept -> Boolean {
        return this->v && value;
    }

    __CDS_cpplang_ConstexprDestructor auto operator ||(Boolean const & o) const noexcept -> Boolean {
        return this->v || o.v;
    }

    __CDS_cpplang_ConstexprDestructor auto operator || ( bool value ) const noexcept -> Boolean {
        return this->v || value;
    }

    __CDS_cpplang_ConstexprDestructor auto operator ! () const noexcept -> Boolean {
        return !this->v;
    }

    constexpr auto operator == (Boolean const & o) const noexcept -> bool { return this->v == o.v; }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->v;
    }

    __CDS_NoDiscard constexpr inline auto get () const noexcept -> bool {
        return this->v;
    }

    __CDS_NoDiscard auto hash () const noexcept -> Index override {
        return static_cast < Index > (this->v);
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override {
        return String().append(this->v ? "true" : "false");
    }

    inline static auto parse(String const & string) noexcept -> Boolean {
        if ( string.empty() ) return false;

        return string == "true";
    }

    __CDS_NoDiscard auto copy () const noexcept -> Boolean * override {
        return new Boolean( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseBoolean = Atomic<Boolean>; // NOLINT(bugprone-reserved-identifier)
}

class Boolean::Atomic : public hidden::_AtomicBaseBoolean { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(false);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseBoolean(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseBoolean(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Boolean const & v ) noexcept : hidden::_AtomicBaseBoolean(v) { } // NOLINT(google-explicit-constructor)

    Atomic (bool v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    Atomic & operator = (bool value) noexcept {
        this->set(Boolean(value));
        return * this;
    }

    Atomic & operator = (Boolean const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)  /* NOLINT(bugprone-reserved-identifier,bugprone-macro-parenthesis) */                              \
auto operator _operator (bool value) noexcept -> Atomic & {  \
    this->_access.lock();                                   \
    this->_data _operator value;                            \
    this->_access.unlock();                                 \
    return * this;                                          \
}

#undef _PREFIX_OP
};

__CDS_cpplang_ConstexprDestructor auto operator "" _b (unsigned long long int i) noexcept -> Boolean {
    return {i != 0};
}

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

__CDS_cpplang_ConstexprDestructor const Boolean True = true;
__CDS_cpplang_ConstexprDestructor const Boolean False = false;

#else

#define True true
#define False false

#endif

#undef __boolean_constexpr

#endif //CDS_BOOLEAN_HPP
