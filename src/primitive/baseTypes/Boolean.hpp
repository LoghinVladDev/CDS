//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_BOOLEAN_HPP
#define CDS_BOOLEAN_HPP

#include <CDS/Object>
#include <CDS/memory/Allocation>

namespace cds {

    /**
     * @class Object Derived container for a Boolean Value
     *
     * @test Test in primitive/BooleanTest
     */
    class Boolean : public Object {
    private:

        /**
         * @brief Boolean Value contained
         */
        bool v { false };
    public:

        /**
         * @brief Default Constructor
         *
         * Creates a Boolean with false value
         *
         * @exceptsafe
         *
         * @test Tested in primitive/BooleanTest/Constructor Test
         */
        constexpr Boolean () noexcept = default;

        /**
         * @brief Copy Constructor
         *
         * Creates a Boolean with the received container's value
         *
         * @param obj : Boolean cref = Const Reference to an Object whose value to copy
         *
         * @exceptsafe
         *
         * @test Tested in primitive/BooleanTest/Constructor Test
         */
        constexpr Boolean ( Boolean const & ) noexcept = default;

        /**
         * @brief Copy Constructor
         *
         * Creates a Boolean with the received container's value. Move semantics apply, although they do not modify the
         * parameter due to it containing a trivial value.
         *
         * @param obj : Boolean mref = Move Reference to an Object whose value to move
         *
         * @exceptsafe
         *
         * @test Tested in primitive/BooleanTest/Constructor Test
         */
        constexpr Boolean ( Boolean && ) noexcept = default;

        /**
         * @brief Destructor
         *
         * @exceptsafe
         *
         * @test Tested in primitive/BooleanTest/Constructor Test
         */
        __CDS_cpplang_ConstexprDestructor ~Boolean() noexcept override { } /* NOLINT(modernize-use-equals-default) */ /* causes destructor to be created after the True/False constexpr variables (cpp20) */

        /**
         * @brief Constructor from trivial boolean value
         *
         * @param value : bool = value to assign to container
         *
         * @exceptsafe
         *
         * @test Tested in primitive/BooleanTest/Constructor Test
         */
        constexpr Boolean ( bool value ) noexcept : v(value) { } // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)

        /**
         * @brief Copy Operator.
         *
         * @param value : Boolean cref = Constant Reference to a boolean object to copy value from
         *
         * @exceptsafe
         *
         * @returns Boolean ref = Reference to modified object
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Boolean const & value ) noexcept -> Boolean & {
            if ( this == & value ) {
                return * this;
            }

            this->v = value.v;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Boolean && value ) noexcept -> Boolean & {
            if ( this == & value ) {
                return * this;
            }

            this->v = exchange (value.v, false );
            return * this;
        }

        /**
         * @brief Copy Operator.
         *
         * @param value : bool = bool value to get value from
         *
         * @exceptsafe
         *
         * @returns Boolean ref = Reference to modified object
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_NonConstConstexprMemberFunction Boolean & operator = ( bool value ) noexcept {
            this->v = value;
            return * this;
        }

        /**
         * @brief Boolean And Operator
         *
         * @param value : Boolean cref = Constant Reference to Right Operand
         *
         * @exceptsafe
         *
         * @return Boolean containing true value if both left and right operands are true, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator &&(Boolean const & value) const noexcept -> Boolean { // NOLINT(clion-misra-cpp2008-5-2-11)
            return this->v && value.v;
        }

        /**
         * @brief Boolean And Operator
         *
         * @param value : bool = Right Operand
         *
         * @exceptsafe
         *
         * @return Boolean containing true value if both left and right operands are true, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator && ( bool value ) const noexcept -> Boolean { // NOLINT(clion-misra-cpp2008-5-2-11)
            return this->v && value;
        }

        /**
         * @brief Boolean Or Operator
         *
         * @param value : Boolean cref = Constant Reference to Right Operand
         *
         * @exceptsafe
         *
         * @return Boolean containing true value if left or right operands are true, false if none are
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator ||(Boolean const & value) const noexcept -> Boolean { // NOLINT(clion-misra-cpp2008-5-2-11)
            return this->v || value.v;
        }

        /**
         * @brief Boolean And Operator
         *
         * @param value : bool = Right Operand
         *
         * @exceptsafe
         *
         * @return Boolean containing true value if left or right operands are true, false if none are
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator || ( bool value ) const noexcept -> Boolean { // NOLINT(clion-misra-cpp2008-5-2-11)
            return this->v || value;
        }

        /**
         * @brief Boolean Not Operator
         *
         * @exceptsafe
         *
         * @returns Boolean containing reversed value, false if caller is true, true if caller is false
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor auto operator ! () const noexcept -> Boolean {
            return !this->v;
        }

        /**
         * @brief Comparison Operator
         *
         * @param value : Boolean cref = Constant Reference to a Boolean Object to compare this to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects are equal, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        constexpr auto operator == (Boolean const & value) const noexcept -> bool { return this->v == value.v; }

        /**
         * @brief Comparison Operator
         *
         * @param value : bool = Boolean Value to compare this to
         *
         * @exceptsafe
         *
         * @returns bool = true if values are equal, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        constexpr auto operator == (bool value) const noexcept -> bool { return this->v == value; }

        /**
         * @brief Comparison Operator
         *
         * @param value : Boolean cref = Constant Reference to a Boolean Object to compare this to
         *
         * @exceptsafe
         *
         * @returns bool = true if objects are not equal, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        constexpr auto operator != (Boolean const & value) const noexcept -> bool { return this->v != value.v; }

        /**
         * @brief Comparison Operator
         *
         * @param value : bool = Boolean Value to compare this to
         *
         * @exceptsafe
         *
         * @returns bool = true if values are not equal, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        constexpr auto operator != (bool value) const noexcept -> bool { return this->v != value; }

        /**
         * @brief Comparison Function
         *
         * @param value : Object cref = Constant Reference to an Object Derived Object
         *
         * @exceptsafe
         *
         * @return bool = true if objects are equal, same type and value, false otherwise
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & value ) const noexcept -> bool override {
            if ( this == & value ) {
                return true;
            }

            auto pValue = dynamic_cast < decltype (this) > ( & value );
            if (pValue == nullptr ) {
                return false;
            }

            return this->operator==(*pValue);
        }

        /**
         * @brief Cast Specification from container to bool used to obtain value
         *
         * @exceptsafe
         *
         * @returns bool = value contained
         *
         * @test Tested in primitive/BooleanTest/any
         */
        constexpr operator bool () const noexcept { // NOLINT(google-explicit-constructor)
            return this->v;
        }

        /**
         * @brief Function used to obtain the value, same as casting
         *
         * @exceptsafe
         *
         * @returns bool = value contained
         *
         * @test Tested in primitive/BooleanTest/any
         */
        __CDS_NoDiscard constexpr auto get () const noexcept -> bool {
            return this->v;
        }

        /**
         * @brief Function used to obtain the hash value of the Object
         *
         * @exceptsafe
         *
         * @return Hash Value
         *
         * @test Does not Apply
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash () const noexcept -> Size override {
            return static_cast < Index > (this->v);
        }

        /**
         * @brief Function used to obtain the String representation of the Object
         *
         * @exceptsafe
         *
         * @returns String = representation of the Object
         *
         * @test Tested in primitive/BooleanTest
         */
        __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override {
            return String().append(this->v ? "true" : "false");
        }

        /**
         * @brief Function used to obtain a boolean value from a String
         *
         * @param string : String cref = String object containing representation
         *
         * @static
         *
         * @exceptsafe
         *
         * @return Boolean = value obtained from String
         *
         * @test Tested in primitive/BooleanTest/Operator Tests
         */
        __CDS_cpplang_ConstexprDestructor static auto parse(String const & string) noexcept -> Boolean {
            if ( string.empty() ) {
                return false;
            }

            return string == "true";
        }
    };

}

#if defined(CDS_BOOLEAN_POSTFIX)

/**
 * @brief Transformation postfix literal
 *
 * @exceptsafe
 *
 * @returns Boolean = new Boolean object containing requested value
 *
 * @test Tested in primitive/BooleanTest
 */
__CDS_cpplang_ConstexprPostfixLiteral auto operator "" _b (unsigned long long int i) noexcept -> cds :: Boolean {
    return {i != 0};
}

#endif

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

namespace cds {

    /**
     * Boolean Constant describing True Value
     */
    __CDS_cpplang_ConstexprDestructor const Boolean True = true;

    /**
     * Boolean Constant describing False Value
     */
    __CDS_cpplang_ConstexprDestructor const Boolean False = false;

}

#else

/**
 * Boolean Constant describing True Value
 */
#define True true

/**
 * Boolean Constant describing False Value
 */
#define False false

#endif


__CDS_Meta_RegisterParseType(Boolean) // NOLINT(clion-misra-cpp2008-8-0-1)


#endif //CDS_BOOLEAN_HPP
