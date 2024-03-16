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
template <typename T> struct IsTriviallyCopyAssignable : ConvertIntegral<std::is_trivially_copy_assignable<T>> {};
template <typename T> struct IsTriviallyMoveAssignable : ConvertIntegral<std::is_trivially_move_assignable<T>> {};
template <typename T> struct IsDefaultConstructible : ConvertIntegral<std::is_default_constructible<T>> {};
template <typename T> struct IsCopyConstructible : ConvertIntegral<std::is_copy_constructible<T>> {};
template <typename T> struct IsMoveConstructible : ConvertIntegral<std::is_move_constructible<T>> {};
template <typename T, typename... A> struct IsConstructible : ConvertIntegral<std::is_constructible<T, A...>> {};

template <typename T, typename = T, typename = T&, typename = void> struct IsAssignable : meta::False {};
template <typename T, typename P, typename R>
struct IsAssignable<T, P, R, Void<decltype(meta::lvalue<T>() = meta::rvalue<P>())>> :
    meta::IsSame<decltype(meta::lvalue<T>() = meta::rvalue<P>()), R>::Type {};

template <typename T> struct IsCopyAssignable : ConvertIntegral<std::is_copy_assignable<T>> {};
template <typename T> struct IsMoveAssignable : ConvertIntegral<std::is_move_assignable<T>> {};

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
#if CDS_ATTR(spaceship)
template <typename T, typename = T, typename = void> struct IsSpaceshipCompatible : meta::False {};
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

#if CDS_ATTR(spaceship)
template <typename T, typename R>
struct IsSpaceshipCompatible<T, R, Void<decltype(meta::rvalue<T>() <=> meta::rvalue<R>())>> : meta::True {};
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

template <typename Type, typename Param = Type, typename Return = Type&> struct IsAssignable :
    impl::IsAssignable<Type, Param, Return> {};

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

#if CDS_ATTR(spaceship)
template <typename Type, typename With = Type> struct IsSpaceshipCompatible :
    impl::IsSpaceshipCompatible<Type, With>::Type {};
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
