//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_FLOAT_HPP
#define CDS_FLOAT_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/Pointer>
#include <CDS/Utility>

class Float : public Object {
private:
    float v{0.0f};
public:
    using RandomGenerator = Random::Float;

    static auto random () noexcept -> Float {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() ) pRng.reset( new RandomGenerator() );

        return pRng->get();
    }

    static auto random (float low, float high) noexcept -> Float {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset( new RandomGenerator(low, high) );

        return pRng->get();
    }

    constexpr Float() noexcept = default;
    constexpr Float(Float const&)noexcept=default;
    constexpr Float(Float &&)noexcept=default;
    __CDS_cpplang_ConstexprDestructor ~Float() noexcept override = default;
    constexpr Float(float value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    explicit constexpr Float(sint8 value) noexcept: v(value) {}
    explicit constexpr Float(sint16 value) noexcept: v(value) {}
    explicit constexpr Float(sint32 value) noexcept: v(static_cast < float > (value)) {}
    explicit constexpr Float(sint64 value) noexcept: v(static_cast < float > (value)) {}

    explicit constexpr Float(uint8 value) noexcept: v(value) {}
    explicit constexpr Float(uint16 value) noexcept: v(value) {}
    explicit constexpr Float(uint32 value) noexcept: v(static_cast < float > (value)) {}
    explicit constexpr Float(uint64 value) noexcept: v(static_cast < float > (value)) {}

    explicit constexpr Float(double value) noexcept: v(static_cast < float > (value)) {}

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Float const &o) noexcept -> Float & {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(float value) noexcept -> Float & {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Float && value) noexcept -> Float & {
        if (this == & value) return *this;
        this->v = Utility :: exchange ( value.v, 0.0f );
        return *this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator+(Float const &o) const noexcept -> Float { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(float value) const noexcept -> Float { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator+(float value, Float const &o) noexcept -> Float { return value + o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator-(Float const &o) const noexcept -> Float { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(float value) const noexcept -> Float { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator-(float value, Float const &o) noexcept -> Float { return value - o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator*(Float const &o) const noexcept -> Float { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(float value) const noexcept -> Float { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor friend auto operator*(float value, Float const &o) noexcept -> Float { return value * o.v; }

    __CDS_cpplang_ConstexprDestructor auto operator/(Float const &o) const noexcept (false) -> Float {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        return this->v / o.v;
    }

    __CDS_cpplang_ConstexprDestructor auto operator/(float value) const noexcept (false) -> Float {
        if ( value == 0.0f ) throw DivideByZeroException();

        return this->v / value;
    }

    __CDS_cpplang_ConstexprDestructor friend auto operator/(float value, Float const & o) noexcept (false) -> Float {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        return value / o.v;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(Float const &o) noexcept -> Float & {
        this->v += o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(float value) noexcept -> Float & {
        this->v += value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Float const &o) noexcept -> Float & {
        this->v -= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(float value) noexcept -> Float & {
        this->v -= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Float const &o) noexcept -> Float & {
        this->v *= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(float value) noexcept -> Float & {
        this->v *= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Float const &o) noexcept (false) -> Float & {
        if ( o.v == 0.0f ) throw DivideByZeroException();

        this->v /= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(float value) noexcept (false) -> Float & {
        if ( value == 0.0f ) throw DivideByZeroException();

        this->v /= value;
        return *this;
    }

    constexpr auto operator==(Float const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(float value) const noexcept -> bool { return this->v == value; }
    constexpr friend auto operator==(float value, Float const & o) noexcept -> bool { return value == o.v; }
    constexpr auto operator!=(Float const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(float value) const noexcept -> bool { return this->v != value; }
    constexpr friend auto operator!=(float value, Float const & o) noexcept -> bool { return value != o.v; }
    constexpr auto operator>(Float const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(float value) const noexcept -> bool { return this->v > value; }
    constexpr friend auto operator>(float value, Float const & o) noexcept -> bool { return value > o.v; }
    constexpr auto operator<(Float const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(float value) const noexcept -> bool { return this->v < value; }
    constexpr friend auto operator<(float value, Float const & o) noexcept -> bool { return value < o.v; }
    constexpr auto operator>=(Float const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(float value) const noexcept -> bool { return this->v >= value; }
    constexpr friend auto operator>=(float value, Float const & o) noexcept -> bool { return value >= o.v; }
    constexpr auto operator<=(Float const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(float value) const noexcept -> bool { return this->v <= value; }
    constexpr friend auto operator<=(float value, Float const & o) noexcept -> bool { return value <= o.v; }

#if __CDS_cpplang_ThreeWayComparison_Available == true

    constexpr auto operator <=> ( Float const & o ) const noexcept -> std :: partial_ordering { return this->v <=> o.v; }
    constexpr auto operator <=> ( float value ) const noexcept -> std :: partial_ordering { return this->v <=> value; }
    constexpr friend auto operator <=> ( float value, Float const & o ) noexcept -> std :: partial_ordering { return value <=> o.v; }

#endif

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr operator float() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
    constexpr operator int() const noexcept { return static_cast < int > (this->v); } // NOLINT(google-explicit-constructor)
    __CDS_NoDiscard constexpr auto get() const noexcept -> float { return this->v; }

public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return dataTypes::hash(this->v);
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String(this->v); // NOLINT(modernize-return-braced-init-list)
    }

    static auto parse(String const & string) noexcept -> Float {
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

        auto value = static_cast<float> (whole) + ( static_cast<float>(frac) / static_cast<float>(div) );
        return negative ? -value : value;
    }

    [[nodiscard]] auto copy () const noexcept -> Float * override {
        return new Float( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace __CDS_HiddenUtility {
    using _AtomicBaseFloat = Atomic<Float>; // NOLINT(bugprone-reserved-identifier)
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
class Float::Atomic : public __CDS_HiddenUtility::_AtomicBaseFloat { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseFloat(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseFloat(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Float const & v ) noexcept : __CDS_HiddenUtility::_AtomicBaseFloat(v) { } // NOLINT(google-explicit-constructor)

    Atomic (float v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    Atomic & operator = (float value) noexcept {
        this->set(Float(value));
        return * this;
    }

    Atomic & operator = (Float const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator float () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    operator Float () const noexcept { // NOLINT(google-explicit-constructor)
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

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Float const & o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Float const & o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Float const & o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Float const & o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Float const & o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Float const & o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( float o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( float o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( float o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( float o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( float o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( float o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator == ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator != ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator > ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator < ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= ( float o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator == ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator != ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator > ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator < ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= ( Float const & o, Atomic const & obj ) noexcept -> bool {
        return o == obj.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & o ) const noexcept -> Float { return this->get() + o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Float const & o ) const noexcept -> Float { return this->get() + o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( float value ) const noexcept -> Float { return this->get() + value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( float value, Atomic const & o ) noexcept -> Float { return value + o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( Float const & value, Atomic const & o ) noexcept -> Float { return value.get() + o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & o ) const noexcept -> Float { return this->get() - o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Float const & o ) const noexcept -> Float { return this->get() - o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( float value ) const noexcept -> Float { return this->get() - value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( float value, Atomic const & o ) noexcept -> Float { return value - o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( Float const & value, Atomic const & o ) noexcept -> Float { return value.get() - o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & o ) const noexcept -> Float { return this->get() * o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Float const & o ) const noexcept -> Float { return this->get() * o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( float value ) const noexcept -> Float { return this->get() * value; }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( float value, Atomic const & o ) noexcept -> Float { return value * o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( Float const & value, Atomic const & o ) noexcept -> Float { return value.get() * o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & o ) const noexcept(false) -> Float {
        auto rVal = o.get();
        if ( rVal == 0.0f ) throw DivideByZeroException();

        return this->get() / rVal;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Float const & o ) const noexcept(false) -> Float {
        if (o == 0.0f) throw DivideByZeroException();

        return this->get() / o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( float value ) const noexcept(false) -> Float {
        if ( value == 0.0f ) throw DivideByZeroException();

        return this->get() / value;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( float value, Atomic const & o ) noexcept(false) -> Float {
        auto rVal = o.get();
        if ( rVal == 0.0f ) throw DivideByZeroException();

        return value / rVal;
    }

    __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( Float const & value, Atomic const & o ) noexcept(false) -> Float {
        auto rVal = o.get();
        if ( rVal == 0.0f ) throw DivideByZeroException();

        return value.get() / rVal;
    }

    __CDS_OptionalInline auto operator += (float value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (float value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (float value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (float value) noexcept (false) -> Atomic & {
        if (value == 0.0f)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Float const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Float const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Float const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Float const & value) noexcept (false) -> Atomic & {
        if (value == 0.0f)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Atomic const & value) noexcept -> Atomic & {
        float rVal = value.get();

        this->_access.lock();
        this->_data += rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Atomic const & value) noexcept -> Atomic & {
        float rVal = value.get();

        this->_access.lock();
        this->_data -= rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Atomic const & value) noexcept -> Atomic & {
        float rVal = value.get();

        this->_access.lock();
        this->_data *= rVal;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Atomic const & value) noexcept (false) -> Atomic & {
        float rVal = value.get();
        if (rVal == 0.0f)
            throw DivideByZeroException();

        this->_access.lock();
        this->_data /= rVal;
        this->_access.unlock();
        return * this;
    }
};
#pragma clang diagnostic pop

#if defined(CDS_FLOAT_POSTFIX)

__CDS_cpplang_ConstexprDestructor auto operator "" _f (long double value) noexcept -> Float {
    return static_cast < float > ( value );
}

#endif

__CDS_RegisterParseType(Float)

#endif //CDS_FLOAT_HPP
