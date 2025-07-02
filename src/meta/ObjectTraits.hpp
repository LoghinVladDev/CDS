//
// Created by loghin on 12/5/23.
//

#ifndef CDS_META_OBJECT_TRAITS_HPP
#define CDS_META_OBJECT_TRAITS_HPP
#pragma once

#include <cds/meta/TypeTraits>

namespace cds {
namespace meta {
namespace impl {
template <typename T, template <typename...> class, typename, typename = typename IsComplete<T>::Type>
struct IfCompleteCheckIf : False {};

template <typename T, template <typename> class P, typename... A> struct IfCompleteCheckIf<T, P, Pack<A...>, True> :
    P<A...> {};

template <typename T> struct IsTriviallyCopyable : ConvertIntegral<std::is_trivially_copyable<T>> {};
template <typename T, typename... A> struct IsTriviallyConstructible :
    ConvertIntegral<std::is_trivially_constructible<T, A...>> {};

template <typename T, typename A> struct IsTriviallyAssignable :
    ConvertIntegral<std::is_trivially_assignable<meta::AddLValRef<T>, A>> {};

template <typename T> struct IsTriviallyDestructible : ConvertIntegral<std::is_trivially_destructible<T>> {};

template <typename T> struct IsTriviallyDefaultConstructible :
    ConvertIntegral<std::is_trivially_default_constructible<T>> {};

template <typename T> struct IsTriviallyCopyConstructible : ConvertIntegral<std::is_trivially_copy_constructible<T>> {};
template <typename T> struct IsTriviallyMoveConstructible : ConvertIntegral<std::is_trivially_move_constructible<T>> {};

template <typename T> struct IsDefaultConstructible :
    ConvertIntegral<std::is_default_constructible<T>> {};

template <typename T> struct IsCopyConstructible :
    ConvertIntegral<std::is_copy_constructible<T>> {};

template <typename T> struct IsMoveConstructible : ConvertIntegral<std::is_move_constructible<T>> {};

template <typename T, typename... A> struct IsConstructible :
    ConvertIntegral<std::is_constructible<T, A...>> {};

template <typename T> struct IsDestructible : ConvertIntegral<std::is_destructible<T>> {};

template <typename T, typename = typename IsDefaultConstructible<T>::Type> struct IsNoexceptDefaultConstructible :
    meta::False {};

template <typename T, typename = typename IsCopyConstructible<T>::Type> struct IsNoexceptCopyConstructible :
    meta::False {};

template <typename T, typename = typename IsMoveConstructible<T>::Type> struct IsNoexceptMoveConstructible :
    meta::False {};

template <typename, typename> struct IsConstructiblePackVariant : meta::False {};
template <typename T, typename... Args> struct IsConstructiblePackVariant<T, Pack<Args...>> :
    IsConstructible<T, Args...> {};

template <typename T, typename APack, typename = typename IsConstructiblePackVariant<T, APack>::Type>
struct IsNoexceptConstructiblePackVariant : meta::False {};

template <typename T, typename... Args> struct IsNoexceptConstructiblePackVariant<T, Pack<Args...>, meta::True> :
    Bool<noexcept(T(meta::value<Args>()...))> {};

template <typename T, typename... Args> struct IsNoexceptConstructible :
    IsNoexceptConstructiblePackVariant<T, Pack<Args...>> {};

template <typename T> struct IsNoexceptDefaultConstructible<T, meta::True> : Bool<noexcept(T())> {};
template <typename T> struct IsNoexceptCopyConstructible<T, meta::True> : Bool<noexcept(T(meta::lvalue<T const>()))> {};
template <typename T> struct IsNoexceptMoveConstructible<T, meta::True> : Bool<noexcept(T(meta::rvalue<T>()))> {};

template <typename T, typename = T, typename = void> struct IsAssignable : meta::False {};
template <typename T, typename P>
struct IsAssignable<T, P, Void<decltype(meta::lvalue<T>() = meta::rvalue<P>())>> : meta::True {};

template <typename T, typename = T, typename = T&, typename = void> struct IsAssignableAndReturns : meta::False {};
template <typename T, typename P, typename R>
struct IsAssignableAndReturns<T, P, R, Void<decltype(meta::lvalue<T>() = meta::rvalue<P>())>> :
    meta::IsSame<decltype(meta::lvalue<T>() = meta::rvalue<P>()), R>::Type {};

template <typename T> struct IsCopyAssignable : ConvertIntegral<std::is_copy_assignable<T>> {};
template <typename T> struct IsMoveAssignable : ConvertIntegral<std::is_move_assignable<T>> {};
template <typename T> struct IsTriviallyCopyAssignable : ConvertIntegral<std::is_trivially_copy_assignable<T>> {};
template <typename T> struct IsTriviallyMoveAssignable : ConvertIntegral<std::is_trivially_move_assignable<T>> {};

template <typename T, typename = typename IsCopyAssignable<T>::Type> struct IsNoexceptCopyAssignable
    : meta::False {};

template <typename T, typename = typename IsMoveAssignable<T>::Type> struct IsNoexceptMoveAssignable
    : meta::False {};

template <typename T> struct IsNoexceptCopyAssignable<T, meta::True>
    : Bool<noexcept(meta::lvalue<T>() = meta::lvalue<T const>())> {};

template <typename T> struct IsNoexceptMoveAssignable<T, meta::True>
    : Bool<noexcept(meta::lvalue<T>() = meta::rvalue<T>())> {};

template <typename T, typename A, typename = typename IsAssignable<T, A>::Type>
struct IsNoexceptAssignable {};

template <typename T, typename A> struct IsNoexceptAssignable<T, A, False> : meta::False {};
template <typename T, typename A> struct IsNoexceptAssignable<T, A, True>
    : Bool<noexcept(lvalue<T>() = meta::rvalue<A>())> {};

template <typename T, typename A, typename R, typename = typename IsAssignableAndReturns<T, A, R>::Type>
struct IsNoexceptAssignableAndReturns {};

template <typename T, typename A, typename R> struct IsNoexceptAssignableAndReturns<T, A, R, False> : meta::False {};
template <typename T, typename A, typename R> struct IsNoexceptAssignableAndReturns<T, A, R, True> :
    Bool<noexcept(lvalue<T>() = meta::rvalue<A>())> {};

template <typename T, typename = T, typename = void> struct IsAddCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsSubCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsMulCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsDivCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsModCompatible : meta::False {};
template <typename, typename = void> struct IsPrefixIncrementable : meta::False {};
template <typename, typename = void> struct IsPostfixIncrementable : meta::False {};
template <typename, typename = void> struct IsPrefixDecrementable : meta::False {};
template <typename, typename = void> struct IsPostfixDecrementable : meta::False {};

template <typename T, typename = T, typename = void> struct IsLtCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsLeCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsGtCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsGeCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsEqCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNeCompatible : meta::False {};

template <typename T, typename = T, typename = void> struct IsNoexceptLtCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptLeCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptGtCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptGeCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptEqCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptNeCompatible : meta::False {};
#if CDS_ATTR(spaceship)
template <typename T, typename = T, typename = void> struct IsSpaceshipCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsNoexceptSpaceshipCompatible : meta::False {};
#endif

template <typename, typename = void> struct IsNotCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsAndCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsOrCompatible : meta::False {};

template <typename, typename = void> struct IsBitwiseNotCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseAndCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseOrCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseXorCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseLshCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseRshCompatible : meta::False {};

template <typename T, typename = T, typename = void> struct IsAddAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsSubAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsMulAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsDivAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsModAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseAndAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseOrAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseXorAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseLshAssignCompatible : meta::False {};
template <typename T, typename = T, typename = void> struct IsBitwiseRshAssignCompatible : meta::False {};

template <typename, typename = int, typename = void> struct IsSubscriptCompatible : meta::False {};
template <typename, typename = void> struct IsIndirectionCompatible : meta::False {};
template <typename, typename = void> struct IsAddressOfCompatible : meta::False {};

template <typename T, typename R> struct IsAddCompatible<T, R, Void<decltype(meta::rvalue<T>() + meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsSubCompatible<T, R, Void<decltype(meta::rvalue<T>() - meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsMulCompatible<T, R, Void<decltype(meta::rvalue<T>() * meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsDivCompatible<T, R, Void<decltype(meta::rvalue<T>() / meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsModCompatible<T, R, Void<decltype(meta::rvalue<T>() % meta::rvalue<R>())>> :
    meta::True {};

template <typename T> struct IsPrefixIncrementable<T, Void<decltype(++meta::lvalue<T>())>> : meta::True {};
template <typename T> struct IsPostfixIncrementable<T, Void<decltype(meta::lvalue<T>()++)>> : meta::True {};
template <typename T> struct IsPrefixDecrementable<T, Void<decltype(--meta::lvalue<T>())>> : meta::True {};
template <typename T> struct IsPostfixDecrementable<T, Void<decltype(meta::lvalue<T>()--)>> : meta::True {};

template <> struct IsPrefixIncrementable<bool> : meta::False {};
template <> struct IsPostfixIncrementable<bool> : meta::False {};

template <typename T, typename R> struct IsLtCompatible<T, R, Void<decltype(meta::rvalue<T>() < meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsLeCompatible<T, R, Void<decltype(meta::rvalue<T>() <= meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsGtCompatible<T, R, Void<decltype(meta::rvalue<T>() > meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsGeCompatible<T, R, Void<decltype(meta::rvalue<T>() >= meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsEqCompatible<T, R, Void<decltype(meta::rvalue<T>() == meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsNeCompatible<T, R, Void<decltype(meta::rvalue<T>() != meta::rvalue<R>())>> :
    meta::True {};

template <typename L, typename R> struct IsNoexceptLtCompatible<L, R, Void<decltype(rvalue<L>() < rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<L>() < rvalue<R>())> {};

template <typename L, typename R> struct IsNoexceptGtCompatible<L, R, Void<decltype(rvalue<L>() > rvalue<R>())>> :
    meta::Bool<noexcept((rvalue<L>() > rvalue<R>()))> {};

template <typename L, typename R> struct IsNoexceptLeCompatible<L, R, Void<decltype(rvalue<L>() <= rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<L>() <= rvalue<R>())> {};

template <typename L, typename R> struct IsNoexceptGeCompatible<L, R, Void<decltype(rvalue<L>() >= rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<L>() >= rvalue<R>())> {};

template <typename L, typename R> struct IsNoexceptEqCompatible<L, R, Void<decltype(rvalue<L>() == rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<L>() == rvalue<R>())> {};

template <typename L, typename R> struct IsNoexceptNeCompatible<L, R, Void<decltype(rvalue<L>() != rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<L>() != rvalue<R>())> {};

#if CDS_ATTR(spaceship)
template <typename T, typename R>
struct IsSpaceshipCompatible<T, R, Void<decltype(meta::rvalue<T>() <=> meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsNoexceptSpaceshipCompatible<T, R, Void<decltype(meta::rvalue<T>() <=> meta::rvalue<R>())>> :
    meta::Bool<noexcept(rvalue<T>() <=> rvalue<R>())> {};
#endif

template <typename T> struct IsNotCompatible<T, Void<decltype(!meta::rvalue<T>())>> : meta::True {};
template <typename T, typename R> struct IsAndCompatible<T, R, Void<decltype(meta::rvalue<T>() && meta::rvalue<R>())>> :
    meta::True {};

template <typename T, typename R> struct IsOrCompatible<T, R, Void<decltype(meta::rvalue<T>() || meta::rvalue<R>())>> :
    meta::True {};

template <typename T> struct IsBitwiseNotCompatible<T, Void<decltype(~meta::rvalue<T>())>> : meta::True {};

template <typename T, typename R>
struct IsBitwiseAndCompatible<T, R, Void<decltype(meta::rvalue<T>() & meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsBitwiseOrCompatible<T, R, Void<decltype(meta::rvalue<T>() | meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsBitwiseXorCompatible<T, R, Void<decltype(meta::rvalue<T>() ^ meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsBitwiseLshCompatible<T, R, Void<decltype(meta::rvalue<T>() << meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsBitwiseRshCompatible<T, R, Void<decltype(meta::rvalue<T>() >> meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsAddAssignCompatible<T, R, Void<decltype(meta::lvalue<T>() += meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsSubAssignCompatible<T, R, Void<decltype(meta::lvalue<T>() -= meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsMulAssignCompatible<T, R, Void<decltype(meta::lvalue<T>() *= meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsDivAssignCompatible<T, R, Void<decltype(meta::lvalue<T>() /= meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R>
struct IsModAssignCompatible<T, R, Void<decltype(meta::lvalue<T>() %= meta::rvalue<R>())>> : meta::True {};

template <typename T, typename R> struct IsBitwiseAndAssignCompatible<
    T, R, Void<decltype(meta::lvalue<T>() &= meta::rvalue<R>())>
> : meta::True {};

template <typename T, typename R> struct IsBitwiseOrAssignCompatible<
    T, R, Void<decltype(meta::lvalue<T>() |= meta::rvalue<R>())>
> : meta::True {};

template <typename T, typename R> struct IsBitwiseXorAssignCompatible<
    T, R, Void<decltype(meta::lvalue<T>() ^= meta::rvalue<R>())>
> : meta::True {};

template <typename T, typename R> struct IsBitwiseLshAssignCompatible<
    T, R, Void<decltype(meta::lvalue<T>() <<= meta::rvalue<R>())>
> : meta::True {};

template <typename T, typename R> struct IsBitwiseRshAssignCompatible<
    T, R, Void<decltype(meta::lvalue<T>() >>= meta::rvalue<R>())>
> : meta::True {};


template <typename T, typename I>
struct IsSubscriptCompatible<T, I, Void<decltype(meta::lvalue<T>()[meta::rvalue<I>()])>> : meta::True {};

template <typename T> struct IsIndirectionCompatible<T, Void<decltype(*meta::rvalue<T>())>> : meta::True {};
template <typename T> struct IsAddressOfCompatible<T, Void<decltype(&meta::lvalue<T>())>> : meta::True {};

template <typename B, typename D> struct IsBaseOf : meta::And<
    meta::All<meta::IsClass, B, D>,
    typename meta::IsConvertible<D*, B*>::Type
> {};

namespace intrusiveBaseOf {
template <typename B> auto intrusiveBaseCast(B const volatile*) -> True;
template <typename> auto intrusiveBaseCast(void const volatile*) -> False;
template <typename B, typename D> auto testBaseOfIntrusively(int) ->
    decltype(intrusiveBaseCast<B>(rvalue<D*>()));
template <typename, typename> auto testBaseOfIntrusively(...) -> True;
} // namespace intrusiveBaseOf

template <typename B, typename D> struct IsBaseOfIntrusive : meta::And<
    meta::All<meta::IsClass, B, D>,
    decltype(intrusiveBaseOf::testBaseOfIntrusively<B, D>(0))
> {};

template <typename B, typename D> struct IsBaseOfIntrusiveICVR : meta::And<
    meta::All<meta::IsClass, RemoveCVRef<B>, RemoveCVRef<D>>,
    decltype(intrusiveBaseOf::testBaseOfIntrusively<RemoveCVRef<B>, RemoveCVRef<D>>(0))
> {};

template <typename> struct Member {};
template <typename T, typename C> struct Member<T C::*> { using Type = T; };

template <typename> struct IsMember : False {};
template <typename T, typename C> struct IsMember<T C::*> : True {};

template <typename T> struct IsCallableObject {
  struct Fallback { auto operator()() -> void; };
  struct Resolver : T, Fallback {};
  template <typename O, O> struct check;
  template <typename> static auto test(...) noexcept -> True;
  template <typename C> static auto test(check<void (Fallback::*)(), &C::operator()> const*) noexcept -> False;
  using Type = decltype(test<Resolver>(nullptr));
};
} // namespace impl

template <typename Type> struct IsTriviallyCopyable : impl::IsTriviallyCopyable<Type>::Type {};
template <typename Type, typename... Arguments> struct IsTriviallyConstructible :
    impl::IsTriviallyConstructible<Type, Arguments...>::Type {};

template <typename Type, typename Argument> struct IsTriviallyAssignable :
    impl::IsTriviallyAssignable<Type, Argument>::Type {};

template <typename Type> struct IsTriviallyDestructible : impl::IsTriviallyDestructible<Type>::Type {};
template <typename Type> struct IsTriviallyDefaultConstructible : impl::IsTriviallyDefaultConstructible<Type>::Type {};
template <typename Type> struct IsTriviallyCopyConstructible : impl::IsTriviallyCopyConstructible<Type>::Type {};
template <typename Type> struct IsTriviallyMoveConstructible : impl::IsTriviallyMoveConstructible<Type>::Type {};
template <typename Type> struct IsTriviallyCopyAssignable : impl::IsTriviallyCopyAssignable<Type>::Type {};
template <typename Type> struct IsTriviallyMoveAssignable : impl::IsTriviallyMoveAssignable<Type>::Type {};
template <typename Type> struct IsDefaultConstructible : impl::IsDefaultConstructible<Type>::Type {};
template <typename Type> struct IsCopyConstructible : impl::IsCopyConstructible<Type>::Type {};
template <typename Type> struct IsMoveConstructible : impl::IsMoveConstructible<Type>::Type {};
template <typename Type> struct IsCopyAssignable : impl::IsCopyAssignable<Type>::Type {};
template <typename Type> struct IsMoveAssignable : impl::IsMoveAssignable<Type>::Type {};
template <typename Type, typename... Arguments> struct IsConstructible :
    impl::IsConstructible<Type, Arguments...>::Type {};
template <typename Type> struct IsDestructible : impl::IsDestructible<Type>::Type {};

template <typename Type> struct IsNoexceptDefaultConstructible : impl::IsNoexceptDefaultConstructible<Type>::Type {};
template <typename Type> struct IsNoexceptCopyConstructible : impl::IsNoexceptCopyConstructible<Type>::Type {};
template <typename Type> struct IsNoexceptMoveConstructible : impl::IsNoexceptMoveConstructible<Type>::Type {};
template <typename Type> struct IsNoexceptCopyAssignable : impl::IsNoexceptCopyAssignable<Type>::Type {};
template <typename Type> struct IsNoexceptMoveAssignable : impl::IsNoexceptMoveAssignable<Type>::Type {};
template <typename Type, typename... Arguments> struct IsNoexceptConstructible :
    impl::IsNoexceptConstructible<Type, Arguments...>::Type {};

template <typename Type, typename Param = Type, typename Return = void> struct IsAssignable :
    impl::IsAssignableAndReturns<Type, Param, Return>::Type {};

template <typename Type, typename Param> struct IsAssignable<Type, Param, void> :
    impl::IsAssignable<Type, Param>::Type {};

template <typename Type, typename Param = Type, typename Return = void> struct IsNoexceptAssignable :
    impl::IsNoexceptAssignableAndReturns<Type, Param, Return>::Type {};

template <typename Type, typename Param> struct IsNoexceptAssignable<Type, Param, void> :
    impl::IsNoexceptAssignable<Type, Param>::Type {};

template <typename Type, typename With = Type> struct IsAddCompatible : impl::IsAddCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsSubCompatible : impl::IsSubCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsMulCompatible : impl::IsMulCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsDivCompatible : impl::IsDivCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsModCompatible : impl::IsModCompatible<Type, With>::Type {};

template <typename Type> struct IsPrefixIncrementable : impl::IsPrefixIncrementable<Type>::Type {};
template <typename Type> struct IsPostfixIncrementable : impl::IsPostfixIncrementable<Type>::Type {};
template <typename Type> struct IsPrefixDecrementable : impl::IsPrefixDecrementable<Type>::Type {};
template <typename Type> struct IsPostfixDecrementable : impl::IsPostfixDecrementable<Type>::Type {};

template <typename Type, typename With = Type> struct IsLtCompatible : impl::IsLtCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsLeCompatible : impl::IsLeCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsGtCompatible : impl::IsGtCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsGeCompatible : impl::IsGeCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsEqCompatible : impl::IsEqCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsNeCompatible : impl::IsNeCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptLtCompatible :
    impl::IsNoexceptLtCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptLeCompatible :
    impl::IsNoexceptLeCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptGtCompatible :
    impl::IsNoexceptGtCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptGeCompatible :
    impl::IsNoexceptGeCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptEqCompatible :
    impl::IsNoexceptEqCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptNeCompatible :
    impl::IsNoexceptNeCompatible<Type, With>::Type {};

#if CDS_ATTR(spaceship)
template <typename Type, typename With = Type> struct IsSpaceshipCompatible :
    impl::IsSpaceshipCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNoexceptSpaceshipCompatible :
    impl::IsNoexceptSpaceshipCompatible<Type, With>::Type {};
#endif

template <typename Type> struct IsNotCompatible : impl::IsNotCompatible<Type>::Type {};
template <typename Type, typename With = Type> struct IsAndCompatible : impl::IsAndCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsOrCompatible : impl::IsOrCompatible<Type, With>::Type {};
template <typename Type> struct IsBitwiseNotCompatible : impl::IsBitwiseNotCompatible<Type>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseAndCompatible :
    impl::IsBitwiseAndCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseOrCompatible :
    impl::IsBitwiseOrCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseXorCompatible :
    impl::IsBitwiseXorCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseLshCompatible :
    impl::IsBitwiseLshCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseRshCompatible :
    impl::IsBitwiseRshCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsAddAssignCompatible :
    impl::IsAddAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsSubAssignCompatible :
    impl::IsSubAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsMulAssignCompatible :
    impl::IsMulAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsDivAssignCompatible :
    impl::IsDivAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsModAssignCompatible :
    impl::IsModAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseAndAssignCompatible :
    impl::IsBitwiseAndAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseOrAssignCompatible :
    impl::IsBitwiseOrAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseXorAssignCompatible :
    impl::IsBitwiseXorAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseLshAssignCompatible :
    impl::IsBitwiseLshAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseRshAssignCompatible :
    impl::IsBitwiseRshAssignCompatible<Type, With>::Type {};

template <typename Type, typename Index = int> struct IsSubscriptCompatible :
    impl::IsSubscriptCompatible<Type, Index>::Type {};

template <typename Type> struct IsIndirectionCompatible : impl::IsIndirectionCompatible<Type>::Type {};
template <typename Type> struct IsAddressOfCompatible : impl::IsAddressOfCompatible<Type>::Type {};

template <typename Base, typename Derived> struct IsBaseOf : impl::IsBaseOf<Base, Derived>::Type {};
template <typename Derived, typename Base> struct IsDerivedFrom : impl::IsBaseOf<Base, Derived>::Type {};
template <typename MemberType> using Member = typename impl::Member<MemberType>::Type;

template <typename Type> struct IsCallableObject :
    Conditional<IsClass<Type>, impl::IsCallableObject<Type>, False>::Type {};

template <typename Type> struct IsMember : impl::IsMember<Type>::Type {};

template <typename Type> struct IsCallable :
    And<Not<IsMember<Type>>, Or<IsCallableObject<Type>, IsFunction<RemovePointer<Type>>>> {};
} // namespace meta
} // namespace cds

#endif // CDS_META_OBJECT_TRAITS_HPP
