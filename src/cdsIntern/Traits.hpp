//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_TRAITS_HPP
#define CDS_TRAITS_HPP

#include <type_traits>
#include <utility>
#include <iostream>
#include "../prepro.h"

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

template < bool value >
using BoolConstant = std :: bool_constant < value >;

#else

template < bool value >
using BoolConstant = std :: integral_constant < bool, value >;

#endif

template < typename T, typename U, typename = std::void_t<> > struct isComparableLess : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct __CDS_MaybeUnused isComparableLessNoexcept : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableEquals : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct __CDS_MaybeUnused isComparableEqualsNoexcept : std::false_type {};

template < typename T, typename U > struct isComparableLess < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct __CDS_MaybeUnused isComparableLessNoexcept < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U>() ) > > : BoolConstant < noexcept ( std::declval <T> () < std::declval <U> () ) > { };

template < typename T, typename U > struct isComparableEquals < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct __CDS_MaybeUnused isComparableEqualsNoexcept < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U>() ) > > : BoolConstant < noexcept ( std::declval <T> () == std::declval <U> () ) > { };

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

#if defined(__cpp_concepts)
template < typename T >
concept IsMappable = isPair<T>::value;
#endif

template < typename T, typename U = void >
struct isPrintable : std::false_type {};

#include <iostream>
template < typename T >
struct isPrintable <
        T,
        typename std::enable_if <
                std::is_same < decltype (std::cout << std::declval<T>()), std::ostream & >::value
        > :: type
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
    using returnType __CDS_MaybeUnused = R;
    using classType = void;
    using argsType = std::tuple < A... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) > {
    using returnType __CDS_MaybeUnused = R;
    using classType = C;
    using argsType = std::tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) const > {
    using returnType __CDS_MaybeUnused = R;
    using classType = C;
    using argsType = std::tuple < A ... >;
};

template < typename T >
struct functionTraits < T, std::void_t < decltype ( & T :: operator () ) > > :
    public functionTraits < decltype ( & T :: operator () ) > {
};

template < typename T, typename = void >
struct returnTrait;

template < typename R, typename ... A >
struct returnTrait < R (*) (A ...) > {
    using returnType = R;
};

template < typename R, typename C, typename ... A >
struct returnTrait < R (C::*) (A ...) > {
    using returnType = R;
};

template < typename R, typename C, typename ... A >
struct returnTrait < R (C::*) (A ...) const > {
    using returnType = R;
};

template < typename T >
struct returnTrait < T, std::void_t < decltype ( & T :: operator () ) > > :
    public returnTrait < decltype ( & T :: operator () ) > {

};

template < typename T >
using returnOf = typename returnTrait < T > :: returnType;

template < typename T >
using argumentsOf = typename functionTraits < T > :: argsType;

template < typename T >
using classOf __CDS_MaybeUnused = typename functionTraits < T > :: classType;

# if defined (__cpp_concepts)

template < typename T >
concept PairType = isPair < T > :: value ;

template < typename T, typename V >
concept LessComparable = isComparableLess < T, V > :: type :: value;

template < typename T >
concept TypeLessComparable = LessComparable < T, T >;

template < typename T, typename V >
concept EqualsComparable = isComparableEquals < T, V > :: type :: value;

template < typename T >
concept TypeEqualsComparable = EqualsComparable < T, T >;

# endif

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

template < typename T >
struct Type {
    using BaseType = T;

    using WithoutReference = Type < typename std :: remove_reference < T > :: type >;
    using WithoutConst = Type < typename std :: remove_const < T > :: type >;

    using WithoutConstReference = typename Type < T > :: WithoutConst :: WithoutReference;

    static constexpr bool defaultConstructible = typeDefaultConstructible < T> ();
    static constexpr bool copyConstructible = typeCopyConstructible < T > ();
    static constexpr bool moveConstructible = typeMoveConstructible< T > ();

    static constexpr bool copyAssignable = typeCopyAssignable< T > ();
    static constexpr bool moveAssignable = typeMoveAssignable< T > ();

    static constexpr bool hasEqualityOperator = typeHasEqualityOperator < T > ();
    static constexpr bool objectDerived = typeObjectDerived < T > ();


    static constexpr bool ostreamPrintable = isPrintable < T > :: type :: value;

    static constexpr bool fundamental = typeFundamental < T >();

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

    template < typename U = T >
    static constexpr auto compare (T const & a, T const & b, int = 0) noexcept -> typename std :: enable_if < Type < U > :: hasEqualityOperator, bool > :: type {
        return a == b;
    }

    template < typename U = T >
    static inline auto compare (T const & a, T const & b, float = 0.0f) noexcept -> typename std :: enable_if < ! Type < U > :: hasEqualityOperator && Type < U > :: objectDerived, bool > :: type {
        return a.equals(b);
    }

    template < typename U = T >
    static constexpr auto compare (T const & a, T const & b) noexcept -> typename std :: enable_if < ! Type < U > :: hasEqualityOperator && ! Type < U > :: objectDerived, bool > :: type {
        return & a == & b;
    }

    template < typename U = T >
    static constexpr auto streamPrint(std::ostream & ostream, T const & obj) noexcept -> typename std :: enable_if < Type < U > :: ostreamPrintable, std :: ostream & > :: type {
        return (ostream << obj);
    }

    template < typename U = T >
    static constexpr auto streamPrint(std::ostream & ostream, T const & obj) noexcept -> typename std :: enable_if < !Type < U > :: ostreamPrintable, std :: ostream & > :: type {
        return (ostream << &obj);
    }

    template < typename V = typename std :: remove_reference < T > :: type >
    constexpr static auto unsafeAddress () noexcept -> V * { return reinterpret_cast < V * > (0x10); }
    constexpr static auto unsafeReference () noexcept -> T & { return * Type :: unsafeAddress(); }
};

template < typename T, typename = void >
struct pairTrait {
    using FirstType = void;
    using SecondType = void;
    using Type = Pair < FirstType, SecondType >;
};

template < typename T >
struct pairTrait < T > {
    using FirstType = typename std :: enable_if < isPair < T > :: type :: value, typename std::remove_reference < decltype ( Type < T > :: unsafeAddress() -> first() ) > :: type > :: type;
    using SecondType = typename std :: enable_if < isPair < T > :: type :: value, typename std::remove_reference < decltype ( Type < T > :: unsafeAddress() -> second() ) > :: type > :: type;
    using Type = Pair < FirstType, SecondType >;
};

#endif //CDS_TRAITS_HPP
