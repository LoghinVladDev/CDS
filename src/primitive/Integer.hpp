//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <CDS/Object>
#include "./PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __integer_constexpr constexpr
#else
#define __integer_constexpr
#endif

class Integer : public Object {
private:
    int v{0};
public:
    constexpr Integer() noexcept = default;
    constexpr Integer(Integer const&)noexcept=default;
    constexpr Integer(Integer &&)noexcept=default;

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
    constexpr operator int() const noexcept { return this->v; }
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

    [[nodiscard]] auto copy () const noexcept -> Integer * override {
        return new Integer( * this );
    }
};

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST

#endif //CDS_INTEGER_HPP
