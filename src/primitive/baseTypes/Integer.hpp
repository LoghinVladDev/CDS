//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_INTEGER_HPP
#define CDS_INTEGER_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/Utility>
#include <CDS/Range>
#include <CDS/Memory>

namespace cds {

    /**
     * @class Object Derived container for an Integer Value
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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto rangeTo (Integer const & value) const noexcept -> Range {
            return Range(this->v, value.v);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto rangeTo (int value) const noexcept -> Range {
            return Range(this->v, value);
        }

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
        __CDS_MaybeUnused static auto random () noexcept -> Integer {
            static UniquePointer < RandomGenerator > pRng;
            if (pRng.isNull()) {
                pRng.reset(Memory :: instance() .create < RandomGenerator > ());
            }

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
            if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) {
                pRng.reset(Memory :: instance() .create < RandomGenerator > (low, high));
            }

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
        constexpr Integer(Integer &&) noexcept = default;

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
        constexpr Integer(sint32 value) noexcept: v(value) {} // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)

        explicit constexpr Integer(sint8 value) noexcept: v(value) {}
        explicit constexpr Integer(sint16 value) noexcept: v(value) {}
        explicit constexpr Integer(sint64 value) noexcept: v(static_cast < int > ( value )) {}
        explicit constexpr Integer(uint8 value) noexcept: v(static_cast < int > ( value )) {}
        explicit constexpr Integer(uint32 value) noexcept: v(static_cast < int > ( value )) {}
        explicit constexpr Integer(uint64 value) noexcept: v(static_cast < int > ( value )) {}

        explicit constexpr Integer(float value) noexcept: v(static_cast < int > ( value )) {}
        explicit constexpr Integer(double value) noexcept: v(static_cast < int > ( value )) {}

        /**
         * @brief Assignment Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to assign value from
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Constructor Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Integer const &integer) noexcept -> Integer & {
            if (this == &integer) {
                return *this;
            }

            this->v = integer.v;
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

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Integer && value) noexcept -> Integer & {
            if (this == & value) {
                return *this;
            }

            this->v = exchange ( value.v, 0 );
            return *this;
        }

        /**
         * @brief Sum Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to sum with caller Object
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing sum of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator+(Integer const &integer) const noexcept -> Integer { return this->v + integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator+ (int value, Integer const & integer) noexcept -> Integer { return value + integer.v; }

        /**
         * @brief Difference Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to subtract from caller Object
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing difference of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator-(Integer const &integer) const noexcept -> Integer { return this->v - integer.v; }

        __CDS_cpplang_ConstexprDestructor friend auto operator - (int value, Integer const & integer) noexcept -> Integer { return value - integer.v; }

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
         * @param integer : Integer cref = Constant Reference to an Integer Object to multiply from caller Object
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing multiplication of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator*(Integer const &integer) const noexcept -> Integer { return this->v * integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator * (int value, Integer const & integer) noexcept -> Integer { return value * integer.v; }

        /**
         * @brief Division Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to divide caller Object with
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer = new Object containing division of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator/(Integer const &integer) const noexcept (false) -> Integer {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return this->v / integer.v;
        }

        friend auto operator / (int value, Integer const & integer) noexcept (false) -> Integer {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return value / integer.v;
        }

        /**
         * @brief Division Operator
         *
         * @param value : int = int value to divide caller Object with
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer = new Object containing division of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator / (int value) const noexcept (false) -> Integer {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return this->v / value;
        }

        /**
         * @brief Modulo Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to obtain remainder from caller Object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer = new Object containing remainder of division of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator % (Integer const &integer) const noexcept (false) -> Integer {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return this->v % integer.v;
        }

        /**
         * @brief Modulo Operator
         *
         * @param value : int = int value to obtain remainder from caller Object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer = new Object containing remainder of division of operands
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator % (int value) const noexcept (false) -> Integer {
            if ( value == 0) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return this->v % value;
        }

        __CDS_cpplang_ConstexprDestructor friend auto operator % (int value, Integer const & integer) noexcept (false) -> Integer {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return value % integer.v;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param integer : Integer cref = Constant Reference to Integer Object to sum into left, caller object
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator+=(Integer const &integer) noexcept -> Integer & {
            this->v += integer.v;
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
         * @param integer : Integer cref = Constant Reference to Integer Object to subtract into left, caller object
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Integer const &integer) noexcept -> Integer & {
            this->v -= integer.v;
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
         * @param integer : Integer cref = Constant Reference to Integer Object to multiply with left, caller object
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Integer const &integer) noexcept -> Integer & {
            this->v *= integer.v;
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
         * @param integer : Integer cref = Constant Reference to Integer Object to divide with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Integer const &integer) noexcept (false) -> Integer & {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->v /= integer.v;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param value : int = value to divide with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(int value) noexcept (false) -> Integer & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->v /= value;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param integer : Integer cref = Constant Reference to Integer Object to apply modulo with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Integer const &integer) noexcept (false) -> Integer & {
            if (integer.v == 0 ) {
                throw DivideByZeroException();
            }

            if (integer.v == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            this->v %= integer.v;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param value : int = value to apply modulo with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is INT32_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Integer ref = Reference to modified object
         *
         * @test Tested in primitive/Integer/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(int value) noexcept (false) -> Integer & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN || this->v == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            this->v %= value;
            return *this;
        }

        /**
         * @brief Equality Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects have same value, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator==(Integer const &integer) const noexcept -> bool { return this->v == integer.v; }

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
        __CDS_NoDiscard constexpr auto operator==(int value) const noexcept -> bool { return this->v == value; }

        __CDS_NoDiscard constexpr friend auto operator == (int value, Integer const & integer) noexcept -> bool { return value == integer.v; }

        /**
         * @brief Difference Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects do not have same value, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator!=(Integer const &integer) const noexcept -> bool { return this->v != integer.v; }

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
        __CDS_NoDiscard constexpr auto operator!=(int value) const noexcept -> bool { return this->v != value; }

        __CDS_NoDiscard constexpr friend auto operator != (int value, Integer const & integer) noexcept -> bool { return value != integer.v; }

        /**
         * @brief Greater Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is greater that right's, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator>(Integer const &integer) const noexcept -> bool { return this->v > integer.v; }

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
        __CDS_NoDiscard constexpr auto operator>(int value) const noexcept -> bool { return this->v > value; }

        __CDS_NoDiscard constexpr friend auto operator > (int value, Integer const & integer) noexcept -> bool { return value > integer.v; }

        /**
         * @brief Less Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is less than right's, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator<(Integer const &integer) const noexcept -> bool { return this->v < integer.v; }

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
        __CDS_NoDiscard constexpr auto operator<(int value) const noexcept -> bool { return this->v < value; }

        __CDS_NoDiscard constexpr friend auto operator < (int value, Integer const & integer) noexcept -> bool { return value < integer.v; }

        /**
         * @brief Greater or Equals Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is greater or equals that right's, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator>=(Integer const &integer) const noexcept -> bool { return this->v >= integer.v; }

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
        __CDS_NoDiscard constexpr auto operator>=(int value) const noexcept -> bool { return this->v >= value; }

        __CDS_NoDiscard constexpr friend auto operator >= (int value, Integer const & integer) noexcept -> bool { return value >= integer.v; }

        /**
         * @brief Less or Equals Comparison Operator
         *
         * @param integer : Integer cref = Constant Reference to an Integer Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is less or equals that right's, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operators
         */
        constexpr auto operator<=(Integer const &integer) const noexcept -> bool { return this->v <= integer.v; }

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

        constexpr friend auto operator <= (int value, Integer const & integer) noexcept -> bool { return value <= integer.v; }

    #if __CDS_cpplang_ThreeWayComparison_available == true

        constexpr auto operator <=> (Integer const & integer) const noexcept -> std::strong_ordering { return this->v <=> integer.v; }

        constexpr auto operator <=> (int value) const noexcept -> std::strong_ordering { return this->v <=> value; }

        constexpr friend auto operator <=> (int value, Integer const & integer) noexcept -> std::strong_ordering { return value <=> integer.v; }

    #endif

        /**
         * @brief Bitwise And Operator
         *
         * @param integer : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing the resulted value
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator&(Integer const &integer) const noexcept -> Integer { return this->v & integer.v; } // NOLINT(clion-misra-cpp2008-5-3-3)

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
        __CDS_cpplang_ConstexprDestructor auto operator&(int value) const noexcept -> Integer { return this->v & value; } // NOLINT(clion-misra-cpp2008-5-3-3)

        __CDS_cpplang_ConstexprDestructor friend auto operator & (int value, Integer const & integer) noexcept -> Integer { return value & integer.v; } // NOLINT(clion-misra-cpp2008-5-3-3)

        /**
         * @brief Bitwise Or Operator
         *
         * @param integer : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing the resulted value
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator|(Integer const &integer) const noexcept -> Integer { return this->v | integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator | (int value, Integer const & integer) noexcept -> Integer { return value | integer.v; }

        /**
         * @brief Bitwise Xor Operator
         *
         * @param integer : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing the resulted value
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator^(Integer const &integer) const noexcept -> Integer { return this->v ^ integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator ^ (int value, Integer const & integer) noexcept -> Integer { return value ^ integer.v; }

        /**
         * @brief Bitwise Left Shift Operator
         *
         * @param integer : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing the resulted value
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator<<(Integer const &integer) const noexcept -> Integer { return this->v << integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator << (int value, Integer const & integer) noexcept -> Integer { return value << integer.v; }

        /**
         * @brief Bitwise Right Shift Operator
         *
         * @param integer : Integer cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Integer = new Object containing the resulted value
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator>>(Integer const &integer) const noexcept -> Integer { return this->v >> integer.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator >> (int value, Integer const & integer) noexcept -> Integer { return value >> integer.v; }

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
         * @param integer : Integer cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to the modified Object
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Integer const &integer) noexcept -> Integer & {
            this->v &= integer.v;
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
         * @param integer : Integer cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to the modified Object
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Integer const &integer) noexcept -> Integer & {
            this->v |= integer.v;
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
         * @param integer : Integer cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to the modified Object
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Integer const &integer) noexcept -> Integer & {
            this->v ^= integer.v;
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
         * @param integer : Integer cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to the modified Object
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Integer const &integer) noexcept -> Integer & {
            this->v <<= integer.v;
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
         * @param integer : Integer cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Integer ref = Reference to the modified Object
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Integer const &integer) noexcept -> Integer & {
            this->v >>= integer.v;
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
         * @param object : Object cref = Constant Reference to a CDS Object derived Instance
         *
         * @exceptsafe
         *
         * @returns bool = true if objects are same or of same type and value, false otherwise
         *
         * @test Tested in primitive/IntegerTest/Relational Operator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pInteger = dynamic_cast < Integer const * > ( & object );
            if (pInteger == nullptr ) {
                return false;
            }

            return this->operator==(*pInteger);
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
        __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Integer { auto integer = * this; this->v++; return integer; }

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
        __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Integer { auto integer = * this; this->v--; return integer; }

        /**
         * @brief Explicit Conversion to Literal Function
         *
         * @exceptsafe
         *
         * @returns int = value contained
         *
         * @test Tested in primitive/IntegerTest
         */
        __CDS_NoDiscard constexpr auto get() const noexcept -> int { return this->v; }
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
            return :: cds :: hash(this->v);
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
        __CDS_NoDiscard __CDS_OptimalInline auto toString() const noexcept -> String override {
            return String(this->v); // NOLINT(modernize-return-braced-init-list)
        }

        __CDS_NoDiscard __CDS_OptimalInline auto toString(int base) const noexcept -> String {
            auto intValue = this->v;
            String rep;

            __CDS_cpplang_ConstexprLambda auto baseDigitToString = [](int value) noexcept -> char {
                if ( value < 10 ) {
                    return static_cast < char > (value + '0');
                }

                return static_cast < char > (value + 'a' - 10);
            };

            while (intValue > 0 ) {
                rep += baseDigitToString(intValue % base);
                intValue /= base;
            }

            return std :: move ( (rep + (this->v < 0 ? "-" : "")).reversed() );
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
        static auto parse(String const & string, int base = 10) noexcept -> Integer {
            if ( string.empty() ) {
                return 0;
            }

            bool negative = false;

            auto iterator = string.begin();
            __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char character) noexcept -> bool { return character >= '0' && character <= '9'; };
            __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char character) noexcept -> int {
                return static_cast < int > ( character ) - 48;
            };

            __CDS_cpplang_ConstexprLambda static auto isBaseNumericChar = [](int base, char character) noexcept -> bool {
                if ( base < 10 ) {
                    return character >= '0' && character < static_cast < char > ('0' + base);
                }

                return character >= '0' && character <= '9' || (character >= 'A' && character < 'A' + (base - 10) || character >= 'a' && character < 'a' + (base - 10));
            };

            __CDS_cpplang_ConstexprLambda static auto baseNumericCharToInt = [](char character) noexcept -> int {
                if (character >= '0' && character <= '9' ) {
                    return static_cast < int > ( character ) - '0';
                }

                if (character >= 'A' && character <= 'Z' ) {
                    return static_cast < int > ( character ) - 'A' + 10;
                }

                if (character >= 'a' && character <= 'z' ) {
                    return static_cast < int > ( character ) - 'a' + 10;
                }

                return static_cast<int>(character);
            };

            while(( base == 10 && ! isNumericChar (iterator.value() ) || ! isBaseNumericChar(base, iterator.value()) ) && iterator != string.end() ) {
                if (iterator.value() == '-' ) {
                    negative = true;
                }

                (void) iterator.next();
            }

            if ( base == 16 ) {
                auto copy = iterator;
                if ( copy.value() == '0' && copy.next().value() == 'x' ) {
                    iterator = copy.next();
                }
            }

            int numericValue = 0;

            while (( base == 10 && isNumericChar (iterator.value() ) || isBaseNumericChar(base, iterator.value() ) ) && iterator != string.end() ) {
                numericValue = numericValue * base + ((base == 10) ? numericCharToInt (iterator.value() ) : baseNumericCharToInt(iterator.value()));
                (void) iterator.next();
            }

            return negative ? (-numericValue) : numericValue;
        }

        /**
         * @brief Thread Safe, Atomic container for Integer Type
         */
        class Atomic; // NOLINT(cppcoreguidelines-virtual-class-destructor)

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceAtLeast ( Integer const & minimumValue ) const noexcept -> Integer {
            return minimumValue > * this ? minimumValue : * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceAtMost ( Integer const & maximumValue ) const noexcept -> Integer {
            return maximumValue < * this ? maximumValue : * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceAtLeast ( int minimumValue ) const noexcept -> Integer {
            return minimumValue > * this ? minimumValue : this->v;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceAtMost ( int maximumValue ) const noexcept -> Integer {
            return maximumValue < * this ? maximumValue : this->v;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceIn ( Integer const & minimumValue, Integer const & maximumValue ) const noexcept -> Integer { // NOLINT(bugprone-easily-swappable-parameters)
            if ( minimumValue > * this ) {
                return minimumValue;
            }

            if ( maximumValue < * this ) {
                return maximumValue;
            }

            return * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceIn ( Integer const & minimumValue, int maximumValue ) const noexcept -> Integer { // NOLINT(bugprone-easily-swappable-parameters)
            if ( minimumValue > * this ) {
                return minimumValue;
            }

            if ( maximumValue < * this ) {
                return maximumValue;
            }

            return * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceIn ( int minimumValue, Integer const & maximumValue ) const noexcept -> Integer { // NOLINT(bugprone-easily-swappable-parameters)
            if ( minimumValue > * this ) {
                return minimumValue;
            }

            if ( maximumValue < * this ) {
                return maximumValue;
            }

            return * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto coerceIn ( int minimumValue, int maximumValue ) const noexcept -> Integer { // NOLINT(bugprone-easily-swappable-parameters)
            if ( minimumValue > * this ) {
                return minimumValue;
            }

            if ( maximumValue < * this ) {
                return maximumValue;
            }

            return * this;
        }

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto isDigit () const noexcept -> bool { return this->v < 10 && this->v >= 0; }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto digitToChar () const noexcept (false) -> char {
            if ( ! this->isDigit() ) {
                throw IllegalArgumentException();
            }

            return static_cast < char > ( this->v ) + '0'; // NOLINT(cppcoreguidelines-narrowing-conversions)
        }

        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto static isEven (int value) noexcept -> bool {
            return value % 2 == 0;
        }
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto static isOdd (int value) noexcept -> bool { return value % 2 == 1; }
    };

}

#include <CDS/Atomic>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden {
            namespace integerAtomicImpl {

                using Base = Atomic<Integer>; // NOLINT(bugprone-reserved-identifier)

            }
        }
    }
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

namespace cds {

    class Integer::Atomic : public utility :: hidden :: integerAtomicImpl :: Base { // NOLINT(bugprone-reserved-identifier)
    public:

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         * @threadsafe
         *
         * @test Tested in primitive/IntegerTest/Atomic Tests
         */
        Atomic () noexcept {
            this->set(0);
        }

        /**
         * @brief Copy Constructor
         *
         * @param obj : Atomic cref = Constant Reference to an Atomic < Integer > Object
         *
         * @excetptsafe
         * @threadsafe
         *
         * @test Tested in primitive/IntegerTest/Atomic Tests
         */
        Atomic ( Atomic const & obj ) noexcept : // NOLINT(modernize-use-equals-default)
                utility :: hidden :: integerAtomicImpl :: Base (obj) {

        }

        Atomic ( Atomic && obj ) noexcept : // NOLINT(performance-move-constructor-init)
                utility :: hidden :: integerAtomicImpl :: Base ( std :: forward < utility :: hidden :: integerAtomicImpl :: Base > ( obj ) ) {

        }

        Atomic ( Integer const & integer ) noexcept : // NOLINT(google-explicit-constructor)
                utility :: hidden :: integerAtomicImpl :: Base (integer) {

        }


        Atomic (int value) noexcept { // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
            this->set(value);
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

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() == atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() != atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Integer const & integer ) const noexcept -> bool {
            return this->get() == integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Integer const & integer ) const noexcept -> bool {
            return this->get() != integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( int value ) const noexcept -> bool {
            return this->get() == value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( int value ) const noexcept -> bool {
            return this->get() != value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() > atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() < atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Integer const & integer ) const noexcept -> bool {
            return this->get() > integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Integer const & integer ) const noexcept -> bool {
            return this->get() < integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( int value ) const noexcept -> bool {
            return this->get() > value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( int value ) const noexcept -> bool {
            return this->get() < value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() >= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() <= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Integer const & integer ) const noexcept -> bool {
            return this->get() >= integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Integer const & integer ) const noexcept -> bool {
            return this->get() <= integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( int value ) const noexcept -> bool {
            return this->get() >= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( int value ) const noexcept -> bool {
            return this->get() <= value;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (int value, Atomic const & atomic) noexcept -> bool {
            return value == atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value == atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (int value, Atomic const & atomic) noexcept -> bool {
            return value != atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value != atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (int value, Atomic const & atomic) noexcept -> bool {
            return value >= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value >= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (int value, Atomic const & atomic) noexcept -> bool {
            return value <= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value <= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (int value, Atomic const & atomic) noexcept -> bool {
            return value > atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value > atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (int value, Atomic const & atomic) noexcept -> bool {
            return value < atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (Integer const & value, Atomic const & atomic) noexcept -> bool {
            return value < atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & atomic ) const noexcept -> Integer { return this->get() + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Integer const & integer ) const noexcept -> Integer { return this->get() + integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( int value ) const noexcept -> Integer { return this->get() + value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value + atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( int value, Atomic const & atomic ) noexcept -> Integer { return value + atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & atomic ) const noexcept -> Integer { return this->get() - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Integer const & integer ) const noexcept -> Integer { return this->get() - integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( int value ) const noexcept -> Integer { return this->get() - value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value - atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( int value, Atomic const & atomic ) noexcept -> Integer { return value - atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & atomic ) const noexcept -> Integer { return this->get() * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Integer const & integer ) const noexcept -> Integer { return this->get() * integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( int value ) const noexcept -> Integer { return this->get() * value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value * atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( int value, Atomic const & atomic ) noexcept -> Integer { return value * atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & atomic ) const noexcept (false) -> Integer {
            int rValue = atomic.get();
            int lValue = this->get();

            if ( rValue == 0 ) {
                throw DivideByZeroException();
            }

            if ( rValue == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return lValue / rValue;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Integer const & integer ) const noexcept (false) -> Integer {
            int lValue = this->get();

            if (integer == 0 ) {
                throw DivideByZeroException();
            }

            if (integer == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return lValue / integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( int value ) const noexcept (false) -> Integer {
            auto lValue = this->get();

            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return lValue / value;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( Integer const & value, Atomic const & atomic ) noexcept (false) -> Integer {
            int rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if ( rVal == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return value / rVal;
        }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( int value, Atomic const & atomic ) noexcept (false) -> Integer {
            int rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if ( rVal == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            return value / rVal;
        }


        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Atomic const & atomic ) const noexcept (false) -> Integer {
            int rValue = atomic.get();
            int lValue = this->get();

            if (rValue == 0 ) {
                throw DivideByZeroException();
            }

            if (rValue == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return lValue % rValue;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Integer const & integer ) const noexcept (false) -> Integer {
            int lValue = this->get();

            if (integer == 0 ) {
                throw DivideByZeroException();
            }

            if (integer == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return lValue % integer;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( int rValue ) const noexcept (false) -> Integer {
            int lValue = this->get();
            if (rValue == 0 ) {
                throw DivideByZeroException();
            }

            if (rValue == INT32_MIN || lValue == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return lValue % rValue;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( Integer const & value, Atomic const & atomic ) noexcept (false) -> Integer {
            int rVal = atomic.get();

            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if ( rVal == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return value % rVal;
        }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( int value, Atomic const & atomic ) noexcept (false) -> Integer {
            int rVal = atomic.get();

            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if ( rVal == INT32_MIN || value == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            return value % rVal;
        }


        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Atomic const & atomic ) const noexcept -> Integer { return this->get() & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Integer const & integer ) const noexcept -> Integer { return this->get() & integer; } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( int value ) const noexcept -> Integer { return this->get() & value; } // NOLINT(clion-misra-cpp2008-5-3-3)

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( int value, Atomic const & atomic ) noexcept -> Integer { return value & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)


        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Atomic const & atomic ) const noexcept -> Integer { return this->get() | atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Integer const & integer ) const noexcept -> Integer { return this->get() | integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( int value ) const noexcept -> Integer { return this->get() | value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value | atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( int value, Atomic const & atomic ) noexcept -> Integer { return value | atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Atomic const & atomic ) const noexcept -> Integer { return this->get() ^ atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Integer const & integer ) const noexcept -> Integer { return this->get() ^ integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( int value ) const noexcept -> Integer { return this->get() ^ value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value ^ atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( int value, Atomic const & atomic ) noexcept -> Integer { return value ^ atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Atomic const & atomic ) const noexcept -> Integer { return this->get() << atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Integer const & integer ) const noexcept -> Integer { return this->get() << integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( int value ) const noexcept -> Integer { return this->get() << value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value << atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( int value, Atomic const & atomic ) noexcept -> Integer { return value << atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Atomic const & atomic ) const noexcept -> Integer { return this->get() >> atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Integer const & integer ) const noexcept -> Integer { return this->get() >> integer; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( int value ) const noexcept -> Integer { return this->get() >> value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( Integer const & value, Atomic const & atomic ) noexcept -> Integer { return value >> atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( int value, Atomic const & atomic ) noexcept -> Integer { return value >> atomic.get(); }

        __CDS_NoDiscard __CDS_OptimalInline auto hash () const noexcept -> Index override {
            return this->get().hash();
        }

        __CDS_OptionalInline auto operator += (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data += value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator -= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data -= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator *= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data *= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator /= (int value) noexcept (false) -> Atomic & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
            }

            this->_data /= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (int value) noexcept (false) -> Atomic & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
            }

            this->_data %= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator &= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data &= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator |= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data |= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator ^= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data ^= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator >>= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data >>= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator <<= (int value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data <<= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator += (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data += value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator -= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data -= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator *= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data *= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator /= (Integer const & value) noexcept (false) -> Atomic & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( value == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
            }

            this->_data /= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (Integer const & value) noexcept (false) -> Atomic & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
            }

            if ( value == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();
            this->_data %= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator &= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data &= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator |= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data |= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator ^= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data ^= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator >>= (Integer const & value) noexcept -> Atomic & {
            this->_access.lock();
            this->_data >>= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator <<= (Integer const & value) noexcept -> Atomic & {
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
            if ( rValue == 0 ) {
                throw DivideByZeroException();
            }

            if ( rValue == INT32_MIN ) {
                throw ArithmeticException("Division by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
            }

            this->_data /= rValue;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (Atomic const & value) noexcept (false) -> Atomic & {
            auto rValue = value.get();
            if ( rValue == 0 ) {
                throw DivideByZeroException();
            }

            if ( rValue == INT32_MIN ) {
                throw ArithmeticException("Modulo by INT32_MIN is undefined behaviour");
            }

            this->_access.lock();

            if ( this->_data == INT32_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by INT32_MIN is undefined behaviour");
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

        __CDS_NoDiscard __CDS_OptionalInline auto operator ~ () const noexcept -> Integer {
            return this->get().operator~();
        }
    };

}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#if defined(CDS_INTEGER_POSTFIX)

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _i (unsigned long long int value) noexcept -> cds :: Integer {
    return static_cast < int > (value);
}

#endif

namespace cds {

    using Int = Integer;

}

__CDS_Meta_RegisterParseType(Integer) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_INTEGER_HPP
