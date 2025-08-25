//
// Created by loghin on 8/24/25.
//

#ifndef CDS_FUNCTIONAL_FUNCTION_REF_HPP
#define CDS_FUNCTIONAL_FUNCTION_REF_HPP
#pragma once

#include <cds/meta/Compiler>

#include "functionRef/FunctionRefBase.hpp"
#include "functionRef/FunctionRefDecl.hpp"

namespace cds {
namespace functional {
namespace impl {
using meta::ConstSignatureOf;
using meta::SignatureOf;

template <typename S> class FunctionRef;
template <typename S> class NodiscardFunctionRef;

template <typename R, typename... A> class FunctionRef<R(A...)> :
    public FunctionRefBase<BoolTrait::False, BoolTrait::Unknown, BoolTrait::False, R, A...> {
  using Base = FunctionRefBase<BoolTrait::False, BoolTrait::Unknown, BoolTrait::False, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

template <typename R, typename... A> class FunctionRef<R(A...) const> :
    public FunctionRefBase<BoolTrait::True, BoolTrait::Unknown, BoolTrait::False, R, A...> {
  using Base = FunctionRefBase<BoolTrait::True, BoolTrait::Unknown, BoolTrait::False, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

#if CDS_ATTR(cpp17)
template <typename R, typename... A> class FunctionRef<R(A...) noexcept> :
    public FunctionRefBase<BoolTrait::False, BoolTrait::True, BoolTrait::False, R, A...> {
  using Base = FunctionRefBase<BoolTrait::False, BoolTrait::True, BoolTrait::False, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

template <typename R, typename... A> class FunctionRef<R(A...) const noexcept> :
    public FunctionRefBase<BoolTrait::True, BoolTrait::True, BoolTrait::False, R, A...> {
  using Base = FunctionRefBase<BoolTrait::True, BoolTrait::True, BoolTrait::False, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};
#endif

template <typename R, typename... A> class NodiscardFunctionRef<R(A...)> :
    public FunctionRefBase<BoolTrait::False, BoolTrait::Unknown, BoolTrait::True, R, A...> {
  using Base = FunctionRefBase<BoolTrait::False, BoolTrait::Unknown, BoolTrait::True, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

template <typename R, typename... A> class NodiscardFunctionRef<R(A...) const> :
    public FunctionRefBase<BoolTrait::True, BoolTrait::Unknown, BoolTrait::True, R, A...> {
  using Base = FunctionRefBase<BoolTrait::True, BoolTrait::Unknown, BoolTrait::True, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

#if CDS_ATTR(noexcept_fn_type)
template <typename R, typename... A> class NodiscardFunctionRef<R(A...) noexcept> :
    public FunctionRefBase<BoolTrait::False, BoolTrait::True, BoolTrait::True, R, A...> {
  using Base = FunctionRefBase<BoolTrait::False, BoolTrait::True, BoolTrait::True, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};

template <typename R, typename... A> class NodiscardFunctionRef<R(A...) const noexcept> :
    public FunctionRefBase<BoolTrait::True, BoolTrait::True, BoolTrait::True, R, A...> {
  using Base = FunctionRefBase<BoolTrait::True, BoolTrait::True, BoolTrait::True, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};
#endif // #if CDS_ATTR(noexcept_fn_type)

#if CDS_ATTR(ctad)
template <typename R, typename... A> FunctionRef(R(*)(A...)) -> FunctionRef<R(A...)>;
template <typename F> FunctionRef(F&) -> FunctionRef<SignatureOf<decltype(&F::operator())>>;
template <typename F> FunctionRef(F&&) -> FunctionRef<SignatureOf<decltype(&F::operator())>>;
template <typename F> FunctionRef(F const&) -> FunctionRef<ConstSignatureOf<decltype(&F::operator())>>;
template <typename F> FunctionRef(F const&&) -> FunctionRef<ConstSignatureOf<decltype(&F::operator())>>;

template <typename R, typename... A> NodiscardFunctionRef(R(*)(A...)) -> NodiscardFunctionRef<R(A...)>;
template <typename F> NodiscardFunctionRef(F&) -> NodiscardFunctionRef<SignatureOf<decltype(&F::operator())>>;
template <typename F> NodiscardFunctionRef(F&&) -> NodiscardFunctionRef<SignatureOf<decltype(&F::operator())>>;
template <typename F> NodiscardFunctionRef(F const&)
    -> NodiscardFunctionRef<ConstSignatureOf<decltype(&F::operator())>>;
template <typename F> NodiscardFunctionRef(F const&&)
    -> NodiscardFunctionRef<ConstSignatureOf<decltype(&F::operator())>>;
#endif // #if CDS_ATTR(ctad)
} // namespace impl
} // namespace functional
} // namespace cds

#endif // #ifndef CDS_FUNCTIONAL_FUNCTION_REF_HPP
