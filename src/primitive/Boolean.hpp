//
// Created by loghin on 25.02.2021.
//

#ifndef CDS_BOOLEAN_HPP
#define CDS_BOOLEAN_HPP

#include <CDS/Object>

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
     * @param v : bool = value to assign to container
     *
     * @exceptsafe
     *
     * @test Tested in primitive/BooleanTest/Constructor Test
     */
    constexpr Boolean ( bool v ) noexcept : v(v) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Copy Operator.
     *
     * @param o : Boolean cref = Constant Reference to a boolean object to copy value from
     *
     * @exceptsafe
     *
     * @returns Boolean ref = Reference to modified object
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Boolean const & o ) noexcept -> Boolean & {
        if ( this == & o ) return * this;
        this->v = o.v;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Boolean && o ) noexcept -> Boolean & {
        if ( this == & o ) return * this;
        this->v = Utility :: exchange ( o.v, false );
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
     * @param o : Boolean cref = Constant Reference to Right Operand
     *
     * @exceptsafe
     *
     * @return Boolean containing true value if both left and right operands are true, false otherwise
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator &&(Boolean const & o) const noexcept -> Boolean {
        return this->v && o.v;
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
    __CDS_cpplang_ConstexprDestructor auto operator && ( bool value ) const noexcept -> Boolean {
        return this->v && value;
    }

    /**
     * @brief Boolean Or Operator
     *
     * @param o : Boolean cref = Constant Reference to Right Operand
     *
     * @exceptsafe
     *
     * @return Boolean containing true value if left or right operands are true, false if none are
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    __CDS_cpplang_ConstexprDestructor auto operator ||(Boolean const & o) const noexcept -> Boolean {
        return this->v || o.v;
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
    __CDS_cpplang_ConstexprDestructor auto operator || ( bool value ) const noexcept -> Boolean {
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
     * @param o : Boolean cref = Constant Reference to a Boolean Object to compare this to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects are equal, false otherwise
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    constexpr auto operator == (Boolean const & o) const noexcept -> bool { return this->v == o.v; }

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
     * @param o : Boolean cref = Constant Reference to a Boolean Object to compare this to
     *
     * @exceptsafe
     *
     * @returns bool = true if objects are not equal, false otherwise
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    constexpr auto operator != (Boolean const & o) const noexcept -> bool { return this->v != o.v; }

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
     * @param o : Object cref = Constant Reference to an Object Derived Object
     *
     * @exceptsafe
     *
     * @return bool = true if objects are equal, same type and value, false otherwise
     *
     * @test Tested in primitive/BooleanTest/Operator Tests
     */
    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
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
    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash () const noexcept -> Index override {
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
    __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto toString () const noexcept -> String override {
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
        if ( string.empty() ) return false;

        return string == "true";
    }

    /**
     * @brief Function used to obtain a copy of this object into another, new variable
     *
     * @exceptsafe
     *
     * @returns Boolean ptr = Address to a new Boolean Object
     *
     * @test Does not Apply
     */
    __CDS_NoDiscard inline auto copy () const noexcept -> Boolean * override {
        return new Boolean( * this );
    }

    /**
     * @brief Thread Safe, Atomic container for Boolean Type
     */
    class Atomic;
};

#include <CDS/Atomic>
namespace __CDS_HiddenUtility { // NOLINT(bugprone-reserved-identifier)
    /**
     * @brief Wrapper name used to avoid naming conflicts
     */
    using _AtomicBaseBoolean = Atomic<Boolean>; // NOLINT(bugprone-reserved-identifier)
}

class Boolean::Atomic : public __CDS_HiddenUtility::_AtomicBaseBoolean { // NOLINT(bugprone-reserved-identifier)
public:

    /**
     * @brief Default Constructor for Wrapper Type - Atomic < Boolean > - encapsulating a Boolean variable
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic () noexcept {
        this->set(false);
    }

    /**
     * @brief Copy Constructor for Atomic < Boolean > type
     *
     * @param obj : Atomic cref = Constant Reference to an Atomic < Boolean > Object
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic ( Atomic const & obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseBoolean(obj) { } /* NOLINT(modernize-use-equals-default,google-explicit-constructor) */

    /**
     * @brief Move Constructor using an Atomic < Boolean > type value
     *
     * @param obj : Atomic mref = Move Reference ( rvalue ) to an Atomic < Boolean > Object
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic ( Atomic && obj ) noexcept : __CDS_HiddenUtility::_AtomicBaseBoolean(obj) { } // NOLINT(performance-move-constructor-init,google-explicit-constructor)

    /**
     * @brief Constructor from Boolean Object
     *
     * @param v : Boolean cref = Constant Reference to a Boolean Object
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic ( Boolean const & v ) noexcept : __CDS_HiddenUtility::_AtomicBaseBoolean(v) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor from Boolean Object
     *
     * @param v : Boolean mref = Move Reference ( rvalue ) to a Boolean Object
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic ( Boolean && v ) noexcept : __CDS_HiddenUtility::_AtomicBaseBoolean(v) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor from bool literal
     *
     * @param v : bool = value to assign
     *
     * @exceptsafe
     * @threadsafe
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline Atomic (bool v) noexcept { // NOLINT(google-explicit-constructor)
        this->set(v);
    }

    /**
     * @brief Assignment Operator
     *
     * @param value : bool = value to assign
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Atomic & = Reference to the modified Object
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline auto operator = (bool value) noexcept -> Atomic & {
        this->set(Boolean(value));
        return * this;
    }

    /**
     * @brief Assignment Operator
     *
     * @param obj : Boolean cref = Constant Reference to the Object to acquire the value to assign from
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Atomic & = Reference to the modified Object
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline auto operator = (Boolean const & obj) noexcept -> Atomic & override {
        this->set(obj);
        return * this;
    }

    /**
     * @brief Assignment Operator
     *
     * @param obj : Atomic < Boolean > cref = Constant Reference to the Object to acquire the value to assign from
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Atomic & = Reference to the modified Object
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline auto operator = (Atomic const &) noexcept -> Atomic & = default;

    /**
     * @brief Move Assignment Operator
     *
     * @param obj : Atomic < Boolean > mref = Move Reference to the Object to move the value to assign from
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Atomic & = Reference to the modified Object
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline auto operator = (Atomic &&) noexcept -> Atomic & = default;

    /**
     * @brief Conversion Specification to contained type
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Boolean = new Boolean object containing same contained value
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline operator Boolean () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get();
    }

    /**
     * @brief Conversion Specification to bool literal type
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns bool = contained value
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->get().get();
    }

    /**
     * @brief toString Function
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns String = Object string representation
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    __CDS_NoDiscard inline auto toString() const noexcept -> String override {
        return this->get().toString();
    }

    /**
     * @brief Hash Function
     *
     * @exceptsafe
     * @threadsafe
     *
     * @returns Index = Hash Value of Object
     *
     * @test Tested in primitive/BooleanTest/Boolean::Atomic Tests
     */
    inline auto hash () const noexcept -> Index override {
        return this->get().hash();
    }
};

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
__CDS_cpplang_ConstexprDestructor auto operator "" _b (unsigned long long int i) noexcept -> Boolean {
    return {i != 0};
}

#endif

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

/**
 * Boolean Constant describing True Value
 */
__CDS_cpplang_ConstexprDestructor const Boolean True = true;

/**
 * Boolean Constant describing False Value
 */
__CDS_cpplang_ConstexprDestructor const Boolean False = false;

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


__CDS_RegisterParseType(Boolean)


#endif //CDS_BOOLEAN_HPP
