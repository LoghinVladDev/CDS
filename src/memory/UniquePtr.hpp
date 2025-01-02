//
// Created by loghin on 11/9/24.
//

#ifndef CDS_MEMORY_UNIQUE_PTR_HPP
#define CDS_MEMORY_UNIQUE_PTR_HPP
#pragma once

#include <cds/memory/Allocator>

#include <cds/meta/TypeTraits>
#include <cds/meta/ObjectTraits>
#include <cds/meta/Semantics>

#include <cds/functional/Invoke>

namespace cds {
namespace impl {
using meta::AddRValRef;
using meta::And;
using meta::EnableIf;
using meta::Eq;
using meta::False;
using meta::IsArray;
using meta::IsBoundedArray;
using meta::IsLValRef;
using meta::IsConvertible;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptDefaultConstructible;
using meta::IsNoexceptCopyAssignable;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptMoveAssignable;
using meta::IsNoexceptMoveConstructible;
using meta::IsNoexceptInvocable;
using meta::IsUnboundedArray;
using meta::IsVoid;
using meta::Null;
using meta::Not;
using meta::Or;
using meta::RemoveRef;
using meta::RemoveCVRef;
using meta::RemoveExtent;
using meta::ReturnIf;
using meta::True;

namespace f = functional;

template <typename T> class DefaultDeleter {
public:
  DefaultDeleter() noexcept = default;
  DefaultDeleter(DefaultDeleter const&) = default;
  DefaultDeleter(DefaultDeleter&&) = default;
  auto operator=(DefaultDeleter const&) -> DefaultDeleter& = default;
  auto operator=(DefaultDeleter&&) -> DefaultDeleter& = default;

  template <typename U, EnableIf<And<IsConvertible<U*, T*>, Eq<IsArray<T>, IsArray<U>>>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) DefaultDeleter(DefaultDeleter<U>) noexcept {}

  CDS_ATTR(constexpr(20)) auto operator()(T* p) const noexcept -> void {
    delete p;
  }
};

template <typename T> class DefaultDeleter<T[]> {
public:
  DefaultDeleter() = default;
  DefaultDeleter(DefaultDeleter const&) = default;
  DefaultDeleter(DefaultDeleter&&) = default;
  auto operator=(DefaultDeleter const&) -> DefaultDeleter& = default;
  auto operator=(DefaultDeleter&&) -> DefaultDeleter& = default;

  template <typename U, EnableIf<And<IsConvertible<U*, T*>, Eq<IsArray<T>, IsArray<U>>>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) DefaultDeleter(DefaultDeleter<U>) noexcept {}

  CDS_ATTR(constexpr(20)) auto operator()(T* p) const noexcept -> void {
    delete[] p;
  }
};

template <typename T, typename A = Allocator<RemoveExtent<T>>> class CDS_ATTR(ebo) UninitializedDeleter : private A {
  using A::deallocate;

public:
  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) UninitializedDeleter(Args&&... args) noexcept :
      A {fwd<Args>(args)...} {
    static_assert(IsNoexceptConstructible<A, Args...>::value, "Allocator does not satisfy NoexceptConstructible");
  }

  UninitializedDeleter(UninitializedDeleter const&) = default;
  UninitializedDeleter(UninitializedDeleter&&) = default;
  auto operator=(UninitializedDeleter const&) -> UninitializedDeleter& = default;
  auto operator=(UninitializedDeleter&&) -> UninitializedDeleter& = default;

  template <typename U, EnableIf<And<IsConvertible<U*, T*>, Eq<IsArray<T>, IsArray<U>>>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) UninitializedDeleter(UninitializedDeleter<U>) noexcept {}

  CDS_ATTR(constexpr(20)) auto operator()(T* p) const noexcept -> void {
    deallocate(p, 1);
  }
};

template <typename T, typename A> class CDS_ATTR(ebo) UninitializedDeleter<T[], A> : private A {
  using A::deallocate;

public:
  UninitializedDeleter() noexcept = delete;
  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) UninitializedDeleter(Size size, Args&&... args)
      noexcept : A{fwd<Args>(args)...}, _size{size} {
    static_assert(IsNoexceptConstructible<A, Args...>::value, "Allocator does not satisfy NoexceptConstructible");
  }

  template <typename U, EnableIf<And<IsConvertible<U*, T*>, Eq<IsArray<T>, IsArray<U>>>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) UninitializedDeleter(UninitializedDeleter<U> deleter) noexcept :
      _size{deleter.size()} {}

  UninitializedDeleter(UninitializedDeleter const&) = default;
  UninitializedDeleter(UninitializedDeleter&&) = default;
  auto operator=(UninitializedDeleter const&) -> UninitializedDeleter& = default;
  auto operator=(UninitializedDeleter&&) -> UninitializedDeleter& = default;

  CDS_ATTR(constexpr(20)) auto operator()(T* p) const noexcept -> void {
    Allocator<T>::deallocate(p, _size);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return _size;
  }

private:
  Size _size;
};

template <typename D> class CDS_ATTR(ebo) UniquePointerDeleterStorageBase : private D {
protected:
  template <typename...A> CDS_ATTR(2(explicit, constexpr(20))) UniquePointerDeleterStorageBase(A&&... dArgs) noexcept :
      D{fwd<A>(dArgs)...} {}

public:
  using D::D;
  using D::operator=;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto deleter() const noexcept -> D const& {
    return *static_cast<D const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto deleter() noexcept -> D& {
    return *static_cast<D*>(this);
  }
};

template <typename D> class UniquePointerDeleterStorageBase<D&> {
protected:
  template <typename...A> CDS_ATTR(2(explicit, constexpr(20))) UniquePointerDeleterStorageBase(A&&... dArgs) noexcept :
      _deleter{fwd<A>(dArgs)...} {}

public:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto deleter() const noexcept -> D const& {
    return _deleter;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto deleter() noexcept -> D& {
    return _deleter;
  }

private:
  D& _deleter;
};

template <typename T, typename D>
class CDS_ATTR(ebo) UniquePtrStorageBase : protected UniquePointerDeleterStorageBase<D> {
  static_assert(IsNoexceptInvocable<D, T*>::value, "Deleter does not satisfy NoexceptInvocable requirement");
  using Base = UniquePointerDeleterStorageBase<D>;

protected:
  template <typename...A> CDS_ATTR(2(explicit, constexpr(20))) UniquePtrStorageBase(T* ptr, A&&... dArgs) noexcept :
      Base{fwd<A>(dArgs)...}, _pointer{ptr} {}

public:
  using Base::deleter;

  CDS_ATTR(constexpr(20)) ~UniquePtrStorageBase() noexcept {
    f::invoke(_deleter, _pointer);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto release() noexcept -> T* {
    return xch(_pointer, nullptr);
  }

  CDS_ATTR(constexpr(14)) auto reset(T* ptr) noexcept -> void {
    f::invoke(_deleter, xch(_pointer, ptr));
  }

  CDS_ATTR(constexpr(14)) auto reset(Null = nullptr) noexcept -> void {
    f::invoke(_deleter, xch(_pointer, nullptr));
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const noexcept -> T* {
    return _pointer;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto deleter() const noexcept -> D const& {
    return _deleter;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto deleter() noexcept -> D& {
    return _deleter;
  }

private:
  T* _pointer;
  D _deleter;
};

template <typename T, typename D, typename = typename IsNoexceptCopyConstructible<D>::Type>
class CDS_ATTR(ebo) UniquePtrDeleterCopyInitBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterCopyInitBase<T, D, True> :
    public UniquePtrStorageBase<T, D> {
  using Base = UniquePtrStorageBase<T, D>;

public:
  using Base::Base;

  CDS_ATTR(constexpr(11)) UniquePtrDeleterCopyInitBase(T* ptr, D const& deleter) noexcept : Base{ptr, deleter} {}
};
template <typename T, typename D> class UniquePtrDeleterCopyInitBase<T, D, False> : public UniquePtrStorageBase<T, D> {
  using Base = UniquePtrStorageBase<T, D>;

public:
  using Base::Base;

  UniquePtrDeleterCopyInitBase(T* ptr, D const& deleter) = delete;
};

template <typename T, typename D, typename = typename IsNoexceptMoveConstructible<D>::Type>
class UniquePtrDeleterMoveInitBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveInitBase<T, D, True> :
    public UniquePtrDeleterCopyInitBase<T, D> {
  using Base = UniquePtrDeleterCopyInitBase<T, D>;

public:
  using Base::Base;
  CDS_ATTR(constexpr(11)) UniquePtrDeleterMoveInitBase(T* ptr, D&& deleter) noexcept : Base{ptr, mv(deleter)} {}
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveInitBase<T, D, False> :
    public UniquePtrDeleterCopyInitBase<T, D> {
  using Base = UniquePtrDeleterCopyInitBase<T, D>;

public:
  using Base::Base;
  UniquePtrDeleterMoveInitBase(T* ptr, D&& deleter) = delete;
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterInitBase :
    public UniquePtrDeleterMoveInitBase<T, D> {
  using Base = UniquePtrDeleterMoveInitBase<T, D>;

public:
  using Base::Base;
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterInitBase<T, D&> :
    protected UniquePtrStorageBase<T, D&> {
  using Base = UniquePtrStorageBase<T, D&>;

public:
  CDS_ATTR(constexpr(11)) UniquePtrDeleterInitBase(T* ptr, D& deleter) noexcept : Base{ptr, deleter} {}
  UniquePtrDeleterInitBase(T* ptr, D&& deleter) = delete;
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterInitBase<T, D const&> :
    public UniquePtrStorageBase<T, D const&> {
  using Base = UniquePtrStorageBase<T, D&>;

public:
  CDS_ATTR(constexpr(11)) UniquePtrDeleterInitBase(T* ptr, D const& deleter) noexcept : Base{ptr, deleter} {}
  UniquePtrDeleterInitBase(T* ptr, D const&& deleter) = delete;
};

template <typename T, typename D, typename = typename IsNoexceptDefaultConstructible<D>::Type>
class UniquePtrDeleterDefaultConstructibleBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterDefaultConstructibleBase<T, D, True> :
    public UniquePtrDeleterInitBase<T, D> {
  using Base = UniquePtrDeleterInitBase<T, D>;

public:
  using Base::Base;
  CDS_ATTR(constexpr(11)) UniquePtrDeleterDefaultConstructibleBase() noexcept : Base{nullptr} {}
  CDS_ATTR(2(implicit, constexpr(11))) UniquePtrDeleterDefaultConstructibleBase(Null) noexcept : Base{nullptr} {}
  CDS_ATTR(2(explicit, constexpr(11))) UniquePtrDeleterDefaultConstructibleBase(T* ptr) noexcept : Base{ptr} {}
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterDefaultConstructibleBase<T, D, False> :
    public UniquePtrDeleterInitBase<T, D> {
  using Base = UniquePtrDeleterInitBase<T, D>;

public:
  using Base::Base;
  UniquePtrDeleterDefaultConstructibleBase() = delete;
  UniquePtrDeleterDefaultConstructibleBase(Null) = delete;
  UniquePtrDeleterDefaultConstructibleBase(T* ptr) = delete;
};

template <typename T, typename D, typename = typename IsNoexceptMoveConstructible<D>::Type>
class UniquePtrDeleterMoveConstructibleBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveConstructibleBase<T, D, True> :
    public UniquePtrDeleterDefaultConstructibleBase<T, D> {
  using Base = UniquePtrDeleterDefaultConstructibleBase<T, D>;

public:
  using Base::Base;
  UniquePtrDeleterMoveConstructibleBase() = default;
  UniquePtrDeleterMoveConstructibleBase(UniquePtrDeleterMoveConstructibleBase const&) = default;
  CDS_ATTR(constexpr(11)) UniquePtrDeleterMoveConstructibleBase(UniquePtrDeleterMoveConstructibleBase&& ptr) noexcept :
      Base{ptr.release(), mv(ptr.deleter())} {}
  auto operator=(UniquePtrDeleterMoveConstructibleBase const&) -> UniquePtrDeleterMoveConstructibleBase& = default;
  auto operator=(UniquePtrDeleterMoveConstructibleBase&&) -> UniquePtrDeleterMoveConstructibleBase& = default;
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveConstructibleBase<T, D, False> :
    public UniquePtrDeleterDefaultConstructibleBase<T, D> {
  using Base = UniquePtrDeleterDefaultConstructibleBase<T, D>;

public:
  using Base::Base;
  UniquePtrDeleterMoveConstructibleBase() = default;
  UniquePtrDeleterMoveConstructibleBase(UniquePtrDeleterMoveConstructibleBase const&) = default;
  UniquePtrDeleterMoveConstructibleBase(UniquePtrDeleterMoveConstructibleBase&& ptr) = delete;
  auto operator=(UniquePtrDeleterMoveConstructibleBase const&) -> UniquePtrDeleterMoveConstructibleBase& = default;
  auto operator=(UniquePtrDeleterMoveConstructibleBase&&) -> UniquePtrDeleterMoveConstructibleBase& = default;
};

template <typename T, typename D, typename = typename Or<
    And<Not<IsLValRef<D>>, IsNoexceptMoveAssignable<D>>,
    And<IsLValRef<D>, IsNoexceptCopyAssignable<RemoveRef<D>>>
>::Type> class UniquePtrDeleterMoveAssignableBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveAssignableBase<T, D, True> :
    public UniquePtrDeleterMoveConstructibleBase<T, D> {
  using Base = UniquePtrDeleterMoveConstructibleBase<T, D>;

public:
  using Base::Base;
  using Base::deleter;
  using Base::reset;
  using Base::release;

  UniquePtrDeleterMoveAssignableBase() = default;
  UniquePtrDeleterMoveAssignableBase(UniquePtrDeleterMoveAssignableBase const&) = default;
  UniquePtrDeleterMoveAssignableBase(UniquePtrDeleterMoveAssignableBase&& ptr) = default;
  auto operator=(UniquePtrDeleterMoveAssignableBase const&) -> UniquePtrDeleterMoveAssignableBase& = default;
  CDS_ATTR(constexpr(14)) auto operator=(UniquePtrDeleterMoveAssignableBase&& ptr) noexcept
      -> UniquePtrDeleterMoveAssignableBase& {
    if (this == &ptr) {
      return *this;
    }

    reset(ptr.release());
    deleter() = fwd<D>(ptr.deleter());
    return *this;
  }
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDeleterMoveAssignableBase<T, D, False> :
    public UniquePtrDeleterMoveConstructibleBase<T, D> {
  using Base = UniquePtrDeleterMoveConstructibleBase<T, D>;

public:
  using Base::Base;

  UniquePtrDeleterMoveAssignableBase() = default;
  UniquePtrDeleterMoveAssignableBase(UniquePtrDeleterMoveAssignableBase const&) = default;
  UniquePtrDeleterMoveAssignableBase(UniquePtrDeleterMoveAssignableBase&& ptr) = default;
  auto operator=(UniquePtrDeleterMoveAssignableBase const&) -> UniquePtrDeleterMoveAssignableBase& = default;
  auto operator=(UniquePtrDeleterMoveAssignableBase&& ptr) -> UniquePtrDeleterMoveAssignableBase& = delete;
};

template <typename T, typename D> class UniquePtrTransferBase :
    public UniquePtrDeleterMoveAssignableBase<RemoveExtent<T>, D> {
  using Base = UniquePtrDeleterMoveAssignableBase<RemoveExtent<T>, D>;

public:
  using Base::Base;
  using Base::deleter;
  using Base::reset;

  template <typename U, typename E, EnableIf<And<
      IsConvertible<U*, T*>,
      Eq<IsArray<T>, IsArray<U>>,
      IsLValRef<E>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) UniquePtrTransferBase(UniquePtrTransferBase<U, E>&& ptr) noexcept :
      Base{ptr.release(), ptr.deleter()} {}

  template <typename U, typename E, EnableIf<And<
      IsConvertible<U*, T*>,
      Eq<IsArray<T>, IsArray<U>>,
      Not<IsLValRef<E>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) UniquePtrTransferBase(UniquePtrTransferBase<U, E>&& ptr) noexcept :
      Base{ptr.release(), mv(ptr.deleter())} {}

  template <typename U, typename E, EnableIf<And<
      IsConvertible<U*, T*>,
      Eq<IsArray<T>, IsArray<U>>
  >> = 0> CDS_ATTR(constexpr(14)) auto operator=(UniquePtrTransferBase<U, E>&& ptr) noexcept -> UniquePtrTransferBase& {
    static_assert(noexcept(deleter() = fwd<E>(ptr.deleter())),
        "UniquePtr transfer requires deleter to be noexcept assignable");
    reset(ptr.release());
    deleter() = fwd<E>(ptr.deleter());
    return *this;
  }

  UniquePtrTransferBase() = default;
  UniquePtrTransferBase(UniquePtrTransferBase const&) = default;
  UniquePtrTransferBase(UniquePtrTransferBase&& ptr) = default;
  auto operator=(UniquePtrTransferBase const&) -> UniquePtrTransferBase& = default;
  auto operator=(UniquePtrTransferBase&&) -> UniquePtrTransferBase& = default;
};

template <typename T, typename D, typename = typename IsVoid<RemoveCVRef<RemoveExtent<T>>>::Type>
class UniquePtrDereferencingBase;

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDereferencingBase<T, D, False> :
    public UniquePtrTransferBase<T, D> {
  using Base = UniquePtrTransferBase<T, D>;

public:
  using Base::Base;
  using Base::get;

  UniquePtrDereferencingBase() = default;
  UniquePtrDereferencingBase(UniquePtrDereferencingBase const&) = default;
  UniquePtrDereferencingBase(UniquePtrDereferencingBase&& ptr) = default;
  auto operator=(UniquePtrDereferencingBase const&) -> UniquePtrDereferencingBase& = default;
  auto operator=(UniquePtrDereferencingBase&&) -> UniquePtrDereferencingBase& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const CDS_ATTR(noexcept(noexcept(*get()))) -> T& {
    return *get();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> T* {
    return get();
  }
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrDereferencingBase<T[], D, False> :
    public UniquePtrTransferBase<T[], D> {
  using Base = UniquePtrTransferBase<T[], D>;

public:
  using Base::Base;
  using Base::get;

  UniquePtrDereferencingBase() = default;
  UniquePtrDereferencingBase(UniquePtrDereferencingBase const&) = default;
  UniquePtrDereferencingBase(UniquePtrDereferencingBase&& ptr) = default;
  auto operator=(UniquePtrDereferencingBase const&) -> UniquePtrDereferencingBase& = default;
  auto operator=(UniquePtrDereferencingBase&&) -> UniquePtrDereferencingBase& = default;

  template <typename I> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](I idx) const
      CDS_ATTR(noexcept(noexcept(*get()))) -> T& {
    return *get();
  }
};

template <typename T, typename D> class CDS_ATTR(ebo) UniquePtrObservableBase :
    public UniquePtrDereferencingBase<T, D> {
  using Base = UniquePtrDereferencingBase<T, D>;

public:
  using Base::Base;
  using Base::get;

  UniquePtrObservableBase() = default;
  UniquePtrObservableBase(UniquePtrObservableBase const&) = delete;
  UniquePtrObservableBase(UniquePtrObservableBase&& ptr) = default;
  auto operator=(UniquePtrObservableBase const&) -> UniquePtrObservableBase& = delete;
  auto operator=(UniquePtrObservableBase&&) -> UniquePtrObservableBase& = default;

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return get();
  }
};

template <typename T, typename D = DefaultDeleter<T>> class CDS_ATTR(ebo) UniquePtr :
    public UniquePtrObservableBase<T, D> {
  using Base = UniquePtrObservableBase<T, D>;

public:
  using Base::Base;

  UniquePtr() = default;
  UniquePtr(UniquePtr const&) = delete;
  UniquePtr(UniquePtr&& ptr) = default;
  auto operator=(UniquePtr const&) -> UniquePtr& = delete;
  auto operator=(UniquePtr&&) -> UniquePtr& = default;
};

template <typename T, typename...A> CDS_ATTR(constexpr(20)) auto makeUnique(A&&... args)
    -> ReturnIf<UniquePtr<T>, Not<IsArray<T>>> {
  return UniquePtr<T>{new T(fwd<A>(args)...)};
}

template <typename T> CDS_ATTR(constexpr(20)) auto makeUnique(Size size)
    -> ReturnIf<UniquePtr<T>, IsUnboundedArray<T>> {
  return UniquePtr<T>{new RemoveExtent<T>[size]()};
}

template <typename T> auto makeUnique(Size size) -> ReturnIf<void, IsBoundedArray<T>> = delete;

template <typename T> CDS_ATTR(constexpr(20)) auto makeUniqueForOverwrite() -> ReturnIf<UniquePtr<T>, Not<IsArray<T>>> {
  return UniquePtr<T>{new T};
}

template <typename T> CDS_ATTR(constexpr(20)) auto makeUniqueForOverwrite(Size size)
    -> ReturnIf<UniquePtr<T>, IsUnboundedArray<T>> {
  return UniquePtr<T>{new RemoveExtent<T>[size]};
}

template <typename T> auto makeUniqueForOverwrite(Size size) -> ReturnIf<void, IsBoundedArray<T>> = delete;

template <typename T, typename A = Allocator<T>, typename... AllocArgs>
CDS_ATTR(constexpr(20)) auto makeUniqueUninitialized(AllocArgs&&... args)
    -> ReturnIf<UniquePtr<T, UninitializedDeleter<T, A>>, Not<IsArray<T>>> {
  A alloc {fwd<AllocArgs>(args)...};
  auto ptr = alloc.allocate(1);
  return UniquePtr<T, UninitializedDeleter<T, A>>{ptr, UninitializedDeleter<T, A>{mv(alloc)}};
}

template <typename T, typename A = Allocator<T>, typename... AllocArgs>
CDS_ATTR(constexpr(20)) auto makeUniqueUninitialized(Size size, AllocArgs&&... args)
    -> ReturnIf<UniquePtr<T>, IsUnboundedArray<T>> {
  A alloc {fwd<AllocArgs>(args)...};
  auto ptr = alloc.allocate(size);
  return UniquePtr<T, UninitializedDeleter<T, A>>{ptr, UninitializedDeleter<T, A>{size, mv(alloc)}};
}

template <typename T, typename... Args>
auto makeUniqueUninitialized(Size size, Args&&... args) -> ReturnIf<void, IsBoundedArray<T>> = delete;

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() == rhs.get();
}

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() != rhs.get();
}

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() < rhs.get();
}

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() > rhs.get();
}

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() <= rhs.get();
}

template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs.get() >= rhs.get();
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() == rhs;
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() != rhs;
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() < rhs;
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() > rhs;
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() <= rhs;
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> bool {
  return lhs.get() >= rhs;
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs == rhs.get();
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs != rhs.get();
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs < rhs.get();
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs > rhs.get();
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs <= rhs.get();
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return lhs >= rhs.get();
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return lhs.get();
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return !lhs.get();
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return lhs.get() < nullptr;
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return lhs.get() > nullptr;
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return lhs.get() <= nullptr;
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> bool {
  return lhs.get() >= nullptr;
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return rhs.get();
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return !rhs.get();
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return nullptr < rhs.get();
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return nullptr > rhs.get();
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return nullptr <= rhs.get();
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> bool {
  return nullptr >= rhs.get();
}

#if CDS_ATTR(spaceship)
template <typename T1, typename D1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    UniquePtr<T1, D1> const& lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> decltype(lhs.get() <=> rhs.get()) {
  return lhs.get() <=> rhs.get();
}

template <typename T1, typename D1, typename T2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    UniquePtr<T1, D1> const& lhs, T2* rhs
) noexcept -> decltype(lhs.get() <=> rhs) {
  return lhs.get() <=> rhs;
}

template <typename T1, typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    T1* lhs, UniquePtr<T2, D2> const& rhs
) noexcept -> decltype(lhs <=> rhs.get()) {
  return lhs <=> rhs.get();
}

template <typename T1, typename D1> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    UniquePtr<T1, D1> const& lhs, Null
) noexcept -> decltype(lhs.get() <=> nullptr) {
  return lhs.get() <=> nullptr;
}

template <typename T2, typename D2> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    Null, UniquePtr<T2, D2> const& rhs
) noexcept -> decltype(nullptr <=> rhs.get()) {
  return nullptr <=> rhs.get();
}
#endif // #if CDS_ATTR(spaceship)
} // namespace impl

using impl::UniquePtr;

using impl::makeUnique;
using impl::makeUniqueForOverwrite;
using impl::makeUniqueUninitialized;
} // namespace cds

#endif // #ifndef CDS_MEMORY_UNIQUE_PTR_HPP
