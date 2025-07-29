//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_SPECIAL_MEMBER_FUNCTIONS_DETAIL_HPP
#define CDS_PRIMITIVE_EXPECTED_SPECIAL_MEMBER_FUNCTIONS_DETAIL_HPP
#pragma once

#include "../../meta/SpecialMemberFunctions.hpp"

namespace cds {
namespace impl {
using meta::IsCopyAssignable;
using meta::IsCopyConstructible;
using meta::IsMoveAssignable;
using meta::IsMoveConstructible;
using meta::IsDefaultConstructible;
using meta::IsDestructible;
using meta::IsTriviallyCopyAssignable;
using meta::IsTriviallyCopyConstructible;
using meta::IsTriviallyMoveAssignable;
using meta::IsTriviallyMoveConstructible;
using meta::IsTriviallyDefaultConstructible;
using meta::IsTriviallyDestructible;
using meta::SpecialMemberFunctionInfo;
using meta::SpecialMemberFunctionInfoProvider;
using meta::Unless;

template <typename T, typename E> struct ExpectedDestructionDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyDestructible, Unless<IsDestructible>::Type, T, E
> {};

template <typename T, typename E> struct ExpectedDefaultConstructionDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyDefaultConstructible, Unless<IsDefaultConstructible>::Type, T
> {};

template <typename T, typename E> struct ExpectedCopyConstructionDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyCopyConstructible, Unless<IsCopyConstructible>::Type, T, E
> {};

template <typename T, typename E> struct ExpectedMoveConstructionDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyMoveConstructible, Unless<IsMoveConstructible>::Type, T, E
> {};

template <typename T, typename E> struct ExpectedCopyAssignDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyCopyAssignable, Unless<IsCopyAssignable>::Type, T, E
> {};

template <typename T, typename E> struct ExpectedMoveAssignDetail : SpecialMemberFunctionInfoProvider<
    IsTriviallyMoveAssignable, Unless<IsMoveAssignable>::Type, T, E
> {};

template <typename E> struct ExpectedDestructionDetail<void, E> : SpecialMemberFunctionInfoProvider<
    IsTriviallyDestructible, Unless<IsDestructible>::Type, E
> {};

template <typename E> struct ExpectedDefaultConstructionDetail<void, E> :
    SpecialMemberFunctionInfo<typename True::Type, typename False::Type> {};

template <typename E> struct ExpectedCopyConstructionDetail<void, E> : SpecialMemberFunctionInfoProvider<
    IsTriviallyCopyConstructible, Unless<IsCopyConstructible>::Type, E
> {};

template <typename E> struct ExpectedMoveConstructionDetail<void, E> : SpecialMemberFunctionInfoProvider<
    IsTriviallyMoveConstructible, Unless<IsMoveConstructible>::Type, E
> {};

template <typename E> struct ExpectedCopyAssignDetail<void, E> : SpecialMemberFunctionInfoProvider<
    IsTriviallyCopyAssignable, Unless<IsCopyAssignable>::Type, E
> {};

template <typename E> struct ExpectedMoveAssignDetail<void, E> : SpecialMemberFunctionInfoProvider<
    IsTriviallyMoveAssignable, Unless<IsMoveAssignable>::Type, E
> {};
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_EXPECTED_SPECIAL_MEMBER_FUNCTIONS_DETAIL_HPP
