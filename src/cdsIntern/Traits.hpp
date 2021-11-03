//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_TRAITS_HPP
#define CDS_TRAITS_HPP

#include <type_traits>
#include <utility>
#include <iostream>
#include "../prepro.h"

template < bool expression, typename T = int >
using EnableIf = typename std :: enable_if < expression, T > :: type;

template < typename T >
using RemoveReference = typename std :: remove_reference < T > :: type;

template < typename T >
using RemoveConst = typename std :: remove_const < T > :: type;

template < typename T >
using RemovePointer = typename std :: remove_pointer < T > :: type;

template < typename T >
using RemoveModifiers = RemoveReference < RemovePointer < RemoveConst < T > > >;

template < typename T, typename V >
using IsSame = typename std :: is_same < T, V > :: type :: value;


template < bool condition, typename TrueType, typename FalseType >
using TypeIf = typename std :: conditional < condition, TrueType, FalseType > :: type;

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

template < bool value >
using BoolConstant = std :: bool_constant < value >;

#else

template < bool value >
using BoolConstant = std :: integral_constant < bool, value >;

#endif

template < typename T, typename U, typename = std::void_t<> > struct isComparableLess : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct __CDS_MaybeUnused isComparableLessNoexcept : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableGreater : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct __CDS_MaybeUnused isComparableGreaterNoexcept : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableEquals : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct __CDS_MaybeUnused isComparableEqualsNoexcept : std::false_type {};

template < typename T, typename U > struct isComparableLess < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct __CDS_MaybeUnused isComparableLessNoexcept < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U>() ) > > : BoolConstant < noexcept ( std::declval <T> () < std::declval <U> () ) > { };

template < typename T, typename U > struct isComparableEquals < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct __CDS_MaybeUnused isComparableEqualsNoexcept < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U>() ) > > : BoolConstant < noexcept ( std::declval <T> () == std::declval <U> () ) > { };

template < typename T, typename U > struct isComparableGreater < T, U, std::void_t < decltype ( std::declval <T> () > std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct __CDS_MaybeUnused isComparableGreaterNoexcept < T, U, std::void_t < decltype ( std::declval <T> () > std::declval <U>() ) > > : BoolConstant < noexcept ( std::declval <T> () > std::declval <U> () ) > { };

template < typename T >
constexpr auto typeHasEqualityOperator () noexcept -> bool {
    return isComparableEquals < T, T > :: type :: value;
}

template < typename K, typename V >
class Pair;

template < class T >
struct isPair : public std::false_type {};
template < class T1, class T2 >
struct isPair <Pair<T1, T2>> : public std::true_type {};

template < typename T >
class UniquePointer;
template < typename T >
class SharedPointer;
template < typename T >
class AtomicSharedPointer;
template < typename T >
class ForeignPointer;

template < typename T >
struct isSmartPointer : public std :: false_type {};
template < typename T >
struct isSmartPointer < UniquePointer < T > > : public std :: true_type {};
template < typename T >
struct isSmartPointer < SharedPointer < T > > : public std :: true_type {};
template < typename T >
struct isSmartPointer < AtomicSharedPointer < T > > : public std :: true_type {};
template < typename T >
struct isSmartPointer < ForeignPointer < T > > : public std :: true_type {};

template < typename T, typename U = void >
struct isPrintable : std::false_type {};

#include <iostream>
template < typename T >
struct isPrintable <
        T,
        typename std :: enable_if < std::is_same < decltype (std::cout << std::declval<T>()), std::ostream & >::value > :: type
> : std::true_type { };

template < typename D, typename B >
using isDerivedFrom = std::is_base_of < B, D >;

template < typename B, typename D >
using isBaseOf __CDS_MaybeUnused = std::is_base_of < B, D >;

template < typename D >
using isObjectDerived = isDerivedFrom < D, Object >;

template < typename D >
constexpr auto typeObjectDerived () noexcept -> bool {
    return isObjectDerived < D > :: type :: value;
}

template < typename T, typename = void >
struct functionTraits;

template < typename R, typename ... A >
struct functionTraits < R (*) (A ...) > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = void;
    using argsType __CDS_Deprecated = std::tuple < A... >;

    using ReturnType = R;
    using ClassType = void;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = C;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = C;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) const > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = C;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = C;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename ... A >
struct functionTraits < R ( A ... ) > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = void;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = void;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename ... A >
struct functionTraits < R (*) (A ...) noexcept > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = void;
    using argsType __CDS_Deprecated = std::tuple < A... >;

    using ReturnType = R;
    using ClassType = void;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) noexcept > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = C;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = C;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) const noexcept > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = C;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = C;
    using ArgsType = std :: tuple < A ... >;
};

template < typename R, typename ... A >
struct functionTraits < R ( A ... ) noexcept > {
    using returnType __CDS_Deprecated __CDS_MaybeUnused = R;
    using classType __CDS_Deprecated = void;
    using argsType __CDS_Deprecated = std::tuple < A ... >;

    using ReturnType = R;
    using ClassType = void;
    using ArgsType = std :: tuple < A ... >;
};

template < typename T >
struct functionTraits < T, std::void_t < decltype ( & T :: operator () ) > > :
    public functionTraits < decltype ( & T :: operator () ) > {
};

template < typename T >
using returnOf = typename functionTraits < T > :: ReturnType;

template < typename T >
using argumentsOf = typename functionTraits < T > :: ArgsType;

template < typename T >
using classOf __CDS_MaybeUnused = typename functionTraits < T > :: ClassType;

template < typename T >
constexpr auto typeFundamental () noexcept -> bool {
    return std :: is_fundamental < T > :: type :: value || std :: is_enum < T > :: type :: value;
}

template < typename T >
constexpr auto typeDefaultConstructible () noexcept -> bool {
    return std :: is_default_constructible < T > :: type :: value;
}

template < typename T >
constexpr auto typeCopyConstructible () noexcept -> bool {
    return std :: is_copy_constructible < T > :: type :: value;
}

template < typename T >
constexpr auto typeMoveConstructible () noexcept -> bool {
    return std :: is_move_constructible < T > :: type :: value;
}

template < typename T >
constexpr auto typeCopyAssignable () noexcept -> bool {
    return std :: is_copy_assignable< T > :: type :: value;
}

template < typename T >
constexpr auto typeMoveAssignable () noexcept -> bool {
    return std :: is_move_assignable < T > :: type :: value;
}

template<typename T, typename U = void>
struct isCallableType
{
    static bool const constexpr value = std::conditional<
            std::is_class<typename std::remove_reference<T> :: type>::value,
            isCallableType<typename std::remove_reference<T> :: type, int>,
            std::false_type
        >::type::value;
};

template <> struct isCallableType <String> : std :: false_type{};
template <> struct isCallableType <Object> : std :: false_type{};

template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(*)(Args...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(&)(Args...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(*)(Args...,...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(&)(Args...,...), U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)volatile, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const volatile, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)volatile, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const volatile, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)&, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)volatile&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const volatile&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)&, U> : std::true_type {};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)volatile&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const volatile&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)volatile&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...)const volatile&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)volatile&&, U> : std::true_type{};
template<typename T, typename U, typename ...Args>
struct isCallableType<T(Args...,...)const volatile&&, U> : std::true_type{};

template<typename T>
struct isCallableType<T, int>
{
private:
    using YesType = char(&)[1];
    using NoType = char(&)[2];

    struct Fallback { void operator()(); };

    struct Derived : T, Fallback {};

    template<typename U, U>
    struct Check;

    template<typename>
    static YesType Test(...);

    template<typename C>
    static NoType Test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static bool const constexpr value = sizeof(Test<Derived>(0)) == sizeof(YesType);
};

namespace Utility {

    template<typename T>
    struct TypeParseTraits {
        constexpr static StringLiteral name = "Undefined";
    };

}

#define __CDS_RegisterParseType(_type) /* NOLINT(bugprone-reserved-identifier) */ \
namespace Utility {                                                               \
    template <>                                       \
    struct TypeParseTraits < _type > {     \
        constexpr static StringLiteral name = # _type; \
    }; \
}

#define __CDS_RegisterParseTypeTemplateT(_type) /* NOLINT(bugprone-reserved-identifier) */  \
namespace Utility {                             \
    template < typename T >                     \
    struct TypeParseTraits < _type < T > > {    \
        constexpr static StringLiteral name = # _type;                                            \
    };\
}

__CDS_RegisterParseType(sint8)
__CDS_RegisterParseType(sint16)
__CDS_RegisterParseType(sint32)
__CDS_RegisterParseType(sint64)

__CDS_RegisterParseType(uint8)
__CDS_RegisterParseType(uint16)
__CDS_RegisterParseType(uint32)
__CDS_RegisterParseType(uint64)

__CDS_RegisterParseType(void)
__CDS_RegisterParseType(bool)
__CDS_RegisterParseType(float)
__CDS_RegisterParseType(double)

template < typename T, typename = void >
struct isStaticFunctionType {
    constexpr static bool value = false;
};

template < typename T, typename = void >
struct isCallableObjectType : public std :: false_type {};

template < typename T >
struct isCallableObjectType < T, std :: void_t < decltype ( & T :: operator () ) > > : std :: true_type {};

template < typename T >
struct isStaticFunctionType < T > {
    constexpr static bool value = std :: is_function < T > :: value && ! isCallableObjectType < T > :: value;
};

__CDS_WarningSuppression_FunctionTypeTraits_SuppressEnable

template < typename T >
struct Type {
    using BaseType = T;

#if defined(__CDS_Type_FormMetaTypes)

    using WithoutReference = Type < typename std :: remove_reference < T > :: type >;
    using WithoutConst = Type < typename std :: remove_const < T > :: type >;
    using WithoutPointer = Type < typename std :: remove_pointer < T > :: type >;
    using WithoutModifiers __CDS_MaybeUnused = typename Type < T > :: WithoutReference :: WithoutPointer :: WithoutConst;

    using AsUniquePointer __CDS_MaybeUnused = UniquePointer < typename Type < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsForeignPointer = ForeignPointer < typename Type < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsSharedPointer __CDS_MaybeUnused = SharedPointer < typename Type < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsAtomicSharedPointer __CDS_MaybeUnused = AtomicSharedPointer < typename Type < T > :: WithoutReference :: WithoutPointer :: BaseType >;

#endif

    static constexpr bool defaultConstructible = typeDefaultConstructible < T> ();
    static constexpr bool copyConstructible = typeCopyConstructible < T > ();
    static constexpr bool moveConstructible = typeMoveConstructible< T > ();

    static constexpr bool copyAssignable = typeCopyAssignable< T > ();
    static constexpr bool moveAssignable = typeMoveAssignable< T > ();

    static constexpr bool hasEqualityOperator = typeHasEqualityOperator < T > ();
    static constexpr bool objectDerived = typeObjectDerived < T > ();


    static constexpr bool ostreamPrintable = isPrintable < T > :: type :: value;

    static constexpr bool equalsComparable = isComparableEquals < T, T > :: type :: value;

    static constexpr bool isFundamental = typeFundamental < T >();
    __CDS_MaybeUnused static constexpr bool isIntegral = std::is_integral < T > :: type :: value;
    static constexpr bool isNumeric = std :: is_arithmetic < T > :: type :: value;
    static constexpr bool isBasicPointer = std :: is_pointer < T > :: type :: value;
    static constexpr bool isSmartPointer = :: isSmartPointer < T > :: type :: value;
    static constexpr bool isPointer = isBasicPointer || isSmartPointer;
    __CDS_MaybeUnused static constexpr bool isReference = std :: is_reference < T > :: type :: value;
    __CDS_MaybeUnused static constexpr bool isLvalue = std :: is_lvalue_reference < T > :: type :: value;
    __CDS_MaybeUnused static constexpr bool isRvalue = std :: is_rvalue_reference < T > :: type :: value;
    __CDS_MaybeUnused static constexpr bool isConst = std :: is_const < T > :: type :: value;

    static constexpr bool isCallable = isCallableType < T > :: value || std::is_function < T > :: value;
    static constexpr bool isCallableObject = isCallableObjectType < T > :: value;
    static constexpr bool isFunction = isStaticFunctionType < T > :: value;

#if __CDS_cpplang_VariableTemplates_available == true

    template < typename Base >
    static constexpr bool derivedFrom = isDerivedFrom < T, Base > :: type :: value;

    template < typename Derived >
    static constexpr bool baseOf = isDerivedFrom < Derived, T > :: type :: value;

#else

    template < typename Base >
    static constexpr auto derivedFrom () noexcept -> bool {
        return isDerivedFrom < T, Base > :: type :: value;
    }

    template < typename Derived >
    static constexpr auto baseOf () noexcept -> bool {
        return isDerivedFrom < Derived, T > :: type :: value;
    }

#endif

    template < typename U = T, EnableIf < Type < U > :: hasEqualityOperator > = 0 >
    constexpr static auto compare (T const & a, T const & b, int = 0) noexcept -> bool {
        return a == b;
    }

    template < typename U = T, EnableIf < ! Type < U > :: hasEqualityOperator && Type < U > :: objectDerived > = 0 >
    __CDS_cpplang_VirtualConstexpr static auto compare (T const & a, T const & b, float = 0.0f) noexcept -> bool {
        return a.equals(b);
    }

    template < typename U = T, EnableIf < ! Type < U > :: hasEqualityOperator && ! Type < U > :: objectDerived > = 0 >
    constexpr static auto compare (T const & a, T const & b) noexcept -> bool {
        return & a == & b;
    }

    template < typename U = T, EnableIf < Type < U > :: ostreamPrintable > = 0 >
    static constexpr auto streamPrint(std::ostream & ostream, T const & obj) noexcept -> std :: ostream & {
        return (ostream << obj);
    }

    template < typename U = T, EnableIf < ! Type < U > :: ostreamPrintable > = 0 >
    static constexpr auto streamPrint(std::ostream & ostream, T const & obj) noexcept -> std :: ostream & {
        return (ostream << ( & obj ) );
    }

    template < typename V = typename std :: remove_reference < T > :: type >
    constexpr static auto unsafeAddress () noexcept -> V * { return reinterpret_cast < V * > (0x10); }
    constexpr static auto unsafeReference () noexcept -> T & { return * Type :: unsafeAddress(); }

    template < typename U = T >
    constexpr static auto name () noexcept -> StringLiteral { return Utility :: TypeParseTraits < U > :: name; }
};

__CDS_WarningSuppression_FunctionTypeTraits_SuppressDisable

template < typename T, typename = void >
struct pairTrait {
    using FirstType = void;
    using SecondType = void;
    using Type = Pair < FirstType, SecondType >;
};

template < typename T >
struct pairTrait < T > {
    using FirstType = EnableIf < isPair < T > :: type :: value, typename std::remove_reference < decltype ( Type < T > :: unsafeAddress() -> first() ) > :: type >;
    using SecondType = EnableIf < isPair < T > :: type :: value, typename std::remove_reference < decltype ( Type < T > :: unsafeAddress() -> second() ) > :: type >;
    using Type = Pair < FirstType, SecondType >;
};

namespace Utility {
    template<typename T>
    struct TypeParseTraits<Type<T>> {
        constexpr static StringLiteral name = "Type Metaclass";
    };
}

template < typename T >
struct TypeExtensions {
    using BaseType = T;

    using WithoutReference = TypeExtensions < typename std :: remove_reference < T > :: type >;
    using WithoutConst = TypeExtensions < typename std :: remove_const < T > :: type >;
    using WithoutPointer = TypeExtensions < typename std :: remove_pointer < T > :: type >;
    using WithoutModifiers __CDS_MaybeUnused = typename TypeExtensions < T > :: WithoutReference :: WithoutPointer :: WithoutConst;

    using AsUniquePointer __CDS_MaybeUnused = UniquePointer < typename TypeExtensions < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsForeignPointer = ForeignPointer < typename TypeExtensions < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsSharedPointer __CDS_MaybeUnused = SharedPointer < typename TypeExtensions < T > :: WithoutReference :: WithoutPointer :: BaseType >;
    using AsAtomicSharedPointer __CDS_MaybeUnused = AtomicSharedPointer < typename TypeExtensions < T > :: WithoutReference :: WithoutPointer :: BaseType >;
};

#endif //CDS_TRAITS_HPP
