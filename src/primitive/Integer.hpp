//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <CDS/Object>
#include "../cdsIntern/PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __integer_constexpr constexpr
#else
#define __integer_constexpr
#endif

#include <CDS/Random>
#include <CDS/Pointer>

class Integer : public Object {
private:
    int v{0};
public:
    using RandomGenerator = Random::Int;

    static auto random () noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if (pRng.isNull()) pRng.reset(new RandomGenerator());

        return pRng->get();
    }

    static auto random (int low, int high) noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset(new RandomGenerator(low, high));

        return pRng->get();
    }

    constexpr Integer() noexcept = default;
    constexpr Integer(Integer const&)noexcept = default;
    constexpr Integer(Integer &&)noexcept = default;

    __integer_constexpr ~Integer () noexcept override = default;

    constexpr Integer(int value) noexcept: v(value) {}

    constexpr Integer &operator=(Integer const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }
    constexpr Integer &operator=(int value) noexcept {
        this->v = value;
        return *this;
    }

    __integer_constexpr auto operator+(Integer const &o) const noexcept -> Integer { return this->v + o.v; }
    __integer_constexpr auto operator+(int value) const noexcept -> Integer { return this->v + value; }
    __integer_constexpr auto operator-(Integer const &o) const noexcept -> Integer { return this->v - o.v; }
    __integer_constexpr auto operator-(int value) const noexcept -> Integer { return this->v - value; }
    __integer_constexpr auto operator*(Integer const &o) const noexcept -> Integer { return this->v * o.v; }
    __integer_constexpr auto operator*(int value) const noexcept -> Integer { return this->v * value; }
    __integer_constexpr auto operator/(Integer const &o) const noexcept -> Integer { return this->v / o.v; }
    __integer_constexpr auto operator/(int value) const noexcept -> Integer { return this->v / value; }
    __integer_constexpr auto operator%(Integer const &o) const noexcept -> Integer { return this->v % o.v; }
    __integer_constexpr auto operator%(int value) const noexcept -> Integer { return this->v % value; }

    __integer_constexpr auto operator+=(Integer const &o) noexcept -> Integer & {
        this->v += o.v;
        return *this;
    }
    constexpr auto operator+=(int value) noexcept -> Integer & {
        this->v += value;
        return *this;
    }
    constexpr auto operator-=(Integer const &o) noexcept -> Integer & {
        this->v -= o.v;
        return *this;
    }
    constexpr auto operator-=(int value) noexcept -> Integer & {
        this->v -= value;
        return *this;
    }
    constexpr auto operator*=(Integer const &o) noexcept -> Integer & {
        this->v *= o.v;
        return *this;
    }
    constexpr auto operator*=(int value) noexcept -> Integer & {
        this->v *= value;
        return *this;
    }
    constexpr auto operator/=(Integer const &o) noexcept -> Integer & {
        this->v /= o.v;
        return *this;
    }
    constexpr auto operator/=(int value) noexcept -> Integer & {
        this->v /= value;
        return *this;
    }
    constexpr auto operator%=(Integer const &o) noexcept -> Integer & {
        this->v %= o.v;
        return *this;
    }
    constexpr auto operator%=(int value) noexcept -> Integer & {
        this->v %= value;
        return *this;
    }
    constexpr auto operator==(Integer const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(int value) const noexcept -> bool { return this->v == value; }
    constexpr auto operator!=(Integer const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(int value) const noexcept -> bool { return this->v != value; }
    constexpr auto operator>(Integer const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(int value) const noexcept -> bool { return this->v > value; }
    constexpr auto operator<(Integer const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(int value) const noexcept -> bool { return this->v < value; }
    constexpr auto operator>=(Integer const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(int value) const noexcept -> bool { return this->v >= value; }
    constexpr auto operator<=(Integer const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(int value) const noexcept -> bool { return this->v <= value; }

    __integer_constexpr auto operator&(Integer const &o) const noexcept -> Integer { return this->v & o.v; }
    __integer_constexpr auto operator&(int value) const noexcept -> Integer { return this->v & value; }
    __integer_constexpr auto operator|(Integer const &o) const noexcept -> Integer { return this->v | o.v; }
    __integer_constexpr auto operator|(int value) const noexcept -> Integer { return this->v | value; }
    __integer_constexpr auto operator^(Integer const &o) const noexcept -> Integer { return this->v ^ o.v; }
    __integer_constexpr auto operator^(int value) const noexcept -> Integer { return this->v ^ value; }
    __integer_constexpr auto operator<<(Integer const &o) const noexcept -> Integer { return this->v << o.v; }
    __integer_constexpr auto operator<<(int value) const noexcept -> Integer { return this->v << value; }
    __integer_constexpr auto operator>>(Integer const &o) const noexcept -> Integer { return this->v >> o.v; }
    __integer_constexpr auto operator>>(int value) const noexcept -> Integer { return this->v >> value; }
    __integer_constexpr auto operator~() const noexcept -> Integer {return ~this->v;}

    constexpr auto operator&=(Integer const &o) noexcept -> Integer & {
        this->v &= o.v;
        return *this;
    }
    constexpr auto operator&=(int value) noexcept -> Integer & {
        this->v &= value;
        return *this;
    }
    constexpr auto operator|=(Integer const &o) noexcept -> Integer & {
        this->v |= o.v;
        return *this;
    }
    constexpr auto operator|=(int value) noexcept -> Integer & {
        this->v |= value;
        return *this;
    }
    constexpr auto operator^=(Integer const &o) noexcept -> Integer & {
        this->v ^= o.v;
        return *this;
    }
    constexpr auto operator^=(int value) noexcept -> Integer & {
        this->v ^= value;
        return *this;
    }
    constexpr auto operator<<=(Integer const &o) noexcept -> Integer & {
        this->v <<= o.v;
        return *this;
    }
    constexpr auto operator<<=(int value) noexcept -> Integer & {
        this->v <<= value;
        return *this;
    }
    constexpr auto operator>>=(Integer const &o) noexcept -> Integer & {
        this->v >>= o.v;
        return *this;
    }
    constexpr auto operator>>=(int value) noexcept -> Integer & {
        this->v >>= value;
        return *this;
    }

    constexpr operator int() const noexcept { return this->v; }

    auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr auto operator ++ () noexcept -> Integer & { this->v++; return * this; }
    __integer_constexpr auto operator ++ (int) noexcept -> Integer { auto c = * this; this->v++; return c; }
    constexpr auto operator -- () noexcept -> Integer & { this->v--; return * this; }
    __integer_constexpr auto operator -- (int) noexcept -> Integer { auto c = * this; this->v--; return c; }

    [[nodiscard]]constexpr inline auto get() const noexcept -> int { return this->v; }
public:
    [[nodiscard]] auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v);
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Integer {
        if ( string.empty() ) return 0;

        bool negative = false;

        auto it = string.begin();
        constexpr static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        constexpr static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > ( c ) - 48; };

        while( ! isNumericChar ( it.value() ) && it != string.end() ) {
            if ( it.value() == '-' )
                negative = true;
            it.next();
        }

        int numericValue = 0;

        while ( isNumericChar ( it.value() ) && it != string.end() ) {
            numericValue = numericValue * 10 + numericCharToInt ( it.value() );
            it.next();
        }

        return negative ? (-numericValue) : numericValue;
    }

    [[nodiscard]] auto copy () const noexcept -> Integer * override {
        return new Integer( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseInteger = Atomic<Integer>;
}

class Integer::Atomic : public hidden::_AtomicBaseInteger {
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseInteger(obj) { }
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseInteger(obj) { }
    Atomic ( Integer const & v ) noexcept : hidden::_AtomicBaseInteger(v) { }

    Atomic (int v) noexcept {
        this->set(v);
    }

    auto operator ++ () noexcept -> Atomic & {
        this->_access.lock();
        this->_data++;
        this->_access.unlock();

        return *this;
    }

    auto operator ++ (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        this->_data ++;
        this->_access.unlock();

        return copy;
    }

    auto operator -- () noexcept -> Atomic & {
        this->_access.lock();
        this->_data --;
        this->_access.unlock();

        return * this;
    }

    auto operator -- (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        this->_data --;
        this->_access.unlock();

        return copy;
    }

    Atomic & operator = (int value) noexcept {
        this->set(Integer(value));
        return * this;
    }

    Atomic & operator = (Integer const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator int () const noexcept {
        return this->get().get();
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
//        return String().append(this->get());
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)                               \
auto operator _operator (int value) noexcept -> Atomic & {  \
    this->_access.lock();                                   \
    this->_data _operator value;                            \
    this->_access.unlock();                                 \
    return * this;                                          \
}

    _PREFIX_OP(+=)
    _PREFIX_OP(-=)
    _PREFIX_OP(*=)
    _PREFIX_OP(/=)
    _PREFIX_OP(%=)
    _PREFIX_OP(|=)
    _PREFIX_OP(&=)
    _PREFIX_OP(^=)

#undef _PREFIX_OP
};

__integer_constexpr auto operator "" _i (unsigned long long int value) noexcept -> Integer {
    return Integer(value);
}

#undef __integer_constexpr

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST

#endif //CDS_INTEGER_HPP
