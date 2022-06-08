//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_DOUBLE_HPP
#define CDS_DOUBLE_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/Utility>
#include <CDS/Memory>

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
        __CDS_NoDiscard auto hash() const noexcept -> Index override {
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

            while (! ( isNumericChar (iterator.value() ) ) && iterator != string.end() && ! negative ) {
                if (iterator.value() == '-' ) {
                    negative = true;
                }

                (void) iterator.next();
            }

            while (! ( isNumericChar (iterator.value() ) ) && iterator != string.end() ) {
                if (iterator.value() == '.' ) {
                    pastFloatingPoint = true;
                }

                (void) iterator.next();
            }

            int whole = 0;
            int frac = 0;
            int div = 1;

            while ((isNumericChar (iterator.value()) || iterator.value() == '.' ) && iterator != string.end() ) {
                if (iterator.value() == '.' ) {
                    pastFloatingPoint = true;
                    (void) iterator.next();
                    continue;
                }

                if ( ! pastFloatingPoint ) {
                    whole = whole * 10 + numericCharToInt(iterator.value());
                } else {
                    frac = frac * 10 + numericCharToInt(iterator.value());
                    div *= 10;
                }

                (void) iterator.next();
            }

            auto value = static_cast<double> (whole) + ( static_cast<double>(frac) / static_cast<double>(div) );
            return negative ? -value : value;
        }

        class Atomic; // NOLINT(cppcoreguidelines-virtual-class-destructor)
    };

}

#include <CDS/Atomic>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace doubleAtomicImpl {

                using Base = Atomic<Double>; // NOLINT(bugprone-reserved-identifier)

            }
        }
    }
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

namespace cds {

    class Double::Atomic : public utility :: hidden :: doubleAtomicImpl :: Base { // NOLINT(bugprone-reserved-identifier)
    public:
        Atomic () noexcept {
            this->set(0.0);
        }

        Atomic ( Atomic const & obj ) noexcept : // NOLINT(modernize-use-equals-default)
                utility :: hidden :: doubleAtomicImpl :: Base (obj) {

        }

        Atomic ( Atomic && obj ) noexcept : // NOLINT(performance-move-constructor-init)
                utility :: hidden :: doubleAtomicImpl :: Base ( std :: forward < utility :: hidden :: doubleAtomicImpl :: Base > ( obj ) ) {

        }

        Atomic ( Double const & value ) noexcept : // NOLINT(google-explicit-constructor)
                utility :: hidden :: doubleAtomicImpl :: Base (value) {

        }

        Atomic (double value) noexcept { // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
            this->set(value);
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

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() == atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() != atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() > atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() < atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() >= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() <= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Double const & aDouble ) const noexcept -> bool {
            return this->get() == aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Double const & aDouble ) const noexcept -> bool {
            return this->get() != aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Double const & aDouble ) const noexcept -> bool {
            return this->get() > aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Double const & aDouble ) const noexcept -> bool {
            return this->get() < aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Double const & aDouble ) const noexcept -> bool {
            return this->get() >= aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Double const & aDouble ) const noexcept -> bool {
            return this->get() <= aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( double value ) const noexcept -> bool {
            return this->get() == value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( double value ) const noexcept -> bool {
            return this->get() != value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( double value ) const noexcept -> bool {
            return this->get() > value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( double value ) const noexcept -> bool {
            return this->get() < value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( double value ) const noexcept -> bool {
            return this->get() >= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( double value ) const noexcept -> bool {
            return this->get() <= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator == (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator != (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator > (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator < (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= (double value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator == (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator != (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator > (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator < (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= (Double const & aDouble, Atomic const & obj ) noexcept -> bool {
            return aDouble == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & atomic ) const noexcept -> Double { return this->get() + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Double const & aDouble ) const noexcept -> Double { return this->get() + aDouble; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( double value ) const noexcept -> Double { return this->get() + value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( double value, Atomic const & atomic ) noexcept -> Double { return value + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( Double const & value, Atomic const & atomic ) noexcept -> Double { return value.get() + atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & atomic ) const noexcept -> Double { return this->get() - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Double const & aDouble ) const noexcept -> Double { return this->get() - aDouble; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( double value ) const noexcept -> Double { return this->get() - value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( double value, Atomic const & atomic ) noexcept -> Double { return value - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( Double const & value, Atomic const & atomic ) noexcept -> Double { return value.get() - atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & atomic ) const noexcept -> Double { return this->get() * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Double const & aDouble ) const noexcept -> Double { return this->get() * aDouble; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( double value ) const noexcept -> Double { return this->get() * value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( double value, Atomic const & atomic ) noexcept -> Double { return value * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( Double const & value, Atomic const & atomic ) noexcept -> Double { return value.get() * atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & atomic ) const noexcept(false) -> Double {
            auto rVal = atomic.get();
            if ( rVal == 0.0 ) {
                throw DivideByZeroException();
            }

            return this->get() / rVal;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Double const & aDouble ) const noexcept(false) -> Double {
            if (aDouble == 0.0) {
                throw DivideByZeroException();
            }

            return this->get() / aDouble;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( double value ) const noexcept(false) -> Double {
            if ( value == 0.0 ) {
                throw DivideByZeroException();
            }

            return this->get() / value;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( double value, Atomic const & atomic ) noexcept(false) -> Double {
            auto rVal = atomic.get();
            if ( rVal == 0.0 ) {
                throw DivideByZeroException();
            }

            return value / rVal;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( Double const & value, Atomic const & atomic ) noexcept(false) -> Double {
            auto rVal = atomic.get();
            if ( rVal == 0.0 ) {
                throw DivideByZeroException();
            }

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
            if (value == 0.0f) {
                throw DivideByZeroException();
            }

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
            if (value == 0.0) {
                throw DivideByZeroException();
            }

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
            if (rVal == 0.0) {
                throw DivideByZeroException();
            }

            this->_access.lock();
            this->_data /= rVal;
            this->_access.unlock();
            return * this;
        }
    };

}

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

__CDS_RegisterParseType(Double) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_DOUBLE_HPP
