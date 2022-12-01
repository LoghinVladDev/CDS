//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_FLOAT_HPP
#define CDS_FLOAT_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/memory/UniquePointer>
#include <CDS/exception/DivideByZeroException>
#include <CDS/exception/IllegalArgumentException>
#include <CDS/memory/Allocation>

namespace cds {

    class Float : public Object {
    private:
        float v{0.0f};
    public:
        using RandomGenerator = Random::Float;

        __CDS_MaybeUnused static auto random () noexcept -> Float {
            static UniquePointer < RandomGenerator > pRng;
            if ( pRng.isNull() ) {
                pRng.reset( Memory :: instance () .create < RandomGenerator > () );
            }

            return pRng->get();
        }

        __CDS_MaybeUnused static auto random (float low, float high) noexcept -> Float {
            static UniquePointer < RandomGenerator > pRng;
            if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) {
                pRng.reset( Memory :: instance () .create < RandomGenerator > (low, high) );
            }

            return pRng->get();
        }

        constexpr Float() noexcept = default;
        constexpr Float(Float const&)noexcept=default;
        constexpr Float(Float &&)noexcept=default;
        __CDS_cpplang_ConstexprDestructor ~Float() noexcept override = default;
        constexpr Float(float value) noexcept: v(value) {} // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)

        explicit constexpr Float(sint8 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(sint16 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(sint32 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(sint64 value) noexcept: v(static_cast < float > (value)) {}

        explicit constexpr Float(uint8 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(uint16 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(uint32 value) noexcept: v(static_cast < float > (value)) {}
        explicit constexpr Float(uint64 value) noexcept: v(static_cast < float > (value)) {}

        explicit constexpr Float(double value) noexcept: v(static_cast < float > (value)) {}

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Float const &aFloat) noexcept -> Float & {
            if (this == &aFloat) {
                return *this;
            }

            this->v = aFloat.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(float value) noexcept -> Float & {
            this->v = value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Float && value) noexcept -> Float & {
            if (this == & value) {
                return *this;
            }

            this->v = exchange ( value.v, 0.0f );
            return *this;
        }

        __CDS_cpplang_ConstexprDestructor auto operator+(Float const &aFloat) const noexcept -> Float { return this->v + aFloat.v; }
        __CDS_cpplang_ConstexprDestructor auto operator+(float value) const noexcept -> Float { return this->v + value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator+(float value, Float const &aFloat) noexcept -> Float { return value + aFloat.v; }

        __CDS_cpplang_ConstexprDestructor auto operator-(Float const &aFloat) const noexcept -> Float { return this->v - aFloat.v; }
        __CDS_cpplang_ConstexprDestructor auto operator-(float value) const noexcept -> Float { return this->v - value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator-(float value, Float const &aFloat) noexcept -> Float { return value - aFloat.v; }

        __CDS_cpplang_ConstexprDestructor auto operator*(Float const &aFloat) const noexcept -> Float { return this->v * aFloat.v; }
        __CDS_cpplang_ConstexprDestructor auto operator*(float value) const noexcept -> Float { return this->v * value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator*(float value, Float const &aFloat) noexcept -> Float { return value * aFloat.v; }

        __CDS_cpplang_ConstexprDestructor auto operator/(Float const &aFloat) const noexcept (false) -> Float {
            if (aFloat.v == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->v / aFloat.v;
        }

        __CDS_cpplang_ConstexprDestructor auto operator/(float value) const noexcept (false) -> Float {
            if ( value == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->v / value;
        }

        __CDS_cpplang_ConstexprDestructor friend auto operator/(float value, Float const & aFloat) noexcept (false) -> Float {
            if (aFloat.v == 0.0f ) {
                throw DivideByZeroException();
            }

            return value / aFloat.v;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(Float const &aFloat) noexcept -> Float & {
            this->v += aFloat.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(float value) noexcept -> Float & {
            this->v += value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Float const &aFloat) noexcept -> Float & {
            this->v -= aFloat.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(float value) noexcept -> Float & {
            this->v -= value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Float const &aFloat) noexcept -> Float & {
            this->v *= aFloat.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(float value) noexcept -> Float & {
            this->v *= value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Float const &aFloat) noexcept (false) -> Float & {
            if (aFloat.v == 0.0f ) {
                throw DivideByZeroException();
            }

            this->v /= aFloat.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(float value) noexcept (false) -> Float & {
            if ( value == 0.0f ) {
                throw DivideByZeroException();
            }

            this->v /= value;
            return *this;
        }

        constexpr auto operator==(Float const &aFloat) const noexcept -> bool { return this->v == aFloat.v; }
        constexpr auto operator==(float value) const noexcept -> bool { return this->v == value; }
        constexpr friend auto operator==(float value, Float const & aFloat) noexcept -> bool { return value == aFloat.v; }
        constexpr auto operator!=(Float const &aFloat) const noexcept -> bool { return this->v != aFloat.v; }
        constexpr auto operator!=(float value) const noexcept -> bool { return this->v != value; }
        constexpr friend auto operator!=(float value, Float const & aFloat) noexcept -> bool { return value != aFloat.v; }
        constexpr auto operator>(Float const &aFloat) const noexcept -> bool { return this->v > aFloat.v; }
        constexpr auto operator>(float value) const noexcept -> bool { return this->v > value; }
        constexpr friend auto operator>(float value, Float const & aFloat) noexcept -> bool { return value > aFloat.v; }
        constexpr auto operator<(Float const &aFloat) const noexcept -> bool { return this->v < aFloat.v; }
        constexpr auto operator<(float value) const noexcept -> bool { return this->v < value; }
        constexpr friend auto operator<(float value, Float const & aFloat) noexcept -> bool { return value < aFloat.v; }
        constexpr auto operator>=(Float const &aFloat) const noexcept -> bool { return this->v >= aFloat.v; }
        constexpr auto operator>=(float value) const noexcept -> bool { return this->v >= value; }
        constexpr friend auto operator>=(float value, Float const & aFloat) noexcept -> bool { return value >= aFloat.v; }
        constexpr auto operator<=(Float const &aFloat) const noexcept -> bool { return this->v <= aFloat.v; }
        constexpr auto operator<=(float value) const noexcept -> bool { return this->v <= value; }
        constexpr friend auto operator<=(float value, Float const & aFloat) noexcept -> bool { return value <= aFloat.v; }

    #if __CDS_cpplang_ThreeWayComparison_available == true

        constexpr auto operator <=> ( Float const & aFloat ) const noexcept -> std :: partial_ordering { return this->v <=> aFloat.v; }
        constexpr auto operator <=> ( float value ) const noexcept -> std :: partial_ordering { return this->v <=> value; }
        constexpr friend auto operator <=> ( float value, Float const & aFloat ) noexcept -> std :: partial_ordering { return value <=> aFloat.v; }

    #endif

        __CDS_NoDiscard auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pFloat = dynamic_cast < decltype (this) > ( & object );
            if (pFloat == nullptr ) {
                return false;
            }

            return this->operator==(*pFloat);
        }

        constexpr operator float() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
        constexpr operator int() const noexcept { return static_cast < int > (this->v); } // NOLINT(google-explicit-constructor)
        __CDS_NoDiscard constexpr auto get() const noexcept -> float { return this->v; }

    public:
        __CDS_NoDiscard auto hash() const noexcept -> Size override {
            return :: cds :: hash(this->v);
        }

        __CDS_NoDiscard auto toString() const noexcept -> String override {
            return String(this->v); // NOLINT(modernize-return-braced-init-list)
        }

        static auto parse(String const & string) noexcept -> Float {
            if ( string.empty() ) {
                return 0.0f;
            }

            auto iterator = string.begin();
            __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char character) noexcept -> bool { return character >= '0' && character <= '9'; };
            __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char character) noexcept -> int { return static_cast < int > (character) - 48; };

            bool pastFloatingPoint = false;
            bool negative = false;

            while (! ( isNumericChar ( * iterator ) ) && iterator != string.end() && ! negative ) {
                if ( * iterator == '-' ) {
                    negative = true;
                }

                (void) ++ iterator;
            }

            while (! ( isNumericChar ( * iterator ) ) && iterator != string.end() ) {
                if ( * iterator == '.' ) {
                    pastFloatingPoint = true;
                }

                (void) ++ iterator;
            }

            int whole = 0;
            int frac = 0;
            int div = 1;

            while ((isNumericChar ( * iterator ) || * iterator == '.' ) && iterator != string.end() ) {
                if ( * iterator == '.' ) {
                    pastFloatingPoint = true;
                    (void) ++ iterator;
                    continue;
                }

                if ( ! pastFloatingPoint ) {
                    whole = whole * 10 + numericCharToInt ( * iterator );
                } else {
                    frac = frac * 10 + numericCharToInt ( * iterator );
                    div *= 10;
                }

                (void) ++ iterator;
            }

            auto value = static_cast<float> (whole) + ( static_cast<float>(frac) / static_cast<float>(div) );
            return negative ? -value : value;
        }
    };

}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#if defined(CDS_FLOAT_POSTFIX)

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _f (long double value) noexcept -> cds :: Float {
    return static_cast < float > ( value );
}

#endif

__CDS_Meta_RegisterParseType(Float) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_FLOAT_HPP
