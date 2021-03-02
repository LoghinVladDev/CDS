//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include "./PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __double_constexpr constexpr
#else
#define __double_constexpr
#endif

class Double : public Object {
private:
    double v{0.0};
public:
    constexpr Double() noexcept = default;
    constexpr Double(Double const&)noexcept=default;
    constexpr Double(Double &&)noexcept=default;
    __double_constexpr ~Double() noexcept override = default;
    constexpr Double(double value) noexcept: v(value) {}
    constexpr Double &operator=(Double const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }
    constexpr Double &operator=(double value) noexcept {
        this->v = value;
        return *this;
    }
    __double_constexpr auto operator+(Double const &o) const noexcept -> Double { return this->v + o.v; }
    __double_constexpr auto operator+(double value) const noexcept -> Double { return this->v + value; }
    __double_constexpr auto operator-(Double const &o) const noexcept -> Double { return this->v - o.v; }
    __double_constexpr auto operator-(double value) const noexcept -> Double { return this->v - value; }
    __double_constexpr auto operator*(Double const &o) const noexcept -> Double { return this->v * o.v; }
    __double_constexpr auto operator*(double value) const noexcept -> Double { return this->v * value; }
    __double_constexpr auto operator/(Double const &o) const noexcept -> Double { return this->v / o.v; }
    __double_constexpr auto operator/(double value) const noexcept -> Double { return this->v / value; }

    constexpr auto operator+=(Double const &o) noexcept -> Double & {
        this->v += o.v;
        return *this;
    }
    constexpr auto operator+=(double value) noexcept -> Double & {
        this->v += value;
        return *this;
    }
    constexpr auto operator-=(Double const &o) noexcept -> Double & {
        this->v -= o.v;
        return *this;
    }
    constexpr auto operator-=(double value) noexcept -> Double & {
        this->v -= value;
        return *this;
    }
    constexpr auto operator*=(Double const &o) noexcept -> Double & {
        this->v *= o.v;
        return *this;
    }
    constexpr auto operator*=(double value) noexcept -> Double & {
        this->v *= value;
        return *this;
    }
    constexpr auto operator/=(Double const &o) noexcept -> Double & {
        this->v /= o.v;
        return *this;
    }
    constexpr auto operator/=(double value) noexcept -> Double & {
        this->v /= value;
        return *this;
    }

    constexpr auto operator==(Double const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(double value) const noexcept -> bool { return this->v == value; }
    constexpr auto operator!=(Double const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(double value) const noexcept -> bool { return this->v != value; }
    constexpr auto operator>(Double const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(double value) const noexcept -> bool { return this->v > value; }
    constexpr auto operator<(Double const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(double value) const noexcept -> bool { return this->v < value; }
    constexpr auto operator>=(Double const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(double value) const noexcept -> bool { return this->v >= value; }
    constexpr auto operator<=(Double const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(double value) const noexcept -> bool { return this->v <= value; }

    constexpr operator double() const noexcept { return this->v; }
    [[nodiscard]]constexpr inline auto get() const noexcept -> double { return this->v; }

public:
    [[nodiscard]] auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v * 10000.0);
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Double {
        if ( string.empty() ) return 0;

        auto it = string.begin();
        constexpr static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        constexpr static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > (c) - 48; };

        bool pastFloatingPoint = false;

        if ( it.value() == '.' ) {
            pastFloatingPoint = true;
            it.next();
        } else
            while ( ! ( isNumericChar ( it.value() ) ) && it != string.end() )
                it.next();

        long long int whole = 0, frac = 0, div = 1;

        while ( ( isNumericChar (it.value()) || it.value() == '.' ) && it != string.end() ) {
            if ( it.value() == '.' ) {
                pastFloatingPoint = true;
                it.next();
                continue;
            }

            if ( ! pastFloatingPoint )
                whole = whole * 10 + numericCharToInt ( it.value() );
            else {
                frac = frac * 10 + numericCharToInt(it.value());
                div *= 10;
            }

            it.next();
        }

        return static_cast<double> (whole) + ( static_cast<double>(frac) / static_cast<double>(div) );
    }

    [[nodiscard]] auto copy () const noexcept -> Double * override {
        return new Double( * this );
    }
};

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST

#endif //CDS_DOUBLE_HPP
