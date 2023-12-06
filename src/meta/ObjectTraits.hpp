//
// Created by loghin on 12/5/23.
//

#ifndef CDS_META_OBJECT_TRAITS_HPP
#define CDS_META_OBJECT_TRAITS_HPP

#include "TypeTraits.hpp"

namespace cds {
namespace meta {
namespace impl {
template <typename T> struct IsTriviallyCopyable : ConvertIntegral<std::is_trivially_copyable<T>> {};
template <typename T, typename... A> struct IsTriviallyConstructible : ConvertIntegral<std::is_trivially_constructible<T, A...>> {};
template <typename T, typename A> struct IsTriviallyAssignable : ConvertIntegral<std::is_trivially_assignable<T, A>> {};
template <typename T> struct IsTriviallyDestructible : ConvertIntegral<std::is_trivially_destructible<T>> {};
template <typename T> struct IsTriviallyDefaultConstructible : ConvertIntegral<std::is_trivially_default_constructible<T>> {};
template <typename T> struct IsTriviallyCopyConstructible : ConvertIntegral<std::is_trivially_copy_constructible<T>> {};
template <typename T> struct IsTriviallyMoveConstructible : ConvertIntegral<std::is_trivially_move_constructible<T>> {};
template <typename T> struct IsTriviallyCopyAssignable : ConvertIntegral<std::is_trivially_copy_assignable<T>> {};
template <typename T> struct IsTriviallyMoveAssignable : ConvertIntegral<std::is_trivially_move_assignable<T>> {};

template <typename T> struct IsDefaultConstructible : ConvertIntegral<std::is_default_constructible<T>> {};
template <typename T> struct IsCopyConstructible : ConvertIntegral<std::is_copy_constructible<T>> {};
template <typename T> struct IsMoveConstructible : ConvertIntegral<std::is_move_constructible<T>> {};
template <typename T> struct IsCopyAssignable : ConvertIntegral<std::is_copy_assignable<T>> {};
template <typename T> struct IsMoveAssignable : ConvertIntegral<std::is_move_assignable<T>> {};

template <typename T, typename R = T, typename = void> struct IsAddCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsSubCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsMulCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsDivCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsModCompatible : False {};
template <typename T, typename = void> struct IsPrefixIncrementable : False {};
template <typename T, typename = void> struct IsPostfixIncrementable : False {};
template <typename T, typename = void> struct IsPrefixDecrementable : False {};
template <typename T, typename = void> struct IsPostfixDecrementable : False {};

template <typename T, typename R = T, typename = void> struct IsLtCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsLeCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsGtCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsGeCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsEqCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsNeCompatible : False {};
#if CDS_ATTR(spaceship)
template <typename T, typename R = T, typename = void> struct IsSpaceshipCompatible : False {};
#endif

template <typename T, typename = void> struct IsNotCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsAndCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsOrCompatible : False {};

template <typename T, typename = void> struct IsBitwiseNotCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseAndCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseOrCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseXorCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseLshCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseRshCompatible : False {};

template <typename T, typename R = T, typename = void> struct IsAddAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsSubAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsMulAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsDivAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsModAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseAndAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseOrAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseXorAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseLshAssignCompatible : False {};
template <typename T, typename R = T, typename = void> struct IsBitwiseRshAssignCompatible : False {};

template <typename T, typename I = int, typename = void> struct IsSubscriptCompatible : False {};
template <typename T, typename = void> struct IsIndirectionCompatible : False {};
template <typename T, typename = void> struct IsAddressOfCompatible : False {};

template <typename T, typename R> struct IsAddCompatible<T, R, Void<decltype(value<T>() + value<R>())>> : True {};
template <typename T, typename R> struct IsSubCompatible<T, R, Void<decltype(value<T>() - value<R>())>> : True {};
template <typename T, typename R> struct IsMulCompatible<T, R, Void<decltype(value<T>() * value<R>())>> : True {};
template <typename T, typename R> struct IsDivCompatible<T, R, Void<decltype(value<T>() / value<R>())>> : True {};
template <typename T, typename R> struct IsModCompatible<T, R, Void<decltype(value<T>() % value<R>())>> : True {};
template <typename T> struct IsPrefixIncrementable<T, Void<decltype(++reference<T>())>> : True {};
template <typename T> struct IsPostfixIncrementable<T, Void<decltype(reference<T>()++)>> : True {};
template <typename T> struct IsPrefixDecrementable<T, Void<decltype(--reference<T>())>> : True {};
template <typename T> struct IsPostfixDecrementable<T, Void<decltype(reference<T>()--)>> : True {};
template <> struct IsPrefixIncrementable<bool> : False {};
template <> struct IsPostfixIncrementable<bool> : False {};

template <typename T, typename R> struct IsLtCompatible<T, R, Void<decltype(value<T>() < value<R>())>> : True {};
template <typename T, typename R> struct IsLeCompatible<T, R, Void<decltype(value<T>() <= value<R>())>> : True {};
template <typename T, typename R> struct IsGtCompatible<T, R, Void<decltype(value<T>() > value<R>())>> : True {};
template <typename T, typename R> struct IsGeCompatible<T, R, Void<decltype(value<T>() >= value<R>())>> : True {};
template <typename T, typename R> struct IsEqCompatible<T, R, Void<decltype(value<T>() == value<R>())>> : True {};
template <typename T, typename R> struct IsNeCompatible<T, R, Void<decltype(value<T>() != value<R>())>> : True {};
#if CDS_ATTR(spaceship)
template <typename T, typename R> struct IsSpaceshipCompatible<T, R, Void<decltype(value<T>() <=> value<R>())>> : True {};
#endif

template <typename T> struct IsNotCompatible<T, Void<decltype(!value<T>())>> : True {};
template <typename T, typename R> struct IsAndCompatible<T, R, Void<decltype(value<T>() && value<R>())>> : True {};
template <typename T, typename R> struct IsOrCompatible<T, R, Void<decltype(value<T>() || value<R>())>> : True {};

template <typename T> struct IsBitwiseNotCompatible<T, Void<decltype(~value<T>())>> : True {};
template <typename T, typename R> struct IsBitwiseAndCompatible<T, R, Void<decltype(value<T>() & value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseOrCompatible<T, R, Void<decltype(value<T>() | value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseXorCompatible<T, R, Void<decltype(value<T>() ^ value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseLshCompatible<T, R, Void<decltype(value<T>() << value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseRshCompatible<T, R, Void<decltype(value<T>() >> value<R>())>> : True {};

template <typename T, typename R> struct IsAddAssignCompatible<T, R, Void<decltype(value<T>() += value<R>())>> : True {};
template <typename T, typename R> struct IsSubAssignCompatible<T, R, Void<decltype(value<T>() -= value<R>())>> : True {};
template <typename T, typename R> struct IsMulAssignCompatible<T, R, Void<decltype(value<T>() *= value<R>())>> : True {};
template <typename T, typename R> struct IsDivAssignCompatible<T, R, Void<decltype(value<T>() /= value<R>())>> : True {};
template <typename T, typename R> struct IsModAssignCompatible<T, R, Void<decltype(value<T>() %= value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseAndAssignCompatible<T, R, Void<decltype(value<T>() &= value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseOrAssignCompatible<T, R, Void<decltype(value<T>() |= value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseXorAssignCompatible<T, R, Void<decltype(value<T>() ^= value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseLshAssignCompatible<T, R, Void<decltype(value<T>() <<= value<R>())>> : True {};
template <typename T, typename R> struct IsBitwiseRshAssignCompatible<T, R, Void<decltype(value<T>() >>= value<R>())>> : True {};

template <typename T, typename I> struct IsSubscriptCompatible<T, I, Void<decltype(value<T>()[value<I>()])>> : True {};
template <typename T> struct IsIndirectionCompatible<T, Void<decltype(*value<T>())>> : True {};
template <typename T> struct IsAddressOfCompatible<T, Void<decltype(&value<T>())>> : True {};
} // namespace impl

template <typename Type> using IsTriviallyCopyable = typename impl::IsTriviallyCopyable<Type>::Type;
template <typename Type, typename... Arguments> using IsTriviallyConstructible = typename impl::IsTriviallyConstructible<Type, Arguments...>::Type;
template <typename Type, typename Argument> struct IsTriviallyAssignable : impl::IsTriviallyAssignable<Type, Argument>::Type {};
template <typename Type> using IsTriviallyDestructible = typename impl::IsTriviallyDestructible<Type>::Type;
template <typename Type> using IsTriviallyDefaultConstructible = typename impl::IsTriviallyDefaultConstructible<Type>::Type;
template <typename Type> using IsTriviallyCopyConstructible = typename impl::IsTriviallyCopyConstructible<Type>::Type;
template <typename Type> using IsTriviallyMoveConstructible = typename impl::IsTriviallyMoveConstructible<Type>::Type;
template <typename Type> using IsTriviallyCopyAssignable = typename impl::IsTriviallyCopyAssignable<Type>::Type;
template <typename Type> using IsTriviallyMoveAssignable = typename impl::IsTriviallyMoveAssignable<Type>::Type;
template <typename Type> using IsDefaultConstructible = typename impl::IsDefaultConstructible<Type>::Type;
template <typename Type> using IsCopyConstructible = typename impl::IsCopyConstructible<Type>::Type;
template <typename Type> using IsMoveConstructible = typename impl::IsMoveConstructible<Type>::Type;
template <typename Type> using IsCopyAssignable = typename impl::IsCopyAssignable<Type>::Type;
template <typename Type> using IsMoveAssignable = typename impl::IsMoveAssignable<Type>::Type;

template <typename Type, typename With = Type> struct IsAddCompatible : impl::IsAddCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsSubCompatible : impl::IsSubCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsMulCompatible : impl::IsMulCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsDivCompatible : impl::IsDivCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsModCompatible : impl::IsModCompatible<Type, With>::Type {};
template <typename Type> using IsPrefixIncrementable = typename impl::IsPrefixIncrementable<Type>::Type;
template <typename Type> using IsPostfixIncrementable = typename impl::IsPostfixIncrementable<Type>::Type;
template <typename Type> using IsPrefixDecrementable = typename impl::IsPrefixDecrementable<Type>::Type;
template <typename Type> using IsPostfixDecrementable = typename impl::IsPostfixDecrementable<Type>::Type;

template <typename Type, typename With = Type> struct IsLtCompatible : impl::IsLtCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsLeCompatible : impl::IsLeCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsGtCompatible : impl::IsGtCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsGeCompatible : impl::IsGeCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsEqCompatible : impl::IsEqCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsNeCompatible : impl::IsNeCompatible<Type, With>::Type {};
#if CDS_ATTR(spaceship)
template <typename Type, typename With = Type> struct IsSpaceshipCompatible : impl::IsSpaceshipCompatible<Type, With>::Type {};
#endif

template <typename Type> using IsNotCompatible = typename impl::IsNotCompatible<Type>::Type;
template <typename Type, typename With = Type> struct IsAndCompatible : impl::IsAndCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsOrCompatible : impl::IsOrCompatible<Type, With>::Type {};

template <typename Type> using IsBitwiseNotCompatible = typename impl::IsBitwiseNotCompatible<Type>::Type;
template <typename Type, typename With = Type> struct IsBitwiseAndCompatible : impl::IsBitwiseAndCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseOrCompatible : impl::IsBitwiseOrCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseXorCompatible : impl::IsBitwiseXorCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseLshCompatible : impl::IsBitwiseLshCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseRshCompatible : impl::IsBitwiseRshCompatible<Type, With>::Type {};

template <typename Type, typename With = Type> struct IsAddAssignCompatible : impl::IsAddAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsSubAssignCompatible : impl::IsSubAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsMulAssignCompatible : impl::IsMulAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsDivAssignCompatible : impl::IsDivAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsModAssignCompatible : impl::IsModAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseAndAssignCompatible : impl::IsBitwiseAndAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseOrAssignCompatible : impl::IsBitwiseOrAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseXorAssignCompatible : impl::IsBitwiseXorAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseLshAssignCompatible : impl::IsBitwiseLshAssignCompatible<Type, With>::Type {};
template <typename Type, typename With = Type> struct IsBitwiseRshAssignCompatible : impl::IsBitwiseRshAssignCompatible<Type, With>::Type {};

template <typename Type, typename Index = int> struct IsSubscriptCompatible : impl::IsSubscriptCompatible<Type, Index>::Type {};
template <typename Type> using IsIndirectionCompatible = typename impl::IsIndirectionCompatible<Type>::Type;
template <typename Type> using IsAddressOfCompatible = typename impl::IsAddressOfCompatible<Type>::Type;
} // namespace meta
} // namespace cds

#endif // CDS_META_OBJECT_TRAITS_HPP
