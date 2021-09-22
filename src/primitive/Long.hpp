//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_LONG_HPP
#define CDS_LONG_HPP

#include <CDS/Object>
#include <CDS/Random>

class Long : public Object {
private:
    long long int v{0llu};
public:
    using RandomGenerator = Random::Long;

    static auto random () noexcept -> Long {
        return RandomGenerator ().get();
    }

    static auto random (long long int low, long long int high) noexcept -> Long {
        return RandomGenerator (low, high).get();
    }

    constexpr Long() noexcept = default;
    constexpr Long(Long const&)noexcept=default;
    constexpr Long(Long &&)noexcept=default;
    __CDS_cpplang_ConstexprDestructor ~Long() noexcept override = default;
    constexpr Long(long long int value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    __CDS_cpplang_NonConstConstexprMemberFunction Long &operator=(Long const &o) noexcept {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction Long &operator=(long long int value) noexcept {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_ConstexprDestructor auto operator+(Long const &o) const noexcept -> Long { return this->v + o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator+(long long int value) const noexcept -> Long { return this->v + value; }
    __CDS_cpplang_ConstexprDestructor auto operator-(Long const &o) const noexcept -> Long { return this->v - o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator-(long long int value) const noexcept -> Long { return this->v - value; }
    __CDS_cpplang_ConstexprDestructor auto operator*(Long const &o) const noexcept -> Long { return this->v * o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator*(long long int value) const noexcept -> Long { return this->v * value; }
    __CDS_cpplang_ConstexprDestructor auto operator/(Long const &o) const noexcept -> Long { return this->v / o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator/(long long int value) const noexcept -> Long { return this->v / value; }
    __CDS_cpplang_ConstexprDestructor auto operator%(Long const &o) const noexcept -> Long { return this->v % o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator%(long long int value) const noexcept -> Long { return this->v % value; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(Long const &o) noexcept -> Long & {
        this->v += o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(long long int value) noexcept -> Long & {
        this->v += value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Long const &o) noexcept -> Long & {
        this->v -= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(long long int value) noexcept -> Long & {
        this->v -= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Long const &o) noexcept -> Long & {
        this->v *= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(long long int value) noexcept -> Long & {
        this->v *= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Long const &o) noexcept -> Long & {
        this->v /= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(long long int value) noexcept -> Long & {
        this->v /= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Long const &o) noexcept -> Long & {
        this->v %= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(long long int value) noexcept -> Long & {
        this->v %= value;
        return *this;
    }

    constexpr auto operator==(Long const &o) const noexcept -> bool { return this->v == o.v; }
    constexpr auto operator==(long long int value) const noexcept -> bool { return this->v == value; }
    constexpr auto operator!=(Long const &o) const noexcept -> bool { return this->v != o.v; }
    constexpr auto operator!=(long long int value) const noexcept -> bool { return this->v != value; }
    constexpr auto operator>(Long const &o) const noexcept -> bool { return this->v > o.v; }
    constexpr auto operator>(long long int value) const noexcept -> bool { return this->v > value; }
    constexpr auto operator<(Long const &o) const noexcept -> bool { return this->v < o.v; }
    constexpr auto operator<(long long int value) const noexcept -> bool { return this->v < value; }
    constexpr auto operator>=(Long const &o) const noexcept -> bool { return this->v >= o.v; }
    constexpr auto operator>=(long long int value) const noexcept -> bool { return this->v >= value; }
    constexpr auto operator<=(Long const &o) const noexcept -> bool { return this->v <= o.v; }
    constexpr auto operator<=(long long int value) const noexcept -> bool { return this->v <= value; }

    __CDS_cpplang_ConstexprDestructor auto operator&(Long const &o) const noexcept -> Long { return this->v & o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator&(long long int value) const noexcept -> Long { return this->v & value; }
    __CDS_cpplang_ConstexprDestructor auto operator|(Long const &o) const noexcept -> Long { return this->v | o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator|(long long int value) const noexcept -> Long { return this->v | value; }
    __CDS_cpplang_ConstexprDestructor auto operator^(Long const &o) const noexcept -> Long { return this->v ^ o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator^(long long int value) const noexcept -> Long { return this->v ^ value; }
    __CDS_cpplang_ConstexprDestructor auto operator<<(Long const &o) const noexcept -> Long { return this->v << o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator<<(long long int value) const noexcept -> Long { return this->v << value; }
    __CDS_cpplang_ConstexprDestructor auto operator>>(Long const &o) const noexcept -> Long { return this->v >> o.v; }
    __CDS_cpplang_ConstexprDestructor auto operator>>(long long int value) const noexcept -> Long { return this->v >> value; }
    __CDS_cpplang_ConstexprDestructor auto operator~() const noexcept -> Long {return ~this->v;}

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Long const &o) noexcept -> Long & {
        this->v &= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(long long int value) noexcept -> Long & {
        this->v &= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Long const &o) noexcept -> Long & {
        this->v |= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(long long int value) noexcept -> Long & {
        this->v |= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Long const &o) noexcept -> Long & {
        this->v ^= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(long long int value) noexcept -> Long & {
        this->v ^= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Long const &o) noexcept -> Long & {
        this->v <<= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(long long int  value) noexcept -> Long & {
        this->v <<= value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Long const &o) noexcept -> Long & {
        this->v >>= o.v;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(long long int  value) noexcept -> Long & {
        this->v >>= value;
        return *this;
    }

    constexpr operator long long int() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)
    __CDS_NoDiscard constexpr inline auto get() const noexcept -> long long int { return this->v; }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Long & { this->v++; return * this; }
    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Long { auto c = * this; this->v++; return c; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Long & { this->v--; return * this; }
    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Long { auto c = * this; this->v--; return c; }

public:
    __CDS_NoDiscard auto hash() const noexcept -> Index override {
        return static_cast < Index > (this->v);
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override {
        return String().append(this->v);
    }

    static auto parse(String const & string) noexcept -> Long {
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

        long long int numericValue = 0;

        while ( isNumericChar ( it.value() ) && it != string.end() ) {
            numericValue = numericValue * 10 + numericCharToInt ( it.value() );
            it.next();
        }

        return negative ? (- numericValue) : numericValue;
    }

    [[nodiscard]] auto copy () const noexcept -> Long * override {
        return new Long( * this );
    }

    class Atomic;
};

#include <CDS/Atomic>
namespace hidden {
    using _AtomicBaseLong = Atomic<Long>; // NOLINT(bugprone-reserved-identifier)
}

class Long::Atomic : public hidden::_AtomicBaseLong { // NOLINT(bugprone-reserved-identifier)
public:
    Atomic () noexcept {
        this->set(0);
    }

    Atomic ( Atomic const & obj ) noexcept : hidden::_AtomicBaseLong(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : hidden::_AtomicBaseLong(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Long const & v ) noexcept : hidden::_AtomicBaseLong(v) { } // NOLINT(google-explicit-constructor)

    Atomic (long long int v) noexcept { // NOLINT(google-explicit-constructor)
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

    Atomic & operator = (long long int value) noexcept {
        this->set(Long(value));
        return * this;
    }

    Atomic & operator = (Long const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator long long int () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

#define _PREFIX_OP(_operator)                               \
auto operator _operator (long long int value) noexcept -> Atomic & {  \
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

#if defined(CDS_LONG_PREFIX)

__CDS_cpplang_ConstexprDestructor auto operator "" _obj (unsigned long long int value) noexcept -> Long {
    return static_cast < long long int > ( value );
}

__CDS_cpplang_ConstexprDestructor auto operator "" _l (unsigned long long int value) noexcept -> Long {
    return static_cast < long long int > ( value );
}

#endif

#endif //CDS_LONG_HPP
