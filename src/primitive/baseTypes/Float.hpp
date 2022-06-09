//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_FLOAT_HPP
#define CDS_FLOAT_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/Utility>
#include <CDS/Memory>

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
        __CDS_NoDiscard auto hash() const noexcept -> Index override {
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

            auto value = static_cast<float> (whole) + ( static_cast<float>(frac) / static_cast<float>(div) );
            return negative ? -value : value;
        }

        class Atomic; // NOLINT(cppcoreguidelines-virtual-class-destructor)
    };

}

#include <CDS/Atomic>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace floatAtomicImpl {

                using Base = Atomic<Float>; // NOLINT(bugprone-reserved-identifier)

            }
        }
    }
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

namespace cds {

    class Float::Atomic : public utility :: hidden :: floatAtomicImpl :: Base { // NOLINT(bugprone-reserved-identifier)
    public:
        Atomic () noexcept {
            this->set(0.0f);
        }

        Atomic ( Atomic const & obj ) noexcept :  // NOLINT(modernize-use-equals-default)
                utility :: hidden :: floatAtomicImpl :: Base (obj) {

        }

        Atomic ( Atomic && obj ) noexcept :  // NOLINT(performance-move-constructor-init)
                utility :: hidden :: floatAtomicImpl :: Base ( std :: forward < utility :: hidden :: floatAtomicImpl :: Base > ( obj ) ) {

        }

        Atomic ( Float const & aFloat ) noexcept :  // NOLINT(google-explicit-constructor)
                utility :: hidden :: floatAtomicImpl :: Base (aFloat) {

        }


        Atomic (float value) noexcept { // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
            this->set(value);
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

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Float const & aFloat ) const noexcept -> bool {
            return this->get() == aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Float const & aFloat ) const noexcept -> bool {
            return this->get() != aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Float const & aFloat ) const noexcept -> bool {
            return this->get() > aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Float const & aFloat ) const noexcept -> bool {
            return this->get() < aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Float const & aFloat ) const noexcept -> bool {
            return this->get() >= aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Float const & aFloat ) const noexcept -> bool {
            return this->get() <= aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( float value ) const noexcept -> bool {
            return this->get() == value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( float value ) const noexcept -> bool {
            return this->get() != value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( float value ) const noexcept -> bool {
            return this->get() > value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( float value ) const noexcept -> bool {
            return this->get() < value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( float value ) const noexcept -> bool {
            return this->get() >= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( float value ) const noexcept -> bool {
            return this->get() <= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator == (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator != (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator > (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator < (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= (float value, Atomic const & obj ) noexcept -> bool {
            return value == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator == (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator != (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator > (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator < (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator >= (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator <= (Float const & aFloat, Atomic const & obj ) noexcept -> bool {
            return aFloat == obj.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & atomic ) const noexcept -> Float { return this->get() + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Float const & aFloat ) const noexcept -> Float { return this->get() + aFloat; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( float value ) const noexcept -> Float { return this->get() + value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( float value, Atomic const & atomic ) noexcept -> Float { return value + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator + ( Float const & value, Atomic const & atomic ) noexcept -> Float { return value.get() + atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & atomic ) const noexcept -> Float { return this->get() - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Float const & aFloat ) const noexcept -> Float { return this->get() - aFloat; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( float value ) const noexcept -> Float { return this->get() - value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( float value, Atomic const & atomic ) noexcept -> Float { return value - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator - ( Float const & value, Atomic const & atomic ) noexcept -> Float { return value.get() - atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & atomic ) const noexcept -> Float { return this->get() * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Float const & aFloat ) const noexcept -> Float { return this->get() * aFloat; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( float value ) const noexcept -> Float { return this->get() * value; }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( float value, Atomic const & atomic ) noexcept -> Float { return value * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline friend auto operator * ( Float const & value, Atomic const & atomic ) noexcept -> Float { return value.get() * atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & atomic ) const noexcept(false) -> Float {
            auto rVal = atomic.get();
            if ( rVal == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->get() / rVal;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Float const & aFloat ) const noexcept(false) -> Float {
            if (aFloat == 0.0f) {
                throw DivideByZeroException();
            }

            return this->get() / aFloat;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( float value ) const noexcept(false) -> Float {
            if ( value == 0.0f ) {
                throw DivideByZeroException();
            }

            return this->get() / value;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( float value, Atomic const & atomic ) noexcept(false) -> Float {
            auto rVal = atomic.get();
            if ( rVal == 0.0f ) {
                throw DivideByZeroException();
            }

            return value / rVal;
        }

        __CDS_NoDiscard __CDS_OptimalInline friend auto operator / ( Float const & value, Atomic const & atomic ) noexcept(false) -> Float {
            auto rVal = atomic.get();
            if ( rVal == 0.0f ) {
                throw DivideByZeroException();
            }

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
            if (value == 0.0f) {
                throw DivideByZeroException();
            }

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
            if (value == 0.0f) {
                throw DivideByZeroException();
            }

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
            if (rVal == 0.0f) {
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

#if defined(CDS_FLOAT_POSTFIX)

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _f (long double value) noexcept -> cds :: Float {
    return static_cast < float > ( value );
}

#endif

__CDS_Meta_RegisterParseType(Float) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_FLOAT_HPP
