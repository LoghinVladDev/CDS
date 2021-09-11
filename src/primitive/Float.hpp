//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_FLOAT_HPP
#define CDS_FLOAT_HPP

#include <CDS/Object>
#include <CDS/Random>

class Float : public Object {
private:
    float v{0.0f};
public:
    using RandomGenerator = Random::Float;

    static auto random () noexcept -> Float {
        return RandomGenerator ().get();
    }

    static auto random (float low, float high) noexcept -> Float {
        return RandomGenerator (low, high).get();
    }

    constexpr Float() noexcept = default;
    constexpr Float(Float const&)noexcept=default;
    constexpr Float(Float &&)noexcept=default;
    __CDS_cpplang_ConstexprDestructor ~Float() noexcept override = default;
    constexpr Float(float value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)
    __CDS_cpplang_NonConstConstexprMemberFunction Float &operator=(Float const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }
    __CDS_cpplang_NonConstConstexprMemberFunction Float &operator=(float value) noexcept {
        this->v = value;
        return *this;
    }
    __CDS_cpplang_ConstexprDestructor auto operator+(Float const &o) const noexcept -> Float { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(float value) const noexcept -> Float { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor auto operator-(Float const &o) const noexcept -> Float { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(float value) const noexcept -> Float { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor auto operator*(Float const &o) const noexcept -> Float { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(float value) const noexcept -> Float { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor auto operator/(Float const &o) const noexcept -> Float { return this->v / o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator/(float value) const noexcept -> Float { return this->v / value; }

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

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Float const &o) noexcept -> Float & {
        this->v /= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(float value) noexcept -> Float & {
        this->v /= value;
        return *this;
    }

    constexpr auto operator==(Float const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(float value) const noexcept -> bool { return this->v == value; }
    constexpr auto operator!=(Float const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(float value) const noexcept -> bool { return this->v != value; }
    constexpr auto operator>(Float const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(float value) const noexcept -> bool { return this->v > value; }
    constexpr auto operator<(Float const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(float value) const noexcept -> bool { return this->v < value; }
    constexpr auto operator>=(Float const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(float value) const noexcept -> bool { return this->v >= value; }
    constexpr auto operator<=(Float const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(float value) const noexcept -> bool { return this->v <= value; }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    constexpr operator float() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
    __CDS_NoDiscard constexpr inline auto get() const noexcept -> float { return this->v; }

public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v * 100.0f);
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Float {
        if ( string.empty() ) return 0;

        auto it = string.begin();
        __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > (c) - 48; };

        bool pastFloatingPoint = false;

        if ( it.value() == '.' ) {
            pastFloatingPoint = true;
            it.next();
        } else
            while ( ! ( isNumericChar ( it.value() ) ) && it != string.end() )
                it.next();

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

        return static_cast<float> (whole) + ( static_cast<float>(frac) / static_cast<float>(div) );
    }

    [[nodiscard]] auto copy () const noexcept -> Float * override {
        return new Float( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseFloat = Atomic<Float>; // NOLINT(bugprone-reserved-identifier)
}

class Float::Atomic : public hidden::_AtomicBaseFloat { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseFloat(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseFloat(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Float const & v ) noexcept : hidden::_AtomicBaseFloat(v) { } // NOLINT(google-explicit-constructor)

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

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)                               \
auto operator _operator (float value) noexcept -> Atomic & {  \
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

__CDS_cpplang_ConstexprDestructor auto operator "" _f (long double value) noexcept -> Float {
    return static_cast < float > ( value );
}

#endif //CDS_FLOAT_HPP
