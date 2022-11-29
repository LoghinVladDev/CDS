//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/memory/UniquePointer>
#include <CDS/Utility>
#include <CDS/memory/Allocation>

namespace cds {

    class Double : public Object {
    private:
    private:
        double v{0.0f};
    public:

        using RandomGenerator = Random::Double;

        __CDS_MaybeUnused static auto random () noexcept -> Double {
            static UniquePointer < RandomGenerator > pRng;
            if ( pRng.isNull() ) {
                pRng.reset( Memory::instance ().create < RandomGenerator > () );
            }

            return pRng->get();
        }

        __CDS_MaybeUnused static auto random (double low, double high) noexcept -> Double {
            static UniquePointer < RandomGenerator > pRng;
            if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) {
                pRng.reset( Memory::instance().create < RandomGenerator >(low, high) );
            }

            return pRng->get();
        }

        constexpr Double() noexcept = default;
        constexpr Double(Double const&)noexcept=default;
        constexpr Double(Double &&)noexcept=default;
        __CDS_cpplang_ConstexprDestructor ~Double() noexcept override = default;
        constexpr Double(double value) noexcept: v(value) {} // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)

        explicit constexpr Double(sint8 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(sint16 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(sint32 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(sint64 value) noexcept: v(static_cast < double > (value)) {}

        explicit constexpr Double(uint8 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(uint16 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(uint32 value) noexcept: v(static_cast < double > (value)) {}
        explicit constexpr Double(uint64 value) noexcept: v(static_cast < double > (value)) {}

        explicit constexpr Double(float value) noexcept: v(static_cast < double > (value)) {}

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Double const & object) noexcept -> Double & {
            if (this == &object) {
                return *this;
            }

            this->v = object.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(double value) noexcept -> Double & {
            this->v = value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Double && value) noexcept -> Double & {
            if (this == & value) {
                return *this;
            }

            this->v = exchange ( value.v, 0.0 );
            return *this;
        }

        __CDS_cpplang_ConstexprDestructor auto operator+(Double const &object) const noexcept -> Double { return this->v + object.v; }
        __CDS_cpplang_ConstexprDestructor auto operator+(double value) const noexcept -> Double { return this->v + value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator+(double value, Double const &object) noexcept -> Double { return value + object.v; }

        __CDS_cpplang_ConstexprDestructor auto operator-(Double const &value) const noexcept -> Double { return this->v - value.v; }
        __CDS_cpplang_ConstexprDestructor auto operator-(double value) const noexcept -> Double { return this->v - value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator-(double value, Double const &object) noexcept -> Double { return value - object.v; }

        __CDS_cpplang_ConstexprDestructor auto operator*(Double const &value) const noexcept -> Double { return this->v * value.v; }
        __CDS_cpplang_ConstexprDestructor auto operator*(double value) const noexcept -> Double { return this->v * value; }
        __CDS_cpplang_ConstexprDestructor friend auto operator*(double value, Double const &object) noexcept -> Double { return value * object.v; }

        __CDS_cpplang_ConstexprDestructor auto operator/(Double const &object) const noexcept (false) -> Double {
            if (object.v == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->v / object.v;
        }

        __CDS_cpplang_ConstexprDestructor auto operator/(double value) const noexcept (false) -> Double {
            if ( value == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->v / value;
        }

        __CDS_cpplang_ConstexprDestructor friend auto operator/(double value, Double const & object) noexcept (false) -> Double {
            if (object.v == 0.0f ) {
                throw DivideByZeroException();
            }

            return value / object.v;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(Double const &value) noexcept -> Double & {
            this->v += value.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(double value) noexcept -> Double & {
            this->v += value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Double const &object) noexcept -> Double & {
            this->v -= object.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(double value) noexcept -> Double & {
            this->v -= value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Double const &value) noexcept -> Double & {
            this->v *= value.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(double value) noexcept -> Double & {
            this->v *= value;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Double const &value) noexcept (false) -> Double & {
            if (value.v == 0.0f ) {
                throw DivideByZeroException();
            }

            this->v /= value.v;
            return *this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(double value) noexcept (false) -> Double & {
            if ( value == 0.0f ) {
                throw DivideByZeroException();
            }

            this->v /= value;
            return *this;
        }

        constexpr auto operator==(Double const &value) const noexcept -> bool { return this->v == value.v; }
        constexpr auto operator==(double value) const noexcept -> bool { return this->v == value; }
        constexpr friend auto operator==(double value, Double const & object) noexcept -> bool { return value == object.v; }
        constexpr auto operator!=(Double const &value) const noexcept -> bool { return this->v != value.v; }
        constexpr auto operator!=(double value) const noexcept -> bool { return this->v != value; }
        constexpr friend auto operator!=(double value, Double const & object) noexcept -> bool { return value != object.v; }
        constexpr auto operator>(Double const &value) const noexcept -> bool { return this->v > value.v; }
        constexpr auto operator>(double value) const noexcept -> bool { return this->v > value; }
        constexpr friend auto operator>(double value, Double const & object) noexcept -> bool { return value > object.v; }
        constexpr auto operator<(Double const &value) const noexcept -> bool { return this->v < value.v; }
        constexpr auto operator<(double value) const noexcept -> bool { return this->v < value; }
        constexpr friend auto operator<(double value, Double const & object) noexcept -> bool { return value < object.v; }
        constexpr auto operator>=(Double const &value) const noexcept -> bool { return this->v >= value.v; }
        constexpr auto operator>=(double value) const noexcept -> bool { return this->v >= value; }
        constexpr friend auto operator>=(double value, Double const & object) noexcept -> bool { return value >= object.v; }
        constexpr auto operator<=(Double const &value) const noexcept -> bool { return this->v <= value.v; }
        constexpr auto operator<=(double value) const noexcept -> bool { return this->v <= value; }
        constexpr friend auto operator<=(double value, Double const & object) noexcept -> bool { return value <= object.v; }

    #if __CDS_cpplang_ThreeWayComparison_available == true

        constexpr auto operator <=> ( Double const & value ) const noexcept -> std :: partial_ordering { return this->v <=> value.v; }
        constexpr auto operator <=> ( double value ) const noexcept -> std :: partial_ordering { return this->v <=> value; }
        constexpr friend auto operator <=> ( double value, Double const & object ) noexcept -> std :: partial_ordering { return value <=> object.v; }

    #endif

        __CDS_NoDiscard auto equals ( Object const & value ) const noexcept -> bool override {
            if ( this == & value ) {
                return true;
            }

            auto pDouble = dynamic_cast < decltype (this) > ( & value );
            if (pDouble == nullptr ) {
                return false;
            }

            return this->operator==(*pDouble);
        }

        constexpr operator double() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
        constexpr operator float() const noexcept { return static_cast < float > ( this->v ); } // NOLINT(google-explicit-constructor)
        constexpr operator int() const noexcept { return static_cast < int > (this->v); } // NOLINT(google-explicit-constructor)
        __CDS_NoDiscard constexpr auto get() const noexcept -> double { return this->v; }

    public:
        __CDS_NoDiscard auto hash() const noexcept -> Size override {
            return :: cds :: hash(this->v);
        }

        __CDS_NoDiscard auto toString() const noexcept -> String override {
            return String(this->v); // NOLINT(modernize-return-braced-init-list)
        }

        static auto parse(String const & string) noexcept -> Double {
            if ( string.empty() ) {
                return 0.0;
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
                    whole = whole * 10 + numericCharToInt( * iterator );
                } else {
                    frac = frac * 10 + numericCharToInt ( * iterator );
                    div *= 10;
                }

                (void) ++ iterator;
            }

            auto value = static_cast<double> (whole) + ( static_cast<double>(frac) / static_cast<double>(div) );
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

#if defined(CDS_DOUBLE_POSTFIX)

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _obj (long double value) noexcept -> cds :: Double {
    return static_cast < double > ( value );
}

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _d (long double value) noexcept -> cds :: Double {
    return static_cast < double > ( value );
}

#endif

__CDS_Meta_RegisterParseType(Double) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_DOUBLE_HPP
