//
// Created by loghin on 7/29/25.
//

#ifndef CDS_META_SPECIAL_MEMBER_FUNCTIONS_HPP
#define CDS_META_SPECIAL_MEMBER_FUNCTIONS_HPP
#pragma once

#include <cds/meta/Base>

namespace cds {
namespace meta {
enum class SpecialMemberFunctionInfoType {
  Trivial, NonTrivial, Deleted
};

template <typename Trivial, typename Deleted> struct SpecialMemberFunctionInfo {
  static constexpr auto value = SpecialMemberFunctionInfoType::NonTrivial;
};

template <> struct SpecialMemberFunctionInfo<typename True::Type, typename False::Type> {
  static constexpr auto value = SpecialMemberFunctionInfoType::Trivial;
};

template <typename Trivial> struct SpecialMemberFunctionInfo<Trivial, typename True::Type> {
  static constexpr auto value = SpecialMemberFunctionInfoType::Deleted;
};

template <template <typename...> class IsTrivial, template <typename...> class IsDeleted, typename... Types>
struct SpecialMemberFunctionInfoProvider : SpecialMemberFunctionInfo<
    typename All<IsTrivial, Types...>::Type,
    typename All<IsDeleted, Types...>::Type
> {};
} // namespace meta
} // namespace cds

#endif // #ifndef CDS_META_SPECIAL_MEMBER_FUNCTIONS_HPP
