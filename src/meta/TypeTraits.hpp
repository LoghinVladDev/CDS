//
// Created by loghin on 5/18/2022.
//

#ifndef __CDS_META_TYPE_TRAITS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_META_TYPE_TRAITS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

#include <CDS/meta/Base>
#include <iostream>

#include "../../src/primitive/pointer/pointer/Predeclarations.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

class Object;

/**
 * @class type representing a Pair of two types.
 * @tparam __K is the type of the first pair member
 * @tparam __V is the type of the second pair member
 */
template <typename __K, typename __V> class Pair; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace meta {        // NOLINT(modernize-concat-nested-namespaces)
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by less than operator (\<)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __LessThanPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by greater than operator (\>)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __GreaterThanPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by less than or equal to operator (\<=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __LessThanOrEqualToPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by greater than or equal to operator (\>=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __GreaterThanOrEqualToPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by equal to operator (==)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __EqualToPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if two given types can be compared by not equal to operator (!=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R, typename = Void <>> struct __NotEqualToPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T, typename = Void <>> struct __IndirectionPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T, typename = Void <>> struct __PrefixIncrementPossible : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __LessThanPossible <__L, __R, Void <decltype (valueOf <__L>() < valueOf <__R>())>> : __TrueType {};

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __GreaterThanPossible <__L, __R, Void <decltype (valueOf <__L>() > valueOf <__R>())>> : __TrueType {};

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __LessThanOrEqualToPossible <__L, __R, Void <decltype (valueOf <__L>() <= valueOf <__R>())>> : __TrueType {};

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __GreaterThanOrEqualToPossible <__L, __R, Void <decltype (valueOf <__L>() >= valueOf <__R>())>> : __TrueType {};

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __EqualToPossible <__L, __R, Void <decltype (valueOf <__L>() == valueOf <__R>())>> : __TrueType {};

template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __NotEqualToPossible <__L, __R, Void <decltype (valueOf <__L>() != valueOf <__R>())>> : __TrueType {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IndirectionPossible <__T, Void <decltype (*valueOf <__T> ())>> : __TrueType {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __PrefixIncrementPossible < __T, Void <decltype (++referenceOf <__T> ())>> : __TrueType {};

/**
 * @brief Meta-type implementation used to check if a given type is printable ( std::ostream << type )
 * @tparam __T is the type for which printability is checked
 */
template < typename __T, typename = void >  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsPrintable : __FalseType {};      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsPrintable <__T, Void <decltype (std::cout << valueOf<__T>())>> : __TrueType {};

namespace __baseOfImpl { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __BaseType>                            auto __conversionTest (__BaseType const volatile *) noexcept -> __TrueType;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename>                                       auto __conversionTest (void     const volatile *) noexcept -> __FalseType;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename, typename>                             auto __testBaseOf (...) -> __TrueType;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __BaseType, typename __DerivedType>    auto __testBaseOf (int) ->                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
decltype ( __conversionTest < __BaseType > ( addressOf < __DerivedType > () ) );
} /* namespace __baseOfImpl */

/**
 * @brief Meta-type implementation used to check if a given type is a base class of another given type
 * @tparam __BaseType is the type given as a base class
 * @tparam __DerivedType is the type given as a derived class
 */
template < typename __BaseType, typename __DerivedType >    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsBaseOf : __And <__IsClass <__BaseType>, __IsClass <__DerivedType>, decltype (__baseOfImpl::__testBaseOf <__BaseType, __DerivedType> (0))> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to obtain the type name in a StringLiteral format ( char const * )
 * @tparam __T is the type for which the name is obtained
 */
template <typename __T> struct __TypeParseTraits { constexpr static StringLiteral name = "Undefined"; }; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if a given type is a Pair type
 * @tparam __T is the type checked
 */
template <typename __T>               struct __IsPair                         : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __K, typename __V> struct __IsPair <cds::Pair <__K, __V>>  : __TrueType {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to check if a given type is a Smart Pointer derived-type
 * @tparam __T is the type checked
 */
template <typename __T>               struct __IsSmartPointer                                 : __FalseType {};   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T>               struct __IsSmartPointer <cds::SmartPointer <__T>>       : __TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T>               struct __IsSmartPointer <cds::RawPointer <__T>>         : __TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __D> struct __IsSmartPointer <cds::UniquePointer <__T, __D>> : __TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __D> struct __IsSmartPointer <cds::SharedPointer <__T, __D>> : __TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __D> struct __IsSmartPointer <cds::WeakPointer <__T, __D>>   : __TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace __decayImpl { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/**
 * @brief Meta-type helper implementation used to obtain safe pass-by-value equivalent type of a given type
 * @tparam __T is the type for which to obtain a pass by value
 *
 * This will act as a switch based on the isArray or isFunction conditions
 * <ul>
 *  <li> If none are satisfied, go with removal of modifiers </li>
 *  <li> If is array, go with extent removal and addition of pointer </li>
 *  <li> If is function, go with addition of pointer </li>
 * </ul>
 */
template <typename __T, bool __isArray = __IsArray <__T>::value, bool __isFunction = __IsFunction <__T>::value>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Decay {};                                                                                                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Decay <__T, false, false> {
  using Type = typename __RemoveConstVolatile <__T>::Type;
};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Decay <__T, true, false> {
  using Type = typename __RemoveExtent <__T>::Type*;
};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Decay <__T, false, true> {
  using Type = typename __AddPointer <__T>::Type;
};
} /* namespace __decayImpl */

/**
 * @brief Meta-type implementation used to obtain safe pass-by-value equivalent type of a given type
 * @tparam __T is the type for which to obtain a pass by value
 * @example decay will convert any rvalue type to a lvalue type <br/>
 * <pre>- Decay\<int\>            = int;</pre>
 * <pre>- Decay\<int &\>          = int;</pre>
 * <pre>- Decay\<int &&\>         = int; </pre>
 * <pre>- Decay\<int const &\>    = int; </pre>
 * @example decay will convert any array with extent type to a pointer type <br/>
 * <pre>- Decay\<int[2]\>         = int *; </pre>
 * @example decay will convert any function signature type to a function pointer for that signature type <br/>
 * <pre>- Decay\<int(int)\>       = int (*)(int); </pre>
 */
template <typename __T>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Decay {            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

private:
  using FirstParseDecayedType = typename __RemoveReference <__T>::Type;

public:
  using Type = typename __decayImpl::__Decay < FirstParseDecayedType >::Type;
};

namespace __isMemberPointerImpl { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/**
 * @brief Meta-type helper implementation used to check if a given type is a member of an object
 * @tparam __T is the type checked
 */
template <typename>                   struct __IsMemberObjectPointer                  : __FalseType {};                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __C> struct __IsMemberObjectPointer <__T __C::*>     : __Not <__IsFunction <__T>> {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
} /* namespace __isMemberPointerImpl */

/**
 * @brief Meta-type implementation used to check if a given type is a member of an object
 * @tparam __T is the type checked
 */
template < typename __T, typename = void >          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsMemberObjectPointer : __FalseType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T>               struct __IsMemberObjectPointer <__T>                    : __isMemberPointerImpl::__IsMemberObjectPointer < typename __RemoveConstVolatile <__T>::Type > {};   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __C> struct __IsMemberObjectPointer < __T __C::*, __C >    : __IsMemberObjectPointer < typename __RemoveConstVolatile < __T __C::* >::Type > {};                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace __isMemberPointerImpl { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/**
 * @brief Meta-type helper implementation used to check if a given type is a member function of an object
 * @tparam __T is the type checked
 */
template <typename>                   struct __IsMemberFunctionPointer                    : __FalseType {};                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __C> struct __IsMemberFunctionPointer < __T __C::* >   : __BoolConstant < __IsFunction <__T>::value > {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
} /* namespace __isMemberPointerImpl */

/**
 * @brief Meta-type implementation used to check if a given type is a member function of an object
 * @tparam __T is the type checked
 */
template <typename __T, typename = void> struct __IsMemberFunctionPointer : __FalseType {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T>               struct __IsMemberFunctionPointer <__T>                : __isMemberPointerImpl::__IsMemberFunctionPointer < typename __RemoveConstVolatile <__T>::Type > {};                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T, typename __C> struct __IsMemberFunctionPointer < __T __C::*, __C >  : __isMemberPointerImpl::__IsMemberFunctionPointer < typename __RemoveConstVolatile < __T __Decay < __C >::Type::* >::Type > {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type implementation used to obtain the common, lvalue type that the given types can be converted to, if any
 * @tparam __TPack is the pack of types to find a common type for
 *
 * Implementation:
 * <ul>
 *      <li> If no types given, Common type does not exist </li>
 *      <li> If only one type is given, Common type is the common type of itself, twice. ( will be reduced to itself ). </li>
 *      <li> If two types are given, the Common type is the common type of the decayed types </li>
 *      <li>
 *          If two types are given and their decayed versions are the same as themselves, attempt to find their common
 *          <ul>
 *              <li> Apply them in a ternary operator, acquire the result from the expression, if any exists, and decay it. </li>
 *          </ul>
 *      </li>
 *      <li> If more than two types are given, the type is the common type of the first two to their common type and the remaining types. </li>
 * </ul>
 */
template <typename ... __TPack> struct __Common;                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <>                     struct __Common <> {};
template <typename __T>         struct __Common <__T> : __Common <__T, __T> {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace __commonImpl { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/**
 * @brief Meta-type helper implementation used to obtain the common type between two types via ternary operator, if possible
 */
struct __CommonTest { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  template <typename __T>   struct SuccessType { using Type = __T; }; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  struct FailureType { };

  template < typename __T, typename __U > using ConditionalType = decltype ( true ? valueOf <__T> () : valueOf < __U > () );                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  template < typename __T, typename __U > static auto __test ( int ) -> SuccessType < typename __Decay < ConditionalType < __T, __U > >::Type >;                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  template < typename __T, typename __U > static auto __test2 ( int ) -> SuccessType < typename __RemoveConstVolatile < ConditionalType < __T const &, __U const & > >::Type >; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename, typename>         static auto __test2 ( ... ) -> FailureType;                                                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  template < typename __T, typename __U > static auto __test ( ... ) -> decltype ( __CommonTest::__test2 < __T, __U > ( 0 ) );                                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

/**
 * @brief Meta-type helper implementation used to decay the types of two given types before using the ternary helper
 * @tparam __T1 is the type given as first type
 * @tparam __T2 is the type given as second type
 * @tparam __DecayedT1 is the decayed type of the first type
 * @tparam __DecayedT2 is the decayed type of the second type
 */
template < typename __T1, typename __T2, typename __DecayedT1 = typename __Decay < __T1 >::Type, typename __DecayedT2 = typename __Decay < __T2 >::Type >   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __CommonDecayed {                                                                                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Type = __Common < __DecayedT1, __DecayedT2 >;
};

template < typename __T1, typename __T2 > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __CommonDecayed < __T1, __T2, __T1, __T2 > : private __CommonTest {
  using Type = decltype ( __CommonTest::__test < __T1, __T2 > (0) );
};

/**
 * @brief Meta-type helper implementation used to preserve the remaining type pack in the case of more than two types given to common
 */
template < typename ... >
struct __CommonPack {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type helper implementation used to apply the fold expression to reducing the two-or-more types of common by the following rule:
 *
 * Common \< T1, T2, T3, ... \> = Common \< Common \< T1, T2 \>, T3, ... \>
 */
template < typename, typename, typename = void >
struct __CommonFold {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template < typename __CurrentType, typename ... __RemainingTypes > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __CommonFold < __CurrentType, __CommonPack < __RemainingTypes ... >, Void < typename __CurrentType::Type > > :
    public meta::__impl::__Common < typename __CurrentType::Type, __RemainingTypes ... > {};

template < typename __CurrentType, typename __RemainingType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __CommonFold < __CurrentType, __RemainingType, void > {};
} /* namespace __commonImpl */

template < typename __T1, typename __T2 > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Common < __T1, __T2 > : public __commonImpl::__CommonDecayed < __T1, __T2 >::Type {};

template < typename __T1, typename __T2, typename ... __RemainingTypes > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __Common < __T1, __T2, __RemainingTypes ... > :
    public __commonImpl::__CommonFold < __Common < __T1, __T2 >, __commonImpl::__CommonPack < __RemainingTypes ... > > {};

template <typename __T>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MakeSigned {       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Type = typename std::make_signed <__T>::type;
};

template <typename __T>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MakeUnsigned {     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Type = typename std::make_unsigned <__T>::type;
};

template <typename __T, typename...__Args>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptConstructible : __Integral <std::is_nothrow_constructible <__T, __Args...>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptDefaultConstructible : __Integral <std::is_nothrow_default_constructible <__T>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptCopyConstructible : __Integral <std::is_nothrow_copy_constructible <__T>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptMoveConstructible : __Integral <std::is_nothrow_move_constructible <__T>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T, typename __Arg> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptAssignable : __Integral <std::is_nothrow_assignable <__T, __Arg>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptCopyAssignable : __Integral <std::is_nothrow_copy_assignable <__T>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IsNoexceptMoveAssignable : __Integral <std::is_nothrow_move_assignable <__T>> {};  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
} /* namespace __impl */

/**
 * @brief Meta-type used to obtain safe pass-by-value equivalent type of a given type
 * @tparam __T is the type for which to obtain a pass by value
 * @example decay will convert any rvalue type to a lvalue type <br/>
 * <pre>- Decay\<int\>            = int;</pre>
 * <pre>- Decay\<int &\>          = int;</pre>
 * <pre>- Decay\<int &&\>         = int; </pre>
 * <pre>- Decay\<int const &\>    = int; </pre>
 * @example decay will convert any array with extent type to a pointer type <br/>
 * <pre>- Decay\<int[2]\>         = int *; </pre>
 * @example decay will convert any function signature type to a function pointer for that signature type <br/>
 * <pre>- Decay\<int(int)\>       = int (*)(int); </pre>
 *
 * <small> It's obviously used to decay radioactive Atomic types into non-radioactive ones. </small>
 */
template <typename __T>                   using Decay     = typename __impl::__Decay <__T>::Type; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-type used to obtain the common, lvalue type that the given types can be converted to, if any
 * @tparam __TPack is the pack of types to find a common type for
 *
 * @example Possible results, cpp implementation defined <br/>
 * <pre>- Common \< int, float \> = float;</pre>
 * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
 * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
 * <pre>- Common \< String, uint64, float \> = String;</pre>
 */
template < typename ... __Ts >           using Common        = typename __impl::__Common < __Ts ... >::Type;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __T>                   using MakeSigned    = typename __impl::__MakeSigned <__T>::Type;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __T>                   using MakeUnsigned  = typename __impl::__MakeUnsigned <__T>::Type;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/**
 * @brief Meta-function used to check if two given types can be compared by less than operator (\<)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto lessThanPossible () noexcept -> bool {
  return __impl::__LessThanPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct LessThanPossible : __impl::__LessThanPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if two given types can be compared by greater than operator (\>)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto greaterThanPossible () noexcept -> bool {
  return __impl::__GreaterThanPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct GreaterThanPossible : __impl::__GreaterThanPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if two given types can be compared by less than or equal to operator (\<=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto lessThanOrEqualToPossible () noexcept -> bool {
  return __impl::__LessThanOrEqualToPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct LessThanOrEqualToPossible : __impl::__LessThanOrEqualToPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if two given types can be compared by greater than or equal to operator (\>=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto greaterThanOrEqualToPossible () noexcept -> bool {
  return __impl::__GreaterThanOrEqualToPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct GreaterThanOrEqualToPossible : __impl::__GreaterThanOrEqualToPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if two given types can be compared by equal to operator (==)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto equalToPossible () noexcept -> bool {
  return __impl::__EqualToPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct EqualToPossible : __impl::__EqualToPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if two given types can be compared by not equal to operator (!=)
 * @tparam __L is the first type
 * @tparam __R is the second type
 */
template <typename __L, typename __R> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto notEqualToPossible () noexcept -> bool {
  return __impl::__NotEqualToPossible < __L, __R >::value;
}

template <typename __L, typename __R = __L> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct NotEqualToPossible : __impl::__NotEqualToPossible <__L, __R> {};

/**
 * @brief Meta-function used to check if a given type is printable ( std::ostream << type )
 * @tparam __T is the type for which printability is checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isPrintable () noexcept -> bool {
  return __impl::__IsPrintable <__T>::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsPrintable : __impl::__IsPrintable <__T> {};

/**
 * @brief Meta-function used to check if a given type is a base class of another given type
 * @tparam __BaseType is the type given as a base class
 * @tparam __DerivedType is the type given as a derived class
 */
template < typename __BaseType, typename __DerivedType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isBaseFor () noexcept -> bool {
  return __impl::__IsBaseOf < __BaseType, __DerivedType >::value;
}

template <typename __BaseType, typename __DerviedType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsBaseFor : __impl::__IsBaseOf <__BaseType, __DerviedType> {};

/**
 * @brief Meta-function used to check if a given type is derived from another given type
 * @tparam __DerivedType is the type given as a derived class
 * @tparam __BaseType is the type given as a base class
 */
template < typename __DerivedType, typename __BaseType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isDerivedFrom () noexcept -> bool {
  return __impl::__IsBaseOf < __BaseType, __DerivedType >::value;
}

template <typename __DerivedType, typename __BaseType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsDerivedFrom : __impl::__IsBaseOf <__BaseType, __DerivedType> {};

/**
 * @brief Meta-function used to check if a given type is derived from the Object base type
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isObjectDerived () noexcept -> bool {
  return isDerivedFrom < __T, Object > ();
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsObjectDerived : IsDerivedFrom <__T, Object> {};

/**
 * @brief Meta-function used to check if a given type is a smart-pointer type = derived from SmartPointer type
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isSmartPointer () noexcept -> bool {
  return __impl::__IsSmartPointer <__T>::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsSmartPointer : __impl::__IsSmartPointer <__T> {};

/**
 * @brief Meta-function used to check if a given type is a basic or smart pointer type
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isPointer () noexcept -> bool {
  return isBasicPointer <__T> () || isSmartPointer <__T> ();
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsPointer : Or <__impl::__IsSmartPointer <__T>, IsBasicPointer <__T>> {};

/**
 * @brief Meta-function used to check if a given type is a Pair type
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isPair () noexcept -> bool {
  return __impl::__IsPair <__T>::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsPair : __impl::__IsPair <__T> {};

/**
 * @brief Meta-function used to check if a given type is a member of an object
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isMemberObjectPointer () noexcept -> bool {
  return __impl::__IsMemberObjectPointer <__T>::value;
}

template <typename __T, typename __C = void> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMemberObjectPointer : __impl::__IsMemberObjectPointer <__T, __C> {};

/**
 * @brief Meta-function used to check if a given type is a member function of an object
 * @tparam __T is the type checked
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isMemberFunctionPointer () noexcept -> bool {
  return __impl::__IsMemberFunctionPointer <__T>::value;
}

template <typename __T, typename __C = void> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMemberFunctionPointer : __impl::__IsMemberFunctionPointer <__T, __C> {};

/**
 * @brief Meta-function used to check if a given type is a member of a given object
 * @tparam __T is the type checked
 * @tparam __C is the object of which T should be a member of
 */
template <typename __T, typename __C> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isMemberObjectPointer () noexcept -> bool {
  return __impl::__IsMemberObjectPointer < __T, __C >::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMemberObjectPointer <__T> : __impl::__IsMemberObjectPointer <__T> {};

/**
 * @brief Meta-function used to check if a given type is a member function of a given object
 * @tparam __T is the type checked
 * @tparam __C is the object of which T should be a member function of
 */
template <typename __T, typename __C> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isMemberFunctionPointer () noexcept -> bool {
  return __impl::__IsMemberFunctionPointer < __T, __C >::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsMemberFunctionPointer <__T> : __impl::__IsMemberFunctionPointer <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr static auto name () noexcept -> StringLiteral {
  return meta::__impl::__TypeParseTraits <__T>::name;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto indirectionPossible () noexcept -> bool {
  return __impl::__IndirectionPossible <__T>::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto prefixIncrementPossible () noexcept -> bool {
  return __impl::__PrefixIncrementPossible <__T>::value;
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto isIterator () noexcept -> bool {
  return
      indirectionPossible <__T> () &&
      prefixIncrementPossible <__T> () &&
      notEqualToPossible < __T, __T > ();
}

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IndirectionPossible : __impl::__IndirectionPossible <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct PrefixIncrementPossible : __impl::__PrefixIncrementPossible <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsIterator : And <
    IndirectionPossible <__T>,
    PrefixIncrementPossible <__T>,
    NotEqualToPossible <__T>
> {};

template <typename __T, typename...__Args>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptConstructible : __impl::__IsNoexceptConstructible <__T, __Args...> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptDefaultConstructible : __impl::__IsNoexceptDefaultConstructible <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptCopyConstructible : __impl::__IsNoexceptCopyConstructible <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptMoveConstructible : __impl::__IsNoexceptMoveConstructible <__T> {};

template <typename __T, typename __Arg> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptAssignable : __impl::__IsNoexceptAssignable <__T, __Arg> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptCopyAssignable : __impl::__IsNoexceptCopyAssignable <__T> {};

template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct IsNoexceptMoveAssignable : __impl::__IsNoexceptMoveAssignable <__T> {};

/**
 * @brief Meta-function used to invoke the most appropriate comparison function between two values
 * @tparam __L is the type to the left side of the == comparison
 * @tparam __R is the type to the right side of the == comparison
 *
 * @example
 * <ul>
 *      <li>If == comparison is possible, invoke ==</li>
 *      <li>If == comparison is not possible, but LeftType is ObjectDerived and RightType is ObjectDerived, invoke Object::equals</li>
 *      <li>If == comparison is not possible and LeftType is not ObjectDerived and RightType is not ObjectDerived, invoke comparison by address</li>
 * </ul>
 */
template <
    typename __L,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __R = __L,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    EnableIf <
        equalToPossible < __L, __R > ()
    > = 0
> constexpr auto equals (
    __L  const & left,
    __R const & right
) noexcept -> bool {

  return left == right;
}


template <
    typename __L,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __R = __L,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    EnableIf <
        ! equalToPossible < __L, __R > ()    &&
        isDerivedFrom < __L, Object > ()             &&
        isDerivedFrom < __R, Object > ()
    > = 0
> constexpr auto equals (
    __L  const & left,
    __R const & right
) noexcept -> bool {

  return left.equals ( right );
}


template <
    typename __L,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __R = __L,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    EnableIf <
        ! equalToPossible < __L, __R > () && ! (
            isDerivedFrom < __L, Object > ()     &&
            isDerivedFrom < __R, Object > ()
        )
    > = 0
> constexpr auto equals (
    __L  const & left,
    __R const & right
) noexcept -> bool {

  return & left == & right;
}


template < typename __T, meta::EnableIf < isPrintable <__T> () > = 0 > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto print (
    std::ostream        & out,
    __T             const & object
) noexcept -> std::ostream & {

  return ( out << object );
}


template < typename __T, meta::EnableIf < ! isPrintable <__T> () > = 0 > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto print (
    std::ostream            & out,
    __T                 const & object
) noexcept -> std::ostream & {

  return ( out << "Unknown@" << std::hex << ( & object ) );
}


/**
 * @brief Meta-object helper, containing utilities for a given type. Alternative to above functions
 * @tparam __T type given for which to access meta functions
 */
template <typename __T> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct Type {

  using BaseType = __T;

  using RemoveConst           = meta::RemoveConst <__T>;
  using RemoveVolatile        = meta::RemoveVolatile <__T>;
  using RemoveReference       = meta::RemoveReference <__T>;
  using RemoveConstVolatile   = meta::RemoveConstVolatile <__T>;
  using RemovePointer         = meta::RemovePointer <__T>;

  template < typename __U > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isSame () noexcept -> bool {
    return meta::isSame < __T, __U > ();
  }

  constexpr static auto hasEqualTo () noexcept -> bool {
    return meta::equalToPossible < __T, __T > ();
  }

  constexpr static auto hasNotEqualTo () noexcept -> bool {
    return meta::notEqualToPossible < __T, __T > ();
  }

  constexpr static auto hasLessThan () noexcept -> bool {
    return meta::lessThanPossible < __T, __T > ();
  }

  constexpr static auto hasGreaterThan () noexcept -> bool {
    return meta::greaterThanPossible < __T, __T > ();
  }

  constexpr static auto hasLessThanOrEqual () noexcept -> bool {
    return meta::lessThanOrEqualToPossible < __T, __T > ();
  }

  constexpr static auto hasGreaterThanOrEqual () noexcept -> bool {
    return meta::greaterThanOrEqualToPossible < __T, __T > ();
  }

  constexpr static auto isPrintable () noexcept -> bool {
    return meta::isPrintable <__T> ();
  }

  constexpr static auto isEnum () noexcept -> bool {
    return meta::isEnum <__T> ();
  }

  constexpr static auto isClass () noexcept -> bool {
    return meta::isEnum <__T> ();
  }

  constexpr static auto isUnion () noexcept -> bool {
    return meta::isUnion <__T> ();
  }

  constexpr static auto isFunction () noexcept -> bool {
    return meta::isFunction <__T> ();
  }

  constexpr static auto isStaticFunction () noexcept -> bool {
    return meta::isStaticFunction <__T> ();
  }

  constexpr static auto isObjectFunction () noexcept -> bool {
    return meta::isObjectFunction <__T> ();
  }

  constexpr static auto isFundamental () noexcept -> bool {
    return meta::isFundamental <__T> ();
  }

  constexpr static auto isIntegral () noexcept -> bool {
    return meta::isIntegral <__T> ();
  }

  constexpr static auto isArithmetic () noexcept -> bool {
    return meta::isArithmetic <__T> ();
  }

  constexpr static auto isPrimitive () noexcept -> bool {
    return meta::isFundamental <__T> ();
  }

  template < typename __DerivedType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isBaseFor () noexcept -> bool {
    return meta::isBaseFor < __T, __DerivedType > ();
  }

  template < typename __BaseType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isDerivedFrom () noexcept -> bool {
    return meta::isDerivedFrom < __T, __BaseType > ();
  }

  constexpr static auto isDefaultConstructible () noexcept -> bool {
    return meta::isDefaultConstructible <__T> ();
  }

  constexpr static auto isCopyConstructible () noexcept -> bool {
    return meta::isCopyConstructible <__T> ();
  }

  constexpr static auto isMoveConstructible () noexcept -> bool {
    return meta::isMoveConstructible <__T> ();
  }

  constexpr static auto isCopyAssignable () noexcept -> bool {
    return meta::isCopyAssignable <__T> ();
  }

  constexpr static auto isMoveAssignable () noexcept -> bool {
    return meta::isMoveAssignable <__T> ();
  }

  constexpr static auto isCallable () noexcept -> bool {
    return meta::isCallable <__T> ();
  }

  constexpr static auto isArray () noexcept -> bool {
    return meta::isArray <__T> ();
  }

  template < Size __size >                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isArray () noexcept -> bool {
    return meta::isArray < __T[__size] > ();  /* NOLINT(*-avoid-c-arrays) */
  }

  constexpr static auto isPointer () noexcept -> bool {
    return meta::isPointer <__T> ();
  }

  constexpr static auto isBasicPointer () noexcept -> bool {
    return meta::isBasicPointer <__T> ();
  }

  constexpr static auto isSmartPointer () noexcept -> bool {
    return meta::isSmartPointer <__T> ();
  }

  constexpr static auto isLValueReference () noexcept -> bool {
    return meta::isLValueReference <__T> ();
  }

  constexpr static auto isRValueReference () noexcept -> bool {
    return meta::isRValueReference <__T> ();
  }

  constexpr static auto isReference () noexcept -> bool {
    return meta::isReference <__T> ();
  }

  constexpr static auto isMoveReference () noexcept -> bool {
    return meta::isMoveReference <__T> ();
  }

  constexpr static auto isMemberObjectPointer () noexcept -> bool {
    return meta::isMemberObjectPointer <__T> ();
  }

  constexpr static auto isMemberFunctionPointer () noexcept -> bool {
    return meta::isMemberFunctionPointer <__T> ();
  }

  template < typename __C > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isMemberObjectPointer () noexcept -> bool {
    return meta::isMemberObjectPointer < __T, __C > ();
  }

  template < typename __C > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static auto isMemberFunctionPointer () noexcept -> bool {
    return meta::isMemberFunctionPointer < __T, __C > ();
  }

  constexpr static auto name () noexcept -> StringLiteral {
    return meta::name <__T> ();
  }

  constexpr static auto isConst () noexcept -> bool {
    return meta::isConst <__T> ();
  }

  constexpr static auto isVolatile () noexcept -> bool {
    return meta::isVolatile <__T> ();
  }
};

} /* namespace meta */
} /* namespace cds */

#define __CDS_Meta_RegisterParseType(_type)                                             \
namespace cds {                                                                         \
    namespace meta {                                                                    \
        namespace __impl {                                                              \
            template <>                                                                 \
            struct __TypeParseTraits < _type > {                                        \
                constexpr static StringLiteral name = # _type;                          \
            };                                                                          \
        }                                                                               \
    }                                                                                   \
                                                                                        \
}

#define __CDS_Meta_RegisterParseTemplateType(_type)                                             \
namespace cds {                                                                                 \
    namespace meta {                                                                            \
        namespace __impl {                                                                      \
            template < typename ... Types >                                                     \
            struct __TypeParseTraits < _type < Types ... > > {                                  \
                constexpr static StringLiteral name = # _type;                                  \
            };                                                                                  \
        }                                                                                       \
    }                                                                                           \
                                                                                                \
}

__CDS_Meta_RegisterParseType ( sint8 )
__CDS_Meta_RegisterParseType ( sint16 )
__CDS_Meta_RegisterParseType ( sint32 )
__CDS_Meta_RegisterParseType ( sint64 )

__CDS_Meta_RegisterParseType ( uint8 )
__CDS_Meta_RegisterParseType ( uint16 )
__CDS_Meta_RegisterParseType ( uint32 )
__CDS_Meta_RegisterParseType ( uint64 )

__CDS_Meta_RegisterParseType ( void )
__CDS_Meta_RegisterParseType ( bool )
__CDS_Meta_RegisterParseType ( float )
__CDS_Meta_RegisterParseType ( double )

#endif /* __CDS_META_TYPE_TRAITS_HPP__ */
