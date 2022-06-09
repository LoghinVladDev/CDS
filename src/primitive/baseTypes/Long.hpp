//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_LONG_HPP
#define CDS_LONG_HPP

#include <CDS/Object>
#include <CDS/Random>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/Utility>
#include <CDS/Limits>
#include <CDS/Integer>
#include <CDS/Memory>

namespace cds {

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
         *  that ranges values in [limits::S64_MIN, INT64_MAX]
         *
         * @static
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing randomly generated integer value
         *
         * @test Tested in primitive/LongTest/Random Tests
         */
        __CDS_MaybeUnused static auto random () noexcept -> Long {
            static UniquePointer < RandomGenerator > pRng;
            if (pRng.isNull()) {
                pRng.reset(Memory :: instance ().create < RandomGenerator > ());
            }

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
        __CDS_MaybeUnused static auto random (CType low, CType high) noexcept -> Long {
            static UniquePointer < RandomGenerator > pRng;
            if ( pRng.isNull() || pRng->low() != low && pRng->high() != high ) {
                pRng.reset(Memory :: instance ().create < RandomGenerator > (low, high));
            }

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

        __CDS_cpplang_ConstexprConditioned Long(Integer const & integer) noexcept : v(integer.get()) { } // NOLINT(google-explicit-constructor)

        __CDS_cpplang_ConstexprConditioned Long(Integer && integer) noexcept : v(integer.get()) { } // NOLINT(google-explicit-constructor)

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
        constexpr Long(CType value) noexcept: v(value) {} // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)

        explicit constexpr Long(sint8 value) noexcept: v(value) {}
        explicit constexpr Long(sint16 value) noexcept: v(value) {}
        explicit constexpr Long(sint32 value) noexcept: v(value) {}

        explicit constexpr Long(uint8 value) noexcept: v(static_cast < sint64 > (value)) {}
        explicit constexpr Long(uint16 value) noexcept: v(static_cast < sint64 > (value)) {}
        explicit constexpr Long(uint32 value) noexcept: v(static_cast < sint64 > (value)) {}
        explicit constexpr Long(uint64 value) noexcept: v(static_cast < sint64 >(value)) {}

        /**
         * @brief Assignment Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to assign value from
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Constructor Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator=(Long const &aLong) noexcept -> Long & {
            if (this == &aLong) {
                return *this;
            }

            this->v = aLong.v;
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
            if (this == & value) {
                return *this;
            }

            this->v = exchange ( value.v, 0ll );
            return *this;
        }

        /**
         * @brief Sum Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to sum with caller Object
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing sum of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator+(Long const &aLong) const noexcept -> Long { return this->v + aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator+ (CType value, Long const & aLong) noexcept -> Long { return value + aLong.v; }

        /**
         * @brief Difference Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to subtract from caller Object
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing difference of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator-(Long const &aLong) const noexcept -> Long { return this->v - aLong.v; }

        __CDS_cpplang_ConstexprDestructor friend auto operator - (CType value, Long const & aLong) noexcept -> Long { return value - aLong.v; }

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
         * @param aLong : Long cref = Constant Reference to an Long Object to multiply from caller Object
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing multiplication of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator*(Long const &aLong) const noexcept -> Long { return this->v * aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator * (CType value, Long const & aLong) noexcept -> Long { return value * aLong.v; }

        /**
         * @brief Division Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to divide caller Object with
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long = new Object containing division of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator/(Long const &aLong) const noexcept (false) -> Long {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }

            if (aLong.v == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return this->v / aLong.v;
        }

        friend auto operator / (CType value, Long const & aLong) noexcept (false) -> Long {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }

            if (aLong.v == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return value / aLong.v;
        }

        /**
         * @brief Division Operator
         *
         * @param value : CType = int value to divide caller Object with
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long = new Object containing division of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator / (CType value) const noexcept (false) -> Long {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if (value == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return this->v / value;
        }

        /**
         * @brief Modulo Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to obtain remainder from caller Object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long = new Object containing remainder of division of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator % (Long const &aLong) const noexcept (false) -> Long {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }
            if (aLong.v == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return this->v % aLong.v;
        }

        /**
         * @brief Modulo Operator
         *
         * @param value : CType = int value to obtain remainder from caller Object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long = new Object containing remainder of division of operands
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator % (CType value) const noexcept (false) -> Long {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }
            if (value == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return this->v % value;
        }

        __CDS_cpplang_ConstexprDestructor friend auto operator % (CType value, Long const & aLong) noexcept (false) -> Long {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }
            if (aLong.v == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return value % aLong.v;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param aLong : Long cref = Constant Reference to Long Object to sum into left, caller object
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator+=(Long const &aLong) noexcept -> Long & {
            this->v += aLong.v;
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
         * @param aLong : Long cref = Constant Reference to Long Object to subtract into left, caller object
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator-=(Long const &aLong) noexcept -> Long & {
            this->v -= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to Long Object to multiply with left, caller object
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator*=(Long const &aLong) noexcept -> Long & {
            this->v *= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to Long Object to divide with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(Long const &aLong) noexcept (false) -> Long & {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }
            if (aLong.v == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->v /= aLong.v;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param value : CType = value to divide with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator/=(CType value) noexcept (false) -> Long & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }
            if (value == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->v /= value;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param aLong : Long cref = Constant Reference to Long Object to apply modulo with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(Long const &aLong) noexcept (false) -> Long & {
            if (aLong.v == 0 ) {
                throw DivideByZeroException();
            }
            if (aLong.v == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            this->v %= aLong.v;
            return *this;
        }

        /**
         * @brief Sum Accumulate Operator
         *
         * @param value : CType = value to apply modulo with left, caller object
         *
         * @throws DivideByZeroException if right hand operator is 0
         * @throws ArithmeticException if right hand operator is limits::S64_MIN due to it being undefined behaviour ( if compiler is not C2 compliant )
         *
         * @returns Long ref = Reference to modified object
         *
         * @test Tested in primitive/Long/Algebraic Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator%=(CType value) noexcept (false) -> Long & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }
            if (value == limits::S64_MIN || this->v == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            this->v %= value;
            return *this;
        }

        /**
         * @brief Equality Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects have same value, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator==(Long const &aLong) const noexcept -> bool { return this->v == aLong.v; }

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

        __CDS_NoDiscard constexpr friend auto operator == (CType value, Long const & aLong) noexcept -> bool { return value == aLong.v; }

        /**
         * @brief Difference Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects do not have same value, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator!=(Long const &aLong) const noexcept -> bool { return this->v != aLong.v; }

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

        __CDS_NoDiscard constexpr friend auto operator != (CType value, Long const & aLong) noexcept -> bool { return value != aLong.v; }

        /**
         * @brief Greater Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is greater that right's, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator>(Long const &aLong) const noexcept -> bool { return this->v > aLong.v; }

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

        __CDS_NoDiscard constexpr friend auto operator > (CType value, Long const & aLong) noexcept -> bool { return value > aLong.v; }

        /**
         * @brief Less Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is less than right's, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator<(Long const &aLong) const noexcept -> bool { return this->v < aLong.v; }

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

        __CDS_NoDiscard constexpr friend auto operator < (CType value, Long const & aLong) noexcept -> bool { return value < aLong.v; }

        /**
         * @brief Greater or Equals Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is greater or equals that right's, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        __CDS_NoDiscard constexpr auto operator>=(Long const &aLong) const noexcept -> bool { return this->v >= aLong.v; }

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

        __CDS_NoDiscard constexpr friend auto operator >= (CType value, Long const & aLong) noexcept -> bool { return value >= aLong.v; }

        /**
         * @brief Less or Equals Comparison Operator
         *
         * @param aLong : Long cref = Constant Reference to an Long Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if left's value is less or equals that right's, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operators
         */
        constexpr auto operator<=(Long const &aLong) const noexcept -> bool { return this->v <= aLong.v; }

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

        constexpr friend auto operator <= (CType value, Long const & aLong) noexcept -> bool { return value <= aLong.v; }

    #if __CDS_cpplang_ThreeWayComparison_available == true

        constexpr auto operator <=> (Long const & aLong) const noexcept -> std::strong_ordering { return this->v <=> aLong.v; }

        constexpr auto operator <=> (CType value) const noexcept -> std::strong_ordering { return this->v <=> value; }

        constexpr friend auto operator <=> (CType value, Long const & aLong) noexcept -> std::strong_ordering { return value <=> aLong.v; }

    #endif

        /**
         * @brief Bitwise And Operator
         *
         * @param aLong : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing the resulted value
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator&(Long const &aLong) const noexcept -> Long { return this->v & aLong.v; } // NOLINT(clion-misra-cpp2008-5-3-3)

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
        __CDS_cpplang_ConstexprDestructor auto operator&(CType value) const noexcept -> Long { return this->v & value; } // NOLINT(clion-misra-cpp2008-5-3-3)

        __CDS_cpplang_ConstexprDestructor friend auto operator & (CType value, Long const & aLong) noexcept -> Long { return value & aLong.v; } // NOLINT(clion-misra-cpp2008-5-3-3)

        /**
         * @brief Bitwise Or Operator
         *
         * @param aLong : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing the resulted value
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator|(Long const &aLong) const noexcept -> Long { return this->v | aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator | (CType value, Long const & aLong) noexcept -> Long { return value | aLong.v; }

        /**
         * @brief Bitwise Xor Operator
         *
         * @param aLong : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing the resulted value
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator^(Long const &aLong) const noexcept -> Long { return this->v ^ aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator ^ (CType value, Long const & aLong) noexcept -> Long { return value ^ aLong.v; }

        /**
         * @brief Bitwise Left Shift Operator
         *
         * @param aLong : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing the resulted value
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator<<(Long const &aLong) const noexcept -> Long { return this->v << aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator << (CType value, Long const & aLong) noexcept -> Long { return value << aLong.v; }

        /**
         * @brief Bitwise Right Shift Operator
         *
         * @param aLong : Long cref = Constant Reference to the Object to use in the bitwise operation as right hand operand
         *
         * @exceptsafe
         *
         * @returns Long = new Object containing the resulted value
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator>>(Long const &aLong) const noexcept -> Long { return this->v >> aLong.v; }

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

        __CDS_cpplang_ConstexprDestructor friend auto operator >> (CType value, Long const & aLong) noexcept -> Long { return value >> aLong.v; }

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
         * @param aLong : Long cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to the modified Object
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator&=(Long const &aLong) noexcept -> Long & {
            this->v &= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to the modified Object
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator|=(Long const &aLong) noexcept -> Long & {
            this->v |= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to the modified Object
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator^=(Long const &aLong) noexcept -> Long & {
            this->v ^= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to the modified Object
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator<<=(Long const &aLong) noexcept -> Long & {
            this->v <<= aLong.v;
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
         * @param aLong : Long cref = Constant Reference to the Object to accumulate to the caller
         *
         * @exceptsafe
         *
         * @returns Long ref = Reference to the modified Object
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator>>=(Long const &aLong) noexcept -> Long & {
            this->v >>= aLong.v;
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
         * @param object : Object cref = Constant Reference to a CDS Object derived Instance
         *
         * @exceptsafe
         *
         * @returns bool = true if objects are same or of same type and value, false otherwise
         *
         * @test Tested in primitive/LongTest/Relational Operator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pLong = dynamic_cast < decltype (this) > ( & object );
            if (pLong == nullptr ) {
                return false;
            }

            return this->operator==(*pLong);
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
        __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Long { auto aLong = * this; this->v++; return aLong; }

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
        __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Long { auto aLong = * this; this->v--; return aLong; }

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

        __CDS_NoDiscard __CDS_OptimalInline auto toString(int base) const noexcept -> String {
            auto intValue = this->v;
            String rep;

            __CDS_cpplang_ConstexprLambda auto baseDigitToString = [](CType value) noexcept -> char {
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
            if ( string.empty() ) {
                return 0;
            }

            bool negative = false;

            auto iterator = string.begin();
            __CDS_cpplang_ConstexprLambda static auto isNumericChar = [] (char character) noexcept -> bool { return character >= '0' && character <= '9'; };
            __CDS_cpplang_ConstexprLambda static auto numericCharToInt = [] (char character) noexcept -> int { return static_cast < int > ( character ) - 48; };

            while(! isNumericChar (iterator.value() ) && iterator != string.end() ) {
                if (iterator.value() == '-' ) {
                    negative = true;
                }

                (void) iterator.next();
            }

            CType numericValue = 0;

            while (isNumericChar (iterator.value() ) && iterator != string.end() ) {
                numericValue = numericValue * 10 + numericCharToInt (iterator.value() );
                (void) iterator.next();
            }

            return negative ? (-numericValue) : numericValue;
        }

        /**
         * @brief Thread Safe, Atomic container for Long Type
         */
        class Atomic; // NOLINT(cppcoreguidelines-virtual-class-destructor)
    };

}

#include <CDS/Atomic>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden {
            namespace longAtomicImpl {

                using Base = Atomic<Long>; // NOLINT(bugprone-reserved-identifier)

            }
        }
    }
}

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#endif

namespace cds {

    class Long::Atomic : public utility :: hidden :: longAtomicImpl :: Base { // NOLINT(bugprone-reserved-identifier)
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
         * @test Tested in primitive/LongTest/Atomic Tests
         */
        Atomic ( Atomic const & obj ) noexcept :  // NOLINT(modernize-use-equals-default)
                utility :: hidden :: longAtomicImpl :: Base (obj) {

        }

        Atomic ( Atomic && obj ) noexcept :  // NOLINT(performance-move-constructor-init)
                utility :: hidden :: longAtomicImpl :: Base ( std :: forward < utility :: hidden :: longAtomicImpl :: Base > ( obj ) ) {

        }

        Atomic ( Long const & aLong ) noexcept :  // NOLINT(google-explicit-constructor)
                utility :: hidden :: longAtomicImpl :: Base (aLong) {

        }

        Atomic (CType value) noexcept { // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
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

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() == atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() != atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( Long const & aLong ) const noexcept -> bool {
            return this->get() == aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( Long const & aLong ) const noexcept -> bool {
            return this->get() != aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator == ( CType value ) const noexcept -> bool {
            return this->get() == value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator != ( CType value ) const noexcept -> bool {
            return this->get() != value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() > atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() < atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( Long const & aLong ) const noexcept -> bool {
            return this->get() > aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( Long const & aLong ) const noexcept -> bool {
            return this->get() < aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator > ( CType value ) const noexcept -> bool {
            return this->get() > value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator < ( CType value ) const noexcept -> bool {
            return this->get() < value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() >= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Atomic const & atomic ) const noexcept -> bool {
            return this->get() <= atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( Long const & aLong ) const noexcept -> bool {
            return this->get() >= aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( Long const & aLong ) const noexcept -> bool {
            return this->get() <= aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator >= ( CType value ) const noexcept -> bool {
            return this->get() >= value;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator <= ( CType value ) const noexcept -> bool {
            return this->get() <= value;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (CType value, Atomic const & atomic) noexcept -> bool {
            return value == atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator == (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value == atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (CType value, Atomic const & atomic) noexcept -> bool {
            return value != atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator != (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value != atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (CType value, Atomic const & atomic) noexcept -> bool {
            return value >= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >= (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value >= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (CType value, Atomic const & atomic) noexcept -> bool {
            return value <= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator <= (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value <= atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (CType value, Atomic const & atomic) noexcept -> bool {
            return value > atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator > (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value > atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (CType value, Atomic const & atomic) noexcept -> bool {
            return value < atomic.get();
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator < (Long const & value, Atomic const & atomic) noexcept -> bool {
            return value < atomic.get();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Atomic const & atomic ) const noexcept -> Long { return this->get() + atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( Long const & aLong ) const noexcept -> Long { return this->get() + aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( CType value ) const noexcept -> Long { return this->get() + value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value + atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator + ( CType value, Atomic const & atomic ) noexcept -> Long { return value + atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Atomic const & atomic ) const noexcept -> Long { return this->get() - atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( Long const & aLong ) const noexcept -> Long { return this->get() - aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator - ( CType value ) const noexcept -> Long { return this->get() - value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value - atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator - ( CType value, Atomic const & atomic ) noexcept -> Long { return value - atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Atomic const & atomic ) const noexcept -> Long { return this->get() * atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( Long const & aLong ) const noexcept -> Long { return this->get() * aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator * ( CType value ) const noexcept -> Long { return this->get() * value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value * atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator * ( CType value, Atomic const & atomic ) noexcept -> Long { return value * atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Atomic const & atomic ) const noexcept (false) -> Long {
            CType rValue = atomic.get();
            CType lValue = this->get();

            if ( rValue == 0 ) {
                throw DivideByZeroException();
            }

            if (rValue == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return lValue / rValue;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( Long const & aLong ) const noexcept (false) -> Long {
            CType lValue = this->get();

            if (aLong == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (aLong == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return lValue / aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator / ( CType value ) const noexcept (false) -> Long {
            auto lValue = this->get();

            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if (value == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return lValue / value;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( Long const & value, Atomic const & atomic ) noexcept (false) -> Long {
            CType rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if (rVal == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return value / rVal;
        }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator / ( CType value, Atomic const & atomic ) noexcept (false) -> Long {
            CType rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if (rVal == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            return value / rVal;
        }


        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Atomic const & atomic ) const noexcept (false) -> Long {
            CType rValue = atomic.get();
            CType lValue = this->get();

            if (rValue == 0 ) {
                throw DivideByZeroException();
            }

            if (rValue == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return lValue % rValue;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( Long const & aLong ) const noexcept (false) -> Long {
            CType lValue = this->get();
            if (aLong == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (aLong == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return lValue % aLong;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto operator % ( CType rValue ) const noexcept (false) -> Long {
            CType lValue = this->get();
            if (rValue == 0 ) {
                throw DivideByZeroException();
            }

            if (rValue == limits::S64_MIN || lValue == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return lValue % rValue;
        }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( Long const & value, Atomic const & atomic ) noexcept (false) -> Long {
            CType rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if (rVal == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return value % rVal;
        }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator % ( CType value, Atomic const & atomic ) noexcept (false) -> Long {
            CType rVal = atomic.get();
            if ( rVal == 0 ) {
                throw DivideByZeroException();
            }

            if (rVal == limits::S64_MIN || value == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            return value % rVal;
        }


        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Atomic const & atomic ) const noexcept -> Long { return this->get() & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( Long const & aLong ) const noexcept -> Long { return this->get() & aLong; } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard __CDS_OptimalInline auto operator & ( CType value ) const noexcept -> Long { return this->get() & value; } // NOLINT(clion-misra-cpp2008-5-3-3)

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator & ( CType value, Atomic const & atomic ) noexcept -> Long { return value & atomic.get(); } // NOLINT(clion-misra-cpp2008-5-3-3)


        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Atomic const & atomic ) const noexcept -> Long { return this->get() | atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( Long const & aLong ) const noexcept -> Long { return this->get() | aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator | ( CType value ) const noexcept -> Long { return this->get() | value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value | atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator | ( CType value, Atomic const & atomic ) noexcept -> Long { return value | atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Atomic const & atomic ) const noexcept -> Long { return this->get() ^ atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( Long const & aLong ) const noexcept -> Long { return this->get() ^ aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator ^ ( CType value ) const noexcept -> Long { return this->get() ^ value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value ^ atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator ^ ( CType value, Atomic const & atomic ) noexcept -> Long { return value ^ atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Atomic const & atomic ) const noexcept -> Long { return this->get() << atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( Long const & aLong ) const noexcept -> Long { return this->get() << aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator << ( CType value ) const noexcept -> Long { return this->get() << value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value << atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator << ( CType value, Atomic const & atomic ) noexcept -> Long { return value << atomic.get(); }


        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Atomic const & atomic ) const noexcept -> Long { return this->get() >> atomic.get(); }
        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( Long const & aLong ) const noexcept -> Long { return this->get() >> aLong; }
        __CDS_NoDiscard __CDS_OptimalInline auto operator >> ( CType value ) const noexcept -> Long { return this->get() >> value; }

        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( Long const & value, Atomic const & atomic ) noexcept -> Long { return value >> atomic.get(); }
        __CDS_NoDiscard friend __CDS_OptimalInline auto operator >> ( CType value, Atomic const & atomic ) noexcept -> Long { return value >> atomic.get(); }

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
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if (value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_access.lock();

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_data /= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (CType value) noexcept (false) -> Atomic & {
            if ( value == 0 ) {
                throw DivideByZeroException();
            }

            if (value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_access.lock();

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
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
            if ( value == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (value == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_access.lock();

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_data /= value;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (Long const & value) noexcept (false) -> Atomic & {
            if ( value == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
            }

            if (value == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

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
            if ( rValue == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (rValue == limits::S64_MIN ) {
                throw ArithmeticException("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_access.lock();

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
            }

            this->_data /= rValue;
            this->_access.unlock();
            return * this;
        }

        __CDS_OptionalInline auto operator %= (Atomic const & value) noexcept (false) -> Atomic & {
            auto rValue = value.get();
            if ( rValue == static_cast < sint64 > ( 0 ) ) {
                throw DivideByZeroException();
            }

            if (rValue == limits::S64_MIN ) {
                throw ArithmeticException("Modulo by limits::S64_MIN is undefined behaviour");
            }

            this->_access.lock();

            if (this->_data == limits::S64_MIN ) {
                this->_access.unlock();
                throw ArithmeticException ("Division by limits::S64_MIN is undefined behaviour");
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

}

#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

#if defined(CDS_INTEGER_POSTFIX)

__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _l (unsigned long long int value) noexcept -> cds :: Long {
    return static_cast < long long int > (value);
}

#endif

__CDS_Meta_RegisterParseType(Long) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_LONG_HPP
