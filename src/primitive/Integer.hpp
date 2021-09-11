//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/Pointer>

class Integer : public Object {
private:
    int v{0};
public:
    using RandomGenerator = Random::Int;

    static auto random () noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if (pRng.isNull()) pRng.reset(new RandomGenerator());

        return pRng->get();
    }

    static auto random (int low, int high) noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset(new RandomGenerator(low, high));

        return pRng->get();
    }

    constexpr Integer() noexcept = default;
    constexpr Integer(Integer const&)noexcept = default;
    constexpr Integer(Integer &&)noexcept = default;

    __CDS_cpplang_ConstexprDestructor ~Integer () noexcept override = default;

    constexpr Integer(int value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    __CDS_cpplang_NonConstConstexprMemberFunction Integer &operator=(Integer const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }
    __CDS_cpplang_NonConstConstexprMemberFunction Integer &operator=(int value) noexcept {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator+(Integer const &o) const noexcept -> Integer { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(int value) const noexcept -> Integer { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor auto operator-(Integer const &o) const noexcept -> Integer { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(int value) const noexcept -> Integer { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor auto operator*(Integer const &o) const noexcept -> Integer { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(int value) const noexcept -> Integer { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor auto operator/(Integer const &o) const noexcept -> Integer { return this->v / o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator/(int value) const noexcept -> Integer { return this->v / value; }
    __CDS_cpplang_ConstexprDestructor auto operator%(Integer const &o) const noexcept -> Integer { return this->v % o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator%(int value) const noexcept -> Integer { return this->v % value; }

    __CDS_cpplang_ConstexprDestructor auto operator+=(Integer const &o) noexcept -> Integer & {
        this->v += o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(int value) noexcept -> Integer & {
        this->v += value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Integer const &o) noexcept -> Integer & {
        this->v -= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(int value) noexcept -> Integer & {
        this->v -= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Integer const &o) noexcept -> Integer & {
        this->v *= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(int value) noexcept -> Integer & {
        this->v *= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Integer const &o) noexcept -> Integer & {
        this->v /= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(int value) noexcept -> Integer & {
        this->v /= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Integer const &o) noexcept -> Integer & {
        this->v %= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(int value) noexcept -> Integer & {
        this->v %= value;
        return *this;
    }

    constexpr auto operator==(Integer const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(int value) const noexcept -> bool { return this->v == value; }
    constexpr auto operator!=(Integer const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(int value) const noexcept -> bool { return this->v != value; }
    constexpr auto operator>(Integer const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(int value) const noexcept -> bool { return this->v > value; }
    constexpr auto operator<(Integer const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(int value) const noexcept -> bool { return this->v < value; }
    constexpr auto operator>=(Integer const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(int value) const noexcept -> bool { return this->v >= value; }
    constexpr auto operator<=(Integer const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(int value) const noexcept -> bool { return this->v <= value; }

    __CDS_cpplang_ConstexprDestructor auto operator&(Integer const &o) const noexcept -> Integer { return this->v & o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator&(int value) const noexcept -> Integer { return this->v & value; }
    __CDS_cpplang_ConstexprDestructor auto operator|(Integer const &o) const noexcept -> Integer { return this->v | o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator|(int value) const noexcept -> Integer { return this->v | value; }
    __CDS_cpplang_ConstexprDestructor auto operator^(Integer const &o) const noexcept -> Integer { return this->v ^ o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator^(int value) const noexcept -> Integer { return this->v ^ value; }
    __CDS_cpplang_ConstexprDestructor auto operator<<(Integer const &o) const noexcept -> Integer { return this->v << o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator<<(int value) const noexcept -> Integer { return this->v << value; }
    __CDS_cpplang_ConstexprDestructor auto operator>>(Integer const &o) const noexcept -> Integer { return this->v >> o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator>>(int value) const noexcept -> Integer { return this->v >> value; }
    __CDS_cpplang_ConstexprDestructor auto operator~() const noexcept -> Integer {return ~this->v;}

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Integer const &o) noexcept -> Integer & {
        this->v &= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(int value) noexcept -> Integer & {
        this->v &= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Integer const &o) noexcept -> Integer & {
        this->v |= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(int value) noexcept -> Integer & {
        this->v |= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Integer const &o) noexcept -> Integer & {
        this->v ^= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(int value) noexcept -> Integer & {
        this->v ^= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Integer const &o) noexcept -> Integer & {
        this->v <<= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(int value) noexcept -> Integer & {
        this->v <<= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Integer const &o) noexcept -> Integer & {
        this->v >>= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(int value) noexcept -> Integer & {
        this->v >>= value;
        return *this;
    }

    constexpr operator int() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Integer & { this->v++; return * this; }
    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Integer { auto c = * this; this->v++; return c; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Integer & { this->v--; return * this; }
    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Integer { auto c = * this; this->v--; return c; }

    __CDS_NoDiscard constexpr inline auto get() const noexcept -> int { return this->v; }
public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v);
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Integer {
        if ( string.empty() ) return 0;

        bool negative = false;

        auto it = string.begin();
        __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char c) noexcept -> bool { return c >= '0' && c <= '9'; };
        __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char c) noexcept -> int { return static_cast < int > ( c ) - 48; };

        while( ! isNumericChar ( it.value() ) && it != string.end() ) {
            if ( it.value() == '-' )
                negative = true;
            it.next();
        }

        int numericValue = 0;

        while ( isNumericChar ( it.value() ) && it != string.end() ) {
            numericValue = numericValue * 10 + numericCharToInt ( it.value() );
            it.next();
        }

        return negative ? (-numericValue) : numericValue;
    }

    __CDS_NoDiscard auto copy () const noexcept -> Integer * override {
        return new Integer( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseInteger = Atomic<Integer>; // NOLINT(bugprone-reserved-identifier)
}

class Integer::Atomic : public hidden::_AtomicBaseInteger { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseInteger(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseInteger(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Integer const & v ) noexcept : hidden::_AtomicBaseInteger(v) { } // NOLINT(google-explicit-constructor)

    Atomic (int v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    auto operator ++ () noexcept -> Atomic & {
        this->_access.lock();
        this->_data++;
        this->_access.unlock();

        return *this;
    }

    auto operator ++ (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        this->_data ++;
        this->_access.unlock();

        return copy;
    }

    auto operator -- () noexcept -> Atomic & {
        this->_access.lock();
        this->_data --;
        this->_access.unlock();

        return * this;
    }

    auto operator -- (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        this->_data --;
        this->_access.unlock();

        return copy;
    }

    Atomic & operator = (int value) noexcept {
        this->set(Integer(value));
        return * this;
    }

    Atomic & operator = (Integer const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator int () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)                               \
auto operator _operator (int value) noexcept -> Atomic & {  \
    this->_access.lock();                                   \
    this->_data _operator value;                            \
    this->_access.unlock();                                 \
    return * this;                                          \
}

    _PREFIX_OP(+=)
    _PREFIX_OP(-=)
    _PREFIX_OP(*=)
    _PREFIX_OP(/=)
    _PREFIX_OP(%=)
    _PREFIX_OP(|=)
    _PREFIX_OP(&=)
    _PREFIX_OP(^=)

#undef _PREFIX_OP

};

__CDS_cpplang_ConstexprDestructor auto operator "" _i (unsigned long long int value) noexcept -> Integer {
    return static_cast < int > (value);
}

#endif //CDS_INTEGER_HPP
