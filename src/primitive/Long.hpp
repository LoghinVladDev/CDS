//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_LONG_HPP
#define CDS_LONG_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/Pointer>
#include <CDS/Utility>
#include <CDS/Limits>
#include <CDS/Integer>

/**
 * @class Object Derived container for a Boolean Value
 *
 * @test Test in primitive/LongTest
 */
class Long : public Object {
public:
    
    using CType = sint64;
private:

    /**
     * @brief wrapped integer value
     */
    CType v{0};
public:

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto rangeTo (Long const & value) const noexcept -> Range {
        return Range(this->v, value.v);
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto rangeTo (sint64 value) const noexcept -> Range {
        return Range(this->v, value);
    }

    /**
     * @brief Alias for Pseudo-Random Number Generator Type
     */
    using RandomGenerator = Random::Long;

    /**
     * @brief Function used to obtain a random Long value from a Pseudo-Random Number Generator created at first call
     *  that ranges values in [Limits::S64_MIN, INT64_MAX]
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing randomly generated integer value
     *
     * @test Tested in primitive/LongTest/Random Tests
     */
    static auto random () noexcept -> Long {
        static UniquePointer < RandomGenerator > pRng;
        if (pRng.isNull()) pRng.reset(new RandomGenerator());

        return pRng->get();
    }

    /**
     * @brief Function used to obtain a random Long value between two points from a Pseudo-Random Number Generator created at first call with given parameters
     * If parameters differ from last call, a new Pseudo-Random Generator is created
     *
     * @param low : int = low value of the interval of values
     * @param high : int = high value of the interval of values
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing randomly generated integer value
     *
     * @test Tested in primitive/LongTest/Random Tests
     */
    static auto random (CType low, CType high) noexcept -> Long {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset(new RandomGenerator(low, high));

        return pRng->get();
    }

    /**
     * @brief Default Constructor. Creates an Long containing the value 0
     *
     * @exceptsafe
     *
     * @test Tested in primitive/LongTest/Constructor Tests
     */
    constexpr Long() noexcept = default;

    /**
     * @brief Copy Constructor
     *
     * @param obj : Long cref = Constant Reference to an Long Object to copy value from
     *
     * @exceptsafe
     *
     * @test Tested in primitive/LongTest/Constructor Tests
     */
    constexpr Long(Long const&)noexcept = default;

    /**
     * @brief Move Constructor
     *
     * @param obj : Long mref = Move Reference to an Long Object to move value from
     *
     * @exceptsafe
     *
     * @test Tested in primitive/LongTest/Constructor Tests
     */
    constexpr Long(Long &&) noexcept = default;

    __CDS_cpplang_ConstexprConditioned Long(Integer const & o) noexcept : v(o.get()) { } // NOLINT(google-explicit-constructor)

    __CDS_cpplang_ConstexprConditioned Long(Integer && o) noexcept : v(o.get()) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Destructor
     *
     * @exceptsafe
     *
     * @test Not Applicable
     */
    __CDS_cpplang_ConstexprDestructor ~Long () noexcept override = default;

    /**
     * @brief Constructor from literal integer value
     *
     * @param value : CType = value to assign to integer
     *
     * @exceptsafe
     *
     * @test Tested in primitive/LongTest/Constructor Tests
     */
    constexpr Long(CType value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    explicit constexpr Long(sint8 value) noexcept: v(value) {}
    explicit constexpr Long(sint16 value) noexcept: v(value) {}
    explicit constexpr Long(sint32 value) noexcept: v(value) {}

    explicit constexpr Long(uint8 value) noexcept: v(value) {}
    explicit constexpr Long(uint16 value) noexcept: v(value) {}
    explicit constexpr Long(uint32 value) noexcept: v(value) {}
    explicit constexpr Long(uint64 value) noexcept: v(static_cast < sint64 >(value)) {}

    /**
     * @brief Assignment Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to assign value from
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Constructor Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Long const &o) noexcept -> Long & {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    /**
     * @brief Assignment Operator
     *
     * @param value : CType = int value to assign
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Constructor Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(CType value) noexcept -> Long & {
        this->v = value;
        return *this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Long && value) noexcept -> Long & {
        if (this == & value) return *this;
        this->v = Utility :: exchange ( value.v, 0ll );
        return *this;
    }

    /**
     * @brief Sum Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to sum with caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing sum of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+(Long const &o) const noexcept -> Long { return this->v + o.v; }

    /**
     * @brief Sum Operator
     *
     * @param value : CType = int value to sum with caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing sum of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+(CType value) const noexcept -> Long { return this->v + value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator+ (CType value, Long const & o) noexcept -> Long { return value + o.v; }

    /**
     * @brief Difference Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to subtract from caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing difference of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator-(Long const &o) const noexcept -> Long { return this->v - o.v; }

    __CDS_cpplang_ConstexprDestructor friend auto operator - (CType value, Long const & o) noexcept -> Long { return value - o.v; }

    /**
     * @brief Difference Operator
     *
     * @param value : CType = int value to subtract from caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing difference of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator-(CType value) const noexcept -> Long { return this->v - value; }

    /**
     * @brief Multiply Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to multiply from caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing multiplication of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator*(Long const &o) const noexcept -> Long { return this->v * o.v; }

    /**
     * @brief Multiply Operator
     *
     * @param value : CType = int value to multiply with caller Object
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing multiplication of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator*(CType value) const noexcept -> Long { return this->v * value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator * (CType value, Long const & o) noexcept -> Long { return value * o.v; }

    /**
     * @brief Division Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to divide caller Object with
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long = new Object containing division of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator/(Long const &o) const noexcept (false) -> Long {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return this->v / o.v;
    }

    friend auto operator / (CType value, Long const & o) noexcept (false) -> Long {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return value / o.v;
    }

    /**
     * @brief Division Operator
     *
     * @param value : CType = int value to divide caller Object with
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long = new Object containing division of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator / (CType value) const noexcept (false) -> Long {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return this->v / value;
    }

    /**
     * @brief Modulo Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to obtain remainder from caller Object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long = new Object containing remainder of division of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator % (Long const &o) const noexcept (false) -> Long {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return this->v % o.v;
    }

    /**
     * @brief Modulo Operator
     *
     * @param value : CType = int value to obtain remainder from caller Object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long = new Object containing remainder of division of operands
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator % (CType value) const noexcept (false) -> Long {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return this->v % value;
    }

    __CDS_cpplang_ConstexprDestructor friend auto operator % (CType value, Long const & o) noexcept (false) -> Long {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return value % o.v;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Long cref = Constant Reference to Long Object to sum into left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+=(Long const &o) noexcept -> Long & {
        this->v += o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : CType = value to sum into left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(CType value) noexcept -> Long & {
        this->v += value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Long cref = Constant Reference to Long Object to subtract into left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Long const &o) noexcept -> Long & {
        this->v -= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : CType = value to subtract into left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(CType value) noexcept -> Long & {
        this->v -= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Long cref = Constant Reference to Long Object to multiply with left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Long const &o) noexcept -> Long & {
        this->v *= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : CType = value to multiply with left, caller object
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(CType value) noexcept -> Long & {
        this->v *= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Long cref = Constant Reference to Long Object to divide with left, caller object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Long const &o) noexcept (false) -> Long & {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->v /= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : CType = value to divide with left, caller object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(CType value) noexcept (false) -> Long & {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->v /= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Long cref = Constant Reference to Long Object to apply modulo with left, caller object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Long const &o) noexcept (false) -> Long & {
        if ( o.v == 0 ) throw DivideByZeroException();
        if ( o.v == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        this->v %= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : CType = value to apply modulo with left, caller object
     *
     * @throws DivideByZeroException if right hand operator is 0
     * @throws ArithmeticException if right hand operator is Limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
     *
     * @returns Long ref = Reference to modified object
     *
     * @test Tested in primitive/Long/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(CType value) noexcept (false) -> Long & {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN || this->v == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        this->v %= value;
        return *this;
    }

    /**
     * @brief Equality Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects have same value, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator==(Long const &o) const noexcept -> bool { return this->v == o.v; }

    /**
     * @brief Equality Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects have same value, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator==(CType value) const noexcept -> bool { return this->v == value; }

    __CDS_NoDiscard constexpr friend auto operator == (CType value, Long const & o) noexcept -> bool { return value == o.v; }

    /**
     * @brief Difference Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects do not have same value, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator!=(Long const &o) const noexcept -> bool { return this->v != o.v; }

    /**
     * @brief Difference Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects do not have same value, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator!=(CType value) const noexcept -> bool { return this->v != value; }

    __CDS_NoDiscard constexpr friend auto operator != (CType value, Long const & o) noexcept -> bool { return value != o.v; }

    /**
     * @brief Greater Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator>(Long const &o) const noexcept -> bool { return this->v > o.v; }

    /**
     * @brief Greater Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator>(CType value) const noexcept -> bool { return this->v > value; }

    __CDS_NoDiscard constexpr friend auto operator > (CType value, Long const & o) noexcept -> bool { return value > o.v; }

    /**
     * @brief Less Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less than right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator<(Long const &o) const noexcept -> bool { return this->v < o.v; }

    /**
     * @brief Less Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less than right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator<(CType value) const noexcept -> bool { return this->v < value; }

    __CDS_NoDiscard constexpr friend auto operator < (CType value, Long const & o) noexcept -> bool { return value < o.v; }

    /**
     * @brief Greater or Equals Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater or equals that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator>=(Long const &o) const noexcept -> bool { return this->v >= o.v; }

    /**
     * @brief Greater or Equals Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater or equals that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    __CDS_NoDiscard constexpr auto operator>=(CType value) const noexcept -> bool { return this->v >= value; }

    __CDS_NoDiscard constexpr friend auto operator >= (CType value, Long const & o) noexcept -> bool { return value >= o.v; }

    /**
     * @brief Less or Equals Comparison Operator
     *
     * @param o : Long cref = Constant Reference to an Long Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less or equals that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    constexpr auto operator<=(Long const &o) const noexcept -> bool { return this->v <= o.v; }

    /**
     * @brief Less or Equals Comparison Operator
     *
     * @param value : CType = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less or equals that right's, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operators
     */
    constexpr auto operator<=(CType value) const noexcept -> bool { return this->v <= value; }

    constexpr friend auto operator <= (CType value, Long const & o) noexcept -> bool { return value <= o.v; }

#if __CDS_cpplang_ThreeWayComparison_Available == true

    constexpr auto operator <=> (Long const & o) const noexcept -> std::strong_ordering { return this->v <=> o.v; }

    constexpr auto operator <=> (CType value) const noexcept -> std::strong_ordering { return this->v <=> value; }

    constexpr friend auto operator <=> (CType value, Long const & o) noexcept -> std::strong_ordering { return value <=> o.v; }

#endif

    /**
     * @brief Bitwise And Operator
     *
     * @param o : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator&(Long const &o) const noexcept -> Long { return this->v & o.v; }

    /**
     * @brief Bitwise And Operator
     *
     * @param value : CType = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator&(CType value) const noexcept -> Long { return this->v & value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator & (CType value, Long const & o) noexcept -> Long { return value & o.v; }

    /**
     * @brief Bitwise Or Operator
     *
     * @param o : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator|(Long const &o) const noexcept -> Long { return this->v | o.v; }

    /**
     * @brief Bitwise Or Operator
     *
     * @param value : CType = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator|(CType value) const noexcept -> Long { return this->v | value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator | (CType value, Long const & o) noexcept -> Long { return value | o.v; }

    /**
     * @brief Bitwise Xor Operator
     *
     * @param o : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator^(Long const &o) const noexcept -> Long { return this->v ^ o.v; }

    /**
     * @brief Bitwise Xor Operator
     *
     * @param value : CType = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator^(CType value) const noexcept -> Long { return this->v ^ value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator ^ (CType value, Long const & o) noexcept -> Long { return value ^ o.v; }

    /**
     * @brief Bitwise Left Shift Operator
     *
     * @param o : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator<<(Long const &o) const noexcept -> Long { return this->v << o.v; }

    /**
     * @brief Bitwise Left Shift Operator
     *
     * @param value : CType = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator<<(CType value) const noexcept -> Long { return this->v << value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator << (CType value, Long const & o) noexcept -> Long { return value << o.v; }

    /**
     * @brief Bitwise Right Shift Operator
     *
     * @param o : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator>>(Long const &o) const noexcept -> Long { return this->v >> o.v; }

    /**
     * @brief Bitwise Right Shift Operator
     *
     * @param value : CType = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator>>(CType value) const noexcept -> Long { return this->v >> value; }

    __CDS_cpplang_ConstexprDestructor friend auto operator >> (CType value, Long const & o) noexcept -> Long { return value >> o.v; }

    /**
     * @brief Bitwise Not Operator
     *
     * @exceptsafe
     *
     * @returns Long = new Object containing the resulted value
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator~() const noexcept -> Long {return ~this->v;}

    /**
     * @brief Bitwise And Accumulator Operator
     *
     * @param o : Long cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Long const &o) noexcept -> Long & {
        this->v &= o.v;
        return *this;
    }

    /**
     * @brief Bitwise And Accumulator Operator
     *
     * @param value : CType = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(CType value) noexcept -> Long & {
        this->v &= value;
        return *this;
    }

    /**
     * @brief Bitwise Or Accumulator Operator
     *
     * @param o : Long cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Long const &o) noexcept -> Long & {
        this->v |= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Or Accumulator Operator
     *
     * @param value : CType = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(CType value) noexcept -> Long & {
        this->v |= value;
        return *this;
    }

    /**
     * @brief Bitwise Xor Accumulator Operator
     *
     * @param o : Long cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Long const &o) noexcept -> Long & {
        this->v ^= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Xor Accumulator Operator
     *
     * @param value : CType = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(CType value) noexcept -> Long & {
        this->v ^= value;
        return *this;
    }

    /**
     * @brief Bitwise Left Shift Accumulator Operator
     *
     * @param o : Long cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Long const &o) noexcept -> Long & {
        this->v <<= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Left Shift Accumulator Operator
     *
     * @param value : CType = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(CType value) noexcept -> Long & {
        this->v <<= value;
        return *this;
    }

    /**
     * @brief Bitwise Right Shift Accumulator Operator
     *
     * @param o : Long cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Long const &o) noexcept -> Long & {
        this->v >>= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Right Shift Accumulator Operator
     *
     * @param value : CType = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Long ref = Reference to the modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(CType value) noexcept -> Long & {
        this->v >>= value;
        return *this;
    }

    /**
     * @brief Conversion specification used to acquire contained value
     *
     * @exceptsafe
     *
     * @returns CType = Contained Value
     *
     * @test Tested in primitive/LongTest
     */
    constexpr operator CType() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)

    constexpr explicit operator int () const noexcept { return static_cast < int > ( this->v ); }

    /**
     * @brief Equality Function used in Object comparisons
     *
     * @param o : Object cref = Constant Reference to a CDS Object derived Instance
     *
     * @exceptsafe
     *
     * @returns bool = true if objects are same or of same type and value, false otherwise
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    /**
     * @brief Prefix Increment Operator
     *
     * @exceptsafe
     *
     * @return Long ref = Reference to modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Long & { this->v++; return * this; }

    /**
     * @brief Postfix Increment Operator
     *
     * @param CType = dummy parameter to separate prefix and postfix operators
     *
     * @exceptsafe
     *
     * @return Long = new Long Object containing value pre-increment
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Long { auto c = * this; this->v++; return c; }

    /**
     * @brief Prefix Decrement Operator
     *
     * @exceptsafe
     *
     * @return Long ref = Reference to modified Object
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Long & { this->v--; return * this; }

    /**
     * @brief Postfix Decrement Operator
     *
     * @param int = dummy parameter to separate prefix and postfix operators
     *
     * @exceptsafe
     *
     * @return Long = new Long Object containing value pre-decrement
     *
     * @test Tested in primitive/LongTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Long { auto c = * this; this->v--; return c; }

    /**
     * @brief Explicit Conversion to Literal Function
     *
     * @exceptsafe
     *
     * @returns int = value contained
     *
     * @test Tested in primitive/LongTest
     */
    __CDS_NoDiscard constexpr auto get() const noexcept -> CType { return this->v; }
public:

    /**
     * @brief Function used to obtain the hash value of the Object
     *
     * @exceptsafe
     *
     * @return Index = Hash Value
     *
     * @test Not Applicable
     */
    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash() const noexcept -> Index override {
        return static_cast<Index>(this->v);
    }

    /**
     * @brief Function used to obtain the String representation of the Long Object
     *
     * @exceptsafe
     *
     * @returns String = String representation
     *
     * @test Tested in primitive/LongTest
     */
    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    /**
     * @brief Function used to obtain an Long value from a String
     *
     * @param string : String cref = Constant Reference to a String
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Long = value extracted from String
     *
     * @test Tested in primitive/LongTest/Utility
     */
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

        CType numericValue = 0;

        while ( isNumericChar ( it.value() ) && it != string.end() ) {
            numericValue = numericValue * 10 + numericCharToInt ( it.value() );
            it.next();
        }

        return negative ? (-numericValue) : numericValue;
    }

    __CDS_NoDiscard auto copy () const noexcept -> Long * override {
        return new Long( * this );
    }

    /**
     * @brief Thread Safe, Atomic container for Long Type
     */
    class Atomic;
};

#include <CDS/Atomic>
namespace __CDS_HiddenUtility { // NOLINT(bugprone-reserved-identifier)
    using _AtomicBaseLong = Atomic<Long>; // NOLINT(bugprone-reserved-identifier)
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

class Long::Atomic : public __CDS_HiddenUtility::_AtomicBaseLong { // NOLINT(bugprone-reserved-identifier)
public:

    /**
     * @brief Default Constructor
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/LongTest/Atomic Tests
     */
    Atomic () noexcept {
        this->set(0);
    }

    /**
     * @brief Copy Constructor
     *
     * @param obj : Atomic cref = Constant Reference to an Atomic < Long > Object
     *
     * @excetptsafe
     * @threadsafe
     *
     * @test Tested in primitive/LongTest/Atomci Tests
     */
    Atomic ( Atomic const & obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseLong(obj) { } // NOLINT(modernize-use-equals-default)
    Atomic ( Atomic && obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseLong(obj) { } // NOLINT(performance-move-constructor-init)
    Atomic ( Long const & v ) noexcept : __CDS_HiddenUtility::_AtomicBaseLong(v) { } // NOLINT(google-explicit-constructor)

    Atomic (CType v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    auto operator ++ () noexcept -> Atomic & {
        this->_access.lock();
        ++this->_data;
        this->_access.unlock();

        return *this;
    }

    auto operator ++ (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        ++this->_data;
        this->_access.unlock();

        return copy;
    }

    auto operator -- () noexcept -> Atomic & {
        this->_access.lock();
        --this->_data;
        this->_access.unlock();

        return * this;
    }

    auto operator -- (int) noexcept -> Atomic {
        this->_access.lock();
        auto copy = this->_data;
        --this->_data;
        this->_access.unlock();

        return copy;
    }

    Atomic & operator = (CType value) noexcept {
        this->set(Long(value));
        return * this;
    }

    Atomic & operator = (Long const & obj) noexcept override {
        this->set(obj);
        return * this;
    }

    Atomic & operator = (Atomic const &) noexcept = default;
    Atomic & operator = (Atomic &&) noexcept = default;

    operator CType () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    operator Long () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Atomic const & o ) const noexcept -> bool {
        return this->get() == o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Atomic const & o ) const noexcept -> bool {
        return this->get() != o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Long const & o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Long const & o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator == ( CType o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator != ( CType o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Atomic const & o ) const noexcept -> bool {
        return this->get() > o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Atomic const & o ) const noexcept -> bool {
        return this->get() < o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Long const & o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Long const & o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator > ( CType o ) const noexcept -> bool {
        return this->get() > o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator < ( CType o ) const noexcept -> bool {
        return this->get() < o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Atomic const & o ) const noexcept -> bool {
        return this->get() >= o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Atomic const & o ) const noexcept -> bool {
        return this->get() <= o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Long const & o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Long const & o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( CType o ) const noexcept -> bool {
        return this->get() >= o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( CType o ) const noexcept -> bool {
        return this->get() <= o;
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (CType value, Atomic const & o) noexcept -> bool {
        return value == o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (Long const & value, Atomic const & o) noexcept -> bool {
        return value == o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (CType value, Atomic const & o) noexcept -> bool {
        return value != o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (Long const & value, Atomic const & o) noexcept -> bool {
        return value != o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (CType value, Atomic const & o) noexcept -> bool {
        return value >= o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (Long const & value, Atomic const & o) noexcept -> bool {
        return value >= o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (CType value, Atomic const & o) noexcept -> bool {
        return value <= o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (Long const & value, Atomic const & o) noexcept -> bool {
        return value <= o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (CType value, Atomic const & o) noexcept -> bool {
        return value > o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (Long const & value, Atomic const & o) noexcept -> bool {
        return value > o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (CType value, Atomic const & o) noexcept -> bool {
        return value < o.get();
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (Long const & value, Atomic const & o) noexcept -> bool {
        return value < o.get();
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & o ) const noexcept -> Long { return this->get() + o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Long const & o ) const noexcept -> Long { return this->get() + o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator + ( CType value ) const noexcept -> Long { return this->get() + value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( Long const & value, Atomic const & o ) noexcept -> Long { return value + o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( CType value, Atomic const & o ) noexcept -> Long { return value + o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & o ) const noexcept -> Long { return this->get() - o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Long const & o ) const noexcept -> Long { return this->get() - o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator - ( CType value ) const noexcept -> Long { return this->get() - value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( Long const & value, Atomic const & o ) noexcept -> Long { return value - o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( CType value, Atomic const & o ) noexcept -> Long { return value - o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & o ) const noexcept -> Long { return this->get() * o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Long const & o ) const noexcept -> Long { return this->get() * o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator * ( CType value ) const noexcept -> Long { return this->get() * value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( Long const & value, Atomic const & o ) noexcept -> Long { return value * o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( CType value, Atomic const & o ) noexcept -> Long { return value * o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & o ) const noexcept (false) -> Long {
        CType rValue = o.get(), lValue = this->get();
        if ( rValue == 0 ) throw DivideByZeroException();
        if ( rValue == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return lValue / rValue;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Long const & o ) const noexcept (false) -> Long {
        CType lValue = this->get();

        if ( o == (sint64)0 ) throw DivideByZeroException();
        if ( o == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return lValue / o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator / ( CType value ) const noexcept (false) -> Long {
        auto lValue = this->get();

        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return lValue / value;
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( Long const & value, Atomic const & o ) noexcept (false) -> Long {
        CType rVal = o.get();
        if ( rVal == 0 ) throw DivideByZeroException();
        if ( rVal == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return value / rVal;
    }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( CType value, Atomic const & o ) noexcept (false) -> Long {
        CType rVal = o.get();
        if ( rVal == 0 ) throw DivideByZeroException();
        if ( rVal == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        return value / rVal;
    }


    __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Atomic const & o ) const noexcept (false) -> Long {
        CType rValue = o.get(), lValue = this->get();
        if (rValue == 0 ) throw DivideByZeroException();
        if (rValue == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return lValue % rValue;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Long const & o ) const noexcept (false) -> Long {
        CType lValue = this->get();
        if ( o == (sint64)0 ) throw DivideByZeroException();
        if ( o == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return lValue % o;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto operator % ( CType rValue ) const noexcept (false) -> Long {
        CType lValue = this->get();
        if (rValue == 0 ) throw DivideByZeroException();
        if (rValue == Limits::S64_MIN || lValue == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return lValue % rValue;
    }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( Long const & value, Atomic const & o ) noexcept (false) -> Long {
        CType rVal = o.get();
        if ( rVal == 0 ) throw DivideByZeroException();
        if ( rVal == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return value % rVal;
    }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( CType value, Atomic const & o ) noexcept (false) -> Long {
        CType rVal = o.get();
        if ( rVal == 0 ) throw DivideByZeroException();
        if ( rVal == Limits::S64_MIN || value == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        return value % rVal;
    }


    __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Atomic const & o ) const noexcept -> Long { return this->get() & o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Long const & o ) const noexcept -> Long { return this->get() & o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator & ( CType value ) const noexcept -> Long { return this->get() & value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( Long const & value, Atomic const & o ) noexcept -> Long { return value & o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( CType value, Atomic const & o ) noexcept -> Long { return value & o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Atomic const & o ) const noexcept -> Long { return this->get() | o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Long const & o ) const noexcept -> Long { return this->get() | o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator | ( CType value ) const noexcept -> Long { return this->get() | value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( Long const & value, Atomic const & o ) noexcept -> Long { return value | o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( CType value, Atomic const & o ) noexcept -> Long { return value | o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Atomic const & o ) const noexcept -> Long { return this->get() ^ o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Long const & o ) const noexcept -> Long { return this->get() ^ o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( CType value ) const noexcept -> Long { return this->get() ^ value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( Long const & value, Atomic const & o ) noexcept -> Long { return value ^ o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( CType value, Atomic const & o ) noexcept -> Long { return value ^ o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Atomic const & o ) const noexcept -> Long { return this->get() << o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Long const & o ) const noexcept -> Long { return this->get() << o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator << ( CType value ) const noexcept -> Long { return this->get() << value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( Long const & value, Atomic const & o ) noexcept -> Long { return value << o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( CType value, Atomic const & o ) noexcept -> Long { return value << o.get(); }


    __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Atomic const & o ) const noexcept -> Long { return this->get() >> o.get(); }
    __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Long const & o ) const noexcept -> Long { return this->get() >> o; }
    __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( CType value ) const noexcept -> Long { return this->get() >> value; }

    __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( Long const & value, Atomic const & o ) noexcept -> Long { return value >> o.get(); }
    __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( CType value, Atomic const & o ) noexcept -> Long { return value >> o.get(); }

    __CDS_NoDiscard __CDS_OptimalInline auto hash () const noexcept -> Index override {
        return this->get().hash();
    }

    __CDS_OptionalInline auto operator += (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (CType value) noexcept (false) -> Atomic & {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator %= (CType value) noexcept (false) -> Atomic & {
        if ( value == 0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        this->_data %= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator &= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data &= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator |= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data |= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator ^= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data ^= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator >>= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data >>= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator <<= (CType value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data <<= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data += value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data -= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data *= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Long const & value) noexcept (false) -> Atomic & {
        if ( value == (sint64)0 ) throw DivideByZeroException();
        if ( value == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        this->_data /= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator %= (Long const & value) noexcept (false) -> Atomic & {
        if ( value == (sint64)0 ) throw DivideByZeroException();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        if ( value == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();
        this->_data %= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator &= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data &= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator |= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data |= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator ^= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data ^= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator >>= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data >>= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator <<= (Long const & value) noexcept -> Atomic & {
        this->_access.lock();
        this->_data <<= value;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator += (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data += rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator -= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data -= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator *= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data *= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator /= (Atomic const & value) noexcept (false) -> Atomic & {
        auto rValue = value.get();
        if ( rValue == (sint64)0 ) throw DivideByZeroException();
        if ( rValue == Limits::S64_MIN ) throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        this->_data /= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator %= (Atomic const & value) noexcept (false) -> Atomic & {
        auto rValue = value.get();
        if ( rValue == (sint64)0 ) throw DivideByZeroException();
        if ( rValue == Limits::S64_MIN ) throw ArithmeticException ("Modulo by Limits::S64_MIN is undefined behaviour");

        this->_access.lock();

        if ( this->_data == Limits::S64_MIN ) {
            this->_access.unlock();
            throw ArithmeticException ("Division by Limits::S64_MIN is undefined behaviour");
        }

        this->_data %= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator &= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data &= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator |= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data |= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator ^= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data ^= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator >>= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data >>= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_OptionalInline auto operator <<= (Atomic const & value) noexcept -> Atomic & {
        auto rValue = value.get();

        this->_access.lock();
        this->_data <<= rValue;
        this->_access.unlock();
        return * this;
    }

    __CDS_NoDiscard __CDS_OptionalInline auto operator ~ () const noexcept -> Long {
        return this->get().operator~();
    }

};

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#if defined(CDS_INTEGER_POSTFIX)

__CDS_cpplang_ConstexprDestructor auto operator "" _l (unsigned long long int value) noexcept -> Long {
    return static_cast < long long int > (value);
}

#endif

__CDS_RegisterParseType(Long)

#endif //CDS_LONG_HPP
