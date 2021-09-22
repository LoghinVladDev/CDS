//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/Pointer>

/**
 * @class Object Derived container for a Boolean Value
 *
 * @test Test in primitive/IntegerTest
 */
class Integer : public Object {
private:

    /**
     * @brief wrapped integer value
     */
    int v{0};
public:

    /**
     * @brief Alias for Pseudo-Random Number Generator Type
     */
    using RandomGenerator = Random::Int;

    /**
     * @brief Function used to obtain a random Integer value from a Pseudo-Random Number Generator created at first call
     *  that ranges values in [INT32_MIN, INT32_MAX]
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing randomly generated integer value
     *
     * @test Tested in primitive/IntegerTest/Random Tests
     */
    static auto random () noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if (pRng.isNull()) pRng.reset(new RandomGenerator());

        return pRng->get();
    }

    /**
     * @brief Function used to obtain a random Integer value between two points from a Pseudo-Random Number Generator created at first call with given parameters
     * If parameters differ from last call, a new Pseudo-Random Generator is created
     *
     * @param low : int = low value of the interval of values
     * @param high : int = high value of the interval of values
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing randomly generated integer value
     *
     * @test Tested in primitive/IntegerTest/Random Tests
     */
    static auto random (int low, int high) noexcept -> Integer {
        static UniquePointer < RandomGenerator > pRng;
        if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) pRng.reset(new RandomGenerator(low, high));

        return pRng->get();
    }

    /**
     * @brief Default Constructor. Creates an Integer containing the value 0
     *
     * @exceptsafe
     *
     * @test Tested in primitive/IntegerTest/Constructor Tests
     */
    constexpr Integer() noexcept = default;

    /**
     * @brief Copy Constructor
     *
     * @param obj : Integer cref = Constant Reference to an Integer Object to copy value from
     *
     * @exceptsafe
     *
     * @test Tested in primitive/IntegerTest/Constructor Tests
     */
    constexpr Integer(Integer const&)noexcept = default;

    /**
     * @brief Move Constructor
     *
     * @param obj : Integer mref = Move Reference to an Integer Object to move value from
     *
     * @exceptsafe
     *
     * @test Tested in primitive/IntegerTest/Constructor Tests
     */
    constexpr Integer(Integer &&)noexcept = default;

    /**
     * @brief Destructor
     *
     * @exceptsafe
     *
     * @test Not Applicable
     */
    __CDS_cpplang_ConstexprDestructor ~Integer () noexcept override = default;

    /**
     * @brief Constructor from literal integer value
     *
     * @param value : int = value to assign to integer
     *
     * @exceptsafe
     *
     * @test Tested in primitive/IntegerTest/Constructor Tests
     */
    constexpr Integer(int value) noexcept: v(value) {} // NOLINT(google-explicit-constructor)

    /**
     * @brief Assignment Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to assign value from
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Constructor Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Integer const &o) noexcept -> Integer & {
        if (this == &o)return *this;
        this->v = o.v;
        return *this;
    }

    /**
     * @brief Assignment Operator
     *
     * @param value : int = int value to assign
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Constructor Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(int value) noexcept -> Integer & {
        this->v = value;
        return *this;
    }

    /**
     * @brief Sum Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to sum with caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing sum of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+(Integer const &o) const noexcept -> Integer { return this->v + o.v; }

    /**
     * @brief Sum Operator
     *
     * @param value : int = int value to sum with caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing sum of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+(int value) const noexcept -> Integer { return this->v + value; }

    /**
     * @brief Difference Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to subtract from caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing difference of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator-(Integer const &o) const noexcept -> Integer { return this->v - o.v; }

    /**
     * @brief Difference Operator
     *
     * @param value : int = int value to subtract from caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing difference of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator-(int value) const noexcept -> Integer { return this->v - value; }

    /**
     * @brief Multiply Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to multiply from caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing multiplication of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator*(Integer const &o) const noexcept -> Integer { return this->v * o.v; }

    /**
     * @brief Multiply Operator
     *
     * @param value : int = int value to multiply with caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing multiplication of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator*(int value) const noexcept -> Integer { return this->v * value; }

    /**
     * @brief Division Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to divide caller Object with
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing division of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator/(Integer const &o) const noexcept -> Integer { return this->v / o.v; }

    /**
     * @brief Division Operator
     *
     * @param value : int = int value to divide caller Object with
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing division of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator/(int value) const noexcept -> Integer { return this->v / value; }

    /**
     * @brief Modulo Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to obtain remainder from caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing remainder of division of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator%(Integer const &o) const noexcept -> Integer { return this->v % o.v; }

    /**
     * @brief Modulo Operator
     *
     * @param value : int = int value to obtain remainder from caller Object
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing remainder of division of operands
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator%(int value) const noexcept -> Integer { return this->v % value; }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Integer cref = Constant Reference to Integer Object to sum into left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator+=(Integer const &o) noexcept -> Integer & {
        this->v += o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : int = value to sum into left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator+=(int value) noexcept -> Integer & {
        this->v += value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Integer cref = Constant Reference to Integer Object to subtract into left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Integer const &o) noexcept -> Integer & {
        this->v -= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : int = value to subtract into left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(int value) noexcept -> Integer & {
        this->v -= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Integer cref = Constant Reference to Integer Object to multiply with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Integer const &o) noexcept -> Integer & {
        this->v *= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : int = value to multiply with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(int value) noexcept -> Integer & {
        this->v *= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Integer cref = Constant Reference to Integer Object to divide with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Integer const &o) noexcept -> Integer & {
        this->v /= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : int = value to divide with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(int value) noexcept -> Integer & {
        this->v /= value;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param o : Integer cref = Constant Reference to Integer Object to apply modulo with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Integer const &o) noexcept -> Integer & {
        this->v %= o.v;
        return *this;
    }

    /**
     * @brief Sum Accumulate Operator
     *
     * @param value : int = value to apply modulo with left, caller object
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to modified object
     *
     * @test Tested in primitive/Integer/Algebraic Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(int value) noexcept -> Integer & {
        this->v %= value;
        return *this;
    }

    /**
     * @brief Equality Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects have same value, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator==(Integer const &o) const noexcept -> bool { return this->v == o.v; }

    /**
     * @brief Equality Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects have same value, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator==(int value) const noexcept -> bool { return this->v == value; }

    /**
     * @brief Difference Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects do not have same value, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator!=(Integer const &o) const noexcept -> bool { return this->v != o.v; }

    /**
     * @brief Difference Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects do not have same value, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator!=(int value) const noexcept -> bool { return this->v != value; }

    /**
     * @brief Greater Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator>(Integer const &o) const noexcept -> bool { return this->v > o.v; }

    /**
     * @brief Greater Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator>(int value) const noexcept -> bool { return this->v > value; }

    /**
     * @brief Less Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less than right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator<(Integer const &o) const noexcept -> bool { return this->v < o.v; }

    /**
     * @brief Less Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less than right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator<(int value) const noexcept -> bool { return this->v < value; }

    /**
     * @brief Greater or Equals Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater or equals that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator>=(Integer const &o) const noexcept -> bool { return this->v >= o.v; }

    /**
     * @brief Greater or Equals Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is greater or equals that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator>=(int value) const noexcept -> bool { return this->v >= value; }

    /**
     * @brief Less or Equals Comparison Operator
     *
     * @param o : Integer cref = Constant Reference to an Integer Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less or equals that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator<=(Integer const &o) const noexcept -> bool { return this->v <= o.v; }

    /**
     * @brief Less or Equals Comparison Operator
     *
     * @param value : int = value to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if left's value is less or equals that right's, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operators
     */
    constexpr auto operator<=(int value) const noexcept -> bool { return this->v <= value; }

    /**
     * @brief Bitwise And Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator&(Integer const &o) const noexcept -> Integer { return this->v & o.v; }

    /**
     * @brief Bitwise And Operator
     *
     * @param value : int = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator&(int value) const noexcept -> Integer { return this->v & value; }

    /**
     * @brief Bitwise Or Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator|(Integer const &o) const noexcept -> Integer { return this->v | o.v; }

    /**
     * @brief Bitwise Or Operator
     *
     * @param value : int = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator|(int value) const noexcept -> Integer { return this->v | value; }

    /**
     * @brief Bitwise Xor Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator^(Integer const &o) const noexcept -> Integer { return this->v ^ o.v; }

    /**
     * @brief Bitwise Xor Operator
     *
     * @param value : int = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator^(int value) const noexcept -> Integer { return this->v ^ value; }

    /**
     * @brief Bitwise Left Shift Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator<<(Integer const &o) const noexcept -> Integer { return this->v << o.v; }

    /**
     * @brief Bitwise Left Shift Operator
     *
     * @param value : int = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator<<(int value) const noexcept -> Integer { return this->v << value; }

    /**
     * @brief Bitwise Right Shift Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator>>(Integer const &o) const noexcept -> Integer { return this->v >> o.v; }

    /**
     * @brief Bitwise Right Shift Operator
     *
     * @param value : int = value to use in the bitwise operation as right hand operand
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator>>(int value) const noexcept -> Integer { return this->v >> value; }

    /**
     * @brief Bitwise Not Operator
     *
     * @exceptsafe
     *
     * @returns Integer = new Object containing the resulted value
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator~() const noexcept -> Integer {return ~this->v;}

    /**
     * @brief Bitwise And Accumulator Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Integer const &o) noexcept -> Integer & {
        this->v &= o.v;
        return *this;
    }

    /**
     * @brief Bitwise And Accumulator Operator
     *
     * @param value : int = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(int value) noexcept -> Integer & {
        this->v &= value;
        return *this;
    }

    /**
     * @brief Bitwise Or Accumulator Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Integer const &o) noexcept -> Integer & {
        this->v |= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Or Accumulator Operator
     *
     * @param value : int = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(int value) noexcept -> Integer & {
        this->v |= value;
        return *this;
    }

    /**
     * @brief Bitwise Xor Accumulator Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Integer const &o) noexcept -> Integer & {
        this->v ^= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Xor Accumulator Operator
     *
     * @param value : int = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(int value) noexcept -> Integer & {
        this->v ^= value;
        return *this;
    }

    /**
     * @brief Bitwise Left Shift Accumulator Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Integer const &o) noexcept -> Integer & {
        this->v <<= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Left Shift Accumulator Operator
     *
     * @param value : int = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(int value) noexcept -> Integer & {
        this->v <<= value;
        return *this;
    }

    /**
     * @brief Bitwise Right Shift Accumulator Operator
     *
     * @param o : Integer cref = Constant Reference to the Object to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Integer const &o) noexcept -> Integer & {
        this->v >>= o.v;
        return *this;
    }

    /**
     * @brief Bitwise Right Shift Accumulator Operator
     *
     * @param value : int = value to accumulate to the caller
     *
     * @exceptsafe
     *
     * @returns Integer ref = Reference to the modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(int value) noexcept -> Integer & {
        this->v >>= value;
        return *this;
    }

    /**
     * @brief Conversion specification used to acquire contained value
     *
     * @exceptsafe
     *
     * @returns int = Contained Value
     *
     * @test Tested in primitive/IntegerTest
     */
    constexpr operator int() const noexcept { return this->v; } // NOLINT(google-explicit-constructor)

    /**
     * @brief Equality Function used in Object comparisons
     *
     * @param o : Object cref = Constant Reference to a CDS Object derived Instance
     *
     * @exceptsafe
     *
     * @returns bool = true if objects are same or of same type and value, false otherwise
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
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
     * @return Integer ref = Reference to modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Integer & { this->v++; return * this; }

    /**
     * @brief Postfix Increment Operator
     *
     * @param int = dummy parameter to separate prefix and postfix operators
     *
     * @exceptsafe
     *
     * @return Integer = new Integer Object containing value pre-increment
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Integer { auto c = * this; this->v++; return c; }

    /**
     * @brief Prefix Decrement Operator
     *
     * @exceptsafe
     *
     * @return Integer ref = Reference to modified Object
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Integer & { this->v--; return * this; }

    /**
     * @brief Postfix Decrement Operator
     *
     * @param int = dummy parameter to separate prefix and postfix operators
     *
     * @exceptsafe
     *
     * @return Integer = new Integer Object containing value pre-decrement
     *
     * @test Tested in primitive/IntegerTest/Relational Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Integer { auto c = * this; this->v--; return c; }

    /**
     * @brief Explicit Conversion to Literal Function
     *
     * @exceptsafe
     *
     * @returns int = value contained
     *
     * @test Tested in primitive/IntegerTest
     */
    __CDS_NoDiscard constexpr inline auto get() const noexcept -> int { return this->v; }
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
     * @brief Function used to obtain the String representation of the Integer Object
     *
     * @exceptsafe
     *
     * @returns String = String representation
     *
     * @test Tested in primitive/IntegerTest
     */
    __CDS_NoDiscard auto toString() const noexcept -> String override {
        return String().append(this->v);
    }

    /**
     * @brief Function used to obtain an Integer value from a String
     *
     * @param string : String cref = Constant Reference to a String
     *
     * @static
     *
     * @exceptsafe
     *
     * @returns Integer = value extracted from String
     *
     * @test Tested in primitive/IntegerTest/Utility
     */
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

    /**
     * @brief Thread Safe, Atomic container for Integer Type
     */
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

    operator Integer () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get();
    }

    __CDS_NoDiscard inline auto operator == ( Atomic const & o ) const noexcept -> bool {
        return this->get() == o.get();
    }

    __CDS_NoDiscard inline auto operator != ( Atomic const & o ) const noexcept -> bool {
        return this->get() != o.get();
    }

    __CDS_NoDiscard inline auto operator == ( Integer const & o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard inline auto operator != ( Integer const & o ) const noexcept -> bool {
        return this->get() != o;
    }

    __CDS_NoDiscard inline auto operator == ( int o ) const noexcept -> bool {
        return this->get() == o;
    }

    __CDS_NoDiscard inline auto operator != ( int o ) const noexcept -> bool {
        return this->get() != o;
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

#if defined(CDS_INTEGER_POSTFIX)

__CDS_cpplang_ConstexprDestructor auto operator "" _i (unsigned long long int value) noexcept -> Integer {
    return static_cast < int > (value);
}

#endif

#endif //CDS_INTEGER_HPP
