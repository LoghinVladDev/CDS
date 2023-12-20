//
// Created by loghin on 12/5/23.
//

#ifndef CDS_META_OBJECT_TRAITS_HPP
#define CDS_META_OBJECT_TRAITS_HPP
#pragma once

#include "TypeTraits.hpp"

namespace cds {
namespace meta {
namespace impl {
template <typename T> struct IsTriviallyCopyable : ::cds::meta::impl::ConvertIntegral<std::is_trivially_copyable<T>> {};
template <typename T, typename... A> struct IsTriviallyConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_constructible<T, A...>> {};

template <typename T, typename A> struct IsTriviallyAssignable :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_assignable<::cds::meta::AddLValRef<T>, A>> {};

template <typename T> struct IsTriviallyDestructible :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_destructible<T>> {};

template <typename T> struct IsTriviallyDefaultConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_default_constructible<T>> {};

template <typename T> struct IsTriviallyCopyConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_copy_constructible<T>> {};

template <typename T> struct IsTriviallyMoveConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_move_constructible<T>> {};

template <typename T> struct IsTriviallyCopyAssignable :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_copy_assignable<T>> {};

template <typename T> struct IsTriviallyMoveAssignable :
    ::cds::meta::impl::ConvertIntegral<std::is_trivially_move_assignable<T>> {};

template <typename T> struct IsDefaultConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_default_constructible<T>> {};

template <typename T> struct IsCopyConstructible : ::cds::meta::impl::ConvertIntegral<std::is_copy_constructible<T>> {};
template <typename T> struct IsMoveConstructible : ::cds::meta::impl::ConvertIntegral<std::is_move_constructible<T>> {};
template <typename T, typename... A> struct IsConstructible :
    ::cds::meta::impl::ConvertIntegral<std::is_constructible<T, A...>> {};

template <typename T, typename P = T, typename R = T&, typename = void> struct IsAssignable : ::cds::meta::False {};
template <typename T, typename P, typename R>
struct IsAssignable<T, P, R, Void<decltype(::cds::meta::lvalue<T>() = ::cds::meta::rvalue<P>())>> :
    ::cds::meta::IsSame<decltype(::cds::meta::lvalue<T>() = ::cds::meta::rvalue<P>()), R>::Type {};

template <typename T> struct IsCopyAssignable :
    ::cds::meta::impl::ConvertIntegral<std::is_copy_assignable<T>> {};

template <typename T> struct IsMoveAssignable :
    ::cds::meta::impl::ConvertIntegral<std::is_move_assignable<T>> {};

template <typename T, typename R = T, typename = void> struct IsAddCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsSubCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsMulCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsDivCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsModCompatible : ::cds::meta::False {};
template <typename T, typename = void> struct IsPrefixIncrementable : ::cds::meta::False {};
template <typename T, typename = void> struct IsPostfixIncrementable : ::cds::meta::False {};
template <typename T, typename = void> struct IsPrefixDecrementable : ::cds::meta::False {};
template <typename T, typename = void> struct IsPostfixDecrementable : ::cds::meta::False {};

template <typename T, typename R = T, typename = void> struct IsLtCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsLeCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsGtCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsGeCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsEqCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsNeCompatible : ::cds::meta::False {};
#if CDS_ATTR(spaceship)
template <typename T, typename R = T, typename = void> struct IsSpaceshipCompatible : ::cds::meta::False {};
#endif

template <typename T, typename = void> struct IsNotCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsAndCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsOrCompatible : ::cds::meta::False {};

template <typename T, typename = void> struct IsBitwiseNotCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseAndCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseOrCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseXorCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseLshCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseRshCompatible : ::cds::meta::False {};

template <typename T, typename R = T, typename = void> struct IsAddAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsSubAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsMulAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsDivAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsModAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseAndAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseOrAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseXorAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseLshAssignCompatible : ::cds::meta::False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseRshAssignCompatible : ::cds::meta::False {};

template <typename T, typename I = int, typename = void> struct IsSubscriptCompatible : ::cds::meta::False {};
template <typename T, typename = void> struct IsIndirectionCompatible : ::cds::meta::False {};
template <typename T, typename = void> struct IsAddressOfCompatible : ::cds::meta::False {};

template <typename T, typename R>
struct IsAddCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() + ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsSubCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() - ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsMulCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() * ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsDivCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() / ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsModCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() % ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T> struct IsPrefixIncrementable<T, ::cds::meta::Void<decltype(++::cds::meta::lvalue<T>())>> :
    ::cds::meta::True {};

template <typename T> struct IsPostfixIncrementable<T, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>()++)>> :
    ::cds::meta::True {};

template <typename T> struct IsPrefixDecrementable<T, ::cds::meta::Void<decltype(--::cds::meta::lvalue<T>())>> :
    ::cds::meta::True {};

template <typename T> struct IsPostfixDecrementable<T, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>()--)>> :
    ::cds::meta::True {};

template <> struct IsPrefixIncrementable<bool> : ::cds::meta::False {};
template <> struct IsPostfixIncrementable<bool> : ::cds::meta::False {};

template <typename T, typename R>
struct IsLtCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() < ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsLeCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() <= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsGtCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() > ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsGeCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() >= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsEqCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() == ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsNeCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() != ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

#if CDS_ATTR(spaceship)
template <typename T, typename R>
struct IsSpaceshipCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() <=> ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};
#endif

template <typename T> struct IsNotCompatible<T, ::cds::meta::Void<decltype(!::cds::meta::rvalue<T>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsAndCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() && ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};
template <typename T, typename R>
struct IsOrCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() || ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T>
struct IsBitwiseNotCompatible<T, ::cds::meta::Void<decltype(~::cds::meta::rvalue<T>())>> : ::cds::meta::True {};

template <typename T, typename R>
struct IsBitwiseAndCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() & ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsBitwiseOrCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() | ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsBitwiseXorCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() ^ ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsBitwiseLshCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() << ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsBitwiseRshCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>() >> ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};


template <typename T, typename R>
struct IsAddAssignCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() += ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsSubAssignCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() -= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsMulAssignCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() *= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsDivAssignCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() /= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R>
struct IsModAssignCompatible<T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() %= ::cds::meta::rvalue<R>())>> :
    ::cds::meta::True {};

template <typename T, typename R> struct IsBitwiseAndAssignCompatible<
    T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() &= ::cds::meta::rvalue<R>())>
> : ::cds::meta::True {};

template <typename T, typename R> struct IsBitwiseOrAssignCompatible<
    T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() |= ::cds::meta::rvalue<R>())>
> : ::cds::meta::True {};

template <typename T, typename R> struct IsBitwiseXorAssignCompatible<
    T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() ^= ::cds::meta::rvalue<R>())>
> : ::cds::meta::True {};

template <typename T, typename R> struct IsBitwiseLshAssignCompatible<
    T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() <<= ::cds::meta::rvalue<R>())>
> : ::cds::meta::True {};

template <typename T, typename R> struct IsBitwiseRshAssignCompatible<
    T, R, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>() >>= ::cds::meta::rvalue<R>())>
> : ::cds::meta::True {};


template <typename T, typename I>
struct IsSubscriptCompatible<T, I, ::cds::meta::Void<decltype(::cds::meta::lvalue<T>()[::cds::meta::rvalue<I>()])>> :
    ::cds::meta::True {};

template <typename T> struct IsIndirectionCompatible<T, ::cds::meta::Void<decltype(*::cds::meta::rvalue<T>())>> :
    ::cds::meta::True {};
template <typename T> struct IsAddressOfCompatible<T, ::cds::meta::Void<decltype(&::cds::meta::lvalue<T>())>> :
    ::cds::meta::True {};

template <typename B, typename D> struct IsBaseOf : ::cds::meta::And<
    ::cds::meta::All<::cds::meta::IsClass, B, D>,
    typename ::cds::meta::IsConvertible<D*, B*>::Type
> {};

template <typename> struct Member {};
template <typename T, typename C> struct Member<T C::*> { using Type = T; };

template <typename> struct IsMember : False {};
template <typename T, typename C> struct IsMember<T C::*> : True {};

template <typename T> struct IsCallableObject {
  struct Fallback { auto operator()() -> void; };
  struct Resolver : T, IsCallableObject::Fallback {};
  template <typename O, O> struct check;
  template <typename> static auto test(...) noexcept -> True;
  template <typename C> static auto test(
      IsCallableObject::check<void (IsCallableObject::Fallback::*)(), &C::operator()> const*
  ) noexcept -> False;
  using Type = decltype(test<Resolver>(nullptr));
};
} // namespace impl

template <typename Type> struct IsTriviallyCopyable : ::cds::meta::impl::IsTriviallyCopyable<Type>::Type {};
template <typename Type, typename... Arguments> struct IsTriviallyConstructible :
    ::cds::meta::impl::IsTriviallyConstructible<Type, Arguments...>::Type {};

template <typename Type, typename Argument> struct IsTriviallyAssignable :
    ::cds::meta::impl::IsTriviallyAssignable<Type, Argument>::Type {};

template <typename Type> struct IsTriviallyDestructible : ::cds::meta::impl::IsTriviallyDestructible<Type>::Type {};
template <typename Type> struct IsTriviallyDefaultConstructible :
    ::cds::meta::impl::IsTriviallyDefaultConstructible<Type>::Type {};

template <typename Type> struct IsTriviallyCopyConstructible :
    ::cds::meta::impl::IsTriviallyCopyConstructible<Type>::Type {};

template <typename Type> struct IsTriviallyMoveConstructible :
    ::cds::meta::impl::IsTriviallyMoveConstructible<Type>::Type {};

template <typename Type> struct IsTriviallyCopyAssignable : ::cds::meta::impl::IsTriviallyCopyAssignable<Type>::Type {};
template <typename Type> struct IsTriviallyMoveAssignable : ::cds::meta::impl::IsTriviallyMoveAssignable<Type>::Type {};

template <typename Type> struct IsDefaultConstructible : ::cds::meta::impl::IsDefaultConstructible<Type>::Type {};
template <typename Type> struct IsCopyConstructible : ::cds::meta::impl::IsCopyConstructible<Type>::Type {};
template <typename Type> struct IsMoveConstructible : ::cds::meta::impl::IsMoveConstructible<Type>::Type {};
template <typename Type> struct IsCopyAssignable : ::cds::meta::impl::IsCopyAssignable<Type>::Type {};
template <typename Type> struct IsMoveAssignable : ::cds::meta::impl::IsMoveAssignable<Type>::Type {};
template <typename Type, typename... Arguments> struct IsConstructible :
    ::cds::meta::impl::IsConstructible<Type, Arguments...>::Type {};

template <typename Type, typename Param = Type, typename Return = Type&> struct IsAssignable :
    ::cds::meta::impl::IsAssignable<Type, Param, Return> {};

template <typename Type, typename With = Type> struct IsAddCompatible :
    ::cds::meta::impl::IsAddCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsSubCompatible :
    ::cds::meta::impl::IsSubCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsMulCompatible :
    ::cds::meta::impl::IsMulCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsDivCompatible :
    ::cds::meta::impl::IsDivCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsModCompatible :
    ::cds::meta::impl::IsModCompatible<Type, With>::Type {};

template <typename Type> struct IsPrefixIncrementable : ::cds::meta::impl::IsPrefixIncrementable<Type>::Type {};
template <typename Type> struct IsPostfixIncrementable : ::cds::meta::impl::IsPostfixIncrementable<Type>::Type {};
template <typename Type> struct IsPrefixDecrementable : ::cds::meta::impl::IsPrefixDecrementable<Type>::Type {};
template <typename Type> struct IsPostfixDecrementable : ::cds::meta::impl::IsPostfixDecrementable<Type>::Type {};

template <typename Type, typename With = Type> struct IsLtCompatible :
    ::cds::meta::impl::IsLtCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsLeCompatible :
    ::cds::meta::impl::IsLeCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsGtCompatible :
    ::cds::meta::impl::IsGtCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsGeCompatible :
    ::cds::meta::impl::IsGeCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsEqCompatible :
    ::cds::meta::impl::IsEqCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsNeCompatible :
    ::cds::meta::impl::IsNeCompatible<Type, With>::Type {};

#if CDS_ATTR(spaceship)
template <typename Type, typename With = Type> struct IsSpaceshipCompatible :
    ::cds::meta::impl::IsSpaceshipCompatible<Type, With>::Type {};
#endif

template <typename Type> struct IsNotCompatible : ::cds::meta::impl::IsNotCompatible<Type>::Type {};
template <typename Type, typename With = Type> struct IsAndCompatible :
    ::cds::meta::impl::IsAndCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsOrCompatible :
    ::cds::meta::impl::IsOrCompatible<Type, With>::Type {};

template <typename Type> struct IsBitwiseNotCompatible : ::cds::meta::impl::IsBitwiseNotCompatible<Type>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseAndCompatible :
    ::cds::meta::impl::IsBitwiseAndCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseOrCompatible :
    ::cds::meta::impl::IsBitwiseOrCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseXorCompatible :
    ::cds::meta::impl::IsBitwiseXorCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseLshCompatible :
    ::cds::meta::impl::IsBitwiseLshCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseRshCompatible :
    ::cds::meta::impl::IsBitwiseRshCompatible<Type, With>::Type {};


template <typename Type, typename With = Type> struct IsAddAssignCompatible :
    ::cds::meta::impl::IsAddAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsSubAssignCompatible :
    ::cds::meta::impl::IsSubAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsMulAssignCompatible :
    ::cds::meta::impl::IsMulAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsDivAssignCompatible :
    ::cds::meta::impl::IsDivAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsModAssignCompatible :
    ::cds::meta::impl::IsModAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseAndAssignCompatible :
    ::cds::meta::impl::IsBitwiseAndAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseOrAssignCompatible :
    ::cds::meta::impl::IsBitwiseOrAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseXorAssignCompatible :
    ::cds::meta::impl::IsBitwiseXorAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseLshAssignCompatible :
    ::cds::meta::impl::IsBitwiseLshAssignCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsBitwiseRshAssignCompatible :
    ::cds::meta::impl::IsBitwiseRshAssignCompatible<Type, With>::Type {};


template <typename Type, typename Index = int> struct IsSubscriptCompatible :
    ::cds::meta::impl::IsSubscriptCompatible<Type, Index>::Type {};

template <typename Type> struct IsIndirectionCompatible : ::cds::meta::impl::IsIndirectionCompatible<Type>::Type {};
template <typename Type> struct IsAddressOfCompatible : ::cds::meta::impl::IsAddressOfCompatible<Type>::Type {};

template <typename Base, typename Derived> struct IsBaseOf : ::cds::meta::impl::IsBaseOf<Base, Derived>::Type {};
template <typename Derived, typename Base> struct IsDerivedFrom : ::cds::meta::impl::IsBaseOf<Base, Derived>::Type {};
template <typename MemberType> using Member = typename ::cds::meta::impl::Member<MemberType>::Type;

template <typename Type> struct IsCallableObject :
    Conditional<IsClass<Type>, ::cds::meta::impl::IsCallableObject<Type>, False>::Type {};

template <typename Type> struct IsMember : ::cds::meta::impl::IsMember<Type>::Type {};

template <typename Type> struct IsCallable :
    And<Not<IsMember<Type>>, Or<IsCallableObject<Type>, IsFunction<RemovePointer<Type>>>> {};
} // namespace meta
} // namespace cds

#endif // CDS_META_OBJECT_TRAITS_HPP
