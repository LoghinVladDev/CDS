//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/Pointer>
#include <CDS/Utility>

class Double : public Object {
private:
    double v{0.0f};
public:

    using RandomGenerator = Random::Double;

    static auto random () noexcept -> Double {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() ) pRng.reset( new RandomGenerator() );

        return pRng->get();
    }

    static auto random (double low, double high) noexcept -> Double {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset( new RandomGenerator(low, high) );

        return pRng->get();
    }

    constexpr Double() noexcept = default;
    constexpr Double(Double const&)noexcept=default;
    constexpr Double(Double &&)noexcept=default;
    __CDS_cpplang_ConstexprDestructor ~Double() noexcept override = default;
    constexpr Double(double value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    explicit constexpr Double(sint8 value) noexcept: v(value) {}
    explicit constexpr Double(sint16 value) noexcept: v(value) {}
    explicit constexpr Double(sint32 value) noexcept: v(static_cast < double > (value)) {}
    explicit constexpr Double(sint64 value) noexcept: v(static_cast < double > (value)) {}

    explicit constexpr Double(uint8 value) noexcept: v(value) {}
    explicit constexpr Double(uint16 value) noexcept: v(value) {}
    explicit constexpr Double(uint32 value) noexcept: v(static_cast < double > (value)) {}
    explicit constexpr Double(uint64 value) noexcept: v(static_cast < double > (value)) {}

    explicit constexpr Double(float value) noexcept: v(static_cast < double > (value)) {}

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Double const &o) noexcept -> Double & {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(double value) noexcept -> Double & {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Double && value) noexcept -> Double & {
        if (this == & value) return *this;
        this->v = Utility :: exchange ( value.v, 0.0 );
        return *this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator+(Double const &o) const noexcept -> Double { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(double value) const noexcept -> Double { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator+(double value, Double const &o) noexcept -> Double { return value + o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator-(Double const &o) const noexcept -> Double { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(double value) const noexcept -> Double { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator-(double value, Double const &o) noexcept -> Double { return value - o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator*(Double const &o) const noexcept -> Double { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(double value) const noexcept -> Double { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator*(double value, Double const &o) noexcept -> Double { return value * o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator/(Double const &o) const noexcept (false) -> Double {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        return this->v / o.v;
    }

    __CDS_cpplang_ConstexprDestructor auto operator/(double value) const noexcept (false) -> Double {
        if ( value == 0.0f ) throw DivideByZeroException();

        return this->v / value;
    }

    __CDS_cpplang_ConstexprDestructor friend auto operator/(double value, Double const & o) noexcept (false) -> Double {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        return value / o.v;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(Double const &o) noexcept -> Double & {
        this->v += o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(double value) noexcept -> Double & {
        this->v += value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Double const &o) noexcept -> Double & {
        this->v -= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(double value) noexcept -> Double & {
        this->v -= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Double const &o) noexcept -> Double & {
        this->v *= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(double value) noexcept -> Double & {
        this->v *= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Double const &o) noexcept (false) -> Double & {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        this->v /= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(double value) noexcept (false) -> Double & {
        if ( value == 0.0f ) throw DivideByZeroException();

        this->v /= value;
        return *this;
    }

    constexpr auto operator==(Double const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(double value) const noexcept -> bool { return this->v == value; }
    constexpr friend auto operator==(double value, Double const & o) noexcept -> bool { return value == o.v; }
    constexpr auto operator!=(Double const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(double value) const noexcept -> bool { return this->v != value; }
    constexpr friend auto operator!=(double value, Double const & o) noexcept -> bool { return value != o.v; }
    constexpr auto operator>(Double const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(double value) const noexcept -> bool { return this->v > value; }
    constexpr friend auto operator>(double value, Double const & o) noexcept -> bool { return value > o.v; }
    constexpr auto operator<(Double const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(double value) const noexcept -> bool { return this->v < value; }
    constexpr friend auto operator<(double value, Double const & o) noexcept -> bool { return value < o.v; }
    constexpr auto operator>=(Double const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(double value) const noexcept -> bool { return this->v >= value; }
    constexpr friend auto operator>=(double value, Double const & o) noexcept -> bool { return value >= o.v; }
    constexpr auto operator<=(Double const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(double value) const noexcept -> bool { return this->v <= value; }
    constexpr friend auto operator<=(double value, Double const & o) noexcept -> bool { return value <= o.v; }

#if __CDS_cpplang_ThreeWayComparison_Available == true

    constexpr auto operator <=> ( Double const & o ) const noexcept -> std :: partial_ordering { return this->v <=> o.v; }
    constexpr auto operator <=> ( double value ) const noexcept -> std :: partial_ordering { return this->v <=> value; }
    constexpr friend auto operator <=> ( double value, Double const & o ) noexcept -> std :: partial_ordering { return value <=> o.v; }

#endif

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr operator double() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
    constexpr operator int() const noexcept { return static_cast < int > (this->v); } // NOLINT(google-explicit-constructor)
    __CDS_NoDiscard constexpr auto get() const noexcept -> double { return this->v; }

public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return dataTypes::hash(this->v);
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String(this->v); // NOLINT(modernize-return-braced-init-list)
    }

    static auto parse(String const & string) noexcept -> Double {
        if ( string.empty() ) return 0;

        auto it = string.begin();
        __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > (c) - 48; };

        bool pastFloatingPoint = false, negative = false;

        while ( ! ( isNumericChar ( it.value() ) ) && it != string.end() && ! negative ) {
            if ( it.value() == '-' )
                negative = true;
            it.next();
        }

        while ( ! ( isNumericChar ( it.value() ) ) && it != string.end() ) {
            if ( it.value() == '.' )
                pastFloatingPoint = true;
            it.next();
        }

        int whole = 0, frac = 0, div = 1;

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

        auto value = static_cast<double> (whole) + ( static_cast<double>(frac) / static_cast<double>(div) );
        return negative ? -value : value;
    }

    [[nodiscard]] auto copy () const noexcept -> Double * override {
        return new Double( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace __CDS_HiddenUtility {
    using _AtomicBaseDouble = Atomic<Double>; // NOLINT(bugprone-reserved-identifier)
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif
class Double::Atomic : public __CDS_HiddenUtility::_AtomicBaseDouble { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseDouble(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseDouble(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Double const & v ) noexcept : __CDS_HiddenUtility::_AtomicBaseDouble(v) { } // NOLINT(google-explicit-constructor)

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

    operator Double () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Atomic const & o ) const noexcept -> bool {
        return this->get() == o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Atomic const & o ) const noexcept -> bool {
        return this->get() != o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Atomic const & o ) const noexcept -> bool {
        return this->get() > o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Atomic const & o ) const noexcept -> bool {
        return this->get() < o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Atomic const & o ) const noexcept -> bool {
        return this->get() >= o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Atomic const & o ) const noexcept -> bool {
        return this->get() <= o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Double const & o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Double const & o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Double const & o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Double const & o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Double const & o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Double const & o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( double o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( double o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( double o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( double o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( double o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( double o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator == ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator != ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator > ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator < ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= ( double o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator == ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator != ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator > ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator < ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= ( Double const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & o ) const noexcept -> Double { return this->get() + o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Double const & o ) const noexcept -> Double { return this->get() + o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( double value ) const noexcept -> Double { return this->get() + value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( double value, Atomic const & o ) noexcept -> Double { return value + o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( Double const & value, Atomic const & o ) noexcept -> Double { return value.get() + o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & o ) const noexcept -> Double { return this->get() - o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Double const & o ) const noexcept -> Double { return this->get() - o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( double value ) const noexcept -> Double { return this->get() - value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( double value, Atomic const & o ) noexcept -> Double { return value - o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( Double const & value, Atomic const & o ) noexcept -> Double { return value.get() - o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & o ) const noexcept -> Double { return this->get() * o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Double const & o ) const noexcept -> Double { return this->get() * o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( double value ) const noexcept -> Double { return this->get() * value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( double value, Atomic const & o ) noexcept -> Double { return value * o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( Double const & value, Atomic const & o ) noexcept -> Double { return value.get() * o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & o ) const noexcept(false) -> Double {
        auto rVal = o.get();
        if ( rVal == 0.0 ) throw DivideByZeroException();

        return this->get() / rVal;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Double const & o ) const noexcept(false) -> Double {
        if (o == 0.0) throw DivideByZeroException();

        return this->get() / o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( double value ) const noexcept(false) -> Double {
        if ( value == 0.0 ) throw DivideByZeroException();

        return this->get() / value;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( double value, Atomic const & o ) noexcept(false) -> Double {
        auto rVal = o.get();
        if ( rVal == 0.0 ) throw DivideByZeroException();

        return value / rVal;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( Double const & value, Atomic const & o ) noexcept(false) -> Double {
        auto rVal = o.get();
        if ( rVal == 0.0 ) throw DivideByZeroException();

        return value.get() / rVal;
    }

    __CDS_OptionalInline auto operator += (double value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (double value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (double value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (double value) noexcept (false) -> Atomic & {
        if (value == 0.0f)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Double const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Double const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Double const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Double const & value) noexcept (false) -> Atomic & {
        if (value == 0.0)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Atomic const & value) noexcept -> Atomic & {
        double rVal = value.get();

        this->_access.lock();
        this->_data += rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Atomic const & value) noexcept -> Atomic & {
        double rVal = value.get();

        this->_access.lock();
        this->_data -= rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Atomic const & value) noexcept -> Atomic & {
        double rVal = value.get();

        this->_access.lock();
        this->_data *= rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Atomic const & value) noexcept (false) -> Atomic & {
        double rVal = value.get();
        if (rVal == 0.0)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= rVal;
        this->_access.unlock();
        return * this;
    }
};

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#if defined(CDS_DOUBLE_POSTFIX)

__CDS_cpplang_ConstexprDestructor auto operator "" _obj (long double value) noexcept -> Double {
    return static_cast < double > ( value );
}

__CDS_cpplang_ConstexprDestructor auto operator "" _d (long double value) noexcept -> Double {
    return static_cast < double > ( value );
}

#endif

__CDS_RegisterParseType(Double)


#endif //CDS_DOUBLE_HPP
