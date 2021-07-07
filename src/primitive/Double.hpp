//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include <CDS/Random>
#include "../cdsIntern/PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __double_constexpr constexpr
#else
#define __double_constexpr inline
#endif

class Double : public Object {
private:
    double v{0.0};
public:
    using RandomGenerator = Random::Double;

    static auto random () noexcept -> Double {
        return RandomGenerator ().get();
    }

    static auto random (double low, double high) noexcept -> Double {
        return RandomGenerator (low, high).get();
    }

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

    auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

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

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseDouble = Atomic<Double>;
}

class Double::Atomic : public hidden::_AtomicBaseDouble {
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseDouble(obj) { }
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseDouble(obj) { }
    Atomic ( Double const & v ) noexcept : hidden::_AtomicBaseDouble(v) { }

    Atomic (double v) noexcept {
        this->set(v);
    }

    Atomic & operator = (double value) noexcept {
        this->set(Double(value));
        return * this;
    }

    Atomic & operator = (Double const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator double () const noexcept {
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
auto operator _operator (double value) noexcept -> Atomic & {  \
    this->_access.lock();                                   \
    this->_data _operator value;                            \
    this->_access.unlock();                                 \
    return * this;                                          \
}

    _PREFIX_OP(+=)
    _PREFIX_OP(-=)
    _PREFIX_OP(*=)
    _PREFIX_OP(/=)

#undef _PREFIX_OP
};

__double_constexpr auto operator "" _obj (long double value) noexcept -> Double {
    return Double(value);
}

__double_constexpr auto operator "" _d (long double value) noexcept -> Double {
    return Double(value);
}

#undef __double_constexpr

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST
#endif //CDS_DOUBLE_HPP
