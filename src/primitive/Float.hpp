//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_FLOAT_HPP
#define CDS_FLOAT_HPP

#include <CDS/Object>
#include "./PrimitiveGenerator.hpp"

#if __cpp_constepxr >= 201907
#define __float_constexpr constexpr
#else
#define __float_constexpr
#endif

class Float : public Object {
//    _G_OBJ(Float, float, v, 0.0f)
private:
    float v{0.0f};
public:
    constexpr Float() noexcept = default;
    constexpr Float(Float const&)noexcept=default;
    constexpr Float(Float &&)noexcept=default;
    __float_constexpr ~Float() noexcept override = default;
    constexpr Float(float value) noexcept: v(value) {}
    constexpr Float &operator=(Float const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }
    constexpr Float &operator=(float value) noexcept {
        this->v = value;
        return *this;
    }
    __float_constexpr auto operator+(Float const &o) const noexcept -> Float { return this->v + o.v; }
    __float_constexpr auto operator+(float value) const noexcept -> Float { return this->v + value; }
    __float_constexpr auto operator-(Float const &o) const noexcept -> Float { return this->v - o.v; }
    __float_constexpr auto operator-(float value) const noexcept -> Float { return this->v - value; }
    __float_constexpr auto operator*(Float const &o) const noexcept -> Float { return this->v * o.v; }
    __float_constexpr auto operator*(float value) const noexcept -> Float { return this->v * value; }
    __float_constexpr auto operator/(Float const &o) const noexcept -> Float { return this->v / o.v; }
    __float_constexpr auto operator/(float value) const noexcept -> Float { return this->v / value; }

    constexpr auto operator+=(Float const &o) noexcept -> Float & {
        this->v += o.v;
        return *this;
    }
    constexpr auto operator+=(float value) noexcept -> Float & {
        this->v += value;
        return *this;
    }
    constexpr auto operator-=(Float const &o) noexcept -> Float & {
        this->v -= o.v;
        return *this;
    }
    constexpr auto operator-=(float value) noexcept -> Float & {
        this->v -= value;
        return *this;
    }
    constexpr auto operator*=(Float const &o) noexcept -> Float & {
        this->v *= o.v;
        return *this;
    }
    constexpr auto operator*=(float value) noexcept -> Float & {
        this->v *= value;
        return *this;
    }
    constexpr auto operator/=(Float const &o) noexcept -> Float & {
        this->v /= o.v;
        return *this;
    }
    constexpr auto operator/=(float value) noexcept -> Float & {
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

    constexpr operator float() const noexcept { return this->v; }
    [[nodiscard]]constexpr inline auto get() const noexcept -> float { return this->v; }

public:
    [[nodiscard]] auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v * 100.0f);
    }

    [[nodiscard]] auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Float {
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
};

#undef _G_OBJ
#undef _G_OP_OBJ
#undef _G_OP_OBJ_CONST

#endif //CDS_FLOAT_HPP
