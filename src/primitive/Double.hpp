//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include <CDS/Random>

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
    __CDS_cpplang_ConstexprDestructor ~Double() noexcept override = default;
    constexpr Double(double value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    constexpr Double &operator=(Double const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    constexpr Double &operator=(double value) noexcept {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator+(Double const &o) const noexcept -> Double { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(double value) const noexcept -> Double { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor auto operator-(Double const &o) const noexcept -> Double { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(double value) const noexcept -> Double { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor auto operator*(Double const &o) const noexcept -> Double { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(double value) const noexcept -> Double { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor auto operator/(Double const &o) const noexcept -> Double { return this->v / o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator/(double value) const noexcept -> Double { return this->v / value; }

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

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr operator double() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
    __CDS_NoDiscard constexpr inline auto get() const noexcept -> double { return this->v; }

public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v * 10000.0);
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
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

    __CDS_NoDiscard auto copy () const noexcept -> Double * override {
        return new Double( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseDouble = Atomic<Double>; // NOLINT(bugprone-reserved-identifier)
}

class Double::Atomic : public hidden::_AtomicBaseDouble { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseDouble(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseDouble(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Double const & v ) noexcept : hidden::_AtomicBaseDouble(v) { } // NOLINT(google-explicit-constructor)

    Atomic (double v) noexcept { // NOLINT(google-explicit-constructor)
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

    operator double () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
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

__CDS_cpplang_ConstexprDestructor auto operator "" _obj (long double value) noexcept -> Double {
    return static_cast < double > ( value );
}

__CDS_cpplang_ConstexprDestructor auto operator "" _d (long double value) noexcept -> Double {
    return static_cast < double > ( value );
}

#endif //CDS_DOUBLE_HPP
